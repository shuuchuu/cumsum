# cplusplus-cumsum

*[English below](#english)*

La somme cumulée d'un tableau NumPy, écrite en C++ et appelée depuis Python.

- [`src/main.cpp`](src/main.cpp) : la fonction C++ `cumsum`, exposée avec
  [pybind11](https://pybind11.readthedocs.io) (`PYBIND11_MODULE`) dans le module
  d'extension `cplusplus_cumsum._core`. Elle lit le tampon du tableau (`request()`) et
  écrit dans un nouveau tableau NumPy.
- [`src/cplusplus_cumsum/_core.pyi`](src/cplusplus_cumsum/_core.pyi) : sa signature pour
  les vérificateurs de types et les éditeurs.
- [`src/cplusplus_cumsum/__init__.py`](src/cplusplus_cumsum/__init__.py) : la commande
  `cplusplus-cumsum`, qui la chronomètre.
- [`pyproject.toml`](pyproject.toml) et [`CMakeLists.txt`](CMakeLists.txt) : le paquet
  Python, construit par [scikit-build-core](https://scikit-build-core.readthedocs.io), et
  la cible CMake de l'extension.

## Prérequis

- [uv](https://docs.astral.sh/uv/getting-started/installation/) (il installe Python
  3.13, pybind11 et scikit-build-core au besoin, ainsi que CMake et Ninja s'ils manquent) ;
- un compilateur C++ (g++ ou clang ; Visual Studio sous Windows).

## Utilisation

```console
$ cd cplusplus-cumsum
$ uv run cplusplus-cumsum
13.9
```

`uv run` compile l'extension au premier lancement, puis à chaque modification d'un
fichier C++ de `src/`, de `CMakeLists.txt` ou de `pyproject.toml`. La commande affiche,
en secondes, la durée de 10 000 appels sur un tableau d'un million de valeurs : divisée
par 10, c'est la durée d'un appel en millisecondes.

Depuis Python :

```console
$ uv run python -c "import numpy; from cplusplus_cumsum._core import cumsum; print(cumsum(numpy.array([1.0, 2.0, 3.0])))"
[1. 3. 6.]
```

pybind11 convertit au besoin le tableau en `float64` : un tableau d'entiers est accepté.
Un tableau à plusieurs dimensions lève une `RuntimeError`.

Pour la comparer à `numpy.cumsum` :

```console
$ uv run python -m timeit -s "import numpy; from cplusplus_cumsum._core import cumsum; a = numpy.linspace(-1, 1, 1_000_000)" "cumsum(a)"
$ uv run python -m timeit -s "import numpy; a = numpy.linspace(-1, 1, 1_000_000)" "numpy.cumsum(a)"
```

## English

The cumulative sum of a NumPy array, written in C++ and called from Python.

- [`src/main.cpp`](src/main.cpp): the C++ `cumsum` function, exposed with
  [pybind11](https://pybind11.readthedocs.io) (`PYBIND11_MODULE`) in the
  `cplusplus_cumsum._core` extension module. It reads the array's buffer (`request()`)
  and writes into a new NumPy array.
- [`src/cplusplus_cumsum/_core.pyi`](src/cplusplus_cumsum/_core.pyi): its signature,
  for type checkers and editors.
- [`src/cplusplus_cumsum/__init__.py`](src/cplusplus_cumsum/__init__.py): the
  `cplusplus-cumsum` command, which times it.
- [`pyproject.toml`](pyproject.toml) and [`CMakeLists.txt`](CMakeLists.txt): the Python
  package, built by [scikit-build-core](https://scikit-build-core.readthedocs.io), and the
  extension's CMake target.

### Requirements

- [uv](https://docs.astral.sh/uv/getting-started/installation/) (it installs Python 3.13,
  pybind11 and scikit-build-core when needed, and CMake and Ninja if they are missing);
- a C++ compiler (g++ or clang; Visual Studio on Windows).

### Usage

```console
$ cd cplusplus-cumsum
$ uv run cplusplus-cumsum
13.9
```

`uv run` compiles the extension on the first run, then after every change to a C++ file
of `src/`, `CMakeLists.txt` or `pyproject.toml`. The command prints, in seconds, how long
10,000 calls on an array of a million values take: divided by 10, that is one call's
duration in milliseconds.

From Python:

```console
$ uv run python -c "import numpy; from cplusplus_cumsum._core import cumsum; print(cumsum(numpy.array([1.0, 2.0, 3.0])))"
[1. 3. 6.]
```

pybind11 converts the array to `float64` when needed: an integer array is accepted. A
multi-dimensional array raises a `RuntimeError`.

To compare it with `numpy.cumsum`:

```console
$ uv run python -m timeit -s "import numpy; from cplusplus_cumsum._core import cumsum; a = numpy.linspace(-1, 1, 1_000_000)" "cumsum(a)"
$ uv run python -m timeit -s "import numpy; a = numpy.linspace(-1, 1, 1_000_000)" "numpy.cumsum(a)"
```
