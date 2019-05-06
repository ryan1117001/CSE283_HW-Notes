#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

class point {
public:
	double x, y;
	point() { x = 0.0; y = 0.0; };
	point(double i, double j) { x = i; y = j; }
	void display_point() { cout << "(" << x << " , " << y << ")" << endl; };
	void input();
	double operator-(point &p2);
};

class shape {
public:
	vector<point> vp;
	void input_v();

	virtual double area() = 0;
	virtual double perimeter() = 0;
	virtual void display_corners() = 0;
};

class triangle : public shape {
protected:
	double side1, side2, side3;
public:
	triangle() {};

	virtual double area() {
		double s = (perimeter()/2)*(perimeter()/2 - side1) * (perimeter()/2 - side2) * (perimeter()/2 - side3);
		return pow(s, .5);
	}
	virtual double perimeter() { return side1 + side2 + side3;	}
	virtual void display_corners() {
		cout << "The corners of the triangle" << endl;
		vector<point>::iterator it1 = vp.begin();
		for (int x = 0; x < 3; x++) {
			it1->display_point();
			it1++;
		}
		cout << "The sides are " << side1 << ", " << side2 << ", and " << side3 << endl;
		cout << "The perimeter is " << perimeter() << endl;
		cout << "The area is " << area() << endl;
	}
	void set_up();
};
class square : public shape {
protected:
	double side1, side2, side3;
public:
	square() {};
	virtual double area() { return length() * width(); }
	virtual double perimeter() { return 2*length() + 2*width(); }
	virtual void display_corners() {
		cout << "The corners of the square" << endl;
		vector<point>::iterator it1 = vp.begin();
			for (int x = 0; x < 4; x++) {
				it1->display_point();
				it1++;
			}
		cout << "The sides are " << length() << " and " << width() << endl;
		cout << "The perimeter is " << perimeter() << endl;
		cout << "The area is " << area() << endl;
	}
	void square_set();
	double length();
	double width();
};
void point::input() {
	cout << "What is your point? Input two numbers with a space" << endl;
	cin >> x >> y;
}
double point::operator-(point &p2) {
	double d1,d2, d3, temp1, temp2;
	temp1 = this->x - p2.x;
	temp2 = this->y - p2.y;
	d1 = pow(temp1, 2.0);
	d2 = pow(temp2, 2.0);
	d3 = pow((d1 + d2), .5);
	return d3;
}
void shape::input_v() {
	int temp, ans;
	cout << "Test 1 is a triangle. Test 2 is a square. Which test is this?" << endl;
	cin >> temp;
	if (temp == 1) ans = 3;
	else ans = 4;
	for (int x = 0; x < ans; x++) {
		point *p1;
		p1 = new point();
		p1->input();
		vp.push_back(*p1);
	}
}
void triangle::set_up() {
	point p1, p2, p3;
	vector<point>::iterator it1 = vp.begin();
	p1 = *it1; p2 = *++it1; p3 = *++it1;
	side1 = p1 - p2;
	side2 = p1 - p3;
	side3 = p2 - p3;

}
void square::square_set() {
	point p1, p2, p3, p4;
	vector<point>::iterator it1 = vp.begin();
	p1 = *it1; p2 = *++it1; p3 = *++it1++; p4 = *++it1;
	side1 = p1 - p2;
	side2 = p1 - p3;
	side3 = p1 - p4;
}
double square::length() {
	if (side1 >= side2 && side1>=side3) {
		if (side2 >= side3) return side2;
		else return side3;
	}
	else if (side2>= side1 && side2>=side3) {
		if (side1 >= side3) return side1;
		else return side3;
	}
	else if (side3>=side1 && side3>=side2) {
		if (side1 >= side2) return side1;
		else return side2;
	}
}
double square::width() {
	if (side1 <= side2 && side1 <= side3) {
		return side1;
	}
	else if (side2 <= side1 && side2 <= side3) {
		return side2;
	}
	else if (side3 <= side1 && side3 <= side2) {
		return side3;
	}
}

int main() {
	triangle poly1;
	square poly2;
	
	poly1.input_v();
	poly1.set_up();
	poly1.display_corners();
	
	poly2.input_v();
	poly2.square_set();
	poly2.display_corners();

	getchar();
	getchar();
	return 0;
}

//Test 1 is a triangle.Test 2 is a square.Which test is this ?
//1
//What is your point ? Input two numbers with a space
//0 0
//What is your point ? Input two numbers with a space
//5 0
//What is your point ? Input two numbers with a space
//0 5
//The corners of the triangle
//(0, 0)
//(5, 0)
//(0, 5)
//The sides are 5, 5, and 7.07107
//The perimeter is 17.0711
//The area is 12.5
//Test 1 is a triangle.Test 2 is a square.Which test is this ?
//2
//What is your point ? Input two numbers with a space
//1 1
//What is your point ? Input two numbers with a space
//6 1
//What is your point ? Input two numbers with a space
//1 6
//What is your point ? Input two numbers with a space
//6 6
//The corners of the square
//(1, 1)
//(6, 1)
//(1, 6)
//(6, 6)
//The sides are 5 and 5
//The angles are 90.
//The perimeter is 20
//The area is 25
