#pragma once

#include "distribution.hpp"
#include <vector>
#include <iostream>

namespace mix_distribution {
	double get_random_value(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p); // генерация случайного числа на промежутке (0, 1)

	double get_density(double x, double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p); // вычисление значения плотности для данного x

	double get_expected_value(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p); // вычисление мат. ожидания

	double get_dispersion(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p); // вычисление дисперсии

	double get_asymmetry(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p); // вычисление асимметрии

	double get_excess(double nu1, double mu1, double lam1, double nu2, double mu2, double lam2, double p); // вычисление эксцесса
}