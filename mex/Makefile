floyd = floyd.cc
dlmio = dlmio.cc
mexfloyd = mexFloyd.cc

matlab_floyd: $(floyd) $(mexfloyd) $(dlmio)
	# clang++ $(floyd) $(mexfloyd) $(dlmio) -I/home/qiuwch/opt/MATLAB/R2010b/extern/include/
	# mex $(mexfloyd) $(floyd) $(dlmio) -O
	clang++ -c  -I/home/qiuwch/opt/MATLAB/R2010b/extern/include -I/home/qiuwch/opt/MATLAB/R2010b/simulink/include -DMATLAB_MEX_FILE -ansi -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC -pthread  -DMX_COMPAT_32 -O3 -DNDEBUG  "mexFloyd.cc"
	clang++ -c  -I/home/qiuwch/opt/MATLAB/R2010b/extern/include -I/home/qiuwch/opt/MATLAB/R2010b/simulink/include -DMATLAB_MEX_FILE -ansi -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC -pthread  -DMX_COMPAT_32 -O3 -DNDEBUG  "floyd.cc"
	clang++ -c  -I/home/qiuwch/opt/MATLAB/R2010b/extern/include -I/home/qiuwch/opt/MATLAB/R2010b/simulink/include -DMATLAB_MEX_FILE -ansi -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC -pthread  -DMX_COMPAT_32 -O3 -DNDEBUG  "dlmio.cc"
	clang++ -O3 -pthread -shared -m32 -Wl,--version-script,/home/qiuwch/opt/MATLAB/R2010b/extern/lib/glnx86/mexFunction.map -Wl,--no-undefined -o  "mexFloyd.mexglx"  mexFloyd.o floyd.o dlmio.o  -Wl,-rpath-link,/home/qiuwch/opt/MATLAB/R2010b/bin/glnx86 -L/home/qiuwch/opt/MATLAB/R2010b/bin/glnx86 -lmx -lmex -lmat -lm



default:
	make -C test/
