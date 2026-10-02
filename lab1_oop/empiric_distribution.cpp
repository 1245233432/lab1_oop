#include "empiric_distribution.hpp"
#include <cmath>
#include <cstdlib>
#include <stdexcept>

using namespace std;

namespace empiric_distribution {

	double get_min(const vector<double>& sample) {
		if (sample.empty()) {
			throw invalid_argument("Sample must not be empty");
		}

		double x_min = sample[0];
		for (size_t i = 1; i < sample.size(); i++) {
			if (sample[i] < x_min) {
				x_min = sample[i];
			}
		}
		return x_min;
	}

	double get_max(const vector<double>& sample) {
		if (sample.empty()) {
			throw invalid_argument("Sample must not be empty");
		}

		double x_max = sample[0];
		for (size_t i = 1; i < sample.size(); i++) {
			if (sample[i] > x_max) {
				x_max = sample[i];
			}
		}
		return x_max;
	}

	int get_k(int n) { // формула Стёрджеса: k = [log2(n)] + 1, где [.] - целая часть
		if (n <= 0) {
			throw invalid_argument("Sample size must be grater then 0");
		}

		return static_cast<int>(floor(log2(static_cast<double>(n)))) + 1;
	}

	static int get_bin_index(double x, double x_min, double h, int k) { // функция, используемая только в этом файле: номер промежутка (от 0 до k-1), которому принадлежит x
		int i = static_cast<int>((x - x_min) / h);

		if (i >= k) { // правая граница X_max и значения, совпадающие с ней, относим к последнему промежутку (он единственный включает правый конец)
			i = k - 1;
		}
		if (i < 0) { // на случай погрешностей вычислений с плавающей точкой у левой границы
			i = 0;
		}
		return i;
	}

	double get_density(double x, const vector<double>& sample, int k) {
		int n = static_cast<int>(sample.size());
		if (n == 0) {
			throw invalid_argument("Sample must not be empty");
		}

		if (k == 0) { // число промежутков не задано явно - используем значение по умолчанию (формула Стёрджеса)
			k = get_k(n);
		}
		if (k <= 0) {
			throw invalid_argument("Number of intervals k must be grater then 0");
		}

		double x_min = get_min(sample);
		double x_max = get_max(sample);

		if (x < x_min || x > x_max) { // вне промежутка X = [X_min, X_max] эмпирическая плотность равна нулю
			return 0.0;
		}

		double h = (x_max - x_min) / k; // длина одного промежутка
		if (h <= 0) { // все элементы выборки совпадают - гистограмму построить нельзя
			throw invalid_argument("Sample is degenerate: X_max must be grater then X_min");
		}

		int idx = get_bin_index(x, x_min, h, k);

		int ni = 0; // количество элементов выборки, попавших в тот же промежуток, что и x
		for (int j = 0; j < n; j++) {
			if (get_bin_index(sample[j], x_min, h, k) == idx) {
				ni++;
			}
		}

		return static_cast<double>(ni) / (n * h); // формула (1.4)
	}

	double get_expected_value(const vector<double>& sample) {
		int n = static_cast<int>(sample.size());
		if (n == 0) {
			throw invalid_argument("Sample must not be empty");
		}

		double sum = 0.0;
		for (int i = 0; i < n; i++) {
			sum += sample[i];
		}
		return sum / n;
	}

	double get_dispersion(const vector<double>& sample) {
		int n = static_cast<int>(sample.size());
		if (n == 0) {
			throw invalid_argument("Sample must not be empty");
		}

		double M = get_expected_value(sample);
		double sum = 0.0;
		for (int i = 0; i < n; i++) {
			sum += (sample[i] - M) * (sample[i] - M);
		}
		return sum / n;
	}

	double get_asymmetry(const vector<double>& sample) {
		int n = static_cast<int>(sample.size());
		if (n == 0) {
			throw invalid_argument("Sample must not be empty");
		}

		double M = get_expected_value(sample);
		double D = get_dispersion(sample);
		if (D <= 0) { // при нулевой выборочной дисперсии коэффициент асимметрии не определен
			return 0.0;
		}

		double sum = 0.0;
		for (int i = 0; i < n; i++) {
			sum += pow(sample[i] - M, 3);
		}
		return (sum / n) / pow(D, 1.5);
	}

	double get_excess(const vector<double>& sample) {
		int n = static_cast<int>(sample.size());
		if (n == 0) {
			throw invalid_argument("Sample must not be empty");
		}

		double M = get_expected_value(sample);
		double D = get_dispersion(sample);
		if (D <= 0) { // при нулевой выборочной дисперсии коэффициент эксцесса не определен
			return 0.0;
		}

		double sum = 0.0;
		for (int i = 0; i < n; i++) {
			sum += pow(sample[i] - M, 4);
		}
		return (sum / n) / (D * D) - 3.0;
	}

	double get_random_value(const vector<double>& sample) { // пример 2.3: выбор элемента исходной выборки с возвращением
		int n = static_cast<int>(sample.size());
		if (n == 0) {
			throw invalid_argument("Sample must not be empty");
		}

		int index = rand() % n;
		return sample[index];
	}

	vector<double> get_random_sample(const vector<double>& sample, int new_n) {
		if (sample.empty()) {
			throw invalid_argument("Sample must not be empty");
		}
		if (new_n <= 0) {
			throw invalid_argument("New sample size must be grater then 0");
		}

		vector<double> new_sample(new_n);
		for (int i = 0; i < new_n; i++) {
			new_sample[i] = get_random_value(sample);
		}
		return new_sample;
	}

}
