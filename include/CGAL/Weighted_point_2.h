// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Weighted_point_2.h
// package       : Triangulation (3.17)
// source        : $RCSfile: Weighted_point_2.h,v $
// revision      : $Revision: 1.1.1.7 $
// revision_date : $Date: 1999/05/11 08:44:32 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_WEIGHTED_POINT_2_H
#define CGAL_WEIGHTED_POINT_2_H

#include <CGAL/Triangulation_2.h>
#include <CGAL/Triangulation_euclidean_traits_2.h>

CGAL_BEGIN_NAMESPACE

template < class Pt, class We >
class Weighted_point_2 : public Pt
{
public:
  typedef We Weight;
  typedef Pt Point;
  typedef typename  Point::RT RT;
private:
	Weight _weight;

public: //constructors and destructors
  Weighted_point_2 ()
    : Point ()
  {
    _weight=Weight ( 0 ) ;
  }


  Weighted_point_2	( const Weighted_point_2 &p0)
  {
    Point::operator=(p0.point() );
    _weight=Weight( p0.weight() );
  }

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
	template <class Weight_0 >
	Weighted_point_2
	( const Weighted_point_2<  Point, Weight_0 > &p0) : Point(p0.point())
	{	_weight=Weight( p0.weight() );
	}
#endif

	Weighted_point_2 ( const Point &p )
		: Point ( p )
	{	_weight=Weight ( 0 ) ;
	}

	Weighted_point_2 ( const RT &x, const RT &y )
		: Point ( x, y )
	{	_weight=Weight ( 0 ) ;
	}

	Weighted_point_2 ( const Point &p, const Weight &_weight_ )
		: Point ( p )
	{	_weight=_weight_;
	}


public:
  // conversion from Weighted_point to Weight
	operator Weight() const
	{return weight();}

	Point point() const
	{	return (Point)*this;
	}

	Weight weight() const
	{	return _weight;
	}

	Weight power(const Point &p)
	{	
	  return square(p.x()-x()) + square(p.y()-y()) - weight();
	}

        Weight power(const Weighted_point_2 &p)
	{	
	  return square(p.x()-x()) + square(p.y()-y()) - weight() - p.weight();
	}



};


template < class Point, class Weight >
std::ostream &operator<<(
        std::ostream &os, const Weighted_point_2<Point,Weight> &p)
{
	return os << p.point() << " " << p.weight() ;
}

template < class Point, class Weight >
std::istream  &operator>>(
         std::istream  &is,  Weighted_point_2<Point,Weight> &p)
{
	Weight _weight_;
	Point _point_;
	is >> _point_  >> _weight_ ;
	p=Weighted_point_2<Point,Weight>( _point_, _weight_ );
	return is;
}

CGAL_END_NAMESPACE

#endif
