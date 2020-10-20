include(FetchContent)
include("${KWIVER_CMAKE_DIR}/kwiver-setup-python.cmake")

FetchContent_Declare(
    autopybind11
    GIT_REPOSITORY https://gitlab.kitware.com/joe-snyder/autopybind11.git
    GIT_TAG d771570ea1579dd2959ed6463d942d8ea3718cd4
)

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

autopybind11_fetch_build_pybind11()

add_subdirectory(kwiver)
