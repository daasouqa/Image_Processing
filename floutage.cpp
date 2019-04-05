//
// Created by Ines Benghezal on 22/02/2019.
//
#include "ImageBase.cpp"
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "ImageBase.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    
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
    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    
//    nR = ImgIn[i];
//    nG = ImgIn[i+1];
//    nB = ImgIn[i+2];
    for (int i = 0; i < nTaille3; ++i) {
        ImgOut[i] = ImgIn[i];
    }
    cout << "nW = " << nW << " nH = " << nH << endl;
    int cpt = 0;
    for (int i = nW; i < nTaille3 - nW; i += 3) {
        int ir = i, ig = i + 1, ib = i + 2;
        if ((i % nW) != 0 && ((i + 3) % nW) != 0) {
            int pixel = ImgIn[ir - nW*3 - 3] + ImgIn[ir - nW*3] + ImgIn[ir - nW*3 + 3] + ImgIn[ir - 3] + ImgIn[ir] +
                        ImgIn[ir + 3] + ImgIn[ir + nW*3 - 3] + ImgIn[ir + nW*3] + ImgIn[ir + nW*3 + 3];
            ImgOut[ir] = (pixel / 9);
            pixel = ImgIn[ig - nW*3 - 3] + ImgIn[ig - nW*3] + ImgIn[ig - nW*3 + 3] + ImgIn[ig - 3] + ImgIn[ig] +
                    ImgIn[ig + 3] + ImgIn[ig + nW*3 - 3] + ImgIn[ig + nW*3] + ImgIn[ig + nW*3 + 3];
            ImgOut[ig] = (pixel / 9);
            pixel = ImgIn[ib - nW*3 - 3] + ImgIn[ib - nW*3] + ImgIn[ib - nW*3 + 3] + ImgIn[ib - 3] + ImgIn[ib] +
                    ImgIn[ib + 3] + ImgIn[ib + nW*3 - 3] + ImgIn[ib + nW*3] + ImgIn[ib + nW*3 + 3];
            ImgOut[ib] = (pixel / 9);
        } else {
//            ImgOut[ir] = ImgIn[ir];
//            ImgOut[ig] = ImgIn[ig];
//            ImgOut[ib] = ImgIn[ib];
            cpt++;
        }
    }
    cout << "Ignored : " << cpt << endl;
    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}