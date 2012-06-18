addpath ..
bin_image = imread('../obj10_10.bmp');
n = 500;
points = RandSample(bin_image, n);
W = GenGraph(points);
G = PruneGraph(W, 5);
% make weight between very close points not zero.
diag = sub2ind(size(G), 1:size(G, 1), 1:size(G, 2));
G(G == 0) = 0.0001;
G(diag) = 0;

dlmwrite('test/gt_G.txt', G);

% use dijstra algorithm to generate ground truth
G(G==inf) = 0;
sparse_G = sparse(G);
UG = tril(sparse_G);

min_distance = graphallshortestpaths(UG,'Directed', false);
dlmwrite('test/gt_min_distance.txt', min_distance);