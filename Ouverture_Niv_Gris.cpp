<<<<<<< HEAD
//
// Created by Ines Benghezal on 08/02/2019.
//

//Erosion puis dilatation

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
    ImageBase erosion(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    
    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
            if (i == 0 && j == 0) { // Coin haut gauche
                int min = imageBase[i + 1][j];
                if (imageBase[i][j + 1] < min)
                    min = imageBase[i][j + 1];
                if (imageBase[i + 1][j + 1] < min)
                    min = imageBase[i + 1][j + 1];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (i == 0 && j == imageBase.getWidth() - 1) { // Coin haut droit
                int min = imageBase[i][j - 1];
                if (imageBase[i + 1][j] < min)
                    min = imageBase[i + 1][j];
                if (imageBase[i - 1][j - 1] < min)
                    min = imageBase[i - 1][j - 1];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (i == imageBase.getHeight() - 1 && j == 0) { // Coin bas gauche
                int min = imageBase[i][j + 1];
                if (imageBase[i - 1][j] < min)
                    min = imageBase[i - 1][j];
                if (imageBase[i - 1][j + 1] < min)
                    min = imageBase[i - 1][j + 1];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (i == imageBase.getHeight() - 1 && j == imageBase.getWidth() - 1) { // Coin bas droit
                int min = imageBase[i][j - 1];
                if (imageBase[i - 1][j] < min)
                    min = imageBase[i - 1][j];
                if (imageBase[i - 1][j - 1] < min)
                    min = imageBase[i - 1][j - 1];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (i == 0) { // Extrémité haute
                int min = imageBase[i][j - 1];
                if (imageBase[i][j + 1] < min)
                    min = imageBase[i][j + 1];
                if (imageBase[i + 1][j] < min)
                    min = imageBase[i + 1][j];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (j == 0) { // Extrémité gauche
                int min = imageBase[i + 1][j];
                if (imageBase[i - 1][j] < min)
                    min = imageBase[i - 1][j];
                if (imageBase[i][j + 1] < min)
                    min = imageBase[i][j + 1];
                if (imageBase[i + 1][j - 1] < min)
                    min = imageBase[i + 1][j - 1];
                if (imageBase[i + 1][j + 1] < min)
                    min = imageBase[i + 1][j + 1];
                erosion[i][j] = static_cast<unsigned char>(min);
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
                erosion[i][j] = static_cast<unsigned char>(min);
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
                erosion[i][j] = static_cast<unsigned char>(min);
            } else {
                int min = imageBase[i][j + 1];
                if (imageBase[i][j - 1] < min)
                    min = imageBase[i][j - 1];
                if (imageBase[i + 1][j] < min)
                    min = imageBase[i + 1][j];
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
                erosion[i][j] = static_cast<unsigned char>(min);
            }
        }
    }
    
    ImageBase out(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    
    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
            if (i == 0 && j == 0) { // Coin haut gauche
                int max = erosion[i + 1][j];
                if (erosion[i][j + 1] > max)
                    max = erosion[i][j + 1];
                if (erosion[i + 1][j + 1] > max)
                    max = erosion[i + 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == 0 && j == erosion.getWidth() - 1) { // Coin haut droit
                int max = erosion[i][j - 1];
                if (erosion[i + 1][j] > max)
                    max = erosion[i + 1][j];
                if (erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == erosion.getHeight() - 1 && j == 0) { // Coin bas gauche
                int max = erosion[i][j + 1];
                if(erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i - 1][j + 1] > max)
                    max = erosion[i - 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == erosion.getHeight() - 1 && j == erosion.getWidth() - 1) { // Coin bas droit
                int max = erosion[i][j - 1];
                if(erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if(erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == 0) { // Extrémité haute
                int max = erosion[i][j - 1];
                if (erosion[i][j + 1]  > max)
                    max = erosion[i][j + 1];
                if (erosion[i + 1][j] > max)
                    max = erosion[i + 1][j];
                out[i][j] = static_cast<unsigned char>(max);
            }else if ( j == 0){ // Extrémité gauche
                int max = erosion[i + 1][j];
                if (erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i][j + 1] > max)
                    max = erosion[i][j + 1];
                if(erosion[i + 1][j - 1] > max)
                    max = erosion[i + 1][j - 1];
                if (erosion[i + 1][j + 1] > max)
                    max = erosion[i + 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == erosion.getHeight() - 1) { // Extrémité basse
                int max = erosion[i][j - 1];
                if (erosion[i][j + 1] > max)
                    max = erosion[i][j + 1];
                if (erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                if (erosion[i - 1][j + 1] > max)
                    max = erosion[i - 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (j == erosion.getWidth() - 1) { // Extrémité droite
                int max = erosion[i + 1][j];
                if (erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i][j - 1] > max)
                    max = erosion[i][j - 1];
                if (erosion[i + 1][j - 1] > max)
                    max = erosion[i + 1][j - 1];
                if (erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else {
                int max = erosion[i][j + 1];
                if (erosion[i][j - 1] > max)
                    max = erosion[i][j - 1];
                if (erosion[i+1][j] > max)
                    max = erosion[i+1][j];
                if (erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i - 1][j + 1] > max)
                    max = erosion[i - 1][j + 1];
                if (erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                if (erosion[i + 1][j - 1] > max)
                    max = erosion[i + 1][j - 1];
                if (erosion[i + 1][j + 1] > max)
                    max = erosion[i + 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            }
        }
    }
    out.save(cNomImgEcrite);
    
=======
//
// Created by Ines Benghezal on 08/02/2019.
//

//Erosion puis dilatation

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
    ImageBase erosion(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    
    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
            if (i == 0 && j == 0) { // Coin haut gauche
                int min = imageBase[i + 1][j];
                if (imageBase[i][j + 1] < min)
                    min = imageBase[i][j + 1];
                if (imageBase[i + 1][j + 1] < min)
                    min = imageBase[i + 1][j + 1];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (i == 0 && j == imageBase.getWidth() - 1) { // Coin haut droit
                int min = imageBase[i][j - 1];
                if (imageBase[i + 1][j] < min)
                    min = imageBase[i + 1][j];
                if (imageBase[i - 1][j - 1] < min)
                    min = imageBase[i - 1][j - 1];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (i == imageBase.getHeight() - 1 && j == 0) { // Coin bas gauche
                int min = imageBase[i][j + 1];
                if (imageBase[i - 1][j] < min)
                    min = imageBase[i - 1][j];
                if (imageBase[i - 1][j + 1] < min)
                    min = imageBase[i - 1][j + 1];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (i == imageBase.getHeight() - 1 && j == imageBase.getWidth() - 1) { // Coin bas droit
                int min = imageBase[i][j - 1];
                if (imageBase[i - 1][j] < min)
                    min = imageBase[i - 1][j];
                if (imageBase[i - 1][j - 1] < min)
                    min = imageBase[i - 1][j - 1];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (i == 0) { // Extrémité haute
                int min = imageBase[i][j - 1];
                if (imageBase[i][j + 1] < min)
                    min = imageBase[i][j + 1];
                if (imageBase[i + 1][j] < min)
                    min = imageBase[i + 1][j];
                erosion[i][j] = static_cast<unsigned char>(min);
            } else if (j == 0) { // Extrémité gauche
                int min = imageBase[i + 1][j];
                if (imageBase[i - 1][j] < min)
                    min = imageBase[i - 1][j];
                if (imageBase[i][j + 1] < min)
                    min = imageBase[i][j + 1];
                if (imageBase[i + 1][j - 1] < min)
                    min = imageBase[i + 1][j - 1];
                if (imageBase[i + 1][j + 1] < min)
                    min = imageBase[i + 1][j + 1];
                erosion[i][j] = static_cast<unsigned char>(min);
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
                erosion[i][j] = static_cast<unsigned char>(min);
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
                erosion[i][j] = static_cast<unsigned char>(min);
            } else {
                int min = imageBase[i][j + 1];
                if (imageBase[i][j - 1] < min)
                    min = imageBase[i][j - 1];
                if (imageBase[i + 1][j] < min)
                    min = imageBase[i + 1][j];
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
                erosion[i][j] = static_cast<unsigned char>(min);
            }
        }
    }
    
    ImageBase out(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    
    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
            if (i == 0 && j == 0) { // Coin haut gauche
                int max = erosion[i + 1][j];
                if (erosion[i][j + 1] > max)
                    max = erosion[i][j + 1];
                if (erosion[i + 1][j + 1] > max)
                    max = erosion[i + 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == 0 && j == erosion.getWidth() - 1) { // Coin haut droit
                int max = erosion[i][j - 1];
                if (erosion[i + 1][j] > max)
                    max = erosion[i + 1][j];
                if (erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == erosion.getHeight() - 1 && j == 0) { // Coin bas gauche
                int max = erosion[i][j + 1];
                if(erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i - 1][j + 1] > max)
                    max = erosion[i - 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == erosion.getHeight() - 1 && j == erosion.getWidth() - 1) { // Coin bas droit
                int max = erosion[i][j - 1];
                if(erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if(erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == 0) { // Extrémité haute
                int max = erosion[i][j - 1];
                if (erosion[i][j + 1]  > max)
                    max = erosion[i][j + 1];
                if (erosion[i + 1][j] > max)
                    max = erosion[i + 1][j];
                out[i][j] = static_cast<unsigned char>(max);
            }else if ( j == 0){ // Extrémité gauche
                int max = erosion[i + 1][j];
                if (erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i][j + 1] > max)
                    max = erosion[i][j + 1];
                if(erosion[i + 1][j - 1] > max)
                    max = erosion[i + 1][j - 1];
                if (erosion[i + 1][j + 1] > max)
                    max = erosion[i + 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (i == erosion.getHeight() - 1) { // Extrémité basse
                int max = erosion[i][j - 1];
                if (erosion[i][j + 1] > max)
                    max = erosion[i][j + 1];
                if (erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                if (erosion[i - 1][j + 1] > max)
                    max = erosion[i - 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else if (j == erosion.getWidth() - 1) { // Extrémité droite
                int max = erosion[i + 1][j];
                if (erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i][j - 1] > max)
                    max = erosion[i][j - 1];
                if (erosion[i + 1][j - 1] > max)
                    max = erosion[i + 1][j - 1];
                if (erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                out[i][j] = static_cast<unsigned char>(max);
            } else {
                int max = erosion[i][j + 1];
                if (erosion[i][j - 1] > max)
                    max = erosion[i][j - 1];
                if (erosion[i+1][j] > max)
                    max = erosion[i+1][j];
                if (erosion[i - 1][j] > max)
                    max = erosion[i - 1][j];
                if (erosion[i - 1][j + 1] > max)
                    max = erosion[i - 1][j + 1];
                if (erosion[i - 1][j - 1] > max)
                    max = erosion[i - 1][j - 1];
                if (erosion[i + 1][j - 1] > max)
                    max = erosion[i + 1][j - 1];
                if (erosion[i + 1][j + 1] > max)
                    max = erosion[i + 1][j + 1];
                out[i][j] = static_cast<unsigned char>(max);
            }
        }
    }
    out.save(cNomImgEcrite);
    
>>>>>>> master
}