floyd = floyd.cc
dlmio = dlmio.cc
mexfloyd = mexFloyd.cc

matlab_floyd: $(floyd) $(mexfloyd) $(dlmio)
	# clang++ $(floyd) $(mexfloyd) $(dlmio) -I/home/qiuwch/opt/MATLAB/R2010b/extern/include/
	mex $(floyd) $(mexfloyd) $(dlmio)


default:
	make -C test/
