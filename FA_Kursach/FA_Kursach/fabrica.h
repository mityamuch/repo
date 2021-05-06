
#include "tickets.h"
#include <memory>
#include <ctime>
#pragma once

class abstr_factory
{
public:

	virtual ~abstr_factory();
	virtual std::shared_ptr<v_ticket> maketicket() = 0;
	 
private:
};


class fabric_5_36 :public abstr_factory
{
public:
	fabric_5_36() {
		serial = 0;
	}
	~fabric_5_36 ();
	std::shared_ptr<v_ticket> maketicket() override {
		srand(time(0));
		int digits[5];
		for (size_t i = 0; i < 5; )
		{
			int a = 1 + rand() % 36;
			bool flag=true;
			for (size_t k = 0; k < i; k++)
			{
				if (digits[k] == a) {
					flag = false;
					break;
				}
			}
			if (flag) {
				digits[i] = a;
				i++;
			}
		}
		serial += 1;
		return  std::shared_ptr<v_ticket>{(v_ticket*)(new ticket_5_36(digits, serial))};
	}

private:
	int serial;
};


