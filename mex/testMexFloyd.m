G = dlmread('test/G.txt');
tic;
[dist, path] = mexFloyd(G);
toc;