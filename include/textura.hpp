#include <GL/glut.h>
#include "jpg_imagen.hpp"
#include "tuplas.hpp"

#ifndef TEXTURA_HPP
#define TEXTURA_HPP

using namespace jpg;

class Textura{
private:
   Imagen * pimg = NULL ;
   unsigned int tamx;
   unsigned int tamy;
   unsigned char * texels;
   unsigned int idText;
   bool gen_autom;
   Tupla4f coor_t,coor_s;

public:
   Textura(const char * nombreFichero, bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs,Tupla3f punto_origen);
   Textura(const char * nombreFichero, bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs);

   inline void activar(){
      glBindTexture( GL_TEXTURE_2D, idText );
      if(gen_autom){
         glEnable( GL_TEXTURE_GEN_S );
         glEnable( GL_TEXTURE_GEN_T );
         glTexGenfv( GL_S, GL_OBJECT_PLANE, coor_s.coo ) ;
         glTexGenfv( GL_T, GL_OBJECT_PLANE, coor_t.coo ) ;
      }
      else{
         glDisable( GL_TEXTURE_GEN_S );
         glDisable( GL_TEXTURE_GEN_T );
      }
   }
};

#endif
