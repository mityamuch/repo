#pragma once
#include "fabrica.h"
#include <deque>


const int size_of_circulation = 25000000;


struct win_ticket
{
	int win;
	std::shared_ptr<v_ticket> ticket;
};


template <template<typename> typename T>
class Lottery
{
public:
	Lottery();
	~Lottery();

	T<win_ticket> start_5_36(){
	return	start(fabric_5_36());
	}
	T<win_ticket> start_6_49() {
		return	start(fabric_6_49());
	}




private:
	T<win_ticket> start(abstr_factory& factory) {
		std::deque<v_ticket> Tickets;
		for (size_t i = 0; i < size_of_circulation; i++)
		{
			Tickets.push_back(factory.maketicket());
		}
		std::shared_ptr<v_ticket> win_ticket = factory.maketicket();
		std::vector<int> win_digits = win_ticket->getdigits();
		for (auto& c : win_digits)
		{





		}



	}
};

