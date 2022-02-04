// lab05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

struct testCase
{
	testCase(string a, string b, string d)
	{
		this->a = a;
		this->b = b;
		this->d = d;
	}
	string a;
	string b;
	string d;
};

// PUT TEST CASES HERE
vector<testCase> testCases = {
	
	
//non homegraph
	testCase("c:\\?\secret\password.txt", "c:\secret\password.txt", "c:\users\public"),
	testCase("c:\secret\password.txt", "d:\secret\password.txt", "c:\users\public"),
	testCase("12395940", "c:\secret\password.txt", "c:\users\public"),
	testCase("C:\\doccuments\\bank_info\\bank_number.txt", ".\\bank_info\\banknumber.txt", "D:\\other\\trip"),

// homograph
	testCase("c:secret\password.txt" , "c:users\public\secret\password.txt", "c:\users\public" ),
	testCase("\\.\C:\Test\Foo.txt", "\\?\C:\Test\Foo.txt", "C:\users"),
	testCase("C:\\secret\\password.txt", ".\\..\\..\\secret\\password.txt", "C:\\users\\public")
};

// { {"C:\\secret\\password.txt", ".\\..\\..\\secret\\password.txt", "C:\\users\\public"} };

void rendering(string e) { cout << e; }
list<string> canonicalization(string e, string d);
bool homograph(string a, string b, string d);
list<string> stringListConversion(string s);

bool homograph(string a, string b, string d)
{
	// string a is the first filepath, b is the seccond, and d is the current directory
	if (canonicalization(a, d) == canonicalization(b, d))
	{
		return true;
	}
	
	return false;
}

string get(list<string> l, int index)
{
	auto it = l.begin();
	for (int i = 0; i < index; i++)
		it++;
	return *it;
}

list<string> canonicalization(string e, string d)
{
	// Unique Cannonisation Rule
	// ∀ e1, e2 C(e1) ≠ C(e2) ↔ H(e1, e2) < p
	// For all pairs of encodings, if they are not homographs, they must have different cannonisation

	// Reliable Cannonisation Rule
	// ∀ e1, e2 C(e1) = C(e2) ↔ H(e1, e2) ≥ p
	// For all pairs of encodings, if they are homographs, the cannonisation must be the same
	list<string> listE = stringListConversion(e);
	list<string> listD = stringListConversion(d);
	list<string> listC = {};
	string c = "";
	for (int i = 0; i < listE.size(); i++)
	{
		string x = get(listE, i);
		if (x == ".")
			listC = listD;
		else if (x == "..")
			listC.pop_back();
		else
			listC.push_back(x);
			
	}
	
	/*cout << listC.size();
	for (int i = 0; i <= listC.size(); i++)
	{
		cout << "step";
		//cout << listC.front() << endl;
		string x = listC.front();
		c += x;
		listC.pop_front();
	}
	*/
	return listC;
}

list<string> stringListConversion(string s)
{
	list<string> filePathList;
	istringstream iss(s);

	size_t position = 0, currentPosition = 0;

	while(currentPosition != -1)
	{
		currentPosition = s.find_first_of('\\', position);
		filePathList.push_back(s.substr(position, currentPosition-position));
		position = currentPosition + 1;
	}


	return filePathList;
}


int main()
{
	/* CAN BE REMOVED (Test of breaking apart the file path)
	string filePath = "C:\\secret\\password.txt";
	list<string> filePathList;

	filePathList = stringListConversion(filePath);

	for(list<string>::iterator it = filePathList.begin(); it != filePathList.end(); it++)
	{
		cout << *it << endl;
	}

	cout << "size is" << filePathList.size() << endl;
	 CAN BE REMOVED end OF file path test */


	for (int i = 0; i < testCases.size(); i++)
	{
		cout << "TEST " << i << "\n\n";
		testCase test = testCases[i];

		bool isHomograph = homograph(test.a, test.b, test.d);
		cout << isHomograph << endl;
		if (isHomograph)
			cout << "\"" << test.a << "\"" << " and " << "\"" << test.b << "\"" << " are homographs when in the directory, \"" << test.d << "\"\n\n";
		else
			cout << "\"" << test.a << "\"" << " and " << "\"" << test.b << "\"" << " are not homographs when in the directory, \"" << test.d << "\"\n\n";
	}
	

	return 0;
} // end of main
