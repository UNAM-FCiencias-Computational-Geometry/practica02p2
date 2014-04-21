/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "dcel/dcel.h"

#include "double_linked_list/double_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

dcel* init_dcel()
{
	dcel* dcel;
	dcel = (struct dcel*) malloc(sizeof(struct dcel));
	
	if (dcel == NULL) {
		printf("Ya no hay memoria disponible: init_dcel()\n");
		exit(EXIT_FAILURE);
	}

	dcel->face = NULL;
	dcel->vertex = NULL;
	dcel->half_edge = NULL;

	return dcel;
}

void destroy_dcel(dcel* dcel)
{
	destroy_rb_tree(dcel->face);
	destroy_rb_tree(dcel->vertex);
	destroy_rb_tree(dcel->half_edge);

	free(dcel);
}

void dcel_insert_face(dcel* dcel, face* face)
{
	if (face == NULL || dcel == NULL)
		return;

	if (dcel->face == NULL)
		dcel->face = init_rb_tree(FACE);

	if (rb_search(dcel->face,face) != NULL)
		return;
	
	rb_insert(dcel->face, face);
}

void dcel_insert_half_edge(dcel* dcel, half_edge* half_edge)
{
	if (half_edge == NULL || dcel == NULL)
		return;

	if (dcel->half_edge == NULL) {
		dcel->half_edge = init_rb_tree(HALF_EDGE);
	}

	if (rb_search(dcel->half_edge,half_edge) != NULL)
		return;

	rb_insert(dcel->half_edge, half_edge);
}

void dcel_insert_vertex(dcel* dcel, vertex* vertex)
{
	if (dcel == NULL || vertex == NULL)
		return;

	if (dcel->vertex == NULL)
		dcel->vertex = init_rb_tree(POINT);
	
	if (rb_search(dcel->vertex,vertex) != NULL)
		return;

	rb_insert(dcel->vertex,vertex);
}

list* incident_he_to_v(vertex* vertex){
	struct double_linked_list *incident_he;
	struct half_edge *he, *twin_he, *original;
	
	incident_he = init_double_linked_list(HALF_EDGE);
	he = original = vertex->incident_edge;
	twin_he = he->twin;
	push_back(incident_he, he);
	he = twin_he->next;
	twin_he = he->twin;
	
	while(!(half_edge_equals(original, twin_he->twin))){
		
		push_back(incident_he, he);
		he = twin_he->next;
		twin_he = he->twin;
	}
	
	return incident_he;
}

list* incident_f_to_f(face* face) 
{
	struct double_linked_list* l;
	struct list_item* tmp;
	struct rb_tree* rb_tree;
	struct half_edge* he;
	
	l = incident_he_to_f(face);//lista de todas las aristas incidentes a la cara
	tmp = l->head;
	rb_tree = init_rb_tree(FACE);
	
	while(tmp != NULL){
		he = tmp->element;	
		if(rb_search(rb_tree, he->twin->incident_face) == NULL){
			rb_insert(rb_tree, he->twin->incident_face);
			tmp = tmp->right;
		}else{
			tmp = tmp->right;
		}
	}
	
	return rb_tree_to_list(rb_tree);
}

list* incident_he_to_f(face* face)
{	
	struct double_linked_list* l;
	l = he_from_f(face);
	
	if(face->inner_components != NULL){
		struct double_linked_list* l1;
		struct list_item* tmp;
		
		l1 = face->inner_components;
		tmp = l1->head;
	
		while(tmp != NULL){
			struct half_edge* he = tmp->element;
			struct half_edge* he_tmp = he->next;
			
			push_back(l,he);
			while(!(half_edge_equals(he,he_tmp))){
				push_back(l, he_tmp);
				he_tmp = he_tmp->next;
			}
			
			tmp = tmp->right;
		}
	}else{
		return l;
	}
	return l;
}

list* he_from_f(face* face){
	
	struct half_edge *he, *he_tmp;
	struct double_linked_list* l;
		
	he = face->outer_component;//esta línea es la que está chillando
	he_tmp = he->next;
	l = init_double_linked_list(HALF_EDGE);
	push_back(l,he);

	while(!(half_edge_equals(he,he_tmp))){
		push_back(l, he_tmp);
		he_tmp = he_tmp->next;
	}
	
	return l;
}
