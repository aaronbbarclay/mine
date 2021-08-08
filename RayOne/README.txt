Build instructions

# Setup the build
cmake . -DCMAKE_BUILD_TYPE=Debug -S . -B cmake-build

# Execute the build
cmake --build cmake-build

# Run the executable from the build directory
/cmake-build/raymondo