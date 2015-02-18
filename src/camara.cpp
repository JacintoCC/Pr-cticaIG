#include "camara.hpp"
#include <GL/glut.h>

Camara::Camara(float cam_x, float cam_y, float fr_escala, float fr_ancho, float fr_delantera, float fr_trasera,TipoCamara tipo){
   reinicio[0]=camara_angulo_x=cam_x;
   reinicio[1]=camara_angulo_y=cam_y;   
   reinicio[2]=frustum_factor_escala=fr_escala;  
   reinicio[3]=frustum_ancho=fr_ancho;
   reinicio[4]=frustum_dis_del=fr_delantera;  
   reinicio[5]=frustum_dis_tra=fr_trasera;
   tipo_camara=tipo;

   ventana_tam_x=1024;
   ventana_tam_y=800; 
}

void Camara::CambioTamanoVentana(int nuevo_ancho, int nuevo_alto){
   ventana_tam_x  = nuevo_ancho;
   ventana_tam_y  = nuevo_alto ;
   
   glViewport( 0, 0, ventana_tam_x, ventana_tam_y );
   FijarProyeccion();
}

void Camara::FijarProyeccion(){     
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   MatrizProyeccion();

   glTranslatef( VRP.coo[0], VRP.coo[1], VRP.coo[2]-0.5*(frustum_dis_del+frustum_dis_tra));
   
   glScalef( frustum_factor_escala, frustum_factor_escala,  frustum_factor_escala );
}

void Camara::MatrizProyeccion(){
   if(tipo_camara==ORTOGONAL)
      FijarProyeccionOrtogonal();
   else
      FijarProyeccionPerspectiva();
}

void Camara::FijarProyeccionPerspectiva(){
   const GLfloat ratioYX = GLfloat( ventana_tam_y )/GLfloat( ventana_tam_x );

   // (3) proyectar en el plano de visión
   glFrustum
   (  -frustum_ancho,
      +frustum_ancho,
      -frustum_ancho*ratioYX,
      +frustum_ancho*ratioYX,
      +frustum_dis_del,
      +frustum_dis_tra
   );
   
}

void Camara::FijarProyeccionOrtogonal(){
   const GLfloat ratioYX = GLfloat( ventana_tam_y )/GLfloat( ventana_tam_x );

   // (3) proyectar en el plano de visión
   glOrtho
   (  -frustum_ancho,
      +frustum_ancho,
      -frustum_ancho*ratioYX,
      +frustum_ancho*ratioYX,
      +frustum_dis_del,
      +frustum_dis_tra
   );
   
}

void Camara::FijarCamara(){
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   
   glRotatef(camara_angulo_x,1,0,0);
   glRotatef(camara_angulo_y,0,1,0);

}

void Camara::ReiniciarCamara(){
   camara_angulo_x=reinicio[0];
   camara_angulo_y=reinicio[1];   
   frustum_factor_escala=reinicio[2]; 
   frustum_ancho=reinicio[3];
   frustum_dis_del=reinicio[4];
   frustum_dis_tra=reinicio[5];

   VRP=Tupla3f(0,0,0);
}

void Camara::Girar(int giro_y,int giro_x){
   camara_angulo_y+=giro_y*M_PI/15.0;
   camara_angulo_x+=giro_x*M_PI/15.0; 
}

void Camara::setVRP(Tupla3f punto_atencion){
   VRP=punto_atencion;
}
