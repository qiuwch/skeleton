function MarkFarthestPoints(points, dist)

n = length(points);
farPointsId = zeros(n, 1);
unreachAbleFlag = false(n, 1);
noInfDist = dist;
noInfDist(noInfDist == inf) = -1;
for i = 1:n
    % find longest point for each point
    pointDistance = noInfDist(i, :);
    [v, idx] = max(pointDistance);
    if v == 0 % this point is not reachable
        unreachAbleFlag(i) = 1; % mark this point unreachable
        % this idx is meaningless, because distance to every other node
        % set to 0
    end
    %       fprintf('i: %d to j: %d v: %f\n', i, idx, v);
    farPointsId(i) = idx;
end
borderPointsId = unique(farPointsId(~unreachAbleFlag));
%     unreachablePointsId = unique(farPointsId(unreachAbleFlag));
unreachablePointsId = unreachAbleFlag;
assert(all(find(unreachablePointsId) == unique(farPointsId(unreachAbleFlag))));

borderPoints = points(borderPointsId, :);
unreachablePoints = points(unreachablePointsId, :);

hold on;
PlotPoints(points, 'b');
PlotPoints(borderPoints, 'r');
PlotPoints(unreachablePoints, 'y');
end