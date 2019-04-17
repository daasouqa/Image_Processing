#include "ImageBase.h"
#include <stdio.h>
#include "image_ppm.h"
#include "ImageBase.cpp"

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250], cNomImgDil[250];
  
	if (argc != 4) 
	{
		printf("Usage: ImageIn.pgm ImageDil.pgm ImageOut.pgm \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgDil);
    sscanf (argv[3],"%s",cNomImgEcrite);

	
	//ImageBase imIn, imOut;
	ImageBase imIn, imDil;
	imIn.load(cNomImgLue);
    imDil.load(cNomImgDil);

	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for(int x = 0; x < imIn.getHeight(); ++x)

		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			if (imIn[x][y] == 255 && imDil[x][y]==255) {

                imOut[x][y]=255;
                
			}else if(imIn[x][y]==0 && imDil[x][y]==0){

				imOut[x][y] = 255;

			}else if(imIn[x][y]==255 && imDil[x][y]==0){

                imOut[x][y] = 0;

            }
		}
		
	imOut.save(cNomImgEcrite);
		



	return 0;
}
