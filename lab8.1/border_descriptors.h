#pragma once
#include "memory.h"
#include <list>
#include <iostream>

#pragma pack(push, 1)
struct free_block_suffix
{
	size_t size;
	bool isused;
};

struct free_block_prefix
{
	bool isused;
	size_t size;
	free_block_prefix* next;
	free_block_prefix* prev;
};

struct used_block_prefix
{
	bool isused;
	size_t size;
};

struct used_block_suffix
{
	bool isused;
};

#pragma pack(pop)

const int extra_free_block_size = sizeof(free_block_prefix) + sizeof(free_block_suffix);
const int extra_used_block_size = sizeof(used_block_prefix) + sizeof(used_block_suffix);

void* advance(void* p, size_t size)
{
	return ((char*)p + size);
}

void* back(void* p, size_t size)
{
	return ((char*)p - size);
}

class userblock : public kusokpam
{
	friend class border_descriptors;
public:
	userblock(char* pointer)
		:kusokpam(pointer) {}

	size_t get_size() override
	{
		return ((used_block_prefix*)back(m_pointer, sizeof(used_block_prefix)))->size;
	}
};

class border_descriptors:public memory
{
public:
	border_descriptors(size_t N):memory(N){
		
		*(bool*)(m_buffer) = true;
		*(bool*)(m_buffer+m_size-sizeof(bool)) = true;
		m_avail = (free_block_prefix*)(m_buffer + sizeof(bool));
		m_avail->isused = false;
		m_avail->next = nullptr;
		m_avail->prev = nullptr;
		m_avail->size = m_size-2*sizeof(bool);
		
		free_block_suffix* suffix = (free_block_suffix*)advance(m_avail, int(m_avail->size - sizeof(free_block_suffix)));
		
		suffix->isused = false;
		suffix->size = m_avail->size;
	}

	void print_leaked_blocks() override
	{
		for (auto& i : usedblocks)
		{
			std::cout << (void*)i.m_pointer << "\t" << i.get_size() << std::endl;
		}
	}

private:
	kusokpam* try_allocate_block(size_t size) override {
		//	Чтобы быть уверенным, что потом при освобождении в новый блок поместятся все структуры свободного блока,
		//	возможно нужно запросить чуть больше: 
		if (size + extra_used_block_size < extra_free_block_size)
			size = extra_free_block_size - extra_used_block_size;
		//	Ищем подходящий свободный блок
		for (auto i = m_avail;i != nullptr;i = i->next)
		{
			if (i->size - extra_used_block_size >= size) {

				if (i->size - size - extra_used_block_size <= extra_free_block_size) {
					// Делаем свободный блок занятым
					if (i->prev != nullptr)
						(i->prev)->next = i->next;
					else
						m_avail = i->next;
					if (i->next != nullptr)
						(i->next)->prev = i->prev;
				}
				else
				{
					//	откусываем от свободного блока
					free_block_prefix* newpos = (free_block_prefix*)advance(i, size + extra_used_block_size);
					memcpy(newpos, i, sizeof(free_block_prefix));
					if (newpos->next != nullptr)
						(newpos->next)->prev = newpos;
					if (newpos->prev != nullptr)
						(newpos->prev)->next = newpos;
					else
						m_avail = newpos;
					newpos->size = newpos->size - size - extra_used_block_size;
					free_block_suffix* suffix = (free_block_suffix*)advance(newpos, newpos->size - sizeof(free_block_suffix));
					suffix->size = newpos->size;
					i->size = size + extra_used_block_size;
				}

				//	заполняем префикс/суффикс нового занятого блока
				used_block_prefix* new_used_block = (used_block_prefix*)i;
				new_used_block->isused = true;
				used_block_suffix* new_used_block_suffix = (used_block_suffix*)advance(
					new_used_block,
					new_used_block->size - sizeof(used_block_suffix));
				new_used_block_suffix->isused = true;

				auto it = std::find_if(usedblocks.begin(), usedblocks.end(),
					[&](const userblock& b) {return b > (char*)new_used_block;});
				return &(*usedblocks.emplace(it, (char*)advance(new_used_block, sizeof(used_block_prefix))));
			}
		}
		return nullptr;
	}

	void compact() override {
		auto buffer_copy = m_buffer + sizeof(bool);
		for (auto& i : usedblocks)
		{
			size_t size = i.get_size();
			char* block_start = (char*)back(i.m_pointer, sizeof(used_block_prefix));
			if (block_start != buffer_copy) {
				memcpy(buffer_copy, block_start, size);
			}
			i.m_pointer = (char*)advance(buffer_copy, sizeof(used_block_prefix));
			buffer_copy += size;
		}

		if (m_size - sizeof(bool) - (buffer_copy - m_buffer) < extra_free_block_size)
		{
			m_avail = nullptr;
			return;
		}
		m_avail = (free_block_prefix*)buffer_copy;
		m_avail->isused = false;
		m_avail->next = nullptr;
		m_avail->prev = nullptr;
		m_avail->size = m_size - (buffer_copy - m_buffer) - sizeof(bool);

		free_block_suffix* suffix = (free_block_suffix*)advance(m_avail, m_avail->size - sizeof(free_block_suffix));

		suffix->isused = false;
		suffix->size = m_avail->size;
	}

	std::pair<char*, size_t> find_used_block(kusokpam* pam) override
	{
		auto it = std::find_if(usedblocks.begin(), usedblocks.end(), [&](const userblock& b) {return pam == &b;});
		if (it == usedblocks.end())
			throw allocassert("No such block");
		used_block_prefix* used_block = (used_block_prefix*)back(((userblock*)pam)->m_pointer, sizeof(used_block_prefix));
		usedblocks.erase(it);
		return std::make_pair((char*)used_block, used_block->size);
	}

	std::pair<char*, size_t> try_extend_left(char* block, size_t size) override
	{
		used_block_suffix* prev_block_suffix = (used_block_suffix*)back(block, sizeof(used_block_suffix));
		if (!prev_block_suffix->isused)
		{
			free_block_suffix* prev_free_block_suffix = (free_block_suffix*)back(block, sizeof(free_block_suffix));
			free_block_prefix* prev_block_prefix = (free_block_prefix*)back(block, prev_free_block_suffix->size);
			prev_block_prefix->size += size;

			//	убираем блок слева из списка свободных
			if (prev_block_prefix->prev)
				prev_block_prefix->prev->next = prev_block_prefix->next;
			else
				m_avail = prev_block_prefix->next;
			if (prev_block_prefix->next)
				prev_block_prefix->next->prev = prev_block_prefix->prev;

			return std::make_pair ((char*)prev_block_prefix, prev_block_prefix->size);
		}
		return std::make_pair(block, size);
	}
	
	std::pair<char*, size_t> try_extend_right(char* block, size_t size) override
	{
		free_block_prefix* next_block_prefix = (free_block_prefix*)advance(block, size);
		free_block_prefix* cur_block_prefix = (free_block_prefix*)block;
		if (!next_block_prefix->isused)
		{
			size += next_block_prefix->size;

			//	убираем блок справа из списка свободных
			if (next_block_prefix->prev)
				next_block_prefix->prev->next = next_block_prefix->next;
			else
				m_avail = next_block_prefix->next;
			if (next_block_prefix->next)
				next_block_prefix->next->prev = next_block_prefix->prev;
		}
		return std::make_pair(block, size);
	}

	void add_to_free_blocks(char* block, size_t size) override
	{
		//	дозаполняем префикс и суффикс объединенного блока
		free_block_prefix* cur_block_prefix = (free_block_prefix*)block;
		free_block_suffix* cur_block_suffix = (free_block_suffix*)advance(block, size - sizeof(free_block_suffix));
		cur_block_prefix->isused = false;
		cur_block_prefix->size = size;
		cur_block_suffix->isused = false;
		cur_block_suffix->size = size;

		//	вставляем его в начало списка свободных
		cur_block_prefix->next = m_avail;
		cur_block_prefix->prev = nullptr;
		if (cur_block_prefix->next)
			cur_block_prefix->next->prev = cur_block_prefix;
		m_avail = cur_block_prefix;
	}

private:
	std::list<userblock> usedblocks;
	free_block_prefix* m_avail;
};
