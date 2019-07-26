//
// Created by Ines Benghezal on 28/02/019.
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
    char cNomImgLue[250], cNomImgEcrite[250],nomMasque[250];
    int iterations;
    if (argc != 4) {
        printf("Usage: ImageIn.pgm masque.pgm ImageOut.pgm\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nomMasque);
    sscanf(argv[3], "%s", cNomImgEcrite);

    ImageBase imageBase, masque;
    masque.load(nomMasque);
    imageBase.load(cNomImgLue);
    ImageBase out(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());

    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
            if (masque[i][j] == 255 && i > 0 && j > 0 && i < imageBase.getHeight() && j < imageBase.getWidth()) {
                int sum = 0;
                sum += imageBase[i+1][j] * 2;
                sum += imageBase[i-1][j] * 2;
                sum += imageBase[i][j + 1] * 2;
                sum += imageBase[i][j - 1] * 2;
                sum += imageBase[i - 1][j - 1];
                sum += imageBase[i + 1][j - 1];
                sum += imageBase[i + 1][j + 1];
                sum += imageBase[i - 1][j + 1];
                sum += imageBase[i][j] * 4;

                out[i][j] = sum / 16;
            } else {
                out[i][j] = imageBase[i][j];
            }
        }
    }
    out.save(cNomImgEcrite);
}