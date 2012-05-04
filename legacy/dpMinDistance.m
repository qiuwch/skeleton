function shortest_path = dpMinDistance(G)
    n = size(G, 1);
    G1 = G;
    G(G==inf) = 9999;
    
    j = 1;
    tic;
    % start of algorithm
    [val, idx] = sort(G(:,j), 'ascend');
    for ii = 1:length(idx)
        disp(ii);
        i = idx(ii);
        for midi = 1:ii-1
            mid = idx(midi);
            G(i,j) = min(G1(i, mid) + G(mid, j), G(i, j));
        end
        
        G = update(G, G1, ii-1, j, G(i,j), i, idx);
    end
    % end of algorithm
    toc
    pause
    
    euclidean_distance_matrix = sparse(G);
    UG = tril(euclidean_distance_matrix);
    for ii = 1:n
        [val, idx] = sort(G(:,j), 'ascend');
        i = idx(ii);
        % check code
        [dist, path, pred] = graphshortestpath(UG, i, j, 'directed', false, 'Method', 'Dijkstra');
        fprintf('Minimum distance: dijkstra %f, DP %f\n', dist, G(i, j));
        assert((G(i,j) - dist) < 0.01);
    end
    
    keyboard;
end

function G = update(G, G1, ii, j, dist, mid, idx)
% ii, size of existing graph
% j, destination
% dist, distance threshold    
% update graph
    iis = 1:ii;
    % the order of update matters
    inneris1 = idx(iis)';
    
    subgraph = G(inneris1, j);

    inneris = idx(iis(subgraph > dist))';
    
    if ii ~= 0 && ~isempty(inneris)
        assert(max(inneris) <= max(idx(ii)));
    end
    assert(dist == G(mid, j));
    if (length(inneris) > 1)
        tmpd = G(inneris, j);
%         keyboard;
    end

%     [val, sortidx] = sort(G(inneris, j), 'ascend');
%     inneris = inneris(sortidx);
    
    %     inneriis = find(G(inneriis, j) > dist)';
    for inneri = inneris  % from the smallest value
        newval = G1(inneri, mid) + G(mid, j);
        if newval < G(inneri, j);
            % if shortest path updated
            G(inneri, j) = newval;
            G = update(G, G1, ii, j, G(inneri, j), inneri, idx);
        end
    end
end
