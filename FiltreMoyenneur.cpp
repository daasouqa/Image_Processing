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
    char cNomImgLue[250], cNomImgEcrite[250],nomMasque[250];
    int ponderation;
    if (argc != 5) {
        printf("Usage: ImageIn.pgm masque.pgm ImageOut.pgm paramPonderation\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nomMasque);
    sscanf(argv[3], "%s", cNomImgEcrite);
    sscanf(argv[4], "%d", &ponderation);
    
    ImageBase imageBase, masque;
    imageBase.load(cNomImgLue);
    masque.load(nomMasque);
    ImageBase out(imageBase.getWidth(), imageBase.getHeight(), imageBase.getColor());
    
    int imin = imageBase.getHeight(),imax = 0,jmin = imageBase.getWidth(),jmax = 0;
    for (int i = 0; i < masque.getHeight(); ++i) {
        for (int j = 0; j < masque.getWidth(); ++j) {
            if (masque[i][j] == 0) {
                if (i < imin) {
                    imin = i;
                }else if (i > imax) {
                    imax = i;
                }
                if (j < jmin) {
                    jmin = j;
                }else if (j > jmax) {
                    jmax = j;
                }
            }
        }
    }
    
    for (int j = jmin; j < jmax; ++j) {
        if (j == imageBase.getWidth() - 1) {
            out[imin][j] = static_cast<unsigned char>((imageBase[imin][j - 1] + imageBase[imin][j]) / 2);
        } else if (j == 0) {
            out[imin][j] = static_cast<unsigned char>((imageBase[imin][j] + imageBase[imin][j + 1]) / 2);
        } else {
            imageBase[imin][j] = static_cast<unsigned char>(
                    (out[imin][j - 1] + ponderation * imageBase[imin][j] + imageBase[imin][j + 1]) / 2 *
                    ponderation);
        }
    }
    
    imin++;
    
    for (int i = imin; i < imax; ++i) {
        if (i == 0) {
            out[i][jmax] = static_cast<unsigned char>((imageBase[i][jmax + 1] + imageBase[i][jmax + 1]) / 2);
        } else if (i == imageBase.getHeight() - 1) {
            out[i][jmax] = static_cast<unsigned char>((imageBase[i - 1][jmax + 1] + imageBase[i][jmax + 1]) / 2);
        } else {
            out[i][jmax] = static_cast<unsigned char>(
                    (imageBase[i - 1][jmax + 1] + ponderation * imageBase[i][jmax + 1] + imageBase[i + 1][jmax + 1]) /
                    ponderation * 2);
        }
    }
    jmax++;
    
    for (int j = jmax; j < jmin; --j) {
        if (j == imageBase.getWidth() - 1) {
            out[imax][j] = static_cast<unsigned char>((imageBase[imax][j - 1] + imageBase[imax + 1][j]) / 2);
        } else if (j == 0) {
            out[imax][j] = static_cast<unsigned char>((imageBase[imax + 1][j] + imageBase[imax + 1][j + 1]) / 2);
        } else {
            out[imax][j] = static_cast<unsigned char>(
                    (imageBase[imax + 1][j - 1] + ponderation * imageBase[imax + 1][j] + imageBase[imax + 1][j + 1]) /
                    2 * ponderation);
        }
    }
    imax--;
    
    /**Si jmin est différent de 1
Sinon M(i, jmin)=( M(i-1, jmin-1)+ K*M(i, jmin-1) + M(i+1, jmin-1)) / 2+K*/
    
    for (int i = imax; i < imin; --i) {
        if (i == 0) {
            out[i][jmin] = static_cast<unsigned char>((imageBase[i + 1][jmin - 1] + imageBase[i][jmin - 1]) / 2);
        } else if (i == imageBase.getHeight() - 1) {
            out[i][jmin] = static_cast<unsigned char>((imageBase[i - 1][jmin - 1] + imageBase[i][jmin - 1]) / 2);
        } else {
            out[i][jmin] = static_cast<unsigned char>(
                    (imageBase[i - 1][imin - 1] + ponderation * imageBase[i][jmin - 1] + imageBase[i + 1][jmin - 1]) /
                    2 * ponderation);
        }
    }
    jmin++;
    
    out.save(cNomImgEcrite);
    
    
}
