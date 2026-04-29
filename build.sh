rm -rf build && rm nanotekspice
cmake -S . -B build && cmake --build build -j && cp build/nanotekspice .
