//HW3 Sparse Matrix Operations
//Due: 11:59 Friday, Oct. 1

//You need to complete the implementation for member funcitons add_element, operator+, and operator*.
//Feel free to modify my code to fit your need.
//You need to try sufficient test cases in main function.

//The following are the three matrices for you to try.
//10 0 0 25 0 2 50 1 1 80 2 1 100 2 2             For m1:  3 rows, 3 columns, 5 elements

//-1 0 2 -1 0 3 1 1 1 2 2 0 1 2 1 1 2 3           For m2: 3 rows, 4 columns, 6 elements

//-10 0 0 20 0 1 20 1 0 30 2 1			  For m4: 3 rows, 3 columns, 4 elements


//Partial code written by C-Y (Roger) Chen
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class node {
public:
	int value;
	int r_pos;
	int c_pos;
	node *r_next;
	node *c_next;
	node() { r_next = NULL; c_next = NULL; }
	node(int v, int r, int c) { value = v; r_pos = r; c_pos = c; r_next = NULL; c_next = NULL; }
};

class my_matrix {
public:
	string m_name;
	int num_rows;
	int num_cols;
	int num_elements;
	vector<node *> r_vec;
	vector<node *> c_vec;
	my_matrix() {};
	my_matrix operator+(my_matrix m);
	my_matrix operator*(my_matrix m);
	void matrix_input();
	void matrix_print_r();
	void matrix_print_c();
	void add_element(int v, int r, int c);
};

void my_matrix::add_element(int v, int r, int c) {
	node *p1 = r_vec[r], *p2 = c_vec[c], *p3, *p4, *p5;
	p3 = new node(v, r, c);
	int added;

	//first, add it to the proper low linked list
	if (p1 == nullptr) r_vec[r] = p3;
	else if (c < p1->c_pos) { p3->r_next = p1; r_vec[r] = p3; }
	else {
		p4 = p1;
		p1 = p1->r_next;
		added = 0;
		while (added == 0) {
			if (p1 == nullptr) {
				p4->r_next = p3;
				added = 1;
			}
			else if (c < p1->c_pos) { p4->r_next = p3; p3->r_next = p1; added = 1; }

			else { p4 = p1; p1 = p1->r_next; }

		}
	}
	//Next, you need to add it to the proper column linked list in a way similar to the above code
	if (p2 == nullptr) c_vec[c] = p3;
	else if (r < p2->r_pos) { p3->c_next = p2; c_vec[c] = p3; }
	else {
		p5 = p2;
		p2 = p2->c_next;
		added = 0;
		while (added == 0) {
			if (p2 == nullptr) {
				p5->c_next = p3;
				added = 1;
			}
			else if (r < p2->r_pos) { p5->c_next = p3; p3->c_next = p2; added = 1; }
			else { p5 = p2; p2 = p2->c_next; }
		}
	}
}


void my_matrix::matrix_input() {
	int v, r, c;
	string s;
	cout << "Enter Matrix name, number of rows, number of columns, separated by space: \n";
	cin >> m_name >> num_rows >> num_cols;
	r_vec.assign(num_rows, NULL);
	c_vec.assign(num_cols, NULL);
	cout << "\nEnter number of elements:\n";
	cin >> num_elements;
	cout << "\nEnter elements: value, row, col, separated by space:\n";
	for (int i = 0; i < num_elements; i++) { cin >> v >> r >> c; add_element(v, r, c); }
}


void my_matrix::matrix_print_r() {

	int i;
	node *p1;
	for (i = 0; i < num_rows; i++) {
		p1 = r_vec[i];
		while (p1 != NULL) { cout << "( " << p1->value << " , " << p1->r_pos << " , " << p1->c_pos << " )"; p1 = p1->r_next; }
	}


}

void my_matrix::matrix_print_c() {

	int i;
	node *p1;
	for (i = 0; i < num_cols; i++) {
		p1 = c_vec[i];
		while (p1 != NULL) { cout << "( " << p1->value << " , " << p1->r_pos << " , " << p1->c_pos << " )"; p1 = p1->c_next; }
	}


}

my_matrix my_matrix::operator*(my_matrix m) {
	int dot_p = 0;
	my_matrix m1 = *this, m2 = m, m3;
	node *n1, *n2;
	
	m3.m_name = "Multiply two matrices";
	m3.num_rows = m1.num_rows;
	m3.num_cols = m2.num_cols;
	m3.r_vec.assign(num_rows, NULL);
	m3.c_vec.assign(num_cols, NULL);
	m3.num_elements = 0;
	
	int r, c, b, b2;
	n1 = m1.r_vec[0];
	n2 = m2.c_vec[0];

	if (m1.num_cols < m2.num_rows)
		b2 = m1.num_cols;
	else
		b2 = m2.num_rows;
	
	for (c = 0; c < m3.num_cols; c++) {
		n2 = m2.c_vec[c];
		dot_p = 0;
		for (r = 0; r < m3.num_rows; r++) {
			n1 = m1.r_vec[r];
			for (b = 0; b < b2; b++) {
				if (n1->c_pos == n2->r_pos && n1->c_pos == b && n2->r_pos == b) { dot_p += (n1->value * n2->value); }
				if (n1->c_pos == b) n1 = n1->r_next;
				if (n2->r_pos == b) n2 = n2->c_next;
			}
			if (dot_p != 0) m3.add_element(dot_p, r, c);
		}
	}
	return m3;
}

my_matrix my_matrix::operator+(my_matrix m) {
	my_matrix m3;
	
	node *n1 = c_vec[0], *n2 = m.c_vec[0];
	
	if (num_cols > m.num_cols) m3.num_cols = num_cols;
	else m3.num_cols = m.num_cols;

	if (num_rows > m.num_rows) m3.num_rows = num_rows;
	else m3.num_rows = m.num_rows;

	m3.m_name = "Add two matrices";
	m3.r_vec.assign(num_rows, NULL);
	m3.c_vec.assign(num_cols, NULL);
	m3.num_elements = 0;

	for (size_t x = 0; x < m3.num_cols; x++) {
		n1 = c_vec[0];
		n2 = m.c_vec[0];
		for (size_t y = 0; y < m3.num_rows; y++) {
			if (n1 == NULL) {
				while (n2 != NULL) {
					m3.add_element(n2->value, n2->r_pos, x);
					n2 = n2->c_next;
					m3.num_elements++;
				}
				return m3;
			}
			else if (n2 == NULL) {
				while (n1 == NULL) {
					m3.add_element(n1->value, n1->r_pos, x);
					n1 = n1->c_next;
					m3.num_elements++;
				}
				return m3;
			}
			if (n1->r_pos == y && n2->r_pos == y) {
				m3.add_element((n1->value + n2->value), y, x);
				n1 = n1->c_next;
				n2 = n2->c_next;
				m3.num_elements++;
			}
			else if (n1->r_pos != y && n2->r_pos == y) {
				m3.add_element(n2->value, y, x);
				n2 = n2->c_next;
				m3.num_elements++;
			}
			else if (n2->r_pos != y && n1->r_pos == y) {
				m3.add_element(n1->value, y, x);
				n1 = n1->c_next;
				m3.num_elements++;
			}
		}
	}
}
int main() {

	my_matrix m1, m2, m3, m4, m5;
	m1.matrix_input();
	m1.matrix_print_r(); //row-oriented printing
	cout << "\n";
	m1.matrix_print_c(); //column-oriented printing
	cout << "\n";

	m2.matrix_input();
	m2.matrix_print_r();
	cout << "\n";
	m2.matrix_print_c();

	m3 = m1*m2;
	cout << "\n";
	m3.matrix_print_r();
	cout << "\n";
	m3.matrix_print_c();
	cout << "\n";
	
	m4.matrix_input();
	m4.matrix_print_r();
	cout << "\n";
	m4.matrix_print_c();
	
	m5 = m1 + m4;
	cout << "\n";
	m5.matrix_print_r();
	cout << "\n";
	m5.matrix_print_c();

	getchar();
	getchar();
	return 0;
}


//The following is a screen display for the input data given at the beginning of this document.
/*

Enter Matrix name, number of rows, number of columns, separated by space:
MA 3 3

Enter number of elements:
5

Enter elements: value, row, col, separated by space:
10 1 1 25 1 3 50 2 2 80 3 2 100 3 3
( 10 , 1 , 1 )( 25 , 1 , 3 )( 50 , 2 , 2 )( 80 , 3 , 2 )( 100 , 3 , 3 )
( 10 , 1 , 1 )( 50 , 2 , 2 )( 80 , 3 , 2 )( 25 , 1 , 3 )( 100 , 3 , 3 )
Enter Matrix name, number of rows, number of columns, separated by space:
MB 3 4

Enter number of elements:
6

Enter elements: value, row, col, separated by space:
-1 1 3 -1 1 4 1 2 2 2 3 1 1 3 2 1 3 4
( -1 , 1 , 3 )( -1 , 1 , 4 )( 1 , 2 , 2 )( 2 , 3 , 1 )( 1 , 3 , 2 )( 1 , 3 , 4 )
( 2 , 3 , 1 )( 1 , 2 , 2 )( 1 , 3 , 2 )( -1 , 1 , 3 )( -1 , 1 , 4 )( 1 , 3 , 4 )
( 50 , 1 , 1 )( 25 , 1 , 2 )( -10 , 1 , 3 )( 15 , 1 , 4 )( 50 , 2 , 2 )( 200 , 3 , 1 )( 180 , 3 , 2 )( 100 , 3 , 4 )
( 50 , 1 , 1 )( 200 , 3 , 1 )( 25 , 1 , 2 )( 50 , 2 , 2 )( 180 , 3 , 2 )( -10 , 1 , 3 )( 15 , 1 , 4 )( 100 , 3 , 4 )
Enter Matrix name, number of rows, number of columns, separated by space:
MC 3 3

Enter number of elements:
4

Enter elements: value, row, col, separated by space:
-10 1 1 20 1 2 20 2 1 30 3 2
( -10 , 1 , 1 )( 20 , 1 , 2 )( 20 , 2 , 1 )( 30 , 3 , 2 )
( -10 , 1 , 1 )( 20 , 2 , 1 )( 20 , 1 , 2 )( 30 , 3 , 2 )
( 20 , 1 , 2 )( 25 , 1 , 3 )( 20 , 2 , 1 )( 50 , 2 , 2 )( 110 , 3 , 2 )( 100 , 3 , 3 )
( 20 , 2 , 1 )( 20 , 1 , 2 )( 50 , 2 , 2 )( 110 , 3 , 2 )( 25 , 1 , 3 )( 100 , 3 , 3 )

*/


