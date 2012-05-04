function shortest_path = dpMinDistance1(G)
    n = size(G, 1);
    G1 = G;
    G(G==inf) = 9999;
    

    tic;
    % begin of algorithm
    j = 1;

    i = 1;
    pi = i;
    ii = 0;
    pii = ii; 
    % means we are processing the pii node in the shortest path list
    while pii ~= n 
        % ii == n, means the last item has been processed
%         disp(ii);
        [val, idx] = sort(G(:,j), 'ascend');
        ii = find(idx == pi, 1);

        % G = update(G1, G, ii+1, pii, pi, idx, j);
        
        % fast update
        %{
        while ii < pii + 1
            % when ii == pii + 1, stop
            i = idx(ii);
%             disp(ii);
            G(i,j) = min(G(i, pi) + G(pi, j), G(i, j)); 
            % if inner update change order
            ii = ii + 1;
        end
        %}
        
        % ii = pii + 1; % if update finish, we can use this
        ii = ii + 1; % process from next item
        i = idx(ii);
        
        fprintf('Current distance to node %d is %f\n', i, val(ii));

        % choose the minimun distance each time
        for midi = 1:ii
            mid = idx(midi);
            G(i,j) = min(G1(i, mid) + G(mid, j), G(i, j));
        end
        
        pi = i;
        pii = ii;
    end
    toc

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


function G = update(G1, G, ii, pii, pi, idx, j)
% pii, the last element in list
% ii, the first element in list    
% pi, the updated node
    
    while ii < pii + 1
        i = idx(ii); % actual node index
        newval = G1(i, pi) + G(pi, j);
        if newval < G(i,j)
            G(i,j) = newval;
            [val, idx1] = sort(G(:,j), 'ascend');
            ii1 = find(idx1 == i, 1);
            G = update(G1, G, ii1+1, pii, i, idx1, j);
        end
        ii = ii + 1;
    end
end
