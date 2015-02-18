// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 4  (implementación)
// **
// *********************************************************************


#include <GL/glut.h>

#include "error-ogl.hpp"
#include "practica4.hpp"
#include "escena.hpp"
#include "transformacion.hpp"
#include "tuplas.hpp"
#include "drawer.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Tupla4f posicion_luz=Tupla4f(3.0,0.0,11.0,1.0);

Drawer dibujador_p4;
EscenaGE escena_p4;

Luminaria luminaria1=Luminaria(&posicion_luz,Tupla3f(0.6,0,0));
LuminariaCoordEsferica luminaria2=LuminariaCoordEsferica(0,0,Tupla3f(1,1,1));

// ---------------------------------------------------------------------
// función para implementar en la práctica 4 para gestionar los eventos

bool P4_FGE_PulsarTeclaNormal( unsigned char tecla){

   bool redisp=true;

   switch(tecla){
      case '1':         
         dibujador_p4.cambiarModoVisualizacion(SOM_PLANO);
         break;
      case '2':         
         dibujador_p4.cambiarModoVisualizacion(SOM_SUAVE);
         break;
      case 'A':
      case 'a':
         luminaria2.modAlpha(M_PI/10.0);
         break;
      case 'Z':
      case 'z':
         luminaria2.modAlpha(-M_PI/10.0);
         break;
      case 'X':
      case 'x':
         luminaria2.modBeta(M_PI/10.0);
         break;
      case 'C':
      case 'c':
         luminaria2.modBeta(-M_PI/10.0);
         break;
      case 'i':
         luminaria1.modVector(Tupla3f(0.1,0,0));
         break;
      case 'I':
         luminaria1.modVector(Tupla3f(-0.1,0,0));
         break;
      case 'j':
         luminaria1.modVector(Tupla3f(0,0.1,0));
         break;
      case 'J':
         luminaria1.modVector(Tupla3f(0,-0.1,0));
         break;
      case 'k':
         luminaria1.modVector(Tupla3f(0,0,0.1));
         break;
      case 'K':
         luminaria1.modVector(Tupla3f(0,0,-0.1));
         break;
      default:
         redisp=false;
         break;
   }

   return redisp;
}

// ---------------------------------------------------------------------
// función para implementar en la práctica 4 para inicialización
// se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL.

void P4_Inicializar( int argc, char *argv[] )
{
   P4_InicializarEscena(&dibujador_p4);
   P4_MontarEscena(&escena_p4,&dibujador_p4);  
   
   glEnable(GL_NORMALIZE);
   glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
   glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR ) ;
   glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
   glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
   glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

   dibujador_p4.cambiarModoVisualizacion(SOM_SUAVE);

   dibujador_p4.incluirLuminaria(&luminaria1);
   dibujador_p4.incluirLuminaria(&luminaria2);
}

// ---------------------------------------------------------------------
// función a implementar en la práctica 3 para dibujar los objetos

void P4_DibujarObjetos()
{
   P4_SetDibujador(&dibujador_p4);
   escena_p4.visualizar();
}
