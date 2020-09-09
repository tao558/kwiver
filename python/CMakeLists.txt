include(FetchContent)
FetchContent_Declare(
    autopybind11
    GIT_REPOSITORY https://gitlab.kitware.com/autopybind11/autopybind11.git
)

# Get autopybind all set here to be used in lower modules
FetchContent_MakeAvailable(autopybind11)
find_package(AutoPyBind11)

find_package(pybind11)

autopybind11_fetch_build_pybind11(PYBIND11_DIR ${pybind11_root})

add_subdirectory(kwiver)