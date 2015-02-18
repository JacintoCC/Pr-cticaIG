#include <vector>
#include "malla.hpp"
#include "luminaria.hpp"
#include "material.hpp"

#ifndef DRAWER_HPP
#define DRAWER_HPP

// ---------------------------------------------------------------------
// Tipos enumerados para determinar el modo y la fuente de visualización 

enum ModoVisualizacion {PUNTOS,ALAMBRE,SOLIDO,AJEDREZ,NORMALES,SOM_PLANO,SOM_SUAVE};

class Drawer{
private:
   // ---------------------------------------------------------------------
   // variables que determinan el modo de visualización y de visualizar las normales

   ModoVisualizacion modo_activo;
   int modo_normales_activo;
   vector<Luminaria *> luces;

   // ---------------------------------------------------------------------
   // Métodos para dibujar objetos

   void dibujarPuntos(Malla & malla);
   void dibujarTriangulos(Malla & malla);
   void dibujarAjedrez(Malla & malla);

   void dibujarNormales(Malla & malla, int modo);

   void dibujarNormalesColorCara(Malla & malla);
   void dibujarNormalesColorVertice(Malla & malla);
   void dibujarNormalesSegmentoVertice(Malla &malla);
   void dibujarNormalesSegmentoCara(Malla &malla);

   void dibujarSombreadoPlano(Malla &malla);
   void dibujarSombreadoSuave(Malla &malla);

public:
   Drawer(){
      modo_normales_activo=-1;
      modo_activo=PUNTOS;
   };

   void dibujarMalla(Malla &malla);
   void dibujarMalla(Malla &malla, Material &material);

   // ---------------------------------------------------------------------
   // Funciones gestoras de eventos

   void cambiarModoVisualizacion(ModoVisualizacion nuevo_modo);

   inline void cambiarVisualizacionNormales(){
      modo_normales_activo=(modo_normales_activo+1)%8;
   }

   inline void incluirLuminaria(Luminaria * luz){
      luces.push_back(luz);
      luz->activarLuminaria();
   }

};

#endif
