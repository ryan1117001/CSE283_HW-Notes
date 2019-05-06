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
	void remove_one(int i); //remove the first match
	void reverse();
	void swap_min();
	void make_random_linked_list(int k);
	void sort();
	void remove_all(int i);
	void new_remove_all(int i);


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

void linked_list::remove_one(int i) {
	node * p = head, *p1 = head;
	if (num_of_nodes == 0) { cout << "Error! Linked list empty" << endl; return; }
	if (head->value == i) {
		head = head->next;
		delete p;
		num_of_nodes--;
		return;
	}
	while (p != nullptr) {
		if (p->value == i) {
			p1->next = p->next;
			delete p;
			num_of_nodes--;
			return;
		}
		p1 = p;
		p = p->next;
	}
}
void linked_list::reverse() {
	node * p1 = head, *p2 = head, *p3 = head;
	if (num_of_nodes < 2) return;
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

void linked_list::swap_min() {
	node * p = head, *p_min;
	if (num_of_nodes == 0) {
		cout << "Error! Linked list is empty" << endl;
		return;
	}
	int min = head->value;
	p_min = head;
	while (p != nullptr) {
		if (p->value < min) {
			min = p->value;
			p_min = p;
		}
		p = p->next;
	}
	p_min->value = head->value;
	head->value = min;
}

void linked_list::make_random_linked_list(int k) {

	node *p;
	for (int i = 0; i < k; i++) {
		p = new node(rand() % 100);//0-99 random number
		p->next = head;
		head = p;
		num_of_nodes++;
	}

}
void linked_list::sort() {
	node *p1 = head, *p2;
	int min;
	node * p_min ;

	while (p1 != nullptr) {
		min = p1->value;
		p_min = p1;;
		p2 = p1;
		while (p2 != nullptr) {
			if (p2->value < min) {
				min = p2->value;
				p_min = p2;
			}
			p2 = p2->next;
		}
		p_min->value = p1->value;
		p1->value = min;
		p1 = p1->next;
	}
}


void linked_list::new_remove_all(int i) {
	if (num_of_nodes == 0) {
		cout << "Error!  Linked list is empty!" << endl;
		return;
	}
	int match_count = 0;
	node *p = head;
	while (p != nullptr) {
		if (p->value == i) match_count++;
		p = p->next;
	}
	while (match_count > 0) {
		remove_one(i);
		match_count--;
	}
}

void linked_list::remove_all(int i) {
	node * p = head, *p1 = head;
	if (num_of_nodes == 0) { cout << "Error! Linked list empty" << endl; return; }
	while (p != nullptr) {
		if (p == head && p->value == i) {
			head = head->next;
			delete p;
			p = head;
			num_of_nodes--;
		}
		else if (p->value == i) {
				p1->next = p->next;
				delete p;
				p = p1->next;
				num_of_nodes--;
			}
		else  {
			p1 = p;
			p = p->next;
		}
	}
}


int main() {
	linked_list L1;
	L1.make_linked_list(20);
	L1.print_linked_list();
	L1.remove_one(11);
	L1.print_linked_list();
	L1.reverse();
	L1.print_linked_list();
	L1.sort();
	L1.print_linked_list();
	linked_list L2;
	L2.make_random_linked_list(30);
	L2.print_linked_list();
	L2.swap_min();
	L2.print_linked_list();
	L2.sort();
	L2.print_linked_list();
	L2.remove_all(95);
	L2.print_linked_list();
	L2.remove_all(91);
	L2.print_linked_list();
	getchar();
	getchar();
	return 0;

}