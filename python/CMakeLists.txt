include(FetchContent)
include("${KWIVER_CMAKE_DIR}/kwiver-setup-python.cmake")

FetchContent_Declare(
    autopybind11
    GIT_REPOSITORY https://gitlab.kitware.com/john.parent/autopybind11.git
    GIT_TAG 1366d4ed421d42a05b4c70ec9fcb79be9e75af12
)
# 0e1b99030feaf3dee116143e37f77fea3cc83b1a
# Get autopybind all set here to be used in lower modules
FetchContent_MakeAvailable(autopybind11)
find_package(AutoPyBind11)

# Installs dependencies and locates
# AutoPyBind11 python scripts
execute_process(
    COMMAND
      ${PYTHON_EXECUTABLE} -m pip install
      ${autopybind11_SOURCE_DIR}
  )

# possible issue with APB grabing a pybind independent of fletch's pb
# pybind is a header only library, so this shouldnt result in an issue
# up front, but I believe both pybinds have the ability to grab different versions
# of python libs, which later will result in a linker error
autopybind11_fetch_build_pybind11()

add_subdirectory(kwiver)
