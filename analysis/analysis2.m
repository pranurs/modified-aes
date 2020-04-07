    %% Correlation
    clc
    clear
    image = uint8(importdata("mickeyMAES3.txt"));
    nr = size(image,1);
    nc = size(image,2);
    imageAdj = uint8(zeros(nr-1,nc-1));

    for i = 1:(nr-1)
        for j = 1:(nc-1)
            imageAdj(i,j) = image(i,j+1); ...  horizontally adjacent 
                                          ... =image(i+1,j); vertically adjacent
        end 
    end

    image = double(reshape(image(1:(nr-1), 1:(nc-1)), [(nr-1)*(nc-1),1]));
    imageAdj = double(reshape(imageAdj, [(nr-1)*(nc-1),1]));
    plot(image, imageAdj, ".b");
    title("Correlation of Horizontally adjacent values");

    %% Correlation Coeffecient
    Ex = mean(image);
    Ey = mean(imageAdj);
    covM = cov(image, imageAdj);
    covariance = covM(1,2);
    Dx = (sum((image-Ex).^2))./length(image);
    Dy = (sum((image-Ey).^2))./length(image);
    rxy = covariance/(sqrt(Dx)*sqrt(Dy));
