// xml-parcer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include <fstream>

#ifdef WIN32
#include<windows.h>
#endif

int main(int argc,char* argv[])
{
#ifdef WIN32
	SetConsoleOutputCP(65001);
#endif
	
	try
	{
		if (argc != 2) { throw(std::logic_error("2 parametress requered")); }
		std::ifstream stream(argv[1]);
		if (!stream.is_open())
			throw(std::logic_error("can't open file"));

		boost::property_tree::ptree propertyTree;

		//Читаем XML
		boost::property_tree::read_xml(stream, propertyTree);

		//Читаем значения:
		for (const auto& v : propertyTree.get_child("store"))
		{
			bool flag = true;
			std::cout << v.second.get<std::string>("<xmlattr>.name") << "\n";

			for (const auto& l : v.second) {
				if (l.first != "<xmlattr>")
				{
					
					for (const auto& c : l.second) {
						if (flag) {
							std::cout << c.first << '\t';
						}
					}
					if(flag)
						std::cout<<std::endl;
					flag = false;
					for (const auto& c : l.second) {
						std::cout << c.second.get<std::string>("") << '\t';
					}
					std::cout << std::endl;
				}
			}
			std::cout << std::endl;
		}
	}
	catch (boost::property_tree::xml_parser_error)
	{

		std::cout << "XML parser error!" << std::endl;

	}

	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

}
