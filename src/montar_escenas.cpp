#include "tuplas.hpp"
#include "malla.hpp"
#include "transformacion.hpp"
#include "practica4.hpp"
#include "practica5.hpp"
#include <cmath>

// Mallas

Malla m_helado=Malla("./img/helado.ply",11,true);
Malla m_cono=Malla("./img/cono.ply",11,true);

Malla m_pajaro=Malla("./img/Soren.ply");
Malla m_casa=Malla("./img/Casa.ply");
Malla m_aguja=Malla("./img/aguja.ply");
Malla m_engranaje=Malla("./img/engranaje.ply");
Malla m_vaca=Malla("./img/cow.ply");
Malla m_base=Malla("./img/cilindro.ply",20,true);

Malla m_peon=Malla("./img/peon.ply",20,true);
Malla m_lata_s=Malla("./img/lata-psup.ply",20,false);
Malla m_lata_c=Malla("./img/lata-pcue.ply",20,false);
Malla m_lata_i=Malla("./img/lata-pinf.ply",20,false);

// Materiales

Material mat_galleta;
Material mat_vaca;
Material mat_madera;
Material mat_blanco;
Material mat_negro;
Material mat_metal;
Material mat_cola;
Material mat_plumas;

// Objetos

ElementoSimple o_helado;
ElementoSimple o_cono;

ElementoSimple o_pajaro;
ElementoSimple o_casa;
ElementoSimple o_aguja;
ElementoSimple o_engranaje;
ElementoSimple o_vaca;
ElementoSimple o_base;

ElementoSimple o_madera;
ElementoSimple o_blanco;
ElementoSimple o_negro;
ElementoSimple o_lata_s;
ElementoSimple o_lata_c;
ElementoSimple o_lata_i;

// Matrices Transformación
   //helado
MatrizTranslacion trans_hel=MatrizTranslacion(Tupla3f(6,3,0));
MatrizEscalado esc_hel=MatrizEscalado(Tupla3f(0.3,0.3,0.3));
   //P3
MatrizTranslacion trans_p3=MatrizTranslacion(Tupla3f(-3,0.8,0));
MatrizEscalado esc_p3=MatrizEscalado(Tupla3f(2,2,2));
   //pájaro
MatrizTranslacion trans_paj=MatrizTranslacion(Tupla3f(0,1.15,-0.25));
MatrizEscalado esc_paj=MatrizEscalado(Tupla3f(0.1,0.1,0.1));
MatrizRotacion rot_paj=MatrizRotacion(Tupla3f(1,0,0),14*M_PI/10.0);
   //casa
MatrizEscalado esc_casa=MatrizEscalado(Tupla3f(1.05,0.7,0.4));
MatrizTranslacion trans_casa=MatrizTranslacion(Tupla3f(0.8,-2,-2.25));
MatrizRotacion rot_casa=MatrizRotacion(Tupla3f(0,1,0),M_PI/2.0);
   //agujas
MatrizRotacion rot_aguja=MatrizRotacion(Tupla3f(0,0,1),-M_PI/2.0);
MatrizTranslacion trans_aguja=MatrizTranslacion(Tupla3f(-0.3,0,0.1));
MatrizEscalado esc_aguja=MatrizEscalado(Tupla3f(0.1,0.1,0.1));
MatrizTranslacion trans_minutero=MatrizTranslacion(Tupla3f(0,0,-0.03));
MatrizRotacion rotac_minutero=MatrizRotacion(Tupla3f(0,0,1),M_PI/2.0);
MatrizEscalado esc_horario=MatrizEscalado(Tupla3f(0.7,0.7,1));
   //engranajes
MatrizEscalado esc_engranaje=MatrizEscalado(Tupla3f(0.2,0.2,-0.2));
MatrizEscalado esc_engranaje2=MatrizEscalado(Tupla3f(0.85,0.85,0.85));
MatrizTranslacion trans_engranaje2=MatrizTranslacion(Tupla3f(0.2,0.4,0));
MatrizRotacion rot_engranaje2=MatrizRotacion(Tupla3f(0,0,1),M_PI/7.0);
MatrizEscalado esc_engranaje3=MatrizEscalado(Tupla3f(1.2,1.2,1.2));
MatrizTranslacion trans_engranaje3=MatrizTranslacion(Tupla3f(-0.1,0.55,0));
   //vaca
MatrizRotacion rotac_vaca=MatrizRotacion(Tupla3f(0,1,0),-M_PI/2.0);
MatrizTranslacion trans_vaca=MatrizTranslacion(Tupla3f(0.3,-0.8,0.3));
MatrizEscalado esc_vaca=MatrizEscalado(Tupla3f(0.1,0.1,0.1));
   //base
MatrizTranslacion trans_base=MatrizTranslacion(Tupla3f(0.0,-0.8,0.05));
MatrizEscalado esc_base=MatrizEscalado(Tupla3f(1.5,-0.1,1.5));
   //peon
MatrizTranslacion trans_X_peon=MatrizTranslacion(Tupla3f(3,0,0));
MatrizTranslacion trans_Y_Z_peon=MatrizTranslacion(Tupla3f(0,1.4,5));
   //lata
MatrizEscalado esc_lata=MatrizEscalado(Tupla3f(6,6,6));

// Escenas 
   //P3
EscenaGE sc_p3;
EscenaGE sc_pajaro;
EscenaGE sc_casa;
EscenaGE sc_aguja,sc_minutero,sc_horario;
EscenaGE sc_engranajes,sc_engranaje1,sc_engranaje2,sc_engranaje3;
EscenaGE sc_vaca;
EscenaGE sc_base;
   //P4
EscenaGE sc_p4;
EscenaGE sc_lata;

// Métodos para montar las escenas
void P3_InicializarEscena(Drawer *dibujador){
   mat_madera=Material("./img/text-madera.jpg",true,Tupla3f(1,0,0),Tupla3f(0,1,0),Tupla4f(0.5,0.4,0.5,1.0),Tupla4f(0.5,0.2,0.0,1),Tupla4f(0.5,0.2,0.0,1),50);
   mat_vaca=Material("./img/vaca.jpg",true,Tupla3f(0.1,0,0),Tupla3f(0,0,0.1),Tupla4f(0.5,0.5,0.5,1.0),Tupla4f(0.5,0.5,0.5,1),Tupla4f(0.5,0.5,0.5,1),80);
   mat_negro=Material(Tupla4f(0.01,0.01,0.01,1),Tupla4f(0.1,0.1,0.1,1),Tupla4f(0.9,0.9,0.9,1),10.0);
   mat_metal=Material(Tupla4f(0.2,0.2,0.2,1.0),Tupla4f(0.5,0.5,0.5,1),Tupla4f(0.5,0.5,0.5,1),80);
   mat_plumas=Material("./img/plumas.jpg",true,Tupla3f(1,0,0),Tupla3f(0,0,1),Tupla4f(0.8,0.8,0.8,1),Tupla4f(0.8,0.8,0.8,1),Tupla4f(0.2,0.2,0.2,1),90);

   o_pajaro=ElementoSimple(&m_pajaro,dibujador,&mat_plumas);
   o_casa=ElementoSimple(&m_casa,dibujador,Tupla4f(0.8,0.6,0.15,0.5));
   o_aguja=ElementoSimple(&m_aguja,dibujador,&mat_negro);
   o_engranaje=ElementoSimple(&m_engranaje,dibujador,&mat_metal);
   o_vaca=ElementoSimple(&m_vaca,dibujador,&mat_vaca);
   o_base=ElementoSimple(&m_base,dibujador,&mat_madera);

   sc_pajaro.incluirHijo(&trans_paj);
   sc_pajaro.incluirHijo(&esc_paj);
   sc_pajaro.incluirHijo(&rot_paj);
   sc_pajaro.incluirHijo(&o_pajaro);

   sc_casa.incluirHijo(&esc_casa);
   sc_casa.incluirHijo(&trans_casa);
   sc_casa.incluirHijo(&rot_casa);
   sc_casa.incluirHijo(&o_casa);

   sc_aguja.incluirHijo(&rot_aguja);
   sc_aguja.incluirHijo(&trans_aguja);
   sc_aguja.incluirHijo(&esc_aguja);
   sc_aguja.incluirHijo(&o_aguja);

   sc_minutero.incluirHijo(&trans_minutero);
   sc_minutero.incluirHijo(&rotac_minutero);
   sc_minutero.incluirHijo(&sc_aguja);

   sc_horario.incluirHijo(&esc_horario);
   sc_horario.incluirHijo(&sc_aguja); 

   sc_engranaje1.incluirHijo(&esc_engranaje);
   sc_engranaje1.incluirHijo(&o_engranaje);

   sc_engranaje2.incluirHijo(&esc_engranaje2);
   sc_engranaje2.incluirHijo(&trans_engranaje2);
   sc_engranaje2.incluirHijo(&rot_engranaje2);
   sc_engranaje2.incluirHijo(&sc_engranaje1);

   sc_engranaje3.incluirHijo(&esc_engranaje3);
   sc_engranaje3.incluirHijo(&trans_engranaje3);
   sc_engranaje3.incluirHijo(&sc_engranaje1);

   sc_engranajes.incluirHijo(&sc_engranaje1);
   sc_engranajes.incluirHijo(&sc_engranaje2);
   sc_engranajes.incluirHijo(&sc_engranaje3);

   sc_vaca.incluirHijo(&trans_vaca);
   sc_vaca.incluirHijo(&esc_vaca);
   sc_vaca.incluirHijo(&rotac_vaca);
   sc_vaca.incluirHijo(&o_vaca);

   sc_base.incluirHijo(&trans_base);
   sc_base.incluirHijo(&esc_base);
   sc_base.incluirHijo(&o_base);

}

void P3_MontarEscena( EscenaGE *escena, Drawer *dibujador ){
   escena->incluirHijo(&sc_pajaro);
   escena->incluirHijo(&sc_minutero);
   escena->incluirHijo(&sc_horario);
   escena->incluirHijo(&sc_engranajes);
   escena->incluirHijo(&sc_casa);
   escena->incluirHijo(&sc_vaca);
   escena->incluirHijo(&sc_base);
}


void P4_InicializarEscena(Drawer *dibujador){
   mat_madera=Material("./img/text-madera.jpg",true,Tupla3f(1,0,0),Tupla3f(0,1,0),Tupla4f(0.5,0.4,0.5,1.0),Tupla4f(0.5,0.2,0.0,1),Tupla4f(0.5,0.2,0.0,1),50);
   mat_blanco=Material(Tupla4f(0.1,0.1,0.1,1),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(0.0,0.0,0.0,1),128.0);
   mat_negro=Material(Tupla4f(0.01,0.01,0.01,1),Tupla4f(0.1,0.1,0.1,1),Tupla4f(0.9,0.9,0.9,1),10.0);
   mat_metal=Material(Tupla4f(0.2,0.2,0.2,1.0),Tupla4f(0.5,0.5,0.5,1),Tupla4f(0.5,0.5,0.5,1),80);
   mat_cola=Material("./img/text-lata-1.jpg",false,Tupla3f(1,0,0),Tupla3f(0,1,0),Tupla4f(0.2,0.2,0.2,1.0),Tupla4f(0.5,0.5,0.5,1),Tupla4f(0.5,0.5,0.5,1),80);

   o_madera=ElementoSimple(&m_peon,dibujador,&mat_madera);
   o_blanco=ElementoSimple(&m_peon,dibujador,&mat_blanco);
   o_negro=ElementoSimple(&m_peon,dibujador,&mat_negro);
   o_lata_s=ElementoSimple(&m_lata_s,dibujador,&mat_metal);
   o_lata_c=ElementoSimple(&m_lata_c,dibujador,&mat_cola);
   o_lata_i=ElementoSimple(&m_lata_i,dibujador,&mat_metal);

   sc_lata.incluirHijo(&esc_lata);
   sc_lata.incluirHijo(&o_lata_s);
   sc_lata.incluirHijo(&o_lata_c);
   sc_lata.incluirHijo(&o_lata_i);

}

void P4_MontarEscena( EscenaGE *escena, Drawer *dibujador ){

   escena->incluirHijo(&sc_lata);
   escena->incluirHijo(&trans_Y_Z_peon);
   escena->incluirHijo(&o_madera);
   escena->incluirHijo(&trans_X_peon);
   escena->incluirHijo(&o_blanco);
   escena->incluirHijo(&trans_X_peon);
   escena->incluirHijo(&o_negro);

}


void P5_MontarEscena( EscenaGE *escena, Drawer *dibujador ){
   mat_galleta=Material("./img/galleta.jpg",false,Tupla3f(1,0,0),Tupla3f(0,1,0),Tupla4f(0.5,0.4,0.5,1.0),Tupla4f(0.2,0.2,0.2,1),Tupla4f(0.1,0.1,0.1,1),100);
   o_cono=ElementoSimple(&m_cono,dibujador,&mat_galleta);
   o_helado=ElementoSimple(&m_helado,dibujador,Tupla4f(0.6,0.6,0.2,1));

   sc_p3.incluirHijo(&esc_p3);
   sc_p3.incluirHijo(&trans_p3);

   P3_MontarEscena(&sc_p3,dibujador);

   P4_MontarEscena(&sc_p4,dibujador);

   escena->incluirHijo(&sc_p3);
   escena->incluirHijo(&sc_p4);
   escena->incluirHijo(&trans_hel);
   escena->incluirHijo(&esc_hel);
   escena->incluirHijo(&o_cono);
   escena->incluirHijo(&o_helado);
}


// Reasignar dibujador
void P3_SetDibujador( Drawer *dibujador ){
   o_pajaro.setDibujador(dibujador);
   o_casa.setDibujador(dibujador);
   o_aguja.setDibujador(dibujador);
   o_engranaje.setDibujador(dibujador);
   o_vaca.setDibujador(dibujador);
   o_base.setDibujador(dibujador);
}

void P4_SetDibujador( Drawer *dibujador ){
   o_madera.setDibujador(dibujador);
   o_blanco.setDibujador(dibujador);
   o_negro.setDibujador(dibujador);
   o_lata_s.setDibujador(dibujador);
   o_lata_c.setDibujador(dibujador);
   o_lata_i.setDibujador(dibujador);
}

void P5_SetDibujador( Drawer *dibujador ){
   P3_SetDibujador(dibujador);
   P4_SetDibujador(dibujador);
}
