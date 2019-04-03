#include "ImageBase.h"
#include <stdio.h>
#include "image_ppm.h"
#include "ImageBase.cpp"

int maximum(int x, int y, int z){

    if(x>=y){
        if(y>=z){
            return x;
        }else{
            if(x>=z){
                return x;
            }else{
                return z;
            }
        }
    }else{
        if(y>z){
            return y;
        }else{
            return z;
        }
    }
}



int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250], nomMasque[250];;
  
	if (argc != 4) 
	{
		printf("Usage: ImageIn.pgm masque.pgm ImageOut.pgm \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",nomMasque);
	sscanf (argv[3],"%s",cNomImgEcrite);

	
	//ImageBase imIn, imOut;
	ImageBase imIn, masque;
	imIn.load(cNomImgLue);
	masque.load(nomMasque);

    int max = 0, max2 = 0, max8 = 0;

	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for(int x = 0; x < imIn.getHeight(); ++x){


		for(int y = 0; y < imIn.getWidth(); ++y)
		{

			if(masque[x][y]==255){

				if(x==0 && (y!=0 || y==imIn.getWidth()-1)){

                    max = maximum(imIn[x][y-1],imIn[x+1][y-1],imIn[x+1][y]);
                    max2 = maximum(max,imIn[x+1][y+1],imIn[x][y+1]);
					imOut[x][y] = max2;

				}else if(y==0 && (x!=0 && x!=imIn.getHeight()-1)){

                    max = maximum(imIn[x-1][y],imIn[x-1][y+1],imIn[x][y+1]);
                    max2 = maximum(max,imIn[x+1][y+1],imIn[x+1][y]);
					imOut[x][y] = max2;

				}else if(x==imIn.getHeight()-1 && (y!=0 || y!=imIn.getWidth()-1)){

                    max = maximum(imIn[x][y-1],imIn[x-1][y-1],imIn[x-1][y]);
                    max2 = maximum(max,imIn[x-1][y+1],imIn[x][y+1]);
					imOut[x][y] = max2;
					
				}else if(y==imIn.getWidth()-1 && (x!=0 || x!=imIn.getHeight()-1)){

                    max = maximum(imIn[x-1][y],imIn[x-1][y-1],imIn[x][y-1]);
                    max2= maximum(max,imIn[x+1][y],imIn[x+1][y-1]);
					imOut[x][y] = max2;
				
				}else if(x==0 && y==0){

                    max = maximum(imIn[x][y+1],imIn[x+1][y+1],imIn[x+1][y]);
					imOut[x][y] = max;

				}else if(x==imIn.getHeight()-1 && y==0){

                    max = maximum(imIn[x-1][y],imIn[x-1][y+1],imIn[x+1][y+1]);
					imOut[x][y] = max;

				}else if(x==0 && y==imIn.getWidth()-1){

                    max = maximum(imIn[x][y-1],imIn[x+1][y-1],imIn[x+1][y]);
					imOut[x][y] = max;

				}else if(x==imIn.getHeight()-1 && y==imIn.getWidth()-1){

                    max = maximum(imIn[x][y-1],imIn[x-1][y],imIn[x-1][y-1]);
					imOut[x][y] = max;

				}else{

                    max = maximum(imIn[x][y-1],imIn[x][y+1],imIn[x-1][y-1]);
                    max2 = maximum(max,imIn[x-1][y],imIn[x-1][y+1]);
                    max8 = maximum(max2,imIn[x+1][y-1],imIn[x+1][y]);
                    if(max8>=imIn[x+1][y+1]){
					    imOut[x][y] = max8;
                    }else imOut[x][y] = imIn[x+1][y+1];
					
                }
			}else{
				imOut[x][y] = imIn[x][y];
			}
		}
	}
		
	imOut.save(cNomImgEcrite);
		



	return 0;
}
