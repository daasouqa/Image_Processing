//
// Created by Ines Benghezal on 31/01/2019.
//

#include "../../../../MinGW/include/stdio.h"
#include "../../../../MinGW/include/stdlib.h"
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB, sR, sG, sB;
    
    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm \n");
        exit (1) ;
    }
    
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    
    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    unsigned char aminRed = 28, amaxRed = 70;
    unsigned char aminGreen = 22, amaxGreen = 50;
    unsigned char aminBlue = 18, amaxBlue = 95;
    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    for (int i=0; i < nTaille3; i+=3)
    {
        nR = ImgIn[i];
        nG = ImgIn[i+1];
        nB = ImgIn[i+2];
        if (nR < aminRed) ImgOut[i] = aminRed; else if (nR > amaxRed) ImgOut[i] = amaxRed;
        if (nG < aminGreen) ImgOut[i + 1] = aminGreen; else if (nG > amaxGreen)ImgOut[i + 1] = amaxGreen;
        if (nB < aminBlue) ImgOut[i + 2] = aminBlue; else if (nB > amaxBlue) ImgOut[i + 2] = amaxBlue;
    }
    
    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}