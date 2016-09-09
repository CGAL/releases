// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Triangulation_3.h
// package       : Triangulation3 (1.29)
// revision      : $Revision: 1.74 $
//
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_3_H
#define CGAL_TRIANGULATION_3_H

#include <CGAL/basic.h>

#include <iostream>
#include <list>
#include <map> 

#include <utility>

#include <CGAL/Triangulation_utils_3.h>
#include <CGAL/Random.h>
#include <CGAL/triple.h>

#include <CGAL/Pointer.h>
#include <CGAL/circulator.h>

//#include <CGAL/predicates_on_points_3.h>

#include <CGAL/triangulation_assertions.h>

#include <CGAL/Triangulation_data_structure_3.h>

#include <CGAL/Triangulation_cell_3.h>
#include <CGAL/Triangulation_vertex_3.h>
#include <CGAL/Triangulation_handles_3.h>
#include <CGAL/Triangulation_iterators_3.h>
#include <CGAL/Triangulation_circulators_3.h>

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class GT, class Tds>
class Triangulation_cell_iterator_3;
template < class GT, class Tds>
class Triangulation_vertex_iterator_3;
template < class GT, class Tds>
class Triangulation_edge_iterator_3;
template < class GT, class Tds>
class Triangulation_facet_iterator_3;

template < class GT, class Tds>
class Triangulation_cell_circulator_3;
template < class GT, class Tds>
class Triangulation_facet_circulator_3;

template < class GT, class Tds>
class Triangulation_cell_3;

template < class GT, class Tds > std::istream& operator>> 
(std::istream& is, Triangulation_3<GT,Tds> &tr);
 
template < class GT, class Tds >
class Triangulation_3
  :public Triangulation_utils_3
{
  friend std::istream& operator>> CGAL_NULL_TMPL_ARGS
  (std::istream& is, Triangulation_3<GT,Tds> &tr);

  friend class Triangulation_cell_3<GT,Tds>;
  friend class Triangulation_vertex_3<GT,Tds>;

  friend Triangulation_cell_iterator_3<GT,Tds>;
  friend Triangulation_facet_iterator_3<GT,Tds>;
  friend Triangulation_edge_iterator_3<GT,Tds>;
  friend Triangulation_vertex_iterator_3<GT,Tds>;

  friend Triangulation_cell_circulator_3<GT,Tds>;
  friend Triangulation_facet_circulator_3<GT,Tds>;

public:

  typedef typename GT::Point Point;
  typedef typename GT::Segment Segment;
  typedef typename GT::Triangle Triangle;
  typedef typename GT::Tetrahedron Tetrahedron;

  typedef Triangulation_cell_handle_3<GT,Tds> Cell_handle;
  typedef Triangulation_vertex_handle_3<GT,Tds> Vertex_handle;

  typedef Triangulation_cell_3<GT,Tds> Cell;
  typedef Triangulation_vertex_3<GT,Tds> Vertex;
  typedef std::pair<Cell_handle, int> Facet;
  typedef triple<Cell_handle, int, int> Edge;

  typedef Triangulation_cell_circulator_3<GT,Tds>      Cell_circulator;
  typedef Triangulation_facet_circulator_3<GT,Tds>     Facet_circulator;

  typedef Triangulation_cell_iterator_3<GT,Tds>   Cell_iterator;
  typedef Triangulation_facet_iterator_3<GT,Tds>   Facet_iterator;
  typedef Triangulation_edge_iterator_3<GT,Tds>   Edge_iterator;
  typedef Triangulation_vertex_iterator_3<GT,Tds> Vertex_iterator;

  enum Locate_type {
    VERTEX=0, 
    EDGE, //1
    FACET, //2
    CELL, //3
    OUTSIDE_CONVEX_HULL, //4
    OUTSIDE_AFFINE_HULL };//5

protected:
  Tds _tds;
  GT  _gt;
  Vertex_handle infinite; //infinite vertex
  
  void init_tds()
    {
      infinite = (Vertex*) 
 	_tds.insert_increase_dimension(Vertex());
      // this causes a problem of accessing non initialized data 
      // (seen by purify) in _tds.insert_increase_dimension
      // when doing Vertex* w = new Vertex(v)
      // to be solved...
      // but the following solution does not work for regular triangulation :

// 	_tds.insert_increase_dimension(Vertex(Point(0,0,0)));
//       // coordinates are given to this vertex but they will and must
//       // NEVER be accessed !! done to avoid a problem of accessing
//       // non initialized data

      handle2pointer( infinite ); 
      handle2pointer( Cell_handle() );
      // ( forces the compiler to instanciate handle2pointer )
    }
  
  // debug
  Triangulation_3(const Point & p0,
		  const Point & p1, 
		  const Point & p2,
		  const Point & p3)
    : _tds(), _gt()
    {
      init_tds();
      insert_increase_dimension(p0);
      insert_increase_dimension(p1);
      insert_increase_dimension(p2);
      insert_increase_dimension(p3);
    } 

public:

  // CONSTRUCTORS
  Triangulation_3()
    : _tds(), _gt()
    {
      init_tds();
    }

  Triangulation_3(const GT & gt) 
    : _tds(), _gt(gt)
    {
      init_tds();
    }

  // copy constructor duplicates vertices and cells
  Triangulation_3(const Triangulation_3<GT,Tds> & tr)
    : _gt(tr._gt)
    {
      infinite = (Vertex *) _tds.copy_tds(tr._tds, &(*(tr.infinite)) );
    }

  // DESTRUCTOR

  ~Triangulation_3()
    {
      clear();
      //    infinite.Delete();    BUG !!! already deleted by _tds.clear()
    }

  void clear()
    {
      _tds.clear();
      init_tds();
    }

  Triangulation_3 & operator=(const Triangulation_3 & tr)
    {
      //     clear();               BUG !!
      //     infinite.Delete();
      infinite = (Vertex *) _tds.copy_tds( tr._tds, &*tr.infinite );
      _gt = tr._gt;
      return *this;
    }

  // HELPING FUNCTIONS
   
  void copy_triangulation(const Triangulation_3<GT,Tds> & tr)
    {
      //     clear();               BUG !!
      //     infinite.Delete();
      _gt = tr._gt;
      infinite = (Vertex *) _tds.copy_tds( tr._tds, &*tr.infinite );
    }

  void swap(Triangulation_3 &tr)
    {
      GT t(geom_traits());
      _gt = tr.geom_traits();
      tr._gt = t; 

      Vertex_handle inf = infinite_vertex();
      infinite = tr.infinite_vertex();
      tr.infinite = inf;

      _tds.swap(tr._tds);
    }

  //ACCESS FUNCTIONS
  inline 
  const GT & geom_traits() const 
    { return _gt;}
  
  inline
  const Tds & tds() const 
    { return _tds;}
  
  //  inline
  int dimension() const 
    { return _tds.dimension();}

  int number_of_finite_cells() const;

  int number_of_cells() const;
 
  int number_of_finite_facets() const;

  int number_of_facets() const;

  int number_of_finite_edges() const;
 
  int number_of_edges() const;
  
  inline
  int number_of_vertices() const // number of finite vertices
    {return _tds.number_of_vertices()-1;}

  inline
  Vertex_handle infinite_vertex() const
    {
      return infinite;
    }
   
  inline
  Cell_handle infinite_cell() const
    {
      //    CGAL_triangulation_precondition(infinite_vertex()->cell()->
      //				    has_vertex(infinite_vertex()));
      return infinite_vertex()->cell();
    }

  // ASSIGNMENT
  void set_number_of_vertices(int n) 
    { _tds.set_number_of_vertices(n+1); }
   
  inline
  void add_cell( Cell_handle c ) { _tds.add_cell( &(*c) ); }

  // GEOMETRIC ACCESS FUNCTIONS
  
  Tetrahedron tetrahedron(const Cell_handle c) const
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      CGAL_triangulation_precondition( ! is_infinite(c) );
      return Tetrahedron(c->vertex(0)->point(),
			 c->vertex(1)->point(),
			 c->vertex(2)->point(),
			 c->vertex(3)->point());
    }

  Triangle triangle(const Cell_handle c, int i) const;

  Triangle triangle(const Facet & f) const
    { return triangle(f.first, f.second); }

  Segment segment(const Cell_handle c, int i, int j) const;


  Segment segment(const Edge & e) const
    { return segment(e.first,e.second,e.third); }

  //   Segment segment(const Edge_circulator& ec) const
  //   {
  //     return segment(*ec);
  //   }
    
  //   Segment segment(const Edge_iterator& ei) const
  //   {
  //     return segment(*ei);
  //   }

  // TEST IF INFINITE FEATURES
  bool is_infinite(const Vertex_handle v) const 
    { return v == infinite_vertex(); }

  bool is_infinite(const Cell_handle c) const 
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      return c->has_vertex(infinite_vertex());
    }
  
  bool is_infinite(const Cell_handle c, int i) const;

  bool is_infinite(const Facet & f) const 
    { return is_infinite(f.first,f.second); }

  bool is_infinite(const Cell_handle c, int i, int j) const; 

  bool is_infinite(const Edge & e) const
    { return is_infinite(e.first,e.second,e.third); }

  //   bool is_infinite(const Edge_circulator& ec) const 
  //     {
  //       return is_infinite(*ec);
  //     }

  //   bool is_infinite(const Edge_iterator& ei) const 
  //     {
  //       return is_infinite(*ei);
  //     }

  //QUERIES

  bool is_vertex(const Point & p, Vertex_handle & v) const;

  Cell_handle locate(const Point & p) const;

  inline Cell_handle
  locate(const Point & p, Cell_handle start) const
    {
      Locate_type lt;
      int li, lj;
      return locate( p, start, lt, li, lj);
    }

  inline Cell_handle
  locate(const Point & p,
	 Locate_type & lt, int & li, int & lj) const;

  Cell_handle
  locate(const Point & p,
	 Cell_handle start,
	 Locate_type & lt, int & li, int & lj) const;
  // returns the (finite or infinite) cell p lies in
  // starts at cell "start"
  // start must be non NULL and finite
  // if lt == OUTSIDE_CONVEX_HULL, li is the
  // index of a facet separating p from the rest of the triangulation
  // in dimension 2 :
  // returns a facet (Cell_handle,li) if lt == FACET
  // returns an edge (Cell_handle,li,lj) if lt == EDGE
  // returns a vertex (Cell_handle,li) if lt == VERTEX
  // if lt == OUTSIDE_CONVEX_HULL, li, lj give the edge of c
  // separating p from the rest of the triangulation
  // lt = OUTSIDE_AFFINE_HULL if p is not coplanar with the triangulation


  // PREDICATES ON POINTS ``TEMPLATED'' by the geom traits
  
  Bounded_side
  side_of_tetrahedron(const Point & p,
		      const Point & p0, 
		      const Point & p1,
		      const Point & p2, 
		      const Point & p3,
		      Locate_type & lt, int & i, int & j ) const;
  // p0,p1,p2,p3 supposed to be non coplanar
  // tetrahedron p0,p1,p2,p3 is supposed to be well oriented
  // returns :
  // ON_BOUNDED_SIDE if p lies strictly inside the tetrahedron
  // ON_BOUNDARY if p lies on one of the facets
  // ON_UNBOUNDED_SIDE if p lies strictly outside the tetrahedron
  // ?? locate type...

  Bounded_side
  side_of_cell(const Point & p, 
	       Cell_handle c,
	       Locate_type & lt, int & i, int & j) const;
  // returns
  // ON_BOUNDED_SIDE if p inside the cell
  // (for an infinite cell this means that p lies strictly in the half space
  // limited by its finite facet)
  // ON_BOUNDARY if p on the boundary of the cell
  // (for an infinite cell this means that p lies on the *finite* facet)
  // ON_UNBOUNDED_SIDE if p lies outside the cell
  // (for an infinite cell this means that p is not in the preceding
  // two cases)  
  // lt has a meaning only when ON_BOUNDED_SIDE or ON_BOUNDARY

  Bounded_side
  side_of_triangle(const Point & p,
		   const Point & p0, 
		   const Point & p1,
		   const Point & p2,
		   Locate_type & lt, int & i, int & j ) const;
  // p0,p1,p2 supposed to define a plane
  // p supposed to lie on plane p0,p1,p2
  // triangle p0,p1,p2 defines the orientation of the plane
  // returns
  // ON_BOUNDED_SIDE if p lies strictly inside the triangle
  // ON_BOUNDARY if p lies on one of the edges
  // ON_UNBOUNDED_SIDE if p lies strictly outside the triangle


  Bounded_side
  side_of_facet(const Point & p,
		Cell_handle c,
		//		int i,
		Locate_type & lt, int & li, int & lj) const;
  // supposes dimension 2 otherwise does not work for infinite facets
  // returns :
  // ON_BOUNDED_SIDE if p inside the facet
  // (for an infinite facet this means that p lies strictly in the half plane
  // limited by its finite edge)
  // ON_BOUNDARY if p on the boundary of the facet
  // (for an infinite facet this means that p lies on the *finite* edge)
  // ON_UNBOUNDED_SIDE if p lies outside the facet
  // (for an infinite facet this means that p is not in the
  // preceding two cases) 
  // lt has a meaning only when ON_BOUNDED_SIDE or ON_BOUNDARY
  // when they mean anything, li and lj refer to indices in the cell c 
  // giving the facet (c,i)

  Bounded_side
  side_of_facet(const Point & p,
		const Facet & f,
		Locate_type & lt, int & li, int & lj) const
    {
      CGAL_triangulation_precondition( f.second == 3 );
      return side_of_facet(p, f.first, lt, li, lj);
    }

  Bounded_side
  side_of_segment(const Point & p,
		  const Point & p0, 
		  const Point & p1,
		  Locate_type & lt, int & i ) const;
  // p0, p1 supposed to be different
  // p supposed to be collinear to p0, p1
  // returns :
  // ON_BOUNDED_SIDE if p lies strictly inside the edge
  // ON_BOUNDARY if p equals p0 or p1
  // ON_UNBOUNDED_SIDE if p lies strictly outside the edge

  Bounded_side
  side_of_edge(const Point & p,
	       Cell_handle c,
	       Locate_type & lt, int & li) const;
  // supposes dimension 1 otherwise does not work for infinite edges
  // returns :
  // ON_BOUNDED_SIDE if p inside the edge 
  // (for an infinite edge this means that p lies in the half line
  // defined by the vertex)
  // ON_BOUNDARY if p equals one of the vertices
  // ON_UNBOUNDED_SIDE if p lies outside the edge
  // (for an infinite edge this means that p lies on the other half line)
  // lt has a meaning when ON_BOUNDED_SIDE and ON_BOUNDARY
  // li refer to indices in the cell c 

  Bounded_side
  side_of_edge(const Point & p,
	       const Edge & e,
	       Locate_type & lt, int & li) const
    {
      CGAL_triangulation_precondition( e.second == 0 );
      CGAL_triangulation_precondition( e.third == 1 );
      return side_of_edge(p, e.first, lt, li);
    }

  // MODIFIERS
  bool flip(Facet f);
  bool flip(Cell_handle c, int i);
  // returns false if the facet is not flippable
  // true other wise and
  // flips facet i of cell c
  // c will be replaced by one of the new cells
  void flip_flippable(Facet f);
  void flip_flippable(Cell_handle c, int i);
  // flips facet i of cell c
  // c will be replaced by one of the new cells

  bool flip(Edge e);
  bool flip(Cell_handle c, int i, int j);
  // returns false if the edge is not flippable
  // true otherwise and
  // flips edge i,j of cell c
  // c will be deleted
  void flip_flippable(Edge e);
  void flip_flippable(Cell_handle c, int i, int j);
  // flips edge i,j of cell c
  // c will be deleted

  //INSERTION 

  Vertex_handle insert(const Point & p );

  Vertex_handle insert(const Point & p, Cell_handle start);

  template < class InputIterator >
  int insert(InputIterator first, InputIterator last)
    {
      int n = number_of_vertices();
      while(first != last){
	insert(*first);
	++first;
      }
      return number_of_vertices() - n;
    }

  Vertex_handle
  insert_in_cell(const Point & p, Cell_handle c);

  Vertex_handle
  insert_in_facet(const Point & p, Cell_handle c, int i);

  Vertex_handle
  insert_in_facet(const Point & p, const Facet & f)
    {
      return insert_in_facet(p, f.first,f.second);
    }

  Vertex_handle
  insert_in_edge(const Point & p, Cell_handle c, int i, int j);

  Vertex_handle
  insert_in_edge(const Point & p, const Edge & e)
    {
      return insert_in_edge(p, e.first,e.second,e.third);
    }
  
  Vertex_handle
  insert_outside_convex_hull(const Point & p, Cell_handle c);
  //			     int li, int lj=0)
  // c is an infinite cell containing p
  // whose facet li lies on the convex hull boundary
  // and separates p from the triangulation (in dimension 3)
  // p is strictly outside the convex hull
  // in dimension 2, edge li,lj separates p from the triangulation
  // in dimension 1, vertex li separates p from the triangulation
  // dimension 0 not allowed, use outside-affine-hull

private:
  Cell_handle
  hat(Vertex_handle v, Cell_handle c);
  // recursive traversal of the set of facets of the convex hull
  // that are visible from v
  // v replaces infinite_vertex in these cells
  // on the boundary, new cells with vertices v, infinite_vertex
  // and the two vertices of an edge of the boumdary are created
  // returns a cell inside the "hat", having a facet on its boundary
  
  void
  link(Vertex_handle v, Cell_handle c);
  // c belongs to the hat of v and has a facet on its boundary
  // traverses the boundary of the hat and finds adjacencies
  // traversal is done counterclockwise as seen from v
public:

  Vertex_handle
  insert_outside_affine_hull(const Point & p);

  //TRAVERSING : ITERATORS AND CIRCULATORS
  Cell_iterator finite_cells_begin() const
    {
      if ( dimension() < 3 ) return cells_end();
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds> *)this;
      return Cell_iterator(ncthis, false); // false means "without
      // infinite cells" 
    }
  Cell_iterator all_cells_begin() const
    {
      if ( dimension() < 3 ) return cells_end();
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds> *)this;
      return Cell_iterator(ncthis, true); // true means "with infinite cells"
    }
  Cell_iterator cells_end() const
    {
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds> *)this;
      return Cell_iterator(ncthis); // not second argument -> past-end
    }

  Vertex_iterator finite_vertices_begin() const
    {
      if ( number_of_vertices() <= 0 ) return vertices_end();
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Vertex_iterator(ncthis, false);
    }
  Vertex_iterator all_vertices_begin() const
    {
      if ( number_of_vertices() <= 0 ) return vertices_end();
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Vertex_iterator(ncthis, true);
    }
  Vertex_iterator vertices_end() const
    {
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Vertex_iterator(ncthis);
    }

  Edge_iterator finite_edges_begin() const
    {
      if ( dimension() < 1 ) return edges_end();
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Edge_iterator(ncthis, false);
    }
  Edge_iterator all_edges_begin() const
    {
      if ( dimension() < 1 ) return edges_end();
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Edge_iterator(ncthis, true);
    }
  Edge_iterator edges_end() const
    {
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Edge_iterator(ncthis);
    }

  Facet_iterator finite_facets_begin() const
    {
      if ( dimension() < 2 ) return facets_end();
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Facet_iterator(ncthis, false);
    }
  Facet_iterator all_facets_begin() const
    {
      if ( dimension() < 2 ) return facets_end();
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Facet_iterator(ncthis, true);
    }
  Facet_iterator facets_end() const
    {
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Facet_iterator(ncthis);
    }

  // cells around an edge
  Cell_circulator incident_cells(const Edge & e) const
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Cell_circulator(ncthis,e);
    }
  Cell_circulator incident_cells(Cell_handle c, int i, int j) const
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Cell_circulator(ncthis,c,i,j);
    }
  Cell_circulator incident_cells(const Edge & e, Cell_handle start) const
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Cell_circulator(ncthis,e,start);
    }
  Cell_circulator incident_cells(Cell_handle c, int i, int j, 
				 Cell_handle start) const  
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Cell_circulator(ncthis,c,i,j,start);
    }

  // facets around an edge
  Facet_circulator incident_facets(const Edge & e) const
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Facet_circulator(ncthis,e);
    }
  Facet_circulator incident_facets(Cell_handle c, int i, int j) const
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Facet_circulator(ncthis,c,i,j);
    }
  Facet_circulator incident_facets(const Edge & e, 
				   const Facet & start) const
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Facet_circulator(ncthis,e,start);
    }
  Facet_circulator incident_facets(Cell_handle c, int i, int j, 
				   const Facet & start) const  
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Facet_circulator(ncthis,c,i,j,start);
    }
  Facet_circulator incident_facets(const Edge & e, 
				   Cell_handle start, int f) const
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Facet_circulator(ncthis,e,start,f);
    }
  Facet_circulator incident_facets(Cell_handle c, int i, int j, 
				   Cell_handle start, int f) const  
    {
      CGAL_triangulation_precondition( dimension() == 3 );
      Triangulation_3<GT, Tds>* ncthis 
	= (Triangulation_3<GT, Tds>*)this;
      return Facet_circulator(ncthis,c,i,j,start,f);
    }

  // around a vertex
  void
  incident_cells(Vertex_handle v, 
		 std::set<Cell*, std::less<Cell*> > & cells,
		 Cell_handle c = (Cell*) NULL ) const;


  void
  incident_vertices(Vertex_handle v, 
		    std::set<Vertex*, std::less<Vertex*> > & vertices,
		    Cell_handle c = (Cell*) NULL ) const;

private:
  void 
  util_incident_vertices(Vertex_handle v, 
			 std::set<Vertex*, std::less<Vertex*> > & vertices,
			 std::set<Cell*, std::less<Cell*> > & cells,
			 Cell_handle c ) const;
  inline
  Cell_handle create_cell(Vertex_handle v0, Vertex_handle v1,
			  Vertex_handle v2, Vertex_handle v3,
			  Cell_handle c0, Cell_handle c1,
			  Cell_handle c2, Cell_handle c3)
    {
      Cell_handle cnew = new Cell (v0,v1,v2,v3,c0,c1,c2,c3);
      _tds.add_cell( &(*cnew) );
      return cnew;
    }

public:

  // CHECKING
  bool is_valid(bool verbose = false, int level = 0) const;

  bool is_valid(Cell_handle c, bool verbose = false, int level = 0) const;

  bool is_valid_finite(Cell_handle c, 
		       bool verbose = false, int level = 0) const;

};


template < class GT, class Tds >
std::istream & 
operator>> (std::istream& is, Triangulation_3<GT, Tds> &tr)
  // reads
  // the dimension
  // the number of finite vertices
  // the non combinatorial information on vertices (point, etc)
  // the number of cells
  // the cells by the indices of their vertices in the preceding list
  // of vertices, plus the non combinatorial information on each cell
  // the neighbors of each cell by their index in the preceding list of cells
  // when dimension < 3 : the same with faces of maximal dimension
{
  //  return operator>>(is, tr._tds);
  typedef Triangulation_3<GT, Tds> Triangulation;
  typedef  typename Triangulation::Vertex_handle  Vertex_handle;
  typedef  typename Triangulation::Cell_handle Cell_handle;
  typedef  typename Triangulation::Vertex  Vertex;
  typedef  typename Triangulation::Cell Cell;
  typedef  typename Triangulation::Edge Edge;
  typedef  typename Triangulation::Facet Facet;
  typedef typename GT::Point Point;
  typedef typename Tds::Vertex TdsVertex;
  typedef typename Tds::Cell TdsCell;

  tr._tds.clear(); // infinite vertex created
  tr.infinite = new Vertex(); 

  int i;
  int n, m, d;
  is >> d >> n;
  tr._tds.set_dimension(d);
  tr.set_number_of_vertices(n);

  //  Point p;
  //  std::vector<Vertex_handle> V(n+1);
  std::map< int, TdsVertex*, std::less<int> > V;
  V[0] = &*(tr.infinite_vertex());
  // the infinite vertex is numbered 0

  for (i=1; i <= n; i++) {
//     is >> p;
//     V[i] = new Vertex();
//     V[i]->set_point(p);
    V[i] = new Vertex();
    is >> *V[i];
  }

  std::map< int, TdsCell*, std::less<int> > C;

  read_cells(is, tr._tds, n+1, V, m, C);
  for ( i=0 ; i<m; i++ ) {
    is >> *(C[i]);
  }
  CGAL_triangulation_assertion( tr.is_valid(false) );
  return is;

}
    
template < class GT, class Tds >
std::ostream & 
operator<< (std::ostream& os, const Triangulation_3<GT, Tds> &tr)
  // writes :
  // the dimension
  // the number of finite vertices
  // the non combinatorial information on vertices (point, etc)
  // the number of cells
  // the cells by the indices of their vertices in the preceding list
  // of vertices, plus the non combinatorial information on each cell
  // the neighbors of each cell by their index in the preceding list of cells
  // when dimension < 3 : the same with faces of maximal dimension
{
  typedef Triangulation_3<GT, Tds> Triangulation;
  typedef  typename Triangulation::Vertex  Vertex;
  typedef  typename Triangulation::Cell Cell;
  typedef  typename Triangulation::Edge Edge;
  typedef  typename Triangulation::Facet Facet;
  typedef  typename Triangulation::Vertex_iterator  Vertex_iterator;
  typedef  typename Triangulation::Cell_iterator  Cell_iterator;
  typedef  typename Triangulation::Edge_iterator  Edge_iterator;
  typedef  typename Triangulation::Facet_iterator  Facet_iterator;
 
  std::map< void*, int, std::less<void*> > V;
  //  std::map< void*, int, less<void*> > C;

  // outputs dimension and number of vertices
  int n = tr.number_of_vertices();
  switch ( tr.dimension() ) {
  case 3:
    {
      if(is_ascii(os)){
        os << tr.dimension() << std::endl << n << std::endl;
      } else {
        os << tr.dimension() << n;
      }
      break;
    }
  case 2:
    {
      if(is_ascii(os)){
        os << tr.dimension() << std::endl << n << std::endl;
      } else {
        os << tr.dimension() << n;
      }
      break;
    }
  case 1:
    {
      if(is_ascii(os)){
        os << tr.dimension() << std::endl << n << std::endl;
      } else {
        os << tr.dimension() << n ;
      }
      break;
    }
  case 0:
    {
      if(is_ascii(os)){
	os << tr.dimension() << std::endl << n << std::endl;
      } else {
	os << tr.dimension() << n;
      }
      break;
    }
  default:
    {
      if(is_ascii(os)){
	os << tr.dimension() << std::endl << n << std::endl;
      } else {
	os << tr.dimension() << n;
      }
    }
  }

  if (n == 0){
    return os;
  }

  // write the vertices
  V[&(*tr.infinite_vertex())] = 0;
  // the infinite vertex is numbered 0
  int i = 1;
  Vertex_iterator it = tr.all_vertices_begin();
    
  while(it != tr.vertices_end()){
    if ( (&(*it)) != &(*(tr.infinite_vertex())) ) {
      V[&(*it)] = i++;
      os << *it; // uses the << operator of Vertex
      if(is_ascii(os)){
	os << std::endl;
      }
    }
    ++it;
  }
  CGAL_triangulation_assertion( i == (n+1) );

  // write the non combinatorial information on the cells
  // using the << operator of Cell
  // works because the iterator of the tds traverses the cells in the
  // same order as the iterator of the triangulation
  switch ( tr.dimension() ) {
  case 3:
    {
      Cell_iterator it = tr.all_cells_begin();
      while( it != tr.cells_end() ) {
	os << *it; // other information
	++it;
      }
      break;
    }
  case 2:
    {
      Facet_iterator it = tr.all_facets_begin();
      while( it != tr.facets_end() ) {
	os << *((*it).first); // other information
	++it;
      }
      break;
    }
  case 1:
    {
      Edge_iterator it = tr.all_edges_begin();
      while( it != tr.edges_end() ) {
	os << *((*it).first); // other information 
	++it;
      }
      break;
    }
  }

  // asks the tds for the combinatorial information 
  //  print_cells(os, tr.tds(), n+1, V);
  print_cells(os, tr.tds(), V);
  
  //   // write the cells
  //   i = 0;
  //   int j;
  //   switch ( tr.dimension() ) {
  //   case 3:
  //     {
  //       os << m;
  //       if(is_ascii(os)){ os << std::endl;}

  //       // write the cells
  //       Cell_iterator it = tr.all_cells_begin();
  //       while( it != tr.cells_end() ) {
  // 	C[&(*it)] = i++;
  // 	for(j = 0; j < 4; j++){
  // 	  os << V[&(*it->vertex(j))];
  // 	  if(is_ascii(os)) {
  // 	    if ( j==3 ) {
  // 	      os << *it; // other information
  // 	      os << std::endl;
  // 	    } else {
  // 	      os << ' ';
  // 	    }
  // 	  }
  // 	}
  // 	++it;
  //       }
  //       CGAL_triangulation_assertion( i == m );
      
  //       // write the neighbors
  //       it = tr.all_cells_begin();
  //       while ( it != tr.cells_end() ) {
  // 	for (j = 0; j < 4; j++) {
  // 	  os << C[&(* it->neighbor(j))];
  // 	  if(is_ascii(os)){
  // 	    if(j==3) {
  // 	      os << std::endl;
  // 	    } else {
  // 	      os <<  ' ';
  // 	    }
  // 	  }
  // 	}
  // 	++it;
  //       }
  //       break;
  //     }
  //   case 2:
  //     {
  //       os << m;
  //       if(is_ascii(os)){ os << std::endl;}

  //       // write the facets
  //       Facet_iterator it = tr.all_facets_begin();
  //       while( it != tr.facets_end() ) {
  // 	C[&*((*it).first)] = i++;
  // 	for(j = 0; j < 3; j++){
  // 	  os << V[&(*(*it).first->vertex(j))];
  // 	  if(is_ascii(os)) {
  // 	    if ( j==2 ) {
  // 	      os << *((*it).first); // other information
  // 	      os << std::endl;
  // 	    } else {
  // 	      os <<  ' ';
  // 	    }
  // 	  }
  // 	}
  // 	++it;
  //       }
  //       CGAL_triangulation_assertion( i == m );
      
  //       // write the neighbors
  //       it = tr.all_facets_begin();
  //       while ( it != tr.facets_end() ) {
  // 	for (j = 0; j < 3; j++) {
  // 	  os << C[&*((*it).first->neighbor(j))];
  // 	  if(is_ascii(os)){
  // 	    if(j==2) {
  // 	      os << std::endl;
  // 	    } else {
  // 	      os <<  ' ';
  // 	    }
  // 	  }
  // 	}
  // 	++it;
  //       }
  //       break;
  //     }
  //   case 1:
  //     {
  //       os << m;
  //       if(is_ascii(os)){ os << std::endl;}

  //       // write the edges
  //       Edge_iterator it = tr.all_edges_begin();
  //       while( it != tr.edges_end() ) {
  // 	C[&*((*it).first)] = i++;
  // 	for(j = 0; j < 2; j++){
  // 	  os << V[&(*(*it).first->vertex(j))];
  // 	  if(is_ascii(os)) {
  // 	    if ( j==1 ) {
  // 	      os << *((*it).first); // other information 
  // 	      os << std::endl;
  // 	    } else {
  // 	      os <<  ' ';
  // 	    }
  // 	  }
  // 	}
  // 	++it;
  //       }
  //       CGAL_triangulation_assertion( i == m );
      
  //       // write the neighbors
  //       it = tr.all_edges_begin();
  //       while ( it != tr.edges_end() ) {
  // 	for (j = 0; j < 2; j++) {
  // 	  os << C[&*((*it).first->neighbor(j))];
  // 	  if(is_ascii(os)){
  // 	    if(j==1) {
  // 	      os << std::endl;
  // 	    } else {
  // 	      os <<  ' ';
  // 	    }
  // 	  }
  // 	}
  // 	++it;
  //       }
  //       break;
  //     }
  // //   default:
  // //     {
  // //       os << m;
  // //       if(is_ascii(os)){ os << std::endl;}
  // //       break;
  // //     }
  //   }
  return os ;
}

template < class GT, class Tds >
int
Triangulation_3<GT,Tds>::
number_of_finite_cells() const 
{ 
  if ( dimension() < 3 ) return 0;

  int i=0;
  Cell_iterator it = finite_cells_begin();
  while(it != cells_end()) {
    ++i;
    ++it;
  }
  return i;
}
  
template < class GT, class Tds >
int
Triangulation_3<GT,Tds>::
number_of_cells() const 
{ 
  if ( dimension() < 3 ) return 0;

  int i=0;
  Cell_iterator it = all_cells_begin();
  while(it != cells_end()) {
    ++i;
    ++it;
  }
  return i;
}

template < class GT, class Tds >
int
Triangulation_3<GT,Tds>::
number_of_finite_facets() const
{
  if ( dimension() < 2 ) return 0;

  int i=0;
  Facet_iterator it = finite_facets_begin();
  while(it != facets_end()) {
    ++i;
    ++it;
  }
  return i;
}

template < class GT, class Tds >
int
Triangulation_3<GT,Tds>::
number_of_facets() const
{
  if ( dimension() < 2 ) return 0;

  int i=0;
  Facet_iterator it = all_facets_begin();
  while(it != facets_end()) {
    ++i;
    ++it;
  }
  return i;
}

template < class GT, class Tds >
int
Triangulation_3<GT,Tds>::
number_of_finite_edges() const
{
  if ( dimension() < 1 ) return 0;

  int i=0;
  Edge_iterator it = finite_edges_begin();
  while(it != edges_end()) {
    ++i;
    ++it;
  }
  return i;
}

template < class GT, class Tds >
int
Triangulation_3<GT,Tds>::
number_of_edges() const
{
  if ( dimension() < 1 ) return 0;

  int i=0;
  Edge_iterator it = all_edges_begin();
  while(it != edges_end()) {
    ++i;
    ++it;
  }
  return i;
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Triangle
Triangulation_3<GT,Tds>::
triangle(const Cell_handle c, int i) const
{ 
  switch ( dimension() ) {
  case 3:
    {
      CGAL_triangulation_precondition
	( i == 0 || i == 1 || i == 2 || i == 3 );
      break;
    }
  case 2:
    {
      CGAL_triangulation_precondition( i == 3 );
      break;
    }
  default:
    CGAL_triangulation_assertion( false );
    // return ?
  }
  CGAL_triangulation_precondition( ! is_infinite(std::make_pair(c,i)) );
  switch (i) {
  case 0:
    return Triangle(c->vertex(1)->point(),
		    c->vertex(2)->point(),
		    c->vertex(3)->point());
    break;
  case 1:
    return Triangle(c->vertex(0)->point(),
		    c->vertex(2)->point(),
		    c->vertex(3)->point());
  case 2:
    return Triangle(c->vertex(0)->point(),
		    c->vertex(1)->point(),
		    c->vertex(3)->point());
  case 3:
    return Triangle(c->vertex(0)->point(),
		    c->vertex(1)->point(),
		    c->vertex(2)->point());
  default:
    {
      // impossible
      CGAL_triangulation_assertion( false );
      // to avoid warning at compile time :
      return Triangle(c->vertex(1)->point(),
		      c->vertex(2)->point(),
		      c->vertex(3)->point());
    }
  }
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Segment
Triangulation_3<GT,Tds>::
segment(const Cell_handle c, int i, int j) const
{
  CGAL_triangulation_precondition( i != j );
  switch ( dimension() ) {
  case 3:
    {
      CGAL_triangulation_precondition
	( ( i == 0 || i == 1 || i == 2 || i == 3 ) &&
	  ( j == 0 || j == 1 || j == 2 || j == 3 ) );
      break;
    }
  case 2:
    {
      CGAL_triangulation_precondition
	( ( i == 0 || i == 1 || i == 2 ) &&
	  ( j == 0 || j == 1 || j == 2 ) );
      break;
    }
  case 1:
    {
      CGAL_triangulation_precondition( ( i == 0 || i == 1 ) &&
				       ( j == 0 || j == 1 ) );
      break;
    }
  default:
    CGAL_triangulation_assertion( false );
    // return ?
  }
  CGAL_triangulation_precondition( ! is_infinite(make_triple(c,i,j)) );
  return Segment( c->vertex(i)->point(), c->vertex(j)->point() );
}

template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
is_infinite(const Cell_handle c, int i) const 
{
  switch ( dimension() ) {
  case 3:
    {
      CGAL_triangulation_precondition
	( i == 0 || i == 1 || i == 2 || i == 3 );
      break;
    }
  case 2:
    {
      CGAL_triangulation_precondition( i == 3 );
      break;
    }
  default:
    CGAL_triangulation_assertion( false );
    // return ?
  }
  switch (i) {
  case 0:
    return ( is_infinite(c->vertex(1)) ||
	     is_infinite(c->vertex(2)) ||
	     is_infinite(c->vertex(3)) );
    break;
  case 1:
    return ( is_infinite(c->vertex(0)) ||
	     is_infinite(c->vertex(2)) ||
	     is_infinite(c->vertex(3)) );
  case 2:
    return ( is_infinite(c->vertex(0)) ||
	     is_infinite(c->vertex(1)) ||
	     is_infinite(c->vertex(3)) );
  case 3:
    return ( is_infinite(c->vertex(0)) ||
	     is_infinite(c->vertex(1)) ||
	     is_infinite(c->vertex(2)) );
  }
  // we never get here
  CGAL_triangulation_precondition( false );
  return false;
}

template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
is_infinite(const Cell_handle c, int i, int j) const 
{ 
  CGAL_triangulation_precondition( ! (i == j) );
  switch ( dimension() ) {
  case 3:
    {
      CGAL_triangulation_precondition
	( ( i == 0 || i == 1 || i == 2 || i == 3 ) &&
	  ( j == 0 || j == 1 || j == 2 || j == 3 ) );
      break;
    }
  case 2:
    {
      CGAL_triangulation_precondition
	( ( i == 0 || i == 1 || i == 2 ) &&
	  ( j == 0 || j == 1 || j == 2 ) );
      break;
    }
  case 1:
    {
      CGAL_triangulation_precondition( ( i == 0 || i == 1 ) &&
				       ( j == 0 || j == 1 ) );
      break;
    }
  default:
    CGAL_triangulation_assertion( false );
    // return 
  }
  return ( is_infinite( c->vertex(i) ) ||
	   is_infinite( c->vertex(j) ) );
}

template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
is_vertex(const Point & p, Vertex_handle & v) const
{
  Locate_type lt;
  int li, lj;
  Cell_handle c = locate( p, lt, li, lj );
  if ( lt == VERTEX ) {
    v = c->vertex(li);
    return true;
  }
  return false;
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Cell_handle
Triangulation_3<GT,Tds>::
locate(const Point & p) const
{
  Locate_type lt;
  int li, lj;
  Cell_handle start;
  if ( dimension() >= 1 ) {
    // there is at least one finite "cell" (or facet or edge)
    start = infinite_vertex()->cell()->neighbor
      ( infinite_vertex()->cell()->index( infinite_vertex()) );
  }
  else {
    start = NULL;
  }
  return locate( p, start, lt, li, lj);
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Cell_handle
Triangulation_3<GT,Tds>::
locate(const Point & p,
       Locate_type & lt,
       int & li,
       int & lj) const
{
  Cell_handle start;
  if ( dimension() >= 1 ) {
    // there is at least one finite "cell" (or facet or edge)
    start = infinite_vertex()->cell()->neighbor
      ( infinite_vertex()->cell()->index( infinite_vertex()) );
  }
  else {
    start = NULL;
  }
  return locate( p, start, lt, li, lj);
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Cell_handle
Triangulation_3<GT,Tds>::
locate(const Point & p,
       Cell_handle start,
       Locate_type & lt,
       int & li,
       int & lj) const
  // returns the (finite or infinite) cell p lies in
  // starts at cell "start"
  // start must be non NULL and finite
  // if lt == OUTSIDE_CONVEX_HULL, li is the
  // index of a facet separating p from the rest of the triangulation
  // in dimension 2 :
  // returns a facet (Cell_handle,li) if lt == FACET
  // returns an edge (Cell_handle,li,lj) if lt == EDGE
  // returns a vertex (Cell_handle,li) if lt == VERTEX
  // if lt == OUTSIDE_CONVEX_HULL, li, lj give the edge of c
  // separating p from the rest of the triangulation
  // lt = OUTSIDE_AFFINE_HULL if p is not coplanar with the triangulation
{
  static Random rand( (long) 0 );
  int i, inf;
  Point p0,p1,p2,p3;
  switch (dimension()) {
  case 3:
    {
      CGAL_triangulation_precondition
	( (&(*start) != NULL) 
	  && ( ! start->has_vertex(infinite) ) );
      Cell_handle c = start;
      Orientation o[4];
      while (1) {
	  
	if ( c->has_vertex(infinite,li) ) {
	  // c must contain p in its interior
	  lt = OUTSIDE_CONVEX_HULL;
	  return c;
	}
	   
	// else c is finite
	// we test its facets in a random order until we find a
	// neighbor to go further
	i = rand.get_int(0,4);
	p0 = c->vertex( i )->point();
	p1 = c->vertex( (i+1)&3 )->point();
	p2 = c->vertex( (i+2)&3 )->point();
	p3 = c->vertex( (i+3)&3 )->point();
	if ( (i&1) == 0 ) {
	  o[0] = geom_traits().orientation( p, p1, p2, p3 );
	  if ( o[0] == NEGATIVE ) {
	    c = c->neighbor(i);
	    continue;
	  }
	  // (i+1)%2 == 1
	  o[1] = geom_traits().orientation( p2, p, p3, p0 );
	  if ( o[1] == NEGATIVE ) {
	    c = c->neighbor((i+1)&3);
	    continue;
	  }
	  // (i+2)%2 == 0
	  o[2] = geom_traits().orientation( p, p3, p0, p1 );
	  if ( o[2] == NEGATIVE ) {
	    c = c->neighbor((i+2)&3);
	    continue;
	  }
	  // (i+3)%2 == 1
	  o[3] = geom_traits().orientation( p0, p, p1, p2 );
	  if ( o[3] == NEGATIVE ) {
	    c = c->neighbor((i+3)&3);
	    continue;
	  }
	}
	else {// (i%2) == 1
	  o[0] = geom_traits().orientation( p1, p, p2, p3 );
	  if ( o[0] == NEGATIVE ) {
	    c = c->neighbor(i);
	    continue;
	  }
	  // (i+1)%2 == 0
	  o[1] = geom_traits().orientation( p, p2, p3, p0 );
	  if ( o[1] == NEGATIVE ) {
	    c = c->neighbor((i+1)&3);
	    continue;
	  }
	  // (i+2)%2 == 1
	  o[2] = geom_traits().orientation( p3, p, p0, p1 );
	  if ( o[2] == NEGATIVE ) {
	    c = c->neighbor((i+2)&3);
	    continue;
	  }
	  // (i+3)%2 == 0
	  o[3] = geom_traits().orientation( p, p0, p1, p2 );
	  if ( o[3] == NEGATIVE ) {
	    c = c->neighbor((i+3)&3);
	    continue;
	  }
	}
	  
	// now p is in c or on its boundary
	int sum = ( o[0] == COPLANAR )
	  + ( o[1] == COPLANAR )
	  + ( o[2] == COPLANAR )
	  + ( o[3] == COPLANAR );
	switch (sum) {
	case 0:
	  {
	    lt = CELL;
	    break;
	  }
	case 1:
	  { 
	    lt = FACET;
	    li = ( o[0] == COPLANAR ) ? i :
	      ( o[1] == COPLANAR ) ? (i+1)&3 :
	      ( o[2] == COPLANAR ) ? (i+2)&3 :
	      (i+3)&3;
	    break;
	  }
	case 2:
	  { 
	    lt = EDGE;
	    li = ( o[0] != COPLANAR ) ? i :
	      ( o[1] != COPLANAR ) ? ((i+1)&3) :
	      ((i+2)&3);
	    lj = ( o[ (li+1-i)&3 ] != COPLANAR ) ? ((li+1)&3) :
	      ( o[ (li+2-i)&3 ] != COPLANAR ) ? ((li+2)&3) :
	      ((li+3)&3);
	    CGAL_triangulation_assertion
	      ( geom_traits().collinear( p,
					 c->vertex( li )->point(),
					 c->vertex( lj )->point() ) );
	    break;
	  }
	case 3:
	  {
	    lt = VERTEX;
	    li = ( o[0] != COPLANAR ) ? i :
	      ( o[1] != COPLANAR ) ? (i+1)&3 :
	      ( o[2] != COPLANAR ) ? (i+2)&3 :
	      (i+3)&3;
	    break;
	  }
	}
	return c;
      }
      // to avoid warning
      return start;
    }
  case 2:
    {
      CGAL_triangulation_precondition
	( (&(*start) != NULL) 
	  && ( ! start->has_vertex(infinite) ) );
      //first tests whether p is coplanar with the current triangulation
      Facet_iterator finite_fit = finite_facets_begin();
      if ( geom_traits().orientation
	   ( p, 
	     (*finite_fit).first->vertex(0)->point(),
	     (*finite_fit).first->vertex(1)->point(),
	     (*finite_fit).first->vertex(2)->point() ) 
	   != DEGENERATE ) {
	lt = OUTSIDE_AFFINE_HULL;
	li = 3; // only one facet in dimension 2
	return (*finite_fit).first;
      }
      // if p is coplanar, location in the triangulation
      // only the facet numbered 3 exists in each cell
      Cell_handle c = start;
      Orientation o[3];
      while (1) {
	  
	if ( c->has_vertex(infinite,inf) ) {
	  // c must contain p in its interior
	  lt = OUTSIDE_CONVEX_HULL;
	  li = cw(inf);
	  lj = ccw(inf);
	  return c;
	}

	// else c is finite
	// we test its edges in a random order until we find a
	// neighbor to go further
	i = rand.get_int(0,3);
	p0 = c->vertex( i )->point();
	p1 = c->vertex( ccw(i) )->point();
	p2 = c->vertex( cw(i) )->point();
	o[0] = geom_traits().orientation_in_plane(p0,p1,p2,p);
	if ( o[0] == NEGATIVE ) {
	  c = c->neighbor( cw(i) );
	  continue;
	}
	o[1] = geom_traits().orientation_in_plane(p1,p2,p0,p);
	if ( o[1] == NEGATIVE ) {
	  c = c->neighbor( i );
	  continue;
	}
	o[2] = geom_traits().orientation_in_plane(p2,p0,p1,p);
	if ( o[2] == NEGATIVE ) {
	  c = c->neighbor( ccw(i) );
	  continue;
	}

	// now p is in c or on its boundary
	int sum = ( o[0] == COLLINEAR )
	  + ( o[1] == COLLINEAR )
	  + ( o[2] == COLLINEAR );
	switch (sum) {
	case 0:
	  {
	    lt = FACET;
	    li = 3; // useless ?
	    break;
	  }
	case 1:
	  {
	    lt = EDGE;
	    li = ( o[0] == COLLINEAR ) ? i :
	      ( o[1] == COLLINEAR ) ? ccw(i) :
	      cw(i);
	    lj = ccw(li);
	    break;
	  }
	case 2:
	  {
	    lt = VERTEX;
	    li = ( o[0] != COLLINEAR ) ? cw(i) :
	      ( o[1] != COLLINEAR ) ? i :
	      ccw(i);
	    break;
	  }
	}
	return c;
      }
      // to avoid warning
      return start;
    }
  case 1:
    {
      CGAL_triangulation_precondition
	( (&(*start) != NULL) 
	  && ( ! start->has_vertex(infinite) ) );
      //first tests whether p is collinear with the current triangulation
      Edge_iterator finite_eit = finite_edges_begin();
      if ( ! geom_traits().collinear(p,
				     (*finite_eit).first->vertex(0)->point(),
				     (*finite_eit).first->vertex(1)->point()) ) {
	lt = OUTSIDE_AFFINE_HULL;
	return (*finite_eit).first;
      }
      // if p is collinear, location :
      Cell_handle c = start;
      Comparison_result o, o0, o1;
      int xyz;
      p0 = start->vertex(0)->point();
      p1 = start->vertex(1)->point();
      CGAL_triangulation_assertion
	( ( geom_traits().compare_x(p0,p1) != EQUAL ) ||
	  ( geom_traits().compare_y(p0,p1) != EQUAL ) ||
	  ( geom_traits().compare_z(p0,p1) != EQUAL ) );
      o = geom_traits().compare_x(p0,p1);
      if ( o == EQUAL ) {
	o = geom_traits().compare_y(p0,p1);
	if ( o == EQUAL ) {
	  o = geom_traits().compare_z(p0,p1);
	  xyz = 3;
	}
	else {
	  xyz = 2;
	}
      }
      else {
	xyz  = 1;
      }
      //	bool notfound = true;
      while (1) {
	  
	if ( c->has_vertex(infinite,inf) ) {
	  // c must contain p in its interior
	  lt = OUTSIDE_CONVEX_HULL;
	  return c;
	}

	// else c is finite
	// we test on which direction to continue the traversal
	p0 = c->vertex(0)->point();
	p1 = c->vertex(1)->point();
	switch ( xyz ) {
	case 1:
	  {
	    o = geom_traits().compare_x(p0,p1);
	    o0 = geom_traits().compare_x(p0,p);
	    o1 = geom_traits().compare_x(p,p1);
	    break;
	  }
	case 2:
	  {
	    o = geom_traits().compare_y(p0,p1);
	    o0 = geom_traits().compare_y(p0,p);
	    o1 = geom_traits().compare_y(p,p1);
	    break;
	  }
	default: // case 3
	  {
	    o = geom_traits().compare_z(p0,p1);
	    o0 = geom_traits().compare_z(p0,p);
	    o1 = geom_traits().compare_z(p,p1);
	  }
	}
	// 	  o = geom_traits().compare_x(p0,p1);
	// 	  if ( o == EQUAL ) {
	// 	    o = geom_traits().compare_y(p0,p1);
	// 	    if ( o == EQUAL ) {
	// 	      o = geom_traits().compare_z(p0,p1);
	// 	      o0 = geom_traits().compare_z(p0,p);
	// 	      o1 = geom_traits().compare_z(p,p1);
	// 	    }
	// 	    else {
	// 	      o0 = geom_traits().compare_y(p0,p);
	// 	      o1 = geom_traits().compare_y(p,p1);
	// 	    }
	// 	  }
	// 	  else {
	// 	    o0 = geom_traits().compare_x(p0,p);
	// 	    o1 = geom_traits().compare_x(p,p1);
	// 	  }
	  
	if (o0 == EQUAL) {
	  lt = VERTEX;
	  li = 0;
	  return c;
	}
	if (o1 == EQUAL) {
	  lt = VERTEX;
	  li = 1;
	  return c;
	}
	if ( o0 == o1 ) {
	  lt = EDGE;
	  li = 0;
	  lj = 1;
	  return c;
	}
	if ( o0 == o ) { 
	  c = c->neighbor(0);
	  continue;
	}
	if ( o1 == o ) { 
	  c = c->neighbor(1);
	  continue; 
	}
      }
      // 	do {
      // 	  if ( side_of_edge( p, c, 0, 1, lt, li ) != ON_UNBOUNDED_SIDE ) {
      // 	    notfound = false;
      // 	  }
      // 	  else {
      // 	    if ( geom_traits().compare_x(p,c->vertex(1)->point()) 
      // 		 == LARGER ) {
      // 	      c = c->neighbor(0);
      // 	    }
      // 	    else {
      // 	      c = c->neighbor(1);
      // 	    }
      // 	  }
      // 	} while ( notfound );
      // 	if ( lt == EDGE ) {
      // 	  if ( c->has_vertex(infinite) ) {
      // 	    lt = OUTSIDE_CONVEX_HULL;
      // 	  }
      // 	  lj = 1-li;
      // 	} // else vertex, li is already the right index
	
      // to avoid warning
      return start;
    }
  case 0:
    {
      Vertex_iterator vit = finite_vertices_begin();
      if ( ! geom_traits().equal( p, vit->point() ) ) {
	lt = OUTSIDE_AFFINE_HULL;
      }
      else {
	lt = VERTEX;
	li = 0;
      }
      return vit->cell();
      break;
    }
  case -1:
    {
      lt = OUTSIDE_AFFINE_HULL;
      return NULL;
    }
  default:
    {
      CGAL_triangulation_assertion(false);
      return NULL;
    }
  }
  // to avoid warning
  CGAL_triangulation_assertion(false);
  return start;
}
	  
template < class GT, class Tds >
Bounded_side
Triangulation_3<GT,Tds>::
side_of_tetrahedron(const Point & p,
		    const Point & p0, 
		    const Point & p1,
		    const Point & p2, 
		    const Point & p3,
		    Locate_type & lt, int & i, int & j ) const
  // p0,p1,p2,p3 supposed to be non coplanar
  // tetrahedron p0,p1,p2,p3 is supposed to be well oriented
  // returns :
  // ON_BOUNDED_SIDE if p lies strictly inside the tetrahedron
  // ON_BOUNDARY if p lies on one of the facets
  // ON_UNBOUNDED_SIDE if p lies strictly outside the tetrahedron
{
  CGAL_triangulation_precondition
    ( geom_traits().orientation(p0,p1,p2,p3) == POSITIVE );
				      
  Orientation o0 = geom_traits().orientation(p,p1,p2,p3);
  Orientation o1 = geom_traits().orientation(p0,p,p2,p3);
  Orientation o2 = geom_traits().orientation(p0,p1,p,p3);
  Orientation o3 = geom_traits().orientation(p0,p1,p2,p);

  if ( (o0 == NEGATIVE) ||
       (o1 == NEGATIVE) ||
       (o2 == NEGATIVE) ||
       (o3 == NEGATIVE) ) {
    lt = OUTSIDE_CONVEX_HULL;
    return ON_UNBOUNDED_SIDE;
  }

  // now all the oi's are >=0
  // sum gives the number of facets p lies on
  int sum = 
    ( (o0 == ZERO) ? 1 : 0 ) + 
    ( (o1 == ZERO) ? 1 : 0 ) +
    ( (o2 == ZERO) ? 1 : 0 ) + 
    ( (o3 == ZERO) ? 1 : 0 );

  switch (sum) {
  case 0:
    {
      lt = CELL;
      return ON_BOUNDED_SIDE;
    }
  case 1:
    {
      lt = FACET;
      // i = index such that p lies on facet(i)
      i = ( o0 == ZERO ) ? 0 :
	( o1 == ZERO ) ? 1 :
	( o2 == ZERO ) ? 2 :
	3;
      return ON_BOUNDARY;
    }
  case 2:
    {
      lt = EDGE;
      // i = smallest index such that p does not lie on facet(i)
      // i must be < 3 since p lies on 2 facets
      i = ( o0 == POSITIVE ) ? 0 :
	( o1 == POSITIVE ) ? 1 :
	2;
      // j = larger index such that p not on facet(j)
      // j must be > 0 since p lies on 2 facets
      j = ( o3 == POSITIVE ) ? 3 :
	( o2 == POSITIVE ) ? 2 :
	1;
      return ON_BOUNDARY;
    }
  case 3:
    {
      lt = VERTEX;
      // i = index such that p does not lie on facet(i)
      i = ( o0 == POSITIVE ) ? 0 :
	( o1 == POSITIVE ) ? 1 :
	( o2 == POSITIVE ) ? 2 :
	3;
      return ON_BOUNDARY;
    }
  default:
    {
      // impossible : cannot be on 4 facets for a real tetrahedron
      CGAL_triangulation_assertion(false);
      return ON_BOUNDARY;
    }
  }
}

template < class GT, class Tds >
Bounded_side
Triangulation_3<GT,Tds>::
side_of_cell(const Point & p, 
	     Cell_handle c,
	     Locate_type & lt, int & i, int & j) const
  // returns
  // ON_BOUNDED_SIDE if p inside the cell
  // (for an infinite cell this means that p lies strictly in the half space
  // limited by its finite facet)
  // ON_BOUNDARY if p on the boundary of the cell
  // (for an infinite cell this means that p lies on the *finite* facet)
  // ON_UNBOUNDED_SIDE if p lies outside the cell
  // (for an infinite cell this means that p is not in the preceding
  // two cases)  
  // lt has a meaning only when ON_BOUNDED_SIDE or ON_BOUNDARY
{
  CGAL_triangulation_precondition( dimension() == 3 );
  if ( ! is_infinite(c) ) {
    return side_of_tetrahedron(p,
			       c->vertex(0)->point(),
			       c->vertex(1)->point(),
			       c->vertex(2)->point(),
			       c->vertex(3)->point(),
			       lt, i, j);
  }
  else {
    int inf = c->index(infinite);
    Orientation o;
    Vertex_handle 
      v1=c->vertex((inf+1)&3), 
      v2=c->vertex((inf+2)&3), 
      v3=c->vertex((inf+3)&3);
    if ( (inf&1) == 0 ) {
      o = geom_traits().orientation(p,
				    v1->point(),
				    v2->point(),
				    v3->point());
    }
    else {
      o =  geom_traits().orientation(v3->point(),
				     p,
				     v1->point(),
				     v2->point());
    }
    switch (o) {
    case POSITIVE:
      {
	lt = CELL;
	return ON_BOUNDED_SIDE;
      }
    case NEGATIVE:
      return ON_UNBOUNDED_SIDE;
    case ZERO:
      {
	// location in the finite facet
	int i_f, j_f;
	Bounded_side side = 
	  side_of_triangle(p,
			   v1->point(),
			   v2->point(),
			   v3->point(),
			   lt, i_f, j_f);
	// lt need not be modified in most cases :
	switch (side) {
	case ON_BOUNDED_SIDE:
	  {
	    // lt == FACET ok
	    i = inf;
	    return ON_BOUNDARY;
	  }
	case ON_BOUNDARY:
	  {
	    // lt == VERTEX OR EDGE ok
	    i = ( i_f == 0 ) ? ((inf+1)&3) :
	      ( i_f == 1 ) ? ((inf+2)&3) :
	      ((inf+3)&3);
	    if ( lt == EDGE ) {
	      j = (j_f == 0 ) ? ((inf+1)&3) :
		( j_f == 1 ) ? ((inf+2)&3) :
		((inf+3)&3);
	    }
	    return ON_BOUNDARY;
	  }
	case ON_UNBOUNDED_SIDE:
	  {
	    // p lies on the plane defined by the finite facet
	    // lt must be initialized
	    return ON_UNBOUNDED_SIDE;
	  }
	default:
	  {
	    CGAL_triangulation_assertion(false);
	    return ON_BOUNDARY;
	  }
	} // switch side
      }// case ZERO
    default:
      {
	CGAL_triangulation_assertion(false);
	return ON_BOUNDARY;
      }
    } // switch o
  } // else infinite cell
} // side_of_cell

template < class GT, class Tds >
Bounded_side
Triangulation_3<GT,Tds>::
side_of_triangle(const Point & p,
		 const Point & p0, 
		 const Point & p1,
		 const Point & p2,
		 Locate_type & lt, int & i, int & j ) const
  // p0,p1,p2 supposed to define a plane
  // p supposed to lie on plane p0,p1,p2
  // triangle p0,p1,p2 defines the orientation of the plane
  // returns
  // ON_BOUNDED_SIDE if p lies strictly inside the triangle
  // ON_BOUNDARY if p lies on one of the edges
  // ON_UNBOUNDED_SIDE if p lies strictly outside the triangle
{
  CGAL_triangulation_precondition
    ( ! geom_traits().collinear(p0,p1,p2) );
  CGAL_triangulation_precondition
    ( geom_traits().orientation(p,p0,p1,p2) == COPLANAR );

  // edge p0 p1 :
  Orientation o0 = geom_traits().orientation_in_plane(p0,p1,p2,p);
  // edge p1 p2 :
  Orientation o1 = geom_traits().orientation_in_plane(p1,p2,p0,p);
  // edge p2 p0 :
  Orientation o2 = geom_traits().orientation_in_plane(p2,p0,p1,p);

  if ( (o0 == NEGATIVE) ||
       (o1 == NEGATIVE) ||
       (o2 == NEGATIVE) ) {
    lt = OUTSIDE_CONVEX_HULL;
    return ON_UNBOUNDED_SIDE;
  }

  // now all the oi's are >=0
  // sum gives the number of edges p lies on
  int sum = 
    ( (o0 == ZERO) ? 1 : 0 ) + 
    ( (o1 == ZERO) ? 1 : 0 ) +
    ( (o2 == ZERO) ? 1 : 0 );

  switch (sum) {
  case 0:
    {
      lt = FACET;
      return ON_BOUNDED_SIDE;
    }
  case 1:
    {
      lt = EDGE;
      i = ( o0 == ZERO ) ? 0 :
	( o1 == ZERO ) ? 1 :
	2;
      if ( i == 2 ) { j=0; }
      else { j = i+1; }
      return ON_BOUNDARY;
    }
  case 2:
    {
      lt = VERTEX;
      i = ( o0 == POSITIVE ) ? 2 :
	( o1 == POSITIVE ) ? 0 :
	1;
      return ON_BOUNDARY;
    }
  default:
    {
      // cannot happen
      CGAL_triangulation_assertion(false);
      return ON_BOUNDARY;
    }
  }
}

template < class GT, class Tds >
Bounded_side
Triangulation_3<GT,Tds>::
side_of_facet(const Point & p,
	      Cell_handle c,
	      Locate_type & lt, int & li, int & lj) const
  // supposes dimension 2 otherwise does not work for infinite facets
  // returns :
  // ON_BOUNDED_SIDE if p inside the facet
  // (for an infinite facet this means that p lies strictly in the half plane
  // limited by its finite edge)
  // ON_BOUNDARY if p on the boundary of the facet
  // (for an infinite facet this means that p lies on the *finite* edge)
  // ON_UNBOUNDED_SIDE if p lies outside the facet
  // (for an infinite facet this means that p is not in the
  // preceding two cases) 
  // lt has a meaning only when ON_BOUNDED_SIDE or ON_BOUNDARY
  // when they mean anything, li and lj refer to indices in the cell c 
  // giving the facet (c,i)
{//side_of_facet
  CGAL_triangulation_precondition( dimension() == 2 );
  //      CGAL_triangulation_precondition( i == 3 );
  //      if ( ! is_infinite(c,i) ) {
  if ( ! is_infinite(c,3) ) {
    // The following precondition is useless because it is written
    // in side_of_facet  
    // 	CGAL_triangulation_precondition( geom_traits().orientation
    // 					 (p, 
    // 					  c->vertex(0)->point,
    // 					  c->vertex(1)->point,
    // 					  c->vertex(2)->point)
    // 					 == COPLANAR );
    //	int i0, i1, i2; // indices in the considered facet
    Bounded_side side;
    int i_t, j_t;
    side = side_of_triangle(p,
			    c->vertex(0)->point(),
			    c->vertex(1)->point(),
			    c->vertex(2)->point(),
			    lt, i_t, j_t);
    // indices in the original cell :
    li = ( i_t == 0 ) ? 0 :
      ( i_t == 1 ) ? 1 :
      2;
    lj = ( j_t == 0 ) ? 0 :
      ( j_t == 1 ) ? 1 :
      2;
    return side;
  }
  // else infinite facet
  int inf = c->index(infinite);
    // The following precondition is useless because it is written
    // in side_of_facet  
    // 	CGAL_triangulation_precondition( geom_traits().orientation
    // 					 (p,
    // 					  c->neighbor(inf)->vertex(0)->point(),
    // 					  c->neighbor(inf)->vertex(1)->point(),
    // 					  c->neighbor(inf)->vertex(2)->point())
    // 					 == COPLANAR );
  int i1,i2; // indices in the facet
//     if ( 3 == ((inf+1)&3) ) {
//       i1 = (inf+2)&3;
//       i2 = (inf+3)&3;
//     }
//     else {
//       if ( 3 == ((inf+2)&3) ) {
// 	i1 = (inf+3)&3;
// 	i2 = (inf+1)&3;
//       }
//       else {
// 	i1 = (inf+1)&3;
// 	i2 = (inf+2)&3;
//       }
//     }
  // replaced using next_around_edgeij
  i2 = next_around_edge(inf,3);
  i1 = 3-inf-i2;
  Vertex_handle 
    v1 = c->vertex(i1),
    v2 = c->vertex(i2);
	
  // does not work in dimension 3
  Cell_handle n = c->neighbor(inf);
  // n must be a finite cell
  Orientation o =
    geom_traits().orientation_in_plane
    ( v1->point(), 
      v2->point(), 
      n->vertex(n->index(c))->point(),
      p );
  switch (o) {
  case POSITIVE:
    // p lies on the same side of v1v2 as vn, so not in f
    {
      return ON_UNBOUNDED_SIDE;
    }
  case NEGATIVE:
    // p lies in f
    { 
      lt = FACET;
      li = 3;
      return ON_BOUNDED_SIDE;
    }
  case ZERO:
    // p collinear with v1v2
    {
      int i_e;
      Bounded_side side = 
	side_of_segment( p,
			 v1->point(), v2->point(),
			 lt, i_e );
      switch (side) {
	// computation of the indices inthe original cell
      case ON_BOUNDED_SIDE:
	{
	  // lt == EDGE ok
	  li = i1;
	  lj = i2;
	  return ON_BOUNDARY;
	}
      case ON_BOUNDARY:
	{
	  // lt == VERTEX ok
	  li = ( i_e == 0 ) ? i1 : i2;
	  return ON_BOUNDARY;
	}
      case ON_UNBOUNDED_SIDE:
	{
	  // p lies on the line defined by the finite edge
	  return ON_UNBOUNDED_SIDE;
	}
      default:
	{
	  // cannot happen. only to avoid warning with eg++
	  return ON_UNBOUNDED_SIDE;
	}
      } 
    }// case ZERO
  }// switch o
  // end infinite facet
  // cannot happen. only to avoid warning with eg++
  CGAL_triangulation_assertion(false);
  return ON_UNBOUNDED_SIDE;
}

template < class GT, class Tds >
Bounded_side
Triangulation_3<GT,Tds>::
side_of_segment(const Point & p,
		const Point & p0, 
		const Point & p1,
		Locate_type & lt, int & i ) const
  // p0, p1 supposed to be different
  // p supposed to be collinear to p0, p1
  // returns :
  // ON_BOUNDED_SIDE if p lies strictly inside the edge
  // ON_BOUNDARY if p equals p0 or p1
  // ON_UNBOUNDED_SIDE if p lies strictly outside the edge
{
  CGAL_triangulation_precondition
    ( ! geom_traits().equal(p0,p1) );
  CGAL_triangulation_precondition
    ( geom_traits().collinear(p,p0,p1) );
      
  Comparison_result c = geom_traits().compare_x(p0,p1);
  Comparison_result c0;
  Comparison_result c1;

  if ( c == EQUAL ) {
    c = geom_traits().compare_y(p0,p1);
    if ( c == EQUAL ) {
      c = geom_traits().compare_z(p0,p1);
      c0 = geom_traits().compare_z(p0,p);
      c1 = geom_traits().compare_z(p,p1);
    }
    else {
      c0 = geom_traits().compare_y(p0,p);
      c1 = geom_traits().compare_y(p,p1);
    }
  }
  else {
    c0 = geom_traits().compare_x(p0,p);
    c1 = geom_traits().compare_x(p,p1);
  }
      
  //      if ( (c0 == SMALLER) && (c1 == SMALLER) ) {
  if ( c0 == c1 ) {
    lt = EDGE;
    return ON_BOUNDED_SIDE;
  }
  if (c0 == EQUAL) {
    lt = VERTEX;
    i = 0;
    return ON_BOUNDARY;
  }
  if (c1 == EQUAL) {
    lt = VERTEX;
    i = 1;
    return ON_BOUNDARY;
  }
  lt = OUTSIDE_CONVEX_HULL;
  return ON_UNBOUNDED_SIDE;
}

template < class GT, class Tds >
Bounded_side
Triangulation_3<GT,Tds>::
side_of_edge(const Point & p,
	     Cell_handle c,
	     Locate_type & lt, int & li) const
  // supposes dimension 1 otherwise does not work for infinite edges
  // returns :
  // ON_BOUNDED_SIDE if p inside the edge 
  // (for an infinite edge this means that p lies in the half line
  // defined by the vertex)
  // ON_BOUNDARY if p equals one of the vertices
  // ON_UNBOUNDED_SIDE if p lies outside the edge
  // (for an infinite edge this means that p lies on the other half line)
  // lt has a meaning when ON_BOUNDED_SIDE and ON_BOUNDARY  
  // li refer to indices in the cell c 
{//side_of_edge
  CGAL_triangulation_precondition( dimension() == 1 );
  if ( ! is_infinite(c,0,1) ) 
    return side_of_segment(p,
			   c->vertex(0)->point(),
			   c->vertex(1)->point(),
			   lt, li);
  // else infinite edge
  int inf = c->index(infinite);
  if ( geom_traits().equal( p, c->vertex(1-inf)->point() ) ) {
    lt = VERTEX;
    li = 1-inf;
    return ON_BOUNDARY;
  }
  // does not work in dimension > 2
  Cell_handle n = c->neighbor(inf);
  int i_e = n->index(c);
  // we know that n is finite
  Vertex_handle
    v0 = n->vertex(0),
    v1 = n->vertex(1);
  Comparison_result c01 = 
    geom_traits().compare_x(v0->point(), v1->point());
  Comparison_result cp;
  if ( c01 == EQUAL ) {
    c01 = geom_traits().compare_y(v0->point(),v1->point());
    if ( i_e == 0 ) {
      cp = geom_traits().compare_y( v1->point(), p );
    }
    else {
      cp = geom_traits().compare_y( p, v0->point() );
    }
  }
  else {
    if ( i_e == 0 ) {
      cp = geom_traits().compare_x( v1->point(), p );
    }
    else {
      cp = geom_traits().compare_x( p, v0->point() );
    }
  }
  if ( c01 == cp ) {
    // p lies on the same side of n as infinite
    lt = EDGE;
    return ON_BOUNDED_SIDE;
  }
  return ON_UNBOUNDED_SIDE;
}

template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
flip( Facet f )
{
  return flip( f.first, f.second);
}
template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
flip( Cell_handle c, int i )
{
  CGAL_triangulation_precondition( (dimension() == 3) && (0<=i) && (i<4) 
				   && (number_of_vertices() > 5) );

  Cell_handle n = c->neighbor(i);
  int in = n->index(c);
  if ( is_infinite( c ) || is_infinite( n ) ) return false;
  
  if ( i%2 == 1 ) {
    if ( geom_traits().orientation( c->vertex((i+1)&3)->point(),
				    c->vertex((i+2)&3)->point(),
				    n->vertex(in)->point(),
				    c->vertex(i)->point() )
	 != LEFTTURN ) return false;
    if ( geom_traits().orientation( c->vertex((i+2)&3)->point(),
				    c->vertex((i+3)&3)->point(),
				    n->vertex(in)->point(),
				    c->vertex(i)->point() )
	 != LEFTTURN ) return false;
    if ( geom_traits().orientation( c->vertex((i+3)&3)->point(),
				    c->vertex((i+1)&3)->point(),
				    n->vertex(in)->point(),
				    c->vertex(i)->point() )
	 != LEFTTURN ) return false;
  }
  else {
    if ( geom_traits().orientation( c->vertex((i+2)&3)->point(),
				    c->vertex((i+1)&3)->point(),
				    n->vertex(in)->point(),
				    c->vertex(i)->point() )
	 != LEFTTURN ) return false;
    if ( geom_traits().orientation( c->vertex((i+3)&3)->point(),
				    c->vertex((i+2)&3)->point(),
				    n->vertex(in)->point(),
				    c->vertex(i)->point() )
	 != LEFTTURN ) return false;
    if ( geom_traits().orientation( c->vertex((i+1)&3)->point(),
				    c->vertex((i+3)&3)->point(),
				    n->vertex(in)->point(),
				    c->vertex(i)->point() )
	 != LEFTTURN ) return false;
  }

  _tds.flip_flippable( &(*c), i);
  return true;
}

template < class GT, class Tds >
void
Triangulation_3<GT,Tds>::
flip_flippable( Facet f )
{
  return flip_flippable( f.first, f.second);
}
template < class GT, class Tds >
void
Triangulation_3<GT,Tds>::
flip_flippable( Cell_handle c, int i )
{
  CGAL_triangulation_precondition( (dimension() == 3) && (0<=i) && (i<4) 
				   && (number_of_vertices() > 5) );
  CGAL_triangulation_precondition_code( Cell_handle n = c->neighbor(i); );
  CGAL_triangulation_precondition_code( int in = n->index(c); );
  CGAL_triangulation_precondition( ( ! is_infinite( c ) ) && 
				   ( ! is_infinite( n ) ) );
  
  if ( i%2 == 1 ) {
    CGAL_triangulation_precondition
      ( geom_traits().orientation( c->vertex((i+1)&3)->point(),
				   c->vertex((i+2)&3)->point(),
				   n->vertex(in)->point(),
				   c->vertex(i)->point() )
	== LEFTTURN );
    CGAL_triangulation_precondition
      ( geom_traits().orientation( c->vertex((i+2)&3)->point(),
				   c->vertex((i+3)&3)->point(),
				   n->vertex(in)->point(),
				   c->vertex(i)->point() )
	== LEFTTURN );
    CGAL_triangulation_precondition
      ( geom_traits().orientation( c->vertex((i+3)&3)->point(),
				   c->vertex((i+1)&3)->point(),
				   n->vertex(in)->point(),
				   c->vertex(i)->point() )
	== LEFTTURN );
  }
  else {
    CGAL_triangulation_precondition
      ( geom_traits().orientation( c->vertex((i+2)&3)->point(),
				   c->vertex((i+1)&3)->point(),
				   n->vertex(in)->point(),
				   c->vertex(i)->point() )
	== LEFTTURN );
    CGAL_triangulation_precondition
      ( geom_traits().orientation( c->vertex((i+3)&3)->point(),
				   c->vertex((i+2)&3)->point(),
				   n->vertex(in)->point(),
				   c->vertex(i)->point() )
	== LEFTTURN );
    CGAL_triangulation_precondition
      ( geom_traits().orientation( c->vertex((i+1)&3)->point(),
				   c->vertex((i+3)&3)->point(),
				   n->vertex(in)->point(),
				   c->vertex(i)->point() )
	== LEFTTURN );
  }
  
  _tds.flip_flippable( &(*c), i);
}

template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
flip( Edge e )
{
  return flip( e.first, e.second, e.third );
}
template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
flip( Cell_handle c, int i, int j )
  // flips edge i,j of cell c
{
  CGAL_triangulation_precondition( (dimension() == 3) 
				   && (0<=i) && (i<4) 
				   && (0<=j) && (j<4)
				   && ( i != j )
				   && (number_of_vertices() > 5) );

  // checks that degree 3 and not on the convex hull
  int degree = 0;
  Cell_circulator ccir = incident_cells(c,i,j);
  Cell_circulator cdone = ccir;
  do {
    if ( is_infinite(&(*ccir)) ) return false;
    ++degree;
    ++ccir;
  } while ( ccir != cdone );

  if ( degree != 3 ) return false;

  // checks that future tetrahedra are well oriented
  Cell_handle n = c->neighbor( next_around_edge(i,j) );
  int in = n->index( c->vertex(i) );
  int jn = n->index( c->vertex(j) );
  if ( geom_traits().orientation( c->vertex(next_around_edge(i,j))->point(),
				  c->vertex(next_around_edge(j,i))->point(),
				  n->vertex(next_around_edge(jn,in))->point(),
				  c->vertex(j)->point() )
       != LEFTTURN ) return false;
  if ( geom_traits().orientation( c->vertex(i)->point(),
				  c->vertex(next_around_edge(j,i))->point(),
				  n->vertex(next_around_edge(jn,in))->point(),
				  c->vertex(next_around_edge(i,j))->point() )
       != LEFTTURN ) return false;

  _tds.flip_flippable( &(*c), i, j );
  return true;
}

template < class GT, class Tds >
void
Triangulation_3<GT,Tds>::
flip_flippable( Edge e )
{
  return flip_flippable( e.first, e.second, e.third );
}
template < class GT, class Tds >
void
Triangulation_3<GT,Tds>::
flip_flippable( Cell_handle c, int i, int j )
  // flips edge i,j of cell c
{
  CGAL_triangulation_precondition( (dimension() == 3) 
				   && (0<=i) && (i<4) 
				   && (0<=j) && (j<4)
				   && ( i != j )
				   && (number_of_vertices() > 5) );
  CGAL_triangulation_precondition_code
    ( int degree = 0; );
  CGAL_triangulation_precondition_code
    ( Cell_circulator ccir = incident_cells(c,i,j); );
  CGAL_triangulation_precondition_code
    ( Cell_circulator cdone = ccir; );
  CGAL_triangulation_precondition_code
    ( do {
      CGAL_triangulation_precondition( ! is_infinite(&(*ccir)) );
      ++degree;
      ++ccir;
    } while ( ccir != cdone ););
  CGAL_triangulation_precondition( degree==3 );

  CGAL_triangulation_precondition_code
    ( Cell_handle n = c->neighbor( next_around_edge(i,j) ); );
  CGAL_triangulation_precondition_code
    ( int in = n->index( c->vertex(i) ); );
  CGAL_triangulation_precondition_code
    ( int jn = n->index( c->vertex(j) ); );
  CGAL_triangulation_precondition
    ( geom_traits().orientation( c->vertex(next_around_edge(i,j))->point(),
				 c->vertex(next_around_edge(j,i))->point(),
				 n->vertex(next_around_edge(jn,in))->point(),
				 c->vertex(j)->point() )
       == LEFTTURN );
  CGAL_triangulation_precondition
    ( geom_traits().orientation( c->vertex(i)->point(),
				 c->vertex(next_around_edge(j,i))->point(),
				 n->vertex(next_around_edge(jn,in))->point(),
				 c->vertex(next_around_edge(i,j))->point() )
       == LEFTTURN );

  _tds.flip_flippable( &(*c), i, j );
}


template < class GT, class Tds >
Triangulation_3<GT,Tds>::Vertex_handle
Triangulation_3<GT,Tds>::
insert(const Point & p )
{
  Locate_type lt;
  int li, lj;
  Cell_handle c;
  Cell_handle start;
  if ( dimension() >= 1 ) {
    // there is at least one finite "cell" (or facet or edge)
    start = infinite_vertex()->cell()
      ->neighbor( infinite_vertex()->cell()->index( infinite_vertex()) );
  }
  else {
    start = NULL;
  }
  c = locate( p, start, lt, li, lj);
  switch (lt) {
  case VERTEX:
    return c->vertex(li);
  case EDGE:
    return insert_in_edge(p, c, li, lj);
  case FACET:
    return insert_in_facet(p, c, li);
  case CELL:
    return insert_in_cell(p, c);
  case OUTSIDE_CONVEX_HULL:
    return insert_outside_convex_hull(p, c);
  case OUTSIDE_AFFINE_HULL:
    return insert_outside_affine_hull(p);
  }
  // cannot happen, only to avoid warning with eg++
  return insert_in_edge(p, c, li, lj);
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Vertex_handle
Triangulation_3<GT,Tds>::
insert(const Point & p, Cell_handle start)
{
  Locate_type lt;
  int li, lj;
  Cell_handle c;
  c = locate( p, start, lt, li, lj);
  switch (lt) {
  case VERTEX:
    return c->vertex(li);
  case EDGE:
    return insert_in_edge(p, c, li, lj);
  case FACET:
    return insert_in_facet(p, c, li);
  case CELL:
    return insert_in_cell(p, c);
  case OUTSIDE_CONVEX_HULL:
    return insert_outside_convex_hull(p, c);
  case OUTSIDE_AFFINE_HULL:
    return insert_outside_affine_hull(p);
  }
  // cannot happen, only to avoid warning with eg++
  return insert_in_edge(p, c, li, lj);
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Vertex_handle
Triangulation_3<GT,Tds>::
insert_in_cell(const Point & p, Cell_handle c)
{
  CGAL_triangulation_precondition( dimension() == 3 );
  CGAL_triangulation_precondition_code
    ( Locate_type lt;
      int i; int j; );
  CGAL_triangulation_precondition
    ( side_of_tetrahedron( p, 
			   c->vertex(0)->point(),
			   c->vertex(1)->point(),
			   c->vertex(2)->point(),
			   c->vertex(3)->point(),
			   lt,i,j ) == ON_BOUNDED_SIDE );

    return (Vertex*)_tds.insert_in_cell( Vertex(p), &(*c) );
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Vertex_handle
Triangulation_3<GT,Tds>::
insert_in_facet(const Point & p, Cell_handle c, int i)
{
  switch ( dimension() ) {
  case 3:
    {
      CGAL_triangulation_precondition
	( i == 0 || i == 1 || i == 2 || i == 3 );
      break;
    }
  case 2:
    {
      CGAL_triangulation_precondition( i == 3 );
      break;
    }
  default:
    CGAL_triangulation_assertion( false );
    // return ?
  }
  CGAL_triangulation_precondition_code
    ( Locate_type lt;
      int li; int lj; );
  CGAL_triangulation_precondition
    ( (geom_traits().orientation( p, 
				  c->vertex((i+1)&3)->point(),
				  c->vertex((i+2)&3)->point(),
				  c->vertex((i+3)&3)->point() ) == COPLANAR)
      && 
      (side_of_triangle(p, 
			c->vertex((i+1)&3)->point(),
			c->vertex((i+2)&3)->point(),
			c->vertex((i+3)&3)->point(),
			lt,li,lj) == ON_BOUNDED_SIDE) );

    return (Vertex*) _tds.insert_in_facet( Vertex(p), &(*c), i);
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Vertex_handle
Triangulation_3<GT,Tds>::
insert_in_edge(const Point & p, Cell_handle c, int i, int j)
{
  CGAL_triangulation_precondition( i != j );
  switch ( dimension() ) {
  case 3:
    {
      CGAL_triangulation_precondition
	( ( i == 0 || i == 1 || i == 2 || i == 3 ) &&
	  ( j == 0 || j == 1 || j == 2 || j == 3 ) );
      CGAL_triangulation_precondition( ! is_infinite(c,i,j) );
      CGAL_triangulation_precondition_code
	( Locate_type lt;
	  int li; );
      CGAL_triangulation_precondition
	( geom_traits().collinear( c->vertex(i)->point(),
				   p,
				   c->vertex(j)->point() )
	  &&
	  ( side_of_segment( p,
			     c->vertex(i)->point(),
			     c->vertex(j)->point(),
			     lt,li ) == ON_BOUNDED_SIDE ) );
      break;
    }
  case 2:
    {
      CGAL_triangulation_precondition
	( ( i == 0 || i == 1 || i == 2 ) &&
	  ( j == 0 || j == 1 || j == 2 ) );
      CGAL_triangulation_precondition( ! is_infinite(c,i,j) );
      CGAL_triangulation_precondition_code
	( Locate_type lt;
	  int li; )
	CGAL_triangulation_precondition
	  ( geom_traits().collinear( c->vertex(i)->point(),
				     p,
				     c->vertex(j)->point() )
	    &&
	    ( side_of_segment( p,
			       c->vertex(i)->point(),
			       c->vertex(j)->point(),
			       lt,li ) == ON_BOUNDED_SIDE )
	    );
   	break;
    }
  case 1:
    {
      CGAL_triangulation_precondition( ( i == 0 || i == 1 ) &&
				       ( j == 0 || j == 1 ) );
      CGAL_triangulation_precondition_code
	( int li;
	  Locate_type lt; );
      CGAL_triangulation_precondition( side_of_edge(p,c,lt,li)
				       == ON_BOUNDED_SIDE );
      break;
    }
  default:
    CGAL_triangulation_assertion( false );
    // return 
  }

  return (Vertex*) _tds.insert_in_edge( Vertex(p), &(*c), i, j);
}
  
template < class GT, class Tds >
Triangulation_3<GT,Tds>::Vertex_handle
Triangulation_3<GT,Tds>::
insert_outside_convex_hull(const Point & p, Cell_handle c)
  //			     int li, int lj=0)
  // c is an infinite cell containing p
  // whose facet li lies on the convex hull boundary
  // and separates p from the triangulation (in dimension 3)
  // p is strictly outside the convex hull
  // in dimension 2, edge li,lj separates p from the triangulation
  // in dimension 1, vertex li separates p from the triangulation
  // dimension 0 not allowed, use outside-affine-hull
{
  //    CGAL_triangulation_precondition( !
  //    c->has_vertex(infinite_vertex()) ); 
  // not a precondition any more in this version
  CGAL_triangulation_precondition( dimension() > 0 );
  CGAL_triangulation_precondition( c->has_vertex(infinite) );
  // the precondition that p is in c is tested in each of the
  // insertion methods called from this method 
  switch ( dimension() ) {
  case 1:
    {
      // 	// p lies in the infinite edge neighboring c 
      // 	// on the other side of li
      // 	return insert_in_edge(p,c->neighbor(1-li),0,1);
      return insert_in_edge(p,c,0,1);
    }
  case 2:
    {
      // 	Cell_handle n = c->neighbor(3-li-lj);
      // 	// n contains p and is infinite

      Vertex_handle v = new Vertex(p);
      set_number_of_vertices(number_of_vertices()+1);

      Locate_type loc;
      int i, j;

      // traversal in the first one of the two directions
      // of the infinite cells containing p
      // updating of the triangulation at the same time
      // by replacing the infinite vertex by v
      // 	Cell_handle cur = n;
      // 	Cell_handle prev = n->neighbor( ccw(n->index(infinite)) );
      Cell_handle cur = c;
      Cell_handle prev = c->neighbor( ccw(c->index(infinite)) );

      while ( side_of_facet( p, cur, loc, i, j ) 
	      // in dimension 2, cur has only one facet numbered 3
	      == ON_BOUNDED_SIDE ) {
	// loc must be == CELL since p supposed to be
	// strictly outside the convex hull
	cur->set_vertex( cur->index(infinite), v );
	prev = cur;
	cur = cur->neighbor( cw(cur->index(v)) ) ;
      }
	
      // creation of an infinite facet "at the end" of the sequence
      // of infinite facets containing p
      Cell_handle cnew 
	= create_cell( &(*( prev->vertex(ccw(prev->index(v))) )), 
		       &(*v),  
		       &(*infinite_vertex()), NULL,
		       NULL, &(*cur), &(*prev), NULL);
      // neighbor 0 will be set to dnew later
      prev->set_neighbor(prev->index(cur), cnew);
      cur->set_neighbor(cur->index(prev),cnew);

      // traversal in the opposite direction, and same operations
      // starts from the neighbor of n (n already modified)
      // 	prev = n;
      // 	cur = n->neighbor( ccw(n->index(v)) );
      prev = c;
      cur = c->neighbor( ccw(c->index(v)) );

      while ( side_of_facet( p, cur, loc, i, j ) 
	      == ON_BOUNDED_SIDE ) {
	cur->set_vertex( cur->index(infinite), v );
	prev = cur;
	cur = cur->neighbor( ccw(cur->index(v)) ) ;
      }
	
      Cell_handle dnew 
	= create_cell( &(*v), &(*(prev->vertex(cw(prev->index(v))) )), 
		       &(*infinite_vertex()), NULL,
		       &(*cur), &(*cnew), &(*prev), NULL);
      prev->set_neighbor(prev->index(cur), dnew);
      cur->set_neighbor(cur->index(prev),dnew);
      cnew->set_neighbor(0,dnew); // correction for cnew

      infinite->set_cell(dnew);			     
      // 	v->set_cell( n );
      v->set_cell( c );
      return v;
    }
  case 3:
    {
      // 	Cell_handle n = c->neighbor(li);
      // 	// n is an infinite cell containing p

      Vertex_handle v = new Vertex(p);
      // 	v->set_cell( n );
      v->set_cell( c );

      set_number_of_vertices(number_of_vertices()+1);

      // 	link( v, hat(v,n) );
      link( v, hat(v,c) );
      // infinite->set_cell is done by link

      return v;
    }
  }
  // to avoid warning with eg++
  return NULL;
}

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Cell_handle
Triangulation_3<GT,Tds>::
hat(Vertex_handle v, Cell_handle c)
  // recursive traversal of the set of facets of the convex hull
  // that are visible from v
  // v replaces infinite_vertex in these cells
  // on the boundary, new cells with vertices v, infinite_vertex
  // and the two vertices of an edge of the boumdary are created
  // returns a cell inside the "hat", having a facet on its boundary
{
  static Cell_handle bound;

  int inf = c->index(infinite_vertex());
  c->set_vertex( inf , v );

  Cell_handle cni, cnew;
  Locate_type loc;
  int li,lj;

  int i, i1, i2;
  for ( i=0; i<4; i++ ) {
    if ( i!= inf ) {
      cni = c->neighbor(i);
      if ( ! cni->has_vertex( v ) ) {
	if ( side_of_cell( v->point(), cni, loc, li, lj )
	     == ON_BOUNDED_SIDE ) {
	  hat( v, cni );
	}
	else { // we are on the boundary of the set of facets of the
	  // convex hull that are visible from v
	  i1 = next_around_edge(i,inf);
	  i2 = 6-i-i1-inf;
	  cnew = create_cell( &(*(c->vertex(i1))), &(*(c->vertex(i2))), 
			      &(*v), &(*infinite_vertex()),
			      NULL, NULL, &(*cni), &(*c) );
	  c->set_neighbor(i,cnew);
	  cni->set_neighbor( cni->index(c), cnew );

	  bound = c;
	}
      }
    }// no else
  } // for
  return bound;
} // hat

template < class GT, class Tds >
void
Triangulation_3<GT,Tds>::
link(Vertex_handle v, Cell_handle c)
  // c belongs to the hat of v and has a facet on its boundary
  // traverses the boundary of the hat and finds adjacencies
  // traversal is done counterclockwise as seen from v
{
  // finds a facet ib of c on the boundary of the hat
  int iv = c->index(v);
  int ib;
  for ( ib=0; ib<4; ib++ ) {
    if ( ( ib != iv ) && c->neighbor(ib)->has_vertex(infinite) ) {
      break;
    }
  }
  
  infinite->set_cell(c->neighbor(ib));

  Cell_handle bound = c;
  int i = ib;
  int next;
  Vertex_handle v1;

  do {
    iv = bound->index(v);
    // indices of the vertices != v of bound on the boundary of the hat
    // such that (i,i1,i2,iv) positive
    int i1 = next_around_edge(i,iv);
    int i2 = 6-i-i1-iv;

    // looking for the neighbor i2 of bound :
    // we turn around i1 until we reach the boundary of the hat
    v1 = bound->vertex(i1);

    Cell_handle cur = bound;

    next = next_around_edge(i1,iv);
    while ( ! cur->neighbor(next)->has_vertex(infinite) ) {
      cur = cur->neighbor(next);
      next = next_around_edge(cur->index(v1),cur->index(v));
    }
    Cell_handle current = bound->neighbor(i);
    Cell_handle found = cur->neighbor(next);
    current->set_neighbor( current->index(bound->vertex(i2)), found);
    found->set_neighbor( 6 - found->index(v) - 
			 found->index(infinite) -
			 found->index(v1), current );
    bound = cur;
    i = next;
  } while ( ( bound != c ) || ( i != ib ) );
  // c may have two facets on the boundary of the hat
  // test bound != c is not enough, we must test whether
  // facet ib of c has been treated
}// end link

template < class GT, class Tds >
Triangulation_3<GT,Tds>::Vertex_handle
Triangulation_3<GT,Tds>::
insert_outside_affine_hull(const Point & p)
{
  CGAL_triangulation_precondition( dimension() < 3 );
  bool reorient;
  switch ( dimension() ) {
  case 1:
    {
      CGAL_triangulation_precondition_code
	( Cell_handle c = infinite_cell();
	  Cell_handle n = c->neighbor(c->index(infinite_vertex())); )
	CGAL_triangulation_precondition
	  ( ! geom_traits().collinear(p,
				      n->vertex(0)->point(),
				      n->vertex(1)->point()) );
	// no reorientation : the first non-collinear point determines
	// the orientation of the plane
	reorient = false;
	break;
    }
  case 2:
    {
      Cell_handle c = infinite_cell();
      Cell_handle n = c->neighbor(c->index(infinite_vertex()));
      CGAL_triangulation_precondition
	( geom_traits().orientation(n->vertex(0)->point(),
				    n->vertex(1)->point(),
				    n->vertex(2)->point(),
				    p) != COPLANAR );
      reorient = ( geom_traits().orientation( n->vertex(0)->point(),
					      n->vertex(1)->point(),
					      n->vertex(2)->point(),
					      p ) == NEGATIVE );
      break;
    }
  default:
    reorient = false;
    break;
  }

  return( (Vertex*) _tds.insert_increase_dimension( Vertex(p), 
						    &(*infinite_vertex()), 
						    reorient));
}

template < class GT, class Tds >
void
Triangulation_3<GT,Tds>::
incident_cells(Vertex_handle v, 
	       std::set<Cell*, std::less<Cell*> > & cells,
	       Cell_handle c ) const
{
  CGAL_triangulation_precondition( &(*v) != NULL );
  CGAL_triangulation_precondition( _tds.is_vertex(&(*v)) );

  if ( dimension() < 3 ) { return; }

  if ( &(*c) == NULL ) {
    c = v->cell();
  }
  else {
    CGAL_triangulation_precondition( c->has_vertex(v) );
  }
  if ( cells.find( &(*c) ) != cells.end() ) {
    return; // c was already found
  }
  cells.insert( &(*c) );
      
  for ( int j=0; j<4; j++ ) {
    if ( j != c->index(v) ) {
      incident_cells( v, cells, c->neighbor(j) );
    }
  }
}

template < class GT, class Tds >
void
Triangulation_3<GT,Tds>::
incident_vertices(Vertex_handle v, 
		  std::set<Vertex*, std::less<Vertex*> > & vertices,
		  Cell_handle c ) const
{
  CGAL_triangulation_precondition( &(*v) != NULL );
  CGAL_triangulation_precondition( _tds.is_vertex(&(*v)) );
      
  if ( number_of_vertices() < 2 ) { return; }

  if ( &(*c) == NULL ) {
    c = v->cell();
  }
  else {
    CGAL_triangulation_precondition( c->has_vertex(v) );
  }

  std::set<Cell*, std::less<Cell*> > cells;
  util_incident_vertices(v, vertices, cells, c);
  return;
  // previous buggy version !
  //       int found = 0;
  //       for ( j=0; j <= d; j++ ) {
  // 	if ( j != c->index(v) ) {
  // 	  if ( vertices.find( &(*(c->vertex(j))) ) == vertices.end() ) {
  // 	    vertices.insert( &(*(c->vertex(j))) );
  // 	  }
  // 	  else {
  // 	    found++; // c->vertex(j) was already found 
  // 	  }
  // 	}
  //       }
  //       if ( found == 3 ) return; // c was already visited
      
  //       for ( j=0; j <= d; j++ ) {
  // 	if ( j != c->index(v) ) {
  // 	  incident_vertices( v, vertices, c->neighbor(j) );
  // 	}
  //       }
}

template < class GT, class Tds >
void
Triangulation_3<GT,Tds>::
util_incident_vertices(Vertex_handle v, 
		       std::set<Vertex*, std::less<Vertex*> > & vertices,
		       std::set<Cell*, std::less<Cell*> > & cells,
		       Cell_handle c ) const
{
  if ( cells.find( &(*c) ) != cells.end() ) {
    return; // c was already visited
  }
  cells.insert( &(*c) );

  int d = dimension();
  int j;
  for ( j=0; j <= d; j++ ) {
    if ( j != c->index(v) ) {
      if ( vertices.find( &(*(c->vertex(j))) ) == vertices.end() ) {
	vertices.insert( &(*(c->vertex(j))) );
      }
      util_incident_vertices( v, vertices, cells, c->neighbor(j) );
    }
  }
      
}

template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
is_valid(bool verbose, int level) const
{
  if ( ! _tds.is_valid(verbose,level) ) {
    if (verbose) { std::cerr << "invalid data structure" << std::endl; }
    CGAL_triangulation_assertion(false); return false;
  }
    
  if ( &(*infinite_vertex()) == NULL ) {
    if (verbose) { std::cerr << "no infinite vertex" << std::endl; }
    CGAL_triangulation_assertion(false); return false;
  }

  switch ( dimension() ) {
  case 3:
    {
      Cell_iterator it;
      for ( it = finite_cells_begin(); it != cells_end(); ++it ) {
	// 	if ( geom_traits().orientation(it->vertex(0)->point(),
	// 			      it->vertex(1)->point(),
	// 			      it->vertex(2)->point(),
	// 			      it->vertex(3)->point()) != LEFTTURN ) {
	// 	  if (verbose) { std::cerr << "badly oriented cell " 
	// 			      << it->vertex(0)->point() << ", " 
	// 			      << it->vertex(1)->point() << ", " 
	// 			      << it->vertex(2)->point() << ", " 
	// 			      << it->vertex(3)->point() << ", " 
	// 			      << std::endl; }
	// 	  CGAL_triangulation_assertion(false); return false;
	// 	}
	is_valid_finite((*it).handle(),verbose,level);
      }
      break;
    }
  case 2:
    {
      Facet_iterator it;
      for ( it = finite_facets_begin(); it != facets_end(); ++it ) {
	is_valid_finite((*it).first,verbose,level);
      }
      break;
    }
  case 1:
    {
      Edge_iterator it;
      for ( it = finite_edges_begin(); it != edges_end(); ++it ) {
	is_valid_finite((*it).first,verbose,level);
      }
      break;
    }
  }
  if (verbose) { std::cerr << "valid triangulation" << std::endl;}
  return true;
}

template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
is_valid(Cell_handle c, bool verbose, int level) const
{
  int i;
  if ( ! (&(*c))->is_valid(dimension(),verbose,level) ) {
    if (verbose) { 
      std::cerr << "combinatorically invalid cell" ;
      for ( i=0; i <= dimension(); i++ ) {
	std::cerr << c->vertex(i)->point() << ", " ;
      }
      std::cerr << std::endl;
    }
    CGAL_triangulation_assertion(false); return false;
  }
  if ( ! is_infinite(c) ) {
    is_valid_finite(c,verbose,level);
  }
  if (verbose) { std::cerr << "geometrically valid cell" << std::endl;}
  return true;
} //end is_valid(cell)

template < class GT, class Tds >
bool
Triangulation_3<GT,Tds>::
is_valid_finite(Cell_handle c, bool verbose, int) const
{
  switch ( dimension() ) {
  case 3:
    {
      if ( geom_traits().orientation(c->vertex(0)->point(),
				     c->vertex(1)->point(),
				     c->vertex(2)->point(),
				     c->vertex(3)->point()) 
	   != LEFTTURN ) {
	if (verbose) { std::cerr << "badly oriented cell " 
				 << c->vertex(0)->point() << ", " 
				 << c->vertex(1)->point() << ", " 
				 << c->vertex(2)->point() << ", " 
				 << c->vertex(3)->point() << std::endl; 
	}
	CGAL_triangulation_assertion(false); return false;
      }
      break;
    }
  case 2:
    {
      for ( int i=0; i<3; i++ ) {
	if ( ( ! is_infinite
	       ( c->neighbor(i)->vertex(c->neighbor(i)->index(c)) ) )
	     && 
	     geom_traits().orientation_in_plane
	     ( c->vertex(cw(i))->point(),
	       c->vertex(ccw(i))->point(),
	       c->vertex(i)->point(),
	       c->neighbor(i)->vertex(c->neighbor(i)->index(c))->point()
	       )
	     != NEGATIVE ) {
	  if (verbose) { std::cerr << "badly oriented face "
				   << c->vertex(0)->point() << ", " 
				   << c->vertex(1)->point() << ", " 
				   << c->vertex(2)->point() 
				   << "with neighbor " << i
				   << c->neighbor(i)->vertex(0)->point() 
				   << ", " 
				   << c->neighbor(i)->vertex(1)->point() 
				   << ", " 
				   << c->neighbor(i)->vertex(2)->point() 
				   << std::endl; }
	  CGAL_triangulation_assertion(false); return false;
	}
      }
      break;
    }
  case 1:
    {
      Point p0 = c->vertex(0)->point();
      Point p1 = c->vertex(1)->point();
	    
      //	  Point n1 =
      //
      //	  c->neighbor(1)->vertex(c->neighbor(1)->index(c))->point(); 
      if ( ! is_infinite
	   ( c->neighbor(0)->vertex(c->neighbor(0)->index(c)) ) ) {
	Point n0 = 
	  c->neighbor(0)->vertex(c->neighbor(0)->index(c))->point();  
	if ( ( geom_traits().compare_x( p0, p1 )
	       != geom_traits().compare_x( p1, n0 ) )
	     || ( geom_traits().compare_y( p0, p1 )
		  != geom_traits().compare_y( p1, n0 ) )
	     || ( geom_traits().compare_z( p0, p1 )
		  != geom_traits().compare_z( p1, n0 ) ) ) {
	  if (verbose) { std::cerr << "badly oriented edge "
				   << p0 << ", " << p1 << std::endl
				   << "with neighbor 0"
				   << c->neighbor(0)->vertex
			   (1-c->neighbor(0)->index(c))->point() 
				   << ", "
				   << n0
				   << std::endl; }
	  CGAL_triangulation_assertion(false); return false;
	}
      }
      if ( ! is_infinite
	   ( c->neighbor(1)->vertex(c->neighbor(1)->index(c)) ) ) { 
	Point n1 = 
	  c->neighbor(1)->vertex(c->neighbor(1)->index(c))->point();
	if ( ( geom_traits().compare_x( p1, p0 )
	       != geom_traits().compare_x( p0, n1 ) )
	     || ( geom_traits().compare_y( p1, p0 )
		  != geom_traits().compare_y( p0, n1 ) )
	     || ( geom_traits().compare_z( p1, p0 )
		  != geom_traits().compare_z( p0, n1 ) ) ) {
	  if (verbose) { std::cerr << "badly oriented edge "
				   << p0 << ", " << p1 << std::endl
				   << "with neighbor 1"
				   << c->neighbor(1)
			   ->vertex(1-c->neighbor(1)->index(c))->point() 
				   << ", "
				   << n1
				   << std::endl; }
	  CGAL_triangulation_assertion(false); return false;
	}
      }
      break;
    }
  }
  return true;
}

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_3_H

