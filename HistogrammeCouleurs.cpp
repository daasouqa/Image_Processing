// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250], nomFich[250];
    int nH, nW, nTaille, nR = 0, nG = 0, nB = 0;
    
    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm fichier.dat\n");
        exit (1) ;
    }
    
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",nomFich);
    
    OCTET *ImgIn;
    FILE* f = NULL;
    f = fopen(nomFich, "w");
    
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    
    
    int cptR, cptG, cptB;
    for(int j=0; j<=255;j++){
        cptR = 0;
        cptG = 0;
        cptB = 0;
        for (int i=0; i < nTaille3; i+=3)
        {
            nR = ImgIn[i];
            if(nR == j) cptR++;
            nG = ImgIn[i+1];
            if(nG == j) cptG++;
            nB = ImgIn[i+2];
            if(nB == j) cptB++;
        }
        
        fprintf(f,"%d %d %d %d\n",j , cptR, cptG, cptB);
    }
    
    free(ImgIn);
    return 1;
}