#include "bstTree.hpp"
#include "NodeT.hpp"

/*BST.cpp: You must write the BST.cpp and complete the following methods:*/

bool bstTree::insert(string f) {
	NodeT *s = new NodeT(f);
	if (root == NULL) {
		root = s;
		return true;
	}
	NodeT *temp = root;
	//bstNode left = s->left;
	//bstNode right = s->right;
	while (temp) {

		if (f < temp->w->word) {
			if (temp->left == NULL) {
				temp->left = s;
				temp->left->parent = temp;
				setHeight(temp);
				return true;
			} else {
				temp = temp->left;
			}
		} else if (f > temp->w->word) {
			if (temp->right == NULL) {
				temp->right = s;
				temp->right->parent = temp;
				setHeight(temp);
				return true;
			} else {
				temp = temp->right;
			}
		} else
			return false; //equal
	}
	return false;
}

/*: this method takes as input parameters all the fields necessary to create a student object (and will be the fields passed into the bstNode constructor, where the student field exists).  This method returns true if a new node is created and the data is inserted into the tree successfully, and false otherwise.
 Data is inserted alphabetically based:
 1)	on the last name (the l input parameter) and, if there are 2 last names the same,
 2)	then on the first name (f).
 Since we didn�t have any two students with the same name, we don�t have to worry about using the n to sort on if the last name and the first name are the same.
 Be aware: when you insert a new node into the binary search tree, this method should call the setHeights method to adjust the heights */

NodeT* bstTree::find(string l, string f) {
	NodeT *temp = root;
	while (temp) {
		string l_temp = f;
		//string f_temp = temp->student->first;
		if (l_temp == l) {
			return temp;
		} else if (l < l_temp) {
			temp = temp->left;
		} else { //greater than, goes right
			temp = temp->right;
		}
	}
	return NULL;
}

/*:finds whether a student with the last name l and first name f is in the tree is in the tree, and, if it is, returns the node holding that student.  Otherwise it returns NULL.
 //Note that if you find the last name l, you must then check for the first name f.  If it�s not the same, you must keep searching until you find both the last name and the first name, and, if you don�t, return NULL
 */
void bstTree::printTreeIO(NodeT *n) {
	NodeT *temp = n;
	if (temp) {
		if (temp->left == NULL)
			;
		else {
			printTreeIO(temp->left);
		}
		n->printNode();
		if (temp->right == NULL)
			;
		else {
			printTreeIO(temp->right);
		}
	}

} //(3): recursive function that prints out the data in the tree in order

void bstTree::printTreePre(NodeT *n) {
	NodeT *temp = n;
	if (temp) {
		n->printNode();
		if (temp->left == NULL)
			;

		else {
			printTreePre(temp->left);
		}
		if (temp->right == NULL)
			;

		else {
			printTreePre(temp->right);
		}
	}

} //(3):  a recursive function that prints out the data in the tree in pre-order

void bstTree::printTreePost(NodeT *n) {
	NodeT *temp = n;
	if (temp) {
		if (temp->left == NULL)
			;

		else {
			printTreePost(temp->left);
		}
		if (temp->right == NULL)
			;

		else {
			printTreePost(temp->right);
		}
		n->printNode();
	}

} //(3):  a recursive function that prints out the data in the tree in post-order

NodeT* bstTree::remove(string l, string f) //removes node from tree and returns that node
		{
	NodeT *temp = find(l, f);
	NodeT *furthest_right;
	if (temp == NULL) {
		return NULL;
	}
	if (temp->left == NULL && temp->right == NULL) //no kids
	{
		removeNoKids(temp);
	} else if (temp->left && temp->right == NULL) //left is not NULL, right is NULL
	{
		removeOneKid(temp, true);
	} else if (temp->left == NULL && temp->right) //left is  NULL, right is not NULL
			{
		removeOneKid(temp, false);
	} else { //there are two children
		NodeT *right_temp = temp->right;
		NodeT *n = temp->left;
		NodeT *temp_parent = temp->parent;
		while (n) //finds furthest right
		{
			furthest_right = n;
			n = n->right;
		}
		if (temp_parent->right == temp) //makes temps parent point to furthest right
				{
			temp_parent->right = furthest_right;
		} else {
			temp_parent->left = furthest_right;
		}
		if (temp->left != furthest_right) {
			temp->left->parent = furthest_right; //makes temps left kid point to furthest right, if it exists
			furthest_right->left = temp->left; //makes furthest right point to temps left kid, if it exists
			furthest_right->parent->right = NULL; //makes furthest rights old parent point to null for their right kid
		} else {
			furthest_right->left = NULL;
		}
		if (temp->right != NULL)
			temp->right->parent = furthest_right; //makes temps right kid point to furthest right, if it exits
		furthest_right->right = right_temp;
		furthest_right->parent = temp->parent;
	}
	setHeight(temp);
	return temp;
}

//(8) � this method removes a node from the tree, and returns that node.
//There are 3 cases when you remove a node: either the node being removed has no children (left or right), in which case this method calls the method removeNoKids, the  node you are removing has only one child, in which case the method calls removeOneKid (with a Boolean flag set to true if there is a left child, and false if there is a right child),
//or the node being removed has both a left and a right child, in which you replace the node being removed with the appropriate replacement child, and then remove the node used as a replacement by calling either removeNoKids or removeOneKid, depending on which is appropriate.

NodeT* bstTree::removeOneKid(NodeT *tmp, bool leftFlag) //for removing a node with one child, leftflag being used to determine if the child is on the left or right
		{
	NodeT *temp = tmp;
	if (leftFlag) {
		if (temp->parent->left == temp) {
			temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
		} else {
			temp->parent->right = temp->left;
			temp->left->parent = temp->parent;
		}
	} else {
		if (temp->parent->left == temp) {
			temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
		} else {
			temp->parent->right = temp->right;
			temp->right->parent = temp->parent;
		}
	}
	return temp;
}

NodeT* bstTree::removeNoKids(NodeT *tmp) //for removing a node with no children
		{
	NodeT *temp = tmp;
	if (temp->parent->left == temp) {
		temp->parent->left = NULL;
	} else {
		temp->parent->right = NULL;
	}
	return temp;
}

void bstTree::setHeight(NodeT *n) { //This method sets the heights of the nodes in a tree
	NodeT *temp = n;
	int h = 0;
	while (temp != NULL) //changing there nodes ansestors heights
	{
		if (temp->left != NULL)
			h = temp->left->height;
		if (temp->right != NULL) //setting the height to the highest height between the two kids
		{
			if (h < temp->right->height)
				h = temp->right->height;
		}
		h++;
		temp->height = h;
		if (temp->parent == NULL)
			break;
		if (temp->parent->height >= (temp->height + 1))
			break;
		temp = temp->parent;
	}
} //(10): This method sets the heights of the nodes in a tree.  Once a node is inserted, only the node�s ancestors can have their height changed.  Thus you should set the height of the node being inserted (to 1) and then adjust the heights of the node�s parent, grandparent, etc. up until either the height of the node doesn�t change or you hit the root.

bstTree::bstTree() {  // empty constructor
	size = 0;
	root = NULL;
}

bstTree::bstTree(string f) {  // constructor that forms the root
	root = new NodeT(f);
	size = 1;
}

void bstTree::clearTree() {  	//clears out an old tree
//This calls the recursive clearTree with the root node
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	} else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}
void bstTree::clearTree(NodeT *tmp) {
	if (tmp == NULL) {
		return;
	} else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete (tmp);
	}
}

/*Note: the following three functions� sole job is to call printTreeIO(BstNode *t),printTreePre(BstNode *t), and printTreePost(BstNode *t) while printint out which
 Function is being called.
 YOU MUST STILL WRITE THE RECURSIVE VERSION OF THESE FUNCTIONS!!!*/

void bstTree::printTreeIO() { // Just the start � you must write the recursive version
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		cout << endl << "Printing In Order:" << endl;
		printTreeIO(root);
	}
}
void bstTree::printTreePre() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		cout << endl << "Printing PreOrder:" << endl;
		printTreePre(root);
	}
}
void bstTree::printTreePost() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		cout << endl << "Printing PostOrder:" << endl;
		printTreePost(root);
	}
}

/***************************************************************************/
