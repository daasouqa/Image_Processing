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
    if (argc != 5) {
        printf("Usage: ImageIn.pgm masque.pgm ImageOut.pgm iterations\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nomMasque);
    sscanf(argv[3], "%s", cNomImgEcrite);
    sscanf(argv[4], "%d", &iterations);
    
    cout << iterations << endl;
    ImageBase imageBase, masque;
    masque.load(nomMasque);
    imageBase.load(cNomImgLue);
    ImageBase out(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    bool abime = true;
    
    for (int k = 0; k < iterations; ++k) {
        for (int i = 0; i < imageBase.getHeight(); ++i) {
            for (int j = 0; j < imageBase.getWidth(); ++j) {
                if (masque[i][j] == 255) {
                    int max = 0;
                    double sum = 0;
                    int n = 0;
                    
                    if (imageBase[i - 1][j] > 0) {
                        sum += imageBase[i - 1][j];
                        n++;
                    }
                    if (imageBase[i + 1][j] > 0) {
                        sum += imageBase[i + 1][j];
                        n++;
                    }
                    if (imageBase[i - 1][j - 1] > 0) {
                        sum += imageBase[i - 1][j - 1];
                        n++;
                    }
                    if (imageBase[i - 1][j + 1] > 0) {
                        sum += imageBase[i - 1][j + 1];
                        n++;
                    }
                    if (imageBase[i + 1][j + 1] > 0) {
                        sum += imageBase[i + 1][j + 1];
                        n++;
                    }
                    if (imageBase[i + 1][j - 1] > 0) {
                        sum += imageBase[i + 1][j - 1];
                        n++;
                    }
                    if (imageBase[i][j - 1] > 0) {
                        sum += imageBase[i][j - 1];
                        n++;
                    }
                    if (imageBase[i][j + 1] > 0) {
                        sum += imageBase[i][j + 1];
                        n++;
                    }
                    if (n == 0) n = 1;
                    out[i][j] = static_cast<unsigned char>(sum / n);
                } else {
                    out[i][j] = imageBase[i][j];
                }
            }
        }
        for (int l = 0; l < imageBase.getHeight(); ++l) {
            for (int i = 0; i < imageBase.getWidth(); ++i) {
                imageBase[l][i] = out[l][i];
            }
        }
    }
    out.save(cNomImgEcrite);
}