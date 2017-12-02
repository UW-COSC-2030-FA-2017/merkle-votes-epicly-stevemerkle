// Omar Sanchez and Maria Debroy
// COSC 2030 
// Edited 11/29/17

#include "pMT.h"
#include <iostream>

using namespace std;

int main() {
	pMT sam;
	sam.hashSelected = 1;
	sam.insert("forrest", 1);
	sam.insert("ham", 1);
	sam.insert("truck", 2);
	sam.insert("pam", 10);

	sam.locateData("ham");
	return 0;
}