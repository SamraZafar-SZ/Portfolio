#include <iostream>
#include <string>
#include <fstream>
using namespace std;
template<class T>
class stack {
public:                //stack data memebers and functions
	int capacity;
	int top;
	T* list;
	void push(T);
	void pop(T&);
	~stack() {
		if (list != NULL) { delete[] list; }
	}
	bool empty() {
		return (top == -1);
	}
	stack() {
		capacity = 0;
		top = -1;
		list = NULL;
	}
	stack(int s) {
		capacity = s;
		top = -1;
		list = new T[capacity];
	}

};
template<typename T>
void stack<T>::push(T  val) {
	if (top < capacity)
	{
		top++;
		list[top] = val;
	}
}
template<typename T>
void stack<T>::pop(T& val) {
	if (!empty()) {
		val = list[top];
		top--;
	}
}

template<class T>
class xml :public stack<T>
{
public:
	xml<T>(int size) :stack<T>(size) {}
	bool completechecker(string);
	bool attributechecker(string);
	bool checkprolog(string prolog) {              //first line is always this
		return (prolog == "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	}
};
template<typename T>
bool xml<T>::completechecker(string s) {

	bool flag = true;
	char element;
	stack<char> xmlOne(100);
	int i = 0;
	stack<char> xmlTwo(10);
	//xmlTwo.push(s[0]);
	//i++;
	while (i != s.length())                             //chacks braces balance
	{
		if (s[i] == '<' && xmlTwo.list[xmlTwo.top] == '<') {
			flag = false;
			return flag;
		}
		else if (s[i] == '<' && xmlTwo.top == -1) {
			xmlTwo.push(s[i]);
			flag = true;
		}
		else if (xmlTwo.top == -1 && s[i] == '>')
		{
			flag = false;
			return flag;
		}
		else if (s[i] == '>' && xmlTwo.list[xmlTwo.top] == '<') {
			flag = true;
			xmlTwo.pop(element);
		}
		else if (xmlTwo.list[xmlTwo.top] == '>' && s[i] == '>')
		{
			flag = false;
			return flag;
		}

		i++;
	}
	i = 0;
	while (i != s.length()) {                      //checks comments
		if (s[i] == '<' && s[i + 1] == '!') {
			i = i + 2;
			if (s[i] == '-' && s[i + 1] == '-') {
				i = i + 2;
			}
			else {
				flag = false;
				break;
			}
			while (i != s.length()) {
				if (s[i]=='-' && s[i+1]=='-' && s[i + 2] == '>') {
					flag = true;
					break;
				}
				else
					flag = false;
				i++;
			}
			break;
		}
		i++;
	}

	if (flag == false)
		return flag;

	i = 0;
	while (i != s.length()) {                               //checks opening tags and push them in stack
		if ((s[i] == '<') && ((s[i + 1] != '/') && s[i + 1] != '!')) {
			i++;
			while ((s[i] != '>') && (s[i] != ' '))
			{
				this->push(s[i]);
				i++;
			}
		}
		i++;
	}
	i = 0;
	while (i != s.length())                           //checks closing tags if any and checks their balance
	{
		if ((s[i] == '<') && (s[i + 1] == '/')) {
			i = i + 2;
			while (s[i] != '>')
			{
				xmlOne.push(s[i]);
				i++;
			}
			int ptr = xmlOne.top;
			int qtr = this->top;
			while (ptr != -1) {
				if (xmlOne.list[ptr] == this->list[qtr]) {
					flag = true;
					ptr--;
					qtr--;
				}
				else {
					flag = false;
					return flag;
				}
			}
			ptr = xmlOne.top;
			qtr = this->top;
			while (ptr != -1) {
				this->pop(element);
				ptr--;
			}
		}
		i++;
	}
	i = 0;
	while (i != s.length()) {                          //checks attributes if " comes

		if (s[i] == '"') {
			flag = this->attributechecker(s);
			break;
		}

		i++;
	}
	return flag;
}
template<typename T>
bool xml<T>::attributechecker(string s) {
	bool check = false;
	char e;
	stack<char> Stackattr(2);
	int i = 0;
	while (i < s.length())                  //checks if inverted commas are balanced
	{
		if (s[i] == '"') {
			Stackattr.push(s[i]);
			i++;
			while (i < s.length()) {
				if (s[i] == '"') {
					Stackattr.pop(e);
					check = true;
					return check;
				}
				i++;
			}
		}

		i++;

	}
	return check;
}



int main()
{
	xml<char>Stack1(500);
	ifstream file;
	file.open("xml.txt");
	string inputString;
	if (file.is_open()) {                       //file handling
		bool flag = false;
		int line = 0;
		while (!file.eof()) {
			line++;
			getline(file, inputString, '\n');
			if (line == 1) {                               //calls prolog checker at line 1 only
				flag = Stack1.checkprolog(inputString);
				if (!flag)
				{
					cout << "Incorrect prolog at line number 1" << endl;
				}
			}
			else {
				bool check;
				check = Stack1.completechecker(inputString);
				if (check == true)
					cout << "line " << line << "correct" << endl;               //checks line by line file
				else
					cout << "incorrect syntax at line " << line << endl;

			}
		}

		if (Stack1.top != -1)
			cout << "Incorrect. All tags are not closed\n";         //checks if stack is empty and no tags are left to be closed
	}

	else {
		cout << "File does not exist!" << endl;
	}

	system("pause");
	return 0;
}