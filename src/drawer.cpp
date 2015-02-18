#include "drawer.hpp"
#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;

// *********************************************************************
// **
// ** Funciones privadas para dibujar
// **
// *********************************************************************


// ---------------------------------------------------------------------
// Dibujar vector de puntos de una malla

void Drawer::dibujarPuntos(Malla & malla){

   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT, 0, malla.getVertices() );
   glDrawArrays( GL_POINTS, 0, malla.getNumVertices() );

}

// ---------------------------------------------------------------------
// Dibujar vector de triangulos de una malla

void Drawer::dibujarTriangulos(Malla & malla){
   int num_caras=malla.getNumCaras();

   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT, 0, malla.getVertices() );
   glDrawElements( GL_TRIANGLES, num_caras*3, GL_UNSIGNED_INT, malla.getCaras());
}


// ---------------------------------------------------------------------
//  Dibujar los triángulos de una malla en modo ajedrez

void Drawer::dibujarAjedrez(Malla & malla)
{
   vector<Tupla3i> caras_pares,caras_impares;
   
   caras_pares=malla.getCarasParidad(true);
   caras_impares=malla.getCarasParidad(false);

   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT, 0, malla.getVertices() );

   glColor3f( 0, 0, 0.4 );
   glDrawElements( GL_TRIANGLES, caras_pares.size()*3 , GL_UNSIGNED_INT, &(caras_pares.at(0)));

   glColor3f( 0, 0.4, 0 );
   glDrawElements( GL_TRIANGLES, caras_impares.size()*3 , GL_UNSIGNED_INT, &(caras_impares.at(0)));
}

// --------------------------------------------------------------------
// Dibujar una malla por sus normales según un modo

void Drawer::dibujarNormales(Malla & malla, int modo){
   if(modo<4)
      dibujarNormalesColorCara(malla);
   else
      dibujarNormalesColorVertice(malla);

   if(modo%4==1)
      dibujarNormalesSegmentoCara(malla);
   else if(modo%4==2)
      dibujarNormalesSegmentoVertice(malla);
   else if(modo%4==3){
      dibujarNormalesSegmentoCara(malla);
      dibujarNormalesSegmentoVertice(malla);
   }

}

// ---------------------------------------------------------------------
//  Dibujar una malla siguiendo el color determinado por la normal de cada cara

void Drawer::dibujarNormalesColorCara(Malla & malla){

   int num_caras=malla.getNumCaras();
   Tupla3f color_normal;

   glEnableClientState( GL_VERTEX_ARRAY );
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   glVertexPointer( 3, GL_FLOAT, 0, malla.getVertices() );
   
   for(int i=0; i<num_caras; i++){
      color_normal=malla.getNormalCara(i);
      glColor3f( abs(color_normal.coo[0]) , abs(color_normal.coo[1]) , abs(color_normal.coo[2]) );
      glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, malla.getDirCara(i));
   }
}


// ---------------------------------------------------------------------
//  Dibujar una malla siguiendo el color determinado por la interpolación de las normales de los vértices

void Drawer::dibujarNormalesColorVertice(Malla & malla){

   glShadeModel(GL_SMOOTH);

   vector<Tupla3f> colores=malla.coloresNormalVertices();
   glEnableClientState( GL_COLOR_ARRAY );
   glColorPointer(3, GL_FLOAT, 0, &colores.at(0));


   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   dibujarTriangulos(malla);

   glDisableClientState( GL_COLOR_ARRAY );
   
}

// ----------------------------------------------------------------------
//  Dibujar los segmentos determinados por los centros y normales de las caras

void Drawer::dibujarNormalesSegmentoCara(Malla &malla){
   vector<Tupla3f> normales=malla.vectorCentrosYNormales();

   glColor3f(0,0,0.4);
   glPointSize(2);
   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT, 0, &normales.at(0));
   glDrawArrays( GL_LINES, 0, 2*malla.getNumCaras() );

}

// ----------------------------------------------------------------------
//  Dibujar los segmentos determinados por los vértices y sus normales

void Drawer::dibujarNormalesSegmentoVertice(Malla &malla){
   vector<Tupla3f> normales=malla.vectorVerticesYNormales();

   glColor3f(0.4,0.4,0);
   glPointSize(2);
   glEnableClientState( GL_VERTEX_ARRAY );
   glVertexPointer( 3, GL_FLOAT, 0, &normales.at(0));
   glDrawArrays( GL_LINES, 0, 2*malla.getNumVertices() );

}

// ----------------------------------------------------------------------
//  Dibujar en modo Sombreado Plano

void Drawer::dibujarSombreadoPlano(Malla &malla){
   bool tiene_coo_tex=malla.getCoordTextFilled();
   Tupla3i cara;

   glShadeModel(GL_FLAT);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

   glBegin(GL_TRIANGLES);

   for(int i=0; i<malla.getNumCaras(); i++){
      cara=malla.getCara(i);
      glNormal3fv(malla.getDirNormalCara(i));
      for(int j=0; j<3; j++){
         if(tiene_coo_tex) glTexCoord2fv(malla.getCoordTextura(cara.idx[j]));
         glVertex3fv(malla.getDirVertice(cara.idx[j]));
      }
   }

   glEnd() ;

}

//  Dibujar en modo Sombreado Suave

void Drawer::dibujarSombreadoSuave(Malla &malla){
   bool tiene_coo_tex=malla.getCoordTextFilled();

   glShadeModel(GL_SMOOTH);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   
   glVertexPointer( 3, GL_FLOAT, 0, malla.getVertices() );
   glNormalPointer( GL_FLOAT, 0, malla.getNormalesVertices() );
   if(tiene_coo_tex)   glTexCoordPointer( 2, GL_FLOAT, 0, malla.getCoordTextura() );

   glEnableClientState( GL_VERTEX_ARRAY );
   glEnableClientState( GL_NORMAL_ARRAY );
   if(tiene_coo_tex) glEnableClientState( GL_TEXTURE_COORD_ARRAY );

   glDrawElements( GL_TRIANGLES, malla.getNumCaras()*3, GL_UNSIGNED_INT, malla.getCaras());

   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_NORMAL_ARRAY );
   if(tiene_coo_tex) glDisableClientState( GL_TEXTURE_COORD_ARRAY );

}


// *********************************************************************
// **
// ** Funciones públicas para dibujar
// **
// *********************************************************************

void Drawer::dibujarMalla(Malla &malla){
   switch(modo_activo){
      case PUNTOS:
         dibujarPuntos(malla);
         break;
      case ALAMBRE:
         glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         dibujarTriangulos(malla);
         break;
      case SOLIDO:
         glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         dibujarTriangulos(malla);
         break;
      case AJEDREZ:
         dibujarAjedrez(malla);
         break;

      case NORMALES:
         dibujarNormales(malla,modo_normales_activo);
         break;
      case SOM_PLANO:
         dibujarSombreadoPlano(malla);
         break;
      case SOM_SUAVE:
         dibujarSombreadoSuave(malla);
         break;
   }
}

void Drawer::dibujarMalla(Malla &malla, Material &material){
   if(modo_activo==SOM_PLANO or modo_activo==SOM_SUAVE){
      glEnable(GL_LIGHTING);
      glDisable(GL_COLOR_MATERIAL);
   }
   else{
      glDisable(GL_LIGHTING);
      glEnable(GL_COLOR_MATERIAL);
   }

   material.activarMaterial();
   dibujarMalla(malla);
}


// *********************************************************************
// **
// ** Funciones gestoras de eventos
// **
// *********************************************************************

// ---------------------------------------------------------------------
// cambiar el modo de visualizacion activo

void Drawer::cambiarModoVisualizacion(ModoVisualizacion nuevo_modo){

   if(nuevo_modo==SOM_PLANO or nuevo_modo==SOM_SUAVE){
      glEnable(GL_LIGHTING);
      glDisable(GL_COLOR_MATERIAL);
   }
   else{
      glDisable(GL_LIGHTING);
      glEnable(GL_COLOR_MATERIAL);
   }

   modo_activo=nuevo_modo;
}
