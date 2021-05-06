xml-parcer.exe:	xml-parcer.obj
	link xml-parcer.obj /OUT:xml-parcer.exe
 
xml-parcer.obj:	xml-parcer.cpp 
	cl -EHsc -c xml-parcer.cpp -I ../packages/boost.1.72.0.0/lib/native/include -DWIN32
	  