// lab05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <sstream>
#include <iterator>
#include <vector>
using namespace std;

void rendering(string e) { cout << e; }
string canonicalization(string e, string d);
bool homograph(string a, string b, string d);
list<string> stringListConversion(string s);


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

vector<testCase> testCases = {
	testCase("C:\\secret\\password.txt", ".\\..\\..\\secret\\password.txt", "C:\\users\\public"),
	testCase("C:\\doccuments\\bank_info\\bank_number.txt", ".\\bank_info\\banknumber.txt", "D:\\other\\trip")
};

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

string canonicalization(string e, string d)
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
		
		if (x == "\\\\?")
			return e;
		if (i == 0)
			listC = listD;
		if (x == "." || x == "?")
		{
			listC = listD;
		}
		else if (x.find(":") != -1)
		{
			listC = { x };
		}

		else if (x == "..")
		{
			listC.pop_back();
		}
			
		else
		{
			listC.push_back(x);
		}
			
	}
	int size = listC.size();
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
			c += "\\";
		string x = listC.front();
		c += x;
		listC.pop_front();
	}
	cout << c << endl;
	return c;
}

list<string> stringListConversion(string s)
{
	list<string> filePathList;
	istringstream iss(s);

	size_t position = 0, currentPosition = 0;

	while (currentPosition != -1)
	{
		currentPosition = s.find_first_of('\\', position);
		filePathList.push_back(s.substr(position, currentPosition - position));
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

	string testCase1A = "C:\\secret\\password.txt";
	string testCase1B = ".\\..\\..\\secret\\password.txt";
	string testCase1D = "C:\\users\\public";

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

	string path1;
	string path2;
	string directory;
	cout << "enter first file path: ";
	cin >> path1;
	cout << "enter seccond file path: ";
	cin >> path2;
	cout << "enter name of current directory: ";
	cin >> directory;

	bool isHomograph = homograph(path1, path2, directory);
	cout << isHomograph << endl;
	if (isHomograph)
		cout << "\"" << path1 << "\"" << " and " << "\"" << path2 << "\"" << " are homographs when in the directory, \"" << directory << "\"\n\n";
	else
		cout << "\"" << path1 << "\"" << " and " << "\"" << path2 << "\"" << " are not homographs when in the directory, \"" << directory << "\"\n\n";

	return 0;
} // end of main