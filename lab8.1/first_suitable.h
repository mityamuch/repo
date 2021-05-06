#pragma once
#include <iostream>
#include <list>
#include "memory.h"
#include <algorithm>

class block : public kusokpam
{
	friend class first_suitable;

public:
	block(size_t size,char* pointer )
		:m_size(size), kusokpam(pointer){}

	size_t get_size() override {
		return m_size;
	}

private:
	size_t m_size;
};

class first_suitable:public memory
{
public:
	first_suitable(size_t N):memory(N) {
		freeblocks.emplace_back(N, m_buffer);
	}

	void print_leaked_blocks() override
	{
		for (auto& i : usedblocks)
		{
			std::cout << (void*)i.m_pointer << "\t" << i.get_size() << std::endl;
		}
	}
	
private:
	kusokpam* try_allocate_block(size_t size) override{
		for (auto& i : freeblocks)
		{
			if (i.m_size >= size) {
				char* pointer_copy = i.m_pointer;
				i.m_size -= size;
				i.m_pointer += size;
				auto it = std::find_if(usedblocks.begin(), usedblocks.end(), [&](const block& b) {return b > pointer_copy;});
				return &(*usedblocks.emplace(it, size, pointer_copy));
			}
		}
		return nullptr;
	}

	void compact() override{
		auto buffer_copy = m_buffer;
		for (auto& i : usedblocks)
		{
			if (i.m_pointer != buffer_copy) {
				memcpy(buffer_copy, i.m_pointer, i.get_size());
			}
			i.m_pointer = buffer_copy;
			buffer_copy += i.get_size();
		}
		freeblocks.clear();
		freeblocks.emplace_back(m_size - (buffer_copy - m_buffer), buffer_copy);
	}

	std::pair<char*, size_t> find_used_block(kusokpam* pam) override 
	{
		auto it = std::find_if(usedblocks.begin(), usedblocks.end(), [&](const block& b) {return pam == &b;});
		if (it == usedblocks.end())
		{
			throw(allocassert("cant find deallocated block"));
		}

		block resultblock(it->m_size, it->m_pointer);
		usedblocks.erase(it);
		return std::make_pair(resultblock.m_pointer, resultblock.m_size);
	}

	std::pair<char*, size_t> try_extend_left(char* block_to_free, size_t size) override
	{
		auto it = std::find_if(freeblocks.begin(), freeblocks.end(), [&](const block& b) {return b > block_to_free;});

		if (it != freeblocks.begin()) {
			if (std::prev(it)->m_pointer + std::prev(it)->m_size == block_to_free) {
				size += (--it)->m_size;
				freeblocks.erase(it);
			}
		}
		return std::make_pair(block_to_free, size);
	}

	std::pair<char*, size_t> try_extend_right(char* block_to_free, size_t size) override
	{
		auto it = std::find_if(freeblocks.begin(), freeblocks.end(), [&](const block& b) {return b > block_to_free;});

		if (std::next(it) != freeblocks.end()) {
			if (std::next(it)->m_pointer == block_to_free + size) {
				size += (++it)->m_size;
				freeblocks.erase(it);
			}
		}
		return std::make_pair(block_to_free, size);
	}

	void add_to_free_blocks(char* block_to_free, size_t size) override
	{
		auto it = std::find_if(freeblocks.begin(), freeblocks.end(), [&](const block& b) {return b > block_to_free;});
		freeblocks.emplace(it, size, block_to_free);
	}

private:
	std::list<block> freeblocks;
	std::list<block> usedblocks;
};
