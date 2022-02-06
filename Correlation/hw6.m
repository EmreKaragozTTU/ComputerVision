smallImage1 = rgb2gray(imread('small1.png'));  
smallImage2 = rgb2gray(imread('small2.png'));
smallImage3 = rgb2gray(imread('small3.png'));
smallImage4 = rgb2gray(imread('small4.png'));
smallImage5 = rgb2gray(imread('small5.png'));
smallImage6 = rgb2gray(imread('small6.png'));
%smallImage7 = rgb2gray(imread('small7.png'));

bigImage = imread('3elson.jpg');
% smallImage = rgb2gray(imread('small.png'));

bigImage_grayScaled = rgb2gray(bigImage);
[m, n] = size(bigImage_grayScaled);


for N=1:7,
    
    currImage = sprintf('small%d.png', N);
    smallImage = rgb2gray(imread(currImage));
    
    [p, q] = size(smallImage);

    for i=1: m-p,
        for j=1: n-q,

            controlArea = bigImage( i:(i+p-1) , j:(j+q-1) );

            T1 = double(smallImage) - mean2(smallImage);
            I1 = double(controlArea) - mean2(controlArea);

            % 'norms' of T1 and I1
            nT = sqrt(sum(sum(T1.^2)));
            nI = sqrt(sum(sum(I1.^2)));

            correlateResult = sum(sum( T1.*I1))/(nT*nI);

            if( correlateResult > 0.7 )     % draw rectangle
                bigImage(i,j:j+q-1,1:2) = 255; 
                bigImage(i+p,j:j+q-1,1:2) = 255; 
                bigImage(i:i+p-1,j,1:2) = 255; 
                bigImage(i:i+p-1,j+q,1:2) = 255; 
            end        
        end
    end
end
imshow(bigImage);




















