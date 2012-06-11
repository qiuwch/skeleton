function MarkPointsInPath(points, mid)    
    PlotPoints(points, 'b');
    hold on;
    midpointid = unique(mid);
    midpointid(midpointid==0) = [];
    midpoints = points(midpointid, :);
    PlotPoints(midpoints, 'r');
end