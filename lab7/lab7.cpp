#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "avl_tree.h"
#include "relation.h"
#include <fstream>
#include<string>
#include <assert.h>
#include <regex>
#include <time.h>
using namespace std;



struct Contract {
	string name;
	int id;
	int cost;
	tm starttime;
	tm endtime;
	
	void print() {
		cout << name << '\t' <<"dogovor#" <<id<< '\t' << cost << endl;
	}
};


struct message_record {
	string datetime;
	string username;
	string message;
	void print() {
		cout << datetime<<'\t' << username << '\t' << message << endl;
	}
};

class Comparator_datetime {
public:
	bool operator()(message_record* const& x, message_record* const& y) { return x->datetime < y->datetime; }
};

class Comparator_usernamewith {
public:
	bool operator()(message_record* const& x, message_record* const& y) { return x->username < y->username; }
};

class Comparator_message {
public:
	bool operator()(message_record* const& x, message_record* const& y) { return _stricmp(x->message.c_str(), y->message.c_str()) < 0; }
};

class Comparator_composite {
public:
	bool operator()(message_record* const& x,  message_record* const& y) {
		if (Comparator_datetime{} (x, y)) {
			return true;
		}
		if (x->datetime != y->datetime)
			return false;
		return _stricmp(x->username.c_str(), y->username.c_str()) < 0;
	}
};

class Comparator_fio_id {
public:
	bool operator()(Contract* const& x, Contract* const& y) {
		if (x->name < y->name) {
			return true;
		}
		if (x->name != y->name)
			return false;
		return x->id < y->id;
	}
};

class Comparator_duration {
public:
	bool operator()(Contract* const& x, Contract* const& y) {
		double x_dur = difftime(mktime(&x->starttime),mktime(&x->endtime));
		double y_dur = difftime(mktime(&y->starttime), mktime(&y->endtime));
		return x < y;
	}
};


class Comparator_cost {
public:
	bool operator()(Contract* const& x, Contract* const& y) { return x->cost < y->cost; }
};


int main()
{
	//lvl4
	relation<message_record> core;
	avl_tree<message_record*> index1{ Comparator_datetime{} };
	
	core.Addindex(&index1);
	ifstream input("messages.txt");
	//parse
	while (!input.eof()) {
		string line;
		getline(input,line);
		auto endpos=line.find(' ');
		message_record rec;
		rec.datetime = line.substr(0, endpos);
		auto endpos2 = line.find(':',endpos);
		rec.username = line.substr(endpos+1, endpos2 - endpos-1);
		rec.message = line.substr(endpos2+1);
		core.Add(rec);
	}
	avl_tree<message_record*> indexuser{ Comparator_usernamewith {} };

	core.Addindex(&indexuser);

	avl_tree<message_record*> indexmessage{ Comparator_message{} };

	core.Addindex(&indexmessage);

	avl_tree<message_record*> indexcombined{ Comparator_composite {} };

	core.Addindex(&indexcombined);

	core.Find(message_record{ "","mityamuch" }, 1)->print();
	core.Find(message_record{ "2001.12.17"}, 0)->print();
	auto ilya = core.Find(message_record{ "","", "privet ILYA" }, 2);
	ilya->print();
	core.Find(message_record{ "2021.04.16","MASHA" }, 3)->print();

	assert(core.Find(message_record{ "","sfdgdsag" }, 1) == nullptr);

	core.Remove(ilya);

	core.Find(message_record{ "","mityamuch" }, 1)->print();
	core.Find(message_record{ "2001.12.17" }, 0)->print();
	assert(core.Find(message_record{ "","petya" }, 1) == nullptr);
	assert(core.Find(message_record{ "","", "privet ILYA" }, 2) == nullptr);
	assert(core.Find(message_record{ "2001.12.18"}, 0) == nullptr);
	core.Find(message_record{ "2021.04.16","MASHA" }, 3)->print();


	cout << "------------------------------------------------------------------------------------------------------" << endl;

	enum ParserState
	{
		WaitFio,
		WaitOpenBrace,
		WaitContractOrCloseBrace
	};

	//lvl 5
	ifstream input2("contracts.txt");

	ParserState state = WaitFio;
	string fio;
	regex re(".*dogovor#(\\d+)\\snach\\s(\\d+)\\.(\\d+)\\.(\\d+)\\skon\\s(\\d+)\\.(\\d+)\\.(\\d+)\\s(\\d+)");
	relation<Contract> contracts;

	while (!input2.eof()) {
		string line;
		getline(input2, line);

		switch (state)
		{
		case WaitFio:
			fio = line;
			state = WaitOpenBrace;
			break;
		case WaitOpenBrace:
			if (line != "{")
				throw (logic_error("parse error"));
			state = WaitContractOrCloseBrace;
			break;
		case WaitContractOrCloseBrace:
			if (line == "}") {
				state = WaitFio;
			}
			else {
				std::smatch match;
				std::regex_match(line, match, re);
				if (match.size() != 9)
					throw (logic_error("contract parse error"));
				Contract contract;
				contract.name = fio;
				contract.cost = stoi(match[8].str());
				contract.starttime = std::tm{ 0,0,0,stoi(match[4].str()), stoi(match[3].str()), stoi(match[2].str()) };
				contract.endtime = std::tm{ 0,0,0,stoi(match[7].str()), stoi(match[6].str()), stoi(match[5].str()) };
				contract.id = stoi(match[1].str());
				contracts.Add(contract);
			}
			break;
		default:
			break;
		}
	}

	avl_tree<Contract*> indexcost{ Comparator_cost {} };

	 contracts.Addindex(&indexcost);

	 avl_tree<Contract*> indexduration{ Comparator_duration {} };

	 contracts.Addindex(&indexduration);

	 avl_tree<Contract*> indexfioid{ Comparator_fio_id {} };

	 contracts.Addindex(&indexfioid);


	 contracts.Find(Contract{"",0,300},0)->print();
	 contracts.Find(Contract{ "Muhanov dmitriy ilyich",1 }, 2)->print();
	 contracts.Find(Contract{ "Muhanov dmitriy ilyich",4 }, 2)->print();
	 contracts.Find(Contract{ "",0,40000 }, 0)->print();
	 contracts.Find(Contract{ "kalabuhin anton olegovich",1 },2)->print();

	/*
	x.Add(1);
	x.Add(3);
	x.Add(45);
	x.Add(5);
	x.Add(15);
	x.Add(25);
	x.Add(15);
	x.Add(10);
	x.Remove(47);
	x.print();
	*/
}
