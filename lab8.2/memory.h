#pragma once
#include <math.h>
#include <vector>

struct FreeBlockPrefix
{
	bool isUsed;
	int k;
	FreeBlockPrefix* prev;
	FreeBlockPrefix* next;
};

const size_t LogMinBlockSize = (size_t)ceil(log2(sizeof(FreeBlockPrefix)));

struct UsedBlockPrefix
{
	bool isUsed;
	int k;
};

class Memory
{
public:
	Memory(size_t size)
		: m_N((size_t)ceil(log2(size)))
		, m_buffer(new char[1 << m_N])
		, m_avail(new FreeBlockPrefix[m_N - LogMinBlockSize + 1])
	{
		for (size_t i = LogMinBlockSize; i <= m_N; ++i)
		{
			auto& avail =  m_avail[i - LogMinBlockSize];
			if (i == m_N)
			{
				auto freeBlock = (FreeBlockPrefix*)m_buffer;
				avail.next = freeBlock;
				avail.prev = freeBlock;
				freeBlock->next = &avail;
				freeBlock->prev = &avail;
				freeBlock->isUsed = false;
				freeBlock->k = m_N;
			}
			else
			{
				avail.next = &avail;
				avail.prev = &avail;
			}
		}
	}

	~Memory()
	{
		delete[] m_buffer;
		delete[] m_avail;
	}

	char* Alloc(size_t size)
	{
		//	Step 1
		size_t k = (size_t)ceil(log2(size));
		k = k < LogMinBlockSize ? LogMinBlockSize : k;
		size_t j = k;
		for (; j <= m_N; ++j)
		{
			if (m_avail[j - LogMinBlockSize].next != &m_avail[j - LogMinBlockSize])
				break;
		}
		if (j > m_N)
			return nullptr;
		auto& avail = m_avail[j - LogMinBlockSize];

		//	Step 2
		FreeBlockPrefix* block = avail.next;
		block->next->prev = block->prev;
		block->prev->next = block->next;
		block->isUsed = true;

		//	Step 3
		while (j != k)
		{
			//	Step 4
			--j;
			FreeBlockPrefix* secondHalf = (FreeBlockPrefix*)(((char*)block) + (1 << j));
			secondHalf->isUsed = 0;
			secondHalf->k = j;
			auto& curAvail = m_avail[j - LogMinBlockSize];
			curAvail.next = secondHalf;
			curAvail.prev = secondHalf;
			secondHalf->next = &curAvail;
			secondHalf->prev = &curAvail;
		}
		return ((char*)block) + sizeof(UsedBlockPrefix);
	}

	void Free(char* block)
	{
		FreeBlockPrefix* curBlock = (FreeBlockPrefix*)(block - sizeof(UsedBlockPrefix));
		size_t k = curBlock->k;
		//	Step 1
		FreeBlockPrefix* doppel = (FreeBlockPrefix * )(m_buffer +
			((size_t)((char*)curBlock - m_buffer) ^ (1 << k)));
		while (k != m_N && !doppel->isUsed && doppel->k == curBlock->k)
		{
			//	Step 2
			doppel->prev->next = doppel->next;
			doppel->next->prev = doppel->prev;
			++k;
			if (doppel < curBlock)
				curBlock = doppel;
			doppel = (FreeBlockPrefix*)(m_buffer +
				((size_t)((char*)curBlock - m_buffer) ^ (1 << k)));
		}

		//	Step 3
		curBlock->isUsed = false;
		curBlock->prev = &m_avail[k - LogMinBlockSize];
		curBlock->next = m_avail[k - LogMinBlockSize].next;
		curBlock->next->prev = curBlock;
		curBlock->prev->next = curBlock;
	}

private:
	size_t m_N;
	char* m_buffer;

	FreeBlockPrefix* m_avail;
};