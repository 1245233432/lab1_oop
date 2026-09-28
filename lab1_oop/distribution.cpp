#include "distribution.hpp"
#include <cmath>
#include <cstdlib>
#include <stdexcept>

using namespace std;

namespace distribution {

	double phi(double x) {
		return exp(-0.5 * x * x) / sqrt(2.0 * PI);
	}

	double Phi(double x) {
		return 0.5 * (1.0 + erf(x / sqrt(2.0)));
	}

	double get_K(double nu) {
		if (nu <= 0) {
			throw invalid_argument("Parameter nu must be grater then 0");
		}
		return (2.0 / nu) * phi(nu) + 2.0 * Phi(nu) - 1;
	}

	double get_P(double nu) {
		double K = get_K(nu);
		return (2.0 * Phi(nu) - 1) / K;
	}

	static double generate_standart(double nu) { // функция, использующаяся только в этом файле и не объявленная в заголовочном файле, так что целесообразно будет дописать ключевое слово static, которое обеспечит видимость этой функции только в данном файле 
		if (nu <= 0) {
			throw invalid_argument("Parameter nu must be grater then 0");
		}

		double P = get_P(nu);
		double r1; // r1 заранее задать не можем, поэтому используем цикл с постусловием (do - while), чтобы тело выполнилось хотя бы раз
		do {
			r1 = static_cast<double>(rand()) / RAND_MAX;
		} while (r1 == 0.0 || r1 == 1);

		if (r1 <= P) {
			while (true) {
				double r2, r3;
				do { r2 = static_cast<double>(rand()) / RAND_MAX; } while (r2 == 0 || r2 == 1);
				do { r3 = static_cast<double>(rand()) / RAND_MAX; } while (r3 == 0 || r3 == 1);

				double x1 = sqrt(-2.0 * log(r2)) * cos(2.0 * PI * r3);

				if (fabs(x1) <= nu) { // интрестинг открытие: фабс работает с дабл, а абс - с интом.
					return x1;
				}
			}
			
		}

		double r4; 
		do {
			r4 = static_cast<double>(rand()) / RAND_MAX;
		} while (r4 == 0.0 || r4 == 1);

		double x2 = nu - (log(r4) / nu);
		
		if (r1 < (1.0 + P) / 2.0) {
			return x2;
		}
		else {
			return -x2;
		}
	}

	double get_random_value(double nu, double mu, double lam) {
		if (nu <= 0) {
			throw invalid_argument("Parameter nu must be grater then 0");
		}
		if (lam <= 0) { // лямбда тоже должна быть больше нуля, т.к. при нуле задача не имеет смысла, а при отрицательном значении получим отрицательное значение вероятности, что тоже не имеет смысла
			throw invalid_argument("Parameter lambda must be grater then 0");
		}

		double x = generate_standart(nu);

		return mu + x * lam;
	}

	double get_density(double x, double nu, double mu, double lam) {
		if (nu <= 0) {
			throw invalid_argument("Parameter nu must be grater then 0");
		}
		if (lam <= 0) {
			throw invalid_argument("Parameter lambda must be grater then 0");
		}

		double z = (x - mu) / lam;
		double k = get_K(nu);
		double c = 1.0 / (k * lam * sqrt(2.0 * PI));

		if (fabs(z) <= nu) {
			return c * exp(-0.5 * z * z);
		}
		else {
			return c * exp(nu * nu * 0.5 - nu * fabs(z));
		}
	}

	double get_expected_value(double nu, double mu, double lam) {
		if (nu <= 0) {
			throw invalid_argument("Parameter nu must be grater then 0");
		}
		if (lam <= 0) {
			throw invalid_argument("Parameter lambda must be grater then 0");
		}

		return mu;
	}

	double get_dispersion(double nu, double mu, double lam) {
		if (nu <= 0) {
			throw invalid_argument("Parameter nu must be grater then 0");
		}
		if (lam <= 0) {
			throw invalid_argument("Parameter lambda must be grater then 0");
		}

		double k = get_K(nu);
		double sigma = 1.0 + (2.0 * phi(nu) * (nu * nu + 2.0) / nu * nu * nu * k);

		return lam * lam * sigma;
	}

	double get_asymmetry(double nu, double mu, double lam) {
		if (nu <= 0) {
			throw invalid_argument("Parameter nu must be grater then 0");
		}
		if (lam <= 0) {
			throw invalid_argument("Parameter lambda must be grater then 0");
		}

		return 0.0; // так как распределение симметрично
	}

	double get_excess(double nu, double mu, double lam) {
		if (nu <= 0) {
			throw invalid_argument("Parameter nu must be grater then 0");
		}
		if (lam <= 0) {
			throw invalid_argument("Parameter lambda must be grater then 0");
		}

		double K = get_K(nu);
		double sigma2 = 1.0 + (2.0 * phi(nu) * (nu * nu + 2.0) / nu * nu * nu * k);
		double sigma4 = sigma2 * sigma2;

		double a = 24.0 / (nu * nu * nu * nu * nu);
		double b = 24.0 / (nu * nu * nu);
		double c = 12.0 / nu;

		double gamma2 = (1.0 / sigma4 * k) * (3.0 * (2.0 * Phi(nu) - 1) + 2.0 * phi(nu) * (a + b + c + nu)) - 3.0;
		return gamma2;
	}
}