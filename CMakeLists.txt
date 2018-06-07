cmake_minimum_required (VERSION 3.0)
project (NeuralNetworkProject)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package (Threads)
set(CMAKE_CXX_STANDARD 14)

file(GLOB src_nn_files
	"src/*.h"
    "src/*.cpp"
)

 file(GLOB src_utils_files
     "utils/*.h"
     "utils/*.cpp"
 )

file(GLOB threads_files
        "thread/*.h"
        "thread/*.cpp"
        )

# Example of usage of our library
 add_executable(test_nn ${src_nn_files} ${threads_files})
# add_executable(test_utils ${src_utils_files})
#add_executable(test_mm thread/test_mm.cpp thread/threads_multiplication.h thread/threads_multiplication.cpp)
#add_executable(mm playground/mm.cpp)

 target_link_libraries (test_nn Eigen3::Eigen ${CMAKE_THREAD_LIBS_INIT})
# target_link_libraries (test_utils Eigen3::Eigen)
#target_link_libraries (test_mm Eigen3::Eigen ${CMAKE_THREAD_LIBS_INIT})