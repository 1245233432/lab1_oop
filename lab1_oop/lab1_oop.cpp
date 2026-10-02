#include "distribution.hpp"
#include "mix_distribution.hpp"
#include "empiric_distribution.hpp"

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
int test_empiric();

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
		cout << "Error: plot.py returned code " << ret
			<< " (is python3/matplotlib available? is plot.py in cwd?)" << endl;
	}
}


int main() {
	srand(static_cast<unsigned int>(time(nullptr)));
	int switcher = -1;
	bool exit_flag = false;

	while (!exit_flag) {

		cout << endl << "--- Huber`s distribution ---" << endl;
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
	cout << "Enter your choice: " << endl; cin >> switcher; cout << endl;

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
			cout << endl;

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
			cout << endl;

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
			cout << endl;

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
			cout << endl;

			mu1 = 0.0; mu2 = 2.0; lam1 = lam2 = 1.0; nu1 = nu2 = 2.0; p = 0.75; x = 0.0;
			cout << "Shift transformation. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameters nu1 = nu2 = " << nu1 << endl;
			cout << "Shift parameters mu1 = " << mu1 << endl;
			cout << "Shift parameters mu2 = " << mu2 << endl;
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
			cout << endl;

			mu1 = mu2 = 0.0; lam1 = 1.0; lam2 = 3.0; nu1 = nu2 = 2.5; p = 0.5;
			cout << "Scale transformation. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameters nu1 = nu2 = " << nu1 << endl;
			cout << "Shift parameters mu1 = mu2 = " << mu1 << endl;
			cout << "Scale parameters lambda1 = " << lam1 << endl;
			cout << "Scale parameters lambda2 = " << lam2 << endl;
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
			cout << endl;

			mu1 = mu2 = 0.0; lam1 = lam2 = 1.0; nu1 = 1.0; nu2 = 2.0; p = 0.5;
			cout << "Different shape transformation. Data:" << endl;
			cout << "Argument x = " << x << endl;
			cout << "Shape parameters nu1 = " << nu1 << endl;
			cout << "Shape parameters nu2 = " << nu2 << endl;
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
			cout << endl;

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

int test_empiric() {
	int switcher;

	cout << endl << "1. Standart test set (samples generated from the primary/mixed distributions above)" << endl;
	cout << "2. Input from keyboard" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your choice: " << endl; cin >> switcher;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Wrong input" << endl;
		return 0;
	}
	else if (switcher < 1 || switcher > 3) {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Wrong input" << endl;
		return 0;
	}

	switch (switcher) {
		case 1: {
			int sizes[3] = { 300, 5000, 100000 }; // п. 3.3.1: "от нескольких сотен до ста тысяч элементов"

			// --- Блок 1: (нестандартное) основное распределение: мu != 0, lambda != 1 ---
			double nu = 1.5, mu = 2.0, lam = 2.0; // сдвиг-масштабное преобразование - не стандартное распределение

			cout << endl << "=== Primary (Huber) distribution, non-standard parameters ===" << endl;
			cout << "Shape parameter nu = " << nu << endl;
			cout << "Shift parameter mu = " << mu << endl;
			cout << "Scale parameter lambda = " << lam << endl << endl;

			double M_theor = distribution::get_expected_value(nu, mu, lam);
			double D_theor = distribution::get_dispersion(nu, mu, lam);
			double g1_theor = distribution::get_asymmetry(nu, mu, lam);
			double g2_theor = distribution::get_excess(nu, mu, lam);

			cout << "Theoretical characteristics:" << endl;
			cout << "M[ksi] = " << M_theor << "; D[ksi] = " << D_theor
				<< "; gamma1 = " << g1_theor << "; gamma2 = " << g2_theor << endl << endl;

			vector<double> small_sample; // выборка небольшого объема - понадобится ниже для графиков (п. 3.3.1) и повторной выборки (п. 3.3.2)

			for (int s = 0; s < 3; s++) {
				int n = sizes[s];
				vector<double> sample(n);
				for (int i = 0; i < n; i++) {
					sample[i] = distribution::get_random_value(nu, mu, lam); // моделирование основного распределения (пример 2.2)
				}

				double M_emp = empiric_distribution::get_expected_value(sample);
				double D_emp = empiric_distribution::get_dispersion(sample);
				double g1_emp = empiric_distribution::get_asymmetry(sample);
				double g2_emp = empiric_distribution::get_excess(sample);

				cout << "Sample size n = " << n << endl;
				cout << "Empirical M*      = " << M_emp << "; theoretical M      = " << M_theor << endl;
				cout << "Empirical D*      = " << D_emp << "; theoretical D      = " << D_theor << endl;
				cout << "Empirical gamma1* = " << g1_emp << "; theoretical gamma1 = " << g1_theor << endl;
				cout << "Empirical gamma2* = " << g2_emp << "; theoretical gamma2 = " << g2_theor << endl << endl;

				if (s == 0) {
					small_sample = sample;
				}
			}

			// п. 3.3.1: теоретическая и эмпирическая плотности в точках выборки малого объема (для графика, см. п. 5 задания)
			int k = empiric_distribution::get_k(static_cast<int>(small_sample.size()));
			cout << "Number of histogram intervals by Sturges' formula: k = " << k << endl;

			ofstream fout1("empiric_points_primary.csv");
			if (!fout1) {
				cout << "Warning: could not open empiric_points_primary.csv for writing" << endl;
			}
			else {
				fout1 << "x,f_theor,f_emp" << endl;
				for (size_t i = 0; i < small_sample.size(); i++) {
					double x = small_sample[i];
					double f_theor = distribution::get_density(x, nu, mu, lam);
					double f_emp = empiric_distribution::get_density(x, small_sample, k);
					fout1 << x << "," << f_theor << "," << f_emp << endl;
				}
				fout1.close();
				cout << "Theoretical and empirical density values at the sample points (n = " << small_sample.size()
					<< ") saved to empiric_points_primary.csv - use it to build the combined plot (p. 5 of the assignment)" << endl;
			}
			cout << endl;

			// п. 3.3.2: новая выборка того же объема, построенная по эмпирическому распределению выборки малого объема
			vector<double> new_sample = empiric_distribution::get_random_sample(small_sample, static_cast<int>(small_sample.size()));

			double M_emp0 = empiric_distribution::get_expected_value(small_sample);
			double D_emp0 = empiric_distribution::get_dispersion(small_sample);
			double g1_emp0 = empiric_distribution::get_asymmetry(small_sample);
			double g2_emp0 = empiric_distribution::get_excess(small_sample);

			double M_new = empiric_distribution::get_expected_value(new_sample);
			double D_new = empiric_distribution::get_dispersion(new_sample);
			double g1_new = empiric_distribution::get_asymmetry(new_sample);
			double g2_new = empiric_distribution::get_excess(new_sample);

			cout << "Resampling test (p. 3.3.2), sample size n = " << small_sample.size() << ":" << endl;
			cout << "                 original sample    new sample      theoretical" << endl;
			cout << "M*      = " << M_emp0 << "\t" << M_new << "\t" << M_theor << endl;
			cout << "D*      = " << D_emp0 << "\t" << D_new << "\t" << D_theor << endl;
			cout << "gamma1* = " << g1_emp0 << "\t" << g1_new << "\t" << g1_theor << endl;
			cout << "gamma2* = " << g2_emp0 << "\t" << g2_new << "\t" << g2_theor << endl << endl;

			// --- Блок 2: смесь двух основных распределений (п. 3.3.1 требует тестировать и смесь) ---
			double nu1 = 1.0, mu1 = 0.0, lam1 = 1.0;
			double nu2 = 2.0, mu2 = 3.0, lam2 = 1.5;
			double p = 0.4;

			cout << "=== Mixed distribution, some values of its parameters ===" << endl;
			cout << "nu1 = " << nu1 << ", mu1 = " << mu1 << ", lambda1 = " << lam1 << endl;
			cout << "nu2 = " << nu2 << ", mu2 = " << mu2 << ", lambda2 = " << lam2 << endl;
			cout << "p = " << p << endl << endl;

			double Mm_theor = mix_distribution::get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p);
			double Dm_theor = mix_distribution::get_dispersion(nu1, mu1, lam1, nu2, mu2, lam2, p);
			double g1m_theor = mix_distribution::get_asymmetry(nu1, mu1, lam1, nu2, mu2, lam2, p);
			double g2m_theor = mix_distribution::get_excess(nu1, mu1, lam1, nu2, mu2, lam2, p);

			cout << "Theoretical characteristics:" << endl;
			cout << "M[ksi] = " << Mm_theor << "; D[ksi] = " << Dm_theor
				<< "; gamma1 = " << g1m_theor << "; gamma2 = " << g2m_theor << endl << endl;

			vector<double> small_mix_sample;

			for (int s = 0; s < 3; s++) {
				int n = sizes[s];
				vector<double> sample(n);
				for (int i = 0; i < n; i++) {
					sample[i] = mix_distribution::get_random_value(nu1, mu1, lam1, nu2, mu2, lam2, p); // моделирование смеси (пример 2.5)
				}

				double M_emp = empiric_distribution::get_expected_value(sample);
				double D_emp = empiric_distribution::get_dispersion(sample);
				double g1_emp = empiric_distribution::get_asymmetry(sample);
				double g2_emp = empiric_distribution::get_excess(sample);

				cout << "Sample size n = " << n << endl;
				cout << "Empirical M*      = " << M_emp << "; theoretical M      = " << Mm_theor << endl;
				cout << "Empirical D*      = " << D_emp << "; theoretical D      = " << Dm_theor << endl;
				cout << "Empirical gamma1* = " << g1_emp << "; theoretical gamma1 = " << g1m_theor << endl;
				cout << "Empirical gamma2* = " << g2_emp << "; theoretical gamma2 = " << g2m_theor << endl << endl;

				if (s == 0) {
					small_mix_sample = sample;
				}
			}

			int km = empiric_distribution::get_k(static_cast<int>(small_mix_sample.size()));
			cout << "Number of histogram intervals by Sturges' formula: k = " << km << endl;

			ofstream fout2("empiric_points_mixed.csv");
			if (!fout2) {
				cout << "Warning: could not open empiric_points_mixed.csv for writing" << endl;
			}
			else {
				fout2 << "x,f_theor,f_emp" << endl;
				for (size_t i = 0; i < small_mix_sample.size(); i++) {
					double x = small_mix_sample[i];
					double f_theor = mix_distribution::get_density(x, nu1, mu1, lam1, nu2, mu2, lam2, p);
					double f_emp = empiric_distribution::get_density(x, small_mix_sample, km);
					fout2 << x << "," << f_theor << "," << f_emp << endl;
				}
				fout2.close();
				cout << "Theoretical and empirical density values at the sample points (n = " << small_mix_sample.size()
					<< ") saved to empiric_points_mixed.csv - use it to build the combined plot (p. 5 of the assignment)" << endl;
			}
			cout << endl;

			vector<double> new_mix_sample = empiric_distribution::get_random_sample(small_mix_sample, static_cast<int>(small_mix_sample.size()));

			double Mm_emp0 = empiric_distribution::get_expected_value(small_mix_sample);
			double Dm_emp0 = empiric_distribution::get_dispersion(small_mix_sample);
			double g1m_emp0 = empiric_distribution::get_asymmetry(small_mix_sample);
			double g2m_emp0 = empiric_distribution::get_excess(small_mix_sample);

			double Mm_new = empiric_distribution::get_expected_value(new_mix_sample);
			double Dm_new = empiric_distribution::get_dispersion(new_mix_sample);
			double g1m_new = empiric_distribution::get_asymmetry(new_mix_sample);
			double g2m_new = empiric_distribution::get_excess(new_mix_sample);

			cout << "Resampling test (p. 3.3.2), sample size n = " << small_mix_sample.size() << ":" << endl;
			cout << "                 original sample    new sample      theoretical" << endl;
			cout << "M*      = " << Mm_emp0 << "\t" << Mm_new << "\t" << Mm_theor << endl;
			cout << "D*      = " << Dm_emp0 << "\t" << Dm_new << "\t" << Dm_theor << endl;
			cout << "gamma1* = " << g1m_emp0 << "\t" << g1m_new << "\t" << g1m_theor << endl;
			cout << "gamma2* = " << g2m_emp0 << "\t" << g2m_new << "\t" << g2m_theor << endl << endl;

			return 1;
		}

		case 2: {
			int dist_switcher;
			int n;

			cout << endl << "Generate the initial sample from:" << endl;
			cout << "1. Primary distribution" << endl;
			cout << "2. Mixed distribution" << endl;
			cout << "Enter your choice: "; cin >> dist_switcher;

			if (cin.fail() || dist_switcher < 1 || dist_switcher > 2) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Wrong input" << endl;
				return 0;
			}

			cout << "Enter sample size n (n > 0): "; cin >> n;
			if (cin.fail() || n <= 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Incorrect value of n (must be grater then 0)" << endl;
				return 0;
			}

			vector<double> sample(n);
			double M_theor, D_theor, g1_theor, g2_theor;

			if (dist_switcher == 1) {
				double nu, mu, lam;
				cout << "Enter value of shape parameter nu (nu > 0): "; cin >> nu;
				if (nu <= 0) {
					cout << "Incorrect value of nu (must be grater then 0)" << endl;
					return 0;
				}
				cout << "Enter value of shift parameter mu: "; cin >> mu;
				cout << "Enter value of scale parameter lambda (lambda > 0): "; cin >> lam;
				if (lam <= 0) {
					cout << "Incorrect value of lambda (must be grater then 0)" << endl;
					return 0;
				}

				for (int i = 0; i < n; i++) {
					sample[i] = distribution::get_random_value(nu, mu, lam);
				}

				M_theor = distribution::get_expected_value(nu, mu, lam);
				D_theor = distribution::get_dispersion(nu, mu, lam);
				g1_theor = distribution::get_asymmetry(nu, mu, lam);
				g2_theor = distribution::get_excess(nu, mu, lam);
			}
			else {
				double nu1, mu1, lam1, nu2, mu2, lam2, p;
				cout << "Enter value of shape parameter nu1 (nu1 > 0): "; cin >> nu1;
				if (nu1 <= 0) { cout << "Incorrect value of nu1 (must be grater then 0)" << endl; return 0; }
				cout << "Enter value of shape parameter nu2 (nu2 > 0): "; cin >> nu2;
				if (nu2 <= 0) { cout << "Incorrect value of nu2 (must be grater then 0)" << endl; return 0; }
				cout << "Enter value of shift parameter mu1: "; cin >> mu1;
				cout << "Enter value of shift parameter mu2: "; cin >> mu2;
				cout << "Enter value of scale parameter lambda1 (lambda1 > 0): "; cin >> lam1;
				if (lam1 <= 0) { cout << "Incorrect value of lambda1 (must be grater then 0)" << endl; return 0; }
				cout << "Enter value of scale parameter lambda2 (lambda2 > 0): "; cin >> lam2;
				if (lam2 <= 0) { cout << "Incorrect value of lambda2 (must be grater then 0)" << endl; return 0; }
				cout << "Enter value of mixture parameter p (0 <= p <= 1): "; cin >> p;
				if (p < 0 || p > 1) { cout << "Incorrect value of p (0 <= p <= 1)" << endl; return 0; }

				for (int i = 0; i < n; i++) {
					sample[i] = mix_distribution::get_random_value(nu1, mu1, lam1, nu2, mu2, lam2, p);
				}

				M_theor = mix_distribution::get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p);
				D_theor = mix_distribution::get_dispersion(nu1, mu1, lam1, nu2, mu2, lam2, p);
				g1_theor = mix_distribution::get_asymmetry(nu1, mu1, lam1, nu2, mu2, lam2, p);
				g2_theor = mix_distribution::get_excess(nu1, mu1, lam1, nu2, mu2, lam2, p);
			}

			double M_emp = empiric_distribution::get_expected_value(sample);
			double D_emp = empiric_distribution::get_dispersion(sample);
			double g1_emp = empiric_distribution::get_asymmetry(sample);
			double g2_emp = empiric_distribution::get_excess(sample);
			int k = empiric_distribution::get_k(n);

			cout << endl << "Result (n = " << n << ", Sturges' k = " << k << "):" << endl;
			cout << "Empirical M*      = " << M_emp << "; theoretical M      = " << M_theor << endl;
			cout << "Empirical D*      = " << D_emp << "; theoretical D      = " << D_theor << endl;
			cout << "Empirical gamma1* = " << g1_emp << "; theoretical gamma1 = " << g1_theor << endl;
			cout << "Empirical gamma2* = " << g2_emp << "; theoretical gamma2 = " << g2_theor << endl;
			cout << "Empirical density at x = X_min: f*(X_min) = "
				<< empiric_distribution::get_density(empiric_distribution::get_min(sample), sample, k) << endl << endl;

			// п. 3.3.2: новая выборка того же объема по эмпирическому распределению полученной выборки
			vector<double> new_sample = empiric_distribution::get_random_sample(sample, n);
			double M_new = empiric_distribution::get_expected_value(new_sample);
			double D_new = empiric_distribution::get_dispersion(new_sample);
			double g1_new = empiric_distribution::get_asymmetry(new_sample);
			double g2_new = empiric_distribution::get_excess(new_sample);

			cout << "New sample of the same size, generated from the empirical distribution:" << endl;
			cout << "M*      = " << M_new << "; D*      = " << D_new
				<< "; gamma1* = " << g1_new << "; gamma2* = " << g2_new << endl;

			return 1;
		}

		case 3: {
			return 0;
		}

		default:
			return 0;
	}
}