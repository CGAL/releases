// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Kernel_d/Pair_d.h
// package       : Kernel_d (0.9.47)
// chapter       : Basic
//
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/07/16 08:17:16 $
//
// author(s)     : Michael Seel
// coordinator   : Susan Hert
//
// implementation: a pair of points
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_PAIR_D_H
#define CGAL_PAIR_D_H

#include <CGAL/basic.h>
#include <CGAL/Handle_for.h>

CGAL_BEGIN_NAMESPACE

template <class R> class Segment_d;
template <class R> class Ray_d;
template <class R> class Line_d;

template <class R> 
class Pair_d : public Ref_counted { 
  typedef Pair_d<R> Self;
  typedef typename R::Point_d Point_d;
  typedef typename R::Vector_d Vector_d;
  typedef typename R::Direction_d Direction_d;
  Point_d _p[2];

  friend class Line_d<R>; 
  friend class Ray_d<R>; 
  friend class Segment_d<R>; 
   
/* Any line object in $d$ - space is defined by two points |_p1| and |_p2|
respectively. There exists an orientation from _p1 to _p2. */

public: 
Pair_d(int d = 0) { _p[0]=_p[1]=Point_d(d); }

Pair_d(const Point_d& p, const Point_d& q)
{ CGAL_assertion_msg((p.dimension() == q.dimension()), 
  "Pair_d::constructor: source and target must have the same dimension."); 
  _p[0]=p; _p[1]=q;
}

bool is_degenerate() const
{ return (_p[0] == _p[1]); }

Vector_d vector() const 
{ return (_p[1] - _p[0]); }

Direction_d direction() const
{ return vector().direction(); }

void read(std::istream& is)
{ 
  switch( is.iword(CGAL::IO::mode) ) {
    case CGAL::IO::ASCII :
      is >> _p[0] >> _p[1]; break;
    case CGAL::IO::BINARY :
      CGAL::read(is, _p[0]); CGAL::read(is, _p[1]); break;
    default:
    CGAL_assertion_msg(0,"\nStream must be in ascii or binary mode\n"); 
  }
}

void print(std::ostream& os, char* _name) const
{ 
  switch( os.iword(CGAL::IO::mode) ) {
    case CGAL::IO::ASCII :
      os << _p[0] << " " <<  _p[1]; break;
    case CGAL::IO::BINARY :
      CGAL::write(os, _p[0]); CGAL::write(os, _p[1]); break;
    default :
      os << _name << "(" << _p[0] << ", " << _p[1] << ")"; break;
  }
}

}; // Pair_d<R>

CGAL_END_NAMESPACE
#endif //CGAL_PAIR_D_H

