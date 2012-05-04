function plotPath(points, path)
    figure;
    plot(points(:, 1), points(:, 2), '*b');
    for i = 1:length(path)-1
        hold on;
        idx1 = path(i);
        idx2 = path(i+1);
        p = points([idx1, idx2], :);
        plot(p(:, 1), p(:, 2));
    end
end
