//
// Created by Ines Benghezal on 05/04/2019.
//

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
    if (argc != 4) {
        printf("Usage: ImageIn.pgm masque.pgm ImageOut.pgm\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nomMasque);
    sscanf(argv[3], "%s", cNomImgEcrite);
    
    ImageBase masque;
    masque.load(nomMasque);
    
    ImageBase imageBase;
    imageBase.load(cNomImgLue);
    ImageBase out(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    
    for (int i = 1; i < imageBase.getHeight() - 1; ++i) {
        for (int j = 1; j < imageBase.getWidth() - 1; ++j) {
            if (masque[i][j] == 255) {
                int pixel = imageBase[i][j]
                            + imageBase[i - 1][j]
                            + imageBase[i - 1][j - 1]
                            + imageBase[i - 1][j + 1]
                            + imageBase[i + 1][j]
                            + imageBase[i + 1][j - 1]
                            + imageBase[i + 1][j + 1]
                            + imageBase[i][j-1]
                            + imageBase[i][j+1];
                out[i][j] = pixel / 9;
            } else {
                out[i][j] = imageBase[i][j];
            }
        }
    }
    
    out.save(cNomImgEcrite);
    
}
