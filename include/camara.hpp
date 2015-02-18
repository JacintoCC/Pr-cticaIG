#ifndef CAMARA_HPP
#define CAMARA_HPP

#include "tuplas.hpp"

enum TipoCamara{PERSPECTIVA,ORTOGONAL};

class Camara{
private:

   float 
      camara_angulo_x ,
      camara_angulo_y ;   
   float 
      frustum_factor_escala ,
      frustum_ancho ,          
      frustum_dis_del ,    
      frustum_dis_tra ;        
   int 
      ventana_tam_x,
      ventana_tam_y;
   float
      reinicio[6];

   Tupla3f VRP,VPN,VUP;

   TipoCamara tipo_camara;

public:
   Camara(float cam_x, float cam_y, float fr_escala, float fr_ancho, float fr_delantera, float fr_trasera,TipoCamara tipo);

   void CambioTamanoVentana(int nuevo_ancho, int nuevo_alto);

   void FijarProyeccion();
   void FijarCamara();
   void MatrizProyeccion();

   void FijarProyeccionPerspectiva();
   void FijarProyeccionOrtogonal();

   void AumentarEscala(float factor){
      frustum_factor_escala*=factor;
   }

   void DisminuirEscala(float factor){
      frustum_factor_escala/=factor;
   }
   void MoverCamara(Tupla3f vector){
      VRP+=vector;
   }
   void ReiniciarCamara();

   void Girar(int giro_y,int giro_x);
   void setVRP(Tupla3f punto_atencion);
};

#endif
