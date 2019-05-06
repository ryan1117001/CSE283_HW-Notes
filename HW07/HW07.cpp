#include <iostream>
#include <string>
using namespace std;


class node {
public:
	int value;
	int position;
	node *next;
	node() { next = nullptr; };
	node(int v, int p) { value = v; position = p; next = nullptr; }
};

class myvector {
public:
	node *head;
	int length; //vector length
	int num_elements;//number of nonzero elements

	myvector operator+(myvector &v);
	myvector operator=(myvector &v);
	myvector operator=(myvector &&v);
	int operator*(myvector &v);
	void input_vector();
	void print_vector();
	void add_ele(int i, int j); //i and j are for value and position of an element
	myvector() {
		head = nullptr;
		num_elements = 0;
	}
	myvector(const myvector &v) { //copy constructor
		num_elements = v.num_elements;
		length = v.length;
		node *p1, *p2;
		for (int i = 0; i < num_elements; i++) {
			p2 = new node;
			p2->next = head;
			head = p2;
		}
		p1 = v.head;
		p2 = head;
		for (int i = 0; i < num_elements; i++) {
			p2->value = p1->value;
			p2->position = p1->position;
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	myvector(myvector &&v) { //move constructor
		head = v.head;
		length = v.length;
		num_elements = v.length;
		v.head = nullptr;
	}
	~myvector() { //destructor
		node *p1 = head, *p2 = head; 
		for (size_t x = 0; x < num_elements; x++) {
			// If you want to delete p1, you should set p2 = p1->next first,
			// and then delete p1.
			p2 = p1->next;
			delete p1;
			p1 = p2;
		}
	}
	void sort();//sort the vector in order of position
};
void myvector::add_ele(int i, int j) { //i is value, j is position
	node *p1;
	p1 = new node(i, j);
	p1->next = head;
	head = p1;
}

void myvector::input_vector() {
	int i;
	int v, p;
	cout << "\nEnter vector length and number of nonzero elements, separated by space\n";
	cin >> length >> num_elements;
	cout << "Enter all elements: each element is a value and position, seperated by space\n";
	for (i = 0; i < num_elements; i++) {
		cin >> v >> p;
		add_ele(v, p);
	}
	sort();
}

void myvector::print_vector() {
	node *p1;
	p1 = head;
	cout << endl << "value postion" << "\n";
	while (p1 != nullptr) {
		cout << p1->value << " " << p1->position << "   ";
		p1 = p1->next;
	}
	cout << endl;
}
void myvector::sort() {
	node *start = head, *curr = NULL, *trail = NULL, *temp = NULL;
	for (int i = 0; i < num_elements; i++) {
		curr = trail = head; //initial setup

		while (curr->next != NULL) {
			if (curr->position > curr->next->position) { //comparison to sort from least to greatest
				temp = curr->next; //beginning of switch
				curr->next = curr->next->next;
				temp->next = curr;
				if (curr == head)
					head = trail = temp;
				else
					trail->next = temp;
				curr = temp;
			}
			trail = curr;
			curr = curr->next;
		}
	}
}
myvector myvector::operator+(myvector &v2) {
	int new_length, temp;
	myvector v3;
	node *p1 = this->head, *p2 = v2.head;
	if (length > v2.length)
		new_length = length;
	else
		new_length = v2.length;
	v3.length = new_length;
	for (size_t x = 1; x <= v3.length; x++) {
		if (p1 == nullptr) {
			while (p2 != nullptr) {
				v3.add_ele(p2->value, p2->position);
				p2 = p2->next;
				v3.num_elements++;
			}
			v3.sort();
			return v3;
		}
		else if (p2 == nullptr) {
			while (p1 != nullptr) {
				v3.add_ele(p1->value, p1->position);
				p1 = p1->next;
				v3.num_elements++;
			}
			v3.sort();
			return v3;
		}
		if (p1->position == x && p2->position == x) {
			temp = p1->value + p2->value;
			v3.add_ele(temp, x);
			p1 = p1->next;
			p2 = p2->next;
			v3.num_elements++;
		}
		else if (p1->position != x && p2->position == x) {
			v3.add_ele(p2->value, x);
			p2 = p2->next;
			v3.num_elements++;
		}
		else if (p2->position != x && p1->position == x) {
			v3.add_ele(p1->value, x);
			p1 = p1->next;
			v3.num_elements++;
		}
	}
}
int myvector::operator*(myvector &v2) {
	int dot_p = 0, new_length = 0, temp = 0;
	node *p1 = this->head, *p2 = v2.head;
	if (length > v2.length)
		new_length = length;
	else
		new_length = v2.length;
	for (size_t x = 1; x <= new_length; x++) {
		if (p1->position == x && p2->position == x) {
			temp = 0;
			temp = p1->value * p2->value;
			dot_p += temp;

		}
		if (p1->position == x) p1 = p1->next;
		if (p2->position == x) p2 = p2->next;
		if (p1 == nullptr || p2 == nullptr) {
			return dot_p;
		}
	}
}
myvector myvector::operator=(myvector &v) {
	length = v.length;
	num_elements = v.num_elements;
	node *p1, *p2;
	for (int i = 0; i < num_elements; i++) {
		p2 = new node;
		p2->next = head;
		head = p2;
	}
	p1 = v.head;
	p2 = head;
	for (int i = 0; i < num_elements; i++) {
		p2->value = p1->value;
		p2->position = p1->position;
		p1 = p1->next;
		p2 = p2->next;
	}
	return *this;
}
myvector myvector::operator=(myvector &&v) {
	head = v.head;
	length = v.length;
	num_elements = v.num_elements;
	v.head = nullptr;
	return *this;
}
int main() {

	myvector v1, v2, v3;
	v1.input_vector();
	v1.print_vector();
	/*
	v2.input_vector();
	v2.print_vector();

	cout << "\ninner product = " << v1*v2 << endl;

	v3 = v1 + v2;
	v3.print_vector();*/

	myvector v4, v5(v1);
	v4 = v1;
	v4.sort();
	v4.print_vector();

	v5.sort();
	v5.print_vector();

	myvector v6(move(v5));
	v6.sort();
	v6.print_vector();
	
	myvector v7;
	v7 = move(v6);

	getchar();
	getchar();
	return 0;

}
/*
Enter vector length and number of nonzero elements, separated by space
10 4
Enter all elements : each element is a value and position, seperated by space
5 7 1 3 4 5 2 1

value postion
2 1   1 3   4 5   5 7

Enter vector length and number of nonzero elements, separated by space
10 3
Enter all elements : each element is a value and position, seperated by space
2 5 3 1 1 2

value postion
3 1   1 2   2 5

Inner Product = 14

value postion
5 1   1 2   1 3   6 5   5 7
*/
