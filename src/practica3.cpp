// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 3  (implementación)
// **
// *********************************************************************


#include <GL/glut.h>

#include "error-ogl.hpp"
#include "practica3.hpp"
#include "escena.hpp"
#include "transformacion.hpp"
#include <iostream>
#include <cmath>

using namespace std;

// ---------------------------------------------------------------------
// Grados de libertad

float rot_minutero=0;
float rot_engranaje=0;
float rot_engranaje_inverso=M_PI/7;

float rot_horario=0;

bool mov_pajaro=false;

Tupla3f posicion_pajaro=Tupla3f(0,1.15,-0.25);

float rot_escena_vaca=0.0;
float rot_vaca=-M_PI/2.0;

// ---------------------------------------------------------------------
// Velocidades

float vel_reloj_reserva=M_PI/1800.0,velocidad_reloj=M_PI/1800.0;
float vel_pajaro_reserva=0.01,velocidad_pajaro=0.01;
float vel_vaca_reserva=-M_PI/1000.0,velocidad_vaca=-M_PI/1000.0;

// ---------------------------------------------------------------------
// Escena a dibujar en la práctica 3

MatrizTranslacion translacion_paj=MatrizTranslacion(&posicion_pajaro);
MatrizEscalado escalado_paj=MatrizEscalado(Tupla3f(0.1,0.1,0.1));
MatrizRotacion rotacion_paj=MatrizRotacion(Tupla3f(1,0,0),14*M_PI/10.0);
Malla malla_pajaro;
ElementoSimple pajaro;
EscenaGE escena_pajaro;


MatrizEscalado escalado_casa=MatrizEscalado(Tupla3f(1.05,0.7,0.4));
MatrizTranslacion translacion_casa=MatrizTranslacion(Tupla3f(0.8,-2,-2.25));
MatrizRotacion rotacion_casa=MatrizRotacion(Tupla3f(0,1,0),M_PI/2.0);
Malla malla_casa;
ElementoSimple casa;
EscenaGE escena_casa;

MatrizRotacion rotacion_aguja=MatrizRotacion(Tupla3f(0,0,1),-M_PI/2.0);
MatrizTranslacion translacion_aguja=MatrizTranslacion(Tupla3f(-0.3,0,0.1));
MatrizEscalado escalado_aguja=MatrizEscalado(Tupla3f(0.1,0.1,0.1));
Malla malla_aguja;
ElementoSimple aguja;
EscenaGE escena_aguja;

MatrizTranslacion translacion_minutero=MatrizTranslacion(Tupla3f(0,0,-0.03));
MatrizRotacion rotacion_minutero=MatrizRotacion(Tupla3f(0,0,1),&rot_minutero);
EscenaGE escena_minutero;

MatrizEscalado escalado_horario=MatrizEscalado(Tupla3f(0.7,0.7,1));
MatrizRotacion rotacion_horario=MatrizRotacion(Tupla3f(0,0,1),&rot_horario);
EscenaGE escena_horario;

MatrizRotacion rotacion_engranaje=MatrizRotacion(Tupla3f(0,0,1),&rot_engranaje);
MatrizEscalado escalado_engranaje=MatrizEscalado(Tupla3f(0.2,0.2,-0.2));
Malla malla_engranaje;
ElementoSimple engranaje;
EscenaGE escena_engranaje1;

MatrizEscalado escalado_engranaje2=MatrizEscalado(Tupla3f(0.85,0.85,0.85));
MatrizTranslacion translacion_engranaje2=MatrizTranslacion(Tupla3f(0.2,0.4,0));
MatrizRotacion rotacion_engranaje2=MatrizRotacion(Tupla3f(0,0,1),&rot_engranaje_inverso);
EscenaGE escena_engranaje2;

MatrizEscalado escalado_engranaje3=MatrizEscalado(Tupla3f(1.2,1.2,1.2));
MatrizTranslacion translacion_engranaje3=MatrizTranslacion(Tupla3f(-0.1,0.55,0));
EscenaGE escena_engranaje3;

EscenaGE escena_engranajes;

MatrizRotacion rotacion_escena_vaca=MatrizRotacion(Tupla3f(0,1,0),&rot_escena_vaca);
MatrizTranslacion translacion_vaca=MatrizTranslacion(Tupla3f(0.3,-0.8,0));
MatrizEscalado escalado_vaca=MatrizEscalado(Tupla3f(0.1,0.1,0.1));
MatrizRotacion rotacion_vaca=MatrizRotacion(Tupla3f(0,1,0),&rot_vaca);
Malla malla_vaca;
ElementoSimple vaca;
EscenaGE escena_vaca;


MatrizTranslacion translacion_base=MatrizTranslacion(Tupla3f(0.0,-0.8,0.05));
MatrizEscalado escalado_base=MatrizEscalado(Tupla3f(1.5,-0.1,1.5));
Malla malla_base;
ElementoSimple base;
EscenaGE escena_base;

Drawer dibujador_p3;
EscenaGE escena;


// Materiales
Material material_madera;
Material material_plumas;
Material material_aguja;
Material material_vaca;
Material material_engranaje;

// ---------------------------------------------------------------------
// función para implementar en la práctica 3 para gestionar los eventos
// referentes a la práctica 3 para la modificación de los grados de
// libertad

bool P3_FGE_PulsarTeclaNormal( unsigned char tecla){

   bool redisp=true;

   switch(tecla){
      case '1':         
         dibujador_p3.cambiarModoVisualizacion(SOLIDO);
         break;
      case '2':         
         dibujador_p3.cambiarModoVisualizacion(SOM_PLANO);
         break;
      case '3':         
         dibujador_p3.cambiarModoVisualizacion(SOM_SUAVE);
         break;
      case 'z':
         rot_minutero-=M_PI/30;
         rot_engranaje+=M_PI/15;
         rot_engranaje_inverso-=2*M_PI/15;
         break;
      case 'Z':
         rot_minutero+=M_PI/30;
         rot_engranaje-=M_PI/15;
         rot_engranaje_inverso+=2*M_PI/15;
         break;
      case 'x':
         rot_horario-=M_PI/180;
         break;
      case 'X':
         rot_horario+=M_PI/180;
         break;
      case 'c':
         if(velocidad_pajaro!=0)
            posicion_pajaro.coo[2]+=0.05*(velocidad_pajaro/abs(velocidad_pajaro));
         else
            posicion_pajaro.coo[2]+=0.05*(vel_pajaro_reserva/abs(vel_pajaro_reserva));
         break;
      case 'C':
         if(velocidad_pajaro!=0)
            posicion_pajaro.coo[2]-=0.05*(velocidad_pajaro/abs(velocidad_pajaro));
         else
            posicion_pajaro.coo[2]-=0.05*(vel_pajaro_reserva/abs(vel_pajaro_reserva));
         break;
      case 'v':
         if(velocidad_vaca!=0)
            rot_escena_vaca+=M_PI/500.0*(velocidad_vaca/abs(velocidad_vaca));
         else
            rot_escena_vaca+=M_PI/500.0*(vel_vaca_reserva/abs(vel_vaca_reserva));
         
         rot_vaca-=M_PI/500.0;

         break;
      case 'V':
         if(velocidad_vaca!=0)
            rot_escena_vaca-=M_PI/500.0*(velocidad_vaca/abs(velocidad_vaca));
         else
            rot_escena_vaca-=M_PI/500.0*(vel_vaca_reserva/abs(vel_vaca_reserva));
         
         rot_vaca+=M_PI/500.0;
         break;
      case 'b':
         velocidad_reloj+=M_PI/18000.0;
         break;
      case 'B':
         velocidad_reloj-=M_PI/18000.0;
         break;
      case 'n':
         velocidad_pajaro+=0.001;
         break;
      case 'N':
         velocidad_pajaro-=0.001;
         break;
      case 'm':
         velocidad_vaca+=-M_PI/10000.0;
         break;
      case 'M':
         velocidad_vaca-=-M_PI/10000.0;
         break;
      case 'p':
      case 'P':
         if(velocidad_reloj>0){
            vel_pajaro_reserva=velocidad_pajaro;
            vel_reloj_reserva=velocidad_reloj;
            vel_vaca_reserva=velocidad_vaca;
            velocidad_pajaro=0;
            velocidad_reloj=0;
            velocidad_vaca=0;
         }
         else{
            velocidad_reloj=vel_reloj_reserva;
            velocidad_pajaro=vel_pajaro_reserva;
            velocidad_vaca=vel_vaca_reserva;
         }
         break;
      default:
         redisp=false;
         break;
   }

   if(posicion_pajaro.coo[2]>=0.25 or posicion_pajaro.coo[2]<=-0.25){
      velocidad_pajaro*=-1;
      vel_pajaro_reserva*=-1;
   }
   if(posicion_pajaro.coo[2]<=-0.25)
      mov_pajaro=false;
   if(rot_escena_vaca<=-M_PI/2.0 or rot_escena_vaca>=M_PI/2.0){
      velocidad_vaca*=-1;
      vel_vaca_reserva*=-1;
   }

   return redisp;
}

// ---------------------------------------------------------------------
// función para implementar en la práctica 3 para inicialización
// se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL. La malla de puntos se debe crear aquí

void P3_Inicializar( int argc, char *argv[] )
{
   P3_InicializarEscena(&dibujador_p3);
//Crear y situar el cuco
   material_plumas=Material("./img/plumas.jpg",true,Tupla3f(1,0,0),Tupla3f(0,0,1),Tupla4f(0.8,0.8,0.8,1),Tupla4f(0.8,0.8,0.8,1),Tupla4f(0.2,0.2,0.2,1),90);
   malla_pajaro=Malla("./img/Soren.ply");
   pajaro=ElementoSimple(&malla_pajaro,&dibujador_p3,&material_plumas);

   escena_pajaro.incluirHijo(&translacion_paj);
   escena_pajaro.incluirHijo(&escalado_paj);
   escena_pajaro.incluirHijo(&rotacion_paj);
   escena_pajaro.incluirHijo(&pajaro);


//Crear y situar el soporte del reloj
   material_madera=Material("./img/text-madera.jpg",true,Tupla3f(0,1,0),Tupla3f(1,0,0),Tupla4f(1,1,1,0.5),Tupla4f(0.5,0.2,0.2,0.5),Tupla4f(0.5,0.2,0.2,0.5),50);
   malla_casa=Malla("./img/Casa.ply");
   casa=ElementoSimple(&malla_casa,&dibujador_p3,&material_madera);

   escena_casa.incluirHijo(&escalado_casa);
   escena_casa.incluirHijo(&translacion_casa);
   escena_casa.incluirHijo(&rotacion_casa);
   escena_casa.incluirHijo(&casa);

//Crear y situar la aguja para la creación del minutero y el horario
   material_aguja=Material(Tupla4f(0.01,0.01,0.01,1),Tupla4f(0.1,0.1,0.1,1),Tupla4f(0.9,0.9,0.9,1),10.0);
   malla_aguja=Malla("./img/aguja.ply");
   aguja=ElementoSimple(&malla_aguja,&dibujador_p3,&material_aguja);

   escena_aguja.incluirHijo(&rotacion_aguja);
   escena_aguja.incluirHijo(&translacion_aguja);
   escena_aguja.incluirHijo(&escalado_aguja);
   escena_aguja.incluirHijo(&aguja);

   escena_minutero.incluirHijo(&translacion_minutero);
   escena_minutero.incluirHijo(&rotacion_minutero);
   escena_minutero.incluirHijo(&escena_aguja);

   escena_horario.incluirHijo(&rotacion_horario);
   escena_horario.incluirHijo(&escalado_horario);
   escena_horario.incluirHijo(&escena_aguja);

// Crear y situar los engranajes
   material_engranaje=Material(Tupla4f(0.2,0.2,0.2,1.0),Tupla4f(0.5,0.5,0.5,1),Tupla4f(0.5,0.5,0.5,1),80);
   malla_engranaje=Malla("./img/engranaje.ply");
   engranaje=ElementoSimple(&malla_engranaje,&dibujador_p3,&material_engranaje);

   escena_engranaje1.incluirHijo(&rotacion_engranaje);
   escena_engranaje1.incluirHijo(&escalado_engranaje);
   escena_engranaje1.incluirHijo(&engranaje);

   escena_engranaje2.incluirHijo(&escalado_engranaje2);
   escena_engranaje2.incluirHijo(&translacion_engranaje2);
   escena_engranaje2.incluirHijo(&rotacion_engranaje2);
   escena_engranaje2.incluirHijo(&escena_engranaje1);

   escena_engranaje3.incluirHijo(&escalado_engranaje3);
   escena_engranaje3.incluirHijo(&translacion_engranaje3);
   escena_engranaje3.incluirHijo(&escena_engranaje1);

   escena_engranajes.incluirHijo(&escena_engranaje1);
   escena_engranajes.incluirHijo(&escena_engranaje2);
   escena_engranajes.incluirHijo(&escena_engranaje3);

// Crear y situar la vaca
   material_vaca=Material("./img/vaca.jpg",true,Tupla3f(1,0,0),Tupla3f(0,0,1),Tupla4f(0.8,0.8,0.8,1),Tupla4f(0.5,0.5,0.5,1),Tupla4f(0.2,0.2,0.2,1),80);
   malla_vaca=Malla("./img/cow.ply");
   vaca=ElementoSimple(&malla_vaca,&dibujador_p3,&material_vaca);

   escena_vaca.incluirHijo(&rotacion_escena_vaca);
   escena_vaca.incluirHijo(&translacion_vaca);
   escena_vaca.incluirHijo(&escalado_vaca);
   escena_vaca.incluirHijo(&rotacion_vaca);
   escena_vaca.incluirHijo(&vaca);

// Crear y situar la base
   
   malla_base=Malla("./img/cilindro.ply",50,true);
   base=ElementoSimple(&malla_base,&dibujador_p3,&material_madera);

   escena_base.incluirHijo(&translacion_base);
   escena_base.incluirHijo(&escalado_base);
   escena_base.incluirHijo(&base);
   
//Montar escena

   escena.incluirHijo(&escena_pajaro);
   escena.incluirHijo(&escena_minutero);
   escena.incluirHijo(&escena_horario);
   escena.incluirHijo(&escena_engranajes);
   escena.incluirHijo(&escena_casa);
   escena.incluirHijo(&escena_vaca);
   escena.incluirHijo(&escena_base);

  
   dibujador_p3.cambiarModoVisualizacion(SOLIDO);
}
// ---------------------------------------------------------------------
// función gestora del evento ocioso
void P3_IDLE()
{
   float param,cociente,decimales;

   rot_minutero-=velocidad_reloj;
   rot_horario-=velocidad_reloj/30;
   rot_engranaje+=velocidad_reloj*8;
   rot_engranaje_inverso-=16*velocidad_reloj;

   param=-rot_minutero/(2*M_PI);
   
   decimales=modf(param,&cociente);
   
   if(decimales<=0.005 and mov_pajaro==false){
      mov_pajaro=true;
   }

   if(mov_pajaro){
      posicion_pajaro.coo[2]+=velocidad_pajaro;

      if(posicion_pajaro.coo[2]>=0.25 or posicion_pajaro.coo[2]<=-0.25){
         velocidad_pajaro*=-1;
         vel_pajaro_reserva*=-1;
      }
   
      if(posicion_pajaro.coo[2]<=-0.25)
         mov_pajaro=false;
   }


   rot_escena_vaca+=velocidad_vaca;
   rot_vaca-=abs(velocidad_vaca);
   
   if(rot_escena_vaca<=-M_PI/2.0 or rot_escena_vaca>=M_PI/2.0){
      velocidad_vaca*=-1;
      vel_vaca_reserva*=-1;
   }
   
   glutPostRedisplay();

}
// ---------------------------------------------------------------------
// función a implementar en la práctica 3 para dibujar los objetos

void P3_DibujarObjetos()
{
   escena.visualizar();
}
