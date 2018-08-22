all:
	g++ src/main.cpp -std=c++17 -lX11 -s -Os

llvm:
	clang++ src/main.cpp -std=c++17 -lX11 -s -Os
