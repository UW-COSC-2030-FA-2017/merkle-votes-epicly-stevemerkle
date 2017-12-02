// Omar Sanchez and Maria Debroy
// COSC 2030 
// Edited 11/29/17

#include "bTREE.h"
#include <iostream>

using namespace std;


int main_()
	{
	cout << "hello world" << endl;
		bTREE sam;
		sam.insert("fun",2);
		sam.insert("morefun", 25);
		sam.insert("tater", 26);
		sam.insert("mashed", 14);
		sam.insert("lake", 12);
		cout << sam;

		cout << sam.locate("tater") << endl;







		return 0;
	}
