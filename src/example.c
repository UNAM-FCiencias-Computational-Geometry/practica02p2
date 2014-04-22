#include "example.h"

#include "red_black_tree/rb_tree.h"

#include "dcel/dcel.h"

#include "points/2d_points.h"
#include "half_edge/half_edge.h"
#include "face/face.h"

#include <stdlib.h>
#include <stdio.h>

void print_half_edge(half_edge* a)
{
	printf("Half_Edge: %s, first: %s, incident_face: %s, twin: %s, next: %s, prev: %s\n",
		   a->name,a->first->name, ((face*) a->incident_face)->name,
		   a->twin->name, a->next->name,a->prev->name);
}

dcel* construct_example()
{
	/** Declaramos los vertices. */
	vertex *A, *B, *C, *D, *E, *F, *G, *H, *I, *J, *K, *L, *M;
	
	/** 
	 * Inicializamos cada vertice, los nombres que se le pasan sirven, para
	 * identificar de forma más sencilla los vertices.
	 */
	A = init_point(1.0,1.0,"A\0");
	B = init_point(13.0,1.0,"B\0");
	C = init_point(1.0,9.0,"C\0");
	D = init_point(13.0,9.0,"D\0");
	E = init_point(3.0,3.0,"E\0");
	F = init_point(4.0,5.0,"F\0");
	G = init_point(3.0,7.0,"G\0");
	H = init_point(6.0,7.0,"H\0");
	I = init_point(5.0,4.0,"I\0");
	J = init_point(8.0,2.0,"J\0");
	K = init_point(10.0,5.0,"K\0");
	L = init_point(11.0,4.0,"L\0");	
	M = init_point(11.0,2.0,"M\0");

	/** 
	 * Declaramos todas las aristas del ejemplo, dado que C no acepta
	 * declaraciones tipo c', lo sustituimos por c1.
	 */
	half_edge *a, *a1, *b, *b1, *c, *c1, *d, *d1, *e, *e1, *f, *f1, *g, *g1,
		*h, *h1, *i, *i1, *j, *j1, *k, *k1, *l, *l1, *m, *m1, *n, *n1, *p, *p1,
		*q, *q1;

	/** Inicializamos los half_edge. */
	a = init_half_edge(A,B,"a\0");
	a1 = init_half_edge(B,A,"a'\0");

	b = init_half_edge(C,A,"b\0");
	b1 = init_half_edge(A,C,"b'\0");
	
	c = init_half_edge(B,D,"c\0");
	c1 = init_half_edge(D,B,"c'\0");
	
	d = init_half_edge(D,C,"d\0");
	d1 = init_half_edge(C,D,"d'\0");

	e = init_half_edge(G,E,"e\0");
	e1 = init_half_edge(E,G,"e'\0");
	
	f = init_half_edge(E,I,"f\0");
	f1 = init_half_edge(I,E,"f'\0");
	
	g = init_half_edge(I,F,"g\0");
	g1 = init_half_edge(F,I,"g'\0");

	h = init_half_edge(F,E,"h\0");
	h1 = init_half_edge(E,F,"h'\0");
	
	i = init_half_edge(G,F,"i\0");
	i1 = init_half_edge(F,G,"i'\0");

	j = init_half_edge(H,G,"j\0");
	j1 = init_half_edge(G,H,"j'\0");
	
	k = init_half_edge(I,H,"k\0");
	k1 = init_half_edge(H,I,"k'\0");
	
	l = init_half_edge(F,H,"l\0");
	l1 = init_half_edge(H,F,"l'\0");

	m = init_half_edge(K,J,"m\0");
	m1 = init_half_edge(J,K,"m'\0");
	
	n = init_half_edge(L,K,"n\0");
	n1 = init_half_edge(K,L,"n'\0");
	
	p = init_half_edge(M,L,"p\0");
	p1 = init_half_edge(L,M,"p'\0");

	q = init_half_edge(J,M,"q\0");
	q1 = init_half_edge(M,J,"q'\0");

	/** Inidicamos los gemelos de cada half_edge. */
	a->twin = a1;
	a1->twin = a;

	b->twin = b1;
	b1->twin = b;

	c->twin = c1;
	c1->twin = c;

	d->twin = d1;
	d1->twin = d;
	
	e->twin = e1;
	e1->twin = e;

	f->twin = f1;
	f1->twin = f;

	g->twin = g1;
	g1->twin = g;

	h->twin = h1;
	h1->twin = h;
	
	i->twin = i1;
	i1->twin = i;

	j->twin = j1;
	j1->twin = j;

	k->twin = k1;
	k1->twin = k;

	l->twin = l1;
	l1->twin = l;

	m->twin = m1;
	m1->twin = m;
	
	n->twin = n1;
	n1->twin = n;

	p->twin = p1;
	p1->twin = p;

	q->twin = q1;
	q1->twin = q;

	/** Inializamos los apuntadores next y prev de cada half_edge. */
	a->next = c;
	a->prev = b;

	a1->next = b1;
	a1->prev = c1;

	b->next = a;
	b->prev = d;
	
	b1->next = d1;
	b1->prev = a1;

	c->next = d;
	c->prev = a;
	
	c1->next = a1;
	c1->prev = d1;

	d->next = b;
	d->prev = c;

	d1->next = c1;
	d1->prev = b1;

	e->next = f;
	e->prev = j;

	e1->next = i;
	e1->prev = h;

	f->next = k;
	f->prev = e;
	
	f1->next = h1;
	f1->prev = g1;

	g->next = l;
	g->prev = k1;
	
	g1->next = f1;
	g1->prev = h1;

	h->next = e1;
	h->prev = i;

	h1->next = g1;
	h1->prev = f1;

	i->next = h;
	i->prev = e1;

	i1->next = j1;
	i1->prev = l1;

	j->next = e;
	j->prev = k;

	j1->next = l1;
	j1->prev = i1;

	k->next = j;
	k->prev = f;
	
	k1->next = g;
	k1->prev = l;

	l->next = k1;
	l->prev = g;

	l1->next = i1;
	l1->prev = j1;

	m->next = q;
	m->prev = n;

	m1->next = n1;
	m1->prev = q1;

	n->next = m;
	n->prev = p;

	n1->next = p1;
	n1->prev = m1;

	p->next = n;
	p->prev = q;

	p1->next = q1;
	p1->prev = n1;

	q->next = p;
	q->prev = m;

	q1->next = m1;
	q1->prev = p1;
		
	
	/** Inicializamos la lista de componentes internos.*/
	list *f1_inner, *f2_inner;
	f1_inner = init_double_linked_list(HALF_EDGE);
	f2_inner = init_double_linked_list(HALF_EDGE);

	push_back(f1_inner,c);
	
	push_back(f2_inner,k);
	push_back(f2_inner,m);

	/**  Inicializamos las caras. */
	face* face1, *face2, *face3, *face4, *face5, *face6, *face7;
	
	face1 = init_face("face 1\0", a, f1_inner);

	face2 = init_face("face 2\0", c1, f2_inner);
	
	face3 = init_face("face 3\0", m1, NULL);
	
	face4 = init_face("face 4\0", j1, NULL);

	face5 = init_face("face 5\0", k1, NULL);

	face6 = init_face("face 6\0", e1, NULL);
		
	face7 = init_face("face 7\0", f1, NULL);

	/** Le indicamos a las caras cual es su cara incidente */

	a->incident_face = face1;
	a1->incident_face = face2;
	
	b->incident_face = face1;
	b1->incident_face = face2;
	
	c->incident_face = face1;
	c1->incident_face = face2;
	
	d->incident_face = face1;
	d1->incident_face = face2;
	
	e->incident_face = face2;
	e1->incident_face = face6;
		
	f->incident_face = face2;
	f1->incident_face = face7;
	
	g->incident_face = face5;
	g1->incident_face = face7;
	
	h->incident_face = face6;
	h1->incident_face = face7;
	
	i->incident_face = face6;
	i1->incident_face = face4;
	
	j->incident_face = face2;
	j1->incident_face = face4;
		
	k->incident_face = face2;
	k1->incident_face = face5;
	
	l->incident_face = face5;
	l1->incident_face = face4;
	
	m->incident_face = face2;
	m1->incident_face = face3;
	
	n->incident_face = face2;
	n1->incident_face = face3;
	
	p->incident_face = face2;
	p1->incident_face = face3;

	q->incident_face = face2;
	q1->incident_face = face3;

	/**
	 * Ahora que las estructuras internas de la DCEL estan completas, inicializo
	 * la dcel y le agrego sus estructuras.
	 */
	
	dcel* dcel = init_dcel();

	/** Insertamos los vertices.*/
	dcel_insert_vertex(dcel,A);
	dcel_insert_vertex(dcel,B);
	dcel_insert_vertex(dcel,C);
	dcel_insert_vertex(dcel,D);
	dcel_insert_vertex(dcel,E);
	dcel_insert_vertex(dcel,F);
	dcel_insert_vertex(dcel,G);
	dcel_insert_vertex(dcel,H);
	dcel_insert_vertex(dcel,I);
	dcel_insert_vertex(dcel,J);
	dcel_insert_vertex(dcel,K);
	dcel_insert_vertex(dcel,L);
	dcel_insert_vertex(dcel,M);

	/** Insertamos los half_edges. */
	dcel_insert_half_edge(dcel,a);
	dcel_insert_half_edge(dcel,a1);

	dcel_insert_half_edge(dcel,b);
	dcel_insert_half_edge(dcel,b1);

	dcel_insert_half_edge(dcel,c);
	dcel_insert_half_edge(dcel,c1);

	dcel_insert_half_edge(dcel,d);
	dcel_insert_half_edge(dcel,d1);

	dcel_insert_half_edge(dcel,e);
	dcel_insert_half_edge(dcel,e1);

	dcel_insert_half_edge(dcel,f);
	dcel_insert_half_edge(dcel,f1);

	dcel_insert_half_edge(dcel,g);
	dcel_insert_half_edge(dcel,g1);

	dcel_insert_half_edge(dcel,h);
	dcel_insert_half_edge(dcel,h1);

	dcel_insert_half_edge(dcel,i);
	dcel_insert_half_edge(dcel,i1);

	dcel_insert_half_edge(dcel,j);
	dcel_insert_half_edge(dcel,j1);

	dcel_insert_half_edge(dcel,k);
	dcel_insert_half_edge(dcel,k1);

	dcel_insert_half_edge(dcel,l);
	dcel_insert_half_edge(dcel,l1);

	dcel_insert_half_edge(dcel,m);
	dcel_insert_half_edge(dcel,m1);

	dcel_insert_half_edge(dcel,n);
	dcel_insert_half_edge(dcel,n1);

	dcel_insert_half_edge(dcel,p);
	dcel_insert_half_edge(dcel,p1);

	dcel_insert_half_edge(dcel,q);
	dcel_insert_half_edge(dcel,q1);

	/** Insertamos las caras. */
	dcel_insert_face(dcel,face1);
	dcel_insert_face(dcel,face2);
	dcel_insert_face(dcel,face3);
	dcel_insert_face(dcel,face4);
	dcel_insert_face(dcel,face5);
	dcel_insert_face(dcel,face6);
	dcel_insert_face(dcel,face7);
	
	return dcel;
}

