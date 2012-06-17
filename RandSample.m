function points = RandSample(binImage, num)
    sz = size(binImage);
    h = sz(1);
    w = sz(2);
    
    points = zeros(num, 2);
    count = 0;
    while count ~= num
        y = randi(h, 1);
        x = randi(w, 1);
        
        if binImage(y, x) == 0
            count = count + 1;
            points(count, :) = [x, y];
        end
    end
end
