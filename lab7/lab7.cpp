#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "avl_tree.h"
#include "relation.h"
#include <fstream>
#include<string>
using namespace std;
struct message_record {
	string datetime;
	string username;
	string message;

};
class Comparator_datetime {
public:
	bool operator()(const message_record*& x, const message_record*& y) { return x->datetime < y->datetime; }
};

class Comparator_usernamewith {
public:
	bool operator()(const message_record*& x, const message_record*& y) { return x->datetime < y->datetime; }
};



class Comparator_message {
public:
	bool operator()(const message_record*& x, const message_record*& y) { return _stricmp(x->message.c_str(), y->message.c_str())==-1 ; }
};

class Comparator_composite {
public:
	bool operator()(const message_record*& x, const message_record*& y) {
		if (Comparator_datetime{} (x, y)) {
			return true;
		}
		if (x->datetime != y->datetime)
			return false;
		return _stricmp(x->username.c_str(), y->username.c_str()) == -1;
	}
};



int main()
{
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
		rec.username = line.substr(endpos+1, endpos2);
		rec.message = line.substr(endpos2+1);
		core.Add(rec);
	}
	avl_tree<message_record*> indexuser{ Comparator_usernamewith {} };

	core.Addindex(&indexuser);

	avl_tree<message_record*> indexmessage{ Comparator_message{} };

	core.Addindex(&indexmessage);

	avl_tree<message_record*> indexcombined{ Comparator_composite {} };

	core.Addindex(&indexcombined);


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

	std::cout << "Hello World!\n";
}
