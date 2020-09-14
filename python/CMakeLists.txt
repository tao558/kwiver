include(FetchContent)
FetchContent_Declare(
    autopybind11
    GIT_REPOSITORY https://gitlab.kitware.com/autopybind11/autopybind11.git
    GIT_TAG f5d6e3d835171e95faf69a775ed3ede92f155f99
)

# Get autopybind all set here to be used in lower modules
FetchContent_MakeAvailable(autopybind11)
find_package(AutoPyBind11)

autopybind11_fetch_build_pybind11()

add_subdirectory(kwiver)