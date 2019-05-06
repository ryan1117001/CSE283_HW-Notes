#include <iostream>
#include <string>
using namespace std;

class course {
public:
	string name;//An example: "CSE283"
	int section;
	int credits;
	course * next;
	course() { next = nullptr; }
	course(string n, int s, int c) { name = n; section = s; credits = c;  next = nullptr; }
};
class student {
public:
	int ID;
	course * head; //points to a link list of courses
	student() { head = nullptr; }
	student(int i) { ID = i; head = nullptr; }
};


void add_student(student DB[], int &num_students); //Add student to array
void add_course(student DB[], int &num_students); //Add course under student
void remove_student(student DB[], int &num_students); //remove a student from the array
void remove_course(student DB[], int & num_students); //remove course undera student
void total_credits(student DB[], int & num_students); //count up total number of credits under student
void print_courses(student DB[], int & num_students); //print out all course under a student
void check_ID(student DB[], int &num_students); //check the existence of a student
void check_course(student DB[], int &num_students); //check if a student is taking a certain course
void print_studentID(student DB[], int &num_students); //Print out all student IDs
void print_all(student DB[], int &num_students); //Print both Id and courses
void sort_ID(student DB[], int &num_students); //Sort student ID by smallest to greatest
int main() {
	student DB[10];
	int num_students = 0;
	int select = -1;
	do {
		cout << "Enter 0-10(?) to select an operation\n";
		cout << "0 to quit program" << endl;
		cout << "1 to add a student" << endl;
		cout << "2 to add a course for a student" << endl;
		cout << "3 to remove a student" << endl;
		cout << "4 to remove a course of a student" << endl;
		cout << "5 to add total credits for student" << endl;
		cout << "6 to check if student exists" << endl;
		cout << "7 to see a student's course." << endl;
		cout << "8 to print all course(s) of a student." << endl;
		cout << "9 to print all student IDs" << endl;
		cout << "10 to print all student info" << endl;
		cout << "11 to sort students by ID" << endl;
		cin >> select;
		switch (select) {
		case 0: break;//to quit
		case 1: add_student(DB, num_students); break;
		case 2: add_course(DB, num_students); break;
		case 3: remove_student(DB, num_students); break;
		case 4: remove_course(DB, num_students); break;
		case 5: total_credits(DB, num_students); break;
		case 6: check_ID(DB, num_students); break;
		case 7: check_course(DB, num_students); break;
		case 8: print_courses(DB, num_students); break;
		case 9: print_studentID(DB, num_students); break;
		case 10: print_all(DB, num_students); break;
		case 11: sort_ID(DB, num_students); break;

		}

	} while (select != 0);
	getchar();
	getchar();
	return 0;

}
void add_student(student DB[], int &num_students) {
	int id;
	cout << "Enter student ID\n"; //to add an ID
	cin >> id;
	for (int i = 0; i < num_students; i++) { 
		if (DB[i].ID == id) {
			cout << "The student already exists\n" << endl;
			return;
		}
	}
	DB[num_students].ID = id; //associate id with index
	DB[num_students].head = nullptr;
	num_students++;
	return;
}
void add_course(student DB[], int &num_students) {
	int id;
	string n;
	int s, c;
	cout << "Enter student ID" << endl; //used to check existence
	cin >> id;
	int find = -1;
	for (int i = 0; i < num_students; i++) {
		if (DB[i].ID == id) {
			find = i;
			break;
		}
	}
	if (find == -1) {
		cout << "Error!  The student does not exist!\n" << endl;
		return;
	}
	cout << "Enter course name, section, and credits, separated by space" << endl; 
	cin >> n >> s >> c;
	course * p = DB[find].head;
	while (p != nullptr) {
		if (p->name == n) {
			cout << " Error!  The course already exits!\n" << endl;
			return;
		}
		p = p->next;
	}
	p = new course(n, s, c); //pointer points to new course
	p->next = DB[find].head;
	DB[find].head = p;
	return;
}
void remove_student(student DB[], int &num_students) {
	int id;
	cout << "Enter student ID" << endl;
	cin >> id;
	int find = -1;
	for (int i = 0; i < num_students; i++) { 
		if (DB[i].ID == id) {
			find = i;
			break;
		}
	}
	if (find == -1) {
		cout << "Error!  The student does not exist!\n" << endl;
		return;
	}
	for (int x = find; x < num_students; x++)
		DB[x] = DB[x + 1]; //pushes given student id to the last and
	num_students--; //makes array smaller
	cout << "Student has been removed\n" << endl;
	return;
}
void remove_course(student DB[], int &num_students) {
	int id;
	cout << "Enter student ID" << endl;
	cin >> id;
	int find = -1;
	for (int i = 0; i < num_students; i++) {
		if (DB[i].ID == id) {
			find = i;
			break;
		}
	}
	if (find == -1) {
		cout << "Error!  The student does not exist!\n" << endl;
		return;
	}
	string n;
	cout << "Which course is being deleted?" << endl;
	cin >> n;
	course *p1 = DB[find].head, *temp = NULL;
	
	if (p1->name == n && p1 != nullptr) { 
		DB[find].head = p1->next; //makes next in line the head
		delete p1;
		cout << "Course has been removed.\n" << endl;
		return;
	}
	while (p1 != nullptr && p1->name != n) { //temp made to keep lists linked
		temp = p1;
		p1 = p1->next;
	}
	if (p1 == NULL) {
		cout << "Course does not exist.\n" << endl;
		return;
	}
	temp->next = p1->next;
	delete p1; //removes course
	cout << "Course has been removed." << endl;
	return;
}
void total_credits(student DB[], int &num_students) {
	int id;
	cout << "Enter student ID to see total score" << endl;
	cin >> id;
	int find = -1;
	for (int i = 0; i < num_students; i++) {
		if (DB[i].ID == id) {
			find = i;
			break;
		}
	}
	if (find == -1) {
		cout << "Error!  The student does not exist!\n" << endl;
		return;
	}
	course * p = DB[find].head;
	int c = 0;
	while (p != nullptr) { //finds credits and adds them together
		c += p->credits;
		p = p->next;
	}
	cout << "Total Credit: " << c << endl;
	return;
}
void check_ID(student DB[], int &num_students) {
	int id;
	cout << "Enter student ID to check existence." << endl;
	cin >> id;
	int find = -1;
	for (int i = 0; i < num_students; i++) {
		if (DB[i].ID == id) { //finds id equal to given id
			find = i;
			cout << id << " does exist.\n" << endl;
			break;
		}
	}
	if (find == -1) {
		cout << "Error!  The student does not exist!\n" << endl;
		return;
	}
	return;
}
void check_course(student DB[], int &num_students) { 
	int id;
	cout << "Enter student ID" << endl;
	cin >> id;
	int find = -1;
	for (int i = 0; i < num_students; i++) {
		if (DB[i].ID == id) {
			find = i;
			break;
		}
	}
	if (find == -1) {
		cout << "Error!  The student does not exist!\n" << endl;
		return;
	}
	string c;
	cout << "What is the course you are looking for?" << endl;
	cin >> c;
	course *p = DB[find].head;
	while (p != nullptr) { //finds course
		if (p->name == c) {
			cout << "The student is taking " << c << ".\n" << endl;
			break;
		}
	}
	cout << "The student is not taking the class.\n" << endl;
	return;
}
void print_courses(student DB[], int & num_students) {
	int id;
	cout << "Enter student ID to print courses" << endl;
	cin >> id;
	int find = -1;
	for (int i = 0; i < num_students; i++) {
		if (DB[i].ID == id) {
			find = i;
			break;
		}
	}
	if (find == -1) {
		cout << "Error!  The student does not exist!\n" << endl;
		return;
	}
	cout << "The courses for student " << DB[find].ID << " : " << endl;
	course * p = DB[find].head; 
	while (p != nullptr) { //once found prints name, section and credits
		cout << p->name << " " << p->section << " " << p->credits << endl;
		p = p->next;
	}
	cout << endl;
	return;
}
void print_studentID(student DB[], int &num_students) {
	cout << "All Student IDs.\n";
	for (int i = 0; i < num_students; i++)
		cout << DB[i].ID << endl;
}
void print_all(student DB[], int &num_students) {
	cout << "All student information" << endl;
	for (int i = 0; i < num_students; i++) {
		cout << DB[i].ID << endl;
		course *p = DB[i].head;
		while (p != nullptr) {
			cout << p->name << " " << p->section << " " << p->credits << endl << endl;
			p = p->next;
		}
	}
	return;
}
void sort_ID(student DB[], int &num_students) { //selected sort used to order IDs
	int current, temp;
	for (int x = 0; x < num_students; x++) {
		current = x;
		for (int y = (x + 1); y < num_students; y++) {
			if (DB[y].ID < DB[current].ID)
				current = y;
			temp = DB[current].ID;
			DB[current].ID = DB[x].ID;
			DB[x].ID = temp;
		}
	}
	cout << "Students have been sorted" << endl;
	return;
}