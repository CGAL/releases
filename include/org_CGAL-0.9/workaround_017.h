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



// Implementation: Workaround for C++-style casts
// file  : include/CGAL/workaround_017.h
// author: Sven Schoenherr
// $Id: workaround_017.h,v 1.1 1997/04/25 14:13:12 sven Exp $
//

#if ! ( CGAL_WORKAROUND_017_H)
#define CGAL_WORKAROUND_017_H 1

// workaround for C++-style casts
#if defined( CGAL_WORKAROUND_017)
#  define      CGAL_static_cast(type,expr) (type)( expr)
#  define       CGAL_const_cast(type,expr) (type)( expr)
#  define CGAL_reinterpret_cast(type,expr) (type)( expr)
#  define     CGAL_dynamic_cast(type,expr) (type)( expr)
#else
#  define      CGAL_static_cast(type,expr)      static_cast< type>(expr)
#  define       CGAL_const_cast(type,expr)       const_cast< type>(expr)
#  define CGAL_reinterpret_cast(type,expr) reinterpret_cast< type>(expr)
#  define     CGAL_dynamic_cast(type,expr)     dynamic_cast< type>(expr)
#endif // defined( CGAL_WORKAROUND_017_H)

#endif // CGAL_WORKAROUND_017_H
