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


// file  : include/CGAL/Optimisation_circle_2.C
// author: Sven Schönherr

// Class implementation (continued)
// ================================
// includes
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#  include <CGAL/optimisation_assertions.h>
#endif

// I/O
// ---
template < class _R >
ostream&
operator << ( ostream& os, CGAL_Optimisation_circle_2<_R> const& c)
{
  switch ( CGAL_get_mode( os)) {

    case CGAL_IO::PRETTY:
      os << "CGAL_Optimisation_circle_2( "
	 << c.center() << ", "
	 << c.squared_radius() << ')';
      break;

    case CGAL_IO::ASCII:
      os << c.center() << ' ' << c.squared_radius();
      break;

    case CGAL_IO::BINARY:
      os << c.center();
      CGAL_write( os, c.squared_radius());
      break;

    default:
      CGAL_optimisation_assertion_msg( false, "CGAL_get_mode( os) invalid!");
      break; }

  return( os);
}

template < class _R >
istream&
operator >> ( istream& is, CGAL_Optimisation_circle_2<_R>& c)
{
    typedef typename  CGAL_Optimisation_circle_2<_R>::Point     Point;
    typedef typename  CGAL_Optimisation_circle_2<_R>::Distance  Distance;

    switch ( CGAL_get_mode( is)) {

      case CGAL_IO::PRETTY:
	cerr << endl;
	cerr << "Stream must be in ascii or binary mode" << endl;
	break;

      case CGAL_IO::ASCII: {
	Point     center;
	Distance  squared_radius;
	is >> center >> squared_radius;
	c.set( center, squared_radius); }
	break;

      case CGAL_IO::BINARY: {
	Point     center;
	Distance  squared_radius;
	is >> center;
	CGAL_read( is, squared_radius);
	c.set( center, squared_radius); }
	break;

      default:
	CGAL_optimisation_assertion_msg( false, "CGAL_get_mode( is) invalid!");
	break; }

    return( is);
}

// ===== EOF ==================================================================
