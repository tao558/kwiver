include(FetchContent)
FetchContent_Declare(
    autopybind11
    GIT_REPOSITORY https://gitlab.kitware.com/autopybind11/autopybind11.git
    GIT_TAG f160da46e409e06e5bd760f4efae0b4e9b466d7f
)

# Get autopybind all set here to be used in lower modules
FetchContent_MakeAvailable(autopybind11)
find_package(AutoPyBind11)

autopybind11_fetch_build_pybind11()

add_subdirectory(kwiver)