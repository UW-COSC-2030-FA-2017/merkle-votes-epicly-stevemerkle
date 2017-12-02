#include "pMT.h"
#include <vector>
#include <sstream>
#include<string>
#include<iterator>
#include<queue>
using namespace std;

pMT::pMT()

 //* @brief 
 //* @param hashSelect a number corresponding to the hashfunction to use for this pMT
 //* @return 
 
{
	myMerkle.root = new treeNode();
	myMerkle.root->data = "";
	myMerkle.q = new queue<treeNode*>();
	
	
}


int pMT::hashSelection(int hashSelect, string word)
{
	myMerkle.root = new treeNode();


	if (hashSelect == 1) {
		myMerkle.root = new treeNode;
		myMerkle.root->data = hash_1(word);
		hashSelected = 1;
	}
	else if (hashSelect == 2) {
		myMerkle.root = new treeNode;
		myMerkle.root->data = hash_2(word);
		hashSelected = 2;
	}
	else if (hashSelect == 3) {
		myMerkle.root = new treeNode;
		myMerkle.root->data = hash_3(word);
		hashSelected = 3;
	}
	else {
		myMerkle.root = new treeNode;
		myMerkle.root->data = hash_2(word);
		hashSelected = 2;
	}
	myMerkle.q = new queue<treeNode*>();

	return hashSelected;
}
pMT::~pMT()
/**
 * @brief destructor
 * @return nada
 */
{
}

int pMT::insert(string vote, int time)
/**
 * @brief insert a vote and time into a leaf node of tree
 * @param vote - a string
 * @param time - an int representing the time 
 * @return the number of operations needed to do the insert, -1 if out of memory
 */

{
	string hash;
	if (hashSelected == 1) {
		hash = hash_1(vote);
	}
	else if (hashSelected == 2) {
		hash = hash_2(vote);
	}
	else if (hashSelected == 3) {
		hash = hash_3(vote);
	}
	else {
		hash = hash_2(vote);
	}
	
	treeNode* temp2 = new treeNode();
	temp2->time = time;
	temp2->data = hash;
	temp2->left_ = NULL;
	temp2->right_ = NULL;
	int counter = 0;

	if (myMerkle.root->data == "") {
		myMerkle.root = temp2;
		myMerkle.q->push(myMerkle.root);
	}
	else {
		// Do level order traversal until we find
		// an empty place. 
		treeNode* tmp = myMerkle.q->front();
		if (tmp->left_ == NULL) {
			counter++;
			tmp->data = hash;
			tmp->left_ = temp2;
			myMerkle.q->push(temp2);
		}
		else if (tmp->right_ == NULL) {
			string ashy = tmp->left_->data + tmp->right_->data;
			if (hashSelected == 1) {
				tmp->data = hash_1(ashy);
			}
			else if (hashSelected == 2) {
				tmp->data = hash_2(ashy);
			}
			else if (hashSelected == 3) {
				tmp->data = hash_3(ashy);
			}
			else {
				tmp->data = hash_2(ashy);
			}
			counter++;
			tmp->right_ = temp2;
			myMerkle.q->push(temp2);
			myMerkle.q->pop();
		}
	}
	return counter;
}
int pMT::findHelper(string vote, int time, int hashSelect, treeNode* node) //Inorder traversal method 
{
	count++; //increase the count for the number of operations 

	if (node->left_ != NULL) //keeps recursing through the function until it finds a left most node that is pointing to Null. 
	{
		findHelper(vote, time, hashSelect, node->left_);
	}
	if (node->data == vote && node->time && hashSelect) //If the contents of the node 
	{
		cout << "\nString '" << vote << "' found." << endl;
		found = true;

	}
	if (node->right_ != NULL)
	{
		findHelper(vote, time, hashSelect, node->right_);
	}


	return count;

}

int pMT::find(string vote, int time, int hashSelect)

/** @brief given a vote, timestamp, and hash function, does this vote exist in the tree?
* @param vote, a string
* @param time, an int
* @param hashSelect, an int corresponding to the hash functions _1, _2, and _3
* @return 0 if not found, else number of opperations required to find the matching vote*/

{
	hashSelect = 1; 
	found = false;
	count++;
	treeNode* node = myMerkle.root;
	findHelper(vote, time, hashSelect, node);
	if (found == false)
	{
		cout << "\nNot Found" << endl;
	}
	return count;


}

int pMT::findHash(string mhash)
/*
* @brief does this hash exist in the tree?
* @param mhash, a string to search for in the tree
* @return 0 if not found, else number of opperations required to find the matching hash*/
{


	found = false;
	count++;
	treeNode* node = myMerkle.root;
	findHashHelper(mhash, node);

	if (found == false)
	{
		cout << "\nHash Not Found";
	}
	return count;


}

int pMT::findHashHelper(string mhash, treeNode* node) //Inorder Traversal
{
	count++;
	if (node->left_ != NULL)
	{
		findHashHelper(mhash, node->left_);

	}
	if (node->data == mhash)
	{
		cout << "Hash '" << mhash << "' found." << endl;
		found = true;
	}
	if (node->right_ != NULL)
	{
		findHashHelper(mhash, node->left_);
	}
	return count++;
}

//Not defined in the header
string pMT::locateData(string vote)
/**
 * @brief Function takes a hash of Vote and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
 * @param vote, the data to search for
 * @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
 */
{
	// Check if the input is "found" in the tree - if input is found, locate the input. Otherwise, print that the input
	// has not been located.
	string input;
	if (hashSelected == 1) {
		input = hash_1(vote);
	}
	else if (hashSelected == 2) {
		input = hash_2(vote);
	}
	else if (hashSelected == 3) {
		input = hash_3(vote);
	}
	else {
		input = hash_2(vote);
	}
	
	myMerkle.path = "- ";
	if (myMerkle.find(input))
	{
	locateH(myMerkle.root, input, myMerkle.path);
	return myMerkle.path;
	}
	else
	{
	return "Input not located.";
	}
}


//Not defined in the header
string pMT::locateHash(string input)
/**
 * @brief Function takes a hash and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
 * @param mhash, the hash to search for
 * @return sequence of L's and R's comprising the movement to the hash node, ; else return a dot '.'
 */
{
	// Check if the input is "found" in the tree - if input is found, locate the input. Otherwise, print that the input
	// has not been located.
	myMerkle.path = "- ";
	if (myMerkle.find(input))
	{
		locateH(myMerkle.root, input, myMerkle.path);
		return myMerkle.path;
	}
	else
	{
		return "Input not located.";
	}
}



void pMT::locateH(treeNode* subtree, string data, string  pathway)
{
	// Check if the data is located in the root node.
	if (subtree->data == data)
	{
		myMerkle.path = pathway;
		return;
	}
	// Recursively check if the data is in the root of the left subtree.
	if (subtree->left_ != NULL)
	{
		locateH(subtree->left_, data, pathway + "L ");
	}
	// Recursively check if the data is in the root of the right subtree.
	if (subtree->right_ != NULL)
	{
		locateH(subtree->right_, data, pathway + "R ");
	}

}




string pMT::hash_1(string key)

 //* @brief A function that takes in a key and returns a hash of that key using some custom function
 //* @param key, a string
 //* @return a hash of the key
 
{
	
	vector<int> keyInts;
	int length = key.size();
	for (int i = 0; i <= length; i++) {
		char temp = key.at(i);
		int temp2 = temp;
		keyInts.push_back(temp2);
	}
	int total = 0;
	string hash;
	for (int i = 0; i <= length; i++) {
		total = total + i;
	}
	hash = to_string(total);

	return hash;
}

string pMT::hash_2(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	string queenb;


	for (std::size_t i = 0; i < key.length(); i++)
	{
		hash = hash * a + key[i];
		a = a * b;
	}

	queenb = to_string(hash);
	return queenb;
}

string pMT::hash_3(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	char tmp;
	vector<char> vect[1];

	//Reverses the spelling of the word, reassigns certain characters to new ones and pushes it into a vector, then returns the values int he vector back to a string in index order.
	for (int i = key.length(); i >= 0; i--)
	{
		char tmp = key.at(i);
		if (tmp == '|')
		{
			tmp == '*';
		}
		else if (tmp == 'e')
		{
			tmp == '}';
		}
		else if (tmp == 'i')
		{
			tmp == '~';
		}
		else if (tmp == 'o')
		{
			tmp == '9';
		}
		else if (tmp == 't')
		{
			tmp == '7';
		}
		else if (tmp == 'n')
		{
			tmp == '5';
		}
		else if (tmp == 's')
		{
			tmp == '3';
		}
		else if (tmp == 'h')
		{
			tmp == '1';
		}
		vect->push_back(tmp);
	}

	stringstream ss;
	copy(vect->begin(), vect->end(), ostream_iterator<char>(ss, " "));

	key.clear();
	key = ss.str();
	key = key.substr(0, key.length() - 1);
	return key;
}
		

bool operator ==(const pMT& lhs, const pMT& rhs) //removed "friend", "pMT::"
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if equal, false otherwise
 */
{
	return lhs.myMerkle.root->data == rhs.myMerkle.root->data;
}

bool operator !=(const pMT& lhs, const pMT& rhs) //removed "friend", "pMT::"
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
	if (lhs.myMerkle.root->data == rhs.myMerkle.root->data)
	{
		return false;
	}
	else
	{
		return true;
	}
}

pMT operator ^=(const pMT& lhs, const pMT& rhs) //removed "friend", "pMT::"
/**
 * @brief XOR between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
    
}
/*void pMT::Print()
{
	printPrivate(myMerkle.root);

}*/
void pMT::printPrivate(treeNode* PouderValley)
{
	if (myMerkle.root != NULL)
	{
		if (PouderValley->left_ != NULL)
		{
			printPrivate(PouderValley->left_);
		}
		cout << PouderValley->data << " ";
		if (PouderValley->right_ != NULL)
		{
			printPrivate(PouderValley->right_);
		}
	}
	else
	{
		cout << "Tree is  Empty" << endl;
	}
}

void pMT::postOrder(treeNode* temp) {
	myMerkle.traversal.clear();
	if (temp->left_ == NULL&&temp->right_ == NULL) {
		myMerkle.traversal.push_back(temp->data);
	}
	else
	{

		if (temp->left_ != NULL) {
			postOrder(temp->left_);
		}

		if (temp->right_ != NULL) {
			postOrder(temp->right_);
		}
		myMerkle.traversal.push_back(temp->data);

	}
}

std::ostream& operator <<(std::ostream& out, pMT& p) //removed "friend", "pMT::"
/**
 * @brief Print out a tree
 * @param out
 * @param p
 * @return a tree to the screen
 */
{
	p.myMerkle.postOrder(p.myMerkle.root);
	for (int i = 0; i < p.myMerkle.traversal.size(); i++) {
		out << p.myMerkle.traversal[i] << " ";
	}
	return out;
}


pMT operator ^(const pMT& lhs, const pMT& rhs) //removed "friend", "pMT::"
/**
 * @brief Where do two trees differ
 * @param lhs
 * @param rhs
 * @return a tree comprised of the right hand side tree nodes that are different from the left
 */
{
}