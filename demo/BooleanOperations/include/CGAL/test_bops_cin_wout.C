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
// file          : demo/BooleanOperations/include/CGAL/test_bops_cin_wout.C
// source        : demo/BooleanOperations/include/CGAL/test_bops_cin_wout.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:02 MET 1998  $
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

//#include <CGAL/test_bops.h>

//#include <CGAL/IO/ostream.h>
//#include <fstream.h>
//#include <CGAL/IO/new_iostream.h>
#define red leda_red
#define black leda_black
#include <CGAL/IO/Window_stream.h>
#include <CGAL/IO/polygon_Window_stream.h>
#undef red 
#undef black


//CGAL_Window_stream& operator <<(CGAL_Window_stream& w, const Polygon_2& pgon);
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


CGAL_Window_stream& operator <<(
		CGAL_Window_stream& w,
		const Polygon_2& pgon)
{
	CGAL_Window_ostream_iterator< Segment_2 > w_seg(w);
	copy(pgon.edges_begin(), pgon.edges_end(), w_seg);
	return w;
}

void print_stream(CGAL_Window_stream& w, const Polygon_2& pgon)
{
	CGAL_Window_ostream_iterator< Segment_2 > w_seg(w);
	copy(pgon.edges_begin(), pgon.edges_end(), w_seg);
	return;
}                     

CGAL_Window_stream& operator <<(CGAL_Window_stream& w, const CGAL_Object& obj) {
  Point_2 pt;
  Segment_2 seg;
  Polygon_2 pgon;
  Iso_rectangle_2 irect;
  Triangle_2 triangle;
  if( CGAL_assign( pgon, obj) )          {
	/* polygon */
	print_stream(w,pgon);
	//w << pgon;
  }
  else if( CGAL_assign( irect, obj) )    { /* iso-rectangle */ w << irect; }
  else if( CGAL_assign( triangle, obj) ) { /* triangle */ w << triangle; }
  else if( CGAL_assign( seg, obj) )      { /* segment */ w << seg; }
  else if( CGAL_assign( pt, obj) )       { /* point */   w << pt; }
  return w;
}

#define wout (*W_global_ptr)
CGAL_Window_stream *W_global_ptr;
CGAL_Window_ostream_iterator< CGAL_Object >   winout_obj(wout);
CGAL_Window_ostream_iterator< Segment_2 > winout_seg(wout);

int click_to_continue(CGAL_Window_stream& W= wout)
{
  double x, y;
  return W.read_mouse(x,y);
}


void test_result_win_output_base( const list<CGAL_Object>& result ) {
  Point_2 pt;
  Segment_2 seg;
  Polygon_2 pgon;
  Iso_rectangle_2 irect;
  Triangle_2 triangle;
 
  list<CGAL_Object>::const_iterator it;
  wout << CGAL_RED;
  for( it= result.begin(); it != result.end(); it++) {
    if( CGAL_assign( pgon, *it) )          { /* polygon */ wout << pgon; }
    else if( CGAL_assign( irect, *it) )    { /* iso-rectangle */ wout << irect; }
    else if( CGAL_assign( triangle, *it) ) { /* triangle */ wout << triangle; }
    else if( CGAL_assign( seg, *it) )      { /* segment */ wout << seg; }
    else if( CGAL_assign( pt, *it) )       { /* point */   wout << pt; }
  }
 
  return;
}

template< class _polygon>
void test_result_win_output(
   const _polygon& A,
   const _polygon& B,
   const list<CGAL_Object>& result
)
{
  bool loop_on= true;
  wout.clear();
  wout << CGAL_BLACK << A << CGAL_BLUE << B;
  test_result_win_output_base(result);
  while( loop_on == true ) {
    switch( click_to_continue() ) {
      case -2: //middle button
        wout.clear();
        wout << CGAL_BLACK << A << CGAL_BLUE << B;
        break;
      case -3: //right button
        wout.clear();
        wout << CGAL_BLACK << A << CGAL_BLUE << B;
        test_result_win_output_base(result);
        break;
      case -1: //left button
      default:
        loop_on= false;
        //cout << "button= " << button << endl;
    }
  }
  return;
}


/*
    --------------------------------------------------------------------
       Polygons
    --------------------------------------------------------------------
*/

template< class _polygon>
void test_intersection(const _polygon& A, const _polygon& B) {
  wout << CGAL_BLACK << A << CGAL_BLUE << B;
  list<CGAL_Object> result;
  CGAL_intersection(A,B, back_inserter(result));
  test_result_output(result);
  test_result_win_output(A,B,result);
}


template< class _polygon>
void test_difference(const _polygon& A, const _polygon& B) {
  wout << CGAL_BLACK << A << CGAL_BLUE << B;
  list<CGAL_Object> result;
  CGAL_difference(A,B, back_inserter(result));
  test_result_output(result);
  test_result_win_output(A,B,result);
}


template< class _polygon>
void test_union(const _polygon& A, const _polygon& B) {
  wout << CGAL_BLACK << A << CGAL_BLUE << B;
  list<CGAL_Object> result;
  CGAL_union(A,B, back_inserter(result));
  test_result_output(result);
  test_result_win_output(A,B,result);
}



/*
    --------------------------------------------------------------------
       MAIN
    --------------------------------------------------------------------
*/

int main( int argc, char *argv[] )
{
  int arg= 0;
  if( argc > 1 ) {
    arg= atoi(argv[1]);
  }

  Polygon_2 A,B;

  if (!read_pgn(A)) {
	cerr << "Polygon A is wrong!" << endl;
	return 1;
  }
  // check counterclockwise orientation
  if ( A.orientation() == CGAL_CLOCKWISE) {
    A.reverse_orientation();
    cout << "orientation reversed" << endl;
  }
  cout << "polygon A: (BLACK) " << A << endl;

  if (!read_pgn(B)) {
	cerr << "Polygon B is wrong!" << endl;
	return 1;
  }
  // check counterclockwise orientation
  if ( B.orientation() == CGAL_CLOCKWISE) {
    B.reverse_orientation();
    cout << "orientation reversed" << endl;
  }
  cout << "polygon B: (BLUE) " << B << endl;
  
  // WINDOW-INIT
  float w = 600.0, h = 600.0;
  CGAL_Window_stream W(w,h);
  CGAL_cgalize(W);
  //double x_extension= 1.0;
  //double y_extension = x_extension * h / w;
  //W.init(-x_extension, x_extension, -y_extension);//(-1.0, 1.0, -1.0);
  W_global_ptr = &W;
  
  CGAL_Bbox_2 box_A= A.bbox();
  CGAL_Bbox_2 box_B= B.bbox();
  double xmin= min(box_A.xmin(), box_B.xmin());
  double xmax= max(box_A.xmax(), box_B.xmax());
  double ymin= min(box_A.ymin(), box_B.ymin());
  double ymax= max(box_A.ymax(), box_B.ymax());
  double dx=(xmax-xmin);
  double dy=(ymax-ymin);
  double d= max(dx,dy);
  dx *= 0.025;
  dy *= 0.025;
  W.init(xmin-dx,xmin+d+dx,ymin-dy);
  W.display();
  W.clear();
  wout << CGAL_BLACK << A << CGAL_BLUE << B;
  click_to_continue(W);

  switch( arg ) {
  case 1:
    cout << "INTERSECTION: " << endl;
    test_intersection(A,B);
    break;
  case 2:
    cout << "UNION: A + B " << endl;
    test_union(A, B);
    break;
  case 3:
    cout << "DIFFERENCE:  A - B" << endl;
    test_difference(A, B);
    break;
  case 4:
    cout << "DIFFERENCE:  B - A" << endl;
    test_difference(B, A);
    break;
  case 5:  // iso-rectangles
    //Iso_rectangle_2 rA, rB;
    if( A.size() != 4 )
      cout << "size of polygon A is NOT 4 (=" << A.size() << ")" <<endl;
    else if( B.size() != 4 )
      cout << "size of polygon B is NOT 4 (=" << B.size() << ")" <<endl;
    else {
      Polygon_2::Vertex_const_iterator it;
      it= A.vertices_begin();
      Iso_rectangle_2 rA(*it++, *++it);
      it= B.vertices_begin();
      Iso_rectangle_2 rB(*it++, *++it);
      cout << "ISO-RECT. INTERSECTION: " << endl;
      test_intersection(rA,rB);
      cout << "ISO-RECT. UNION: " << endl;
      test_union(rA,rB);
      cout << "ISO-RECT. DIFFERENCE: A-B" << endl;
      test_difference(rA,rB);
      cout << "ISO-RECT. DIFFERENCE: B-A" << endl;
      test_difference(rB,rA);
    }
    
    break;
  default:
 
    cout << "INTERSECTION: " << endl;
    test_intersection(A,B);
 
    cout << "UNION: A + B " << endl;
    test_union(A, B);
 
    cout << "DIFFERENCE:  A - B" << endl;
    test_difference(A, B);
 
    cout << "DIFFERENCE:  B - A" << endl;
    test_difference(B, A);
  }

  return 0;
}
