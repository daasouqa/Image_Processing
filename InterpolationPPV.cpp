//
// Created by Ines Benghezal on 03/04/2019.
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
    char cNomImgLue[250], cNomImgEcrite[250], nomMasque[250];
    int iterations;
    if (argc != 4) {
        printf("Usage: ImageIn.pgm masque.pgm ImageOut.pgm\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nomMasque);
    sscanf(argv[3], "%s", cNomImgEcrite);
    
    ImageBase imageBase, masque;
    ImageBase out(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    imageBase.load(cNomImgLue);
    masque.load(nomMasque);
    
    int cleanPixels[imageBase.getHeight() * imageBase.getWidth()];
    int cpt = 0;
    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
            if (masque[i][j] == 0) {
               cleanPixels[cpt] = imageBase[i][j];
               cout << "cleanPixels[" << cpt << "] = " << cleanPixels[cpt] << endl;
               cpt++;
            }
        }
    }
    
    cout << "Taille de cleanPixels = " << cpt << endl;
    for (int i = 0; i < masque.getHeight(); ++i) {
        for (int j = 0; j < masque.getWidth(); ++j) {
            if (masque[i][j] == 255) {
                int xk = (masque.getWidth() * i + j) / cpt, xk1 = (masque.getHeight() * i + j) / cpt + 1;
                int x = (masque.getWidth() * i + j) / cpt;
                if (x > (xk + xk1) / 2) {
                    out[i][j] = static_cast<unsigned char>(cleanPixels[xk1 / cpt]);
                } else {
                    out[i][j] = static_cast<unsigned char>(cleanPixels[xk / cpt]);
                }
            } else {
                out[i][j] = imageBase[i][j];
            }
        }
    }
    
    out.save(cNomImgEcrite);
}
