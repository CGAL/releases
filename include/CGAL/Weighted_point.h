// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Weighted_point.h
// package       : Triangulation_2 (5.18)
// source        : $RCSfile: Weighted_point.h,v $
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/07/05 14:57:52 $
// author(s)     : Mariette Yvinec
//                 Sylvain Pion
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_WEIGHTED_POINT_H
#define CGAL_WEIGHTED_POINT_H

CGAL_BEGIN_NAMESPACE

template < class Pt, class We >
class Weighted_point : public Pt
{
public:
  typedef We Weight;
  typedef Pt Point;
  typedef typename Point::RT RT;

  Weighted_point (const Point &p=Point(), const Weight &w = Weight(0))
      : Point(p), _weight(w) {}

  Point point() const
  {
      return (Point)*this;
  }

  Weight weight() const
  {
      return _weight;
  }

// The following power() member functions are not used at the moment.
// They belong to the traits class anyway.
//
//  Weight power(const Point &p)
//  {	
//      return squared_distance(*this, p) - weight();
//  }
// 
//  Weight power(const Weighted_point &p)
//  {	
//      return squared_distance(*this, p) - weight() - p.weight();
//  }

private:
  Weight _weight;
};


template < class Point, class Weight >
std::ostream &
operator<<(std::ostream &os, const Weighted_point<Point,Weight> &p)
{
	return os << p.point() << " " << p.weight();
}

template < class Point, class Weight >
std::istream &
operator>>(std::istream &is, Weighted_point<Point,Weight> &wp)
{
	Weight w;
	Point p;
	is >> p >> w;
	wp = Weighted_point<Point,Weight>(p,w);
	return is;
}

CGAL_END_NAMESPACE

#endif // CGAL_WEIGHTED_POINT_H
