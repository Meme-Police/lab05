// lab05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <sstream>
using namespace std;

void rendering(string e) { cout << e; }
string canonicalization(string e);
bool homograph(string a, string b);

bool homograph(string a, string b)
{
	if (canonicalization(a) == canonicalization(b))
	{
		return true;
	}
	
	return false;
}

string canonicalization(string e)
{
	// Unique Cannonisation Rule
	// ∀ e1, e2 C(e1) ≠ C(e2) ↔ H(e1, e2) < p
	// For all pairs of encodings, if they are not homographs, they must have different cannonisation

	// Reliable Cannonisation Rule
	// ∀ e1, e2 C(e1) = C(e2) ↔ H(e1, e2) ≥ p
	// For all pairs of encodings, if they are homographs, the cannonisation must be the same

	// TODO: Implement the cannonisation function

	// placeholder
	return "none";
}

list<string> stringListConversion (string s)
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
	// CAN BE REMOVED (Test of breaking apart the file path)
	string filePath = "C:\\secret\\password.txt";
	list<string> filePathList;

	filePathList = stringListConversion(filePath);

	for(list<string>::iterator it = filePathList.begin(); it != filePathList.end(); it++)
	{
		cout << *it << endl;
	}
	// CAN BE REMOVED end OF file path test

	return 0;
} // end of main
