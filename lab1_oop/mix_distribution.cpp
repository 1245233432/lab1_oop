#include "mix_distribution.hpp"
#include <cstdlib>
#include <cmath>
#include <stdexcept>

using namespace std;

namespace mix_distribution {
	double get_random_value(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p) {
		if (nu1 <= 0 || nu2 <= 0 || p < 0 || p > 1) {
			throw invalid_argument("Incorrect parameters for mixed distribution");
		}

		double r;
		do {
			r = static_cast<double>(rand()) / RAND_MAX;
		} while (r == 0 || r == 1);

		if (r < p) {
			return distribution::get_random_value(nu2, mu2, lam2);
		}
		else {
			return distribution::get_random_value(nu1, mu1, lam1);
		}
	}

	double get_density(double x, double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p) {
		if (nu1 <= 0 || nu2 <= 0 || p < 0 || p > 1) {
			throw invalid_argument("Incorrect parameters for mixed distribution");
		}

		return (1.0 - p) * distribution::get_density(x, nu1, mu1, lam1) + p * distribution::get_density(x, nu2, mu2, lam2);
	}

	double get_expected_value(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p) {
		if (nu1 <= 0 || nu2 <= 0 || p < 0 || p > 1) {
			throw invalid_argument("Incorrect parameters for mixed distribution");
		}

		return (1.0 - p) * distribution::get_expected_value(nu1, mu1, lam1) + p * distribution::get_expected_value(nu2, mu2, lam2);
	}

	double get_dispersion(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p) {
		if (nu1 <= 0 || nu2 <= 0 || p < 0 || p > 1) {
			throw invalid_argument("Incorrect parameters for mixed distribution");
		}

		double M = get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p);
		double M1 = distribution::get_expected_value(nu1, mu1, lam1);
		double M2 = distribution::get_expected_value(nu2, mu2, lam2);
		double D1 = distribution::get_dispersion(nu1, mu1, lam1);
		double D2 = distribution::get_dispersion(nu2, mu2, lam2);

		return (1.0 - p) * (M1 * M1 + D1) + p * (M2 * M2 + D2) - (M * M);
	}

	double get_asymmetry(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p) {
		if (nu1 <= 0 || nu2 <= 0 || p < 0 || p > 1) {
			throw invalid_argument("Incorrect parameters for mixed distribution");
		}

		double M = get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p);
		double D = get_dispersion(nu1, mu1, lam1, nu2, mu2, lam2, p);
		if (D < 0) {
			return 0.0;
		}

		double M1 = distribution::get_expected_value(nu1, mu1, lam1);
		double M2 = distribution::get_expected_value(nu2, mu2, lam2);
		double D1 = distribution::get_dispersion(nu1, mu1, lam1);
		double D2 = distribution::get_dispersion(nu2, mu2, lam2);
		double gamma1_1 = distribution::get_asymmetry(nu1, mu1, lam1);
		double gamma1_2 = distribution::get_asymmetry(nu2, mu2, lam2);

		double a = (1.0 - p) * (pow(M1 - M, 3) + 3.0 * D1 * (M1 - M) + gamma1_1 * pow(D1, 1.5));
		double b = p * (pow(M2 - M, 3) + 3.0 * D2 * (M2 - M) + gamma1_2 * pow(D2, 1.5));

		return (a + b) / pow(D, 1.5);
	}

	double get_excess(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p) {
		if (nu1 <= 0 || nu2 <= 0 || p < 0 || p > 1) {
			throw invalid_argument("Incorrect parameters for mixed distribution");
		}

		double M = get_expected_value(nu1, mu1, lam1, nu2, mu2, lam2, p);
		double D = get_dispersion(nu1, mu1, lam1, nu2, mu2, lam2, p);
		if (D < 0) {
			return 0.0;
		}

		double M1 = distribution::get_expected_value(nu1, mu1, lam1);
		double M2 = distribution::get_expected_value(nu2, mu2, lam2);
		double D1 = distribution::get_dispersion(nu1, mu1, lam1);
		double D2 = distribution::get_dispersion(nu2, mu2, lam2);
		double gamma1_1 = distribution::get_asymmetry(nu1, mu1, lam1);
		double gamma1_2 = distribution::get_asymmetry(nu2, mu2, lam2);
		double gamma2_1 = distribution::get_excess(nu1, mu1, lam1);
		double gamma2_2 = distribution::get_excess(nu2, mu2, lam2);

		double a = (1.0 - p) * (pow(M1 - M, 4) 
			+ 6.0 * D1 * pow(M1 - M, 2) 
			+ 4.0 * gamma1_1 * pow(D1, 1.5) * (M1 - M) 
			+ D1 * D1 * (gamma2_1 + 3));
		double b = p * (pow(M2 - M, 4)
			+ 6.0 * D2 * pow(M2 - M, 2)
			+ 4.0 * gamma1_2 * pow(D2, 1.5) * (M2 - M)
			+ D2 * D2 * (gamma2_2 + 3));

		return ((a + b) / pow(D, 2)) - 3;
	}
}