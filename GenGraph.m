function W = genGraph(points)
    pointCoordinate = points(:, 1:2);
    n = length(pointCoordinate);
    W = zeros(n, n);
    for i = 1:n
        p = pointCoordinate(i, :);
        diff = pointCoordinate - repmat(p, n, 1);
        dist = sqrt(sum(diff .^ 2, 2));
        W(i, :) = dist;
    end
    assert(all(all(W == W')));
end