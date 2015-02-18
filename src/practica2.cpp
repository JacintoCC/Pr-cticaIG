// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 2  (implementación)
// **
// *********************************************************************


#include <GL/glut.h>

#include "error-ogl.hpp"
#include "escena.hpp"
#include "practica2.hpp"
#include "file_ply_stl.hpp"
#include <iostream>
#include <cmath>

using namespace std;

// ---------------------------------------------------------------------
// Malla de puntos a dibujar en la práctica 2

Malla malla_p2;
ElementoSimple objeto_p2;

// ---------------------------------------------------------------------
// Dibujador de la práctica 2

Drawer dibujador_p2;

// ---------------------------------------------------------------------
// función para implementar en la práctica 2 para gestionar los eventos
// generados al pulsar distintas teclas.

bool P2_FGE_PulsarTeclaNormal( unsigned char tecla){
   bool capturada=true;

   switch(toupper(tecla)){
      case '0':
         dibujador_p2.cambiarModoVisualizacion(PUNTOS);
         break;
      case '1':
         dibujador_p2.cambiarModoVisualizacion(ALAMBRE);
         break;
      case '2':
         dibujador_p2.cambiarModoVisualizacion(SOLIDO);
         break;
      case '3':         
         dibujador_p2.cambiarModoVisualizacion(AJEDREZ);
         break;
      case '4':
         dibujador_p2.cambiarVisualizacionNormales();         
         dibujador_p2.cambiarModoVisualizacion(NORMALES);
         break;
      default:
         capturada=false;
         break;
   }

   return capturada;
}

// ---------------------------------------------------------------------
// función para implementar en la práctica 2 para inicialización
// se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL. La malla de puntos se debe crear aquí

void P2_Inicializar( int argc, char *argv[] )
{
   if(argc==4){
      int num_rotaciones=atoi(argv[3]);
      malla_p2=Malla(argv[2],num_rotaciones,true);
      objeto_p2=ElementoSimple(&malla_p2,&dibujador_p2);
   }
}

// ---------------------------------------------------------------------
// función a implementar en la práctica 2 para dibujar los objetos

void P2_DibujarObjetos()
{
   objeto_p2.visualizar();
   
}
