On Ubuntu 16.04:

- Install gcc-7 and g++7
sudo add-apt-repository ppa:jonathonf/gcc-7.1
sudo apt-get update
sudo apt-get install gcc-7 g++-7

- Use gcc-7 and g++7 in CMake project by modifying
CMAKE_CXX_COMPILER="/usr/bin/g++-7"
CMAKE_C_COMPILER="/usr/bin/gcc-7"