#pragma once


class v_ticket
{
public:
	virtual ~v_ticket();
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



private:

	int m_digits[6];
	int m_id;
};