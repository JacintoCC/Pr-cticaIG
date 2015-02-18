// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Práctica 4  (declaraciones públicas)
// **
// *********************************************************************

#include "escena.hpp"
#include "drawer.hpp"

#ifndef IG_PRACTICA4_HPP
#define IG_PRACTICA4_HPP

void P4_InicializarEscena( Drawer *dibujador ) ;
void P4_MontarEscena( EscenaGE *escena, Drawer *dibujador ) ;
void P4_SetDibujador( Drawer *dibujador ) ;

bool P4_FGE_PulsarTeclaNormal( unsigned char tecla);
void P4_DibujarObjetos(); 
void P4_Inicializar( int argc, char *argv[] ) ;

#endif
