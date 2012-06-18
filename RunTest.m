function runTest()
    close all;
    addpath plot;
    addpath mex;
    addpath func;
    binImage = imread('obj10_10.bmp');

    runSingleImage(binImage);
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
    end
end

function runSingleImage(binImage)
    figBinImage = figure();
    imshow(binImage);
    n = 500;
    points = RandSample(binImage, n);
    
    W = GenGraph(points);
    G = PruneGraph(W, 5);
    
    [dist, path, mid] = mexFloyd(G);

    % Plot all shortest path
    figSamplePoints = figure();
    PlotPoints(points, 'b');
    %     hold on;
    %     x = [];
    %     y = [];
    %{ Draw path, useless
    %     for i = 1:n
    %         for j = i:n
    %             if isempty(path{i,j})
    %                 fprintf('Empty path! Point %d is not reachable\n', j);
    %                 plot(points(j,1), points(j, 2), 'y*');
    %             end
    %             p = path{i, j};
    %             x = [x; nan; points(p, 1)];
    %             y = [y; nan; points(p, 2)];
    %             PlotPath(points, path{i, j});
    %             disp(path{i, j});
    %         end
    %         disp(i);
    %         pause;
    %     end
    %     line(x, y);
    %     pause;
    %}

    figPathPoint = figure;
    MarkPointsInPath(points, mid);
    figFarthestPoint = figure;
    MarkFarthestPoints(points, dist);

    figure(figBinImage);
    print('-dpng', 'binImage.png');
    figure(figSamplePoints);
    print('-dpng', 'sampledPoints.png');
    figure(figPathPoint);
    print('-dpng', 'pathPoint.png');
    figure(figFarthestPoint);
    print('-dpng', 'farPoint.png');
end

