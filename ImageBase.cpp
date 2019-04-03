/******************************************************************************
* ICAR_Library
*
* Fichier : ImageBase.cpp
*
* Description : Voir le fichier .h
*
* Auteur : Mickael Pinto
*
* Mail : mickael.pinto@live.fr
*
* Date : Octobre 2012
*
*******************************************************************************/

#include "ImageBase.h"
#include "Image_ppm.h"
#include <fstream>
#include <iostream>
#include <array>
#include <map>

using namespace std;

ImageBase::ImageBase(void)
{
    isValid = false;
    init();
}


ImageBase::ImageBase(int imWidth, int imHeight, bool isColor)
{
    isValid = false;
    init();
    
    color = isColor;
    height = imHeight;
    width = imWidth;
    nTaille = height * width * (color ? 3 : 1);
    
    if(nTaille == 0)
        return;
    
    allocation_tableau(data, OCTET, nTaille);
    dataD = (double*)malloc(sizeof(double) * nTaille);
    isValid = true;
}


ImageBase::~ImageBase(void)
{
    reset();
}

ImageBase::ImageBase(ImageBase &imageBase) {
    ImageBase imageBase1 = *this;
    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
            imageBase1[i][j] = imageBase[i][j];
        }
    }
    this->copy(imageBase1);
}

void ImageBase::init()
{
    if(isValid)
    {
        free(data);
        free(dataD);
    }
    
    data = 0;
    dataD = 0;
    height = width = nTaille = 0;
    isValid = false;
}

void ImageBase::reset()
{
    if(isValid)
    {
        free(data);
        free(dataD);
    }
    isValid = false;
}

void ImageBase::load(char *filename)
{
    init();
    
    int l = strlen(filename);
    
    if(l <= 4) // Le fichier ne peut pas etre que ".pgm" ou ".ppm"
    {
        printf("Chargement de l'image impossible : Le nom de fichier n'est pas conforme, il doit comporter l'extension, et celle ci ne peut être que '.pgm' ou '.ppm'");
        exit(0);
    }
    
    int nbPixel = 0;
    
    if( strcmp(filename + l - 3, "pgm") == 0) // L'image est en niveau de gris
    {
        color = false;
        lire_nb_lignes_colonnes_image_pgm(filename, &height, &width);
        nbPixel = height * width;
        
        nTaille = nbPixel;
        allocation_tableau(data, OCTET, nTaille);
        lire_image_pgm(filename, data, nbPixel);
    }
    else if( strcmp(filename + l - 3, "ppm") == 0) // L'image est en couleur
    {
        color = true;
        lire_nb_lignes_colonnes_image_ppm(filename, &height, &width);
        nbPixel = height * width;
        
        nTaille = nbPixel * 3;
        allocation_tableau(data, OCTET, nTaille);
        lire_image_ppm(filename, data, nbPixel);
    }
    else
    {
        printf("Chargement de l'image impossible : Le nom de fichier n'est pas conforme, il doit comporter l'extension, et celle ci ne peut être que .pgm ou .ppm");
        exit(0);
    }
    
    dataD = (double*)malloc(sizeof(double) * nTaille);
    
    isValid = true;
}

bool ImageBase::save(char *filename)
{
    if(!isValid)
    {
        printf("Sauvegarde de l'image impossible : L'image courante n'est pas valide");
        exit(0);
    }
    
    if(color)
        ecrire_image_ppm(filename, data,  height, width);
    else
        ecrire_image_pgm(filename, data,  height, width);
    
    return true;
}

ImageBase *ImageBase::getPlan(PLAN plan)
{
    if( !isValid || !color )
        return 0;
    
    ImageBase *greyIm = new ImageBase(width, height, false);
    
    switch(plan)
    {
        case PLAN_R:
            planR(greyIm->data, data, height * width);
            break;
        case PLAN_G:
            planV(greyIm->data, data, height * width);
            break;
        case PLAN_B:
            planB(greyIm->data, data, height * width);
            break;
        default:
            printf("Il n'y a que 3 plans, les valeurs possibles ne sont donc que 'PLAN_R', 'PLAN_G', et 'PLAN_B'");
            exit(0);
            break;
    }
    
    return greyIm;
}

void ImageBase::copy(const ImageBase &copy)
{
    reset();
    
    isValid = false;
    init();
    
    color = copy.color;
    height = copy.height;
    width = copy.width;
    nTaille = copy.nTaille;
    isValid = copy.isValid;
    
    if(nTaille == 0)
        return;
    
    allocation_tableau(data, OCTET, nTaille);
    dataD = (double*)malloc(sizeof(double) * nTaille);
    isValid = true;
    
    for(int i = 0; i < nTaille; ++i)
    {
        data[i] = copy.data[i];
        dataD[i] = copy.dataD[i];
    }
    
}

unsigned char *ImageBase::operator[](int l)
{
    if(!isValid)
    {
        printf("L'image courante n'est pas valide");
        exit(0);
    }
    
    if((!color && l >= height) || (color && l >= height*3))
    {
        printf("L'indice se trouve en dehors des limites de l'image");
        exit(0);
    }
    
    return data+l*width;
}

void ImageBase::afficherHistogrammeCouleurs() {
    ImageBase imageBase = *this;
    ImageBase *composanteRouge = imageBase.getPlan(PLAN_R);
    ImageBase *composanteVerte = imageBase.getPlan(PLAN_G);
    ImageBase *composanteBleu = imageBase.getPlan(PLAN_B);
    ofstream myFile;
    myFile.open("histogrammeCouleurs.dat");
    for (int k = 0; k < 256; ++k) {
        int occR = 0, occG = 0, occB = 0;
        for (int i = 0; i < imageBase.getHeight(); ++i) {
            for (int j = 0; j < imageBase.getWidth(); ++j) {
                cout << k << " " << (int) composanteRouge[i][j] / 3 << endl;
                if ((int) composanteRouge[i][j] == k)
                    occR++;
                if ((int) composanteVerte[i][j] == k)
                    occG++;
                if ((int) composanteBleu[i][j] == k)
                    occB++;
            }
        }
        myFile << k << "  " << occR << " " << occG << " " << occB << endl;
    }
    myFile.close();
}






















//void ImageBase::afficherHistogrammeCouleurs() {
//    ImageBase imageBase;
//    imageBase = *this;
//    ofstream file;
//    file.open("histogrammeCouleurs.dat");
//    ImageBase *composanteVerte;
//    ImageBase *composanteBleue;
//    ImageBase *composanteRouge;
//    composanteRouge = imageBase.getPlan(ImageBase::PLAN_R);
//    composanteBleue = imageBase.getPlan(ImageBase::PLAN_B);
//    composanteVerte = imageBase.getPlan(ImageBase::PLAN_G);
//    long rouge[256] = {0}, bleu[256] = {0}, vert[256] = {0};
//    for (int i = 0; i < composanteRouge->getHeight(); ++i) {
//        for (int j = 0; j < composanteRouge->getWidth(); ++j) {
//            rouge[(int) composanteRouge[i][j]]++;
//        }
//    }
//    for (int i = 0; i < composanteBleue->getHeight(); ++i) {
//        for (int j = 0; j < composanteBleue->getWidth(); ++j) {
//            bleu[(int) composanteBleue[i][j]]++;
//        }
//    }
//    for (int i = 0; i < composanteVerte->getHeight(); ++i) {
//        for (int j = 0; j < composanteVerte->getWidth(); ++j) {
//            vert[(int) composanteVerte[i][j]]++;
//        }
//    }
//    for (int k = 0; k < 256; ++k) {
//        file << k << " " << rouge[k] << " " << bleu[k] << " " << vert[k] << endl;
//    }
//    file.close();
//}

//void ImageBase::afficherHistogrammeCouleurs() {
//    ImageBase imageBase;
//    imageBase = *this;
//    ofstream file;
//    file.open("histogrammeCouleurs.txt");
//    map<int, array<int, 3> > histo_data;
//    ImageBase* imageBase_RED;
//    imageBase_RED = imageBase.getPlan(ImageBase::PLAN_R);
//    for (int i = 0; i < imageBase.getHeight(); ++i) {
//        for (int j = 0; j < imageBase.getWidth(); ++j) {
//            histo_data[(*imageBase_RED)[i][j]][0]++;
//        }
//    }
//
//    ImageBase* imageBase_GREEN;
//    imageBase_GREEN = imageBase.getPlan(ImageBase::PLAN_G);
//    for (int i = 0; i < imageBase.getHeight(); ++i) {
//        for (int j = 0; j < imageBase.getWidth(); ++j) {
//            histo_data[(*imageBase_GREEN)[i][j]][1]++;
//        }
//    }
//
//    ImageBase* imageBase_BLUE;
//    imageBase_BLUE = imageBase.getPlan(ImageBase::PLAN_B);
//    for (int i = 0; i < imageBase.getHeight(); ++i) {
//        for (int j = 0; j < imageBase.getWidth(); ++j) {
//            histo_data[(*imageBase_BLUE)[i][j]][2]++;
//        }
//    }
//
//    double nb_pixels = imageBase.getHeight() * imageBase.getWidth();
//
//    for (auto it = histo_data.begin() ; it != histo_data.end() ; ++it){
//        file << it->first << " " << it->second[0]  << " " << it->second[1]  << " " << it->second[2]  << endl;
//    }
//    file.close();
//
//}
void ImageBase::afficherHistogramme() {
    ImageBase imageBase;
    imageBase = *this;
    ofstream myfile;
    myfile.open("histogramme.dat");
    
    for (int i = 0; i < 256; ++i) {
        int occ = 0;
        for (int j = 0; j < imageBase.getHeight(); ++j) {
            for (int k = 0; k < imageBase.getWidth(); ++k) {
                if (imageBase[j][k] == i)
                    occ++;
            }
        }
        myfile << i << " " << occ <<endl;
    }
    myfile.close();
}

void ImageBase::afficherProfil(bool isColonne, int indice){
    ImageBase imageBase;
    imageBase = *this;
    
    ofstream myfile;
    myfile.open ("profil.dat");
    
    if (isColonne) {
        for (int i = 0; i < imageBase.getHeight(); ++i) {
            cout << i << " " << (int) imageBase[i][indice] << endl;
            myfile << i << " " << (int) imageBase[i][indice] << endl;
        }
    } else {
        for (int i = 0; i < imageBase.getWidth(); ++i) {
            cout << i << " " << (int) imageBase[indice][i] << endl;
            myfile << i << " " << (int) imageBase[indice][i] << endl;
        }
    }
    myfile.close();
}

void ImageBase::seuillageCouleurs(char *nomImgEcrite, int s_R, int s_G, int s_B) {
    ImageBase imageBase;
    imageBase = *this;
    for (int i = 0; i < imageBase.getHeight(); ++i) {
        for (int j = 0; j < imageBase.getWidth(); ++j) {
        
        }
    }
}

/** Effectue un seuillage à un niveaux sur un fichier lu
 * @param nomImgLue nom du fichier en entrée
 * @param nomImgEcrite nom du fichier en sortie
 * @param seuil premier seuil */
void ImageBase::seuillageTwoLevels(char *nomImgEcrite, int seuil) {
    ImageBase imIn;
    imIn = *this;
    ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
    
    for (int i = 0; i < imIn.getHeight() ; ++i) {
        for (int j = 0; j < imIn.getWidth(); ++j) {
            if (imIn[i][j] < seuil) {
                imOut[i][j] = 0;
            } else {
                imOut[i][j] = 255;
            }
        }
    }
    cout << "seuillage réussi. Ecriture du fichier " << nomImgEcrite;
    imOut.save(nomImgEcrite);
    cout << "Ecriture reussie";
}

/** Effectue un seuillage à deux niveaux sur un fichier lu
 * @param nomImgLue nom du fichier en entrée
 * @param nomImgEcrite nom du fichier en sortie
 * @param s1 premier seuil
 * @param s2 deuxième seuil */

void ImageBase::seuillageThreeLevels(char *nomImgEcrite, int s1, int s2) {
    ImageBase imIn;
    imIn = *this;
    ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
    
    for (int i = 0; i < imIn.getHeight(); ++i) {
        for (int j = 0; j < imIn.getWidth(); ++j) {
            if (imIn[i][j] < s1) {
                imOut[i][j] = 0;
            } else if (imIn[i][j] < s2) {
                imOut[i][j] = 128;
            } else {
                imOut[i][j] = 255;
            }
        }
    }
    
    cout << "seuillage réussi. Ecriture du fichier " << nomImgEcrite << endl;
    imOut.save(nomImgEcrite);
    cout << "Ecriture reussie" << endl;
}

/** Effectue un seuillage à trois niveaux sur un fichier lu
 * @param nomImgLue nom du fichier en entrée
 * @param nomImgEcrite nom du fichier en sortie
 * @param s1 premier seuil
 * @param s2 deuxième seuil
 * @param s3 troisième seuil*/

void ImageBase::seuillageFourLevels(char *nomImgEcrite, int s1, int s2, int s3) {
    ImageBase imIn;
    imIn = *this;
    ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
    
    for (int i = 0; i < imIn.getHeight(); ++i) {
        for (int j = 0; j < imIn.getWidth(); ++j) {
            if (imIn[i][j] < s1) {
                imOut[i][j] = 0;
            } else {
                if (imIn[i][j] < s2) {
                    imOut[i][j] = 85;
                } else {
                    if (imIn[i][j] < s3) {
                        imOut[i][j] = 170;
                    } else {
                        imOut[i][j] = 255;
                    }
                }
            }
        }
    }
    cout << "seuillage réussi. Ecriture du fichier " << nomImgEcrite;
    imOut.save(nomImgEcrite);
    cout << "Ecriture reussie";
}





