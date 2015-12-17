/*
 * TaskCpp.cpp
 *
 *  Created on: 2015��12��16��
 *      Author: wendyhu
 */

#include <iostream>
#include <functional>
#include "lexical_cast.hpp"

using namespace retio;
using namespace std;

void testLexical_cast() {
	cout << "lexical_cast<int,int>" << lexical_cast<int>(1) << endl;
	cout << "lexical_cast<int,std::string>" << lexical_cast<int>("1") << endl;
	cout << "lexical_cast<long,std::string>" << lexical_cast<long>("1") << endl;
	cout << "lexical_cast<string,int>" << lexical_cast<string>(1) << endl;
	cout << "lexical_cast<bool,int>" << lexical_cast<bool>(0) << endl;
	cout << "lexical_cast<double,std::string>" << lexical_cast<double>("1.2")
			<< endl;
	cout << "lexical_cast<float,std::string>" << lexical_cast<float>("1.2")
			<< endl;
	string s = "true";
	cout << lexical_cast<bool>(s) << endl;
	char* p = "false";
	cout << lexical_cast<bool>(p) << endl;
	const char* q = "false";
	cout << lexical_cast<bool>(q) << endl;
	cout << lexical_cast<bool>("true") << endl;
	cout << lexical_cast<bool>("test") << endl;
}

int main(int argc, char** argv) {

	testLexical_cast();
	std::cout << "test.cpp" << std::endl;
}

