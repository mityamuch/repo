#include <iostream>
#include <regex>
#include "memory.h"
#include <fstream>
#include <map>
#include <vector>

using namespace std;
struct Var {
	int size;
	char* pointer;
};

void TrashCollect(vector<map<string, Var>>& trashcan,Memory& mem) {
	for (auto& i : trashcan)
	{
		for (auto& c : i)
		{
			mem.Free(c.second.pointer);
		}

	}
	trashcan.clear();
}

void PrintVars(const vector<map<string, Var>>& vars)
{
	cout << "Print vars:" << endl;
	for (auto& i : vars)
	{
		for (auto& c : i)
		{
			cout << c.first << "\t" << c.second.size << endl;
		}
	}
}


int main()
{
	ifstream input("input.txt");
	regex al("\\s*(.+)\\s*=\\s*new\\s*\\(\\s*(\\d+)\\s*\\)\\s*;\\s*");
	regex print("\\s*PrintVars.*");
	regex open("\\s*\\{.*");
	regex close("\\s*\\}.*");

	string size;
	getline(input, size);
	Memory a(stoi(size));

	vector<map<string,Var>> vars;
	vector<map<string, Var>> trashcan;
	int currentLevel=-1;

	try {
		while (!input.eof()) {
			string line;
			getline(input, line);
			smatch match;
			if (regex_match(line, match, al)) {

				Var newVar{ stoi(match[2].str()),a.Alloc(stoi(match[2].str()))};
				if (newVar.pointer == nullptr) {
					TrashCollect(trashcan, a);
					newVar.pointer=a.Alloc(stoi(match[2].str()));
				}

				if (newVar.pointer != nullptr)
					vars[currentLevel][match[1].str()] = newVar;
				else
				{
					cout << "Can't allocate " << match[1].str() << endl;
				}
			}
			else if(regex_match(line, match, print)){
				PrintVars(vars);
			}
			else if(regex_match(line, match, open)){
				
				vars.push_back(map<string, Var>());
				currentLevel++;
			}
			else if(regex_match(line, match, close)){
				
				trashcan.push_back(move(vars[currentLevel]));
				vars.erase(vars.begin()+currentLevel);
				currentLevel--;
			}

		}
	}
	catch(std::exception err){ cout << err.what() << endl; }

}
