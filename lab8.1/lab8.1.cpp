#include "memory.h"
#include"first_suitable.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <map>

using namespace std;
int main()
{
    ifstream input("in.txt");

	regex al("(.+)=allocate\\((\\d+)\\)");
	regex deal("dealloc\\((.+)\\)");
	regex ravno("(.+)=(.+)");

	string size;
	getline(input, size);
	first_suitable a(stoi(size));

	map<string,kusokpam*> vars;

	try {
		while (!input.eof()) {
			string line;
			getline(input, line);
			smatch match;
			if (regex_match(line, match, al)) {
				vars[match[1].str()] = a.allocate(stoi(match[2].str()));

			}
			else if (regex_match(line, match, deal))
			{
				auto result = vars.find(match[1].str());
				if (result == vars.end())
					throw(logic_error("deallocate error"));

				a.deallocate(result->second);
			}
			else if (regex_match(line, match, ravno))
			{
				auto result = vars.find(match[2].str());
				if (result == vars.end())
					throw(logic_error("opa ne nashel"));
				vars[match[1].str()] = result->second;
			}


		}
		a.print_leaked_blocks();
	}
	catch (exception error) { cout << error.what() << endl; }


}

