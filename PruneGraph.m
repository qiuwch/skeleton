function G = PruneGraph(W, r)
    G = W;
    G(G>r) = inf;
end