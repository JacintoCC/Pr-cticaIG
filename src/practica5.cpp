// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 5  (implementación)
// **
// *********************************************************************


#include <GL/glut.h>

#include "error-ogl.hpp"
#include "practica5.hpp"
#include "camara.hpp"
#include <iostream>
#include <cmath>

using namespace std;

EscenaGE escena_p5;
Drawer dibujador_p5;

Camara camara_alzado=Camara(0,0,0.1,0.05,1,10.0,PERSPECTIVA);
Camara camara_perfil=Camara(0,-90,0.1,0.05,1,10.0,ORTOGONAL);
Camara camara_planta=Camara(90,0,0.1,0.05,1,10.0,PERSPECTIVA);
Camara camara_examinar=Camara(0,0,0.1,0.05,1,10.0,PERSPECTIVA);
Camara *camara_activa;

GLuint selectBuf[100];

bool boton_der_pulsado=false;
int x_ant,y_ant;

// ---------------------------------------------------------------------
// función para implementar en la práctica 5 para gestionar los eventos

bool P5_FGE_PulsarTeclaNormal( unsigned char tecla, int x_raton, int y_raton ){

   bool redisp=true;

   switch(toupper(tecla)){
      case '+' :
         camara_activa->AumentarEscala(1.05);
         break;
      case '-' :
         camara_activa->DisminuirEscala(1.05);
         break;
      case 'E':         
         if(camara_activa!=&camara_examinar) camara_activa->MoverCamara(Tupla3f(0,-0.1,0));
         break;
      case 'A':
         if(camara_activa!=&camara_examinar) camara_activa->MoverCamara(Tupla3f(0.1,0,0));
         break;
      case 'X':         
         if(camara_activa!=&camara_examinar) camara_activa->MoverCamara(Tupla3f(0,0.1,0));
         break;
      case 'D':         
         if(camara_activa!=&camara_examinar) camara_activa->MoverCamara(Tupla3f(-0.1,0,0));
         break;
      case 'W':         
         if(camara_activa!=&camara_examinar)camara_activa->MoverCamara(Tupla3f(0,0,0.1));
         break;
      case 'S':         
         if(camara_activa!=&camara_examinar) camara_activa->MoverCamara(Tupla3f(0,0,-0.1));
         break;
      case 'R':         
         if(camara_activa!=&camara_examinar) camara_activa->ReiniciarCamara();
         break;
      default:
         redisp=false;
         break;
   }

   return redisp;
}

bool P5_FGE_PulsarTeclaEspecial( unsigned char tecla, int x_raton, int y_raton ){
   bool redisp=true;

   switch(tecla){
      case GLUT_KEY_F1:
         camara_activa=&camara_alzado;
         break;
      case GLUT_KEY_F2:
         camara_activa=&camara_planta;
         break;
      case GLUT_KEY_F3:
         camara_activa=&camara_perfil;
         break;
      default:
         redisp=false;
         break;
   }

   return redisp;
}

bool P5_FGE_Pulsar_Raton( int tecla, int estado, int x_raton, int y_raton )
{
   bool redisp = true;
   
   switch(tecla){
      case GLUT_LEFT_BUTTON:
         if(estado==GLUT_DOWN)
            P5_pick(x_raton,y_raton);
         break;
      case GLUT_RIGHT_BUTTON:
         if(estado==GLUT_DOWN){
            boton_der_pulsado=true;
            x_ant=x_raton;
            y_ant=y_raton;
         }
         else boton_der_pulsado=false;
         break;
      default:
         redisp=false;
   }

   return redisp;
}

bool P5_FGE_Mover_Raton( int x_raton, int y_raton )
{
   bool redisp = true;
   
   if(boton_der_pulsado){
      camara_activa->Girar(x_ant-x_raton,y_ant-y_raton);
      x_ant=x_raton;
      y_ant=y_raton;
   }

   return redisp;
}

bool P5_procesarHits(GLint hits){
   GLuint names, *ptr, minZ,*ptrNames, numberOfNames=0;
   ptr=(GLuint *) selectBuf;
   minZ=-0xffffffff;
   for(int i=0;i<hits;i++){
      names=*ptr;
      ptr++;
      if(*ptr>minZ){
         numberOfNames=names;
         minZ = *ptr;
         ptrNames=ptr+2;
      }
      ptr+=names+2;
   }
   ptr=ptrNames;
   escena_p5.visualizar(ptr);
   Tupla3f centro=escena_p5.centro(ptr);
   camara_activa=&camara_examinar;
   camara_activa->setVRP(centro);

   return minZ==-0xffffffff;
}

bool P5_pick(int x_raton, int y_raton){
   GLint hits,viewport[4];
   glGetIntegerv (GL_VIEWPORT, viewport);
   glSelectBuffer(100,selectBuf);
   
   glRenderMode (GL_SELECT);
      glInitNames();
      glMatrixMode (GL_PROJECTION);
      glLoadIdentity ();
      gluPickMatrix (x_raton,(viewport[3] - y_raton),5.0,5.0, viewport);
      camara_activa->MatrizProyeccion();
      glMatrixMode (GL_MODELVIEW);
      escena_p5.visualizar();

   hits=glRenderMode(GL_RENDER);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   camara_activa->FijarProyeccion();

   escena_p5.desseleccionar();

   if(hits!=0) return P5_procesarHits(hits);
   else{
      camara_activa=&camara_alzado;
      return false;
   } 
}

void P5_FijarProyeccion(){
   camara_activa->FijarProyeccion();
}
void P5_FijarCamara(){
   camara_activa->FijarCamara();
}
void P5_FGE_CambioTamano(int nuevo_alto,int nuevo_ancho){
   camara_activa->CambioTamanoVentana( nuevo_alto,nuevo_ancho);
}

// ---------------------------------------------------------------------
// función para implementar en la práctica 5 para inicialización
// se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL.

void P5_Inicializar( int argc, char *argv[] )
{
   P5_MontarEscena(&escena_p5,&dibujador_p5);
   camara_activa=&camara_alzado;
   dibujador_p5.cambiarModoVisualizacion(SOM_SUAVE);
}

// ---------------------------------------------------------------------
// función a implementar en la práctica 5 para dibujar los objetos

void P5_DibujarObjetos()
{
   P5_SetDibujador(&dibujador_p5);
   escena_p5.visualizar();
}
