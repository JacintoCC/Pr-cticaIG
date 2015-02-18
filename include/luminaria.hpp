#ifndef LUMINARIA_HPP
#define LUMINARIA_HPP

#include "tuplas.hpp"
#include <GL/glut.h>  

class Luminaria{
protected:
   static int num_luces;

   int id_luz;
   Tupla4f * vector;
   Tupla3f color; 

public:
   Luminaria();
   Luminaria(Tupla4f * vector, Tupla3f color);

   inline static int getNumLuces(){
      return num_luces;
   }

   inline static void activarLuminaria(int i){
      glEnable(GL_LIGHT0 + i);
   }

   inline static void desactivarLuminaria(int i){
      glDisable(GL_LIGHT0 + i);
   }

   inline static void activarLuminarias(){
      for(int i=0;i<num_luces;i++)
         activarLuminaria(i);
   }
   inline static void desactivarLuminarias(){
      for(int i=0;i<num_luces;i++)
         desactivarLuminaria(i);
   }
   inline void modVector(Tupla3f nuevo_vector){
      vector->coo[0]+=nuevo_vector.coo[0];
      vector->coo[1]+=nuevo_vector.coo[1];
      vector->coo[2]+=nuevo_vector.coo[2];
      glLightfv( GL_LIGHT0 + id_luz, GL_POSITION, vector->coo );
   }

   void activarLuminaria();

};

class LuminariaCoordEsferica : public Luminaria{
private:
   float alpha;
   float beta;
   
public:
   LuminariaCoordEsferica();
   LuminariaCoordEsferica(float alpha, float beta, Tupla3f color);
   
   void modAlpha(float incremento){ 
      alpha+=incremento;
      setDireccion();
   }

   void modBeta(float incremento){ 
      beta+=incremento; 
      setDireccion();
   }
   void activarLuminaria();
   void setDireccion();

};

#endif
