//
// Created by Ines Benghezal on 03/02/2019.
//
#include "ImageBase.cpp"
#include <cstdio>
#include <math.h>
#include "ImageBase.h"

int main(int argc, char **argv) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int object, background;
    if (argc != 3) {
        printf("Usage: ImageIn.pgm ImageOut.pgm\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    ImageBase imageBase;
    imageBase.load(cNomImgLue);
    ImageBase out(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    
    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
            if (i == 0 && j == 0) { // Coin haut gauche
                int max = imageBase[i + 1][j];
                if (imageBase[i][j + 1] > max)
                    max = imageBase[i][j + 1];
                if (imageBase[i + 1][j + 1] > max)
                    max = imageBase[i + 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == 0 && j == imageBase.getWidth() - 1) { // Coin haut droit
                int max = imageBase[i][j - 1];
                if (imageBase[i + 1][j] > max)
                    max = imageBase[i + 1][j];
                if (imageBase[i - 1][j - 1] > max)
                    max = imageBase[i - 1][j - 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == imageBase.getHeight() - 1 && j == 0) { // Coin bas gauche
                int max = imageBase[i][j + 1];
                if(imageBase[i - 1][j] > max)
                    max = imageBase[i - 1][j];
                if (imageBase[i - 1][j + 1] > max)
                    max = imageBase[i - 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == imageBase.getHeight() - 1 && j == imageBase.getWidth() - 1) { // Coin bas droit
                int max = imageBase[i][j - 1];
                if(imageBase[i - 1][j] > max)
                    max = imageBase[i - 1][j];
                if(imageBase[i - 1][j - 1] > max)
                    max = imageBase[i - 1][j - 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == 0) { // Extrémité haute
                int max = imageBase[i][j - 1];
                if (imageBase[i][j + 1]  > max)
                    max = imageBase[i][j + 1];
                if (imageBase[i + 1][j] > max)
                    max = imageBase[i + 1][j];
                out[i][j] = static_cast<unsigned char>(max);
            }else if ( j == 0){ // Extrémité gauche
                int max = imageBase[i + 1][j];
                if (imageBase[i - 1][j] > max)
                    max = imageBase[i - 1][j];
                if (imageBase[i][j + 1] > max)
                    max = imageBase[i][j + 1];
                if(imageBase[i + 1][j - 1] > max)
                    max = imageBase[i + 1][j - 1];
                if (imageBase[i + 1][j + 1] > max)
                    max = imageBase[i + 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == imageBase.getHeight() - 1) { // Extrémité basse
                int max = imageBase[i][j - 1];
                if (imageBase[i][j + 1] > max)
                    max = imageBase[i][j + 1];
                if (imageBase[i - 1][j] > max)
                    max = imageBase[i - 1][j];
                if (imageBase[i - 1][j - 1] > max)
                    max = imageBase[i - 1][j - 1];
                if (imageBase[i - 1][j + 1] > max)
                    max = imageBase[i - 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (j == imageBase.getWidth() - 1) { // Extrémité droite
                int max = imageBase[i + 1][j];
                if (imageBase[i - 1][j] > max)
                    max = imageBase[i - 1][j];
                if (imageBase[i][j - 1] > max)
                    max = imageBase[i][j - 1];
                if (imageBase[i + 1][j - 1] > max)
                    max = imageBase[i + 1][j - 1];
                if (imageBase[i - 1][j - 1] > max)
                    max = imageBase[i - 1][j - 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else {
                int max = imageBase[i][j + 1];
                if (imageBase[i][j - 1] > max)
                    max = imageBase[i][j - 1];
                if (imageBase[i+1][j] > max)
                    max = imageBase[i+1][j];
                if (imageBase[i - 1][j] > max)
                    max = imageBase[i - 1][j];
                if (imageBase[i - 1][j + 1] > max)
                    max = imageBase[i - 1][j + 1];
                if (imageBase[i - 1][j - 1] > max)
                    max = imageBase[i - 1][j - 1];
                if (imageBase[i + 1][j - 1] > max)
                    max = imageBase[i + 1][j - 1];
                if (imageBase[i + 1][j + 1] > max)
                    max = imageBase[i + 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            }
        }
    }
    out.save(cNomImgEcrite);
    
    
}