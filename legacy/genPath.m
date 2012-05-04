function genPath(euclidean_distance_matrix, radius)
    euclidean_distance_matrix(find(euclidean_distance_matrix > radius)) = 0;
    
    euclidean_distance_matrix = sparse(euclidean_distance_matrix);
    
    UG = tril(euclidean_distance_matrix);
    
%     shortest_path_distance_matrix = graphallshortestpaths(UG, 'directed', false);
    
    virtex_num = size(euclidean_distance_matrix, 1);
    shortest_path = cell(virtex_num, virtex_num);
    shortest_path_distance_matrix = zeros(virtex_num, virtex_num);
    
    for i = 1:virtex_num
        for j = 1:virtex_num
            %
            tic;
            [dist, path, pred] = graphshortestpath(UG, i, j, 'directed', false, 'Method', 'Dijkstra');
            toc;
            shortest_path{i, j} = path;
            shortest_path{j, i} = fliplr(path);
            
            shortest_path_distance_matrix(i, j) = dist;
            shortest_path_distance_matrix(i, j) = dist;
        end
    end
end
