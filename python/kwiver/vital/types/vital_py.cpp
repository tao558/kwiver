#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

py::module apb11_camera_perspective_vital_py_register(py::module &m)
{
  py::module vital = m.def_submodule("vital", "");
  
  return vital;
}
