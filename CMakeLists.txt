cmake_minimum_required(VERSION 3.7.2)
project(projet_neuron)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
add_subdirectory(gtest)
set(SOURCE_FILES
	mainNeuron.cpp
        Network.cpp
        Network.hpp
        neuron.cpp
        neuron.hpp)


include_directories(${gtest_SOURCE_DIR}/include${gtest_SOURCE_FILES})

add_executable(Neuron ${SOURCE_FILES})
add_executable(neuron_unittest neuron.cpp neuron_unittest.cpp)

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest neuron_unittest)