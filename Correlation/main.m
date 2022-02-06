
P1 = imread('3elson.jpg');
whos P1;
imshow(P1); title('First Image');
pause();

P2 = imread('resizedimage.jpg');
whos p2;
imshow(P2); title('Second Image');
pause();

[m n] = size(P1Gray);
[p q] = size(P2Gray);

for (i=1: m-p)
    
    for (j=1: n-q)
        
        corr(i,j) = Correlation(P2Gray, P1Gray( i:i+p-1 , j:j+q-1) );
      
    end
    
end

[num idx] = max(corr(:));
            [i j] = ind2sub(size(corr),idx);
        
            P1(i:i+p,j:j+10)=255;
            P1(i:i+10,j:j+q)=255;
            P1(i:i+p,j+q:j+q+10)=255;
            P1(i+p:i+p+10,j:j+q)=255;
 
                        num2=0;
            if(j-q/2<0)
               num2=q/2-j;
               floor(num2);
               num2=num2+1;
            end
           
            cero=zeros(p-num1,q-num2);
            corr(i-p/2+num1:i+p/2-1 , j-q/2+num2:j+q/2-1)=cero;
            
            cero1=zeros(p,q);
            corr(i:i+p-1 , j:j+q-1)=cero1;
            
 imshow(P1); title('First Image with drawed rectangles');           