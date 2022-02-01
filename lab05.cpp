// lab05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
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




int main()
{
	cout << "hello world";
}
