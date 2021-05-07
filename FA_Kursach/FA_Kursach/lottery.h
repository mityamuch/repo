#pragma once
#include "fabrica.h"
#include <deque>


const int size_of_circulation = 25000000;


struct win_ticket
{
	int win;//1-100 2-500 3-1000 4-10000 5-100000
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
	deque<win_ticket> start(abstr_factory& factory) {
		//производство билетов
		std::deque<v_ticket> Tickets;
		for (size_t i = 0; i < size_of_circulation; i++)
		{
			Tickets.push_back(factory.maketicket());
		}
		//делание тиража
		std::deque<v_ticket> Tirag;
		for (auto& ticket : Tickets)
		{
			srand(time(0));
			int randomfactor= 1 + rand() % 100;
			if (randomfactor <= 70)
				Tirag.push_back(ticket);

		}
		// делание выигрышного билета
		std::shared_ptr<v_ticket> win_ticket = factory.maketicket();
		std::vector<int> win_digits = win_ticket->getdigits();



		//поиск выигравших билетов и занесение их в список выигравших билетов
		std::deque<win_ticket> Prize_tickets;

		for (auto& c : win_digits)
		{
			for (auto& ticket : Tirag)
			{
				std::vector<int> ticket_digits = ticket.getdigits();
				bool flag = false;
				for (auto& digit : ticket_digits)
				{
					if (digit = c) 
						flag = true;
				}
				if (flag) 
				{
					//ищем в списке выигравших билетов билет с таким же id
					bool find = false;
					//запоминаем найденный элемент
					std::shared_ptr<v_ticket> find_ticket;
					for (auto& prizeticket : Prize_tickets)
					{
						if (ticket.getid() == prizeticket.ticket.getid()) {
							find = true;
							find_ticket = ticket&;
							break;
						}

					}




				}


			}
		}



	}
};

