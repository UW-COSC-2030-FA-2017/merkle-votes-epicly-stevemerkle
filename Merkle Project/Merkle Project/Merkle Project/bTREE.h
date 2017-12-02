#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
#ifndef BTREE_H_
#define BTREE_H_

struct treeNode {
	string data;
	int time;
	treeNode* right_;
	treeNode* left_;
};

class bTREE{

	//some data structure to hold your treeNodes together ...
    //DATASTUCTURE treeNodes tree;
    //any helper private variables you need
	void printPrivate(treeNode* Felp);
	
public:
    bTREE();
    ~bTREE();
	void Print();
	int inorderTraversal(string treasure, treeNode* node);
    int insert(string name, int time);
	void printPostOrder();
	void postOrder(treeNode* temp);
    int find(string treasure); 
    string locate(string input);
	void locateH(treeNode* subtree, string data, string  pathway);
    friend bool operator==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);
    friend std::ostream& operator<<(std::ostream& out, bTREE& p);
	treeNode* root;
	vector<string> traversal;
	queue<treeNode*> *q;
	int counter = 0;
	bool found;
	string path;
};
#endif