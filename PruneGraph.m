function G = pruneGraph(W, r)
    G = W;
    G(G>r) = inf;
end