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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Delaunay_triangulation_3.h
// package       : Triangulation3 (1.42)
// revision      : $Revision: 1.33 $
//
// author(s)     : Monique Teillaud
//
// coordinator   : INRIA Sophia Antipolis 
//                 (Mariette Yvinec)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_DELAUNAY_TRIANGULATION_3_H
#define CGAL_DELAUNAY_TRIANGULATION_3_H

#include <CGAL/basic.h>

#include <set>
#include <CGAL/Triangulation_utils_3.h>
#include <CGAL/Triangulation_3.h>

#include <CGAL/Triangulation_short_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds>
class Delaunay_triangulation_3 : public Triangulation_3<Gt,Tds>
{
  friend std::istream& operator >> CGAL_NULL_TMPL_ARGS
  (std::istream& is, Triangulation_3<Gt,Tds> &tr);

public:

  typedef typename Gt::Point Point;
  typedef typename Gt::Segment Segment;
  typedef typename Gt::Triangle Triangle;
  typedef typename Gt::Tetrahedron Tetrahedron;

  typedef typename Triangulation_3<Gt,Tds>::Cell_handle Cell_handle;
  typedef typename Triangulation_3<Gt,Tds>::Vertex_handle Vertex_handle;

  typedef typename Triangulation_3<Gt,Tds>::Cell Cell;
  typedef typename Triangulation_3<Gt,Tds>::Vertex Vertex;
  typedef typename Triangulation_3<Gt,Tds>::Facet Facet;
  typedef typename Triangulation_3<Gt,Tds>::Edge Edge;

  typedef typename Triangulation_3<Gt,Tds>::Cell_circulator Cell_circulator;
  typedef typename Triangulation_3<Gt,Tds>::Cell_iterator Cell_iterator;
  typedef typename Triangulation_3<Gt,Tds>::Facet_iterator Facet_iterator;
  typedef typename Triangulation_3<Gt,Tds>::Edge_iterator Edge_iterator;
  typedef typename Triangulation_3<Gt,Tds>::Vertex_iterator Vertex_iterator;

  typedef typename Triangulation_3<Gt,Tds>::Locate_type Locate_type;

  Delaunay_triangulation_3()
    : Triangulation_3<Gt,Tds>() {}
  
  Delaunay_triangulation_3(const Gt & gt)
    : Triangulation_3<Gt,Tds>(gt) {}
  
  Delaunay_triangulation_3(const Point & p0,
			   const Point & p1,
			   const Point & p2,
			   const Point & p3)
    : Triangulation_3<Gt,Tds>(p0,p1,p2,p3){} // debug

  // copy constructor duplicates vertices and cells
  Delaunay_triangulation_3(const Delaunay_triangulation_3<Gt,Tds> & tr)
    : Triangulation_3<Gt,Tds>(tr)
    { CGAL_triangulation_postcondition( is_valid() );  }
  
  template < class InputIterator >
  int
  insert(InputIterator first, InputIterator last)
  {
    int n = number_of_vertices();
    while(first != last){
      insert(*first);
      ++first;
    }
    return number_of_vertices() - n;
  }

  Vertex_handle insert(const Point & p );

  Vertex_handle insert(const Point & p, Cell_handle start);
  
  bool remove(Vertex_handle v );

  // to be made private after tests
  void make_hole_3D(Vertex_handle v,
		    std::set<Facet> & boundhole,
		    std::set<Vertex_handle> & boundvert);	

  bool fill_hole_3D(std::set<Facet> & boundhole,
		    std::set<Vertex_handle> & boundvert);	
  void print(Vertex_handle v) const;

private:
  void
  find_conflicts_3(std::set<void*, std::less<void*> > & conflicts, 
		   const Point & p,
		   Cell_handle c, Cell_handle & ac, int & i);
    // 3d case
    // p is in conflict with c
    // finds the set conflicts of cells in conflict with p
    // gives a cell ac having a facet on the boundary of conflicts
    // and the index i of its facet on the boundary
  void
  find_conflicts_2(std::set<void*, std::less<void*> > & conflicts, 
		   const Point & p,
		   Cell_handle c, Cell_handle & ac, int & i);
    // 2d case
    // p is in conflict with c
    // finds the set conflicts of cells in conflict with p
    // gives a cell ac having a facet on the boundary of conflicts
    // and the index i of its facet on the boundary
  inline bool
  violates( Vertex_handle u, 
	    Vertex_handle v0, Vertex_handle v1, Vertex_handle v2, 
	    Facet f);
  // checks whether edge uv crosses f

  bool remove_3D(Vertex_handle v );
  //  void make_hole_3D(Vertex_handle v,
  //		    std::list<Facet> & hole) const;		 

  Bounded_side
  side_of_sphere( Vertex_handle v0, 
		  Vertex_handle v1, 
		  Vertex_handle v2, 
		  Vertex_handle v3, 
		  const Point & p) const;

public:

  Bounded_side
  side_of_sphere( Cell_handle c, const Point & p) const;

  Bounded_side
  side_of_circle( const Facet & f, const Point & p) const
    {
      return side_of_circle(f.first, f.second, p);
    }

  Bounded_side
  side_of_circle( Cell_handle c, int i, const Point & p) const;
    // precondition : dimension >=2
    // in dimension 3, - for a finite facet
    // returns ON_BOUNDARY if the point lies on the circle,
    // ON_UNBOUNDED_SIDE when exterior, ON_BOUNDED_SIDE
    // interior
    // for an infinite facet, considers the plane defined by the
    // adjacent finite facet of the same cell, and does the same as in 
    // dimension 2 in this plane
    // in dimension 2, for an infinite facet
    // in this case, returns ON_BOUNDARY if the point lies on the 
    // finite edge (endpoints included) 
    // ON_BOUNDED_SIDE for a point in the open half-plane
    // ON_UNBOUNDED_SIDE elsewhere
  
  bool is_valid(bool verbose = false, int level = 0) const;

  bool is_valid(Cell_handle c, bool verbose = false, int level = 0) const;

};

template < class Gt, class Tds >
Delaunay_triangulation_3<Gt,Tds>::Vertex_handle
Delaunay_triangulation_3<Gt,Tds>::
insert(const Point & p )
{
  Cell_handle start;
  if ( dimension() >= 1 ) {
    // there is at least one finite "cell" (or facet or edge)
    start = infinite_vertex()->cell()
      ->neighbor( infinite_vertex()->cell()->index( infinite_vertex()) );
  }
  else {
    start = NULL;
  }
  return insert( p, start );
}

template < class Gt, class Tds >
Delaunay_triangulation_3<Gt,Tds>::Vertex_handle
Delaunay_triangulation_3<Gt,Tds>::
insert(const Point & p, Cell_handle start)
{
  switch (dimension()) {
  case 3:
    {
      Locate_type lt;
      int li, lj;
      Cell_handle c = locate( p, start, lt, li, lj);
      if ( lt == VERTEX ) return c->vertex(li);
      else {
//       case OUTSIDE_CONVEX_HULL:
//       case CELL:
//       case FACET:
//       case EDGE:
	  Vertex_handle v = new Vertex(p);
	  set_number_of_vertices(number_of_vertices()+1);
	  std::set<void*, std::less<void*> > conflicts;
	  Cell_handle aconflict;
	  int ineighbor;
	  find_conflicts_3(conflicts,p,c,aconflict,ineighbor);
	  _tds.star_region(conflicts,&(*v),&(*aconflict),ineighbor);
	  return v;
      }
      break;
    }// dim 3
  case 2:
    {
      Locate_type lt;
      int li, lj;
      Cell_handle c = locate( p, start, lt, li, lj);
      switch (lt) {
      case OUTSIDE_CONVEX_HULL:
      case CELL:
      case FACET:
      case EDGE:
	{
	  Vertex_handle v = new Vertex(p);
	  set_number_of_vertices(number_of_vertices()+1);
	  std::set<void*, std::less<void*> > conflicts;
	  Cell_handle aconflict;
	  int ineighbor;
	  find_conflicts_2(conflicts,p,c,aconflict,ineighbor);
	  _tds.star_region(conflicts,&(*v),&(*aconflict),ineighbor);
	  return v;
	}
      case VERTEX:
	return c->vertex(li);
      case OUTSIDE_AFFINE_HULL:
	{
	  // if the 2d triangulation is Delaunay, the 3d
	  // triangulation will be Delaunay
	  return
	    Triangulation_3<Gt,Tds>::insert_outside_affine_hull(p); 
	}
      }
    }//dim 2
  default :
    // dimension <= 1
    return Triangulation_3<Gt,Tds>::insert(p);
  }
  return Triangulation_3<Gt,Tds>::insert(p);// to avoid warning with egcs
}// insert(p)

template < class Gt, class Tds >
bool
Delaunay_triangulation_3<Gt,Tds>::
remove(Vertex_handle v)
{
  CGAL_triangulation_precondition( v != Vertex_handle());
  CGAL_triangulation_precondition( !is_infinite(v));
  CGAL_triangulation_precondition( _tds.is_vertex(&(*v)) );

  if ( dimension() <3 ) {
    // to be implemented : removal in degenerate dimensions
    // the traingulation is now rebuilt...

    Vertex_iterator vit;
    Vertex_iterator vdone = vertices_end();
    std::list<Point> points;
    for ( vit = finite_vertices_begin(); vit != vdone ; ++vit) {
      if ( v != (*vit).handle() ) 
	{ points.push_front( vit->point() ); }
    }
    typename std::list<Point>::iterator pit;
    typename std::list<Point>::iterator pdone = points.end();
    
    clear();
    for ( pit = points.begin(); pit != pdone; ++pit) {
      insert( *pit );
    }

    return true;
  }

  return remove_3D(v);
}// remove(v)

template < class Gt, class Tds >
bool
Delaunay_triangulation_3<Gt,Tds>::
remove_3D(Vertex_handle v)
{
  CGAL_triangulation_precondition( dimension() == 3 );

  std::set<Facet> boundary; // facets on the boundary of the hole
  std::set<Vertex_handle> bdvert; // vertices on the boundary of the hole

  if ( test_dim_down(v) ) {

    // _tds.remove_dim_down(&(*v)); return; 
    // !!!!!!!!!!!! TO BE DONE !!!!!!!!!!!!!
    // the triangulation is rebuilt...

    Vertex_iterator vit;
    Vertex_iterator vdone = vertices_end();
    std::list<Point> points;
    for ( vit = finite_vertices_begin(); vit != vdone ; ++vit) {
	if ( v != (*vit).handle() ) { points.push_front( vit->point() ); }
    }
    typename std::list<Point>::iterator pit;
    typename std::list<Point>::iterator pdone = points.end();
    
    clear();
    for ( pit = points.begin(); pit != pdone; ++pit) {
      insert( *pit );
    }
    return true;
  }

  //  std::cout << "removed point " << v->point() << std::endl;

  make_hole_3D(v, boundary, bdvert);
  bool b = fill_hole_3D(boundary, bdvert);

  delete( &(*v) );
  set_number_of_vertices(number_of_vertices()-1);

  return b;
}// remove_3D(v)

template < class Gt, class Tds >
void
Delaunay_triangulation_3<Gt,Tds>::
make_hole_3D( Vertex_handle v, 
	      std::set<Facet> & boundhole,
	      std::set<Vertex_handle> & boundvert)
{
  CGAL_triangulation_precondition( ! test_dim_down(v) );

  typedef std::set<Cell_handle, std::less<Cell_handle> > Hole_cells;
  Hole_cells cells;
  incident_cells( v, cells );
  int i, indv;

  typename Hole_cells::iterator cit = cells.begin();
  typename Hole_cells::iterator cdone = cells.end();

  Cell_handle opp_cit;
  Vertex_handle vi;
  do {
    indv = (*cit)->index(&(*v));
    opp_cit = (*cit)->neighbor( indv );
    
    boundhole.insert
      (	std::make_pair( opp_cit, opp_cit->index(*cit)) );
    for ( i=0; i<4; i++) {
      if ( i != indv ) {
	vi = (*cit)->vertex(i);
	if ( boundvert.find( vi ) == boundvert.end() )
	  {
	    boundvert.insert( vi );
	    vi->set_cell( opp_cit );
	  }
      }
    }
    
    _tds.delete_cell( &*(*cit) );

    ++cit;
  } while ( cit != cdone );

  return;
}// make_hole_3D

//debug
template < class Gt, class Tds >
void 
Delaunay_triangulation_3<Gt,Tds>::
print( Vertex_handle v ) const
{
  if ( is_infinite( v ) )
    std::cout << "inf" << "; ";
  else 
    std::cout << v->point() << "; ";
};

template < class Gt, class Tds >
bool
Delaunay_triangulation_3<Gt,Tds>::
fill_hole_3D( std::set<Facet> & boundhole,
	      std::set<Vertex_handle> & boundvert)
  // examines each facet of the hole in turn and finds the fourth
  // vertex to build a cell
{
  typename std::set<Facet>::iterator fit;
  typename std::set<Facet>::iterator fitset_tmp;

  Facet fit_stick;
  typename std::list<Facet>::iterator fitlist_tmp;

  typename std::set<Vertex_handle>::iterator vit;
  typename std::set<Vertex_handle>::iterator vdone = boundvert.end();

  Vertex_handle v[3]; // current facet
  Vertex_handle vf1,vf2,vf3;

  std::set<Vertex_handle> oppvert; // vertices of the hole
  // that are all copsherical with the current facet and whose sphere
  // is empty 
  typename std::set<Vertex_handle>::iterator bv;

  std::list<Facet> cosph_bound; // facets of boundhole that
  // are cospherical with the vertices of oppvert 
  std::list<Facet> not_violate;
  std::list<Facet> for_next; // facets created or not used by
  // the current vertex 

  // the facets in these sets will always be given by the cell
  // **outside** the hole and their index in this cell

  Cell_handle cnew;
  int i;

  Bounded_side sos;
  Orientation or;
  bool opp_inf, sticked, created;
  int nbnew = 1; // to detect a loop in the execution due to an
  // impossible case 

  //debug
  //  int nbfacet = 0;

  while( ! boundhole.empty() ) {
    //    std::cout << boundhole.size() << " boundary faces remaining" 
    // << std::endl;
    fit = boundhole.begin();
//     for ( fit = boundhole.begin(); fit != boundhole.end(); ++fit ) {
// 	print( (*fit).first->vertex( ((*fit).second+1)&3 ) );
// 	print( (*fit).first->vertex( ((*fit).second+2)&3 ) );
// 	print( (*fit).first->vertex( ((*fit).second+3)&3 ) );
// 	std::cout << std::endl;
//     }	       

    fit = boundhole.begin();
    while( (fit != boundhole.end()) && has_vertex(*fit,infinite_vertex()) ) {
      ++fit;
    }
    if (fit == boundhole.end()) {
      // all the remaining facets have the infinite vertex 
      //      std::cout << " pb" << std::endl;
    }

    cosph_bound.clear();
    oppvert.clear();
    //    new_fac.clear();

    //debug
    //    nbfacet++;
    
    // orientation of the facet chosen so that the future cell
    // v0,v1,v2,oppvert is correctly oriented
    // (ie. orientation reversed with respect to the cell giving (*fit),
    // which is outside the hole)

    if ( ((*fit).second%2) == 0) {
      v[0] = (*fit).first->vertex( ((*fit).second+1)&3 );
      v[1] = (*fit).first->vertex( ((*fit).second+2)&3 );
      v[2] = (*fit).first->vertex( ((*fit).second+3)&3 );
    }
    else {
      v[0] = (*fit).first->vertex( ((*fit).second+2)&3 );
      v[1] = (*fit).first->vertex( ((*fit).second+1)&3 );
      v[2] = (*fit).first->vertex( ((*fit).second+3)&3 );
    }      

    //debug
//     std::cout << std::endl << nbfacet << "- facet : " << std::endl;
//     for ( i=0; i<3; i++ ) { print( v[i] ); }
//     std::cout << " index " << (*fit).second << std::endl;
//     std::cout << "   cell " ;
//     for ( i=0; i<4; i++ ) { print( (*fit).first->vertex(i) ); }
//     std::cout << std::endl;

    if ( nbnew == 0 ) {
      // the program is looping
      std::cerr << " !!!!! IMPOSSIBLE TO RETRIANGULATE !!!!! " << std::endl;
      return false;
    }
    nbnew = 0;
   
    // looking for a vertex to build a cell with the current facet *fit
    vit = boundvert.begin();
    while ( (( *vit == v[0] ) || ( *vit == v[1] ) || ( *vit == v[2] )) 
	    ||
	    ( ( ! is_infinite(v[0]) ) && 
	      ( ! is_infinite(v[1]) ) &&
	      ( ! is_infinite(v[2]) ) &&
	      ( ! is_infinite(*vit) ) &&
	      geom_traits().orientation( v[0]->point(),v[1]->point(),
					 v[2]->point(),(*vit)->point() ) 
	      != POSITIVE ) ) 
      { ++vit; }
    oppvert.insert(*vit); // candidate to build a cell with *fit
    // it is either infinite or on the positive side of the facet
    opp_inf = is_infinite( *vit );

    // checking whether the current candidate forms an empty sphere
    ++vit;
    i=0;
    while ( vit != vdone ) {
      if ( *vit == v[0] ) {++vit; continue;};
      if ( *vit == v[1] ) {++vit; continue;};
      if ( *vit == v[2] ) {++vit; continue;};

      //debug
//       std::cout << "    vertex " ; print( *oppvert.begin() );
//       std::cout << std::endl << "            test " ; print( *vit );
//       std::cout << std::endl;

      if ( ! is_infinite(*vit) ) {
	sos = side_of_sphere(v[0],v[1],v[2],*oppvert.begin(), 
			     (*vit)->point());
	or = geom_traits().orientation( v[0]->point(), v[1]->point(),
					v[2]->point(), (*vit)->point() );
	if ( or == POSITIVE ) {
	  if ( sos == ON_BOUNDED_SIDE ) {
	    if ( is_infinite(*oppvert.begin()) ) {
	      oppvert.erase(infinite_vertex());
	      opp_inf = false;
	      //	      std::cout << "          cocy kept - inf"
	      //	      << std::endl; 
	    }
	    else {
	      for ( bv=oppvert.begin(); bv!= oppvert.end(); ++bv ) {
		if ( side_of_sphere(v[0],v[1],v[2],(*bv),(*vit)->point())
		     != ON_BOUNDARY ) break;
	      }
	      if ( bv == oppvert.end() ) {
		oppvert.erase(*oppvert.begin());
		// because all the other points are cospherical with vit
		//		std::cout << "          cocy kept" <<
		//		std::endl; 
	      }
	      else {
		oppvert.clear();
	      }
	    }
	    oppvert.insert(*vit); 
	    //	    std::cout << "          inside" << std::endl;
	  }
	  else {
	    if ( sos == ON_BOUNDARY ) {
	      oppvert.insert(*vit); 
	      //	      std::cout << "          cosph" << std::endl;
	    }; 
	  };
	}
	else {
	  if ( (or == COPLANAR) && (opp_inf) && (sos == ON_BOUNDARY) ) {
	    oppvert.insert(*vit); 
	    //	    std::cout << "          cocycl" << std::endl;
	  }
	}
      };

      ++vit;
    }
    // now oppvert contains 
    // either the only possible vertex to build a cell with the
    // current facet *fit
    // or the set of vertices that are cospherical with the vertices
    // of the current facet *fit

    // in the case when there are several vertices in oppvert, the
    // polyhedron they form must be triangulated without violating the 
    // possibly already existing facets on the boundary of the hole.

    // creation of a list of cospherical facets already on the
    // boundary of the hole, that must not be violated
    if ( oppvert.size() > 1 ) {
      fitset_tmp = boundhole.begin();
      //debug
      std::cout << "    constraining facets " << std::endl;
      
      not_violate.clear();

      while ( fitset_tmp != boundhole.end() ) {
	vf1 = (*fitset_tmp).first->vertex(((*fitset_tmp).second+1)&3);
	vf2 = (*fitset_tmp).first->vertex(((*fitset_tmp).second+2)&3);
	vf3 = (*fitset_tmp).first->vertex(((*fitset_tmp).second+3)&3);
	if (
	    ( (vf1 == v[0]) || (vf1 == v[1]) || (vf1 == v[2]) ||
	      ( oppvert.find(vf1) != oppvert.end() ) )
	    &&
	    ( (vf2 == v[0]) || (vf2 == v[1]) || (vf2 == v[2]) ||
	      ( oppvert.find(vf2) != oppvert.end() ) )
	    &&
	    ( (vf3 == v[0]) || (vf3 == v[1]) || (vf3 == v[2]) ||
	      ( oppvert.find(vf3) != oppvert.end() ) )
	    )
	  {
	    cosph_bound.push_front( *fitset_tmp );
	    // fit will be one of the facets inserted

	    //	    print( vf1 ); print( vf2 ); print( vf3 ); 
	    //	    std::cout << " cosph" << std::endl;
	    ++fitset_tmp;
	    continue;
	  }
	for ( bv=oppvert.begin(); bv!=oppvert.end(); ++bv ) {
	  if ( ( ! is_infinite(*bv) )
	       &&
	       ( ! is_infinite( *fitset_tmp ) )
	       &&
	       ((( (vf1 == v[0]) || (vf1 == v[1]) || (vf1 == v[2]) )
		 &&
		 ( (vf2 == v[0]) || (vf2 == v[1]) || (vf2 == v[2]) )
		 &&
		 ( geom_traits().orientation
		   (vf1->point(),vf2->point(),
		    vf3->point(),(*bv)->point()) == COPLANAR ))
		||
		(( (vf1 == v[0]) || (vf1 == v[1]) || (vf1 == v[2]) )
		 &&
		 ( (vf3 == v[0]) || (vf3 == v[1]) || (vf3 == v[2]) )
		 &&
		 ( geom_traits().orientation
		   (vf1->point(),vf2->point(),
		    vf3->point(),(*bv)->point()) == COPLANAR ))
		||
		(( (vf2 == v[0]) || (vf2 == v[1]) || (vf2 == v[2]) )
		 &&
		 ( (vf3 == v[0]) || (vf3 == v[1]) || (vf3 == v[2]) )
		 &&
		 ( geom_traits().orientation
		   (vf1->point(),vf2->point(),
		    vf3->point(),(*bv)->point()) == COPLANAR )) ) )
	    {
	      not_violate.push_front(*fitset_tmp);
	      //	      print( vf1 ); print( vf2 ); print( vf3 ); 
	      //	      std::cout << " copl ";
	      //	      print(*bv); std::cout << std::endl;
	      ++fitset_tmp;
	      continue;
	    }
	}
	++fitset_tmp;
      }
    }
    else cosph_bound.push_front( *fit ); // *fit is the only element in
    // this case

    not_violate.insert(not_violate.end(),
		       cosph_bound.begin(),cosph_bound.end());

    // if there are cospherical vertices, the polyhedron they form is
    // triangulated by linking each vertex in its turn to its visible
    // facets, without violating the facets of cosph_bound
    while ( oppvert.size() > 0 ) {
      // look for all the facets of the polyhedron visible from
      // oppvert.begin() 
//       std::cout << std::endl << "oppvert " ; print(*oppvert.begin());
//       std::cout << std::endl;

      for_next.clear();

      while ( ! cosph_bound.empty() ) {
	fit_stick = cosph_bound.front();
	cosph_bound.pop_front(); 
	

	if ( has_vertex( fit_stick, *oppvert.begin() ) ) {
	  for_next.push_front( fit_stick );
	  continue;
	}
	     
	if ( ((fit_stick).second%2) == 0 ) {
	  v[0] = (fit_stick).first->vertex( ((fit_stick).second+1)&3 );
	  v[1] = (fit_stick).first->vertex( ((fit_stick).second+2)&3 );
	  v[2] = (fit_stick).first->vertex( ((fit_stick).second+3)&3 );
	}
	else {
	  v[0] = (fit_stick).first->vertex( ((fit_stick).second+2)&3 );
	  v[1] = (fit_stick).first->vertex( ((fit_stick).second+1)&3 );
	  v[2] = (fit_stick).first->vertex( ((fit_stick).second+3)&3 );
	}

	//	std::cout << "test facet " ;
	//	for ( i=0; i<3; i++ ) {print(v[i]);}; std::cout << std::endl;

	// testing if the current vertex of oppvert can be associated
	// with this facet fit_stick without violating any facet of
	// not_violate
	fitlist_tmp = not_violate.begin();
	while ( fitlist_tmp != not_violate.end() ) {
 	  if ( (*fitlist_tmp) == fit_stick ) {
 	    ++fitlist_tmp;
 	    continue;
 	  }
	  if ( ! (is_infinite(v[0]) ||
		  is_infinite(v[1]) || 
		  is_infinite(v[2]) ||
		  is_infinite(*oppvert.begin()) ) 
	       ) {
	    if ( violates( *oppvert.begin(),v[0],v[1],v[2],*fitlist_tmp ) ) 
	      break;
	  }
	  ++fitlist_tmp;
	}
	if ( fitlist_tmp != not_violate.end() ) {
	  // this facet cannot form a cell with oppvert.begin()
	  for_next.push_front(fit_stick);
	  continue;
	}
	
	// here fit_stick does not violate any facet
	// test whether it is visible from oppvert.begin()
	created = false;
	if ( ( ! (is_infinite(v[0]) ||
		  is_infinite(v[1]) || 
		  is_infinite(v[2])) )
	     // already tested, ti be removed
	     && 
	     ( ( ! is_infinite((*oppvert.begin())) &&
		 ( geom_traits().orientation
		   (v[0]->point(),v[1]->point(),v[2]->point(),
		    ((*oppvert.begin()))->point()) 
		   == POSITIVE ) )
	       ||
	       ( is_infinite((*oppvert.begin())) &&
		 ! is_infinite( (fit_stick).first
				->vertex((fit_stick).second ) ) )
	       )
	     ) 
	  { // creation of a cell
	    cnew = new Cell (v[0],v[1],v[2],(*oppvert.begin()),
			     NULL,NULL,NULL,(fit_stick).first);
	    ++nbnew;
// 	    std::cout << "cell " ;
// 	    for (i=0;i<4;i++) { print(cnew->vertex(i)); };
// 	    std::cout << std::endl;

	    _tds.add_cell( &(*cnew) );
	    (fit_stick).first->set_neighbor((fit_stick).second,cnew);
	    created = true;
	    ((*oppvert.begin()))->set_cell(cnew);

	    boundhole.erase( fit_stick );
	    not_violate.remove( fit_stick);
	    for_next.remove( fit_stick);

	    for ( i=0; i<3; i++ ) { 
	      v[i]->set_cell(cnew); //useless ? to be checked

	      // if the facet ( cnew, i ) is already on the boundary 
	      // of the hole, it must be sticked and removed from
	      // the hole
// 	      std::cout << "    facet " ;
// 	      for ( j=1; j<4; j++ ) {print(cnew->vertex((i+j)&3));};
// 	      std::cout << std::endl;

	      fitlist_tmp = cosph_bound.begin();
	      sticked = false;
	      while ( (fitlist_tmp != cosph_bound.end()) && (! sticked) ) {
		if ( are_equal( *fitlist_tmp, cnew, i ) ) {
		  (*fitlist_tmp).first->set_neighbor
		    ((*fitlist_tmp).second,cnew);
		  cnew->set_neighbor(i,(*fitlist_tmp).first);

		  not_violate.remove(*fitlist_tmp);
		  boundhole.erase(*fitlist_tmp);
		  cosph_bound.erase(fitlist_tmp);

		  sticked = true;
		  //		  std::cout << "      sticked" << std::endl;
		  break;
		}
		++fitlist_tmp;
	      }
	      fitlist_tmp = for_next.begin();
	      while ( (fitlist_tmp != for_next.end()) && (! sticked) ) {
		if ( are_equal( *fitlist_tmp, cnew, i ) ) {
		  (*fitlist_tmp).first->set_neighbor
		    ((*fitlist_tmp).second,cnew);
		  cnew->set_neighbor(i,(*fitlist_tmp).first);

		  not_violate.remove(*fitlist_tmp);
		  boundhole.erase(*fitlist_tmp);
		  for_next.erase(fitlist_tmp);

		  sticked = true;
		  //		  std::cout << "      sticked" << std::endl;
		  break;
		}
		++fitlist_tmp;
	      }
	      if ( ! sticked ) {
		//		std::cout << "      not sticked" << std::endl;

		for_next.push_front( std::make_pair( cnew, i ) );
		not_violate.push_front( std::make_pair( cnew, i ) );
	      }
	    }
	  }
	else 
	  {
	    // fit_stick is already in not_violate
	    for_next.push_front( fit_stick );
	  }
      }
      cosph_bound = for_next;
      oppvert.erase(oppvert.begin());
    }



//     std::cout << std::endl << "triangulated polyhedron" << std::endl;
//     std::cout << boundhole.size() << " facets in boundhole" <<
//       std::endl;
//     std::cout << cosph_bound.size() << " facets remaining in cosph_bound" 
//       << std::endl;
    // looking whether the new facets just built are already on the
    // boundary 
    // if they are, update the adjacency relations
    //
    // unefficient code, to be changed 

    while ( ! cosph_bound.empty() ) {
      fit_stick = cosph_bound.front();
      cosph_bound.pop_front();

//       std::cout << "   facet " ;
//       for ( i=1; i<4; i++ ) 
// 	{print((fit_stick).first->vertex(((fit_stick).second+i)&3));};
//       std::cout << " index " << (fit_stick).second << std::endl;
      
      sticked = false;
      fitset_tmp = boundhole.begin();
      while (fitset_tmp != boundhole.end()) {
	if ((*fitset_tmp) == fit_stick) { ++fitset_tmp; continue; };
	if ( are_equal( *fitset_tmp, fit_stick ) ) {
// 	  std::cout << "        sticked to " ;
// 	  for ( i=1; i<4; i++ ) {
// 	    print((*fitset_tmp).first->vertex(((*fitset_tmp).second+i)&3));};
// 	  std::cout << " of " ;
// 	  for ( i=0; i<4; i++ ) {
// 	    print((*fitset_tmp).first->vertex(i));}
// 	  std::cout << std::endl;

	  (*fitset_tmp).first->set_neighbor
	    ((*fitset_tmp).second,(fit_stick).first);
	  (fit_stick).first->set_neighbor
	    ((fit_stick).second,(*fitset_tmp).first);

	  boundhole.erase(*fitset_tmp);

	  sticked = true;
	  break;
	};
	++fitset_tmp;
      }
      if ( ! sticked ) {
	boundhole.insert( fit_stick );
	// 	std::cout << "        not sticked" << std::endl;
      }
    }

  }

  return true;
}// fill_hole_3D


template < class Gt, class Tds >
void
Delaunay_triangulation_3<Gt,Tds>::
find_conflicts_3(std::set<void*, std::less<void*> > & conflicts, 
		 const Point & p,
		 Cell_handle c, Cell_handle & ac, int & i)
  // 3d case
  // p is in conflict with c
  // finds the set conflicts of cells in conflict with p
  // gives a cell ac having a facet on the boundary of conflicts
  // and the index i of its facet on the boundary
{
  if ( ( conflicts.find( (void *) &(*c) ) ) != conflicts.end() )
    return;   // c was already found

  (void) conflicts.insert( (void *) &(*c) );

  for ( int j=0; j<4; j++ ) {
    if ( side_of_sphere( c->neighbor(j),p ) 
	 ==  ON_BOUNDED_SIDE ) {
      find_conflicts_3(conflicts, p, c->neighbor(j), ac, i);
    }
    else {
      ac = c;
      i = j;
    }
  }
}// find_conflicts_3

template < class Gt, class Tds >
inline bool
Delaunay_triangulation_3<Gt,Tds>::
violates( Vertex_handle u, 
	  Vertex_handle v0, Vertex_handle v1, Vertex_handle v2, 
	  Facet f)
  {
    // u, v0, v1, v2 supposed to be all different
    Point pu( u->point() );

    int i,j,k,l;

    Point pf[3];
    pf[0] = (f.first)->vertex((f.second+1)&3)->point();
    pf[1] = (f.first)->vertex((f.second+2)&3)->point();
    pf[2] = (f.first)->vertex((f.second+3)&3)->point();
 
    if ( geom_traits().orientation( pu, pf[0], pf[1], pf[2] ) != COPLANAR ) 
      return false;

    Point p[3];
    p[0] = v0->point();
    p[1] = v1->point();
    p[2] = v2->point();
    Orientation o[3];
    o[0] = geom_traits().orientation(p[0],pf[0],pf[1],pf[2]);
    o[1] = geom_traits().orientation(p[1],pf[0],pf[1],pf[2]);
    o[2] = geom_traits().orientation(p[2],pf[0],pf[1],pf[2]);

    if ( ( o[0] != COPLANAR ) && ( o[1] != COPLANAR ) && ( o[2] != COPLANAR ) )
      return false;

    for ( i=0; i<3; i++ ) {
      if ( pu == pf[i] ) {
	j = (i+1)%3;
	k = (i+2)%3;
	if ( 
	    ( (o[0] == COPLANAR) && (p[0] != pf[j]) && (p[0] != pf[k]) &&
	      ( geom_traits().orientation_in_plane(pf[j],pf[k],pf[i],p[0])
		== NEGATIVE ) ) 
	    ||
	    ( (o[1] == COPLANAR) && (p[1] != pf[j]) && (p[1] != pf[k]) &&
	      ( geom_traits().orientation_in_plane(pf[j],pf[k],pf[i],p[1])
		== NEGATIVE ) ) 
	    ||
	    ( (o[2] == COPLANAR) && (p[2] != pf[j]) && (p[2] != pf[k]) &&
	      ( geom_traits().orientation_in_plane(pf[j],pf[k],pf[i],p[2])
		== NEGATIVE ) ) 
	    )
	  return true;
	else
	  return false;
      }
    }

    // here pu is none of pf[i]
    for ( i=0; i<3; i++ ) {
      if ( o[i] == COPLANAR )
	{
	  for ( l=0; l<3; l++ ) {
	    j = (l+1)%3;
	    k = (l+2)%3;
	    if ( p[i] == pf[l] ) {
	      if ( (pu != pf[j]) && (pu != pf[k]) &&
		   ( geom_traits().orientation_in_plane(pf[j],pf[k],pf[l],pu)
		     == NEGATIVE ) )
		return true;
	      else
		continue;
	    }
	    if ( ( geom_traits().orientation_in_plane(pf[j],pf[k],pu,p[i])
		   != POSITIVE ) )
	      return true;
	  }
	}
      else
	continue;
    }

    return false;
  }

template < class Gt, class Tds >
void
Delaunay_triangulation_3<Gt,Tds>::
find_conflicts_2(std::set<void*, std::less<void*> > & conflicts, 
		 const Point & p,
		 Cell_handle c, Cell_handle & ac, int & i)
  // 2d case
  // p is in conflict with c
  // finds the set conflicts of cells in conflict with p
  // gives a cell ac having a facet on the boundary of conflicts
  // and the index i of its facet on the boundary
{
  if ( ( conflicts.find( (void *) &(*c) ) ) != conflicts.end() )
      return;   // c was already found

  (void) conflicts.insert( (void *) &(*c) );

  for ( int j=0; j<3; j++ ) {
    if ( side_of_circle( c->neighbor(j), 3, p ) 
	 ==  ON_BOUNDED_SIDE ) {
      find_conflicts_2(conflicts, p, c->neighbor(j), ac, i);
    }
    else {
      ac = c;
      i = j;
    }
  }
}// find_conflicts_2

template < class Gt, class Tds >
Bounded_side
Delaunay_triangulation_3<Gt,Tds>::
side_of_sphere(Cell_handle c, const Point & p) const
{
  CGAL_triangulation_precondition( dimension() == 3 );
  int i3;
  if ( ! c->has_vertex( infinite_vertex(), i3 ) ) 
    return Bounded_side( geom_traits().side_of_oriented_sphere
			 (c->vertex(0)->point(),
			  c->vertex(1)->point(),
			  c->vertex(2)->point(),
			  c->vertex(3)->point(),p) );
//     Oriented_side
//       o = geom_traits().side_of_oriented_sphere(c->vertex(0)->point(),
// 						c->vertex(1)->point(),
// 						c->vertex(2)->point(),
// 						c->vertex(3)->point(),p);
//     return Bounded_side(o);
  // else infinite cell :
  int i0,i1,i2;
  if ( (i3%2) == 1 ) {
    i0 = (i3+1)&3;
    i1 = (i3+2)&3;
    i2 = (i3+3)&3;
  }
  else {
    i0 = (i3+2)&3;
    i1 = (i3+1)&3;
    i2 = (i3+3)&3;
  }
  Orientation
    o = geom_traits().orientation(c->vertex(i0)->point(),
				  c->vertex(i1)->point(),
				  c->vertex(i2)->point(),
				  p);
  if (o != ZERO)
    return Bounded_side(o);

  return Bounded_side( geom_traits().side_of_oriented_circle
		       ( c->vertex(i0)->point(), 
			 c->vertex(i1)->point(),
			 c->vertex(i2)->point(),
			 p ) );
//     {
//       Oriented_side s = 
// 	geom_traits().side_of_oriented_circle
// 	( c->vertex(i0)->point(),
// 	  c->vertex(i1)->point(),
// 	  c->vertex(i2)->point(),
// 	  p );
//       return ( (s == ON_NEGATIVE_SIDE) ? ON_UNBOUNDED_SIDE :
// 	       (s == ON_POSITIVE_SIDE) ? ON_BOUNDED_SIDE :
// 	       ON_BOUNDARY );
//     }
}// end side of sphere

template < class Gt, class Tds >
Bounded_side
Delaunay_triangulation_3<Gt,Tds>::
side_of_sphere(Vertex_handle v0, 
	       Vertex_handle v1, 
	       Vertex_handle v2, 
	       Vertex_handle v3, 
	       const Point & p) const
  // duplication of code with the other side_of_sphere should (?) be fixed 
{
  CGAL_triangulation_precondition( dimension() == 3 );
  Vertex_handle v[4] = { v0, v1, v2, v3 };
  int i;
  int i0,i1,i2;
  for ( i=0; i<4; i++) {
    if ( is_infinite( v[i] ) ) {
      if ( (i%2) == 1 ) {
	i0 = (i+1)&3;
	i1 = (i+2)&3;
	i2 = (i+3)&3;
      }
      else {
	i0 = (i+2)&3;
	i1 = (i+1)&3;
	i2 = (i+3)&3;
      }
      Orientation
	o = geom_traits().orientation(v[i0]->point(),
				      v[i1]->point(),
				      v[i2]->point(),
				      p);
      if (o != ZERO)
	return Bounded_side(o);

      return Bounded_side( geom_traits().side_of_oriented_circle
			   ( v[i0]->point(), 
			     v[i1]->point(),
			     v[i2]->point(),
			      p ) );
    }
  }
  
  // all vertices are finite
  return Bounded_side( geom_traits().side_of_oriented_sphere
		       ( v[0]->point(),
			 v[1]->point(),
			 v[2]->point(),
			 v[3]->point(), p) );
}// end side of sphere

template < class Gt, class Tds >
Bounded_side
Delaunay_triangulation_3<Gt,Tds>::
side_of_circle(Cell_handle c, int i, const Point & p) const
  // precondition : dimension >=2
  // in dimension 3, - for a finite facet
  // returns ON_BOUNDARY if the point lies on the circle,
  // ON_UNBOUNDED_SIDE when exterior, ON_BOUNDED_SIDE
  // interior
  // for an infinite facet, considers the plane defined by the
  // adjacent finite facet of the same cell, and does the same as in 
  // dimension 2 in this plane
  // in dimension 2, for an infinite facet
  // in this case, returns ON_BOUNDARY if the point lies on the 
  // finite edge (endpoints included) 
  // ON_BOUNDED_SIDE for a point in the open half-plane
  // ON_UNBOUNDED_SIDE elsewhere
{
  CGAL_triangulation_precondition( dimension() >= 2 );
  int i3 = 5;

  if ( dimension() == 2 ) {
    CGAL_triangulation_precondition( i == 3 );
    // the triangulation is supposed to be valid, ie the facet
    // with vertices 0 1 2 in this order is positively oriented
    if ( ! c->has_vertex( infinite_vertex(), i3 ) ) 
      return Bounded_side( geom_traits().side_of_oriented_circle
			   (c->vertex(0)->point(),
			    c->vertex(1)->point(),
			    c->vertex(2)->point(),
			    p) );
//       Oriented_side
// 	o = geom_traits().side_of_oriented_circle(c->vertex(0)->point(),
// 						  c->vertex(1)->point(),
// 						  c->vertex(2)->point(),
// 						  p);
//       //       return ( (o == ON_NEGATIVE_SIDE) ? ON_UNBOUNDED_SIDE :
// 	       (o == ON_POSITIVE_SIDE) ? ON_BOUNDED_SIDE :
// 	       ON_BOUNDARY );
    // else infinite facet
    // v1, v2 finite vertices of the facet such that v1,v2,infinite
    // is positively oriented
    Vertex_handle 
      v1 = c->vertex( ccw(i3) ),
      v2 = c->vertex( cw(i3) );
    // does not work in dimension 3 :
    // we need a fourth point to look at orientation with respect
    // to v1v2
    Cell_handle n = c->neighbor(i3);
    Orientation o =
      geom_traits().orientation_in_plane( v1->point(), 
					  v2->point(), 
					  n->vertex(n->index(c))->point(),
					  p );
    if ( o != ZERO ) return Bounded_side( -o );
    // because p is in f iff
    // is does not lie on the same side of v1v2 as vn
    int i_e;
    Locate_type lt;
    // case when p collinear with v1v2
    return side_of_segment( p,
			    v1->point(), v2->point(),
			    lt, i_e );
//     switch (o) {
//     case POSITIVE:
//       // p lies on the same side of v1v2 as vn, so not in f
//       {
// 	return ON_UNBOUNDED_SIDE;
//       }
//     case NEGATIVE:
//       // p lies in f
//       { 
// 	return ON_BOUNDED_SIDE;
//       }
//     case ZERO:
//       // p collinear with v1v2
//       {
// 	int i_e;
// 	Locate_type lt;
// // 	Bounded_side side = 
// // 	  side_of_segment( p,
// // 			   v1->point(), v2->point(),
// // 			   lt, i_e );
// 	if ( side_of_segment( p,
// 			      v1->point(), v2->point(),
// 			      lt, i_e ) == ON_UNBOUNDED_SIDE )
// 	  // p lies on the line defined by the finite edge, but
// 	  // not in edge v1v2
// 	  return ON_UNBOUNDED_SIDE;
// 	// else p lies in edge v1v2 (including v1 or v2)
// 	return ON_BOUNDARY;
//       }
//     }// switch o
  }// dim 2

  // else dimension == 3
  CGAL_triangulation_precondition( (i >= 0) && (i < 4) );
  if ( ( ! c->has_vertex(infinite_vertex(),i3) ) || ( i3 != i ) ) {
    // finite facet
    // initialization of i0 i1 i2, vertices of the facet positively 
    // oriented (if the triangulation is valid)
    int i0 = (i>0) ? 0 : 1;
    int i1 = (i>1) ? 1 : 2;
    int i2 = (i>2) ? 2 : 3;
    CGAL_triangulation_precondition( geom_traits().orientation
				     (c->vertex(i0)->point(),
				      c->vertex(i1)->point(),
				      c->vertex(i2)->point(),
				      p) == COPLANAR );
    return Bounded_side ( geom_traits().side_of_oriented_circle
			  (c->vertex(i0)->point(),
			   c->vertex(i1)->point(),
			   c->vertex(i2)->point(),
			   p) );
//     Oriented_side
//       o = geom_traits().side_of_oriented_circle(c->vertex(i0)->point(),
// 						c->vertex(i1)->point(),
// 						c->vertex(i2)->point(),
// 						p);
//     return ( (o == ON_NEGATIVE_SIDE) ? ON_UNBOUNDED_SIDE :
// 	     (o == ON_POSITIVE_SIDE) ? ON_BOUNDED_SIDE :
// 	     ON_BOUNDARY );
  }

  //else infinite facet
  // v1, v2 finite vertices of the facet such that v1,v2,infinite
  // is positively oriented
  Vertex_handle 
    v1 = c->vertex( next_around_edge(i3,i) ),
    v2 = c->vertex( next_around_edge(i,i3) );
  Orientation o =
    geom_traits().orientation_in_plane( v1->point(),
					v2->point(),
					c->vertex(i)->point(),
					p );
  // then the code is duplicated from 2d case
  if ( o != ZERO ) return Bounded_side( -o );
  // because p is in f iff 
  // it is not on the same side of v1v2 as c->vertex(i)
  int i_e;
  Locate_type lt;
  // case when p collinear with v1v2
  return side_of_segment( p,
			  v1->point(), v2->point(),
			  lt, i_e );
//   switch (o) {
//   case POSITIVE:
//     // p lies on the same side of v1v2 as c->vertex(i), so not in f
//     {
//       return ON_UNBOUNDED_SIDE;
//     }
//   case NEGATIVE:
//     // p lies in f
//     { 
//       return ON_BOUNDED_SIDE;
//     }
//   case ZERO:
//     // p collinear with v1v2
//     {
//       int i_e;
//       Locate_type lt;
// //       Bounded_side side = 
// // 	side_of_segment( p,
// // 			 v1->point(), v2->point(),
// // 			 lt, i_e );
//       if ( side_of_segment( p,
// 			    v1->point(), v2->point(),
// 			    lt, i_e ) == ON_UNBOUNDED_SIDE )
// 	// p lies on the line defined by the finite edge, but
// 	// not in edge v1v2
// 	return ON_UNBOUNDED_SIDE;
//       // else p lies in edge v1v2 (including v1 or v2)
//       return ON_BOUNDARY;
//     }
//   }// switch o
//   // end infinite facet
//   return ON_BOUNDARY; // to avoid warning with egcs
}// side_of_circle

template < class Gt, class Tds >
bool
Delaunay_triangulation_3<Gt,Tds>::
is_valid(bool verbose, int level) const
{
  if ( ! tds().is_valid(verbose,level) ) {
    if (verbose) { std::cerr << "invalid data structure" << std::endl; }
    CGAL_triangulation_assertion(false); return false;
  }
    
  if ( &(*infinite_vertex()) == NULL ) {
    if (verbose) { std::cerr << "no infinite vertex" << std::endl; }
    CGAL_triangulation_assertion(false); return false;
  }

  int i;

  switch ( dimension() ) {
  case 3:
    {
      Cell_iterator it;
      for ( it = finite_cells_begin(); it != cells_end(); ++it ) {
	is_valid_finite((*it).handle());
	for ( i=0; i<4; i++ ) {
	  if ( side_of_sphere
	       ( (*it).handle(), 
		 it->vertex( (it->neighbor(i))->index((*it).handle() ) )
		 ->point() )
	       == ON_BOUNDED_SIDE ) {
	    if (verbose) { 
	      std::cerr << "non-empty sphere " << std::endl;
	    }
	    CGAL_triangulation_assertion(false); return false;
	  }
	}
      }
      break;
    }
  case 2:
    {
      Facet_iterator it;
      for ( it = finite_facets_begin(); it != facets_end(); ++it ) {
	is_valid_finite((*it).first);
	for ( i=0; i<2; i++ ) {
	  if ( side_of_circle
	       ( (*it).first, 3,
		 (*it).first
		 ->vertex( (((*it).first)->neighbor(i))
			   ->index((*it).first) )->point() )
	       == ON_BOUNDED_SIDE ) {
	    if (verbose) { 
	      std::cerr << "non-empty circle " << std::endl;
	    }
	    CGAL_triangulation_assertion(false); return false;
	  }
	}
      }
      break;
    }
  case 1:
    {
      Edge_iterator it;
      for ( it = finite_edges_begin(); it != edges_end(); ++it ) {
	is_valid_finite((*it).first);
      }
      break;
    }
  }
  if (verbose) { std::cerr << "Delaunay valid triangulation" << std::endl;}
  return true;
}

template < class Gt, class Tds >
bool
Delaunay_triangulation_3<Gt,Tds>::
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
  switch ( dimension() ) {
  case 3:
    {
      if ( ! is_infinite(c) ) {
	is_valid_finite(c,verbose,level);
	for ( i=0; i<4; i++ ) {
	  if ( side_of_sphere
	       ( c, c->vertex( (c->neighbor(i))->index(c) )->point() )
	       == ON_BOUNDED_SIDE ) {
	    if (verbose) { 
	      std::cerr << "non-empty sphere " << std::endl;
	    }
	    CGAL_triangulation_assertion(false); return false;
	  }
	}
      }
      break;
    }
  case 2:
    {
      if ( ! is_infinite(c,3) ) {
	for ( i=0; i<2; i++ ) {
	  if ( side_of_circle
	       ( c , 3, c->vertex(c->neighbor(i)->index(c))->point() )
	       == ON_BOUNDED_SIDE ) {
	    if (verbose) { 
	      std::cerr << "non-empty circle " << std::endl;
	    }
	    CGAL_triangulation_assertion(false); return false;
	  }
	}
      }
      break;
    }
  }
  if (verbose) { std::cerr << "Delaunay valid cell" << std::endl;}
  return true;
}

CGAL_END_NAMESPACE

#endif // CGAL_DELAUNAY_TRIANGULATION_3_H
