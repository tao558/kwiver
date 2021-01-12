#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "vital/types/category_hierarchy.h"




namespace py = pybind11;
void apb11_category_hierarchy_mod_category_hierarchy_py_register(py::module &m)
{
  static bool called = false;
  if(called) { return; }
  called = true;
  py::class_<::kwiver::vital::category_hierarchy> category_hierarchy(m, "category_hierarchy");

    
    category_hierarchy.def(py::init<>())
    .def(py::init<::std::string>(),py::arg("filename"))
    .def(py::init<::kwiver::vital::category_hierarchy::label_vec_t const &,::kwiver::vital::category_hierarchy::label_vec_t const &,::kwiver::vital::category_hierarchy::label_id_vec_t const &>(),py::arg("class_names"),py::arg("parent_names") = (::kwiver::vital::category_hierarchy::label_vec_t)kwiver::vital::category_hierarchy::label_vec_t(),py::arg("ids") = (::kwiver::vital::category_hierarchy::label_id_vec_t)kwiver::vital::category_hierarchy::label_id_vec_t())
    .def("add_class", static_cast<void ( ::kwiver::vital::category_hierarchy::* )( ::kwiver::vital::category_hierarchy::label_t const &,::kwiver::vital::category_hierarchy::label_t const &,::kwiver::vital::category_hierarchy::label_id_t const )>(&::kwiver::vital::category_hierarchy::add_class), py::arg("class_name"), py::arg("parent_name") = (::kwiver::vital::category_hierarchy::label_t)kwiver::vital::category_hierarchy::label_t(""), py::arg("id") = (::kwiver::vital::category_hierarchy::label_id_t const)kwiver::vital::category_hierarchy::label_id_t(-1))
    .def("has_class_name", static_cast<bool ( ::kwiver::vital::category_hierarchy::* )( ::kwiver::vital::category_hierarchy::label_t const & )const>(&::kwiver::vital::category_hierarchy::has_class_name), py::arg("class_name"))
    .def("get_class_name", static_cast<::kwiver::vital::category_hierarchy::label_t ( ::kwiver::vital::category_hierarchy::* )( ::kwiver::vital::category_hierarchy::label_t const & )const>(&::kwiver::vital::category_hierarchy::get_class_name), py::arg("class_name"))
    .def("get_class_id", static_cast<::kwiver::vital::category_hierarchy::label_id_t ( ::kwiver::vital::category_hierarchy::* )( ::kwiver::vital::category_hierarchy::label_t const & )const>(&::kwiver::vital::category_hierarchy::get_class_id), py::arg("class_name"))
    .def("get_class_parents", static_cast<::kwiver::vital::category_hierarchy::label_vec_t ( ::kwiver::vital::category_hierarchy::* )( ::kwiver::vital::category_hierarchy::label_t const & )const>(&::kwiver::vital::category_hierarchy::get_class_parents), py::arg("class_name"))
    .def("add_relationship", static_cast<void ( ::kwiver::vital::category_hierarchy::* )( ::kwiver::vital::category_hierarchy::label_t const &,::kwiver::vital::category_hierarchy::label_t const & )>(&::kwiver::vital::category_hierarchy::add_relationship), py::arg("child_name"), py::arg("parent_name"))
    .def("add_synonym", static_cast<void ( ::kwiver::vital::category_hierarchy::* )( ::kwiver::vital::category_hierarchy::label_t const &,::kwiver::vital::category_hierarchy::label_t const & )>(&::kwiver::vital::category_hierarchy::add_synonym), py::arg("class_name"), py::arg("synonym_name"))
    .def("all_class_names", static_cast<::kwiver::vital::category_hierarchy::label_vec_t ( ::kwiver::vital::category_hierarchy::* )(  )const>(&::kwiver::vital::category_hierarchy::all_class_names))
    .def("child_class_names", static_cast<::kwiver::vital::category_hierarchy::label_vec_t ( ::kwiver::vital::category_hierarchy::* )(  )const>(&::kwiver::vital::category_hierarchy::child_class_names))
    .def("size", static_cast<::size_t ( ::kwiver::vital::category_hierarchy::* )(  )const>(&::kwiver::vital::category_hierarchy::size))
    .def("load_from_file", static_cast<void ( ::kwiver::vital::category_hierarchy::* )( ::std::string const & )>(&::kwiver::vital::category_hierarchy::load_from_file), py::arg("filename"))
    
    
    ;
}
