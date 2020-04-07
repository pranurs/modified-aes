%% histogram
clc
clear 

image = uint8(importdata("mickeyMAES3.txt"));
figure 
imshow(image);
nr = size(image,1);
nc = size(image,2);

histo = zeros(256, 1);

for i = 1:nr
    for j = 1:nc
        x = image(i,j)+1;
        histo(x,1) = histo(x) + 1;
    end
end
figure
plot1 = subplot(1,1,1);
stem(histo, "or");
xlabel(plot1, "Intensity Values");
ylabel(plot1, "No. of pixels");

%% entropy
Pm = histo ./ (nr*nc);
n = find(Pm ~= 0);
H = sum(Pm(n) .* log2(1./Pm(n)));