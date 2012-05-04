function visualizeConnectGraph(points, G)
    figure;
    n = length(points);
    for i = 1:n
        for j = 1:n
            if G(i, j) ~= inf
                p1 = points(i, :);
                p2 = points(j, :);

                hold on;
                plot([p1(1) p2(1)], [p1(2) p2(2)]); 
            end
        end
    end
end

