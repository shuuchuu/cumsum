#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

// Compute cumsum on a NumPy array (1D)
py::array_t<double> cumsum(py::array_t<double> input) {
    // Request buffer info from numpy array
    py::buffer_info buf = input.request();

    if (buf.ndim != 1)
        throw std::runtime_error("cumsum only supports 1D arrays");

    // Get input pointer and size
    auto *ptr = static_cast<double *>(buf.ptr);
    ssize_t n = buf.shape[0];

    // Allocate output array of same shape
    py::array_t<double> result(buf.shape[0]);
    py::buffer_info res_buf = result.request();
    auto *res_ptr = static_cast<double *>(res_buf.ptr);

    // Perform cumulative sum
    if (n > 0) {
        res_ptr[0] = ptr[0];
        for (ssize_t i = 1; i < n; i++)
            res_ptr[i] = res_ptr[i - 1] + ptr[i];
    }

    return result;
}

PYBIND11_MODULE(_core, m) {
    m.doc() = "C++ cumsum example using pybind11";

    m.def("cumsum", &cumsum, R"pbdoc(
        Compute the cumulative sum (cumsum) of a 1D NumPy array.
        Example:
            >>> import _core
            >>> _core.cumsum(np.array([1, 2, 3]))
            array([1., 3., 6.])
    )pbdoc");
}
