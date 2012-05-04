function path = genPointToPointPath(W, i, j)
    euclidean_distance_matrix = sparse(W);
    UG = tril(euclidean_distance_matrix);

    [dist, path, pred] = graphshortestpath(UG, i, j, 'directed', false, 'Method', 'Dijkstra');
end
