#pragma once
#include <vector>

class v_ticket
{
public:
	virtual ~v_ticket() {};
	virtual std::vector<int> getdigits() = 0;
	virtual int getid() = 0;
private:
};

class ticket_5_36:public v_ticket
{
public:

	ticket_5_36(int* digits, int serial) :m_id(serial)
	{
		for (size_t i = 0; i < 5; i++)
		{
			m_digits[i] = digits[i];
		}
	}

	std::vector<int> getdigits() override{
		std::vector<int> digits;
		for (size_t i = 0; i < 5; i++)
		{
			digits.push_back(m_digits[i]);
		}

		return digits;
	}

	int getid() override {
		return m_id;
	}

private:

	int m_digits[5];
	int m_id;
};


class ticket_6_49 :public v_ticket
{
public:
	ticket_6_49(int* digits, int serial) :m_id(serial)
	{
		for (size_t i = 0; i < 6; i++)
		{
			m_digits[i] = digits[i];
		}
	}
	std::vector<int> getdigits() override{
		std::vector<int> digits;
		for (size_t i = 0; i < 6; i++)
		{
			digits.push_back(m_digits[i]);
		}

		return digits;

	}

	int getid()override {
		return m_id;
	}

private:

	int m_digits[6];
	int m_id;
};