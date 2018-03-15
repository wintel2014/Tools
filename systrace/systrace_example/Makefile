INCLUDE=-I /usr/src/kernels/3.10.0-229.el7.x86_64/include/
all:
	g++ main.cpp $(INCLUDE)  -lpthread -o trace_test -g3 -O0 -std=c++14

run:
	sudo env LD_LIBRARY_PATH=D_LIBRARY_PATH:/opt/Apps/local/gcc-5.3.0/lib64/:/usr/local/lib/ ./trace_test

