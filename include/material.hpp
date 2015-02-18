#include "textura.hpp"
#include "tuplas.hpp"

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

class Material{
private:
   Textura * textura=NULL;
   Tupla4f ambiental, difusa, especular;
   float brillo;

public:
   Material();
   Material(Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, float brillo);
   Material(Tupla4f color);
   Material(const char * nombreFichero, bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs);
   Material(const char * nombreFichero, bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs,Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, float brillo);

   void setColores(Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, float brillo);
   void setTextura(const char * nombreFichero, bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs);

   void activarMaterial();

};

#endif
