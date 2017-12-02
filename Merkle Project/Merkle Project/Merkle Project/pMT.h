#pragma once

#include "bTREE.h"
#include <string>
using namespace std;
class pMT
{
private:
    int selectedHash;
   
    string hash_1(string);
    string hash_2(string);
    string hash_3(string);
	void printPrivate(treeNode* Pouder);
public:
	bTREE myMerkle;
	pMT();
	//pMT(int slectedHash, string word);
    ~pMT();
	int hashSelection(int hashSelect, string word);
	void pMT::postOrder(treeNode* temp);
	//void Print();
    int insert(string data, int number);
    
    int find(string vote, int time, int hashSelect);
    int findHash(string);
	int findHelper(string vote, int time, int hashSelect, treeNode* node);
	int findHashHelper(string mhash, treeNode* node);
    string locateHash(string vote);
	string locateData(string data);
	void locateH(treeNode* subtree, string data, string  pathway);
	int hashSelected;
	bool found;
	int count = 0;
    
    friend bool operator==(const pMT& lhs, const pMT& rhs);
    
    friend bool operator!=(const pMT& lhs, const pMT& rhs);
    
    friend pMT operator^(const pMT& lhs, const pMT& rhs);
    friend std::ostream& operator<<(std::ostream& out, pMT& p);
    
};

