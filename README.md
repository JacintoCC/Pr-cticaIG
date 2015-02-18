# PracticaIG
Práctica de Informática Gráfica desarrollada a lo largo del curso

  Descripción de las teclas usadas.
  
        Espacio -> Intercambia entre prácticas
  
  Práctica 1

         C -> Cambia el objeto a dibujar al Cubo
         P -> Cambia el objeto a dibujar al proveniente del archivo PLY
  
  Prácticas 1 y 2

         0 -> Cambia el modo de visualización a Modo Puntos
         1 -> Cambia el modo de visualización a Modo Alambre
         2 -> Cambia el modo de visualización a Modo Sólido
         3 -> Cambia el modo de visualización a Modo Ajedrez
         4 -> Cambia el modo de visualización a Modo Normales.
            Si el modo activo es Modo Normales, cambia las normales mostradas según 8 maneras distintas según las pulsaciones de '4'.
            Este incremento se hace módulo 8:
                     0: Color cara según normal cara.
                     1: Color cara según normal cara, normales de vértices dibujadas mediante segmentos.
                     2: Color cara según normal cara, normales de caras dibujadas mediante segmentos.
                     3: Color cara según normal cara, normales de vértices y caras dibujadas mediante segmentos.
                     4: Color cara interpolando según las normales de los vértices adyacentes.
                     5: Color cara interpolando según las normales de los vértices adyacentes, normales de vértices dibujadas mediante segmentos.
                     6: Color cara interpolando según las normales de los vértices adyacentes, normales de caras dibujadas mediante segmentos.
                     7: Color cara interpolando según las normales de los vértices adyacentes, normales de vértices y caras dibujadas mediante segmentos.

  Práctica 3
  
         1 -> Cambia el modo de visualización a Modo Sólido
         2 -> Cambia el modo de visualización a Modo Sombreado Plano
         3 -> Cambia el modo de visualización a Modo Sombreado Suave
         z/Z -> Gira en sentido horario/antihorario (resp) el horario.
         x/X -> Gira en sentido horario/antihorario (resp) el minutero y los engranajes.
         c/C -> Mueve hacia adelante o hacia atrás el pájaro sin necesidad de llegar a la hora en punto.
         v/V -> Mueve hacia adelante o hacia atrás la vaca.

         b/B -> Aumenta/Disminuye (resp) la velocidad del reloj.
         n/N -> Aumenta/Disminuye (resp) la velocidad del pájaro.
         m/M -> Aumenta/Disminuye (resp) la velocidad de la vaca.

         p y P -> Pausan el movimiento. Al volver a pulsar p o P se reanudan con las velocidades que llevaban antes de la pausa. Facilitan comprobar el movimiento de las teclas z,x,c,v.

  Práctica 4

         1 -> Cambia el modo de visualización a Modo Sombreado Plano
         2 -> Cambia el modo de visualización a Modo Sombreado Suave

         a/A -> Aumenta alpha en PI/10
         z/Z -> Disminuye alpha en PI/10
         x/X -> Aumenta beta en PI/10
         c/C -> Disminuye beta en PI/10

         i -> Aumenta en 0.1 la coordenada X de la luz posicional
         I -> Disminuye en 0.1 la coordenada X de la luz posicional
         j -> Aumenta en 0.1 la coordenada Y de la luz posicional
         J -> Disminuye en 0.1 la coordenada Y de la luz posicional
         k -> Aumenta en 0.1 la coordenada Z de la luz posicional
         K -> Disminuye en 0.1 la coordenada Z de la luz posicional 
         
  Práctica 5
  
      a/A -> Mueve la cámara a la izquierda
      d/D -> Mueve la cámara a la derecha
      w/W -> Mueve la cámara hacia adelante
      s/S -> Mueve la cámara hacia atrás
      e/E -> Mueve la cámara hacia arriba
      x/X -> Mueve la cámara hacia abajo
      r/R -> Reiniciar cámara

      F1 -> Cámara alzado
      F2 -> Cámara planta
      F3 -> Cámara perfil

      Botón izquierdo ratón -> Seleccionar objeto y pasar a modo examinar.
         (La selección no me funciona bien pese a que el código de selección es el dado. Siempre selecciona la base de la lata o nada si
            se pulsa en un punto con coordenada y negativa)
      Botón derecho ratón y arrastrar-> Girar la cámara.

Parámetros en línea de comandos
      
      ./prac archivo_p1.ply perfil_p2.ply NumeroRotaciones

      Al hacer make se carga por defecto el archivo ant.ply y el perfil helado.ply con 11 rotaciones del perfil.
      La práctica visible será la 5 por defecto y modo sombreado suave.
