#include "textura.hpp"

Textura::Textura(char const * nombreFichero,bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs,Tupla3f punto_origen){
   Tupla3f u_t,u_s;

   glGenTextures( 1, &idText );
   pimg = new Imagen(nombreFichero);

   tamx = pimg->tamX();
   tamy = pimg->tamY();
   texels = pimg->leerPixels();

   gen_autom=gen_aut_coordenadas;

   u_t=normalized(ct);
   u_s=normalized(cs);

   for(int i=0;i<3;i++){
      coor_t.coo[i]=u_t.coo[i];
      coor_s.coo[i]=u_s.coo[i];
   }
   
   coor_t.coo[3]=-(punto_origen|u_t);
   coor_s.coo[3]=-(punto_origen|u_s);

   activar();
   gluBuild2DMipmaps( GL_TEXTURE_2D,GL_RGB,tamx,tamy,GL_RGB,GL_UNSIGNED_BYTE,texels);

}

Textura::Textura(char const * nombreFichero,bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs){
   Tupla3f u_t,u_s;

   glGenTextures( 1, &idText );
   pimg = new Imagen(nombreFichero);

   tamx = pimg->tamX();
   tamy = pimg->tamY();
   texels = pimg->leerPixels();

   gen_autom=gen_aut_coordenadas;

   u_t=normalized(ct);
   u_s=normalized(cs);

   for(int i=0;i<3;i++){
      coor_t.coo[i]=u_t.coo[i];
      coor_s.coo[i]=u_s.coo[i];
   }
   
   coor_t.coo[3]=0;
   coor_s.coo[3]=0;

   activar();
   gluBuild2DMipmaps( GL_TEXTURE_2D,GL_RGB,tamx,tamy,GL_RGB,GL_UNSIGNED_BYTE,texels);

}
