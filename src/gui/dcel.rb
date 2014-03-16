# -*- coding: utf-8 -*-
#
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

# Public: Inicializa la ventana y variables de processing
#
require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/dcel"))

def setup
  background 255, 255, 255
  size(600, 400,P3D)

  # Inicializa la DCEL del ejemplo
  dcel = ExampleDCEL.construct_example
  
  # Transforma los arboles rojo negro a un arreglo de puntos y segmentos

  # Los vertices son un arreglo de puntos, donde un punto es un arreglo de dos numeros
  # flotantes.
  # @vertex = [[1.0, 1.0], [1.0, 9.0], [3.0, 3.0], [3.0, 7.0], [4.0, 5.0], [5.0, 4.0], 
  #           [6.0, 7.0], [8.0, 2.0], [10.0, 5.0], [11.0, 2.0], [11.0, 4.0], [13.0, 1.0],
  #           [13.0, 9.0]]
  @vertex = to_a(RBTree.rb_tree_to_list(dcel[:vertex]),"POINT")
  
  # Las aristas son un arreglo de aristas, donde una arista es un arreglo de dos puntos.
  # @half_edge = [[[1.0, 1.0], [1.0, 9.0]], [[1.0, 1.0], [13.0, 1.0]], [[1.0, 9.0], [1.0, 1.0]],
  #              [[1.0, 9.0], [13.0, 9.0]], [[3.0, 3.0], [3.0, 7.0]], [[3.0, 3.0], [4.0, 5.0]], ... ]
  @half_edge = to_a(RBTree.rb_tree_to_list(dcel[:half_edge]),"HALF_EDGE")

  # Variables para transformar los puntos del plano euclidiado a puntos 
  # dentro de la pantalla.
  # NOTA: Ustedes solo deben dibujar los puntos dados, el codigo que sigue ya hace la 
  #       operaciones necesarias para pasar de un plano a otro.
  @zoom = 40
  @translation = -1.0
  
  @vertex = @vertex.map {
              |vertex|
              [vertex[0]*@zoom, vertex[1]*@zoom]
            } 
  @half_edge = @half_edge.map {
                 |half_edge|

                 a = half_edge[0].map{|x| x*@zoom}
                 b = half_edge[1].map{|x| x*@zoom}
                 
                 [a,b]
               }

  push_matrix()
  rotateX(PI);
  translate(0,@height*@translation)
  
  # Despues de transformar los puntos solo resta dibujar los vertices y las aristas.
  draw_vertex_and_half_edges
  pop_matrix()
end

# Public: Dibuja el conjunto de vertices y aristas @vertex y @half_edge
#
# Esta funcion la debes de modificar para que dibuje los puntos y aristas
def draw_vertex_and_half_edges
end

# Public: Una lista de vertices o aristas de C a un arreglo de Ruby.
#         No deberias modificar esta funcion.
def to_a(list,type)
  
  return [] if list.null?

  element = List.pop_front(list)
  array  = []

  while not(element.null?)    
    if (type == "HALF_EDGE")
      half_edge = HalfEdge.cast_half_edge(element)
      first = half_edge[:first]
      last = half_edge[:last]
    
      array << [[first[:x],first[:y]],[last[:x], last[:y]]]
      
    end
    if (type == "POINT")
      point = Points.cast_point(element)
      
      array << [point[:x], point[:y]]
      
    end

    element = List.pop_front(list)
  end
    
  return array
end
