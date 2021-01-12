
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

void apb11_category_hierarchy_mod_category_hierarchy_py_register(py::module &model);

PYBIND11_EXPORT void apb11_category_hierarchy_mod_register_types(py::module &model)
{
// make sure this module is only initialized once
static bool called = false;
if(called) { return; }
called = true;

// initialize class for module category_hierarchy_mod
apb11_category_hierarchy_mod_category_hierarchy_py_register(model);

};

PYBIND11_MODULE(category_hierarchy_mod, model)
{
// First initialize dependent modules
// then this module.
apb11_category_hierarchy_mod_register_types(model);

}

