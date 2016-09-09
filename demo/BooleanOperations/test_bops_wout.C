//  -*- Mode: c++ -*-
// ============================================================================
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
// file          : demo/BooleanOperations/test_bops_wout.C
// source        : demo/BooleanOperations/test_bops_wout.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:05 MET 1998  $
// author(s)     :                        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/test_bops.h>

//#include <CGAL/IO/ostream.h>
//#include <fstream.h>
//#include <CGAL/IO/new_iostream.h>
#define red leda_red
#define black leda_black
#include <CGAL/IO/Window_stream.h>
#undef red 
#undef black


CGAL_Window_stream& operator <<(CGAL_Window_stream& w, const Polygon_2& pgon);
CGAL_Window_stream& operator <<(CGAL_Window_stream& w, const CGAL_Object& obj);

template <class T>
class CGAL_Window_ostream_iterator : public output_iterator
{
protected:
    CGAL_Window_stream* stream;
public:
    CGAL_Window_ostream_iterator(CGAL_Window_stream& s) : stream(&s) {}
    CGAL_Window_ostream_iterator<T>& operator=(const T& value)
    {
        *stream << value;
        return *this;
    }
    CGAL_Window_ostream_iterator<T>& operator*() { return *this; }
    CGAL_Window_ostream_iterator<T>& operator++() { return *this; }
    CGAL_Window_ostream_iterator<T>& operator++(int) { return *this; }
};


CGAL_Window_stream& operator <<(CGAL_Window_stream& w, const Polygon_2& pgon) {
  CGAL_Window_ostream_iterator< Segment_2 > w_seg(w);
  copy(pgon.edges_begin(), pgon.edges_end(), w_seg);
  return w;
}


CGAL_Window_stream& operator <<(CGAL_Window_stream& w, const CGAL_Object& obj) {
  Point_2 pt;
  Segment_2 seg;
  Polygon_2 pgon;
  if( CGAL_assign( pgon, obj) )     { /* polygon */ w << pgon; }
  else if( CGAL_assign( seg, obj) ) { /* segment */ w << seg; }
  else if( CGAL_assign( pt, obj) )  { /* point */   w << pt; }
  return w;
}





void click_to_continue(CGAL_Window_stream& W)
{
  double x, y;
  W.read_mouse(x,y);
}

#define wout (*W_global_ptr)
CGAL_Window_stream *W_global_ptr;
CGAL_Window_ostream_iterator< CGAL_Object >   winout_obj(wout);
CGAL_Window_ostream_iterator< Segment_2 > winout_seg(wout);


void test_result_win_output( const list<CGAL_Object>& result ) {
  Point_2 pt;
  Segment_2 seg;
  Polygon_2 pgon;
 
  list<CGAL_Object>::const_iterator it;
  wout << CGAL_RED;
  for( it= result.begin(); it != result.end(); it++) {
    if( CGAL_assign( pgon, *it) )     { /* polygon */ wout << pgon; }
    else if( CGAL_assign( seg, *it) ) { /* segment */ wout << seg; }
    else if( CGAL_assign( pt, *it) )  { /* point */   wout << pt; }
  }
 
  return;
}



int test_intersection(const Polygon_2& A, const Polygon_2& B) {
  cout << "INTERSECTION" << endl;
  wout << CGAL_BLACK << A << CGAL_BLUE << B;

  list<CGAL_Object> result;
  CGAL_intersection(A,B, back_inserter(result));
  test_result_output(result);
  //copy(result.begin(), result.end(), winout_obj);
  test_result_win_output( result );
  
  return 0;
}


int test_difference(const Polygon_2& A, const Polygon_2& B) {
  cout << "DIFFERENCE" << endl;
  wout << CGAL_BLACK << A << CGAL_BLUE << B;

  list<CGAL_Object> result;
  CGAL_difference(A,B, back_inserter(result));
  test_result_output(result);
  //copy(result.begin(), result.end(), winout_obj);
  test_result_win_output( result );
  
  return 0;
}


int test_union(const Polygon_2& A, const Polygon_2& B) {

  cout << "UNION" << endl;
  wout << CGAL_BLACK << A << CGAL_BLUE << B;

  list<CGAL_Object> result;
  CGAL_union(A,B, back_inserter(result));
  test_result_output(result);
  //copy(result.begin(), result.end(), winout_obj);
  test_result_win_output( result );
  
  return 0;
}


int main( void )
{
  vector<Point_2> vA(6), vB(4);
  test_input( vA, vB);
  Polygon_2 A(vA.begin(), vA.end()), B(vB.begin(),vB.end());

  cout << "polygon A: " << A << endl;
  cout << "polygon B: " << B << endl;
 
  CGAL_Window_stream W(600,600);
  W_global_ptr = &W;
  W.init(-1,6,-1);
  W.clear();

  test_intersection(A,B);
  click_to_continue(W);
  test_union(A, B);
  click_to_continue(W);
  test_difference(A, B);
  click_to_continue(W);
  test_difference(B, A);
  click_to_continue(W);
  return 0;
}

