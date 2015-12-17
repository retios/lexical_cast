#include <iostream>
#include <functional>
#include "lexical_cast.hpp"

using namespace retio;
using namespace std;

void testLexical_cast() {
	cout << "lexical_cast<int,int>" << lexical_cast<int>(1234) << endl;
	cout << "lexical_cast<int,std::string>" << lexical_cast<int>("135") << endl;
	cout << "lexical_cast<long,std::string>" << lexical_cast<long>("16") << endl;
	cout << "lexical_cast<string,int>" << lexical_cast<string>(1236789) << endl;
	cout << "lexical_cast<bool,int>" << lexical_cast<bool>(12) << endl;
	cout << "lexical_cast<double,std::string>" << lexical_cast<double>("12.234322")
			<< endl;
	cout << "lexical_cast<float,std::string>" << lexical_cast<float>("32453.2")
			<< endl;
	string s = "true";
	cout << lexical_cast<bool>(s) << endl;
	char* p = "false";
	cout << lexical_cast<bool>(p) << endl;
	const char* q = "false";
	cout << lexical_cast<bool>(q) << endl;
	cout << lexical_cast<bool>("true") << endl;
	cout << lexical_cast<bool>("xxx") << endl;
}

int main(int argc, char** argv) {

	testLexical_cast();
	std::cout << "test.cpp" << std::endl;
}

