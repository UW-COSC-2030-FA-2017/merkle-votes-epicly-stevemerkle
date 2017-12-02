#include "bTREE.h"
#include <queue>



//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	root = new treeNode();
	root->data = "";

	q = new queue<treeNode*>();
}

bTREE::~bTREE()
{
}




int bTREE::insert(string data, int time)
{
	treeNode* temp2 = new treeNode();
	temp2->data = data;
	temp2->time = time;
	temp2->left_ = NULL;
	temp2->right_ = NULL;
	int counter = 0;

	if(root->data == ""){
		root = temp2;
		q->push(root);	
	}
	else{
	// Do level order traversal until we find
	// an empty place. 
		treeNode* tmp = q->front();
		if (tmp->left_==NULL) {
				counter++;
				tmp->left_ = temp2;
				q->push(temp2);
		}
		else if (tmp->right_==NULL) {
				counter++;
				tmp->right_ = temp2;
				q->push(temp2);
				q->pop();
		}
	}
	return counter;
}
	

int bTREE::inorderTraversal(string treasure, treeNode* node)
{
	counter++;
	if (node->left_ != NULL)
	{
		inorderTraversal(treasure, node->left_);
	}
	if (node->data == treasure)
	{
		cout << "\nString '" << treasure << "' found." << endl;
		found = true;

	}
	if (node->right_ != NULL)
	{
		inorderTraversal(treasure, node->right_);
	}
	return counter;
}



int bTREE::find(string treasure)
{
	found = false;
	counter++;
	treeNode* node = root;
	inorderTraversal(treasure, node);
	if (found == false)
	{
		cout << "\nThe string was not found in the tree" << endl;
	}
	return counter;
}


string bTREE::locate(string input)
{
	// Check if the input is "found" in the tree - if input is found, locate the input. Otherwise, print that the input
	// has not been located.
	path = "- ";
	if (find(input))
	{
		locateH(root, input, path);
		return path;
	}
	else
	{
		return "Input not located.";
	}
}


void bTREE::locateH(treeNode* subtree, string data, string  pathway)
{
	// Check if the data is located in the root node.
	if (subtree->data == data)
	{
		path = pathway;
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




bool operator ==(const bTREE& lhs, const bTREE& rhs)//removed friend, bTree, "::"  Omar 
{
	return lhs.root == rhs.root;
}

bool operator !=(const bTREE& lhs, const bTREE& rhs)//same here
{
	if (lhs.root == rhs.root)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void bTREE::postOrder(treeNode* temp) {
	traversal.clear();
	if (temp->left_ ==NULL&&temp->right_==NULL) {
		traversal.push_back(temp->data);
	}
	else
	{

		if (temp->left_ != NULL) {
			postOrder(temp->left_);
		}

		if (temp->right_ != NULL) {
			postOrder(temp->right_);
		}
		traversal.push_back(temp->data);

	}
}

void bTREE::Print()
{
	
	printPrivate(root);

}
void bTREE::printPrivate(treeNode* Felp)
{
	if (root != NULL)
	{
		if (Felp->left_ != NULL)
		{
			printPrivate(Felp->left_);
		}
		cout << Felp->data << " ";
		if (Felp->right_ != NULL)
		{
			printPrivate(Felp->right_);
		}
	}
	else
	{
		cout << "Tree is  Empty" << endl;
	}
}


std::ostream& operator <<(std::ostream& out, bTREE& p) //same here
{
	p.postOrder(p.root);
	for (int i = 0; i < p.traversal.size(); i++) {
		out << p.traversal[i] << " ";
	}
	return out;
}
