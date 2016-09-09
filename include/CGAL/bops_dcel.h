//  -*- Mode: c++ -*-
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
// file          : include/CGAL/bops_dcel.h
// package       : bops (1.1.2)
// source        : include/CGAL/bops_dcel.h
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:28:50 MET 1998  $
// author(s)     :             Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_H
#define CGAL__DCEL_H

#include <CGAL/bops_dcel_defs.h>
#include <CGAL/bops_dcel_base.h>
#include <CGAL/min_sqr_distance.h>


#ifdef CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS
#define CGAL_CFG_RETURN_TYPE_BUG_2  /* to avoid troubles with sun-pro */
#endif

template<class NT>
inline bool CGAL__number_type_is_non_exact(const NT&) { return false; }

inline bool CGAL__number_type_is_non_exact(const double&) { return true; }
inline bool CGAL__number_type_is_non_exact(const float&) { return true; }


/*
  Implementation of the Double Connected Edge List (DCEL)
  -------------------------------------------------------

  template <class I>
  class CGAL__Dcel : public CGAL__Dcel_base<I>;

  template <class I>
  struct CGAL_Bops_dcel : public CGAL__Dcel< CGAL__Dcel_defs<I> >;

*/



template <class I>
class CGAL__Dcel : public CGAL__Dcel_base<I>
{
public:
  typedef CGAL__Dcel_base<I>  dcel_base;
  typedef typename I::R R;
  typedef typename I::Point Point;
  typedef pair<int,int> epair;

  CGAL__Dcel() { use_epsilon= false; }
  CGAL__Dcel(const CGAL__Dcel<I>& dl) { *this= dl; }
  CGAL__Dcel(const list<epair>& eds, const list<Point>& pts ) {
    use_epsilon= false;
    insert(eds,pts);
  }
  CGAL__Dcel(const list<epair>& eds, const vector<Point>& pts ) {
    use_epsilon= false;
    insert(eds,pts);
  }

# ifdef  CGAL_CFG_RETURN_TYPE_BUG_2
  bool colorize(const list<Point>& pgon, const CGAL__Dcel_Color& col) {
    __point_list= &pgon;
    return colorize(col);
  }
# else
  bool colorize(const list<Point>& pgon, const CGAL__Dcel_Color& col);
# endif  



  Point point(const_vertices_iterator v) const {
    return (*v).point();
  }

  const_vertices_iterator find(const Point& pt) const {
     //CGAL__Dcel_point_compare<I> pred(pt);
     //CGAL__Dcel_point_compare<Point, CGAL__Dcel_vertex_type<I> > pred(pt);
     //return  find_if(_v_list.begin(), _v_list.end(), pred );
     for(const_vertices_iterator it= _v_list.begin(); it != _v_list.end(); it++)
       if( compare_points(pt, (*it).point()) ) return it;
     return _v_list.end();
  }

  
  const_vertices_iterator null_vertex(void) const {
     return _v_list.end();
  }

private:
  double pts_epsilon;
  bool   use_epsilon;

  bool compare_points(const Point& p1, const Point& p2) const {
    if( use_epsilon ) {
      return CGAL_abs(CGAL_to_double(p1.x()-p2.x())) < pts_epsilon &&
             CGAL_abs(CGAL_to_double(p1.y()-p2.y())) < pts_epsilon;
    }
    else
      return p1 == p2;
  }

  void insert_points(const list<Point>& points) {
    if( (use_epsilon= CGAL__number_type_is_non_exact(R::FT(0))) ) {
      /* calculates epsilon for non-exact number types */
      I traits;
      pts_epsilon= minimal_square_distance(
		    points.begin(), points.end(), traits);
      pts_epsilon= sqrt(pts_epsilon)/3.0;
    }

    //vector<vertex_iterator> c_it; /* help-array */
    /* insert vertices (also in help array) */
    _v_list.reserve(points.size());
    int n= 0;
    list<typename I::Point>::const_iterator it;
    for( it= points.begin(); it != points.end(); it++ )          
        c_it.push_back( insert_point( *it, n++ ) );
  
    CGAL__BOPS_DCEL_DEBUG_ITERATOR("c_it", c_it.begin(), c_it.end() );
#   ifdef CGAL__BOPS_DEBUG_ON
    print(cout, "c_it", c_it.begin(), c_it.end() );
    print(cout, "V", vertex_begin(), vertex_end() );
    print(cout, "P", _point_list.begin(), _point_list.end() ); // from dcel-base
    copy(_point_list.begin(), _point_list.end(),
         ostream_iterator<Point>(cout, "\n" ) );
#   endif
    return;
  }

  void insert_points(const vector<Point>& points)
  {
    typedef typename R::FT FT;
    if( (use_epsilon= CGAL__number_type_is_non_exact(FT(0))) ) {
      /* calculates epsilon for non-exact number types */
      I traits;
      pts_epsilon= minimal_square_distance(
		    points.begin(), points.end(), traits);
      pts_epsilon= sqrt(pts_epsilon)/3.0;
    }
    // vector<vertex_iterator> c_it; /* help-array */
    /* insert vertices (also in help array) */
    _v_list.reserve(points.size());
    int n= 0;
    vector< typename I::Point >::const_iterator it;
    for( it= points.begin(); it != points.end(); it++ ) 
        c_it.push_back( insert_point( *it, n++ ) );

    CGAL__BOPS_DCEL_DEBUG_ITERATOR("c_it", c_it.begin(), c_it.end() );
#   ifdef CGAL__BOPS_DEBUG_ON
    print(cout, "c_it", c_it.begin(), c_it.end() );
    print(cout, "V", vertex_begin(), vertex_end() );
    print(cout, "P", _point_list.begin(), _point_list.end() );
#   endif
    return;
  }

  vector<const_vertices_iterator> c_it; /* help-array */

public:
  void insert(const list< epair >& eds, const list< Point >& pts ) {
      insert_points(pts);
#     ifdef  CGAL_CFG_RETURN_TYPE_BUG_2
      // because of compiler (g++, Solaris)  problems,
      // we have to do this:
        __edges= &eds;
        insert_edges();
#     else
        insert_edges(eds);
#     endif  
      c_it= vector<const_vertices_iterator>();
  }

  void insert(const list< epair >& eds, const vector< Point >& pts ) {
      insert_points(pts);
#     ifdef  CGAL_CFG_RETURN_TYPE_BUG_2
      // because of compiler (g++, Solaris)  problems,
      // we have to do this
        __edges= &eds;
        insert_edges();
#     else
        insert_edges(eds);
#     endif  
      c_it= vector<const_vertices_iterator>();
  }

private:

  const_vertices_iterator insert_point( const Point& pt, int index ) {
    return insert_new_vertex(pt, index);
  }
  
  const_vertices_iterator insert_new_vertex(
    const Point& pt,
    int index,
    CGAL__Dcel_Color col = CGAL__NO_COLOR
  )
  {
     const_vertices_iterator it= find(pt);

     if( it == null_vertex() ) {
       /* vertex does not exist, hence append vertex */
       const_points_iterator pt_it= dcel_base::insert(pt);
       //it= dcel_base::insert( CGAL__Dcel_vertex_type<I>(pt, index, col) );
       it= dcel_base::insert( CGAL__Dcel_vertex_type<I>(pt_it, index, col) );
     }

     return it;
  }

private:
#ifdef  CGAL_CFG_RETURN_TYPE_BUG_2
  bool colorize(const CGAL__Dcel_Color& col);
  void insert_edges();
  const list<Point>* __point_list;
  const list<epair>* __edges;
#else
  void insert_edges(const list<epair>& eds);
#endif

};

template <class I>
struct CGAL_Bops_dcel : public CGAL__Dcel< CGAL__Dcel_defs<I> > {
  typedef CGAL__Dcel< CGAL__Dcel_defs<I> >  dcel;
  typedef typename dcel::const_edges_iterator    edge_iterator;
  typedef typename dcel::const_faces_iterator    face_iterator;
  typedef typename dcel::const_vertices_iterator vertex_iterator;
};


#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/bops_dcel.C>
#endif 

#endif /* CGAL__DCEL_H */

