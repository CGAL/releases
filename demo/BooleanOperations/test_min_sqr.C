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
// file          : demo/BooleanOperations/test_min_sqr.C
// source        : demo/BooleanOperations/test_min_sqr.C
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:29:07 MET 1998  $
// author(s)     :                 Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <stdlib.h>
#include <math.h>
#include <CGAL/min_sqr_distance_traits.h>
#include <CGAL/min_sqr_distance.h>
#include <iostream.h>
#include <time.h>
#include <sys/timeb.h>
//extern int ftime(struct timeb *__tp);

struct Time {
  typedef unsigned long  seconds;
  typedef unsigned short milliseconds;
  struct timeb _t;

  milliseconds msec() const { return _t.millitm; }
  seconds sec() const { return _t.time; }
  Time() { set(); }
  Time( seconds s, milliseconds m) {
    _t.time= s;
    _t.millitm= m%1000;
  }

  Time( milliseconds m) {
    _t.time= m/1000;
    _t.millitm= m-sec();
  }
  Time(const Time& t) { _t= t._t; }
  Time& operator=(const Time& t) { _t= t._t; return *this; }

  Time operator-( const Time& t) const {
     seconds s= sec() - t.sec() - (msec() < t.msec());
     return Time( s, msec()-t.msec() );
  }
  void set() { ftime(&_t); }
  unsigned long get_msecs() const { return (unsigned long)(sec()*1000 + msec); }
};


ostream& operator<<(ostream& o, const Time& t) {
  o << (float)t.sec() + ((float)t.msec())/1000.;
  return o;
}


typedef double TestNum;  
double Random(double) { return drand48(); }
void Seed(long seed, double) { srand48(seed); }
typedef CGAL_Cartesian<TestNum>  R_type;
typedef min_sqr_distance_traits<R_type> Traits;
typedef Traits::Point Point;

#include <time.h>

int main(int argc, char *argv[]) {

  list<Point> L;
  int i, n= 24;
  if(argc > 1) n= atoi(argv[1]);
  const double rval= 1000;
  Seed(time(NULL), TestNum(0));
  for(i= 0; i < n; i++)
    L.push_back( Point(Random(TestNum(0))*rval,Random(TestNum(0))*rval) );

  Traits tr;

  cout << "n= " << n << endl;
  //long int t0= time(NULL);
  Time t0;
  t0.set();
  double d1= minimal_square_distance(L.begin(), L.end(), tr);
  //long int t1= time(NULL)-t0;
  Time t1;
  t1= t1 - t0;
  cout << "O(n log n): " << d1 << " (" << t1 << " sec)" << endl;

  t0.set();
  d1= minimal_square_distance(L.begin(), L.end(), tr);
  //long int t1= time(NULL)-t0;
  t1.set();
  t1= t1 - t0;
  cout << "O(n log n): " << d1 << " (" << t1 << " sec)" << endl;


  t0.set();
  d1= minimal_square_distance(L.begin(), L.end(), tr);
  //long int t1= time(NULL)-t0;
  t1.set();
  t1= t1 - t0;
  cout << "O(n log n): " << d1 << " (" << t1 << " sec)" << endl;

  t0.set();
  double d2= minimal_square_distance2(L.begin(), L.end(), tr);
  Time t2;
  //long int t2= time(NULL)-t0;
  t2= t2 - t0;
  cout << "O(n^2): " << d2 << " (" << t2 << " sec)" << endl;

  return 0;
}
