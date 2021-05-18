#include <iostream>
#include "lottery.h"
#include "history.h"


using namespace std;



int main()
{

	History myhistory;
	
	shared_ptr< Lottery<Container>> newlottery= shared_ptr< Lottery<Container>>(new Lottery<Container>);
	newlottery->start_5_36();
	//newlottery.print_results(result);
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	newlottery->print_stat();
	cout << "-----------------------------------------------------------------------------------------------" << endl;

	
		int id;
		vector<win_ticket_t> resultwin;
		int win;
		while (true) {
		int flag;
		cout << "Enter:\n 1 to find by win, \n 2 to find by id,\n 3 to start new lottery, \n 0 to out" << endl;
		cin >> flag;
		switch (flag)
		{
		case 0:
			return 0;
			break;
		case 1:
			cout << "Enter win:" << endl;
			cin >> win;
			resultwin = newlottery->searchbywin(win);
			for (auto& i : resultwin)
			{
				cout << "n" << i.ticket->getid() << "\t" << "win:" << "\t" << i.win << endl;
			}
			break;
		case 2:
			cout << "Enter id:" << endl;
			cin >> id;
			newlottery->searchbyid(id);
			break;
		case 3:
			myhistory.add(newlottery);
			newlottery = shared_ptr< Lottery<Container>>(new Lottery<Container>);
			newlottery->start_5_36();
			//newlottery.print_results(result);
			cout << "-----------------------------------------------------------------------------------------------" << endl;
			newlottery->print_stat();
			cout << "-----------------------------------------------------------------------------------------------" << endl;
			break;
		default:
			break;
		}
	}

	

}
