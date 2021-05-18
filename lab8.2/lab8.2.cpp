#include <iostream>
#include <regex>
#include "memory.h"
#include <fstream>
#include <map>

using namespace std;
int main()
{
	ifstream input("input.txt");
	regex al("^(.+)=new\\((\\d+)\\)");
	regex print("PrintVars");
	regex open("{");
	regex close("}");

	string size;
	getline(input, size);
	Memory a(stoi(size));

	map<string,int> vars;

	try {
		while (!input.eof()) {
			string line;
			getline(input, line);
			smatch match;
			if (regex_match(line, match, al)) {
				
			}
			else if(regex_match(line, match, print)){
			
			}
			else if(regex_match(line, match, open)){
			
			}
			else if(regex_match(line, match, close)){
			
			}


		}
	}
	catch(std::exception err){ cout << err.what() << endl; }

}
