#pragma once
#include <string>
class allocassert:public std::exception {
public:
	using exception::exception;

};


class kusokpam
{
public:
	kusokpam() = delete;
	kusokpam(const kusokpam& a )=delete;
	kusokpam(char* pointer)
		: m_pointer(pointer)
	{}
	virtual ~kusokpam() {};
	virtual size_t get_size() = 0;
	std::string read()
	{
		std::string str;
		for (size_t i = 0; m_pointer[i] != 0; i++)
		{
			str += m_pointer[i];
		}
		return str;
	}

	void write(std::string  bytes)
	{
		if (bytes.size() + 1 > get_size())
			throw(allocassert("ti chto durak lol"));
		char* m_pointer_copy = m_pointer;
		for (auto& i : bytes)
		{
			*m_pointer_copy = i;
			m_pointer_copy++;
		}
		*m_pointer_copy = 0;
	}

	bool operator> (char* pointer) const
	{
		return m_pointer > pointer;
	}

protected:
	char* m_pointer;
};

class memory {
public:
	kusokpam* allocate(size_t size) {
		auto result=try_allocate_block(size);
		if (result == nullptr) {
			compact();
			result= try_allocate_block(size);
			if (result == nullptr)
				throw(allocassert("allocation exception"));
		}
		return result;
	}

	void deallocate(kusokpam* pam)
	{
		auto block = find_used_block(pam);
		block = try_extend_left(block.first, block.second);
		block = try_extend_right(block.first, block.second);
		add_to_free_blocks(block.first, block.second);
	}

	memory(size_t N) {
		m_buffer = new char [N];
		m_size = N;
	}

	~memory(){
		delete[] m_buffer;
	}
	virtual void print_leaked_blocks() = 0;

private:
	virtual kusokpam* try_allocate_block(size_t size) = 0;
	virtual void compact() = 0;

	virtual std::pair<char*, size_t> find_used_block(kusokpam*) = 0;
	virtual std::pair<char*, size_t> try_extend_left(char* block, size_t size) = 0;
	virtual std::pair<char*, size_t> try_extend_right(char* block, size_t size) = 0;
	virtual void add_to_free_blocks (char* block, size_t size) = 0;
protected:
	char* m_buffer;
	size_t m_size;
};