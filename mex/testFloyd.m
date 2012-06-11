function testFloyd()
    G = dlmread('test/G.txt');
    tic;
    [G1, next] = floyd(G);
    fprintf('Time of matlab floyd %f\n', toc);
    mid = dlmread('test/mid.txt');
    
    tic;
    [shortest_path_distance_matrix, path] = mexFloyd(G);
    fprintf('Time of mex floyd %f\n', toc);
    assert(all(all(mid == next)));
    
    euclidean_distance_matrix = sparse(G);
    UG = tril(euclidean_distance_matrix);

    n = size(G, 1);
    tic
    for i = 1:n
        for j = 1:n
            % check code
            [dist, gtpath, ~] = graphshortestpath(UG, i, j, 'directed', false, 'Method', 'Dijkstra');
            fprintf('Minimum distance: dijkstra %f, DP %f\n', dist, shortest_path_distance_matrix(i, j));
            
            if (shortest_path_distance_matrix(i,j) ~= inf && dist ~= inf)
                assert((shortest_path_distance_matrix(i,j) - dist) < 0.0001);
            end
            
            ijpath = path{i,j};
            cost = sumPath(G, ijpath, i, j);
            fprintf('Path distance from sum %f\n', cost);
            if cost ~= inf && shortest_path_distance_matrix(i,j) ~= inf
                assert((cost - shortest_path_distance_matrix(i,j) < 0.00001));
            elseif ~(cost == inf && shortest_path_distance_matrix(i,j) == inf)
                keyboard;
                assert(false);
            end
        end
    end
    fprintf('Time of dijstra %f', toc);
end

function cost = sumPath(G, path, i, j)
    startNode = uint32(path(1:end-1)); 
    endNode = uint32(path(2:end));
    idx = sub2ind(size(G), startNode, endNode);
    % because path is stored in uint16 array
    % if use sub2ind directly will come across 65536 problem.
    singleCosts = G(idx);
    cost = sum(singleCosts);
end

