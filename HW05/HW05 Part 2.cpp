#include <iostream>
#include <string>
#include <list>
using namespace std;


class node {
public:
	int value;
	int position;
	node() {  };
	node(int v, int p) { value = v; position = p; }
	bool operator<(node &n) { return (position < n.position); }
	bool operator==(node &n) { return (position == n.position); }
};

class mylist {
public:
	list<node> *head;
	int length; //list length
	int num_elements;//number of nonzero elements

	mylist operator+(mylist &v);
	int operator*(mylist &v);
	void input_list();//
	void print_list();//
	void add_ele(int i, int j); //i and j are for value and position of an element
	mylist() {
		list<node> *p = new list<node>;
		head = p;
		num_elements = 0;
	}

};
void mylist::add_ele(int i, int j) {
	head->push_back(node(i, j));
}

void mylist::input_list() {
	int i;
	int v, p;
	cout << "\nEnter list length and number of nonzero elements, separated by space\n";
	cin >> length >> num_elements;
	cout << "Enter all elements: each element is a value and position, seperated by space\n";
	for (i = 0; i < num_elements; i++) {
		cin >> v >> p;
		add_ele(v, p);
	}
	head->sort();
}

void mylist::print_list() {

	cout << endl;
	list<node>::iterator it = head->begin();
	for (size_t i = 0; i < head->size(); i++) {
		cout << it->value << " " << it->position << "  ";
		it++;
	}
	cout << endl;
}

mylist mylist::operator+(mylist &l2) {
	mylist l3;
	int new_length, temp;
	list<node>::iterator it1 = head->begin(), it2 = l2.head->begin();
	if (length > l2.length)
		new_length = length;
	else 
		new_length = l2.length;
	l3.length = new_length;
	for (size_t x = 1; x <= l3.length; x++) {
		if (it1 == head->end()) {
			while (it2 != l2.head->end()) {
				l3.add_ele(it2->value, it2->position);
				it2++;
				l3.num_elements++;
			}
			l3.head->sort();
			return l3;
		}
		else if (it2 == l2.head->end()) {
			while (it1 != head->end()) {
				l3.add_ele(it1->value, it1->position);
				it1++;
				l3.num_elements++;
			}
			l3.head->sort();
			return l3;
		}
		if (it1->position == x && it2->position == x) {
			temp = it1->value + it2->value;
			l3.add_ele(temp, x);
			it1++;
			it2++;
			l3.num_elements++;
		}
		else if (it1->position != x && it2->position == x) {
			l3.add_ele(it2->value, x);
			it2++;
			l3.num_elements++;
		}
		else if (it2->position != x && it1->position == x) {
			l3.add_ele(it1->value, x);
			it1++;
			l3.num_elements++;
		}
	}
}

int mylist::operator*(mylist &l2) {
	int dot_p = 0, new_length = 0, temp = 0;
	list<node>::iterator it1 = head->begin(), it2 = l2.head->begin();
	if (length > l2.length)
		new_length = length;
	else
		new_length = l2.length;
	for (size_t x = 1; x <= new_length; x++) {
		if (it1->position == x && it2->position == x) {
			temp = 0;
			temp = it1->value * it2->value;
			dot_p += temp;
		}
		if (it1->position == x) it1++;
		if (it2->position == x) it2++;
		if (it1 == head->end() || it2 == l2.head->end())
			return dot_p;
	}
}






int main() {

	mylist v1, v2, v3;
	v1.input_list();
	v1.print_list();
	v2.input_list();
	v2.print_list();
	cout << "\nInner Product = " << v1*v2;

	v3 = v1 + v2;
	v3.print_list();

	getchar();
	getchar();
	return 0;

}

//Enter list length and number of nonzero elements, separated by space
//10 4
//Enter all elements : each element is a value and position, seperated by space
//5 7 1 3 4 5 2 1
//
//2 1  1 3  4 5  5 7
//
//Enter list length and number of nonzero elements, separated by space
//10 3
//Enter all elements : each element is a value and position, seperated by space
//2 5 3 1 1 2
//
//3 1  1 2  2 5
//
//Inner Product = 14
//5 1  1 2  1 3  6 5  5 7
