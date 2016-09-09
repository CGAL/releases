/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: bops_simple_polygons_2.h 
// Author: Wolfgang Freiseisen
 
#ifndef CGAL_BOPS_SIMPLE_POLYGONS_2_H
#define CGAL_BOPS_SIMPLE_POLYGONS_2_H

//#define CGAL__BOPS_DEBUG_ON
//#define CGAL__DCEL_DEBUG_ON
//#define CGAL__DCEL__V2E_DEBUG_ON
//#define CGAL__INTERSECTING_POLYGONS_DEBUG_ON

#include <list.h>
#include <vector.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Object.h>
#define CGAL_POINT_DEFINED
#include <CGAL/bops_dcel.h>

#include <CGAL/bops_2.h>


template<class R, class Polygon_Container>
class CGAL_Bops_Simple_Polygons_2 {
public:
  typedef CGAL_Point_2< R >                   Point_2;
  typedef CGAL_Segment_2< R >                 Segment_2;
  typedef CGAL_Polygon_2< R, Polygon_Container > Polygon_2;

  typedef list<CGAL_Object>::const_iterator    result_iterator;
  typedef list<CGAL_Object>::size_type         size_type;

  result_iterator begin() const { return _result.begin(); }
  result_iterator end() const { return _result.end(); }
  const list<CGAL_Object>& result() const { return _result; }
  size_type size() const { return _result.size(); }
  bool empty() const { return _result.empty(); }
  

  typedef CGAL__Dcel< R >                      Dcel;
  typedef CGAL__Dcel< R >::face_iterator       face_iterator;
  typedef CGAL__Dcel< R >::edge_iterator       edge_iterator;
  typedef CGAL__Dcel< R >::vertex_iterator     vertex_iterator;
      
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
    _pgon_intersection_type= 0;
    _init= false;
  }


  bool do_intersect() const {
    return _init ? ( _pgon_intersection_type > 0) : false; }

  CGAL_Bops_Simple_Polygons_2(const Polygon_2& pgon1, const Polygon_2& pgon2)
    : _pgon1(pgon1), _pgon2(pgon2)
  {
    _inter_res= Intersect_Polygons(pgon1,pgon2);
#ifdef CGAL__BOPS_DEBUG_ON
    marked= vector<bool>(1);
    marked= vector<bool>(2);
    marked= vector<bool>(3);
#endif // CGAL__BOPS_DEBUG_ON
    _pgon_intersection_type= calc_intersection_type();
#ifdef CGAL__BOPS_DEBUG_ON
    cout << "intersection_type= " << _pgon_intersection_type << endl;
#endif // CGAL__BOPS_DEBUG_ON
    marked_vector_init();
    _init= true;
  }
 
     
  virtual ~CGAL_Bops_Simple_Polygons_2() {}

protected:

  virtual void perform(void) {};

  int calc_intersection_type(void) const;
  /* intersection types: 
     0 empty
     1 identical
     2 A_subset_of_B
     3 B_subset_of_A
     4 intersection
  */

  void create_dcel(void) {
    /* built up the graph (step 2 in README) */
    deque< CGAL_Point_2<R> > ptlst;
    list< pair<int,int> > edlst;

    _inter_res.get_graph_information(ptlst,edlst);
#ifdef CGAL__BOPS_DEBUG_ON
    cout << "after _inter_res.get_graph_information(ptlst,edlst);" << endl;
    print(cout, "ptlst:", ptlst.begin(), ptlst.end());
    print(cout, "edlst:", edlst.begin(), edlst.end());
#endif //CGAL__BOPS_DEBUG_ON
    dcel.insert(edlst, ptlst);
    marked_vector_init();

    /* coloring the dcel */
    list<CGAL_Point_2<R> > pts_on_A;
    list<CGAL_Point_2<R> > pts_on_B;

    pts_on_A = _inter_res.get_color_informationA();
    dcel.colorize(pts_on_A, CGAL__RED);
    pts_on_B = _inter_res.get_color_informationB();
    dcel.colorize(pts_on_B, CGAL__BLACK);

#ifdef CGAL__BOPS_DEBUG_ON
   print(cout, "E", dcel.begin(), dcel.end() );
   print(cout, "V", dcel.vertex_begin(), dcel.vertex_end() );
   print(cout, "F", dcel.face_begin(), dcel.face_end() );
#endif
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
  mark((*a).index());
  v0= ((*a).F1() == face) ? (*a).V1() : (*a).V2();
  result.push_back(dcel.point(v0)); n++;
  mark(v0);
  for( e= dcel.next(a,face); e != a; e= dcel.next(e, face) )
  {
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
  int _pgon_intersection_type;
  Dcel dcel;
  vector<bool> marked;        // marked list for edges
  vector<bool> marked_vertex; // marked list for vertices
  list<CGAL_Object> _result;
  Intersect_Polygons _inter_res;
};


template<class R, class Polygon_Container>
struct CGAL_Bops_Simple_Polygons_2_Intersection
       : public CGAL_Bops_Simple_Polygons_2 <R, Polygon_Container>
{
  typedef CGAL_Polygon_2< R, Polygon_Container > Polygon_2;
  CGAL_Bops_Simple_Polygons_2_Intersection() {}

  CGAL_Bops_Simple_Polygons_2_Intersection(
       const Polygon_2& pgon1, const Polygon_2& pgon2)
       : CGAL_Bops_Simple_Polygons_2<R, Polygon_Container>( pgon1, pgon2) {
  }

  void perform(void);
};


template<class R, class Polygon_Container>
struct CGAL_Bops_Simple_Polygons_2_Difference
       : public CGAL_Bops_Simple_Polygons_2 <R, Polygon_Container>
{
  typedef CGAL_Polygon_2< R, Polygon_Container > Polygon_2;
  CGAL_Bops_Simple_Polygons_2_Difference() {}

  CGAL_Bops_Simple_Polygons_2_Difference(
       const Polygon_2& pgon1, const Polygon_2& pgon2)
       : CGAL_Bops_Simple_Polygons_2<R, Polygon_Container>( pgon1, pgon2) {
  }

  void perform(void);
};


template<class R, class Polygon_Container>
struct CGAL_Bops_Simple_Polygons_2_Union
       : public CGAL_Bops_Simple_Polygons_2 <R, Polygon_Container>
{
  typedef CGAL_Polygon_2< R, Polygon_Container > Polygon_2;
  CGAL_Bops_Simple_Polygons_2_Union() {}

  CGAL_Bops_Simple_Polygons_2_Union(
       const Polygon_2& pgon1, const Polygon_2& pgon2)
       : CGAL_Bops_Simple_Polygons_2<R, Polygon_Container>( pgon1, pgon2) {
  }

  void perform(void);
};


#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include <CGAL/bops_simple_polygons_2.C>
#endif

#endif /* CGAL_BOPS_SIMPLE_POLYGONS_2_H */
