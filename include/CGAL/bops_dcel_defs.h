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


// Source: dcel_defs.h
// Author: Wolfgang Freiseisen
 

#ifndef CGAL__DCEL_DEFS_H
#define CGAL__DCEL_DEFS_H

#ifndef CGAL_POINT_DEFINED
#define CGAL_POINT_DEFINED  // no TEST-Modus
#endif

#ifdef __GNUC__
#include <typeinfo>
#endif

#include <list.h>
#include <vector.h>
#include <deque.h>

#ifdef CGAL_POINT_DEFINED
                            /* with CGAL-POINTS */
//#define __BUILTIN_BOOL__
//#include <CGAL/Cartesian.h>
//#include <iostream.h>
//#include <CGAL/basic.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Object.h>

#define CGAL__Point_2     CGAL_Point_2<R>
#define CGAL__Segment_2   CGAL_Segment_2<R>

template<class R>
bool operator==(const CGAL_Object& o, const CGAL_Point_2<R>& pt) {
  CGAL_Point_2<R> pt_o;
  CGAL_assign(pt_o, o);
  return pt_o != pt;
}
//double CGAL_to_double(int i) { return (double)i; }

#else /* help-structures */
                            /* TESTING without CGAL-POINTS */

typedef pair<int,int>                     CGAL__Point_2;
typedef pair<CGAL__Point_2,CGAL__Point_2> CGAL__Segment_2;

#endif /* CGAL_POINT_DEFINED */


/* Colors for the DCEL */
class CGAL__Dcel_Color {
public:
  CGAL__Dcel_Color() : _c(0) {}
  CGAL__Dcel_Color( const CGAL__Dcel_Color& c ) : _c(c._c) {}
  CGAL__Dcel_Color( int c ) : _c(c) {}

  void operator=(int i) { _c= i; }
  void operator=(CGAL__Dcel_Color other) { _c= other._c; }
  operator int() const {return _c;}
  CGAL__Dcel_Color operator|( const CGAL__Dcel_Color& c) const {
    return CGAL__Dcel_Color( _c | c._c );
  }
private:
  int _c;
};

const CGAL__Dcel_Color   CGAL__NO_COLOR= 0;
const CGAL__Dcel_Color   CGAL__UNCOLORED= 0;
const CGAL__Dcel_Color   CGAL__RED= 1;
const CGAL__Dcel_Color   CGAL__BLACK= 2;
const CGAL__Dcel_Color   CGAL__RED_AND_BLACK= 3;
const CGAL__Dcel_Color   CGAL__TWICE_COLORED= 3;



class CGAL__Dcel_base;

class CGAL__Dcel_vertex_type;
class CGAL__Dcel_face_type;
class CGAL__Dcel_edge_type;

typedef const CGAL__Dcel_vertex_type* CGAL__Dcel_vertex;
typedef const CGAL__Dcel_face_type*   CGAL__Dcel_face;
typedef const CGAL__Dcel_edge_type*   CGAL__Dcel_edge;

#endif /* CGAL__DCEL_DEFS_H */
