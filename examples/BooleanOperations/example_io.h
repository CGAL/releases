//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL basic library.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//
 
// Source: example_io.h
// Author: Wolfgang Freiseisen
 

#ifndef EXAMPLE_IO_H
#define EXAMPLE_IO_H

ostream& operator<<(ostream& o, CGAL_Orientation orient) {
  if(orient == CGAL_CLOCKWISE )
      o << "CLW";
  else if(orient == CGAL_COUNTERCLOCKWISE )
      o << "CCW";
  else /* CGAL_COLLINEAR */
      o << "COL";
  return o;
}

ostream& operator<<(ostream& o, Polygon_2 p) {
  Polygon_2::Vertex_const_iterator it;
  if( p.is_convex() )      o << "convex,";
  /* else if( p.is_simple() ) o << "simple,";
  else                     o << "NOT simple,"; */
  else o << "simple,";
  o << " n=" << p.size() << ", " << p.orientation();
  for( it= p.vertices_begin(); it != p.vertices_end(); it++) 
    o  << ", " << *it;
  return o;
}

void test_input(vector<Point_2>& vA, vector<Point_2>& vB) {
  vA[0]= Point_2(2,4);
  vA[1]= Point_2(0,3);
  vA[2]= Point_2(1,1);
  vA[3]= Point_2(2,3);
  vA[4]= Point_2(3,1);
  vA[5]= Point_2(4,3);
  vB[0]= Point_2(0,2);
  vB[1]= Point_2(0,0);
  vB[2]= Point_2(5,0);
  vB[3]= Point_2(5,2);
}

void test_result_output( const list<CGAL_Object>& result ) {
  Point_2 pt;
  Segment_2 seg;
  Polygon_2 pgon;

  list<CGAL_Object>::const_iterator it;
  cout << endl << "RESULT: (size=" << result.size() << ")" << endl;

  for( it= result.begin(); it != result.end(); it++) {
    if( CGAL_assign( pgon, *it) ) { /* polygon */
      //cout << "POLYGON" << endl;
      cout << "pgon " << pgon << endl;
    }
    else if( CGAL_assign( seg, *it) ) { /* segment */
      cout << "seg  " << seg << endl;
    }
    else if( CGAL_assign( pt, *it) )  { /* point */
      cout << "pt   " << pt << endl;
    }
    else { /* nothing */
      cout << "undefined object " << endl;
    }
  }
  cout << endl << endl << endl;
  
  return;
}

bool read_point(Point_2 &pt)
{
    long x, y, w;
    cin >> x >> y >> w;
    if (!cin.good())
	return false;
    pt = Point_2(TestNum(x), TestNum(y), TestNum(w));
    return true;
}

bool read_pgn(Polygon_2 &pgn)
{
    int n, i;
    cin >> n;
    if (!cin.good())
	return false;
    if (n < 3) {
	cin.clear(ios::failbit);
	return false;
    }
    vector<Point_2> points(n);
    for (i=0; i<n; i++) {
	if (!read_point(points[i]))
	    return false;
    }
    pgn = Polygon_2(points.begin(), points.end());
    return true;
}

#endif // EXAMPLE_IO_H
