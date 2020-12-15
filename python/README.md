## How to add a new binding and requisite test:

Binding c++ in Python is implemented via the PyBind11 header only library
The documentation for which can be found [here](https://pybind11.readthedocs.io/en/stable/)

Upon the addition of a new c++ type/algo/sprokit etc, if appropriate, a binding file should be added to expose
the new piece of c++ to Python users.


-------------------------------------------------------------------------------------------------------------------

Depending on whether the new component of the c++ side is an algo, type, arrow, or sprokit, there is a corresponding
directory under the python/kwiver/ file substructure with both types and algo falling under python/kwiver/vital/
The binding file should be added under the appropriate directory, and with each addition to the python bindings
and entry must be made to the requisite CMakeLists, following the established conventions in each CMakeLists.


Bindings should be created following conventions already established in the existing binding code, whether than means creating a
header file or not, or how the c++ should be translated to be python compatible with respect to the breakdown of classes to modules/or python
classes. Additionally, the API created by the new c++ may not translate well to python or be interpreted properly by PyBind11, so a layer of abstraction
between PyBind11 and the C++ may be desireable.


Additionally templated classes and methods do not lend themselves to direct translation into Python very well.
There is a currently established method for implementing templating, and examples of this can be found in the pre existing bindings. The type bounding_box is a
great example of this.


Additionally, a unit test must be added or if appropriate, extended, for each added module/class/component added to the bindings
The tests are typically divided by python module at the file level.
