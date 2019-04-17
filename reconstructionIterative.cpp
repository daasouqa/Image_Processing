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
    bool abime = true;
    
    
    
    out.save(cNomImgEcrite);
}
