#include<iostream>
using namespace std;
class intervalheap {
	int** h;
	int heapsize;
	int maxsize;
	int count;
	int index=0;

public:
	intervalheap() {                                //default constructor gives 10 size to array
		count = 0;
		heapsize = 0; 
		maxsize = 10;
		h = new int* [2];
		h[0] = new int[10];
		h[1] = new int[10];
		for(int i = 0;i < 10;i++) {
			h[0][i] = -999;
			h[1][i] = -999;
		}
	}
	intervalheap(int max) {                               //parameterized constuctor
		maxsize = max;
		count = 0;
		heapsize = 0;
		h = new int*[2];
		h[0] = new int[maxsize];
		h[1] = new int[maxsize];
		for (int i = 0;i < maxsize;i++) {
			h[0][i] = -999;
			h[1][i] = -999;
		}
	}
	void insert(int key) {
		
		if (count == 0) {                                       //for first value in array
			h[0][0] = key;
		}
		else if (count == 1) {                                  //for second value in array
			if (h[0][0] > key) {
				h[1][0] = h[0][0];
				h[0][0] = key;
			}
			else
				h[1][0] = key;
		}
		else if (count % 2 == 0) {                              //if count%2==0, it is odd insertion
			h[0][index] = key;
		}
		else {                                                  //even insertion
			if (h[0][index] > key) {
				h[1][index] = h[0][index];
				h[0][index] = key;
			}
			else
			    h[1][index] = key;
		}
		count++;
		if (count % 2 == 0)                                     //increment index after every two insertions
			index++;

		reheapup(key);                                         //call reheap up
	}

	void reheapup(int key) {
		bool flag = true;
		int tempindex;
		
		if (h[0][index] == -999 && h[1][index] == -999)                //calculate child index 
			 tempindex = index - 1;
		else
			tempindex = index;
		
		int parent = (tempindex - 1) / 2;                             //calculate parent index


		while (parent >= 0&&flag) {
			if (h[0][tempindex] < h[0][parent] && h[0][tempindex]!=-999) {                  //if it is out of lower bounds of parent
				int temp = h[0][parent];
				h[0][parent] = h[0][tempindex];
				h[0][tempindex] = temp;
			}
			if (h[1][tempindex] > h[1][parent] && h[1][tempindex] != -999) {                //if out of upper bounds of parent
				int temp = h[1][parent];
				h[1][parent] = h[1][tempindex];
				h[1][tempindex] = temp;
			}
			if (h[0][tempindex] > h[1][parent] && h[1][parent]!=-999 && h[0][tempindex]!=-999) {     //if out of lower bounds
				int temp = h[0][tempindex];
				h[0][tempindex] = h[1][parent];
				h[1][parent] = temp;
			}
			if (h[1][tempindex] < h[0][parent] && h[1][tempindex] != -999) {                    //out of upper bounds
				int temp = h[1][tempindex];
				h[1][tempindex] = h[0][parent];
				h[0][parent] = temp;
			}
			tempindex = parent;
			parent = (tempindex - 1) / 2;

			if (tempindex == 0)                                        //if previous index was 0, exit loop
				flag = false;
		}

	}
	void print() {
		int c = (count + 1) / 2;
		for (int i = 0;i < c;i++) {
			cout << h[0][i] << " ";
			if (h[1][i] == -999)                                         //if odd number of enteries, print interval e.g. 23,23
				cout << h[0][i] << endl;
			else
				cout << h[1][i] << endl;                                
		}
		cout << endl;
	}
	void reheapdown() {
		bool flag=true;
		int newparent=0;
		int child = 0;
		int parent = 0;
		while (h[0][child+1]!=-999 || h[1][child+1]!=-999) {
			flag = false;
			child = parent * 2 + 1;                                               //check for left child
			


			//check all upper and lower bounds

			if (h[0][parent] > h[0][child] && h[0][child]!=-999) {
				int temp = h[0][parent];
				h[0][parent] = h[0][child];
				h[0][child] = temp;
				newparent = child;
				flag = true;
			}
			if (h[1][parent] < h[1][child] && h[1][child] != -999) {
				int temp = h[1][parent];
				h[1][parent] = h[1][child];
				h[1][child] = temp;
				newparent = child;
				flag = true;
			}
			if (h[0][child] > h[1][parent] && h[0][child] != -999) {
				int temp = h[0][child];
				h[0][child] = h[1][parent];
				h[1][parent] = temp;
				flag = true;
			}
			if (h[1][child] < h[0][parent] && h[1][child] != -999) {
				int temp = h[1][child];
				h[1][child] = h[0][parent];
				h[0][parent] = temp;
				flag = true;
			}
			if (h[0][child] > h[1][child] && h[1][child] != -999) {
				int temp = h[0][child];
				h[0][child] = h[1][child];
				h[1][child] = temp;
				flag = true;
			}
			if (flag)
				continue; 
			child = parent * 2 + 2;                                                        //check for right child
			
			
			//check all upper and lower bounds
			
			if (h[0][parent] > h[0][child] && h[0][child] != -999) {
				int temp = h[0][parent];
				h[0][parent] = h[0][child];
				h[0][child] = temp;
				newparent = child;
				flag = true;
			}
			if (h[1][parent] < h[1][child] && h[1][child] != -999) {
				int temp = h[1][parent];
				h[1][parent] = h[1][child];
				h[1][child] = temp;
				newparent = child;
				flag = true;
			}
			if (h[0][child] > h[1][parent] && h[0][child] != -999) {
				int temp = h[0][child];
				h[0][child] = h[1][parent];
				h[1][parent] = temp;
				flag = true;
			}
			if (h[1][child] < h[0][parent] && h[1][child] != -999) {
				int temp = h[1][child];
				h[1][child] = h[0][parent];
				h[0][parent] = temp;
				flag = true;
			}
			if (h[0][child]>h[1][child] && h[1][child] != -999) {
				int temp = h[0][child];
				h[0][child] = h[1][child];
				h[1][child] = temp;
				flag = true;
			}
			parent++;
		}
	}

	void update(int newlow,int newhigh) {
		if (newlow > newhigh) {
			int temp = newhigh;
			newhigh = newlow;
			newlow = temp;
		}
		h[0][0] = newlow;                          //update lower and upper interval of 0 index (root)
		h[1][0] = newhigh;
		reheapdown();                              //call reheap down
	}

	void deleteinterval() {
		int c = ((count + 1) / 2) - 1;
		h[0][0] = h[0][c];                          //place last index's data on root
		h[1][0] = h[1][c];

		h[0][c] = -999;                             //delete last index
		h[1][c] = -999;

		if (count % 2 == 0) {
			count = count - 2;
		}
		else {
			count--;
		}

		reheapdown();                               //call reheap down
	}
};
int main() {

	intervalheap H;

	cout << "MAIN MENU" << endl;
	int choice = 0;
	int insert=0, updatelow=0, updatehigh=0;
	do {
		cout << "Press 1 for insertion" << endl;
		cout << "Press 2 for deletion" << endl;
		cout << "Press 3 for updation" << endl;
		cout << "Press 4 for printing" << endl;
		cout << "Press 0 for exiting" << endl;

		cin >> choice;

		if (choice == 1) {
			cout << "enter value to insert: " << endl;
			cin >> insert;
			if (insert <= 0) {
				while (insert <= 0) {
					cout << "enter again: " << endl;
					cin >> insert;
				}
			}
			H.insert(insert);
		}
		if (choice == 2) {
			H.deleteinterval();
		}
		if (choice == 3) {
			cout << "enter low value of interval: " << endl;
			cin >> updatelow;
			if (updatelow <= 0) {
				while (updatelow <= 0) {
					cout << "enter again: " << endl;
					cin >> updatelow;
				}
			}
			cout << "enter high value of interval: " << endl;
			cin >> updatehigh;
			if (updatehigh <= 0) {
				while (updatehigh <= 0) {
					cout << "enter again: " << endl;
					cin >> updatehigh;
				}
			}

			H.update(updatelow, updatehigh);
		}
		if (choice == 4) {
			H.print();
		}
	} while (choice != 0);


	system("pause");
	return 0;
}