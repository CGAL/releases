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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/bops_simple_polygons_2.h
// package       : bops (1.0.5)
// source        : include/CGAL/bops_simple_polygons_2.h
// revision      : $Revision: 1.0.5 $
// revision_date : $Date: Tue Jun 30 19:04:32 MET DST 1998  $
// author(s)     :        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BOPS_SIMPLE_POLYGONS_2_H
#define CGAL_BOPS_SIMPLE_POLYGONS_2_H

//#define CGAL__BOPS_DEBUG_ON
//#define CGAL__DCEL_DEBUG_ON
//#define CGAL__DCEL__V2E_DEBUG_ON
//#define CGAL__INTERSECTING_POLYGONS_DEBUG_ON

#include <list.h>
#include <vector.h>
#include <CGAL/bops_dcel.h>
#include <CGAL/nsquare_intersecting.h>
#include <CGAL/intersecting_polygons.h>

template<class I>
class CGAL_Bops_Simple_Polygons_2 : public I {
public:
  typedef typename I::R                         R;
  typedef typename I::Point                     Point_2;
  typedef typename I::Segment                   Segment_2;
  typedef typename I::Output_polygon_container  Polygon_Container;
  typedef typename I::Output_polygon            Polygon_2;
  typedef typename I::Output_object_container   Output_container;

  typedef typename Output_container::const_iterator    result_iterator;
  typedef typename Output_container::size_type         size_type;

  result_iterator begin() const { return _result.begin(); }
  result_iterator end() const { return _result.end(); }
  const Output_container& result() const { return _result; }
  size_type size() const { return _result.size(); }
  bool empty() const { return _result.empty(); }
  

  typedef CGAL_Bops_dcel<I>                Dcel;
  typedef typename Dcel::const_faces_iterator       face_iterator;
  typedef typename Dcel::const_edges_iterator       edge_iterator;
  typedef typename Dcel::const_vertices_iterator    vertex_iterator;
      
  typedef CGAL__intersecting_polygons<R, Polygon_Container> Intersect_Polygons;

  bool operation() {
    if( !_init ) return false;
    create_dcel();
    unmark ();
    perform(); // call of child-object
    return empty();
  }


  CGAL_Bops_Simple_Polygons_2() {
    marked_vector_init();
    _pgon_intersection_type= is_empty;
    _init= false;
  }


  bool do_intersect() const {
    return _init ? ( _pgon_intersection_type > 0) : false; }

  CGAL_Bops_Simple_Polygons_2(const Polygon_2& pgon1, const Polygon_2& pgon2)
    : _pgon1(pgon1), _pgon2(pgon2)
  {
      _inter_res= Intersect_Polygons(pgon1,pgon2);
      if( _inter_res.size() > 0 )
          _pgon_intersection_type= is_intersection; // Intersection
      else
          _pgon_intersection_type= calc_intersection_type();

#   ifdef CGAL__BOPS_DEBUG_ON
    cout << "_inter_res.size()="  << _inter_res.size() << endl;
    cout << "intersection_type= " << _pgon_intersection_type << endl;
#   endif // CGAL__BOPS_DEBUG_ON

    marked_vector_init();
    _init= true;
  }
 
     
  virtual ~CGAL_Bops_Simple_Polygons_2() {}

protected:

  virtual void perform(void) {};
  enum Intersection_type {
    is_empty         = 0,
    is_identical     = 1,
    A_is_subset_of_B = 2,
    B_is_subset_of_A = 3,
    is_intersection  = 4
  };

  int calc_intersection_type(int) const {
     typename I::Bbox a_box= I::get_Bbox(_pgon1);
     typename I::Bbox b_box= I::get_Bbox(_pgon2);

     if( a_box == b_box ) {
       if( _pgon1 == _pgon2 ) return is_identical;
     }
     if( !I::do_overlap(a_box, b_box) ) return is_empty;

     if( I::box_is_contained_in_box( a_box, b_box) )
       return A_is_subset_of_B;
     if( I::box_is_contained_in_box( b_box, a_box) )
       return B_is_subset_of_A;

     typename Polygon_Container::const_iterator it;
     int sum1= 0, n1= _pgon1.size();
     for( it= _pgon1.vertices_begin(); it != _pgon1.vertices_end(); it++)
       sum1 += I::has_on_bounded_side(_pgon2, *it) ? +1 : -1;

     if( sum1 ==  n1 || sum1 == -n1 ) {
       int sum2= 0, n2= _pgon2.size();
       for( it= _pgon2.vertices_begin(); it != _pgon2.vertices_end(); it++)
         sum2 += I::has_on_bounded_side(_pgon1,*it) ? +1 : -1;
       if( sum2 ==  n2|| sum2 == -n2) {
         if( sum1 == -n1 && sum2 == -n2 ) // polygons are separated
           // iff no intersections occur, otherwise return 4
           return !_inter_res.size() ? is_empty : is_intersection;
         if( sum1 == n1 && sum2 == -n2 ) // A is subset B
           return A_is_subset_of_B; 
         if( sum1 == -n1 && sum2 == n2 ) // B is subset A
           return B_is_subset_of_A; 
       }
     }

     return is_intersection; // intersections occur
  }

  Intersection_type calc_intersection_type(void) const {
    return (Intersection_type)calc_intersection_type(0);
  }

  void create_dcel(void) {
    /* built up the graph (step 2 in README) */
    vector<Point_2> ptlst;
    list< pair<int,int> > edlst;

    _inter_res.get_graph_information(ptlst,edlst);
#   ifdef CGAL__BOPS_DEBUG_ON
      cout << "after _inter_res.get_graph_information(ptlst,edlst);" << endl;
      print(cout, "ptlst:", ptlst.begin(), ptlst.end());
      print(cout, "edlst:", edlst.begin(), edlst.end());
      cout << flush;
#   endif //CGAL__BOPS_DEBUG_ON

    dcel.insert(edlst, ptlst);
#   ifdef CGAL__BOPS_DEBUG_ON
      cout << endl << "after dcel.insert(edlst, ptlst)" << endl;
      print(cout, "E", dcel.begin(), dcel.end() );
      print(cout, "V", dcel.vertex_begin(), dcel.vertex_end() );
      print(cout, "F", dcel.face_begin(), dcel.face_end() );
      cout << flush;
#   endif
    marked_vector_init();

    /* coloring the dcel */
    list<Point_2> pts_on_A;
    list<Point_2> pts_on_B;


    pts_on_A = _inter_res.get_color_informationA();
    dcel.colorize(pts_on_A, CGAL__RED);
    pts_on_B = _inter_res.get_color_informationB();
    dcel.colorize(pts_on_B, CGAL__BLACK);


#   ifdef CGAL__BOPS_DEBUG_ON
      cout << endl << "after dcel.colorize()" << endl;
      print(cout, "E", dcel.begin(), dcel.end() );
      print(cout, "V", dcel.vertex_begin(), dcel.vertex_end() );
      print(cout, "F", dcel.face_begin(), dcel.face_end() );
      cout << flush;
#   endif
  }

  int walk_around(face_iterator face, list<Point_2>& result) const
  {
    /*
       traverses a face in the DCEL and puts the vertices as points in
       into a list. These points define a polygon.
       Additionally, the visited edges will be marked in the marked-vector.
       The size of the marked-vector should be at least the number of edges
       in the DCEL, i.e. marked.size() >= dcel.number_of_edges
       (The result is always be ordered clockwise.)
    */
  
    int n= 0;
    vertex_iterator v0, v; 
    edge_iterator e, a= dcel.begin(face);
    mark(a);
    v0= ((*a).F1() == face) ? (*a).V1() : (*a).V2();
    result.push_back(dcel.point(v0)); n++;
    mark(v0);
    for( e= dcel.next(a,face); e != a; e= dcel.next(e, face) ) {
      mark(e);
      v= (*e).opposite_vertex( v0 );
      mark(v);
      result.push_back(dcel.point(v)); n++;
      v0= v;
    }
  
    return n;
  }


  Polygon_2 walk_around(face_iterator face, bool ccw = true) const {
    /*
       traverses a face in the DCEL and puts the vertices as points in
       into a polygon.
       Additionally, the visited edges will be marked in the marked-vector.
       The size of the marked-vector should be at least the number of edges
       in the DCEL, i.e. marked.size() >= dcel.number_of_edges
       (The result is always be ordered clockwise.)
    */
    list<Point_2> pt_list;
    if( walk_around( face, pt_list) )
      return ccw ? Polygon_2(pt_list.rbegin(), pt_list.rend()) :
                   Polygon_2(pt_list.begin(),  pt_list.end()) ;
  
    return Polygon_2();
  }

  void marked_vector_init() {
    marked= vector<bool>(dcel.number_of_edges());
    marked_vertex= vector<bool>(dcel.number_of_vertices());
  }

  void unmark () {
    fill(marked.begin(), marked.end(), false);
    fill(marked_vertex.begin(), marked_vertex.end(), false);
  }

  void mark   (vertex_iterator v) const {
    (vector<bool>::reference)marked_vertex[(*v).index()]= true;
  }
  void unmark (vertex_iterator v) const {
    (vector<bool>::reference)marked_vertex[(*v).index()]= false;
  }

  bool is_unmarked (vertex_iterator v) const {
    return marked_vertex[(*v).index()] == false;
  }
  bool is_marked (vertex_iterator v) const { return !is_unmarked(v); }

  bool is_unmarked (edge_iterator e) const {
    return marked[(*e).index()] == false;
  }
  bool is_marked (edge_iterator e) const { return !is_unmarked(e); }

  void mark   (edge_iterator e) const {
    (vector<bool>::reference)marked[(*e).index()]= true;
  }
  void unmark (edge_iterator e) const {
    (vector<bool>::reference)marked[(*e).index()]= false;
  }

  void mark   (int index) const {
    (vector<bool>::reference)marked[index]= true;
  }
  void unmark (int index) const {
    (vector<bool>::reference)marked[index]= false;
  }

  bool _init;
  Polygon_2 _pgon1, _pgon2;
  Intersection_type _pgon_intersection_type;
  Dcel dcel;
  vector<bool> marked;        // marked list for edges
  vector<bool> marked_vertex; // marked list for vertices
  Output_container  _result;  // list<CGAL_Object> _result;
  Intersect_Polygons _inter_res;
};


template<class I>
struct CGAL_Bops_Simple_Polygons_2_Intersection
       : public CGAL_Bops_Simple_Polygons_2<I>
{
  typedef typename CGAL_Bops_Simple_Polygons_2<I>::Polygon_2 Polygon_2;
  CGAL_Bops_Simple_Polygons_2_Intersection() {}

  CGAL_Bops_Simple_Polygons_2_Intersection(
       const Polygon_2& pgon1, const Polygon_2& pgon2)
       : CGAL_Bops_Simple_Polygons_2<I>( pgon1, pgon2) {
  }

  void perform(void);
};


template<class I>
struct CGAL_Bops_Simple_Polygons_2_Difference
       : public CGAL_Bops_Simple_Polygons_2<I>
{
  typedef typename CGAL_Bops_Simple_Polygons_2<I>::Polygon_2 Polygon_2;
  CGAL_Bops_Simple_Polygons_2_Difference() {}

  CGAL_Bops_Simple_Polygons_2_Difference(
       const Polygon_2& pgon1, const Polygon_2& pgon2)
       : CGAL_Bops_Simple_Polygons_2<I>( pgon1, pgon2) {
  }

  void perform(void);
};


template<class I>
struct CGAL_Bops_Simple_Polygons_2_Union
       : public CGAL_Bops_Simple_Polygons_2<I>
{
  typedef typename CGAL_Bops_Simple_Polygons_2<I>::Polygon_2 Polygon_2;
  CGAL_Bops_Simple_Polygons_2_Union() {}

  CGAL_Bops_Simple_Polygons_2_Union(
       const Polygon_2& pgon1, const Polygon_2& pgon2)
       : CGAL_Bops_Simple_Polygons_2<I>( pgon1, pgon2) {
  }

  void perform(void);
};


#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/bops_simple_polygons_2.C>
#endif

#endif /* CGAL_BOPS_SIMPLE_POLYGONS_2_H */
