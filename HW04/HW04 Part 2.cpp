#include <iostream>
#include <vector>
#include <list>

using namespace std;

void print_DB1(vector<list<int>> &DB1);
void print_DB2(vector<list<int> *> &DB2);
void print_DB3(list<vector<int>> &DB3);
void DB1_to_DB2(vector<list<int> > &DB1, vector<list<int> *> & DB2); //copy data from DB1 to DB2
void DB1_to_DB3(vector<list<int>> &DB1, list<vector<int>> & DB3);//copy data from DB1 to DB3 (This part is a bonus question, not required.)

int main() {

	list<int> L1 = { 1, 3, 5 };
	list<int> L2 = { 100, 200, 3000,400 };
	list<int> L3 = { 7,8,9,10,11 };
	vector<list<int>> DB1 = { L1, L2, L3 };
	vector<list<int> *> DB2;
	list<vector<int>> DB3;

	DB1_to_DB2(DB1, DB2);
	DB1_to_DB3(DB1, DB3);
	print_DB1(DB1);
	print_DB2(DB2);
	print_DB3(DB3);
	getchar();
	getchar();
	return 0;
}
void print_DB1(vector<list<int>> &DB1) {
	vector<list<int>>::iterator it1 = (DB1.begin());
	while (it1 != DB1.end()) {
		list<int>::iterator it2 = it1->begin();
		for (size_t x = 0; x < it1->size(); x++) {
			cout << *it2 << " ";
			it2++;
		}
		it1++;
	}
	cout << endl;
}
void print_DB2(vector<list<int>*> &DB2) {
	vector<list<int>*>::iterator it1 = DB2.begin();
	while (it1 != DB2.end()) {
		list<int>::iterator it2 = (*it1)->begin();
		for (size_t x = 0; x < (*it1)->size(); x++) {
			cout << *it2 << " ";
			it2++;
		}
		it1++;
	}
	cout << endl;
}
void print_DB3(list<vector<int>> & DB3) {
	list<vector<int>>::iterator it1 = DB3.begin();
	while (it1 != DB3.end()) {
		vector<int>::iterator it2 = it1->begin();
		for (size_t x = 0; x < (it1)->size(); x++) {
			cout << *it2 << " ";
			it2++;
		}
		it1++;
	}
	cout << endl;
}
void DB1_to_DB2(vector<list<int> > &DB1, vector<list<int>*> & DB2) {
	vector<list<int>>::iterator it1 = (DB1.begin());
	while (it1 != DB1.end()) {
		list<int> *d = new list<int>(*it1);
		DB2.push_back(d);
		it1++;
		
	}
}
void DB1_to_DB3(vector<list<int>> &DB1, list<vector<int>> & DB3) {
	vector<list<int>>::iterator it1 = (DB1.begin());
	while (it1 != DB1.end()) {
		vector<int> v1;
		list<int>::iterator it2 = it1->begin();
		for (size_t x = 0; x < it1->size(); x++) {
			v1.push_back(*it2);
			it2++;
		}
		DB3.push_back(v1);
		it1++;
	}
}