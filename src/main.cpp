// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** Carlos Ureña Almagro
// **
// ** Función 'main', inicialización y gestores de eventos
// **
// *********************************************************************

// includes de C/C++

#include <cctype>   // toupper
#include <string>   // std::string
#include <iostream> // std::cout
#include <fstream>  // ifstream
#include <cmath>    // fabs

// includes de OpenGL/glut

#include <GL/glut.h>  // freeglut standard (incluye cabecera opengl)
#include <GL/freeglut_ext.h> // extensiones freeglut (glutSolidCylinder)

// includes de archivos en el directorio de trabajo (de las prácticas)

#include "error-ogl.hpp"
#include "practica1.hpp"
#include "practica2.hpp"
#include "practica3.hpp"
#include "practica4.hpp"
#include "practica5.hpp"

using namespace std;

// *********************************************************************
// **
// ** Variables globales
// ** (se inicializan en las funciones de inicialización)
// **
// *********************************************************************

// variables que definen la posicion de la camara en coordenadas polares

float 
   camara_angulo_x ,   // angulo de rotación entorno al eje X
   camara_angulo_y ;   // angulo de rotación entorno al eje Y

// ---------------------------------------------------------------------
// variables que definen el view-frustum (zona visible del mundo)

float 
   frustum_factor_escala ,  // factor de escala homogeneo que se aplica al frustum (sirve para alejar o acercar)
   frustum_ancho ,          // ancho, en coordenadas del mundo
   frustum_dis_del ,        // distancia al plano de recorte delantero (near)
   frustum_dis_tra ;        // distancia al plano de recorte trasero (far)

// ---------------------------------------------------------------------
// variables que determinan la posicion y tamaño inicial de la ventana 
// (el tamaño se actualiza al cambiar el tamaño durante la ejecución)

int 
   ventana_pos_x  = 50  ,
   ventana_pos_y  = 50  ,
   ventana_tam_x  = 1024,  // ancho inicial y actual de la ventana, en pixels
   ventana_tam_y  = 800 ;  // alto inicial actual de la ventana, en pixels

// ---------------------------------------------------------------------
// variable para determinar la práctica activa
int practica_activa;
bool valido_P2=false;


// *********************************************************************
// **
// ** Funciones auxiliares:
// **
// *********************************************************************


// fija la transformación de proyeccion (zona visible del mundo == frustum)

void FijarProyeccion()
{
   const GLfloat ratioYX = GLfloat( ventana_tam_y )/GLfloat( ventana_tam_x );
   
   CError();
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // (3) proyectar en el plano de visión
   glFrustum
   (  -frustum_ancho,
      +frustum_ancho,
      -frustum_ancho*ratioYX,
      +frustum_ancho*ratioYX,
      +frustum_dis_del,
      +frustum_dis_tra
   );
   

   // (2) situar el origen (0,0,0), en mitad del view frustum 
   //     (en la rama negativa del eje Z)
   glTranslatef( 0.0,0.0,-0.5*(frustum_dis_del+frustum_dis_tra));
   
    // (1) aplicar factor de escala
   glScalef( frustum_factor_escala, frustum_factor_escala,  frustum_factor_escala );
   
   CError();
}


// ---------------------------------------------------------------------
// fijar viewport y proyección (viewport ocupa toda la ventana)

void FijarViewportProyeccion()
{
   glViewport( 0, 0, ventana_tam_x, ventana_tam_y );

   if(practica_activa==5)
      P5_FijarProyeccion();
   else
      FijarProyeccion() ;
}

// ---------------------------------------------------------------------
// fija la transformación de vista (posiciona la camara)

void FijarCamara()
{
   
   CError();
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
   if(practica_activa==5){
      P5_FijarCamara();
   }
   else{
      glRotatef(camara_angulo_x,1,0,0);
      glRotatef(camara_angulo_y,0,1,0);
   }  

   CError();
}

// ---------------------------------------------------------------------
// dibuja los ejes utilizando la primitiva grafica de lineas

void DibujarEjes()
{
   const float long_ejes = 10.0 ;
   
   // establecer modo de dibujo a lineas (podría estar en puntos)
   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
   
   // dibujar tres segmentos
   glBegin(GL_LINES);
      // eje X, color rojo
      glColor3f( 1.0, 0.0, 0.0 );
      glVertex3f( -long_ejes, 0.0, 0.0 );
      glVertex3f( +long_ejes, 0.0, 0.0 );
      // eje Y, color verde
      glColor3f( 0.0, 1.0, 0.0 );
      glVertex3f( 0.0, -long_ejes, 0.0 );
      glVertex3f( 0.0, +long_ejes, 0.0 );
      // eje Z, color azul
      glColor3f( 0.0, 0.0, 1.0 );
      glVertex3f( 0.0, 0.0, -long_ejes );
      glVertex3f( 0.0, 0.0, +long_ejes );
   glEnd();
   
}

// ---------------------------------------------------------------------
// asigna el color de fondo actual a todos los pixels de la ventana

void LimpiarVentana()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

// ---------------------------------------------------------------------
// dibuja los objetos de la escena

void DibujarObjetos()
{
   switch(practica_activa){
      case 1:
         P1_DibujarObjetos() ;  // definido en 'practica1.hpp'
         break;
      case 2:
         P2_DibujarObjetos() ;  // definido en 'practica2.hpp'
         break;
      case 3:
         P3_DibujarObjetos() ;  // definido en 'practica3.hpp'
         break;
      case 4:
         P4_DibujarObjetos() ;  // definido en 'practica4.hpp'
         break;   
      case 5:
         P5_DibujarObjetos() ;  // definido en 'practica4.hpp'
         break;
   }
}


// *********************************************************************
// **
// ** Funciones gestoras de eventos
// **
// *********************************************************************


// ---------------------------------------------------------------------
// cambiar la práctica activa

void cambiarPracticaActiva(int nueva_practica){

   if(nueva_practica == 2 and !valido_P2)
      cout << "La práctica 2 no está disponible." << endl;
   else{
      if(nueva_practica==4)
         glEnable(GL_LIGHTING);
      else
         glDisable(GL_LIGHTING);
   
      practica_activa=nueva_practica;
   }

}

void cambiarPracticaActiva(){

   if(practica_activa == 1 and !valido_P2)
      practica_activa=3;
   else
      practica_activa=practica_activa%5+1;

}

// F.G. del evento de redibujado (se produce cuando hay que volver a 
// dibujar la ventana, tipicamente tras producirse otros eventos)

void FGE_Redibujado()
{
   using namespace std ;
   //cout << "redibujado......" << endl << flush ;
   FijarViewportProyeccion() ; // necesario pues la escala puede cambiar
   FijarCamara();
   LimpiarVentana();
   DibujarEjes() ;
   DibujarObjetos();
   glutSwapBuffers();
}

// ---------------------------------------------------------------------
// F.G. del evento de cambio de tamaño de la ventana

void FGE_CambioTamano( int nuevoAncho, int nuevoAlto )
{
   if(practica_activa==5){
      P5_FGE_CambioTamano(nuevoAncho,nuevoAlto);
   }
   else{
      // guardar nuevo tamaño de la ventana
      ventana_tam_x  = nuevoAncho;
      ventana_tam_y  = nuevoAlto ;
   }
   
   // reestablecer frustum, viewport y proyección
   FijarViewportProyeccion();
   
   // forzar un nuevo evento de redibujado, para actualizar ventana
   glutPostRedisplay();
}

// ---------------------------------------------------------------------
// F.G. del evento de pulsación de la tecla normal
//
// parámetros:
//       tecla: carácter corresondiente a la tecla (minúscula)
//       x_raton, y_raton : posición del ratón al pulsar

void FGE_PulsarTeclaNormal( unsigned char tecla, int x_raton, int y_raton )
{

   bool redisp = true,capturada;

   switch(practica_activa){
      case 1:
         capturada=P1_FGE_PulsarTeclaNormal(tecla);
      case 2:
         capturada=P2_FGE_PulsarTeclaNormal(tecla);
         break;
      case 3:
         capturada=P3_FGE_PulsarTeclaNormal(tecla) ;
         break;
      case 4:
         capturada=P4_FGE_PulsarTeclaNormal(tecla) ;
         break;
      case 5:
         capturada=P5_FGE_PulsarTeclaNormal(tecla,x_raton, y_raton) ;
         break;
      default:
         capturada=false;
   }

   if(capturada==false){

      switch (toupper(tecla)){
         case ' ' :
            cambiarPracticaActiva();
            break; 
         case 'Q' :
            exit( 0 );
            break ;
         case '+' :
            frustum_factor_escala *= 1.05;
            break;
         case '-' :
            frustum_factor_escala /= 1.05;
            break;
         default:
            redisp = false ;
      }
   }

   if (redisp)
      glutPostRedisplay();
}

// ---------------------------------------------------------------------
// F.G. del evento de pulsación de la tecla especial
//
// parámetros:
//       tecla: código GLUT de la tecla pulsada
//       x_raton, y_raton : posición del ratón al pulsar


void FGE_PulsarTeclaEspecial( int tecla, int x_raton, int y_raton )
{
   bool redisp = true,capturada;
   const float da = 5.0 ; // incremento en grados de ángulos de camara

   switch(practica_activa){
      case 5:
         capturada=P5_FGE_PulsarTeclaEspecial(tecla,x_raton, y_raton) ;
         break;
      default:
         capturada=false;
   }

   if(capturada==false){
      switch ( tecla ){
         case GLUT_KEY_LEFT:
            camara_angulo_y = camara_angulo_y - da ;
            break;
         case GLUT_KEY_RIGHT:
            camara_angulo_y = camara_angulo_y + da ;
            break;
         case GLUT_KEY_UP:
            camara_angulo_x = camara_angulo_x - da ;
            break;
         case GLUT_KEY_DOWN:
            camara_angulo_x = camara_angulo_x + da ;
            break;
         case GLUT_KEY_PAGE_UP:
            frustum_factor_escala *= 1.05;
            break;
         case GLUT_KEY_PAGE_DOWN:
            frustum_factor_escala /= 1.05;
            break;
      }
   }

   //cout << "tecla normal....." << frustum_factor_escala << endl ;
   
   // si se ha cambiado algo, forzar evento de redibujado
   if (redisp)
      glutPostRedisplay();
}

// ---------------------------------------------------------------------
// F.G. del evento de pulsación del ratón
//


void FGE_Pulsar_Raton( int tecla, int estado, int x_raton, int y_raton )
{
   bool redisp;
   
   switch(practica_activa){
      case 5:
         redisp=P5_FGE_Pulsar_Raton(tecla,estado,x_raton, y_raton) ;
         break;
      default:
         redisp=false;
   }

   // si se ha cambiado algo, forzar evento de redibujado
   if (redisp)
      glutPostRedisplay();
}

// ---------------------------------------------------------------------
// F.G. del evento de movimiento del ratón
//


void FGE_Mover_Raton( int x_raton, int y_raton )
{
   bool redisp = true;
   
   switch(practica_activa){
      case 5:
         redisp=P5_FGE_Mover_Raton(x_raton, y_raton) ;
         break;
      default:
         redisp=false;
   }

   // si se ha cambiado algo, forzar evento de redibujado
   if (redisp)
      glutPostRedisplay();
}

// *********************************************************************
// **
// ** Funciones de inicialización
// **
// *********************************************************************

// inicialización de GLUT: creación de la ventana, designar FGEs

void Inicializa_GLUT( int argc, char * argv[] )
{
   
   // inicializa variables globales usadas en esta función (y otras)
   ventana_pos_x  = 50 ;
   ventana_pos_y  = 50  ;
   ventana_tam_x  = 1024 ;  // ancho inicial y actual de la ventana, en pixels
   ventana_tam_y  = 800 ;  // alto inicial actual de la ventana, en pixels
   
   // inicializa glut:
   glutInit( &argc, argv );
   
   // establece posicion inicial de la ventana:
   glutInitWindowPosition( ventana_pos_x, ventana_pos_y );
   
   // establece tamaño inicial de la ventana:
   glutInitWindowSize( ventana_tam_x, ventana_tam_y );
   
   // establece atributos o tipo de ventana:
   glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
   
   // crea y visualiza una ventana:
   glutCreateWindow("Practicas IG (14-15)");
   
   // establece función gestora del evento de redibujado:
   glutDisplayFunc( FGE_Redibujado );
   
   // establece función gestora del evento de cambio de tamaño:
   glutReshapeFunc( FGE_CambioTamano );
   
   // establece función gestora del evento de pulsación de tecla normal:
   glutKeyboardFunc( FGE_PulsarTeclaNormal );
    
   // establece función gestora del evento de pulsación de tecla especial:
   glutSpecialFunc( FGE_PulsarTeclaEspecial );

   // establece función gestora del evento de pulsación de ratón:
   glutMouseFunc( FGE_Pulsar_Raton );

   // establece función gestora :
   glutMotionFunc( FGE_Mover_Raton );

   // establece función gestora del evento ocioso:
   glutIdleFunc( P3_IDLE );

   // permite usar la componente alpha de glColor
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

// ---------------------------------------------------------------------
// inicialización de OpenGL

void Inicializa_OpenGL( )
{
   // borrar posibles errores anteriores
   CError();
   
   // habilitar test de comparación de profundidades para 3D (y 2D)
   // es necesario, no está habilitado por defecto:
   // https://www.opengl.org/wiki/Depth_Buffer
   glEnable( GL_DEPTH_TEST );
   
   // establecer color de fondo: (1,1,1) (blanco)
   glClearColor( 1.0, 1.0, 1.0, 1.0 ) ;
   
   // establecer color inicial para todas las primitivas
   glColor4f( 0.7, 0.2, 0.4, 1.0 ) ;
   
   // establecer ancho de línea
   glLineWidth( 1.5 );
   
   // establecer tamaño de los puntos
   glPointSize( 3.0 );
   
   // establecer modo de visualización de prim.
   // (las tres posibilidades son: GL_POINT, GL_LINE, GL_FILL)
   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
   
   // inicializar parámetros del frustum
   frustum_dis_del         = 0.1 ;
   frustum_dis_tra         = 10.0;
   frustum_ancho           = 0.5*frustum_dis_del ;
   //frustum_ancho           = 1.0 ;
   frustum_factor_escala   = 1.0 ;
   
   // inicializar parámetros de la cámara
   camara_angulo_x = 0.0 ;
   camara_angulo_y = 0.0 ;

   // ??
   FijarViewportProyeccion() ;
   FijarCamara() ;
   
   
   // ya está
   CError();
}

// ---------------------------------------------------------------------
// Código de inicialización (llama a los dos anteriores, entre otros)

void Inicializar( int argc, char *argv[] )
{
   // glut (crea la ventana)
   Inicializa_GLUT( argc, argv ) ;
   
   // opengl: define proyección y atributos iniciales
   Inicializa_OpenGL() ;
   
   valido_P2=(argc>3);
   practica_activa=5;
   
   // inicializar práctica 1: carga el ply
     
   P1_Inicializar( argc, argv ) ;

   // inicializar práctica 2: carga el perfil
     
   P2_Inicializar( argc, argv ) ;

   // inicializar práctica 3: carga el modelo
     
   P3_Inicializar( argc, argv ) ;

   // inicializar práctica 4: carga el modelo
     
   P4_Inicializar( argc, argv ) ;

   // inicializar práctica 5: carga las camaras
     
   P5_Inicializar( argc, argv ) ;
}

// *********************************************************************
// **
// ** Función principal
// **
// *********************************************************************


int main( int argc, char *argv[] )
{
   // incializar el programa
   Inicializar( argc, argv ) ;
   
   
   // llamar al bucle de gestión de eventos de glut, tiene el 
   // control hasta el final de la aplicación
   glutMainLoop();
   
   // ya está
   return 0;
}
