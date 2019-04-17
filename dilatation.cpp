#include "ImageBase.h"
#include <stdio.h>
#include "image_ppm.h"
#include "ImageBase.cpp"

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
  
	if (argc != 3) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for(int x = 0; x < imIn.getHeight(); ++x)

		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			if (imIn[x][y] == 0) {
				if(x==0 && (y!=0 || y==imIn.getWidth()-1)){
					imOut[x][y] = 0;
					imOut[x][y-1] = 0;
					imOut[x][y+1] = 0;
					imOut[x+1][y-1] = 0;
					imOut[x+1][y] = 0;
					imOut[x+1][y+1] = 0;
				}else if(y==0 && (x!=0 && x!=imIn.getHeight()-1)){
					imOut[x][y] = 0;
					imOut[x][y+1] = 0;
					imOut[x-1][y] = 0;
					imOut[x-1][y+1] = 0;
					imOut[x+1][y] = 0;
					imOut[x+1][y+1] = 0;
				}else if(x==imIn.getHeight()-1 && (y!=0 || y!=imIn.getWidth()-1)){
					imOut[x][y] = 0;
					imOut[x][y-1] = 0;
					imOut[x][y+1] = 0;
					imOut[x-1][y-1] = 0;
					imOut[x-1][y] = 0;
					imOut[x-1][y+1] = 0;
				}else if(y==imIn.getWidth()-1 && (x!=0 || x!=imIn.getHeight()-1)){
					imOut[x][y] = 0;
					imOut[x][y-1] = 0;
					imOut[x-1][y-1] = 0;
					imOut[x-1][y] = 0;
					imOut[x+1][y-1] = 0;
					imOut[x+1][y] = 0;
				}else if(x==0 && y==0){
					imOut[x][y] = 0;
					imOut[x][y+1] = 0;
					imOut[x+1][y+1] = 0;
					imOut[x+1][y] = 0;
				}else if(x==imIn.getHeight()-1 && y==0){
					imOut[x][y] = 0;
					imOut[x-1][y] = 0;
					imOut[x-1][y+1] = 0;
					imOut[x+1][y+1] = 0;
				}else if(x==0 && y==imIn.getWidth()-1){
					imOut[x][y] = 0;
					imOut[x][y-1] = 0;
					imOut[x+1][y-1] = 0;
					imOut[x+1][y] = 0;
				}else if(x==imIn.getHeight()-1 && y==imIn.getWidth()-1){
					imOut[x][y] = 0;
					imOut[x][y-1] = 0;
					imOut[x-1][y] = 0;
					imOut[x-1][y-1] = 0;
				}else{
					imOut[x][y] = 0;
					imOut[x][y-1] = 0;
					imOut[x][y+1] = 0;
					imOut[x-1][y-1] = 0;
					imOut[x-1][y] = 0;
					imOut[x-1][y+1] = 0;
					imOut[x+1][y-1] = 0;
					imOut[x+1][y] = 0;
					imOut[x+1][y+1] = 0;
				}
			}else{
				imOut[x][y] = 255;
			}
		}
		
	imOut.save(cNomImgEcrite);
		



	return 0;
}
