#include "tuplas.hpp"
#include <vector>
#include <utility>
#include <cmath>


#ifndef MALLA_HPP
#define MALLA_HPP

using namespace std;

// ---------------------------------------------------------------------
// Clase para almacenar una malla con vértices, caras y métodos necesarios

class Malla{
private:

   vector< Tupla3f > vertices;
   vector< Tupla3i > caras;
   vector< Tupla3f > normales_caras;
   vector< Tupla3f > normales_vertices;
   vector< pair<float,float> > coordenadas_textura;
   
   inline float getTamano(){
      return fabs(vertices.at(vertices.size()-1).coo[1]-vertices.at(0).coo[1]);
   }

   void generarNormalesCaras();

   void generarNormalesVertices();

   void generarCoordTextura(int num_rotaciones, int num_vert_perfil, bool tapa_inf, bool tapa_sup);

public:
   
   Malla(){}

   Malla(char const * nombreFichero, int num_rotaciones, bool cerrar);

   Malla(char const * nombreFichero );

   inline void setVertices(const vector<Tupla3f> nuevos_vertices){
      vertices=nuevos_vertices;
   }

   inline void setCaras(const vector<Tupla3i> nuevas_caras){
      caras=nuevas_caras;
   }

   inline Tupla3f* getVertices(){
      return &vertices.at(0);
   }

   inline Tupla3f getVertice(int i){
      return vertices.at(i);
   }

   inline float* getDirVertice(int i){
      return vertices.at(i).coo;
   }

   inline Tupla3i* getCaras(){
      return &caras.at(0);
   }

   inline Tupla3i getCara(int i){
      return caras.at(i);
   }

   inline Tupla3i* getDirCara(int i){
      return &caras.at(i);
   }

   inline Tupla3f getNormalCara(int i){
      return normales_caras.at(i);
   }

   inline Tupla3f* getNormalesCaras(){
      return &normales_caras.at(0);
   }

   inline float* getDirNormalCara(int i){
      return normales_caras.at(i).coo;
   }

   inline Tupla3f getNormalVertice(int i){
      return normales_vertices.at(i);
   }

   inline Tupla3f* getNormalesVertices(){
      return &normales_vertices.at(0);
   }

   inline float* getDirNormalVertice(int i){
      return normales_vertices.at(i).coo;
   }

   inline pair<float,float>* getCoordTextura(){
      return &coordenadas_textura.at(0);
   }

   inline float* getCoordTextura(int i){
      return &coordenadas_textura.at(i).first;
   }

   inline int getNumVertices(){
      return vertices.size();
   }

   inline int getNumCaras(){
      return caras.size();
   }   

   inline bool getCoordTextFilled(){
      return !coordenadas_textura.empty();
   }

   vector<Tupla3i> getCarasParidad(bool par);

   vector<Tupla3f> vectorVerticesYNormales();
   vector<Tupla3f> vectorCentrosYNormales();
   vector<Tupla3f> coloresNormalVertices();

   Tupla3f getCentro();

};

#endif
