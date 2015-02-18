#include "material.hpp"
#include <GL/glut.h>

Material::Material(){
   ambiental=Tupla4f(0,0,1,1);
   difusa=Tupla4f(0.2,0.2,1,1);
   especular=Tupla4f(1,1,1,1);
   brillo=0;
}

Material::Material(Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, float brillo){
   this->ambiental=ambiental;
   this->difusa=difusa;
   this->especular=especular;
   this->brillo=brillo;
}

Material::Material(Tupla4f color){
   ambiental=color;
   difusa=color;
   especular=color;
   brillo=0;
}
   
Material::Material(const char * nombreFichero,bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs){
   textura=new Textura(nombreFichero, gen_aut_coordenadas,ct,cs);

   ambiental=Tupla4f(0.2,0.2,0.2,1);
   difusa=Tupla4f(0.8,0.8,0.8,1);
   especular=Tupla4f(0.1,0.1,0.1,1);
   brillo=0;
}

Material::Material(const char * nombreFichero,bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs,Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, float brillo){
   textura=new Textura(nombreFichero, gen_aut_coordenadas,ct,cs);

   this->ambiental=ambiental;
   this->difusa=difusa;
   this->especular=especular;
   this->brillo=brillo;
}

void Material::setColores(Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, float brillo){
   this->ambiental=ambiental;
   this->difusa=difusa;
   this->especular=especular;
   this->brillo=brillo;
}

void Material::setTextura(const char * nombreFichero, bool gen_aut_coordenadas,Tupla3f ct, Tupla3f cs){
   textura=new Textura(nombreFichero,gen_aut_coordenadas,ct,cs);
}

void Material::activarMaterial(){
   glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambiental.coo ) ;
   glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, difusa.coo ) ;
   glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, especular.coo ) ;
   glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, brillo );
   
   glColor4fv(ambiental.coo);

   if(textura!=NULL){
      glEnable(GL_TEXTURE_2D);
      textura->activar();
   }
   else{
      glDisable(GL_TEXTURE_2D);
   }
}

