
//
// Created by Ines Benghezal on 08/02/2019.
//

#include "ImageBase.cpp"
#include <cstdio>
#include <math.h>
#include "ImageBase.h"

int main(int argc, char **argv) {
    char cNomImgLue[250], cNomImgEcrite[250], nomMasque[250];
    int object, background;
    if (argc != 4) {
        printf("Usage: ImageIn.pgm masque.pgm ImageOut.pgm\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
	sscanf(argv[2], "%s", nomMasque);
    sscanf(argv[3], "%s", cNomImgEcrite);
    ImageBase imageBase;
	ImageBase masque;
    imageBase.load(cNomImgLue);
	masque.load(nomMasque);
    ImageBase out(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    
    for (int i = 0; i < imageBase.getHeight(); ++i) {

        for (int j = 0; j < imageBase.getWidth(); ++j) {

			if(masque[i][j]==255){

				if (i == 0 && j == 0) { // Coin haut gauche
					int min = imageBase[i + 1][j];
					if (imageBase[i][j + 1] < min)
						min = imageBase[i][j + 1];
					if (imageBase[i + 1][j + 1] < min)
						min = imageBase[i + 1][j + 1];
					out[i][j] = static_cast<unsigned char>(min);
				} else if (i == 0 && j == imageBase.getWidth() - 1) { // Coin haut droit
					int min = imageBase[i][j - 1];
					if (imageBase[i + 1][j] < min)
						min = imageBase[i + 1][j];
					if (imageBase[i - 1][j - 1] < min)
						min = imageBase[i - 1][j - 1];
					out[i][j] = static_cast<unsigned char>(min);
				} else if (i == imageBase.getHeight() - 1 && j == 0) { // Coin bas gauche
					int min = imageBase[i][j + 1];
					if(imageBase[i - 1][j] < min)
						min = imageBase[i - 1][j];
					if (imageBase[i - 1][j + 1] < min)
						min = imageBase[i - 1][j + 1];
					out[i][j] = static_cast<unsigned char>(min);
				} else if (i == imageBase.getHeight() - 1 && j == imageBase.getWidth() - 1) { // Coin bas droit
					int min = imageBase[i][j - 1];
					if(imageBase[i - 1][j] < min)
						min = imageBase[i - 1][j];
					if(imageBase[i - 1][j - 1] < min)
						min = imageBase[i - 1][j - 1];
					out[i][j] = static_cast<unsigned char>(min);
				} else if (i == 0) { // Extrémité haute
					int min = imageBase[i][j - 1];
					if (imageBase[i][j + 1]  < min)
						min = imageBase[i][j + 1];
					if (imageBase[i + 1][j] < min)
						min = imageBase[i + 1][j];
					out[i][j] = static_cast<unsigned char>(min);
				}else if ( j == 0){ // Extrémité gauche
					int min = imageBase[i + 1][j];
					if (imageBase[i - 1][j] < min)
						min = imageBase[i - 1][j];
					if (imageBase[i][j + 1] < min)
						min = imageBase[i][j + 1];
					if(imageBase[i + 1][j - 1] < min)
						min = imageBase[i + 1][j - 1];
					if (imageBase[i + 1][j + 1] < min)
						min = imageBase[i + 1][j + 1];
					out[i][j] = static_cast<unsigned char>(min);
				} else if (i == imageBase.getHeight() - 1) { // Extrémité basse
					int min = imageBase[i][j - 1];
					if (imageBase[i][j + 1] < min)
						min = imageBase[i][j + 1];
					if (imageBase[i - 1][j] < min)
						min = imageBase[i - 1][j];
					if (imageBase[i - 1][j - 1] < min)
						min = imageBase[i - 1][j - 1];
					if (imageBase[i - 1][j + 1] < min)
						min = imageBase[i - 1][j + 1];
					out[i][j] = static_cast<unsigned char>(min);
				} else if (j == imageBase.getWidth() - 1) { // Extrémité droite
					int min = imageBase[i + 1][j];
					if (imageBase[i - 1][j] < min)
						min = imageBase[i - 1][j];
					if (imageBase[i][j - 1] < min)
						min = imageBase[i][j - 1];
					if (imageBase[i + 1][j - 1] < min)
						min = imageBase[i + 1][j - 1];
					if (imageBase[i - 1][j - 1] < min)
						min = imageBase[i - 1][j - 1];
					out[i][j] = static_cast<unsigned char>(min);
				} else {
					int min = imageBase[i][j + 1];
					if (imageBase[i][j - 1] < min)
						min = imageBase[i][j - 1];
					if (imageBase[i+1][j] < min)
						min = imageBase[i+1][j];
					if (imageBase[i - 1][j] < min)
						min = imageBase[i - 1][j];
					if (imageBase[i - 1][j + 1] < min)
						min = imageBase[i - 1][j + 1];
					if (imageBase[i - 1][j - 1] < min)
						min = imageBase[i - 1][j - 1];
					if (imageBase[i + 1][j - 1] < min)
						min = imageBase[i + 1][j - 1];
					if (imageBase[i + 1][j + 1] < min)
						min = imageBase[i + 1][j + 1];
					out[i][j] = static_cast<unsigned char>(min);
				}
			}else{
				out[i][j] = imageBase[i][j];
			}
        }
    }
    out.save(cNomImgEcrite);
    
    
}