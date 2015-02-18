#include <GL/glut.h>
#include "transformacion.hpp"
#include "tuplas.hpp"
#include <cmath>
#include <iostream>

using namespace std;

// -------------------------------- Clase Matriz Transformación 

MatrizTransformacion::MatrizTransformacion(){
   for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
         if(i==j) matriz[i][j]=1;
         else     matriz[i][j]=0;
      }
   }
}

// -------------------------------- Clase Matriz Translacion 

MatrizTranslacion::MatrizTranslacion(Tupla3f vector_trans){
   for(int i=0;i<3;i++){
      for(int j=0;j<4;j++){
         if(i==j) matriz[i][j]=1;
         else     matriz[i][j]=0;
      }
   }

   for(int i=0;i<3;i++)
      matriz[3][i]=vector_trans.coo[i];

   matriz[3][3]=1;
}

MatrizTranslacion::MatrizTranslacion(Tupla3f * vector_trans){
   translacion=vector_trans;

   for(int i=0;i<3;i++){
      for(int j=0;j<4;j++){
         if(i==j) matriz[i][j]=1;
         else     matriz[i][j]=0;
      }
   }

   for(int i=0;i<3;i++){
      matriz[3][i]=translacion->coo[i];
   }

   matriz[3][3]=1;
}

void MatrizTranslacion::actualizar(){
   if(translacion!=NULL){
      for(int i=0;i<3;i++){
         matriz[3][i]=translacion->coo[i];
      }
   }
}

// -------------------------------- Clase Matriz Escalado 


MatrizEscalado::MatrizEscalado(Tupla3f vector_esc){
   for(int i=0;i<3;i++){
      for(int j=0;j<4;j++){
         if(i==j) matriz[i][j]=vector_esc.coo[i];
         else     matriz[i][j]=0;
      }
   }

   for(int i=0;i<3;i++)
      matriz[3][i]=0;

   matriz[3][3]=1;
}

MatrizEscalado::MatrizEscalado(Tupla3f * vector_esc){
   escala=vector_esc;

   for(int i=0;i<3;i++){
      for(int j=0;j<4;j++){
         if(i==j) matriz[i][j]=escala->coo[i];
         else     matriz[i][j]=0;
      }
   }

   for(int i=0;i<3;i++)
      matriz[3][i]=0;

   matriz[3][3]=1;
}

void MatrizEscalado::actualizar(){
   if(escala!=NULL){
      for(int i=0;i<3;i++){
         matriz[i][i]=escala->coo[i];
      }   
   }
}

// -------------------------------- Clase Matriz Rotacion 

MatrizRotacion::MatrizRotacion(Tupla3f vector_eje, float angulo){
   float u_x=vector_eje.coo[0],
         u_y=vector_eje.coo[1],
         u_z=vector_eje.coo[2];

   eje=vector_eje;

   matriz[0][0]=cos(angulo)+u_x*u_x*(1-cos(angulo));
   matriz[0][1]=u_y*u_x*(1-cos(angulo))+u_z*sin(angulo);
   matriz[0][2]=u_z*u_x*(1-cos(angulo))-u_y*sin(angulo);

   matriz[1][0]=u_x*u_y*(1-cos(angulo))-u_z*sin(angulo);
   matriz[1][1]=cos(angulo)+u_y*u_y*(1-cos(angulo));
   matriz[1][2]=u_z*u_y*(1-cos(angulo))+u_x*sin(angulo);

   matriz[2][0]=u_x*u_z*(1-cos(angulo))+u_y*sin(angulo);
   matriz[2][1]=u_y*u_z*(1-cos(angulo))-u_x*sin(angulo);
   matriz[2][2]=cos(angulo)+u_z*u_z*(1-cos(angulo));


   for(int i=0;i<3;i++)
      matriz[3][i]=0;

   for(int i=0;i<3;i++)
      matriz[i][3]=0;

   matriz[3][3]=1;
}

MatrizRotacion::MatrizRotacion(Tupla3f vector_eje, float * ang){
   float u_x=vector_eje.coo[0],
         u_y=vector_eje.coo[1],
         u_z=vector_eje.coo[2];

   eje=vector_eje;
   angulo=ang;

   matriz[0][0]=cos(*angulo)+u_x*u_x*(1-cos(*angulo));
   matriz[0][1]=u_y*u_x*(1-cos(*angulo))+u_z*sin(*angulo);
   matriz[0][2]=u_z*u_x*(1-cos(*angulo))-u_y*sin(*angulo);

   matriz[1][0]=u_x*u_y*(1-cos(*angulo))-u_z*sin(*angulo);
   matriz[1][1]=cos(*angulo)+u_y*u_y*(1-cos(*angulo));
   matriz[1][2]=u_z*u_y*(1-cos(*angulo))+u_x*sin(*angulo);

   matriz[2][0]=u_x*u_z*(1-cos(*angulo))+u_y*sin(*angulo);
   matriz[2][1]=u_y*u_z*(1-cos(*angulo))-u_x*sin(*angulo);
   matriz[2][2]=cos(*angulo)+u_z*u_z*(1-cos(*angulo));


   for(int i=0;i<3;i++)
      matriz[3][i]=0;

   for(int i=0;i<3;i++)
      matriz[i][3]=0;

   matriz[3][3]=1;
}

void MatrizRotacion::actualizar(){
   if(angulo!=NULL){
      float u_x=eje.coo[0],
            u_y=eje.coo[1],
            u_z=eje.coo[2];

      matriz[0][0]=cos(*angulo)+u_x*u_x*(1-cos(*angulo));
      matriz[0][1]=u_y*u_x*(1-cos(*angulo))+u_z*sin(*angulo);
      matriz[0][2]=u_z*u_x*(1-cos(*angulo))-u_y*sin(*angulo);

      matriz[1][0]=u_x*u_y*(1-cos(*angulo))-u_z*sin(*angulo);
      matriz[1][1]=cos(*angulo)+u_y*u_y*(1-cos(*angulo));
      matriz[1][2]=u_z*u_y*(1-cos(*angulo))+u_x*sin(*angulo);

      matriz[2][0]=u_x*u_z*(1-cos(*angulo))+u_y*sin(*angulo);
      matriz[2][1]=u_y*u_z*(1-cos(*angulo))-u_x*sin(*angulo);
      matriz[2][2]=cos(*angulo)+u_z*u_z*(1-cos(*angulo));
   }
}
