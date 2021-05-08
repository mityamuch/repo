#pragma once
#include "fabrica.h"
#include <vector>


const int size_of_circulation = 10000;


struct win_ticket_t
{
	int win;//1-100 2-1000 3-10000 4-100000 5-1000000
	std::shared_ptr<v_ticket> ticket;
};

template <template <typename T> typename Container>
class Lottery
{
public:
	void start_5_36(){
	return	start(fabric_5_36());
	}

	void start_6_49() {
		return	start(fabric_6_49());
	}

	void print_results() {

		for (auto& i : m_result)
		{
			std::vector<int> ticket_digits = i.ticket->getdigits();

			std::cout << "n";
			std::cout << i.ticket->getid() << "\t";
			std::cout << "digits:" << "\t";
			for (auto& i : ticket_digits)
			{
				std::cout << i << "  ";
			}
			std::cout << "win" << "\t";
			std::cout << i.win << std::endl;

		}


	}

	void print_stat() {
		int count_100 = 0;
		int count_1000 = 0;
		int count_10000 = 0;
		int count_100000 = 0;
		

		for (auto& i : m_result)
		{
			switch (i.win)
			{
			case 100:

				count_100++;
				break;
			case 1000:
				count_1000++;
				break;
			case 10000:
				count_10000++;
				break;
			case 100000:
				count_100000++;
				break;
			case 1000000:

				std::cout << "winner is id:\t" << i.ticket->getid()<<"\this winnings is 1000000. Congratulations"<< std::endl;
				break;
			case 10000000:

				std::cout << "absolute winner is id:\t" << i.ticket->getid() << "his winnings is 10000000. Congratulations" << std::endl;
				break;
			default:
				break;
			}
			
		}
		std::cout << "the number of players who guessed 1 digit is:\t" << count_100<< std::endl;
		std::cout << "the number of players who guessed 2 digits is:\t" << count_1000<< std::endl;
		std::cout << "the number of players who guessed 3 digits is:\t" << count_10000 << std::endl;
		std::cout << "the number of players who guessed 4 digits is:\t" << count_100000 << std::endl;

	}

	void searchbyid(int id){
		bool flag = false;
		win_ticket_t res;
		for (auto& i : m_result)
		{
			if (i.ticket->getid() == id) {
				res = i;
				flag = true;
			}
		}
		if (flag)
			std::cout << "id:\t" << res.ticket->getid() << "\t"<<"win"<<"\t" << res.win << std::endl << std::endl;
		else
		{
			std::cout << "ticket with this id has not  been found.It looks like you haven't guessed a single number" << std::endl<< std::endl;

		}
	}



	std::vector<win_ticket_t> searchbywin(int win){
		std::vector<win_ticket_t> res;
		for (auto& i : m_result)
		{
			if (i.win == win) {
				res.push_back(i);
			}
		}
		return res;
	}

private:
	void start(const abstr_factory& factory) {
		//производство билетов
		Container<std::shared_ptr<v_ticket>> Tickets;
		for (size_t i = 0; i < size_of_circulation; i++)
		{
			Tickets.push_back(factory.maketicket());
		}
		//делание тиража
		Container<std::shared_ptr<v_ticket>> Tirag;
		for (auto& ticket : Tickets)
		{
			int randomfactor= 1 + rand() % 100;
			if (randomfactor < 70)
				Tirag.push_back(ticket);

		}
		// делание выигрышного билета
		std::shared_ptr<v_ticket> win_ticket = factory.maketicket();
		std::vector<int> win_digits = win_ticket->getdigits();
		std::cout << "win_ticket is:\t";
		for (auto& i : win_digits)
		{
			std::cout << i << "  ";
		}
		std::cout << std::endl;

		//поиск выигравших билетов и занесение их в список выигравших билетов

		for (auto& c : win_digits)
		{
			for (auto& ticket : Tirag)
			{
				std::vector<int> ticket_digits = ticket->getdigits();
				bool flag = false;
				for (auto& digit : ticket_digits)
				{
					if (digit == c) 
						flag = true;
				}
				if (flag) 
				{
					//ищем в списке выигравших билетов билет с таким же id
					bool find = false;
					//запоминаем найденный элемент
					win_ticket_t* find_ticket=nullptr;
					for (auto& prizeticket : m_result)
					{
						if (ticket->getid() == prizeticket.ticket->getid()) {
							find = true;
							find_ticket = &prizeticket;
							break;
						}
					}
					//если не нашли то добавляем в список выигравших
					if(find==false) 
						m_result.push_back(win_ticket_t{ 100,ticket });
					//иначе увеличиваем выигрыш на существующем билете
					else 
						find_ticket->win = find_ticket->win *10;
				}
			}
		}
		
	}
	Container<win_ticket_t> m_result;
};

