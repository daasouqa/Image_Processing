//
// Created by Ines Benghezal on 25/04/019.
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
    char cNomImgLue[250], cNomImgEcrite[250];
    int iterations;
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
            if (imageBase[i][j] == 255){
                out[i][j] = 0;
            } else {
                out[i][j] = 255;
            }
        }
    }
    out.save(cNomImgEcrite);
}