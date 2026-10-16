# cumsum

*[English below](#english)*

La somme cumulée d'un tableau NumPy à une dimension, écrite dans un langage compilé et
appelée depuis Python : la démonstration des formations Python de
[shuuchuu](https://github.com/shuuchuu) sur l'interfaçage avec d'autres langages.

| Dossier | Langage | Liaison | Construction |
| --- | --- | --- | --- |
| [`rust-cumsum`](rust-cumsum) | Rust | [PyO3](https://pyo3.rs) et [rust-numpy](https://github.com/PyO3/rust-numpy) | [maturin](https://www.maturin.rs) |
| [`cplusplus-cumsum`](cplusplus-cumsum) | C++ | [pybind11](https://pybind11.readthedocs.io) | [scikit-build-core](https://scikit-build-core.readthedocs.io) (CMake) |

Chaque dossier est un projet [uv](https://docs.astral.sh/uv/) autonome : son README dit
comment le construire, l'appeler et le chronométrer.

## English

The cumulative sum of a one-dimensional NumPy array, written in a compiled language and
called from Python: the demonstration of [shuuchuu](https://github.com/shuuchuu)'s Python
courses on interfacing with other languages.

| Folder | Language | Binding | Build |
| --- | --- | --- | --- |
| [`rust-cumsum`](rust-cumsum) | Rust | [PyO3](https://pyo3.rs) and [rust-numpy](https://github.com/PyO3/rust-numpy) | [maturin](https://www.maturin.rs) |
| [`cplusplus-cumsum`](cplusplus-cumsum) | C++ | [pybind11](https://pybind11.readthedocs.io) | [scikit-build-core](https://scikit-build-core.readthedocs.io) (CMake) |

Each folder is a self-contained [uv](https://docs.astral.sh/uv/) project: its README
explains how to build it, call it and time it.
