/***********************************************************************
 * Program: W05 LAB HOMOGRAPHS
 *    Week 05, HOMOGRAPHS
 *    Brother Wilson, CSE 453
 * Author:
 *    Ethan Nelson, Josh Donaldson, Benjamin Dyas, Erik Machuca Saez 
 * Summary:
 *    Compare two strings of file paths to determine if they are
 * 	homographs or not.
 *    Estimated: 6 hrs each
 *    Actual: 7 hrs each
 * The difficulty was was with using c++. We were a little rusty with this
 * language. Implementing the functions to determine the homographs was
 * straightforward.
 ************************************************************************/

#include <iostream>
#include <list>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

/***********************************************************************
 * testCase class to hold the strings of the different test cases.
 ***********************************************************************/
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

// variables
vector<testCase> testCases = {
	testCase("C:\\secret\\password.txt", ".\\..\\..\\secret\\password.txt", "C:\\users\\public"),
	testCase("C:\\doccuments\\bank_info\\bank_number.txt", ".\\bank_info\\banknumber.txt", "D:\\other\\trip")
};

// { {"C:\\secret\\password.txt", ".\\..\\..\\secret\\password.txt", "C:\\users\\public"} };

// methods
void rendering(string e) { cout << e; }
list<string> canonicalization(string e, string d);
bool homograph(string a, string b, string d);
list<string> stringListConversion(string s);


/******************************************************
 * METHOD: homograph
 * receives three strings to compare and determine if
 * they are homographs
 *   INPUT:  (3) strings
 *   OUTPUT: boolean
 ******************************************************/
bool homograph(string a, string b, string d)
{
	// string a is the first filepath, b is the seccond, and d is the current directory
	if (canonicalization(a, d) == canonicalization(b, d))
	{
		return true;
	}
	
	return false;
}

/******************************************************
 * METHOD: getString
 * receives a list of strings and index to
 * return a string.
 *   INPUT:  list of strings, int
 *   OUTPUT: boolean
 ******************************************************/
string getString(list<string> l, int index)
{
	auto it = l.begin();
	for (int i = 0; i < index; i++)
		it++;
	return *it;
}

/******************************************************
 * METHOD: canonicalization
 * Uses the following two cannonisation rules to
 * cannonize the strings into a list of of strings:
 * 
 * Unique Cannonisation Rule
 * ∀ e1, e2 C(e1) ≠ C(e2) ↔ H(e1, e2) < p
 * For all pairs of encodings, if they are not homographs,
 * they must have different cannonisation
 * 
 * Reliable Cannonisation Rule
 * ∀ e1, e2 C(e1) = C(e2) ↔ H(e1, e2) ≥ p
 * For all pairs of encodings, if they are homographs,
 * the cannonisation must be the same
 * 
 *   INPUT:  (2) strings
 *   OUTPUT: list<string>
 ******************************************************/
list<string> canonicalization(string e, string d)
{
	list<string> listE = stringListConversion(e);
	list<string> listD = stringListConversion(d);
	list<string> listC = {};
	string c = "";
	for (int i = 0; i < listE.size(); i++)
	{
		string x = getString(listE, i);
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

/******************************************************
 * METHOD: stringListConversion
 * receives a file path string and breaks the string
 * apart from the "\" operator and creates a list of
 * strings.
 *   INPUT:  string
 *   OUTPUT: list<string>
 ******************************************************/
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

/***********************************************************************
 * Prompts the user for a positive and a negative integer.
 * If required input is supplied, the two integers are added and the
 * sum is displayed.
 ***********************************************************************/
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
