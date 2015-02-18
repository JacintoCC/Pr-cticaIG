#include "escena.hpp"

void EscenaGE::visualizar(){
   glPushMatrix();
   glPushName(0);
   for(unsigned int i=0; i<hijos.size(); i++){
      glLoadName(i);
      hijos.at(i)->visualizar();
   }
   glPopName();
   glPopMatrix();
}

void EscenaGE::visualizar(GLuint * ptr){
   int siguiente_seleccionado=*ptr;
   hijos.at(siguiente_seleccionado)->visualizar(ptr+1);

   glPushMatrix();
   glPushName(0);
   for(int i=0; i<hijos.size(); i++){
      if(i!=siguiente_seleccionado){
         glLoadName(i);
         hijos.at(i)->visualizar();
      }
   }
   glPopName();
   glPopMatrix();
}

ElementoSimple::ElementoSimple(Malla * malla,Drawer * dibujador){
   this->malla=malla;
   this->dibujador=dibujador;
   material=new Material();
   seleccionado=false;
}

ElementoSimple::ElementoSimple(Malla * malla,Drawer * dibujador, Material * material){
   this->malla=malla;
   this->dibujador=dibujador;
   this->material=material;
   seleccionado=false;
}

ElementoSimple::ElementoSimple(Malla * malla,Drawer * dibujador, Tupla4f color){
   this->malla=malla;
   this->dibujador=dibujador;
   this->material=new Material(color);
   seleccionado=false;
}

void  ElementoSimple::visualizar(){
   if(seleccionado){
      Material mat_seleccionado=Material(Tupla4f(1,0,0,1));
      dibujador->dibujarMalla(*malla,mat_seleccionado);
   }
   else
      dibujador->dibujarMalla(*malla,*material);
}

void ElementoSimple::visualizar(GLuint * ptr){
   seleccionado=true;
   glColor3f(1,0,0);
   dibujador->dibujarMalla(*malla);
}
