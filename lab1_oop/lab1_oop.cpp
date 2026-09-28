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

			x = 0.0; mu = 0.0; lam = 1.0; nu = 0.5;
			cout << "1. Standart test. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameter ν = " << nu << endl;
			cout << "Shift parameter μ = " << mu << endl;
			cout << "Scale parameter λ = " << lam << endl << endl;

			cout << "Result:" << endl;
			cout << "Density:           f(x) = " << distribution::get_density(x, nu, mu, lam)
				<< "; expected: f0 = 0.223"
				<< endl;
			cout << "Expected value:    M[ξ] = " << distribution::get_expected_value(nu, mu, lam)
				<< "; expected: " << mu
				<< endl;
			cout << "Dispersion:        D[ξ] = " << distribution::get_dispersion(nu, mu, lam)
				<< "; expected: σ^2 = 8.08"
				<< endl;
			cout << "Asymmetry coef.:     γ1 = " << distribution::get_asymmetry(nu, mu, lam)
				<< "; expected: γ1 = 0.0"
				<< endl;
			cout << "Excess coef.:        γ2 = " << distribution::get_excess(nu, mu, lam)
				<< "; expected: γ2 = 2.94"
				<< endl;
			cout << "P{x in central interval} = " << distribution::get_P(nu)
				<< "; expected: 0.214"
				<< endl;


			lam = 2.0; nu = 1.5;
			cout << "2. Scale test. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameter ν = " << nu << endl;
			cout << "Shift parameter μ = " << mu << endl;
			cout << "Scale parameter λ = " << lam << endl << endl;

			cout << "Result:" << endl;
			cout << "Density:            f(x) = " << distribution::get_density(x, nu, mu, lam)
				<< "; expected: f0 = 0.384"
				<< endl;
			cout << "Expected value:     M[ξ] = " << distribution::get_expected_value(nu, mu, lam)
				<< "; expected: " << mu
				<< endl;
			cout << "Dispersion:         D[ξ] = " << distribution::get_dispersion(nu, mu, lam)
				<< "; expected: σ^2 = 1.31"
				<< endl;
			cout << "Asymmetry coef.:      γ1 = " << distribution::get_asymmetry(nu, mu, lam)
				<< "; expected: γ1 = 0.0"
				<< endl;
			cout << "Excess coef.:         γ2 = " << distribution::get_excess(nu, mu, lam)
				<< "; expected: γ2 = 1.30"
				<< endl;
			cout << "P{x in central interval} = " << distribution::get_P(nu)
				<< "; expected: 0.834"
				<< endl;


			mu = 2.0; lam = 2.0; nu = 3.0; x = mu;
			cout << "3. Shift-scale test. Data:" << endl;
			cout << "Argument x = μ = " << x << endl;
			cout << "Shape parameter ν = " << nu << endl;
			cout << "Shift parameter μ = " << mu << endl;
			cout << "Scale parameter λ = " << lam << endl << endl;

			cout << "Result:" << endl;
			cout << "Density:            f(x) = " << distribution::get_density(x, nu, mu, lam)
				<< "; expected: f0 = 0.399"
				<< endl;
			cout << "Expected value:     M[ξ] = " << distribution::get_expected_value(nu, mu, lam)
				<< "; expected: " << mu
				<< endl;
			cout << "Dispersion:         D[ξ] = " << distribution::get_dispersion(nu, mu, lam)
				<< "; expected: σ^2 = 1.00"
				<< endl;
			cout << "Asymmetry coef.:      γ1 = " << distribution::get_asymmetry(nu, mu, lam)
				<< "; expected: γ1 = 0.0"
				<< endl;
			cout << "Excess coef.:         γ2 = " << distribution::get_excess(nu, mu, lam)
				<< "; expected: γ2 = 0.04"
				<< endl;
			cout << "P{x in central interval} = " << distribution::get_P(nu)
				<< "; expected: 0.997"
				<< endl;

			return 1;
		}
		case 2: {
			cout << "Enter value of x: "; cin >> x;
			cout << "Enter value of shape parameter ν (ν > 0): "; cin >> nu;
			if (nu <= 0) {
				cout << "Incorrect value of ν (must be grater then 0)";
				return 0;
			}
			cout << "Enter value of shift parameter μ: "; cin >> mu;
			cout << "Enter value of scale parameter λ (λ > 0): "; cin >> lam;
			if (lam <= 0) {
				cout << "Incorrect value of λ (must be grater then 0)";
				return 0;
			}

			cout << "Result:" << endl;
			cout << "Density:            f(x) = " << distribution::get_density(x, nu, mu, lam) << endl;
			cout << "Expected value:     M[ξ] = " << distribution::get_expected_value(nu, mu, lam) << endl;
			cout << "Dispersion:         D[ξ] = " << distribution::get_dispersion(nu, mu, lam) << endl;
			cout << "Asymmetry coef.:      γ1 = " << distribution::get_asymmetry(nu, mu, lam) << endl;
			cout << "Excess coef.:         γ2 = " << distribution::get_excess(nu, mu, lam) << endl;
			cout << "P{x in central interval} = " << distribution::get_P(nu) << endl;
		}

		case 3: {
			return 0;
		}

		default:
			return 0;

	}
}

int test_mixed() {
	int switcher;
	double x, p, nu1, mu1, lam1, nu2, mu2, lam2;

	cout << endl << "1. Standart test set (data from the content)" << endl;
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

	//switch
}