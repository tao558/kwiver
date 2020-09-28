include(FetchContent)
FetchContent_Declare(
    autopybind11
    GIT_REPOSITORY https://gitlab.kitware.com/autopybind11/autopybind11.git
    GIT_TAG 9f31bc3dd9bfd3afeb5823cb1cd0ee46709a12cd
)

# Get autopybind all set here to be used in lower modules
FetchContent_MakeAvailable(autopybind11)
find_package(AutoPyBind11)

# Installs dependencies and locates
# AutoPyBind11 python scripts
execute_process(
    COMMAND
      ${Python_EXECUTABLE} -m pip install
      ${autopybind11_SOURCE_DIR}
  )

autopybind11_fetch_build_pybind11()

add_subdirectory(kwiver)
