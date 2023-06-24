# CMakeList.txt : CMake project for Kalkulator_MSV2, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Kalkulator_MSV2 "Main_Kalkulator_V1.cpp" "Kalkulator_MS.h" "Kalkulator_MS.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Kalkulator_MSV2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
