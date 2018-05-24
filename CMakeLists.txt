cmake_minimum_required (VERSION 3.0)
project (NeuralNetworkProject)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
set(CMAKE_CXX_STANDARD 14)

file(GLOB src_nn_files
    "src/*.h"
    "src/*.cpp"
)

file(GLOB src_utils_files
    "src/*.h"
    "src/*.cpp"
)

# Example of usage of our library
add_executable(test_nn ${src_nn_files})
add_executable(utils_test ${src_utils_files})

target_link_libraries (test_nn Eigen3::Eigen)
target_link_libraries (utils_test Eigen3::Eigen)
