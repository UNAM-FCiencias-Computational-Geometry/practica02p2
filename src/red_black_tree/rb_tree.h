/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Contiene la estructura que representa un red-black tree para ordenar puntos
 * respecto a la coordenada que se le indique, x o y.
 # En el archivo main.c viene un ejemplo de como crear un rb-tree.
 */

#ifndef RB_TREE_H_
#define RB_TREE_H_

#include "types/types.h"
#include "points/2d_points.h"
#include "double_linked_list/double_linked_list.h"

/** Enumerador que sirve para representar el color de los nodos del arbol. */
typedef enum {RED = 1, BLACK} color;

/**
 *         parent
 *          /
 *       rb_node [color,point]      
 *        /   \         
 *      left right
 */
struct rb_node {
	struct rb_node* left;
	struct rb_node* right;
	struct rb_node* parent;
	
	color color;	

	void* element;
};

typedef struct rb_node rb_node;

/**
   Apuntador hacia el nodo raiz y el nodo sentinela del arbol.
*/
struct rb_tree {
	struct rb_node* root;
	struct rb_node* sentinel;

	int size;
	item_type type;
};

/** Renombramos la estructura anterior para un uso más simple. */
typedef struct rb_tree rb_tree;

/** 
 * Inicializa un rb-tree que ordena puntos a partir de la coordenada que se le
 * pase.
*/
rb_tree* init_rb_tree(item_type type);

/** Destruye el arbol que se le pase, no destruye los puntos.*/
void destroy_rb_tree(rb_tree* tree);

/** Inicializa un nodo. */
rb_node* init_rb_node(rb_tree* tree);

/** Destruye un nodo. */
void destroy_rb_node(rb_tree* tree, rb_node* node);

/** Inseta un punto al rb-tree, puede estar repetido y sigue funcionando. */
void rb_insert(rb_tree* tree, void* element);

/** 
 * Busca el punto que se le pasa.
 */
void* rb_search(rb_tree* tree, void* element);

/** 
 * Borra el punto que se le pasa
 */
void* rb_delete(rb_tree* tree, void* element);

/** 
 * Regresa el punto que tenga coordenada menor/mayor X o Y, dependiendo
 * de cual se le indico al momento de crear el arbol.
 */
void* rb_min(rb_tree* tree);
void* rb_max(rb_tree* tree);

/**
 * Transforma un arbol rojo negro en una lista doblemente ligada.
 */
list* rb_tree_to_list(rb_tree* tree);
#endif
