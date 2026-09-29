#include "distribution.hpp"
#include "mix_distribution.hpp"
//#include "emp_distribution.hpp"

#include <iostream>
#include <ctime>
#include <limits> //  для очистки потока ввода cin
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

int test_normal();
int test_mixed();
//int test_empiric();

using namespace std;

static void plot_density(int flag, double x, double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p) {
	ostringstream cmd;
	cmd << "\"C:\\Users\\Stepan\\AppData\\Local\\Programs\\Python\\Python314\\python.exe\" plot.py "
		<< flag << " "
		<< x << " "
		<< nu1 << " " << mu1 << " " << lam1 << " "
		<< nu2 << " " << mu2 << " " << lam2 << " "
		<< p;
	cout << "Building density plot..." << endl;
	int ret = system(cmd.str().c_str());
	if (ret != 0) {
		cout << "Warning: plot.py returned code " << ret
			<< " (is python3/matplotlib available? is plot.py in cwd?)" << endl;
	}
}


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
		//case 3: test_empiric(); break;
		case 4: exit_flag = true; break;
		default: cout << "Wrong input" << endl; break;
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
			cout << "Shape parameter nu = " << nu << endl;
			cout << "Shift parameter mu = " << mu << endl;
			cout << "Scale parameter lambda = " << lam << endl << endl;

			cout << "Result:" << endl;
			cout << "Density:             f(x) = " << distribution::get_density(x, nu, mu, lam)
				<< "; expected: f0 = 0.223"
				<< endl;
			cout << "Expected value:    M[ksi] = " << distribution::get_expected_value(nu, mu, lam)
				<< "; expected: " << mu
				<< endl;
			cout << "Dispersion:        D[ksi] = " << distribution::get_dispersion(nu, mu, lam)
				<< "; expected: sigma^2 = 8.08"
				<< endl;
			cout << "Asymmetry coef.:   gamma1 = " << distribution::get_asymmetry(nu, mu, lam)
				<< "; expected: gamma1 = 0.0"
				<< endl;
			cout << "Excess coef.:      gamma2 = " << distribution::get_excess(nu, mu, lam)
				<< "; expected: gamma2 = 2.94"
				<< endl;
			cout << "P{x in central interval} =  " << distribution::get_P(nu)
				<< "; expected: 0.214"
				<< endl << endl;

			plot_density(0, x, nu, mu, lam, 0, 0, 0, 0);



			lam = 2.0; nu = 1.5;
			cout << "2. Scale test. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameter nu = " << nu << endl;
			cout << "Shift parameter mu = " << mu << endl;
			cout << "Scale parameter lambda = " << lam << endl << endl;

			cout << "Result:" << endl;
			cout << "Density:             f(x) = " << distribution::get_density(x, nu, mu, lam)
				<< "; expected: f0/lambda = 0.192"
				<< endl;
			cout << "Expected value:    M[ksi] = " << distribution::get_expected_value(nu, mu, lam)
				<< "; expected: " << mu
				<< endl;
			cout << "Dispersion:        D[ksi] = " << distribution::get_dispersion(nu, mu, lam)
				<< "; expected: sigma^2 * lambda^2 = 5.24"
				<< endl;
			cout << "Asymmetry coef.:   gamma1 = " << distribution::get_asymmetry(nu, mu, lam)
				<< "; expected: gamma1 = 0.0"
				<< endl;
			cout << "Excess coef.:      gamma2 = " << distribution::get_excess(nu, mu, lam)
				<< "; expected: gamma2 = 1.30"
				<< endl;
			cout << "P{x in central interval} =  " << distribution::get_P(nu)
				<< "; expected: 0.834"
				<< endl << endl;
			
			plot_density(0, x, nu, mu, lam, 0, 0, 0, 0);



			mu = 2.0; lam = 2.0; nu = 3.0; x = mu;
			cout << "3. Shift-scale test. Data:" << endl;
			cout << "Argument x = mu = " << x << endl;
			cout << "Shape parameter nu = " << nu << endl;
			cout << "Shift parameter mu = " << mu << endl;
			cout << "Scale parameter lambda = " << lam << endl << endl;

			cout << "Results:" << endl;
			cout << "Density:             f(x) = " << distribution::get_density(x, nu, mu, lam)
				<< "; expected: f0/lambda = 0.1995"
				<< endl;
			cout << "Expected value:    M[ksi] = " << distribution::get_expected_value(nu, mu, lam)
				<< "; expected: " << mu
				<< endl;
			cout << "Dispersion:        D[ksi] = " << distribution::get_dispersion(nu, mu, lam)
				<< "; expected: sigma^2 * lambda^2 = 4.00"
				<< endl;
			cout << "Asymmetry coef.:   gamma1 = " << distribution::get_asymmetry(nu, mu, lam)
				<< "; expected: gamma1 = 0.0"
				<< endl;
			cout << "Excess coef.:      gamma2 = " << distribution::get_excess(nu, mu, lam)
				<< "; expected: gamma2 = 0.04"
				<< endl;
			cout << "P{x in central interval} =  " << distribution::get_P(nu)
				<< "; expected: 0.997"
				<< endl;

			plot_density(0, x, nu, mu, lam, 0, 0, 0, 0);

			return 1;
		}
		case 2: {
			cout << "Enter value of x: "; cin >> x;
			cout << "Enter value of shape parameter nu (nu > 0): "; cin >> nu;
			if (nu <= 0) {
				cout << "Incorrect value of nu (must be grater then 0)";
				return 0;
			}
			cout << "Enter value of shift parameter mu: "; cin >> mu;
			cout << "Enter value of scale parameter lambda (lambda > 0): "; cin >> lam;
			if (lam <= 0) {
				cout << "Incorrect value of lambda (must be grater then 0)";
				return 0;
			}

			cout << endl << "Result:" << endl;
			cout << "Density:              f(x) = " << distribution::get_density(x, nu, mu, lam) << endl;
			cout << "Expected value:     M[ksi] = " << distribution::get_expected_value(nu, mu, lam) << endl;
			cout << "Dispersion:         D[ksi] = " << distribution::get_dispersion(nu, mu, lam) << endl;
			cout << "Asymmetry coef.:    gamma1 = " << distribution::get_asymmetry(nu, mu, lam) << endl;
			cout << "Excess coef.:       gamma2 = " << distribution::get_excess(nu, mu, lam) << endl;
			cout << "P{x in central interval}  =  " << distribution::get_P(nu) << endl << endl;

			plot_density(0, x, nu, mu, lam, 0, 0, 0, 0);
			return 1;
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

	switch (switcher) {
		case 1: {
			mu1 = mu2 = x = 1.0; lam1 = lam2 = 2.0; nu1 = nu2 = 1.5; p = 0.3;
			cout << endl << "Trivial case. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameters nu1 = nu2 = " << nu1 << endl;
			cout << "Shift parameters mu1 = mu2 = " << mu1 << endl;
			cout << "Scale parameters lambda1 = lambda2 = " << lam1 << endl;
			cout << "Mixture parameter p = " << p << endl << endl;

			cout << "Results:" << endl;
			cout << "Density:              f(x) = " 
				<< mix_distribution::get_density(x, nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Expected value:     M[ksi] = " 
				<< mix_distribution::get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Dispersion:         D[ksi] = " 
				<< mix_distribution::get_dispersion(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Asymmetry coef.:    gamma1 = " 
				<< mix_distribution::get_asymmetry(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Excess coef.:       gamma2 = " 
				<< mix_distribution::get_excess(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl << endl;

			plot_density(1, x, nu1, mu1, lam1, nu2, mu2, lam2, p);


			mu1 = 0.0; mu2 = 2.0; lam1 = lam2 = 1.0; nu1 = nu2 = 2.0; p = 0.75; x = 0.0;
			cout << "Shift transformation. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameters nu1 = nu2 = " << nu1 << endl;
			cout << "Shift parameters mu1 = mu2 = " << mu1 << endl;
			cout << "Scale parameters lambda1 = lambda2 = " << lam1 << endl;
			cout << "Mixture parameter p = " << p << endl << endl;

			cout << "Results:" << endl;
			cout << "Density:             f(x) = " 
				<< mix_distribution::get_density(x, nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Expected value:    M[ksi] = " 
				<< mix_distribution::get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p) 
				<< "; expected: 1.5"
				<< endl;
			cout << "Dispersion:        D[ksi] = " 
				<< mix_distribution::get_dispersion(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Asymmetry coef.:   gamma1 = " 
				<< mix_distribution::get_asymmetry(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Excess coef.:      gamma2 = " 
				<< mix_distribution::get_excess(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl << endl;

			plot_density(1, x, nu1, mu1, lam1, nu2, mu2, lam2, p);


			mu1 = mu2 = 0.0; lam1 = 1.0; lam2 = 3.0; nu1 = nu2 = 2.5; p = 0.5;
			cout << "Scale transformation. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameters nu1 = nu2 = " << nu1 << endl;
			cout << "Shift parameters mu1 = mu2 = " << mu1 << endl;
			cout << "Scale parameters lambda1 = lambda2 = " << lam1 << endl;
			cout << "Mixture parameter p = " << p << endl << endl;

			cout << "Results:" << endl;
			cout << "Density:             f(x) = "
				<< mix_distribution::get_density(x, nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Expected value:    M[ksi] = "
				<< mix_distribution::get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p)
				<< "; expected: 0.0" << endl;
			cout << "Dispersion:        D[ksi] = "
				<< mix_distribution::get_dispersion(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Asymmetry coef.:   gamma1 = "
				<< mix_distribution::get_asymmetry(nu1, mu1, lam1, nu2, mu2, lam2, p) 
				<< "; expected: 0.0" << endl;
			cout << "Excess coef.:      gamma2 = "
				<< mix_distribution::get_excess(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl << endl;

			plot_density(1, x, nu1, mu1, lam1, nu2, mu2, lam2, p);


			mu1 = mu2 = 0.0; lam1 = lam2 = 1.0; nu1 = 1.0; nu2 = 2.0; p = 0.5;
			cout << "Different shape transformation. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameters nu1 = nu2 = " << nu1 << endl;
			cout << "Shift parameters mu1 = mu2 = " << mu1 << endl;
			cout << "Scale parameters lambda1 = lambda2 = " << lam1 << endl;
			cout << "Mixture parameter p = " << p << endl << endl;

			cout << "Results:" << endl;
			cout << "Density:             f(x) = "
				<< mix_distribution::get_density(x, nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Expected value:    M[ksi] = "
				<< mix_distribution::get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p)
				<< "; expected: 0.0" << endl;
			cout << "Dispersion:        D[ksi] = "
				<< mix_distribution::get_dispersion(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Asymmetry coef.:   gamma1 = "
				<< mix_distribution::get_asymmetry(nu1, mu1, lam1, nu2, mu2, lam2, p)
				<< "; expected: 0.0" << endl;
			cout << "Excess coef.:      gamma2 = "
				<< mix_distribution::get_excess(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;

			plot_density(1, x, nu1, mu1, lam1, nu2, mu2, lam2, p);


			return 1;
		}

		case 2: {
			cout << "Enter value of x: "; cin >> x;

			cout << "Enter value of shape parameter nu1 (nu1 > 0): "; cin >> nu1;
			if (nu1 <= 0) {
				cout << "Incorrect value of nu1 (must be grater then 0)" << endl;
				return 0;
			}

			cout << "Enter value of shape parameter nu2 (nu2 > 0): "; cin >> nu2;
			if (nu2 <= 0) {
				cout << "Incorrect value of nu2 (must be grater then 0)" << endl;
				return 0;
			}

			cout << "Enter value of shift parameter mu1: "; cin >> mu1;
			cout << "Enter value of shift parameter mu2: "; cin >> mu2;

			cout << "Enter value of scale parameter lambda1 (lambda1 > 0): "; cin >> lam1;
			if (lam1 <= 0) {
				cout << "Incorrect value of lambda1 (must be grater then 0)";
				return 0;
			}

			cout << "Enter value of scale parameter lambda2 (lambda2 > 0): "; cin >> lam2;
			if (lam2 <= 0) {
				cout << "Incorrect value of lambda2 (must be grater then 0)";
				return 0;
			}

			cout << "Enter value of mixture parameter P (0 <= P <= 1): "; cin >> p;
			if (p < 0 || p > 1) {
				cout << "Incorrect value of P (0 <= P <= 1)";
				return 0;
			}

			cout << "Results:" << endl;
			cout << "Density:             f(x) = "
				<< mix_distribution::get_density(x, nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Expected value:    M[ksi] = "
				<< mix_distribution::get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Dispersion:        D[ksi] = "
				<< mix_distribution::get_dispersion(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Asymmetry coef.:   gamma1 = "
				<< mix_distribution::get_asymmetry(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl;
			cout << "Excess coef.:      gamma2 = "
				<< mix_distribution::get_excess(nu1, mu1, lam1, nu2, mu2, lam2, p) << endl << endl;

			plot_density(1, x, nu1, mu1, lam1, nu2, mu2, lam2, p);
			return 1;
		}

		case 3: {
			return 0;
		}

		default:
			return 0;
	}
}