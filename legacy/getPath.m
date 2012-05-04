function path = getPath(G, next, i, j)
    if G(i,j) == inf
        path = [];
        return;
    end
    
    mid = next(i,j);
    if mid == 0
        path = [i,j];
        return;
    end
    
    left = getPath(G, next, i, mid);
    right = getPath(G, next, mid, j);
    path = [left mid right];
    return;
end