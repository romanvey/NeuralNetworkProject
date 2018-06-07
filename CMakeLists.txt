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
        "threads/*.h"
        "threads/*.cpp"
        )

file(GLOB mpi_files
        "mpi/*.h"
        "mpi/*.cpp"
        )

# Example of usage of our library
add_executable(test_nn ${src_nn_files} ${threads_files} ${mpi_files} tests/test_nn.cpp tests/test_nn.h)
add_executable(test_utils ${src_utils_files} tests/test_utils.cpp tests/test_utils.h)
add_executable(test_threads ${threads_files} tests/test_threads.cpp)
add_executable(test_mpi ${mpi_files} tests/test_mpi.cpp)

target_link_libraries (test_nn Eigen3::Eigen ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (test_utils Eigen3::Eigen)
target_link_libraries (test_threads Eigen3::Eigen ${CMAKE_THREAD_LIBS_INIT})