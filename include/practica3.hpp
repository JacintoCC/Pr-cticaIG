// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Práctica 3  (declaraciones públicas)
// **
// *********************************************************************

#include <vector>
#include "escena.hpp"
#include "drawer.hpp"

#ifndef IG_PRACTICA3_HPP
#define IG_PRACTICA3_HPP

void P3_InicializarEscena( Drawer *dibujador ) ;
void P3_MontarEscena( EscenaGE *escena, Drawer *dibujador ) ;
void P3_SetDibujador( Drawer *dibujador ) ;

void P3_IDLE();
bool P3_FGE_PulsarTeclaNormal( unsigned char tecla);
void P3_DibujarObjetos(); 
void P3_Inicializar( int argc, char *argv[] ) ;

#endif
