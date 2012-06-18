function TestFloyd()
    % load test data
    gt_G = dlmread('test/gt_G.txt');
    gt_min_distance = dlmread('test/gt_min_distance.txt');

    % performance of first algorithm
    tic;
    [min_distance_alg1, mid_point_alg1] = Floyd(gt_G);
    fprintf('Time of MATLAB floyd %f\n', toc);
    
    % verification for first algorithm
    CheckMatrix(gt_min_distance, min_distance_alg1, 0.01);
    
    % performance of second algorithm
    [min_distance_alg2, path_alg2] = mexFloyd(gt_G);
    fprintf('Time of mex floyd %f\n', toc);

    % verification of second algorithm
    CheckMatrix(min_distance_alg2, min_distance_alg1, 0.0001);
    
    sparse_G = sparse(gt_G);
    UG = tril(sparse_G);

    n = size(gt_G, 1);
    fprintf('Begin using dijkstra to verify algorithm result.\n');
    for i = 1:n
        for j = 1:n
            % check code
            [min_distance_alg3, path_alg3, ~] = graphshortestpath(UG, i, j, 'directed', false, 'Method', 'Dijkstra');
            
            if (min_distance_alg2(i,j) ~= inf && min_distance_alg3 ~= inf)
                assert(abs(min_distance_alg2(i,j) - min_distance_alg3) < 0.0001);
                % make sure mini distance is right.
            end
            
            ijpath = path_alg2{i,j};
            cost = SumPath(gt_G, ijpath);
            if cost ~= inf && min_distance_alg3 ~= inf
                assert((cost - min_distance_alg3 < 0.00001));
                % make sure path is right.
            elseif ~(cost == inf && min_distance_alg2(i,j) == inf)
                assert(false);
            end
        end
    end
    fprintf('Time of dijstra %f\n', toc);
end

function cost = SumPath(G, path)
    if isempty(path)
        cost = inf;
        return;
    end
    
    start_node = uint32(path(1:end-1));
    end_node = uint32(path(2:end));
    % because path is stored in uint16 array
    % if use sub2ind directly will come across 65536 problem.
    
    idx = sub2ind(size(G), start_node, end_node);
    
    single_cost = G(idx);
    cost = sum(single_cost);
end

function CheckMatrix(mat1, mat2, precision)
    n = size(mat1, 1);
    for i = 1:n
        for j = 1:n
            if (mat1(i,j) == inf && mat2(i,j) == inf)
                continue;
            elseif (abs(mat1(i,j) - mat2(i,j)) <= precision)
                continue;
            else
                assert(false);
            end
        end
    end
end

