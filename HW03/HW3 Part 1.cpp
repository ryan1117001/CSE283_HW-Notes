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

void add_student(vector<student> &DB);
void add_course(vector<student> &DB);
void remove_student(vector<student> &DB);
void remove_course(vector<student> &DB);
void total_credits(vector<student> &DB); 
void print_courses(vector<student> &DB); 
void check_ID(vector<student> &DB); 
void check_course(vector<student> &DB);
void print_studentID(vector<student> &DB);
void print_all(vector<student> &DB); 
void sort_ID(vector<student> &DB); 
void sort_course(vector<student> &DB);

int main() {
	vector<student> DB;
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
		cout << "Enter 11 to sort students by ID" << endl;
		cout << "Enter 12 to sort student's courses" << endl;

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
		case 11: sort_ID(DB); break;
		case 12: sort_course(DB); break;		

		}
	} while (select != 0);
	getchar();
	return 0;
}

void add_student(vector<student> &DB) {
	cout << "Enter student ID" << endl;
	int id;
	cin >> id;
	student s1(id);
	vector<student>::iterator it1 = find(DB.begin(), DB.end(), s1);
	if (it1 != DB.end()) {
		cout << "Error!  The student already exists in DB" << endl;
		return;
	}
	s1.head = new list<course>;
	DB.push_back(s1);

}
void add_course(vector<student> &DB) {
	cout << "Enter student ID" << endl;
	int id;
	cin >> id;
	student s1(id);
	vector<student>::iterator it1 = find(DB.begin(), DB.end(), s1);
	if (it1 == DB.end()) {
		cout << "Error!  The student does not exist in DB" << endl;
		return;
	}
	cout << "Enter course name, section, credits separated by space" << endl;
	string name;
	int section, credits;
	cin >> name >> section >> credits;
	course c(name, section, credits);
	list<course>::iterator it2 = find(it1->head->begin(), it1->head->end(), c);
	if (it2 != it1->head->end()) {
		cout << "Error!  The course already exists" << endl;
		return;
	}
	it1->head->push_front(c);
}
void remove_student(vector<student> &DB) {
	cout << "Enter student ID" << endl;
	int id;
	cin >> id;
	student s1(id);
	vector<student>::iterator it1 = find(DB.begin(), DB.end(), s1);
	if (it1 == DB.end()) {
		cout << "Error!  The student does not exist in DB" << endl;
		return;
	}
	delete it1->head;
	DB.erase(it1);
	cout << "Student has been deleted" << endl;
	return;
}
void remove_course(vector<student> &DB) {
	cout << "Enter student ID" << endl;
	int id;
	cin >> id;
	student s1(id);
	vector<student>::iterator it1 = find(DB.begin(), DB.end(), s1);
	if (it1 == DB.end()) {
		cout << "Error!  The student does not exist in DB" << endl;
		return;
	}
	string name;
	int section = 0, credits = 0;
	cout << "Which course is being removed?" << endl;
	cin >> name;
	course c(name, section, credits);
	list<course>::iterator it2 = find(it1->head->begin(), it1->head->end(), c);
	if (it2 == it1->head->end()) {
		cout << "Error!  The course does not exist" << endl;
		return;
	}
	it1->head->erase(it2);
	cout << "Course has been deleted" << endl;
	return;
} 
void total_credits(vector<student> &DB) {
	cout << "Enter student ID" << endl;
	int id;
	cin >> id;
	student s1(id);
	vector<student>::iterator it1 = find(DB.begin(), DB.end(), s1);
	if (it1 == DB.end()) {
		cout << "Error!  The student does not exist in DB" << endl;
		return;
	}
	int x = 0;
	list<course>::iterator it2 = it1->head->begin();
	while (it2 != it1->head->end()) {
		x += it2->credits;
		it2++;
	}
	cout << "The total credits for this student is: " << x << endl;
	return;
}
void check_ID(vector<student> &DB) {
	cout << "Enter student ID" << endl;
	int id;
	cin >> id;
	student s1(id);
	vector<student>::iterator it1 = find(DB.begin(), DB.end(), s1);
	if (it1 == DB.end()) {
		cout << "The student exists" << endl;
		return;
	}
	cout << "The student does not exist" << endl;
	return;
}
void check_course(vector<student> &DB) {
		cout << "Enter student ID" << endl;
		int id;
		cin >> id;
		student s1(id);
		vector<student>::iterator it1 = find(DB.begin(), DB.end(), s1);
		if (it1 == DB.end()) {
			cout << "Error!  The student does not exist in DB" << endl;
			return;
		}
		cout << "Enter course name, section, credits separated by space" << endl;
		string name;
		int section, credits;
		cin >> name >> section >> credits;
		course c(name, section, credits);
		list<course>::iterator it2 = find(it1->head->begin(), it1->head->end(), c);
		if (it2 != it1->head->end()) {
			cout << "The course already exists" << endl;
			return;
		}
		cout << "The course does not exist" << endl;
}
void print_studentID(vector<student> &DB) {
	for (size_t i = 0; i < DB.size(); i++) {
		cout << DB[i].ID << endl;
	}
}
void print_courses(vector<student> &DB) {
	cout << "Enter student ID" << endl;
	int id;
	cin >> id;
	student s1(id);
	vector<student>::iterator it1 = find(DB.begin(), DB.end(), s1);
	if (it1 == DB.end()) {
		cout << "Error!  The student does not exist in DB" << endl;
		return;
	}
	list<course>::iterator it2 = it1->head->begin();
	while (it2 != it1->head->end()) {
		cout << it2->name << " " << it2->section << " " << it2->credits << endl;
		it2++;
	}
}
void print_all(vector<student> &DB) {
	list<course>::iterator it1;
	for (size_t i = 0; i < DB.size(); i++) {
		it1 = (DB[i].head)->begin();
		cout << "ID: " << DB[i].ID << endl;
		while (it1 != (DB[i].head)->end()) {
			cout << it1->name << " " << it1->section << " " << it1->credits << endl;
			it1++;
		}
	}
	return;
}
void sort_ID(vector<student> &DB) {
	sort(DB.begin(), DB.end());
}
void sort_course(vector<student> &DB) {
	vector<student>::iterator it1 = DB.begin();
	while (it1 != DB.end()) {
		it1->head->sort();
		it1++;
	}
}