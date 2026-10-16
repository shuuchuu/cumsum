# rust-cumsum

*[English below](#english)*

La somme cumulée d'un tableau NumPy, écrite en Rust et appelée depuis Python.

- [`src/lib.rs`](src/lib.rs) : la fonction Rust `cumsum`, exposée avec
  [PyO3](https://pyo3.rs) (`#[pyfunction]`, `#[pymodule]`) dans le module d'extension
  `rust_cumsum._core`. Elle lit le tableau sans copie grâce à
  [rust-numpy](https://github.com/PyO3/rust-numpy) et rend un nouveau tableau NumPy.
- [`src/rust_cumsum/_core.pyi`](src/rust_cumsum/_core.pyi) : sa signature pour les
  vérificateurs de types et les éditeurs.
- [`src/rust_cumsum/__init__.py`](src/rust_cumsum/__init__.py) : la commande
  `rust-cumsum`, qui la chronomètre.
- [`pyproject.toml`](pyproject.toml) et [`Cargo.toml`](Cargo.toml) : le paquet Python,
  construit par [maturin](https://www.maturin.rs), et la bibliothèque Rust (`cdylib`).

## Prérequis

- [uv](https://docs.astral.sh/uv/getting-started/installation/) (il installe Python 3.13
  et maturin au besoin) ;
- la chaîne d'outils Rust, par [rustup](https://rustup.rs).

## Utilisation

```console
$ cd rust-cumsum
$ uv run rust-cumsum
27.1
```

`uv run` compile l'extension en mode release au premier lancement, puis à chaque
modification d'un fichier `.rs`, de `Cargo.toml` ou de `pyproject.toml`. La commande
affiche, en secondes, la durée de 10 000 appels sur un tableau d'un million de valeurs :
divisée par 10, c'est la durée d'un appel en millisecondes.

Depuis Python :

```console
$ uv run python -c "import numpy; from rust_cumsum._core import cumsum; print(cumsum(numpy.array([1.0, 2.0, 3.0])))"
[1. 3. 6.]
```

La fonction n'accepte que des tableaux de `float64` à une dimension :
`cumsum(numpy.array([1, 2, 3]))` lève une `TypeError` (convertir avec
`.astype(numpy.float64)`).

Pour la comparer à `numpy.cumsum` :

```console
$ uv run python -m timeit -s "import numpy; from rust_cumsum._core import cumsum; a = numpy.linspace(-1, 1, 1_000_000)" "cumsum(a)"
$ uv run python -m timeit -s "import numpy; a = numpy.linspace(-1, 1, 1_000_000)" "numpy.cumsum(a)"
```

## English

The cumulative sum of a NumPy array, written in Rust and called from Python.

- [`src/lib.rs`](src/lib.rs): the Rust `cumsum` function, exposed with
  [PyO3](https://pyo3.rs) (`#[pyfunction]`, `#[pymodule]`) in the `rust_cumsum._core`
  extension module. It reads the array without a copy through
  [rust-numpy](https://github.com/PyO3/rust-numpy) and returns a new NumPy array.
- [`src/rust_cumsum/_core.pyi`](src/rust_cumsum/_core.pyi): its signature, for type
  checkers and editors.
- [`src/rust_cumsum/__init__.py`](src/rust_cumsum/__init__.py): the `rust-cumsum`
  command, which times it.
- [`pyproject.toml`](pyproject.toml) and [`Cargo.toml`](Cargo.toml): the Python package,
  built by [maturin](https://www.maturin.rs), and the Rust library (`cdylib`).

### Requirements

- [uv](https://docs.astral.sh/uv/getting-started/installation/) (it installs Python 3.13
  and maturin when needed);
- the Rust toolchain, through [rustup](https://rustup.rs).

### Usage

```console
$ cd rust-cumsum
$ uv run rust-cumsum
27.1
```

`uv run` compiles the extension in release mode on the first run, then after every
change to a `.rs` file, `Cargo.toml` or `pyproject.toml`. The command prints, in
seconds, how long 10,000 calls on an array of a million values take: divided by 10, that
is one call's duration in milliseconds.

From Python:

```console
$ uv run python -c "import numpy; from rust_cumsum._core import cumsum; print(cumsum(numpy.array([1.0, 2.0, 3.0])))"
[1. 3. 6.]
```

The function only accepts one-dimensional `float64` arrays:
`cumsum(numpy.array([1, 2, 3]))` raises a `TypeError` (convert with
`.astype(numpy.float64)`).

To compare it with `numpy.cumsum`:

```console
$ uv run python -m timeit -s "import numpy; from rust_cumsum._core import cumsum; a = numpy.linspace(-1, 1, 1_000_000)" "cumsum(a)"
$ uv run python -m timeit -s "import numpy; a = numpy.linspace(-1, 1, 1_000_000)" "numpy.cumsum(a)"
```
