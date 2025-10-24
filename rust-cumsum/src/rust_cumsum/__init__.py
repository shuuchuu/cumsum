from timeit import timeit


def main() -> None:
    print(
        timeit(
            setup="import numpy; from rust_cumsum._core import cumsum; a = numpy.linspace(-1, 1, 1_000_000)",
            stmt="cumsum(a)",
            number=10_000,
        )
    )
