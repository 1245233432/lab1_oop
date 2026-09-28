#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

#define PI 3.14159265358979323846

namespace distribution {

	double phi(double x); // вычисление плотности нормального распределения для данного x

	double Phi(double x); // вычисление значения функции нормального распределения для данного x (M(ksi) = 0, D(ksi) = 1)

	double get_K(double nu); // константа K из плотности распределения Хьюбера (важный мОмЭнТ: nu > 0)

	double get_P(double nu); // вероятность попадания в центральный интервал

	double get_random_value(double nu, double mu, double lam); // генерация случайного числа на промежутке (0, 1)

	double get_density(double x, double nu, double mu, double lam); // вычисление значения плотности для данного x

	double get_expected_value(double nu, double mu, double lam); // вычисление мат. ожидания

	double get_dispersion(double nu, double mu, double lam); // вычисление дисперсии

	double get_asymmetry(double nu, double mu, double lam); // вычисление асимметрии

	double get_excess(double nu, double mu, double lam); // вычисление эксцесса

}