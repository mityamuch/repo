#include "memory.h"
#include "first_suitable.h"
#include "border_descriptors.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include "assert.h"

using namespace std;

void test_first_suitable()
{
	first_suitable a(11);

	auto v1 = a.allocate(3);
	auto v2 = a.allocate(3);
	auto v3 = a.allocate(3);
	
	try {
		auto v4 = a.allocate(3);
		assert(false);
	}
	catch (...) {}

	v1->write("a1");
	v2->write("b2");

	try {
		v3->write("c34");
		assert(false);
	}
	catch (...) {}
	
	v3->write("c3");

	assert(v1->read() == "a1");
	assert(v2->read() == "b2");
	assert(v3->read() == "c3");

	a.deallocate(v2);
	v2 = a.allocate(2);
	v2->write("q");
	auto v4 = a.allocate(2);

	a.deallocate(v1);
	try {
		a.deallocate(v1);
		assert(false);
	}
	catch (...) {}

	try {
		a.allocate(5);
		assert(false);
	}
	catch (...) {}

	a.deallocate(v4);
	v4 = a.allocate(5);
	v4->write("Hell");

	assert(v2->read() == "q");
	assert(v3->read() == "c3");
	assert(v4->read() == "Hell");
}

void test_border_descriptors()
{
	border_descriptors a(400 + 4 * extra_used_block_size + 2 * sizeof(bool));

	auto v1 = a.allocate(100);
	auto v2 = a.allocate(100);
	auto v3 = a.allocate(100);
	auto v4 = a.allocate(100);

	try {
		a.allocate(60);
		assert(false);
	}
	catch (...) {}

	v1->write("Variable v1");
	v2->write("Variable v2");
	v3->write("Variable v3");
	v4->write("Variable v4");

	assert(v1->read() == "Variable v1");
	assert(v2->read() == "Variable v2");
	assert(v3->read() == "Variable v3");
	assert(v4->read() == "Variable v4");

	a.deallocate(v2);
	v2 = a.allocate(extra_free_block_size);
	v2->write("New variable v2");

	a.deallocate(v3);
	v3 = a.allocate(200 - extra_free_block_size);
	v3->write("New variable v3");

	a.deallocate(v4);
	try {
		a.allocate(101);
		assert(false);
	}
	catch (...) {}

	auto v5 = a.allocate(100);
	a.deallocate(v5);
	a.deallocate(v3);
	v3 = a.allocate(200 - 2 * extra_free_block_size);
	v3->write("Even new variable v3");
	try {
		a.allocate(101 + extra_free_block_size);
		assert(false);
	}
	catch (...) {}
	v5 = a.allocate(100 + extra_free_block_size);
	v5->write("New variable v5");

	a.deallocate(v1);
	try {
		a.deallocate(v1);
		assert(false);
	}
	catch (...) {}
	a.deallocate(v3);

	auto v6 = a.allocate(200);
	v6->write("Variable v6");

	assert(v2->read() == "New variable v2");
	assert(v5->read() == "New variable v5");
	assert(v6->read() == "Variable v6");

	a.deallocate(v5);
	a.deallocate(v2);
	a.deallocate(v6);
}

int main()
{
	test_first_suitable();
	test_border_descriptors();

	regex al("(.+)=allocate\\((\\d+)\\)");
	regex deal("dealloc\\((.+)\\)");
	regex ravnostr("(.+)=\"(.+)\"");
	regex printvar("print (.+)");
	regex ravnovar("(.+)=(.+)");

	string size;
	{
		ifstream input("in.txt");
		getline(input, size);
	}

	first_suitable a(stoi(size));
	border_descriptors b(stoi(size));

	memory* memories[2] = { &a, &b };

	for (auto& mem : memories)
	{
		cout << "------------------------------------------------------------" << endl;
		map<string, kusokpam*> vars;
		ifstream input("in.txt");
		string temp;
		getline(input, temp);

		try {
			while (!input.eof()) {
				string line;
				getline(input, line);
				smatch match;
				if (regex_match(line, match, al)) {
					vars[match[1].str()] = mem->allocate(stoi(match[2].str()));
				}
				else if (regex_match(line, match, deal))
				{
					auto result = vars.find(match[1].str());
					if (result == vars.end())
						throw(logic_error("deallocate error: " + match[1].str()));

					mem->deallocate(result->second);
				}
				else if (regex_match(line, match, ravnostr))
				{
					auto result = vars.find(match[1].str());
					if (result == vars.end())
						throw(logic_error("opa ne nashel " + match[1].str()));
					vars[match[1].str()]->write(match[2].str());
				}
				else if (regex_match(line, match, printvar))
				{
					auto result = vars.find(match[1].str());
					if (result == vars.end())
						throw(logic_error("opa ne nashel " + match[1].str()));
					cout << vars[match[1].str()]->read() << endl;
				}
				else if (regex_match(line, match, ravnovar))
				{
					auto result = vars.find(match[2].str());
					if (result == vars.end())
						throw(logic_error("opa ne nashel " + match[2].str()));
					vars[match[1].str()] = result->second;
				}
			}
			mem->print_leaked_blocks();
		}
		catch (exception error) { cout << error.what() << endl; }
	}


	return 0;
}

