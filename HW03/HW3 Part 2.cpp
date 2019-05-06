#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	bool operator==(course c) { return (name == c.name); }
	bool operator<(course c) { return (name < c.name); }
};
class student {
public:
	int ID;
	list<course> * head;
	student() { head = nullptr; }
	student(int i) { ID = i; head = nullptr; }
	bool operator==(student s) { return (ID == s.ID); }
	bool operator<(student s) { return (ID < s.ID); }
};

void add_student(map<int, list<course>> &DB);
void add_course(map<int, list<course>> &DB);
void remove_student(map<int, list<course>> &DB);
void remove_course(map<int, list<course>> &DB);
void total_credits(map<int, list<course>> &DB);
void check_ID(map<int, list<course>> &DB);
void check_course(map<int, list<course>> &DB);
void print_courses(map<int, list<course>> &DB);
void print_studentID(map<int, list<course>> &DB);
void print_all(map<int, list<course>> &DB);
void sort_course(map<int, list<course>> &DB);

int main() {
	map<int, list<course> > DB;
	int select;
	do {
		cout << "Enter 0 to quit" << endl;
		cout << "Enter 1 to add a student " << endl;
		cout << "Enter 2 to add a course" << endl;
		cout << "Enter 3 to remove a student" << endl;
		cout << "Enter 4 to remove a student's course" << endl;
		cout << "Enter 5 to return the number of credits" << endl;
		cout << "Enter 6 to check if a student is in the DB" << endl;
		cout << "Enter 7 to check if a student is taking a specific course" << endl;
		cout << "Enter 8 print out courses of a student" << endl;
		cout << "Enter 9 to print all student IDs" << endl;
		cout << "Enter 10 to print DB" << endl;
		cout << "Enter 11 to sort student's courses" << endl;
		cin >> select;
		switch (select) {
		case 0: break;
		case 1: add_student(DB); break;
		case 2: add_course(DB); break;
		case 3: remove_student(DB); break;
		case 4: remove_course(DB); break;
		case 5: total_credits(DB); break;
		case 6: check_ID(DB); break;
		case 7: check_course(DB); break;
		case 8: print_courses(DB); break;
		case 9: print_studentID(DB); break;
		case 10: print_all(DB); break;
		case 11: sort_course(DB); break;
		}
	} while (select != 0);
	return 0;
}
void add_student(map<int, list<course>> &DB) {
	int id;
	cout << " Enter Student ID" << endl;
	cin >> id;
	if (DB.find(id) != DB.end()) {
		cout << "Error!  The student already exists";
		return;
	}
	list<course> l1;
	DB[id] = l1;
}
void add_course(map<int, list<course>> &DB) {
	int id;
	cout << "Enter Student ID" << endl;
	cin >> id;
	map<int, list<course>>::iterator it9 = DB.find(id);
	if (it9 == DB.end()) {
		cout << "Error!  The student does not exist";
		return;
	}
	cout << "Enter course name, section, credits separated by space" << endl;
	course c1;
	cin >> c1.name >> c1.section >> c1.credits;
	if (find((it9->second).begin(), (it9->second).end(), c1) != (it9->second).end()) {
		cout << "Error!  The course already exists" << endl;
		return;
	}
	(it9->second).push_front(c1);
}
void remove_student(map<int, list<course>> &DB) {
	int id;
	cout << " Enter Student ID" << endl;
	cin >> id;
	map<int, list<course>>::iterator it9 = DB.find(id);
	if (it9 == DB.end()) {
		cout << "Error!  The student does not exist";
		return;
	}
	DB.erase(it9);
}
void remove_course(map<int, list<course>> &DB) {
	int id;
	cout << " Enter Student ID" << endl;
	cin >> id;
	map<int, list<course>>::iterator it9 = DB.find(id);
	if (it9 == DB.end()) {
		cout << "Error!  The student does not exist";
		return;
	}
	cout << "Which course is being deleted" << endl;
	course c2;
	c2.credits = 0;
	c2.section = 0;
	cin >> c2.name;
	list<course>::iterator it2 = find((it9->second).begin(), (it9->second).end(), c2);
	if (find((it9->second).begin(), (it9->second).end(), c2) == (it9->second).end()) {
		cout << "Error! The course does not exist." << endl;
		return;
	}
	(it9->second).erase(it2);
}
void total_credits(map<int, list<course>> &DB) {
	int id;
	cout << " Enter Student ID" << endl;
	cin >> id;
	map<int, list<course>>::iterator it9 = DB.find(id);
	if (it9 == DB.end()) {
		cout << "Error!  The student does not exist";
		return;
	}
	int x = 0;
	list<course>::iterator it1;
	it1 = (it9->second).begin();
	while (it1 != (it9->second).end()) {
		x += it1->credits;
		it1++;
	}
	cout << "The total number of credits are: " << x << endl;
}
void check_ID(map<int, list<course>> &DB) {
	int id;
	cout << " Enter Student ID" << endl;
	cin >> id;
	map<int, list<course>>::iterator it9 = DB.find(id);
	if (it9 == DB.end()) {
		cout << "Error!  The student does not exist";
		return;
	}
	cout << "Student ID does exist" << endl;
}
void check_course(map<int, list<course>> &DB) {
	int id;
	cout << " Enter Student ID" << endl;
	cin >> id;
	map<int, list<course>>::iterator it9 = DB.find(id);
	if (it9 == DB.end()) {
		cout << "Error!  The student does not exist";
		return;
	}
	cout << "Enter course name, section, credits separated by space" << endl;
	course c1;
	c1.credits = 0;
	c1.section = 0;
	cin >> c1.name;
	if (find((it9->second).begin(), (it9->second).end(), c1) == (it9->second).end()) {
		cout << "The course does not exist" << endl;
		return;
	}
	cout << "The course already exists" << endl;
	return;
}
void print_courses(map<int, list<course>> &DB) {
	int id;
	cout << "Enter Student ID" << endl;
	cin >> id;
	map<int, list<course>>::iterator it9 = DB.find(id);
	if (it9 == DB.end()) {
		cout << "Error!  The student does not exist";
		return;
	}
	list<course>::iterator it10 = (it9->second).begin();
	while (it10 != (it9->second).end()) {
		cout << it10->name << " " << it10->section << " " << it10->credits << endl;
		it10++;
	}
	return;
}
void print_studentID(map<int, list<course>> &DB) {
	map<int, list<course>>::iterator it1 = DB.begin();
	while (it1 != DB.end()) {
		cout << it1->first << endl;
		it1++;
	}
}
void print_all (map<int, list<course>> &DB) {
	map<int, list<course>>::iterator it1 = DB.begin();
	list<course>::iterator it2;
	while (it1 != DB.end()) {
		it2 = (it1->second).begin();
		cout << "The courses for student  " << it1->first << " : " << endl;
		while (it2 != (it1->second).end()) {
			cout << it2->name << " " << it2->section << " " << it2->credits << endl;
			it2++;
		}
		it1++;
	}
}
void sort_course(map<int, list<course>> &DB) {
	map<int, list<course>>::iterator it1 = DB.begin();
	while (it1 != DB.end()) {
		it1->second.sort();
		it1++;
	}
}