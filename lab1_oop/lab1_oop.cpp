#include "distribution.hpp"
#include "mix_distribution.hpp"
//#include "emp_distribution.hpp"

#include <iostream>
#include <ctime>
#include <limits> // для очистки потока ввода cin
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

int test_normal();
int test_mixed();
int test_empiric();

using namespace std;

int main() {
	srand(static_cast<unsigned int>(time(nullptr)));
	int switcher = -1;
	bool exit_flag = false;

	while (!exit_flag) {

		cout << endl << "8: Huber`s distribution" << endl;
		cout << "1. Test primary distribution" << endl;
		cout << "2. Test mixed distribution" << endl;
		cout << "3. Test empirical distribution" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: "; cin >> switcher;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Wrong input" << endl;
			continue;
		}
		else if (switcher < 1 || switcher > 4) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Wrong input" << endl;
			continue;
		}

		switch (switcher) {
		case 1: test_normal(); break;
		case 2: test_mixed(); break;
		case 3: test_empiric(); break;
		case 4: exit_flag = true; break;
		deafult: cout << "Wrong input" << endl; break;
		}
	}
	return 0;
}

int test_normal() {
	int switcher;
	double x, nu, mu, lam;

	cout << endl << "1. Standart test set (data from table)" << endl;
	cout << "2. Input from keyboard" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your choice: " << endl; cin >> switcher;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Wrong input" << endl;
		return 0;
	}
	else if (switcher < 1 || switcher > 4) {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Wrong input" << endl;
		return 0;
	}

	switch (switcher) {
		case 1: {
			 
	}
	}
}