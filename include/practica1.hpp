// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Práctica 1  (declaraciones públicas)
// **
// *********************************************************************

#include <vector>
#include "drawer.hpp"

#ifndef IG_PRACTICA1_HPP
#define IG_PRACTICA1_HPP

enum FuenteVisualizacion {CUBO,PLY};

// ---------------------------------------------------------------------
// Métodos principales de la práctica 1

void DibujarCuboPuntos();

bool P1_FGE_PulsarTeclaNormal( unsigned char tecla);
void P1_DibujarObjetos(); 
void P1_Inicializar( int argc, char *argv[] ) ;

#endif
