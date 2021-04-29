#pragma once
#include <list>
#include "memory.h"
#include <algorithm>
class block : public kusokpam
{
public:
	block(size_t size,char* pointer )
		:m_size(size),m_pointer(pointer){}

	std::string read(size_t count) {
		std::string str;
		if (count > m_size)
			throw(allocassert("ti chto durak lol"));
		for (size_t i = 0; i <count; i++)
		{
			str += m_pointer[i];
		}
		return str;
	}

	void write(std::string  bytes) {

		if(bytes.size()>m_size)
			throw(allocassert("ti chto durak lol"));
		char* m_pointer_copy = m_pointer;
		for (auto& i : bytes)
		{
			*m_pointer_copy = i;
			m_pointer_copy++;
		}
	}

private:
	size_t m_size;
	char * m_pointer;
	friend class first_suitable;
};




class first_suitable:public memory
{
public:
	first_suitable(size_t N):memory(N) {
		freeblocks.push_back(block(N, m_buffer));
	}
	~first_suitable();

	void deallocate(kusokpam* pam) {
		auto it = usedblocks.begin();
		for (;it != usedblocks.end(); it++)
		{
			if ((static_cast<block*> (pam)->m_pointer == it->m_pointer  )){
				break;
			}
		}
		if (it==usedblocks.end())
		{
			throw(allocassert("cant find deallocated block"));
		}

		block resultblock(it->m_size, it->m_pointer);
		usedblocks.erase(it);

		it = freeblocks.begin();
		for (;it != freeblocks.end(); it++)
		{
			if ((static_cast<block*> (pam)->m_pointer == it->m_pointer)) {
				break;
			}
		}

		if ( it != freeblocks.begin()) {
			if (std::prev(it)->m_pointer + std::prev(it)->m_size == resultblock.m_pointer) {
				(--it)->m_size += resultblock.m_size;
			}
			else
			{
				it=freeblocks.emplace(it,resultblock.m_size,resultblock.m_pointer);
			}
			
		}
		else
		{
			it = freeblocks.emplace(it, resultblock.m_size, resultblock.m_pointer);
		}



		if (std::next(it) != freeblocks.end()) {
			if (std::next(it)->m_pointer == resultblock.m_pointer+resultblock.m_size) {
				it->m_size += std::next(it)->m_size;
				freeblocks.erase(std::next(it));
			}
		}
	}



	
private:
	kusokpam* findfreeblock(size_t size) override{
		for (auto& i : freeblocks)
		{
			if (i.m_size >= size) {
				char* pointer_copy = i.m_pointer;
				i.m_size -= size;
				i.m_pointer += size;
				auto it = usedblocks.begin();
				for (;it != usedblocks.end(); it++)
				{
					if (it->m_pointer > pointer_copy)
						break;
				}
				return &(*usedblocks.emplace(it, size, pointer_copy));
			}

		}
		return nullptr;
	}
	void compact() override{}


	


private:
	std::list<block> freeblocks;
	std::list<block> usedblocks;


};