#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib.pyplot as plt
from math import erf, sqrt, exp, pi


def phi(t):
    return exp(-0.5 * t * t) / sqrt(2.0 * pi)


def Phi(t):
    return 0.5 * (1.0 + erf(t / sqrt(2.0)))


def K(nu):
    return (2.0 / nu) * phi(nu) + 2.0 * Phi(nu) - 1.0


def huber_density(x, nu, mu, lam):
    z = (x - mu) / lam
    c = 1.0 / (K(nu) * lam * sqrt(2.0 * pi))
    if abs(z) <= nu:
        return c * exp(-0.5 * z * z)
    return c * exp(0.5 * nu * nu - nu * abs(z))


def mix_density(x, nu1, mu1, lam1, nu2, mu2, lam2, p):
    return (1.0 - p) * huber_density(x, nu1, mu1, lam1) + p * huber_density(x, nu2, mu2, lam2)


def main():
    if len(sys.argv) < 10:
        print("Usage: python3 plot.py flag x nu1 mu1 lam1 nu2 mu2 lam2 p")
        sys.exit(1)

    flag = int(float(sys.argv[1]))
    x_mark = float(sys.argv[2])
    nu1 = float(sys.argv[3])
    mu1 = float(sys.argv[4])
    lam1 = float(sys.argv[5])
    nu2 = float(sys.argv[6])
    mu2 = float(sys.argv[7])
    lam2 = float(sys.argv[8])
    p = float(sys.argv[9])


    centers = [mu1]
    scales = [lam1]
    if flag == 1:
        centers.append(mu2)
        scales.append(lam2)
    left = min(c - 6.0 * s for c, s in zip(centers, scales))
    right = max(c + 6.0 * s for c, s in zip(centers, scales))
    xs = np.linspace(left, right, 500)

    plt.figure(figsize=(9, 5))

    if flag == 0:
        ys = [huber_density(xi, nu1, mu1, lam1) for xi in xs]
        plt.plot(xs, ys, color="blue", linewidth=2,
                 label=f"Huber  ν={nu1}, μ={mu1}, λ={lam1}")
        y_mark = huber_density(x_mark, nu1, mu1, lam1)
        title = f"Хьюбер  (ν={nu1}, μ={mu1}, λ={lam1})"
    else:
        ys = [mix_density(xi, nu1, mu1, lam1, nu2, mu2, lam2, p) for xi in xs]
        plt.plot(xs, ys, color="blue", linewidth=2,
                 label=f"Смесь  p={p}")

        y1 = [huber_density(xi, nu1, mu1, lam1) for xi in xs]
        y2 = [huber_density(xi, nu2, mu2, lam2) for xi in xs]
        plt.plot(xs, [(1 - p) * yi for yi in y1], "--", color="green",
                 alpha=0.7, label=f"(1-p)·f1  ν={nu1}, μ={mu1}, λ={lam1}")
        plt.plot(xs, [p * yi for yi in y2], "--", color="orange",
                 alpha=0.7, label=f"p·f2  ν={nu2}, μ={mu2}, λ={lam2}")
        y_mark = mix_density(x_mark, nu1, mu1, lam1, nu2, mu2, lam2, p)
        title = (f"Смесь Хьюбера  (ν1={nu1}, μ1={mu1}, λ1={lam1}; "
                 f"ν2={nu2}, μ2={mu2}, λ2={lam2}; p={p})")

    plt.scatter([x_mark], [y_mark], color="red", zorder=5, s=40,
                label=f"f({x_mark:g}) = {y_mark:.4f}")

    plt.title(title)
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.legend()
    plt.grid(True, alpha=0.4)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
