big = imread('big.png');
small = rgb2gray(imread('small.png'));

big_grayScaled = rgb2gray(big);
[m, n] = size(big_grayScaled);
   
[p, q] = size(small);
correlateResult=0;
correlateRes=0;
corResX=0;
corResY=0;
    for i=1: m-p,
        for j=1: n-q,

            controlArea = big( i:(i+p-1) , j:(j+q-1) );

            T1 = double(small) - mean2(small);
            I1 = double(controlArea) - mean2(controlArea);

            nT = sqrt(sum(sum(T1.^2)));
            nI = sqrt(sum(sum(I1.^2)));

            correlateResult = sum(sum( T1.*I1))/(nT*nI);

            if( correlateResult > correlateRes )
				correlateRes = correlateResult;
				corResX=i;
				corResY=j;
            end   

			
			
        end
    end
	
                big(corResX,corResY:corResY+q-1,1:2) = 128; 
                big(corResX+p,corResY:corResY+q-1,1:2) = 128; 
                big(corResX:corResX+p-1,corResY,1:2) = 128; 
                big(corResX:corResX+p-1,corResY+q,1:2) = 128; 	
	
imshow(big);



