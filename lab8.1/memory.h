#pragma once
#include <string>
class allocassert:public std::exception {
public:
	using exception::exception;

};


class kusokpam
{
public:
	kusokpam()= default;
	virtual ~kusokpam(){};
	kusokpam(const kusokpam& a )=delete;
	virtual std::string read(size_t count) = 0;
	virtual void write(std::string  bytes) = 0;
};

class memory {
public:
	kusokpam* allocate(size_t size) {
		auto result=findfreeblock(size);
		if (result == nullptr) {
			compact();
			result= findfreeblock(size);
			if (result == nullptr)
				throw(allocassert("allocation exception"));
		}
		return result;
	}

	memory(size_t N) {
		m_buffer = new char [N];
		m_size = N;
	}

	~memory(){
		delete[] m_buffer;
	}
	virtual void deallocate(kusokpam* pam) = 0;
	
private:
	virtual kusokpam* findfreeblock(size_t size) = 0;
	virtual void compact() = 0;
protected:
	char* m_buffer;
	size_t m_size;
};