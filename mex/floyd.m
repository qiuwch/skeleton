function [G, next] = floyd(G1)
    n = size(G1, 1);
    G = G1;
    next = zeros(size(G));
    for k = 1:n
        disp(k);
        for i = 1:n
            for j = 1:n
                if G(i,k) + G(k,j) < G(i,j)
                    G(i,j) = G(i,k) + G(k,j);
                    next(i,j) = k;
                end
            end
        end
    end
end

