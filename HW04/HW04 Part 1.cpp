#include <iostream>
using namespace std;
class node {
public:
	int value;
	node * next;
	node() { next = nullptr; }
	node(int i) { value = i; next = nullptr; }
};
class linked_list {
public:
	int num_of_nodes;
	node * head;
	linked_list() { num_of_nodes = 0; head = nullptr; }
	void make_linked_list(int n);
	void print_linked_list();
	void reverse();
	int & operator[](int i);  //Assume i is a valid int; you don't need to check.

	bool operator==(linked_list L); //two linked lists are equal if their num_of_nodes differ by at most 2, and with at least 5 nodes of equal values and at the same positions.
									//Assume that the lists involved contain more than 5 nodes. You don't need to check.

	linked_list combine(linked_list L);//Create a new linked list whose front part is equal to a copy of the current linked list, while the remaining part is a reverse copy of L
									   //For example, if the values of L1 is 1,2,3,4,5 and the values of L2 is 10,20,30,40,50,60
									   //L3 = L1.combine(L2) will have values 1,2,3,4,5,60,50,40,30,20.10
};

void linked_list::make_linked_list(int n) {
	node *p;
	for (int i = n - 1; i >= 0; i--) {
		p = new node(i);
		p->next = head;
		head = p;
		num_of_nodes++;
	}
}
void linked_list::print_linked_list() {
	cout << endl;
	node *p = head;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->next;
	}
}
int & linked_list::operator[](int i) {
	node * p1 = head;
	while (i > 0) {
		p1 = p1->next;
		i--;
	}
	return p1->value;
}
bool linked_list::operator==(linked_list L) {
	if (abs(num_of_nodes - L.num_of_nodes) < 2) {
		node *p1 = head, *p2 = L.head;
		int counter = 0;
		while (p1 != nullptr) {
			if (p1->value == p2->value)
				counter++;
			p1 = p1->next;
			p2 = p2->next;
		}
		if (counter > 5)
			return true;
	}
	else
		return false;
}
void linked_list::reverse() {
	node * p1 = head, *p2 = head, *p3 = head;
	p2 = p1->next;
	while (p2 != nullptr) {
		p3 = p2->next;
		p2->next = p1;
		if (p1 == head) p1->next = nullptr;
		p1 = p2;
		p2 = p3;
	}
	head = p1;
}
linked_list linked_list::combine(linked_list L) {
	linked_list L3;
	node *p1 = head, *p3 = NULL;
	L3.make_linked_list(num_of_nodes + L.num_of_nodes); //create a new linked list with temporary values
	p3 = L3.head;
	//assign
	while (p1->next != nullptr) {
		p3->value = p1->value;
		p3 = p3->next;
		p1 = p1->next;
	}
	p3 = p3->next;
	//reverse 
	L.reverse();
	//assign
	node *p2 = L.head;
	for (int x = 0; x < L.num_of_nodes; x++) {
		p3->value = p2->value;
		p3 = p3->next;
		p2 = p2->next;
	}
	return L3;
}
int main() {
	linked_list L1;
	linked_list L2;
	L1.make_linked_list(20);
	L2.make_linked_list(10);
	L1.print_linked_list();
	L2.print_linked_list();

	if (L1 == L2) {
		cout << "\ncorrect";
	}
	linked_list L3;
	L3 = L1.combine(L2);
	L3.print_linked_list();
	getchar();
	getchar();
	return 0;

}