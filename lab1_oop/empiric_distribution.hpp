#pragma once

#include <vector>
#include <stdexcept>

namespace empiric_distribution {

	double get_min(const std::vector<double>& sample); // минимальный элемент выборки X_min

	double get_max(const std::vector<double>& sample); // максимальный элемент выборки X_max

	int get_k(int n); // число промежутков гистограммы k по формуле Стёрджеса: k = [log2(n)] + 1

	double get_density(double x, const std::vector<double>& sample, int k = 0); // вычисление значения эмпирической плотности (1.4) для данного x; если k = 0 (не задано), число промежутков вычисляется по формуле Стёрджеса

	double get_expected_value(const std::vector<double>& sample); // вычисление выборочного (эмпирического) мат. ожидания M*

	double get_dispersion(const std::vector<double>& sample); // вычисление выборочной дисперсии D*

	double get_asymmetry(const std::vector<double>& sample); // вычисление выборочного коэффициента асимметрии

	double get_excess(const std::vector<double>& sample); // вычисление выборочного коэффициента эксцесса

	double get_random_value(const std::vector<double>& sample); // моделирование случайной величины, имеющей эмпирическое распределение (пример 2.3): выбор элемента исходной выборки с возвращением

	std::vector<double> get_random_sample(const std::vector<double>& sample, int new_n); // моделирование новой выборки объема new_n в соответствии с эмпирическим распределением исходной выборки (п. 3.3.2)

}
