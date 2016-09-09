// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Triangulation_default_data_structure_2.h
// package       : Triangulation (2.10)
// source        : $RCSfile: Triangulation_default_data_structure_2.h,v $
// revision      : $Revision: 1.10.1.12 $
// revision_date : $Date: 1999/01/11 08:59:42 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TRIANGULATION_DEFAULT_DATA_STRUCTURE_2_H
#define CGAL_TRIANGULATION_DEFAULT_DATA_STRUCTURE_2_H

#include <pair.h>
#include <list.h>
#include <map.h>
#include <vector.h>

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_ds_face_2.h>
#include <CGAL/Triangulation_ds_vertex_2.h>
#include <CGAL/Triangulation_ds_iterators_2.h>
#include <CGAL/Triangulation_ds_circulators_2.h>




template < class Gt , class Vb, class Fb>
class CGAL_Triangulation_default_data_structure_2
  :public CGAL_Triangulation_cw_ccw_2
{
friend istream& operator>> CGAL_NULL_TMPL_ARGS
     (istream& is, CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>& tds);

public:
  typedef Gt Geom_traits;
  //typedef typename Geom_traits::Point Point;
  //typedef typename Geom_traits::Segment Segment;
  //typedef typename Geom_traits::Triangle Triangle;

  typedef CGAL_Triangulation_ds_vertex_2<Vb,Fb> Vertex;
  typedef CGAL_Triangulation_ds_face_2<Vb,Fb> Face;
  typedef pair<Face*, int>  Edge;

  typedef CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb> Tds;
  typedef CGAL_Triangulation_ds_face_iterator_2<Tds> Face_iterator;
  typedef CGAL_Triangulation_ds_vertex_iterator_2<Tds> Vertex_iterator;
  typedef CGAL_Triangulation_ds_edge_iterator_2<Tds> Edge_iterator;

  typedef CGAL_Triangulation_ds_face_circulator_2<Vertex,Face> 
							Face_circulator;
  typedef CGAL_Triangulation_ds_vertex_circulator_2<Vertex,Face> 
							Vertex_circulator;
  typedef CGAL_Triangulation_ds_edge_circulator_2<Vertex,Face> 
							Edge_circulator;


  //creators
  CGAL_Triangulation_default_data_structure_2() 
    : _finite_vertex(NULL), _number_of_vertices(0)
  {
    _infinite_vertex = new Vertex();
  }

   CGAL_Triangulation_default_data_structure_2(const Geom_traits& gt) 
    : _finite_vertex(NULL), _number_of_vertices(0), _geom_traits(gt)
  {
    _infinite_vertex = new Vertex();
  }

  CGAL_Triangulation_default_data_structure_2(Vertex * v)
    : _infinite_vertex(NULL),_finite_vertex(NULL), _number_of_vertices(0)
  {
    init(v);
    CGAL_triangulation_postcondition( is_valid() );
  }

  CGAL_Triangulation_default_data_structure_2(Vertex * v, 
					      const Geom_traits& gt)
    : _infinite_vertex(NULL), _finite_vertex(NULL),
      _number_of_vertices(0), _geom_traits(gt)
  {
    init(v);
    CGAL_triangulation_postcondition( is_valid() );
  }

  CGAL_Triangulation_default_data_structure_2(const Tds &tds)
  {
    copy_tds(tds);
  }

   ~CGAL_Triangulation_default_data_structure_2()
  {
    clear();
    delete _infinite_vertex;
  }
  
  //assignement
 Tds& operator= (const Tds &tds)
  {
    copy_tds(tds);
    return *this;
  }  
    

public:
  //ACCESS FUNCTIONS
  int  dimension() const {
    if(number_of_vertices() == 0 || number_of_vertices() == 1){
      return 0;
    }
    Face* f = infinite_vertex()->face();
    int i = f->index(infinite_vertex());
    return (f->neighbor(i)->has_vertex(infinite_vertex())) ? 1 : 2;
  }

  int number_of_vertices() const {return _number_of_vertices;}
  int number_of_faces() const {
    return (number_of_vertices() <= 1) ? 0 : 2 * number_of_vertices() - 2;
  }
  const Geom_traits& geom_traits() const {return _geom_traits;}

  Vertex* finite_vertex() const  
  {
    //CGAL_triangulation_precondition( number_of_vertices() > 0);
    //this precondition plants the swap function 
    return _finite_vertex;  
  }

  Vertex* infinite_vertex() const  {return _infinite_vertex;  }

  Face* infinite_face() const
  {
    CGAL_triangulation_precondition( number_of_vertices() >= 2  &&
				     _infinite_vertex->face() != NULL );
    return _infinite_vertex->face();
  }



  // TEST IF INFINITE FEATURES
  bool is_infinite(const Face* f) const {
    return f->has_vertex(infinite_vertex());
  }

  bool is_infinite(const Vertex* v) const {
    return v == infinite_vertex();
  }

  bool is_infinite(const Face* f, int i) const {
    return is_infinite(f->vertex(ccw(i))) ||
	is_infinite(f->vertex(cw(i)));
  }

  bool is_infinite(Edge e) const {
      return is_infinite(e.first,e.second);
  }

  bool is_infinite(Edge_circulator& ec) const {
      return is_infinite(*ec);
  }

  bool is_infinite(Edge_iterator& ei) const {
    return is_infinite(*ei);
  }


  // SETTING
  // to be protected ?
public:
  void set_number_of_vertices(int n) {_number_of_vertices = n;}

public:
  void set_finite_vertex(Vertex*  v) { _finite_vertex = v;}

//   void set_finite_vertex(CGAL_NULL_TYPE v)
//   {
//     CGAL_triangulation_assertion( v == NULL);
//     _finite_vertex=NULL;
//   }
// 

  void set_infinite_vertex(Vertex*  v) { _infinite_vertex = v;}


  // MODIFY
  void flip(Face* f, int i);
 
  void insert_first(Vertex* v);
  
  void insert_second(Vertex* v);
 
  void insert_in_face(Vertex* v, Face* f);
 
  void insert_in_edge(Vertex* v, Face* f, int i);
 
  // the following function insert in 1_dim triangulation
  // a vertex which is outside the convex hull of the vertices (a segment)
  // loc->vertex(li) is the verex of the triangulation closest to v
  void insert_collinear_outside(Vertex * v, Face * loc, int li);
  

  void remove_degree_3(Vertex* v, Face* f = NULL);
 
  void remove_second(Vertex* v);
  
  void remove_first(Vertex* v);
 
    
// ITERATOR METHODS
    Face_iterator faces_begin() const
    {
        Tds* ncthis = (Tds *)this;
        return Face_iterator(ncthis);
    }

    Face_iterator faces_end() const
    {
        Tds* ncthis = (Tds *)this;
        return Face_iterator(ncthis, 1);
    }

    Vertex_iterator vertices_begin() const
    {
        Tds* ncthis = (Tds*)this;
        return Vertex_iterator(ncthis);
    }

    Vertex_iterator vertices_end() const
    {
        Tds* ncthis = (Tds*)this;
        return Vertex_iterator(ncthis,1);
    }

    Edge_iterator edges_begin() const
    {
        Tds* ncthis = (Tds*)this;
        return Edge_iterator(ncthis);
    }

    Edge_iterator edges_end() const
    {
        Tds* ncthis = (Tds*)this;
        return Edge_iterator(ncthis,1);
    }





  // CHECKING
  bool is_valid(bool verbose = false, int level = 0) const;

  //Helping functions
public:
   void init(Vertex*  v);

public:
  void copy_tds(const Tds &tds);
 
  
  void swap(Tds &tds);
  
  void clear();
 

private:
  Geom_traits _geom_traits;
  Vertex* _infinite_vertex;
  Vertex* _finite_vertex; // to handle number_of_vertices == 1
  int _number_of_vertices; 
};


template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
flip(Face* f, int i)
{
      Face* n  = f->neighbor(i);
    
      Vertex*  v_cw = f->vertex(cw(i));
      Vertex*  v_ccw = f->vertex(ccw(i));

    // we should not attempt to flip two faces which are adjacent on two edges
    // This configuration happens in 1-dim triangulation
      
      int ni;
      CGAL_triangulation_assertion( n->has_vertex(v_cw,ni));
      ni = n->index(v_cw); //necsssary if no assertion is required
      ni = cw(ni);
      CGAL_triangulation_assertion( f->vertex(i) != n->vertex(ni));
      CGAL_triangulation_assertion( f == n->neighbor(ni) );
    
      //Old stuff
      // The following seems natural, but it fails if the faces
      // f and n are neighbors on two edges (1-dim triangulation,
      // with infinite faces
      // int ni = n->index(f);
    
      //  int ni = cw(n->index(v_cw));
      // CGAL_triangulation_assertion( f == n->neighbor(ni) );
    
       // bl == bottom left, tr == top right
        Face* tr = f->neighbor(ccw(i));
	Face* bl = n->neighbor(ccw(ni));
        int bli, tri;
     
        // Old stuff which seems natural
	// but makes problem if f and tr or n and bl are incident through two edges
	// bli = bl->index(n);
        // tri = tr->index(f);
	bli = 3 - ( bl->index(n->vertex(ni)) + bl->index(n->vertex(cw(ni))) );
	tri = 3 - (tr->index(f->vertex(i)) + tr->index(f->vertex(cw(i))));
							 
    
        f->set_vertex(cw(i), n->vertex(ni));
        n->set_vertex(cw(ni), f->vertex(i));
    
        // update the neighborhood relations
        f->set_neighbor(i, bl);
        bl->set_neighbor(bli, f);
    
        f->set_neighbor(ccw(i), n);
        n->set_neighbor(ccw(ni), f);
    
        n->set_neighbor(ni, tr);
        tr->set_neighbor(tri, n);
    
        if(v_cw->face() == f) {
            v_cw->set_face(n);
        }
    
        if(v_ccw->face() == n) {
            v_ccw->set_face(f);
        }
    }
  
template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
insert_first(Vertex* v)
{
    CGAL_triangulation_precondition( number_of_vertices() == 0);
    set_finite_vertex(v);
    v->set_face(NULL);
    set_number_of_vertices(1);
    return;
  }


template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
insert_second(Vertex* v)
 {
    CGAL_triangulation_precondition( number_of_vertices() == 1);
    Face* f1 = new Face(infinite_vertex(), finite_vertex(), v,
			NULL, NULL, NULL);
    Face* f2 = new Face(infinite_vertex(), v, finite_vertex(),
			f1, f1, f1);
    f1->set_neighbor(0, f2);
    f1->set_neighbor(1, f2);
    f1->set_neighbor(2, f2);
    
    infinite_vertex()->set_face(f1);
    v->set_face(f1);
    finite_vertex()->set_face(f1);
    set_number_of_vertices(2);
    return;
  }

template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
insert_in_face(Vertex* v, Face* f)
   //insert in face
    // vertex v will replace f->vertex(0)
  {
    CGAL_triangulation_precondition( v != NULL && f != NULL);
    
    Vertex* v0 = f->vertex(0);
    Vertex* v2 = f->vertex(2);
    Vertex* v1 = f->vertex(1);
    
    Face* n1 = f->neighbor(1);
    Face* n2 = f->neighbor(2);
//     int i1,i2 ;
//     if (n1 != NULL) {i1= cw(n1->index(f->vertex(cw(1))));}
//     if (n2 != NULL) {i2 = cw(n2->index(f->vertex(cw(2))));}
    
    Face* f1 = new Face(v0, v, v2,
			f, n1, NULL);
    
    Face* f2 = new Face(v0, v1, v,
			f, NULL, n2);

    f1->set_neighbor(2, f2);
    f2->set_neighbor(1, f1);
    if (n1 != NULL) {
      int i1 = cw(n1->index(f->vertex(cw(1))));
      n1->set_neighbor(i1,f1);
    }
    if (n2 != NULL) {
      int i2 = cw(n2->index(f->vertex(cw(2))));
      n2->set_neighbor(i2,f2);}

    f->set_vertex(0, v);
    f->set_neighbor(1, f1);
    f->set_neighbor(2, f2);

    if( v0->face() == f  ) {  v0->set_face(f2); }
    v->set_face(f);

    set_number_of_vertices(number_of_vertices() +1);
  }


template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
insert_in_edge(Vertex* v, Face* f, int i)
   //insert in the edge opposite to vertex i of face f
  {
    CGAL_triangulation_precondition(v != NULL && f != NULL); 
    CGAL_triangulation_precondition( i == 0 || i == 1 || i == 2);

    Face* n = f->neighbor(i);

    // The following seems natural, but it may fail if the faces
    // this and n are neighbors on two edges (1-dim triangulation,
    // with infinite faces
    // int in = n->index(this);

    // int in;
    // CGAL_triangulation_assertion( n->has_vertex(f->vertex(cw(i)),in));
    CGAL_triangulation_assertion( n->has_vertex(f->vertex(cw(i))));
    int in= n->index(f->vertex(cw(i)));
    in = cw(in);
    insert_in_face(v,f);
    flip(n,in); 
    return;
  }

// the following function insert in 1_dim triangulation
  // a vertex which is outside the convex hull of the vertices (a segment)
  // loc->vertex(li) is the verex of the triangulation closest to v
template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
insert_collinear_outside(Vertex * v, Face * loc, int li)
{
    Vertex*  w = loc->vertex(li); // the extremal vertex
    Face* n = loc->neighbor(ccw(li));
    int ni = n->index(w);
    Face* f1 = new Face(infinite_vertex(), w, v,
			      NULL, NULL, n);
    n->set_neighbor(cw(ni), f1);
    Face*  f2 = new Face(infinite_vertex(), v, w,
			      f1, loc, f1);
    f1->set_neighbor(0, f2);
    f1->set_neighbor(1, f2);
    loc->set_neighbor(ccw(li), f2);
    v->set_face(f1);
    infinite_vertex()->set_face(f1);
    _number_of_vertices++;
  }

template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
remove_degree_3(Vertex* v, Face* f)
   // remove a vertex of degree 3
  {
    CGAL_triangulation_precondition(v != NULL);
    CGAL_triangulation_precondition(v != _infinite_vertex);
    CGAL_triangulation_precondition(v->degree() == 3);

    if (f == NULL) {f= v->face();}
    else { CGAL_triangulation_assertion( f->has_vertex(v));}
      
    int i = f->index(v);
    Face* left = f->neighbor(cw(i));
    Face* right = f->neighbor(ccw(i));
    Face *ll, *rr;
        
    int li = left->index(f);
    int ri = right->index(f);
    Vertex* q = left->vertex(li);
    CGAL_triangulation_assertion( left->vertex(li) == right->vertex(ri));
    
    ll = left->neighbor(cw(li));
    if(ll != NULL) {
      int lli = ll->index(left);
      ll->set_neighbor(lli, f);
    } 
    f->set_neighbor(cw(i), ll);
    if (f->vertex(ccw(i))->face() == left) f->vertex(ccw(i))->set_face(f);    
        
    rr = right->neighbor(ccw(ri));
    if(rr != NULL) {
      int rri = rr->index(right);
      rr->set_neighbor(rri, f);
    } 
    f->set_neighbor(ccw(i), rr);
    if (f->vertex(cw(i))->face() == right) f->vertex(cw(i))->set_face(f);  
        
    f->set_vertex(i, q);
    if (q->face() == right || q->face() == left) {
	   q->set_face(f);
    }
    delete right;
    delete left;
        
    // take care of _finite_vertex data member
    if (finite_vertex() == v){
      int i=f->index(v);
      Vertex* vv=is_infinite(f->vertex(cw(i))) ?
	f->vertex(ccw(i)) : f->vertex(cw(i));
      set_finite_vertex( vv);
    }

    delete v;
    set_number_of_vertices( number_of_vertices() -1);
  } 

template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
remove_second(Vertex* v)
  // remove the before last vertex
  {
    CGAL_triangulation_precondition(number_of_vertices()== 2);
    CGAL_triangulation_precondition( infinite_face()->has_vertex(v) &&
				     v != infinite_vertex());


    // take care of finite_vertex data member
    if (finite_vertex() == v) {
      Face* f = v->face();
      int i=f->index(v);
      Vertex* vv=is_infinite(f->vertex(cw(i))) ?
                           f->vertex(ccw(i)) : f->vertex(cw(i));
      set_finite_vertex( vv);
      }

    Face* f = v->face();
    Face* ff =f->neighbor(0);
    delete ff;
    delete f;
    delete v;
    set_number_of_vertices(1);
  }


template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
remove_first(Vertex* v)
 {
    CGAL_triangulation_precondition(number_of_vertices()== 1);
    CGAL_triangulation_precondition( finite_vertex()==v);
    
    delete v;
    set_finite_vertex(NULL);
    set_number_of_vertices(0);
    return;
  }

template < class Gt , class Vb, class Fb>
bool
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
is_valid(bool verbose, int level) const
  {
        if(number_of_vertices() <= 1){
            return true;
        }
    
        bool result = true;
	CGAL_triangulation_assertion( is_infinite(infinite_vertex()->face()));
	result = result && is_infinite(infinite_vertex()->face());			      
	// vertex count
        int vertex_count = 0;
        {
            Vertex_iterator it = vertices_begin();
    
            while(it != vertices_end()){
	        result = result && it->is_valid(verbose,level);
		CGAL_triangulation_assertion( it->is_valid(verbose, level) );
                ++vertex_count;
                ++it;
            }
        }
	result = result && (number_of_vertices() == vertex_count);
	CGAL_triangulation_assertion( number_of_vertices() == vertex_count );
    
        //edge count
	int edge_count = 0;
        {
            Edge_iterator it = edges_begin();
    
            while(it != edges_end()){
                ++edge_count;
                ++it;
            }
        }
    
        // face count
	int face_count = 0;
        {
            Face_iterator it = faces_begin();
    
            while(it != faces_end()) {
                ++face_count;
                result = result && it->is_valid(verbose, level);
                CGAL_triangulation_assertion( it->is_valid(verbose, level) );
                result = result && (! is_infinite( &(*it)));
                CGAL_triangulation_assertion( ! is_infinite(&(*it)) );
		++it;
            }
        }
        
        Face_circulator fc(infinite_vertex());
        Face_circulator    fcdone(fc);
        do {
	  result = result && fc->is_valid(verbose, level);
          CGAL_triangulation_assertion( fc->is_valid(verbose, level) );
	  ++face_count;
	  ++edge_count;
        }
        while(++fc != fcdone);
    
	result = result && ( edge_count == 3* (vertex_count -1) );
        CGAL_triangulation_assertion( edge_count == 3* (vertex_count -1) );
        result = result && ( face_count == 2* (vertex_count -1) );
        CGAL_triangulation_assertion( face_count == 2* (vertex_count -1) );
    
        return result;
    }

template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
init(Vertex*  v)
    {
        if( v == NULL ){
            _infinite_vertex = new Vertex();
	    set_number_of_vertices(0);
        } else if( v->face() == NULL ){
	    _infinite_vertex = new Vertex();
            set_finite_vertex(v);
            set_number_of_vertices(1);
        } else if( (v->face()->neighbor(0) == v->face()->neighbor(1))
                 &&(v->face()->neighbor(0) == v->face()->neighbor(2)) ){
            set_infinite_vertex(v);
            Face* f = v->face();
            int i = f->index(v);
            set_finite_vertex(f->vertex(cw(i)));
            set_number_of_vertices(2);
        } else {
            set_infinite_vertex(v);
            Face* f = v->face();
            int i = f->index(v);
            set_finite_vertex(f->vertex(cw(i)));
            // the following makes that the constructor of the
            // vertex iterator class works correctly
            set_number_of_vertices(3);

	    Vertex_iterator it = vertices_begin();
            while(it != vertices_end()){
                ++_number_of_vertices;
                ++it;
            }
            set_number_of_vertices(number_of_vertices()-3);
	}
    }


template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
copy_tds(const Tds &tds)
{
    map< void*, void*, less<void*> > V;
    map< void*, void*, less<void*> > F;
    Vertex*  v2;
    Face* f2;

    int n = tds.number_of_vertices();
    //non used?? int m = tds.number_of_faces();
    set_number_of_vertices(n);
    _geom_traits = tds.geom_traits();
    //the class Geom_traits is required to have a pertinent operator=

    // create the vertex at infinity
    v2 = new Vertex();
    V[tds.infinite_vertex()]=v2;
    set_infinite_vertex(v2);
            
    if(n == 0){  return ;    }

    if(n == 1) { 
       v2 = new Vertex(tds.finite_vertex()->point());
       V[tds.finite_vertex()]=v2;
       set_finite_vertex(v2);
       return;
    }
 
    // create the finite vertices
    {
      Vertex_iterator it=tds.vertices_begin();
      while (it != tds.vertices_end()) {
	V[&(*it)] = new Vertex( it->point() );
	++it;
      }
    }
  
     // create the finite faces
    {
      Face_iterator it = tds.faces_begin();
      while(it != tds.faces_end()){
	F[&(*it)]=  new Face( (Vertex*) V[it->vertex(0)],
			      (Vertex*) V[it->vertex(1)],
			      (Vertex*) V[it->vertex(2)] );
	++(it);
        }
    }

    //create the infinite faces
    {
      Face_circulator fc = tds.infinite_vertex()->incident_faces();
      Face_circulator done(fc);
      do{
	F[&(*fc)]=  new Face( (Vertex*) V[fc->vertex(0)],
			      (Vertex*) V[fc->vertex(1)],
			      (Vertex*) V[fc->vertex(2)] );
      }while(++fc != done);
    }

    // link the infinite vertex to a triangle
    infinite_vertex()->set_face( (Face*) F[tds.infinite_face()] );

    // link the finite vertices to a triangle
    {
      Vertex_iterator it = tds.vertices_begin();
      while(it != tds.vertices_end()) {
            v2 = (Vertex*) V[&(*it)];
            v2->set_face( (Face*) F[it->face()] );
            ++it;
        }
    }

    // hook neighbor pointers of the finite faces
    {
        Face_iterator  it = tds.faces_begin();
        while(it != tds.faces_end()){
          for(int j = 0; j < 3; j++){
            f2 = ((Face*) F[&(*it)]);
            f2->set_neighbor(j, (Face*) F[it->neighbor(j)] );
          }
          ++it;
        }
    }

    // hook neighbor pointers of the infinite faces
    {
        Face_circulator  fc = tds.infinite_vertex()->incident_faces(),
            done(fc);
        do{
          f2 = ((Face*) F[&(*fc)]);
          for(int j = 0; j < 3; j++){
            f2->set_neighbor(j, (Face*) F[fc->neighbor(j)] );
          }
        }while(++fc != done);
    }
    CGAL_triangulation_postcondition( is_valid() );
    return;

  }
 
template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
swap(Tds &tds)
 {
    Geom_traits   t  = geom_traits();
    Vertex*  fv = finite_vertex();
    Vertex*  iv = infinite_vertex();
    int     nv = number_of_vertices();

    _geom_traits = tds.geom_traits(); 
    //the class Geom_traits is required to have a pertinent operator=
    set_finite_vertex(tds.finite_vertex());
    set_infinite_vertex(tds.infinite_vertex());
    set_number_of_vertices(tds.number_of_vertices());

    tds._geom_traits = t;
    tds.set_finite_vertex(fv);
    tds.set_infinite_vertex(iv);
    tds.set_number_of_vertices(nv);
  }

template < class Gt , class Vb, class Fb>
void
CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>::
clear()
 {
   if(number_of_vertices() == 0) return;

   if(number_of_vertices()==1) {
     infinite_vertex()->set_face(NULL);
     delete _finite_vertex;
     set_finite_vertex(NULL);
     set_number_of_vertices(0);
     return;
   }
      
   list<Face*> Faces;
   list<Vertex*> Vertices;

    {
        Vertex_iterator it = vertices_begin(), done = vertices_end();
        do{
            Vertices.push_front(&(*it));
        }while(++it!=done);
    }
    {
        Face_iterator it = faces_begin(), done = faces_end();
        while(it!=done){
            Faces.push_front(&(*it));
            ++it;
        }
        Face_circulator fc = infinite_vertex()->incident_faces(),
            fcdone(fc);
        do{
            Faces.push_front(&(*fc));
        }while(++fc != fcdone);
    }
    CGAL_triangulation_assertion( number_of_faces() == (int) Faces.size());
     
    {
        list<Face*>::iterator
          it=Faces.begin(),done=Faces.end();
        do{
            delete *it;
        }while(++it!=done);
    }
    {
        list<Vertex*>::iterator
          it=Vertices.begin(),done=Vertices.end();
        do{
            delete *it;
        }while(++it!=done);
    }

    infinite_vertex()->set_face(NULL);
    set_finite_vertex(NULL);
    set_number_of_vertices(0);
  }




template < class Gt , class Vb, class Fb>
istream&
operator>>(istream& is,  
	   CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>& tds)
{
  typedef CGAL_Triangulation_ds_vertex_2<Vb,Fb>::Vertex Vertex;
  typedef CGAL_Triangulation_ds_face_2<Vb,Fb>::Face Face;
  typedef Gt Geom_traits;
  typedef typename Vb::Point Point;

  if(tds.number_of_vertices() != 0){
        tds.clear();
    }

    int i = 0;
    int n, m, d;
    is >> n >> m >> d;

    tds.set_number_of_vertices(n-1);

    vector<Vertex* > V(n);
    vector<Face*> F(m);
    Vertex * v;
    Face * f=NULL; //initialised to avoid a warning

    // the first point is at infinity

    Point p;
    is >> p;
    v = tds.infinite_vertex();
    v->set_point(p);
    V[i] = v;
    ++i;

    if(n == 1){
        return is;
    }
    // for the other points we create new vertices
    for(; i < n; i++) {
        Point p;
        is >> p;
        V[i] = new Vertex(p);
    }

    tds.set_finite_vertex(V[i-1]);

    if(n == 2){
        return is;
    }
    // Creation of the faces
    for(i = 0; i < m; i++) {
        int i0, i1, i2;
        is >> i0 >> i1 >> i2;
        f = new Face(V[i0], V[i1], V[i2]);
        F[i] = f;
        // The face pointer of vertices is set too often,
        // but otherwise we had to use a further map
        V[i0]->set_face(f);
        V[i1]->set_face(f);
        V[i2]->set_face(f);
    }

    // Setting the neighbor pointers is the same for the
    // faces on the other side of the plane  and the other faces
    for(i = 0; i < m; i++) {
        int i0, i1, i2;
        is >> i0 >> i1 >> i2;
        f = F[i];
        f->set_neighbor(0, F[i0]);
        f->set_neighbor(1, F[i1]);
        f->set_neighbor(2, F[i2]);
    }
    tds.infinite_vertex()->set_face(f);
    return is;
}


template < class Gt, class Vb, class Fb>
ostream&
operator<<(ostream& os, 
	   const  CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb>  &tds)
{
  map< void*, int, less<void*> > V;
  map< void*, int, less<void*> > F;
  typedef CGAL_Triangulation_default_data_structure_2<Gt,Vb,Fb> Tds;
  typedef  Tds::Vertex  Vertex;
  typedef  Tds::Face   Face;
  typedef  Tds::Edge   Edge;
  typedef  Tds::Face_iterator  Face_iterator;
  typedef  Tds::Vertex_iterator  Vertex_iterator;
  typedef  Tds::Edge_iterator  Edge_iterator;
  typedef  Tds::Face_circulator  Face_circulator;

  Vertex* v;

    int n = tds.number_of_vertices() + 1;
    int m = tds.number_of_faces();
    if(CGAL_is_ascii(os)){
        os << n << ' ' << m << ' ' << tds.dimension() << endl;
    } else {
        os << n << m << tds.dimension();
    }

    // write the vertex at infinity
    int i = 0;
    v = tds.infinite_vertex();
    V[v] = i;
    os << v->point();
    if(CGAL_is_ascii(os)){
        os << ' ';
    }
    if(n == 1){
        return os;
    }

    // write the finite vertices
    {
        Vertex_iterator
          it = tds.vertices_begin();

        while(it != tds.vertices_end()){
            V[&(*it)] = ++i;
            os << it->point();
            if(CGAL_is_ascii(os)){
                os << ' ';
            }
            ++it;
        }
    }
    CGAL_triangulation_assertion( (i+1) == n );
    if(CGAL_is_ascii(os)){ os << "\n";}

    if(n == 2){
        return os;
    }

    i = 0;
    // vertices of the finite faces
    {
        Face_iterator
          it = tds.faces_begin();

        while(it != tds.faces_end()){
            F[&(*it)] = i++;
            for(int j = 0; j < 3; j++){
                os << V[it->vertex(j)];
                if(CGAL_is_ascii(os)){
                    if(j==2) {
                        os << "\n";
                    } else {
                        os <<  ' ';
                    }
                }
            }
            ++it;
        }
    }

    // vertices of the infinite faces
    {
        Face_circulator
            fc = tds.infinite_vertex()->incident_faces(),
            done(fc);

        do{
            F[&(*fc)] = i++;
            for(int j = 0; j < 3; j++){
                os << V[fc->vertex(j)];
                if(CGAL_is_ascii(os)){
                    if(j==2) {
                        os << "\n";
                    } else {
                        os <<  ' ';
                    }
                }
            }
        }while(++fc != done);
    }
    CGAL_triangulation_assertion( i == m );

    // neighbor pointers of the finite faces
    {
        Face_iterator
            it = tds.faces_begin();
        while(it != tds.faces_end()){
            for(int j = 0; j < 3; j++){
                os << F[&(* it->neighbor(j))];
                if(CGAL_is_ascii(os)){
                    if(j==2) {
                        os << "\n";
                    } else {
                        os <<  ' ';
                    }
                }
            }
            ++it;
        }
    }

    // neighbor pointers of the infinite faces
    {
        Face_circulator
            fc = tds.infinite_vertex()->incident_faces(),
            done(fc);

        do{
            for(int j = 0; j < 3; j++){
                os << F[fc->neighbor(j)];
                if(CGAL_is_ascii(os)){
                    if(j==2) {
                        os << "\n";
                    } else {
                        os <<  ' ';
                    }
                }
            }
        }while(++fc != done);
    }

    
    return os;
}


#endif //CGAL_TRIANGULATION_DEFAULT_DATA_STRUCTURE_2_H
