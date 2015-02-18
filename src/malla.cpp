#include "malla.hpp"
#include "file_ply_stl.hpp"
#include <iostream>

using namespace std;

// ---------------------------------------------------------------------
// Método para obtener los vectores pares o impares

vector<Tupla3i> Malla::getCarasParidad(bool par){
   vector<Tupla3i> caras_paridad;

   unsigned int i;
   
   if(par) i=0; else i=1;

   for( ; i<caras.size(); i+=2){
      caras_paridad.push_back(caras.at(i));
   }
   
   return caras_paridad;
}

Malla::Malla(char const * nombreFichero ){
      vector<float> aux_vertices;
      vector<int> aux_caras;
      Tupla3f tupla_vertice;
      Tupla3i tupla_cara;

      ply::read(nombreFichero,aux_vertices,aux_caras);

      vertices.clear();
      caras.clear();

      for(unsigned int i=0; i < aux_vertices.size(); i+=3){
         tupla_vertice=Tupla3f(aux_vertices.at(i),aux_vertices.at(i+1),aux_vertices.at(i+2));
         vertices.push_back(tupla_vertice);
      }

      for(unsigned int j=0; j < aux_caras.size(); j+=3){ 
         tupla_cara=Tupla3i(aux_caras.at(j),aux_caras.at(j+1),aux_caras.at(j+2));
         caras.push_back(tupla_cara);
      }

      generarNormalesCaras();
      generarNormalesVertices();
}


// ---------------------------------------------------------------------
// Método para generar una malla mediante un perfil de revolución

Malla::Malla(char const * nombreFichero, int num_rotaciones, bool cerrar){

      int num_vertices_perfil;
      vector<float> aux_vertices;
      bool tiene_tapa_base;
      bool tiene_tapa_superior;

      ply::read_vertices(nombreFichero,aux_vertices);

      vertices.clear();
      caras.clear();

// Situar Vértices 

      vector<Tupla3f> vertices_tuplas;
      Tupla3f tupla_v;
      float coo_x,coo_y,coo_z;

      if( aux_vertices.at(0)!=0){
         tupla_v=Tupla3f(0,aux_vertices.at(1),0);
         vertices_tuplas.push_back(tupla_v);
      }
      
      for(unsigned int i=0; i<aux_vertices.size()-3; i+=3){
         tupla_v=Tupla3f(aux_vertices.at(i),aux_vertices.at(i+1),aux_vertices.at(i+2));
         vertices_tuplas.push_back(tupla_v);
      }

      if( aux_vertices.at(aux_vertices.size()-3)!=0){
         tupla_v=Tupla3f(aux_vertices.at(aux_vertices.size()-3),aux_vertices.at(aux_vertices.size()-2),0);
         vertices_tuplas.push_back(tupla_v);
      }

      num_vertices_perfil=vertices_tuplas.size()-1;

      for(int j=1; j<=num_rotaciones; j++){
         for(int i=1; i<=num_vertices_perfil;i++){
            coo_x=vertices_tuplas.at(i).coo[0]*cos(2*j*M_PI/num_rotaciones);
            coo_y=vertices_tuplas.at(i).coo[1];
            coo_z=vertices_tuplas.at(i).coo[0]*(-sin(2*j*M_PI/num_rotaciones));
            tupla_v=Tupla3f(coo_x,coo_y,coo_z);
            vertices_tuplas.push_back(tupla_v);
         }
      }
      tupla_v=Tupla3f(0,aux_vertices.at(aux_vertices.size()-2),0);
      vertices_tuplas.push_back(tupla_v);

      setVertices(vertices_tuplas);

// Situar caras

      Tupla3i tupla_c;
      tiene_tapa_base=(cerrar or aux_vertices.at(0)==0);
      tiene_tapa_superior=(cerrar or aux_vertices.at(aux_vertices.size()-3)==0);

   //Tapa inferior
      if(tiene_tapa_base){
         for(int i=0;i<num_rotaciones;i++){
            tupla_c=Tupla3i(0,(i+1)*num_vertices_perfil+1,i*num_vertices_perfil+1);
            caras.push_back(tupla_c);
         }
      }

   //Cuerpo
      for(int j=1; j<num_vertices_perfil; j++){

         for(int i=0; i<num_rotaciones;i++){
            tupla_c=Tupla3i(i*num_vertices_perfil+j,(i+1)*num_vertices_perfil+j,i*num_vertices_perfil+j+1);
            caras.push_back(tupla_c);
         }
         tupla_c=Tupla3i((num_rotaciones-1)*num_vertices_perfil+j,j,(num_rotaciones-1)*num_vertices_perfil+j+1);
         caras.push_back(tupla_c);

         for(int i=0; i<num_rotaciones;i++){
            tupla_c=Tupla3i(i*num_vertices_perfil+j+1,(i+1)*num_vertices_perfil+j,(i+1)*num_vertices_perfil+j+1);
            caras.push_back(tupla_c);
         }
         tupla_c=Tupla3i((num_rotaciones-1)*num_vertices_perfil+j+1,j,j+1);
         caras.push_back(tupla_c);

      }

   //Tapa superior
      if(tiene_tapa_superior){
         for(int i=0;i<num_rotaciones;i++){
            tupla_c=Tupla3i((i+1)*num_vertices_perfil,(i+2)*num_vertices_perfil,(num_rotaciones+1)*num_vertices_perfil+1);
            caras.push_back(tupla_c);
         }
         tupla_c=Tupla3i(num_rotaciones*num_vertices_perfil,num_vertices_perfil,(num_rotaciones+1)*num_vertices_perfil+1);
         caras.push_back(tupla_c);
      }

      generarNormalesCaras();
      generarNormalesVertices();
      generarCoordTextura(num_rotaciones, num_vertices_perfil,tiene_tapa_base,tiene_tapa_superior);
}

// ---------------------------------------------------------------------
// Método para generar los vectores normales a las caras de una malla

void Malla::generarNormalesCaras(){
   Tupla3f normal;
   for (int i=0; i<getNumCaras(); i++){
      normal=(vertices.at(caras.at(i).idx[1])-vertices.at(caras.at(i).idx[0]))*(vertices.at(caras.at(i).idx[2])-vertices.at(caras.at(i).idx[1]));
      normal=normalized(normal);
      normales_caras.push_back(normal);
   }
}

void Malla::generarNormalesVertices(){
   Tupla3f inic=Tupla3f(0,0,0);
   Tupla3f normal;

   normales_vertices=vector<Tupla3f> (getNumVertices(),inic);

   for (int i=0; i<getNumCaras(); i++){
      normal=normales_caras.at(i);

      normales_vertices.at(caras.at(i).idx[0])=normal+normales_vertices.at(caras.at(i).idx[0]);
      normales_vertices.at(caras.at(i).idx[1])=normal+normales_vertices.at(caras.at(i).idx[1]);
      normales_vertices.at(caras.at(i).idx[2])=normal+normales_vertices.at(caras.at(i).idx[2]);
   }

   for (int j=0; j<getNumVertices(); j++){
      normales_vertices.at(j)=normalized(normales_vertices.at(j));
   }
}

// ---------------------------------------------------------------------
// Método para obtener las normales a los vértices mediante segmentos

vector<Tupla3f> Malla::vectorCentrosYNormales(){
   float coo_x,coo_y,coo_z;
   vector<Tupla3f> centros_y_normales;
   Tupla3f centro,normal;

   for(int i=0;i<getNumCaras();i++){
      coo_x=(vertices.at(caras.at(i).idx[0]).coo[0]+vertices.at(caras.at(i).idx[1]).coo[0]+vertices.at(caras.at(i).idx[2]).coo[0])/3.0;
      coo_y=(vertices.at(caras.at(i).idx[0]).coo[1]+vertices.at(caras.at(i).idx[1]).coo[1]+vertices.at(caras.at(i).idx[2]).coo[1])/3.0;
      coo_z=(vertices.at(caras.at(i).idx[0]).coo[2]+vertices.at(caras.at(i).idx[1]).coo[2]+vertices.at(caras.at(i).idx[2]).coo[2])/3.0;

      centro=Tupla3f(coo_x,coo_y,coo_z);
      normal=0.1*getTamano()*normales_caras.at(i);
      centros_y_normales.push_back(centro);
      centros_y_normales.push_back(centro+normal);
   }

   return centros_y_normales;
}

// ---------------------------------------------------------------------
// Método para obtener las normales a las caras mediante segmentos salientes de sus centros

vector<Tupla3f> Malla::vectorVerticesYNormales(){
   vector<Tupla3f> vert_y_normales;
   Tupla3f tupla;

   for(int i=0;i<getNumVertices();i++){
      tupla=vertices.at(i)+(0.1*getTamano()*normales_vertices.at(i));
      vert_y_normales.push_back(vertices.at(i));
      vert_y_normales.push_back(tupla);
   }

   return vert_y_normales;
}

// ---------------------------------------------------------------------
// Método para obtener los colores relativos a las normales de los vértices

vector<Tupla3f> Malla::coloresNormalVertices(){
   vector<Tupla3f> colores;
   Tupla3f tupla;

   for(int i=0; i<getNumVertices(); i++){
      tupla=Tupla3f(fabs(normales_vertices.at(i).coo[0]),fabs(normales_vertices.at(i).coo[1]),fabs(normales_vertices.at(i).coo[2]));
      colores.push_back(tupla);
   }

   return colores;

}

void Malla::generarCoordTextura(int num_rotaciones, int num_vert_perfil, bool tapa_inf, bool tapa_sup){

   vector<float> coord_X,coord_Y, distancias;
   float dist, dist_ultimo;
   pair<float,float> coord;

   for(int i=0;i<=num_rotaciones;i++)
      coord_X.push_back(i/(num_rotaciones*1.0));
  
   distancias.push_back(0);
   for(int i=1;i<num_vert_perfil;i++){
      dist=distancias.at(i-1);
      dist+=distancia(getVertice(i),getVertice(i+1));
      distancias.push_back(dist);
   }

   dist_ultimo=distancias.back();

   for(int i=0;i<num_vert_perfil;i++){
      coord_Y.push_back(1-distancias.at(i)/dist_ultimo);
   }

   coord=make_pair(0.5,1);
   coordenadas_textura.push_back(coord);

   for(int i=0;i<=num_rotaciones;i++){
      for(int j=0;j<num_vert_perfil;j++){
         coord=make_pair(coord_X.at(i),coord_Y.at(j));
         coordenadas_textura.push_back(coord);
      }
   }

   coord=make_pair(0.5,0);
   coordenadas_textura.push_back(coord);

}

Tupla3f Malla::getCentro(){
   Tupla3f centro=Tupla3f(0,0,0);

   for(int i=0;i<getNumVertices();i++){
      centro+=vertices.at(i);
   }

   centro=centro/(1.0*getNumVertices());

   return centro;

}


