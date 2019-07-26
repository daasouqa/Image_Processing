//
// Created by Ines Benghezal on 20/04/2019.
//

#include "ImageBase.cpp"
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "ImageBase.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    char cNomImgLue[250], cNomImgEcrite[250], nomMasque[250], nomPatch[250];
    if (argc != 5) {
        printf("Usage: ImageIn.pgm masque.pgm patch ImageOut.pgm\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nomMasque);
    sscanf(argv[3], "%s", nomPatch);
    sscanf(argv[4], "%s", cNomImgEcrite);
    
    ImageBase image, masque, patch;
    image.load(cNomImgLue);
    masque.load(nomMasque);
    patch.load(nomPatch);
    ImageBase out(image.getWidth(), image.getHeight(), image.getColor());
    
    //Detecter les proportions du patch
    int minX = patch.getWidth(), minY = patch.getHeight(), maxX = 0, maxY = 0;
    for (int i = 0; i < patch.getHeight(); ++i) {
        for (int j = 0; j < patch.getWidth(); ++j) {
            if (patch[i][j] == 255) {
                if (i < minY) {
                    minY = i;
                }
                if (i > maxY) {
                    maxY = i;
                }
                if (j < minX) {
                    minX = j;
                }
                if (j > maxX) {
                    maxX = j;
                }
            }
        }
    }
    
    // Surface du patch
    
    double patchSurface = (maxX - minX) * (maxY - minY);
    
    // Dimensions du trou
    int minI = image.getHeight(), maxI = 0, minJ = image.getWidth(), maxJ = 0;
    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            if (masque[i][j] == 255) {
                if (i < minI) {
                    minI = i;
                }
                if (i > maxI) {
                    maxI = i;
                }
                if (j < minJ) {
                    minJ = j;
                }
                if (j > maxJ) {
                    maxJ = j;
                }
            }
        }
    }
    
    // Surface du trou
    double holeSurface = (maxI - minI) * (maxJ - minJ);
    
    cout << "minX = " << minX << " MaxX = " << maxX << endl;
    cout << "minY = " << minY << " MaxY = " << maxY << endl;
    //Nombre de patches nécessaire
    int iterations = holeSurface / patchSurface;
    
    int indexI = 0, indexJ = 0;
    //Application du patch
    for (int k = minI; k < maxI; ++k) {
        for (int l = minJ; l < maxJ; ++l) {
            if (masque[k][l] == 255) {
                if (patch[minY + indexI][minX + indexJ] != 255) {
                    indexI = 0;
                    indexJ = 0;
                }
                image[k][l] = image[minY + indexI][minX + indexJ];
                if (indexJ >= maxX) {
                    indexJ = 0;
                } else {
                    indexJ++;
                }
            }
        }
        indexJ = 0;
        if (indexI >= maxY) {
            indexI = 0;
        } else {
            indexI++;
        }
    }
    
    image.save(cNomImgEcrite);
}