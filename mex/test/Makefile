floyd = ../floyd.cc floyd_test.cc
dlmio = ../dlmio.cc
mexfloyd = ../mexFloyd.cc


test: floyd_test1 dlmio_test

floyd_test1: $(floyd) $(dlmio)
	clang++ $(floyd) $(dlmio) -o floyd_test1 -Wall -g

floyd_test2: $(floyd) $(dlmio)
	g++ $(floyd) $(dlmio) -o floyd_test2 -Wall -O3

dlmio_test:
	clang++ ../dlmio.cc dlmio_test.cc -o dlmio_test -g -Wall

