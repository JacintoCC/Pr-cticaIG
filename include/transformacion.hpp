#include <GL/glut.h>
#include "escena.hpp"
#include "tuplas.hpp"
#include <cmath>

#ifndef TRANSFORMACION_HPP
#define TRANSFORMACION_HPP

// -------------------------------- Clase Matriz Transformación 

class MatrizTransformacion : public NodoGE{
protected:
   float matriz[4][4];
   
public:
   MatrizTransformacion();

   virtual inline void actualizar(){}

   inline void visualizar(){ 
      actualizar();
      glMultMatrixf(&matriz[0][0]); 
   }

   inline void visualizar(GLuint * ptr){}
   inline void desseleccionar(){}
   inline Tupla3f centro(GLuint * ptr){return Tupla3f(0,0,0);}
};

class MatrizTranslacion : public MatrizTransformacion{
private:

   Tupla3f * translacion=NULL;
   
public:

   MatrizTranslacion(Tupla3f vector_trans);

   MatrizTranslacion(Tupla3f * vector_trans);

   void actualizar();
};

class MatrizEscalado : public MatrizTransformacion{
private:
   Tupla3f * escala=NULL;
   
public:
   MatrizEscalado(Tupla3f vector_esc);

   MatrizEscalado(Tupla3f * vector_esc);

   void actualizar();

};

class MatrizRotacion : public MatrizTransformacion{
private:
   Tupla3f eje;
   float * angulo = NULL;
   
public:
   MatrizRotacion(Tupla3f vector_eje, float angulo);

   MatrizRotacion(Tupla3f vector_eje, float * ang);

   void actualizar();
};

#endif
