#include <iostream>
#include "avl_tree.h"
#include "relation.h"
class Comparator_string {
public:
	bool operator()(const std::string& x, const std::string& y) { return x < y; }
};

class Comparator_int {
public:
	bool operator()(int x, int y) { return x < y; }
};

int main()
{
	avl_tree<int> x{ Comparator_int{} };

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


	relation<int> core;

	std::cout << "Hello World!\n";
}
