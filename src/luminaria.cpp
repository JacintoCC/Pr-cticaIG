#include "luminaria.hpp"
#include <cmath>

int Luminaria::num_luces=0;

Luminaria::Luminaria(){
   vector=new Tupla4f(1,0,0,0);
   color=Tupla3f(1,1,1);

   id_luz=num_luces;
   num_luces++;
}

Luminaria::Luminaria(Tupla4f * vector, Tupla3f color){
   this->vector=vector;
   this->color=color;

   id_luz=num_luces;
   num_luces++;
}

void Luminaria::activarLuminaria(){
   glEnable(GL_LIGHT0 + id_luz);
      
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();

      glLoadIdentity();
      glLightfv( GL_LIGHT0 + id_luz, GL_POSITION, vector->coo );
      glLightfv( GL_LIGHT0 + id_luz, GL_AMBIENT, color.coo ) ; 
      glLightfv( GL_LIGHT0 + id_luz, GL_DIFFUSE, color.coo ) ; 
      glLightfv( GL_LIGHT0 + id_luz, GL_SPECULAR, color.coo ) ;

   glPopMatrix();

}

LuminariaCoordEsferica::LuminariaCoordEsferica(){
   alpha=0;
   beta=0;
   vector=new Tupla4f(0,1,0,0);
   color=Tupla3f(1,1,1);

   id_luz=num_luces;
   num_luces++;
}

LuminariaCoordEsferica::LuminariaCoordEsferica(float alpha, float beta, Tupla3f color){
   this->alpha=alpha;
   this->beta=beta;
   this->color=color;

   vector=new Tupla4f(cos(alpha)*sin(beta),sin(alpha)*sin(beta),cos(beta),0);

   id_luz=num_luces;
   num_luces++;
}

void LuminariaCoordEsferica::activarLuminaria(){
   glEnable(GL_LIGHT0 + id_luz);
      
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
      glLoadIdentity();
      *vector=Tupla4f(cos(alpha)*sin(beta),sin(alpha)*sin(beta),cos(beta),0);
      glLightfv( GL_LIGHT0 + id_luz, GL_POSITION, vector->coo );
      glLightfv( GL_LIGHT0 + id_luz, GL_AMBIENT, color.coo ) ; 
      glLightfv( GL_LIGHT0 + id_luz, GL_DIFFUSE, color.coo ) ; 
      glLightfv( GL_LIGHT0 + id_luz, GL_SPECULAR, color.coo ) ;

   glPopMatrix();

}

void LuminariaCoordEsferica::setDireccion(){
      glMatrixMode( GL_MODELVIEW ) ;
      glPushMatrix() ;
         glLoadIdentity();
         *vector=Tupla4f(cos(alpha)*sin(beta),sin(alpha)*sin(beta),cos(beta),0);
         glLightfv( GL_LIGHT0 + id_luz, GL_POSITION, vector->coo );
      glPopMatrix();
}

