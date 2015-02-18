// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Práctica 5  (declaraciones públicas)
// **
// *********************************************************************
#include "drawer.hpp"
#include "escena.hpp"

#ifndef IG_PRACTICA5_HPP
#define IG_PRACTICA5_HPP

void P5_FijarProyeccion();
void P5_FijarCamara();

void P5_MontarEscena( EscenaGE *escena, Drawer *dibujador ) ;
void P5_SetDibujador( Drawer *dibujador ) ;

bool P5_procesarHits(GLint hits);
bool P5_pick(int x_raton, int y_raton);

bool P5_FGE_Pulsar_Raton( int tecla, int estado, int x_raton, int y_raton);
bool P5_FGE_Mover_Raton( int x_raton, int y_raton);
void P5_FGE_CambioTamano(int nuevo_alto,int nuevo_ancho);
bool P5_FGE_PulsarTeclaNormal( unsigned char tecla, int x_raton, int y_raton );
bool P5_FGE_PulsarTeclaEspecial( unsigned char tecla, int x_raton, int y_raton );
void P5_DibujarObjetos(); 
void P5_Inicializar( int argc, char *argv[] ) ;

#endif
