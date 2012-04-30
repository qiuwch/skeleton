floyd = ../floyd.cc floyd_test.cc
dlmio = ../dlmio.cc
mexfloyd = ../mexFloyd.cc


test: floyd_test dlmio_test

floyd_test: $(floyd) $(dlmio)
	clang++ $(floyd) $(dlmio) -o floyd_test -Wall -g

dlmio_test:
	clang++ ../dlmio.cc dlmio_test.cc -o dlmio_test -g -Wall

