//
// Created by Ines Benghezal on 20/02/2019.
//

#include <stdio.h>
#include "image_ppm.h"
#include "ImageBase.cpp"
#include "ImageBase.h"


int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB, S;
    
    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageOut.pgm \n");
        exit (1) ;
    }
    
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    
    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    ImageBase bw(nW, nH, false);
    int cptH = 0, cptW = 0;
    for (int i=0; i < nTaille3; i+=3) {
        nR = ImgIn[i];
        nG = ImgIn[i + 1];
        nB = ImgIn[i + 2];
        bw[cptH][cptW] = static_cast<unsigned char>((0.3 * nR + 0.5 * nG + 0.1 * nB));
        cptW++;
        if (cptW >= bw.getWidth()) {
            cptW = 0;
            cptH++;
        }
    }
    bw.save(cNomImgEcrite);
    free(ImgIn);
    return 1;
}