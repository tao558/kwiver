#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

py::module apb11_camera_perspective_kwiver_py_register(py::module &m)
{
  py::module kwiver = m.def_submodule("kwiver", "");
  
  return kwiver;
}
