#include <iostream>
#include<cassert>
#include<fstream>
#include<string>
using namespace std;
template <class v>
struct hashitem {                                                 //making hash item struct
	int key;
	v value;
	short status;

	hashitem() :value() {
		status = 0;
		key = -999;
	}
};
struct student {                                                  //making student struct to pass as value v in hash
	string name;
	float cgpa;
	int ID;
	student() {
		name = "";
		ID = 0;
		cgpa = 0.0;
	}
	student(string n, float c, int i) {
		ID = i;
		name = n;
		cgpa = c;
	}
	friend ostream& operator<<(ostream& out, student& s) {
		cout << s.name << " " << s.ID << " " << s.cgpa;
		return out;
	}
	void operator=(const student& s) {
		this->name = s.name;
		this->ID = s.ID;
		this->cgpa = s.cgpa;
	}
};
template<class v>
class hashmap {                                                               //hashmap class
public:
	hashitem<v>* array;
	int capacity;
	int currentelements;
	hashmap() {
		capacity = 10;
		currentelements = 0;
		array = new hashitem<v>[10];

	}
	hashmap(int cap) {
		assert(cap > 1);
		capacity = cap;
		array = new hashitem<v>[cap];
		currentelements = 0;
	}
	virtual int getnextindex(int key, int i) {                                 //finds next index by linear probing
		int index = (key + i) % capacity;
		if (index > capacity - 1) {
			return (index - capacity - 1);
		}
		return index;
	}
	int findindex(int key) {                                                 //helper function to find next index. Checks if next found is empty or not
		int index = 0;
		index = key % capacity;           //finds index
		int i = 0;
		int ret = 0;
		if (array[index].status != 0 && array[index].status != 1) {             //if index not empty
			do {
				i++;
				ret = getnextindex(key, i);                                              //call getindex again
			} while (array[ret].status != 0 && array[ret].status != 1);
			index = ret;
		}
		return index;                                             //return final empty index
	}
	void insert(int key, v value) {
		int index = 0;
		index = findindex(key);
		array[index].status = 2;                                   //inserts data at index found
		array[index].value = value;
		array[index].key = key;
		currentelements++;

		float cap = capacity;
		float elements = currentelements;
		float loadfactor = elements / cap;

		if (loadfactor >= 0.75) {                                 //if LF>=0.75, double hash array capacity
			doublecapacity();
		}
	}
	void print() {
		for (int i = 0;i < capacity;i++) {
			if (array[i].status == 0 || array[i].status == 1) {                       //for empty indexes
				cout << "-" << endl;
			}
			else {
				cout << array[i].key << " " << array[i].value << endl;               //for filled indexes
			}
		}
	}
	void deleteindex(int key) {
		int index = key % capacity;
		array[index].status = 1;
	}
	bool deletekey(int key1) {
		int index = 0;
		index = key1 % capacity;
		int i = 0;
		int ret = 0;
		if (array[index].key == key1) {
			array[index].status = 1;
			return true;
		}
		if (array[index].key != key1) {                           //if index does not have desired key, search next indexes
			while (array[index].key != key1) {
				i++;
				ret = getnextindex(key1, i);
				index = ret;
			}
			array[index].status = 1;                            //if key found, set status to 1 i.e. deleted
			return true;
		}
		return false;                            //return false if key not present
	}

	bool update(int oldkey, int newkey, v newvalue) {
		bool flag = updatehelper(oldkey, newkey, newvalue);
		if (flag) {
			insert(newkey, newvalue);
			deleteindex(oldkey);
		}
		return flag;
	}
	bool updatehelper(int oldkey, int newkey, v newvalue) {

		int index = 0;
		index = oldkey % capacity;
		int i = 0;
		int ret = 0;
		v* temp();
		if (array[index].key == oldkey) {                           //if index is found, return it
			array[index].key = newkey;
			array[index].value = newvalue;
			return true;
		}
		int countofiteration = 0;
		if (array[index].key != oldkey) {                                                     //if not found, iterate and search until the entire array is passed
			while (array[index].key != oldkey && countofiteration < capacity) {
				i++;
				ret = getnextindex(oldkey, i);                       //iterate linearly
				if (array[ret].status == 2) {
					index = ret;
					countofiteration++;
				}
				else
					continue;
			}
			if (oldkey == array[index].key) {                            //if found, return contents of index
				array[index].key = newkey;
				array[index].value = newvalue;
				return true;
			}
		}
		return false;                                  //item not found, return false

	}

	void doublecapacity() {
		capacity = capacity * 2;
		int index, ret, j = 0;
		hashitem<v>* q = new hashitem<v>[capacity];                           //makes a new array of hash items
		for (int i = 0;i < capacity / 2;i++) {
			if (array[i].status == 2) {                                  //only copy those elements which are filled and not empty
				int temp = array[i].key;
				index = array[i].key % capacity;
				if (q[index].status != 0 && q[index].status != 1) {
					do {
						j++;
						ret = getnextindex(array[i].key, j);
					} while (q[ret].status != 0 && q[ret].status != 1);
					index = ret;
				}
				q[index].status = 2;                                         //rehash
				q[index].value = array[i].value;
				q[index].key = array[i].key;
			}
		}
		delete[] array;                                           //delete old array and point to new bigger array
		array = q;
	}

	v* get(int key1) {                                                           //SEARCH FUNCTION
		int index = 0;
		index = key1 % capacity;
		int i = 0;
		int ret = 0;
		v* temp;
		if (array[index].key == key1 && array[index].status == 2) {                          //if found
			temp = &array[index].value;
			return temp;
		}
		int countofiteration = 0;
		if (array[index].key != key1) {
			while (array[index].key != key1 && countofiteration < capacity) {             //if not found, iterate entire array
				i++;
				ret = getnextindex(key1, i);
				if (array[ret].status == 2) {
					index = ret;
					countofiteration++;
				}
				else
					continue;
			}
			if (key1 == array[index].key && array[index].status == 2) {
				temp = &array[index].value;
				return temp;
			}
		}
		return NULL;                               //if not present, return null
	}

	~hashmap<v>() {                       //destructor
		delete[] array;
	}
};
template<class v>
class Qhashmap :public hashmap<v> {
public:
	Qhashmap<v>() :hashmap<v>() {}
	int getnextindex(int key, int i) {                                        //quadratic probing
		int index = (key + (i * i)) % this->capacity;
		if (index > this->capacity - 1) {
			return (index - this->capacity - 1);
		}
		return index;
	}
	/*~Qhashmap<v>() {
		delete array;
	}*/
};
template<class v>
class Dhashmap :public hashmap<v> {
public:
	Dhashmap<v>() :hashmap<v>() {}
	int getnextindex(int key, int i) {                                                     //double hashing method
		int index1 = key % this->capacity;
		int index2 = 11 - (key % 11);
		int index = (index1 + i * index2) % this->capacity;
		if (index > this->capacity - 1) {
			return (index - this->capacity - 1);
		}
		return index;
	}
	/*~Dhashmap<v>() {
		delete array;
	}*/
};
void populatehash(string filename, hashmap<string>* hash) {

	float cgpa; string N; int ID;
	ifstream fin;
	fin.open(filename);                                                       //reads file
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> ID;
			fin >> N;
			fin >> cgpa;
			hash->insert(ID, N);                                              //insert items one by one
		}
	}

}
int main() {

	cout << "***HASH MAP***" << endl;

	hashmap<string>* map;
	map = new hashmap<string>;
	populatehash("student.txt", map);
	map->print();
	cout << endl << "finding value of key 9 " << *map->get(9) << endl;
	map->deletekey(9);
	assert(map->get(9) == NULL);
	delete map;


	cout << endl << "***Q HASH MAP***" << endl;

	map = new Qhashmap<string>;
	populatehash("student.txt", map);
	map->print();
	cout << endl << "finding value of key 98 " << *map->get(98) << endl;
	map->deletekey(98);
	assert(map->get(98) == NULL);
	delete map;

	cout << endl << "***D HASH MAP***" << endl;

	map = new Dhashmap<string>;
	populatehash("student.txt", map);
	map->print();
	cout << endl << "finding value of key 101 " << *map->get(101) << endl;
	map->deletekey(101);
	assert(map->get(101) == NULL);
	delete map;

	system("pause");
	return 0;
}