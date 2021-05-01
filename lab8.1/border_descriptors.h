#pragma once
#include "memory.h"
#include <list>
#include <iostream>



class userblock : public kusokpam
{
public:
	userblock(char* pointer)
		:m_pointer(pointer) {}

	std::string read(size_t count) {
		std::string str;
		if (count > *((int*)(m_pointer + sizeof(bool))))
			throw(allocassert("ti chto durak lol"));
		for (size_t i = 0; i < count; i++)
		{
			str += m_pointer[i];
		}
		return str;
	}

	void write(std::string  bytes) {

		if (bytes.size() > *((int*)(m_pointer + sizeof(bool))))
			throw(allocassert("ti chto durak lol"));
		char* m_pointer_copy = m_pointer;
		for (auto& i : bytes)
		{
			*m_pointer_copy = i;
			m_pointer_copy++;
		}
	}


private:
	char* m_pointer;
	friend class border_descriptors;
};

struct block_suffix
{
	int32_t size;
	bool isused;
};

struct block_prefix
{
	bool isused;
	int32_t size;
	block_prefix* next;
	block_prefix* prev;
};

const int UBLOCKINF = 2 * sizeof(bool) + sizeof(block_prefix*);

class border_descriptors:public memory
{
public:
	border_descriptors(size_t N):memory(N){
		
		*(bool*)(m_buffer) = true;
		*(bool*)(m_buffer+m_size-sizeof(bool)) = true;
		avail = (block_prefix*)m_buffer + sizeof(bool);
		avail->isused = true;
		avail->next = nullptr;
		avail->prev = nullptr;
		avail->size =m_size-2*sizeof(bool);
		
		block_suffix* suffix = (block_suffix*)m_buffer + m_size - sizeof(block_suffix) - sizeof(bool);
		
		suffix->isused = false;
		suffix->size = m_size - 2 * sizeof(bool);


	}

	void deallocate(kusokpam* pam) {}

	void print_leaked_blocks() {
		for (auto& i : usedblocks)
		{
			std::cout << (void*)i.m_pointer << "\t" << *((int*)(i.m_pointer+sizeof(bool))) << std::endl;
		}
	}

	kusokpam* findfreeblock(size_t size) override {
		for (auto i=avail;i!=nullptr;i=i->next)
		{
			if (i->size- UBLOCKINF >= size) {
			
				if( i->size<= size + sizeof(block_prefix) + sizeof(block_suffix) + UBLOCKINF){
					if(i->prev!=nullptr)
						(i->prev )->next=i->next;
					else
						avail = i->next;
					if(i->next!=nullptr)
						(i->next)->prev = i->prev;
				}
				else
				{
					block_prefix* newpos = (block_prefix * )((char*)i + size + UBLOCKINF);
					memcpy(newpos,i, (char*)newpos-(char*)i);
					if (i->next != nullptr)
						(newpos->next)->prev = newpos;
					if(i->prev!=nullptr)
						(newpos->prev)->next = newpos;
					else
						avail=newpos;
					block_suffix* suffix = (block_suffix*)((char*)i + i->size - sizeof(block_suffix));
					suffix->size = i->size - size - UBLOCKINF;
					newpos->size = suffix->size;
				}

				i->isused = true;
				i->size = size + UBLOCKINF;
				*(bool*)((char*)i + i->size - sizeof(bool)) = true;
				usedblocks.emplace_back((char*)i);


			}

		}
		return nullptr;
	
	}

	void compact() override {	
	}



private:
	std::list<userblock> usedblocks;
	block_prefix* avail;
};
