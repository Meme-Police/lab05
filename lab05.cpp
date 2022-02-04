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
#include <string.h>
using namespace std;
// prototypes
string canonicalization(string e, string d);
bool homograph(string a, string b, string d);
list<string> stringListConversion(string s);


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

// test cases
vector<testCase> testCases = {
	
	
//non homegraph
	testCase("c:\\\\?\\..\\..\\secret\\password.txt", "c:\\secret\\password.txt", "c:\\users\\public"),
	testCase("c:\\secret\\password.txt", "d:\\secret\\password.txt", "c:\\users\\public"),
	testCase("12395940", "c:\\secret\\password.txt", "c:\\users\\public"),
	testCase("C:\\doccuments\\bank_info\\bank_number.txt", ".\\bank_info\\banknumber.txt", "D:\\other\\trip"),

// homograph
	testCase("c:secret\\password.txt" , "c:\\users\\public\\secret\\password.txt", "c:\\users\\public" ),
	testCase(".\\C:\Test\\Foo.txt", "C:\Test\\Foo.txt", "C:\\users"),
	testCase("C:\\secret\\password.txt", ".\\..\\..\\secret\\password.txt", "C:\\users\\public")
};

/******************************************************
 * METHOD: homograph
 * receives three strings to compare and determine if
 * the first two are file path homographs
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
 *   OUTPUT: string
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
 *   OUTPUT: string
 ******************************************************/
string canonicalization(string e, string d)
{

	list<string> listE = stringListConversion(e);
	list<string> listD = stringListConversion(d);
	list<string> listC = {};
	string c = "";

	//this for loop constructs the canonicalized string
	for (int i = 0; i < listE.size(); i++)
	{
		
		string x = getString(listE, i);
		if (x == "?")
		{
			cout << e.substr(e.find("?") + 1) << endl;
			return e.substr(e.find("?") + 1);
		}
		if (i == 0)
			listC = listD;
		if (x == ".")
		{
			listC = listD;
		}
		else if (x.find(":") != -1)
		{
			if (x.size() > 2)
			{
				listC = listD;
				listC.push_back(x.substr(2));
			}

			else
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

	while (currentPosition != -1)
	{
		currentPosition = s.find_first_of('\\', position);
		filePathList.push_back(s.substr(position, currentPosition - position));
		position = currentPosition + 1;
	}


	return filePathList;
}

/***********************************************************************
 * Main runs through all of the test cases, then accepts three strings 
 * from a user and determins if the first two are homographs bassed
 * on the third.
 ***********************************************************************/
int main()
{

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