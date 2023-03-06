#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
struct student {
	string firstname;
	string lastname;
	string dept;
	float cgpa;
	int batch;
	student(string fname,string lname,string dep,int batch1,float gpa) {
		firstname = fname;
		lastname = lname;
		cgpa = gpa;
		dept = dep;
		batch = batch1;
	}
	student() {
		firstname = "";
		lastname = "";
		cgpa = 0;
		dept = "";
		batch = 0;
	}
	void operator =(student S) {
		firstname = S.firstname;
		lastname = S.lastname;
		dept = S.dept;
		cgpa = S.cgpa;
		batch = S.batch;
	}
};
template <typename T>
struct node {
	T key;
	int value;
	node* right, * left, * parent;
	node(){
		value = 0;
		left = right = parent = NULL;
	}
	node(int val,T t) {
		key = t;
		value = val;
		right = left = parent = NULL;
	}
	void operator=(node N) {
		value = N.value;
		key = N.key;
		left = N.left;
		right = N.right;
		parent = N.parent;
	}
};
class BST {
public:
    node<student>* root;

	BST() {
		root = NULL;
	}
	void rightrotation(node<student>* x) {
		node<student>* temp = x->left;
		x->left = temp->right;
		if (temp->right != NULL)                               //updating parent of right node
			temp->right->parent = x;
		
		temp->parent = x->parent;
		if (x->parent == NULL)
			root = temp;                                        //if no parent present, make it root node
		else if (x == x->parent->right)
			x->parent->right = temp;
		else if (x == x->parent->left)
			x->parent->left = temp;

		temp->right = x;
		x->parent = temp;
	}

	void leftrotation(node<student>* x) {                    
		node<student>* temp = x->right;
		x->right = temp->left;
		if (temp->left != NULL)                               //updating parent of left node
			temp->left->parent = x;

		temp->parent = x->parent;
		if (x->parent == NULL)                                 //updating root if no parent is present
			root = temp;
		else if (x == x->parent->left) {
			x->parent->left = temp;
		}
		else if(x == x->parent->right)
			x->parent->right = temp;

		temp->left = x;                          
		x->parent = temp;
	}

	void BringToTop(node<student>* child) {
		if (child == NULL)                                         //empty tree
			return;
		while (child->parent != NULL) {                            //child is not the root node
			if (child->parent == root) {                         //if child is root's son
				if (child->parent->left == child)
					rightrotation(child->parent);
				else
					leftrotation(child->parent);
			}

			else {                                                  //if grandparent is resent, find relation
				node<student>* parent = child->parent;
				node<student>* grandparent = parent->parent;

				if (child == child->parent->left && parent == parent->parent->left) {             //LL
					rightrotation(grandparent);
					rightrotation(parent);
				}
				else if (child == child->parent->right && parent == parent->parent->right) {       //RR
					leftrotation(grandparent);
					leftrotation(parent);
				}

				else if (child == child->parent->left && parent == parent->parent->right) {         //RL
					rightrotation(parent);
					leftrotation(grandparent);
				}
				else if (child == child->parent->right && parent == parent->parent->left) {        //LR
					leftrotation(parent);
					rightrotation(grandparent);
				}
			}
		}
	}

	bool insert(node<student> *Node) {                                          //wrapper function for insertion
		node<student>* y=insertR(root, Node);
		BringToTop(y);                                           //send newly created node to splay function
		return true;
	}
	node<student>* insertR(node<student>*& root, node<student>*& Node) {                            //takes root and key to insert
		node<student>* curr = root;
		node<student>* y = NULL;                             

		while (curr) {                                              //find right place of new node in BST
			y = curr;
			if (Node->value == curr->value) {
				cout << "Student with rollno already present. Can't enter again" << endl;
				return NULL;
			}
			else if (Node->value < curr->value)
				curr = curr->left;
			else if (Node->value > curr->value)
				curr = curr->right;
		}

		Node->parent = y;                               //make y as the parent of newly entered node
		if (y == NULL)
			root = Node;
		else if (Node->value < y->value)                         //place new node on left/right depending on value compared to parent node
			y->left = Node;
		else if (Node->value > y->value)
			y->right = Node;

		return Node;                                //return node

	}

	node<student>* search(int key) {
		return searchR(root, key);                                      //helper function
	}

	node<student>* searchR(node<student>*& root, int key) {

		if (root == NULL)                                            //tree is empty
			return NULL;

		if (root->value == key) {                                     //if key is found, store it in temp to return it and splay the tree
			node<student>* temp = root;
			BringToTop(root);                                       
			return temp;
		}
		//traverse to find the key in tree
		else if (root->value < key) {
			if(root->right!=NULL)
			return searchR(root->right, key);
		}
		else if (root->value > key) {
			if(root->left!=NULL)
			return searchR(root->left, key);
		}
		BringToTop(root);
		return NULL;                                              //if key not found
	}


	void printinorder() {
		printinorderR(root);
		cout << endl;
	}
	void printinorderR(node<student>*& root) {
		if (root == NULL)
			return;
		else {
			printinorderR(root->left);
			cout << root->value << " ";
			printinorderR(root->right);
		}
	}

	void printpreorder() {
		printpreorderR(root);
		cout << endl;
	}
	void printpreorderR(node<student>*& root) {
		if (root == NULL)
			return;
		else {
			cout << root->value << " ";
			printpreorderR(root->left);
			printpreorderR(root->right);
		}
	}

	bool delete1(int key) {                                  //helper function
		return deleteR(key, root);
	}
	bool deleteR(int key, node<student>*& root) {
		bool flag;
		if (root!=NULL && key < root->value) {                        
			if (root->left != NULL) {                        //if left of current node is null, don't call the function again, go out and return false
				flag = deleteR(key, root->left);
				return flag;
			}
		}
		else if (root!=NULL && key > root->value) {           //if right subtree is null and key is not found
			if (root->right != NULL) {
				flag = deleteR(key, root->right);
				return flag;
			}
		}
		else if(root!=NULL && root->value == key) {           //if key is found, delete it and splay the tree around its parent node
			deletenode(root);
			if(root!=NULL&&root->parent!=NULL)
			BringToTop(root->parent);
			return true;
		}
		BringToTop(root);                                   //when key is not found
		return false;
	}
	void deletenode(node<student>*& ptr) {
		node<student>* temp1=ptr;
		if (ptr->left == NULL) {                        //node has one child only
			ptr = ptr->right;
			if(ptr!=NULL)
			ptr->parent = temp1->parent;

			delete temp1;
		}
		else if (ptr->right == NULL) {
			ptr = ptr->left;
			if(ptr!=NULL)
			ptr->left->parent = temp1;

			delete temp1;
		}
		else {                                              //node has 2 children
			node<student>* temp = predecessor(ptr->left);
			ptr->value = temp->value;
			deleteR(temp->value, ptr->left);
		}
	}
	node<student>* predecessor(node<student>* ptr) {
		while (ptr->right != NULL) {
			ptr = ptr->right;
		}
		return ptr;
	}
	~BST() {                                                 //destructor
		destroy(root);
	}
	void destroy(node<student>*& root) {
		if (root == NULL)
			return;
		destroy(root->left);
		destroy(root->right);
		delete root;
	}

	void update(int oldRollNumber, int newRollNumber, string newFirstName, string newLastName, int newBatch, string newDepartment, float newCgpa){
		node<student>* up=search(oldRollNumber);                                     //search the node in tree and update its data
		up->value = newRollNumber;
		up->key.firstname = newFirstName;
		up->key.lastname = newLastName;
		up->key.batch = newBatch;
		up->key.cgpa = newCgpa;
		up->key.dept = newDepartment;
		cout << "Successfully updated!" << endl;


		int tempval; student tempkey;
		int curr=up->value;                                                             //store values of updated node
		while (up->left!=NULL && up->value < up->left->value || up->right!=NULL && up->value > up->right->value) {
			if (up->left!=NULL && up->value < up->left->value) {                            //if updated node is smaller than left subtree, swap values
				tempval = up->value;
				tempkey = up->key;
				up->value = up->left->value;
				up->key = up->left->key;

				up->left->key = tempkey;
				up->left->value = tempval;
			}
			else if (up->right!=NULL && up->value > up->right->value) {              //if updated node is larger than right subtree, swap values until BST is maintained
				tempval = up->value;
				tempkey = up->key;
				up->value = up->right->value;
				up->key = up->right->key;

				up->right->key = tempkey;
				up->right->value = tempval;
			}
		}
		search(curr);                     //search the updated node again so it comes to top/root due to splaying
	}
    
	//calculate total nodes
	int noofnodes() {
		return countnodes(root);
	}
	int countnodes(node<student>*& root) {
		if (root == NULL)
			return 0;

		return (countnodes(root->left) + countnodes(root->right) + 1);
	}

	//inorder using VECTORS
	void inorder() {
		vector<node<student>*> nodes;
		inorder(root, nodes);
		inorder(nodes);
	}
	void inorder(node<student>*& root, vector<node<student>*>& nodes) {
		if (root == NULL)
			return;

		inorder(root->left, nodes);
		nodes.push_back(root);                                         //add nodes in vector in order
		inorder(root->right, nodes);
	}
	void inorder(vector<node<student>*>& nodes) {
		cout << "INORDER PRINTING" << endl;
		for (int i = 0; i <nodes.size() ;i++) {
			cout << "student " << i + 1 << endl;
			cout << "rollno " << nodes[i]->value << endl;
			cout << "first name " << nodes[i]->key.firstname << endl;
			cout << "last name " << nodes[i]->key.lastname << endl;
			cout << "batch "<< nodes[i]->key.batch << endl;
			cout << "department "<< nodes[i]->key.dept << endl;
			cout << "cgpa "<< nodes[i]->key.cgpa << endl;
		}
		cout << endl;
	}

	//level order using VECTORS
	void levelorder() {
		vector<node<student>*> res;
		vector<node<student>*> V;
		queue<node<student>*> q;
		node<student>* temp;
		int i = 0;
		if (root) {
			q.push(root);
			q.push(NULL);
		}

		while (!(q.empty())) {                              
			temp = q.front();
			q.pop();

			if (q.empty())
				break;

			if (temp) {                              //if temp has a node, push its left and right child in queue
				if (temp->left)
					q.push(temp->left);

				if (temp->right)
					q.push(temp->right);

				V.push_back(temp);
			}
			else {                                    //if temp is NULL, it is the end of a level
				q.push(NULL);
				res.push_back(V.front());
				V.erase(V.begin());
			}
		}
		if (V.size() != 0) {
			while (V.size() > 0) {
				res.push_back(V.front());
				V.erase(V.begin());
			}
		}
		levelorder(res);                                   //send for printing
	}
	//prints levelorder VECTORS 
	void levelorder(vector<node<student>*> nodes) {
		cout << "LEVEL ORDER PRINTING" << endl;
		for (int i = 0; i < nodes.size();i++) {
			cout << "student " << i + 1 << endl;
			cout << "rollno " << nodes[i]->value << endl;
			cout << "first name " << nodes[i]->key.firstname << endl;
			cout << "last name " << nodes[i]->key.lastname << endl;
			cout << "batch " << nodes[i]->key.batch << endl;
			cout << "department " << nodes[i]->key.dept << endl;
			cout << "cgpa " << nodes[i]->key.cgpa << endl;
		}
		cout << endl;
	}

	//search that return student object
	student* search1(int key) {
		return search1R(root, key);                                      //helper function
	}

	student* search1R(node<student>*& root, int key) {

		if (root == NULL)                                            //tree is empty
			return NULL;

		if (root->value == key) {                                     //if key is found, store it in temp to return it and splay the tree
			node<student>* temp = root;
			BringToTop(root);
			return &temp->key;
		}
		//traverse to find the key in tree
		else if (root->value < key) {
			if (root->right != NULL)
				return search1R(root->right, key);
		}
		else if (root->value > key) {
			if (root->left != NULL)
				return search1R(root->left, key);
		}
		BringToTop(root);
		return NULL;                                              //if key not found
	}

};
class StudentBST {
public:
	BST B;
};
int main() {

	StudentBST S;
	//BST B;
	int n; 
	string fname, lname, dept;
	float gpa=9.9; int batch=999, rollno=999;
	cout << "MAIN MENU" << endl;
	
	do {
		cout << "Press 1 for Insertion" << endl;
		cout << "Press 2 for Searching" << endl;
		cout << "Press 3 for Deletion" << endl;
		cout << "Press 4 for Printing" << endl;
		cout << "Press 5 for Updation" << endl;
		cout << "Press 0 for Exit" << endl;
		cout << "enter: ";
		cin >> n; cout << endl;
		node<student>* flag;
		
		if (n == 1) {                                                      //for insertion
			cout << "enter rollno: ";
			cin >> rollno;
			if (rollno < 0) {                                               //rollno must be +ve
				while (rollno < 0) {
					cout << "enter positive rollno again: ";
					cin >> rollno;
					cout << endl;
				}
			}
			flag=S.B.search(rollno);
			if (flag) {                                                       //rollno shouldn't be present previously
				cout << "rollno already present" << endl;
				while (flag) {
					cout << "enter rollno again: " << endl;
					cin >> rollno;
					if (rollno < 0) {
						while (rollno < 0) {
							cout << "enter positive rollno again: ";
							cin >> rollno;
							cout << endl;
						}
					}
					flag = S.B.search(rollno);
				}
			}

			cout << "enter first name: "; cin >> fname; cout << endl;
			cout << "enter last name: "; cin >> lname; cout << endl;
			cout << "enter department name: "; cin >> dept; cout << endl;

			cout << "enter batch: ";
			cin >> batch;
			if (batch < 0) {
				while (batch < 0) {
					cout << "enter positive rollno again: ";
					cin >> batch;
					cout << endl;
				}
			}

			cout << "enter cgpa: ";
			cin >> gpa;
			if (gpa < 0|| gpa>4.0) {
				while (gpa < 0||gpa>4.0) {
					cout << "enter positive rollno between 0-4 again: ";
					cin >> gpa;
					cout << endl;
				}
			}
			student S1(fname, lname, dept, batch, gpa);
			node<student>* NODE=new node<student>(rollno, S1);
			S.B.insert(NODE);
		}

		if (n == 4) {                                                         //printing
			cout << "inorder printing" << endl;
			S.B.printinorder();
			cout << "preorder printing" << endl;
			S.B.printpreorder();
			int choice=0;
			cout << "enter 1 for INORDER and 2 for LEVEL ORDER" << endl;
			cin >> choice;
			if (choice <= 0) {
				while (choice <= 0) {
					cout << "enter again: ";
					cin >> choice;
				}
			}
			if(choice==1)
			S.B.inorder();
			else if(choice==2)
			cout << endl << endl;
			S.B.levelorder();
		}

		if (n == 2) {                                                         //searching
			cout << "enter rollno to serach: ";
			cin >> rollno;
			if (rollno < 0) {
				while (rollno < 0) {
					cout << "enter positive rollno again: ";
					cin >> rollno;
					cout << endl;
				}
			}
			student* flag1=S.B.search1(rollno);
			if (flag1) {
				cout << "student of rollno " << rollno << " found" << endl;
				cout << "student name: " << flag1->firstname << " " << flag1->lastname << endl;
				cout << "batch: " << flag1->batch << endl;
				cout << "department: " << flag1->dept << endl;
				cout << "cgpa: " << flag1->cgpa << endl;
			}
			else {
				cout << "student not found" << endl;
			}
		}

		if (n == 3) {
			cout << "enter rollno to delete: ";
			cin >> rollno;
			if (rollno < 0) {
				while (rollno < 0) {
					cout << "enter positive rollno again: ";
					cin >> rollno;
					cout << endl;
				}
			}
			bool check=S.B.delete1(rollno);
			if (check)
				cout << "rollno " << rollno << " Deleted Successfully!" << endl;
			else
				cout << "rollno not present in database" << endl;
		}

		if (n == 5) {
			int oldrollno;
			cout << "enter rollno to update: ";
			cin >> oldrollno;
			if (oldrollno < 0) {
				while (oldrollno < 0) {
					cout << "enter positive rollno again: ";
					cin >> oldrollno;
					cout << endl;
				}
			}
			flag=S.B.search(oldrollno);
			if (flag) {
				cout << "student of rollno " << rollno << " found" << endl;
				cout << "student name: " << flag->key.firstname << " " << flag->key.lastname << endl;
				cout << "batch: " << flag->key.batch << endl;
				cout << "department: " << flag->key.dept << endl;
				cout << "cgpa: " << flag->key.cgpa << endl;

				cout << endl;
				cout << "enter new rollno: "; cin >> rollno; 
				
				if (rollno < 0) {
					while (rollno < 0) {
						cout << "enter positive rollno again: ";
						cin >> rollno;
						cout << endl;
					}
				}

				flag = S.B.search(rollno);
				if (flag && flag->value!=oldrollno) {                                                       //rollno shouldn't be present previously
					cout << "rollno already present" << endl;
					while (flag) {
						cout << "enter rollno again: " << endl;
						cin >> rollno;
						if (rollno < 0) {
							while (rollno < 0) {
								cout << "enter positive rollno again: ";
								cin >> rollno;
								cout << endl;
							}
						}
						flag = S.B.search(rollno);
					}
				}

				cout << "enter updated first name: "; cin >> fname; cout << endl;
				cout << "enter updated last name: "; cin >> lname; cout << endl;
				cout << "enter updated cgpa: "; cin >> gpa; cout << endl;
				cout << "enter updated department: "; cin >> dept; cout << endl;
				
				S.B.update(oldrollno,rollno,fname,lname,batch,dept,gpa);
			}
			else {
				cout << "rollno not found in database" << endl;
			}
		}
	} while (n != 0);

		
	
}