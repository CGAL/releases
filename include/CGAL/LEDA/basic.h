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
// file          : include/CGAL/LEDA/basic.h
// package       : cgal_window (1.0.4)
// revision      : 1.0.3
// revision_date : 25 June 2001
// author(s)     : Matthias Baesken, Algorithmic Solutions
//
// coordinator   : Matthias Baesken, Trier  (<baesken>) 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================



#ifndef CGAL_WINDOW_BASIC_H
#define CGAL_WINDOW_BASIC_H


// include system config file
#if defined(CGAL_USE_CGAL_HEADERS)
#include <CGAL/basic.h>
#else

#if !defined(CGAL_CLIB_STD) 
#if defined(_MSC_VER)
#define CGAL_CLIB_STD
#else
#define CGAL_CLIB_STD std
#endif
#endif

#endif


#include <CGAL/LEDA/system.h>

// include std header files

#include <iostream>
#include <iomanip>
#include <fstream>
#include <strstream>
#include <cstddef>
#include <cstdlib>
#include <cmath>


// include basic LEDA headers

#include <CGAL/LEDA/global.h>

#include <string>

namespace CGAL {

extern __exportF void leda_wait(double sec);  
/*{\Mfunc  suspends execution for $sec$ seconds.}*/

// maximal and minimal values for some numerical types

inline int    Max_Value(int& x)     { return x =  MAXINT;   }
inline int    Min_Value(int& x)     { return x = -MAXINT;   }
inline double Max_Value(double& x)  { return x =  MAXDOUBLE;}
inline double Min_Value(double& x)  { return x = -MAXDOUBLE;}

extern __exportF double truncate(double x, int k = 10);
/*{\Mfunc returns a double whose mantissa is truncated after $k-1$ bits after the binary point, i.e, if
$x \not= 0$ then the binary representation of the mantissa of the 
result has the form d.dddddddd, where the number of d's is equal to $k$. 
There is a corresponding function for
|integers|; it has no effect.}*/

}

#endif
