// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 1  (implementación)
// **
// *********************************************************************


#include <GL/glut.h>

#include "error-ogl.hpp"
#include "practica1.hpp"
#include "escena.hpp"
#include "file_ply_stl.hpp"
#include <iostream>

FuenteVisualizacion fuente_activa;
bool valido_PLY;

// ---------------------------------------------------------------------
// Malla de puntos a dibujar en la práctica

Malla malla_p1;
ElementoSimple objeto_p1;

// ---------------------------------------------------------------------
// Dibujador de la práctica 1

Drawer dibujador_p1;

// ---------------------------------------------------------------------
// coordenadas de los vértices del cubo:

   const unsigned num_verts_cubo = 8 ;

   GLfloat coords_verts_cubo[num_verts_cubo][3] = 
      {  { -0.5, -0.5, +0.5 } ,
         { +0.5, -0.5, +0.5 } ,
         { +0.5, +0.5, +0.5 } ,
         { -0.5, +0.5, +0.5 } ,
         { -0.5, -0.5, -0.5 } ,
         { +0.5, -0.5, -0.5 } ,
         { +0.5, +0.5, -0.5 } ,
         { -0.5, +0.5, -0.5 }
      };

// ---------------------------------------------------------------------
//  dibujar vértices del cubo en modo inmediato con begin/end

void DibujarCuboPuntos()
{
   glBegin(GL_POINTS);

   for ( unsigned i= 0 ; i < num_verts_cubo ; i++ )
        glVertex3fv( &( coords_verts_cubo[i][0] ) );

   glEnd();
   
}

// ---------------------------------------------------------------------
// cambiar la fuente de visualizacion activa

void cambiarFuenteVisualizacion(FuenteVisualizacion nueva_fuente){

   if(nueva_fuente==PLY){
      if(valido_PLY)
         fuente_activa=PLY;
      else
         cout << "No se han introducido ficheros PLY." << endl;
   }
   else
      fuente_activa=nueva_fuente;

}

// ---------------------------------------------------------------------
// función para implementar en la práctica 1 para inicialización
// se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL. El PLY se debe cargar aquí.

void P1_Inicializar( int argc, char *argv[] )
{
 
   if(argc==1){
      fuente_activa=CUBO;
   }
   else{
      fuente_activa=PLY;
      valido_PLY=true;
      malla_p1=Malla(argv[1]);
      objeto_p1=ElementoSimple(&malla_p1,&dibujador_p1);
   }

}

// ---------------------------------------------------------------------
// función para implementar en la práctica 1 para gestionar los eventos
// generados al pulsar distintas teclas.

bool P1_FGE_PulsarTeclaNormal( unsigned char tecla){
   bool capturada=true;

   switch(toupper(tecla)){
      case '0':
         dibujador_p1.cambiarModoVisualizacion(PUNTOS);
         break;
      case '1':
         dibujador_p1.cambiarModoVisualizacion(ALAMBRE);
         break;
      case '2':
         dibujador_p1.cambiarModoVisualizacion(SOLIDO);
         break;
      case '3':         
         dibujador_p1.cambiarModoVisualizacion(AJEDREZ);
         break;
      case '4':
         dibujador_p1.cambiarVisualizacionNormales();         
         dibujador_p1.cambiarModoVisualizacion(NORMALES);
         break;
      case 'C':
         cambiarFuenteVisualizacion(CUBO);
         break;
      case 'P':
         cambiarFuenteVisualizacion(PLY);
         break;
      default:
         capturada=false;
         break;
   }

   return capturada;
}

// ---------------------------------------------------------------------
// función a implementar en la práctica 1  dibujar los objetos

void P1_DibujarObjetos()
{
   glColor3f( 0.10, 0.15, 0.40 );
   glPointSize(4);

   switch(fuente_activa){
      case CUBO:
         DibujarCuboPuntos() ;
         break;
      case PLY:
         objeto_p1.visualizar();
         break;
   }
}
