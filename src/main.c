/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */
#include "example.h"

#include "dcel/dcel.h"
#include "double_linked_list/double_linked_list.h"

#include <stdlib.h>
#include <stdio.h>

/** Funcion que sirve para imprimir los elementos de una lista. */
void print_list(list* list)
{
	
	if (list == NULL)
		return;
	
	item* tmp;

	for (tmp = list->head; tmp != NULL ; tmp = tmp->right) {
		if (list->type == HALF_EDGE)		
			printf("half_edge: %s\n", ((half_edge*)tmp->element)->name);
		
		if (list->type == FACE)		
			printf("face: %s\n", ((face*)tmp->element)->name);
		
		if (list->type == POINT)		
			printf("point: %s\n", ((vertex*)tmp->element)->name);
		
	}
}

int main(void)
{	
	/** Construye la DCEL. */
	dcel* dcel;
	dcel = construct_example();
	
	/**
	 * Vertice espejo que sirve para obtener el vertice con las mismas 
	 * coordenadas que tiene la DCEL.
	 */
	vertex* G = init_point(3.0,7.0,"");
	
	vertex* original_G = rb_search(dcel->vertex,G);
	destroy_point(G);
	
	printf("Point: %s\n",original_G->name);

	/** Prueba de la funcion incident_he_to_v() que deben implementar. */
	list* incident_he;
	incident_he = incident_he_to_v(original_G);

	print_list(incident_he);
	destroy_double_linked_list(incident_he);
	
	/**
	 * Cara espejo que sirve para obtener la cara original de la DCEL. 
	 */
    face* face1 = init_face("face 1\0",NULL,NULL);
	face* original_face1 = rb_search(dcel->face,face1);

	printf("%s\n",original_face1->name);

	/** Prueba de la funcion incident_f_to_f() que deben implementar. */
	list* incident_faces;
	incident_faces = incident_f_to_f(original_face1);
	
	print_list(incident_faces);
	destroy_double_linked_list(incident_faces);
	
	/**
	 * Cara espejo que sirve para obtener la cara original de la DCEL. 
	 */
	face* face2 = init_face("face 2\0", NULL, NULL);
	face* original_face2 = rb_search(dcel->face,face2);

	printf("%s\n", original_face2->name);

	/** Prueba de la funcion incident_he_to_f() que deben implementar. */
	list* incident_half_edge_to_faces;
	incident_half_edge_to_faces = incident_he_to_f(original_face2);

	print_list(incident_half_edge_to_faces);
	destroy_double_linked_list(incident_half_edge_to_faces);
	
	return EXIT_SUCCESS;
}
