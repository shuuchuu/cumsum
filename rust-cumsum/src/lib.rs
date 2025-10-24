use numpy::{IntoPyArray, PyArray1, PyReadonlyArray1};
use pyo3::prelude::*;

/// Compute cumulative sum (cumsum) of a 1D NumPy array.
///
/// Example:
/// ```python
/// import numpy as np
/// import _core
/// _core.cumsum(np.array([1, 2, 3]))  # array([1., 3., 6.])
/// ```
#[pyfunction]
fn cumsum(py: Python<'_>, input: PyReadonlyArray1<f64>) -> Py<PyArray1<f64>> {
    let input_slice = input.as_slice().expect("input must be contiguous");

    let mut result = Vec::with_capacity(input_slice.len());
    let mut running_sum = 0.0;

    for &val in input_slice {
        running_sum += val;
        result.push(running_sum);
    }

    // Convert to PyArray1 and then into Py<PyArray1>
    result.into_pyarray(py).into()
}

#[pymodule]
fn _core(m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(cumsum, m)?)?;
    Ok(())
}
