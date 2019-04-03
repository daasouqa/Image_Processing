cmake_minimum_required(VERSION 3.13)
project(TP7_Traitement_d_Images)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP7_Traitement_d_Images main.cpp MakeBW.cpp seuillageCouleurs.cpp seuillageBW.cpp reconstruction.cpp InterpolationPPV.cpp)
