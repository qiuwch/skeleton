function runTest()
    close all;
    addpath plot
    binImage = imread('data/obj10_10.bmp');
    imshow(binImage);
    runSingleImage(binImage);
    pause;
end

function runMultipleImages()
    filenames = dir('data/*.bmp');
    filenames = {filenames.name};
    for filename = filenames
        close all;
        fullname = sprintf('data/%s', filename{1});
        binImage = imread(fullname);
        imshow(binImage);
        runSingleImage(binImage);
        pause;
    end
end

function runSingleImage(binImage)
    n = 500;
    points = sample(binImage, n);
    W = genGraph(points);
    G = pruneGraph(W, 5);
    dlmwrite('mex/G.txt', G);
    keyboard;
    
    %      r = 5;
    %      for r = 1:10
    %          G = pruneGraph(W, r);
    %          % G = pruneGraph(W, 5 * sqrt(2) + 0.1);
    %          visualizeConnectGraph(points, G);
    %      end
    
    % path = genPath(W, 5);
    % path = 1:length(points);

    G1 = G;
    [G, mid] = floyd(G1);
    % keyboard;

    path = cell(n, n);
    for i = 1:n
        disp(i);            
        tic
        for j = 1:i
            ijpath = getPath(G, mid, i, j);

            cost = sumPath(G1, ijpath, i, j);
            if cost ~= inf && G(i,j) ~= inf
                assert((cost - G(i,j) < 0.00001));
            end
            
            path{i,j} = ijpath;
            path{j,i} = fliplr(ijpath);
        end
        toc
    end
    keyboard;

%     dpMinDistance(G);
    path = genPointToPointPath(G, 1, 5);
    plotPath(points, path);
    path = genPointToPointPath(W, 1, 5);
    plotPath(points, path);
    
    % plotPoints(points, G);
end

function cost = sumPath(G1, path, i, j)
    startNode = [i, path];
    endNode = [path, j];
    idx = sub2ind(size(G1), startNode, endNode);
    singleCosts = G1(idx);
    cost = sum(singleCosts);
end
