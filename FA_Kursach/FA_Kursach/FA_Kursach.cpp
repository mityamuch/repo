#include <iostream>
#include "list.h"
#include "lottery.h"

int main()
{
	Lottery newlottery;
	deque<win_ticket_t> result = newlottery.start_6_49();
	//newlottery.print_results(result);
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	newlottery.print_stat(result);
	cout << "-----------------------------------------------------------------------------------------------" << endl;

	int id;
	vector<win_ticket_t> resultwin;
	int win;

	while (true) {
		int flag;
		cout << "Enter 1 to find by win , 2 to find by id or 0 to out" << endl;
		cin >> flag;
		switch (flag)
		{
		case 0:
			return 0;
			break;
		case 1:
			cout << "Enter win:" << endl;
			cin >> win;
			resultwin = newlottery.searchbywin(win,result);
			for (auto& i : resultwin)
			{
				cout << "n";
				cout << i.ticket->getid() << "\t";
				cout << "win" << "\t";
				cout << i.win << endl;
			}
			break;
		case 2:
			cout << "Enter id:" << endl;
			cin >> id;
			newlottery.searchbyid(id,result);



			break;
		default:
			break;
		}
	}



}
