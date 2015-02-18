#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "tuplas.hpp"
#include "malla.hpp"
#include "drawer.hpp"
#include "textura.hpp"

#ifndef ESCENA_HPP
#define ESCENA_HPP

using namespace std;

//------------------------------ Clase Nodo

class NodoGE{
public:
   virtual void visualizar() = 0;
   virtual void visualizar(GLuint * ptr) = 0;
   virtual void desseleccionar() = 0;
   virtual Tupla3f centro(GLuint * ptr) =0;
};


// ----------------------------- Clase EscenaGE

class EscenaGE : public NodoGE{
private:
   vector<NodoGE *> hijos;

public:
   EscenaGE(){}

   void incluirHijo(NodoGE * hijo){
      hijos.push_back(hijo);
   }

   void visualizar();

   void visualizar(GLuint * ptr);

   void desseleccionar(){
      for(unsigned int i=0; i<hijos.size(); i++){
         hijos.at(i)->desseleccionar();
      }
   }

   Tupla3f centro(GLuint * ptr){
      int siguiente_seleccionado=*ptr;
      return(hijos.at(siguiente_seleccionado)->centro(ptr+1));
   }
};


// ------------------------------------ Clase Elemento Simple

class ElementoSimple : public NodoGE{
private:
   Drawer * dibujador;
   Malla * malla;
   Material * material;
   bool seleccionado;

public:
   ElementoSimple(){}

   ElementoSimple(Malla * malla,Drawer * dibujador);

   ElementoSimple(Malla * malla,Drawer * dibujador, Material * material);

   ElementoSimple(Malla * malla,Drawer * dibujador, Tupla4f color);

   void visualizar();

   void visualizar(GLuint * ptr);

   void setDibujador(Drawer * dibujador){this->dibujador=dibujador;}

   void desseleccionar(){seleccionado=false;}

   Tupla3f centro(GLuint * ptr){ return malla->getCentro();}

};

#endif
