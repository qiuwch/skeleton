function points = GridSample(binImage, interval)
    sz = size(binImage);
    h = sz(1);
    w = sz(2);
    [x, y] = meshgrid(1:interval:w, 1:interval:h);
    
    idx = sub2ind(sz, y, x);
    validIdx = (binImage(idx) == 0);
    x = x(validIdx);
    y = y(validIdx);

    figure;
    plot(x, y, '*');
    
    n = length(x);
    points = [x, y, zeros(n, 1)];
    % points = binImage(1:interval:h, 1:interval:w);
end