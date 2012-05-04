function plotPoints(points, G)
    plot(points(:, 1), points(:, 2), '*b');
    nn = sum(G ~= inf);    
    
    maxn = max(nn);
    fprintf('nearest neighbour count %d, ideally 8\n', maxn);
    
    figure;
    idx = (nn > 0);
    plot(points(idx, 1), points(idx, 2), '*r');
    title('All points');
    
    figure;
    idx = (nn < maxn);
    plot(points(idx, 1), points(idx, 2), '*r');
    title('Boarder points');
end
