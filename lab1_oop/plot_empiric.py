#!/usr/bin/env python3
"""
Строит график эмпирической плотности (ступенчатая гистограмма по формуле (1.4),
число промежутков - по формуле Стёрджеса) вместе с теоретической плотностью,
по CSV-файлу, сохранённому в test_empiric() (колонки: x,f_theor,f_emp).

Использование (из C++, интерактивно - открывает окно с графиком):
  python plot_empiric.py primary empiric_points_primary.csv 1.5 2.0 2.0
  python plot_empiric.py mixed   empiric_points_mixed.csv   1.0 0.0 1.0 2.0 3.0 1.5 0.4

Сохранение в файл вместо показа на экране (например, для отчёта):
  python plot_empiric.py primary empiric_points_primary.csv 1.5 2.0 2.0 --save out.png
"""
import sys
import csv
import math
import numpy as np


def phi(t):
    return math.exp(-0.5 * t * t) / math.sqrt(2.0 * math.pi)


def Phi(t):
    return 0.5 * (1.0 + math.erf(t / math.sqrt(2.0)))


def K(nu):
    return (2.0 / nu) * phi(nu) + 2.0 * Phi(nu) - 1.0


def huber_density(x, nu, mu, lam):
    z = (x - mu) / lam
    c = 1.0 / (K(nu) * lam * math.sqrt(2.0 * math.pi))
    if abs(z) <= nu:
        return c * math.exp(-0.5 * z * z)
    return c * math.exp(0.5 * nu * nu - nu * abs(z))


def mix_density(x, nu1, mu1, lam1, nu2, mu2, lam2, p):
    return (1.0 - p) * huber_density(x, nu1, mu1, lam1) + p * huber_density(x, nu2, mu2, lam2)


def get_k(n):
    return int(math.floor(math.log2(n))) + 1


def main():
    args = sys.argv[1:]

    save_path = None
    if "--save" in args:
        i = args.index("--save")
        save_path = args[i + 1]
        del args[i:i + 2]

    if save_path:
        import matplotlib
        matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    mode = args[0]
    csv_path = args[1]
    params = [float(a) for a in args[2:]]

    xs_sample = []
    with open(csv_path, newline="") as f:
        r = csv.DictReader(f)
        for row in r:
            xs_sample.append(float(row["x"]))

    n = len(xs_sample)
    k = get_k(n)
    x_min, x_max = min(xs_sample), max(xs_sample)
    h = (x_max - x_min) / k
    edges = [x_min + i * h for i in range(k + 1)]

    counts = [0] * k
    for x in xs_sample:
        idx = int((x - x_min) / h)
        if idx >= k:
            idx = k - 1
        if idx < 0:
            idx = 0
        counts[idx] += 1
    heights = [c / (n * h) for c in counts]

    left = x_min - 0.5 * (x_max - x_min)
    right = x_max + 0.5 * (x_max - x_min)
    xs = np.linspace(left, right, 600)

    if mode == "primary":
        nu, mu, lam = params
        ys = [huber_density(xi, nu, mu, lam) for xi in xs]
        title = f"Эмпирическая и теоретическая плотности - основное распределение\n(nu={nu}, mu={mu}, lambda={lam}, n={n}, k={k})"
        label_theor = f"теоретическая f(x), Хьюбер (nu={nu}, mu={mu}, lambda={lam})"
    else:
        nu1, mu1, lam1, nu2, mu2, lam2, p = params
        ys = [mix_density(xi, nu1, mu1, lam1, nu2, mu2, lam2, p) for xi in xs]
        title = (f"Эмпирическая и теоретическая плотности - смесь распределений\n"
                 f"(nu1={nu1}, mu1={mu1}, lambda1={lam1}; nu2={nu2}, mu2={mu2}, lambda2={lam2}; p={p}; n={n}, k={k})")
        label_theor = f"теоретическая f(x), смесь (p={p})"

    fig, ax = plt.subplots(figsize=(8, 4.8))
    ax.stairs(heights, edges, fill=True, alpha=0.35, color="#4C72B0",
              edgecolor="#4C72B0", linewidth=1.5, label="эмпирическая плотность f*(x)")
    ax.plot(xs, ys, color="#C44E52", linewidth=2, label=label_theor)
    ax.set_title(title, fontsize=11)
    ax.set_xlabel("x")
    ax.set_ylabel("f(x)")
    ax.legend(fontsize=9)
    ax.grid(True, alpha=0.3)
    fig.tight_layout()

    if save_path:
        fig.savefig(save_path, dpi=150)
        print("saved", save_path)
    else:
        plt.show()


if __name__ == "__main__":
    main()
