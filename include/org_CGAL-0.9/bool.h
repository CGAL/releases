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

#ifndef CGAL_BOOL_H
#define CGAL_BOOL_H

//---------------------------------------------------------------------------//
//                 bool conflict between libraries
//---------------------------------------------------------------------------//
// For compilers not yet supporting the Boolean type in C++
// there is a conflict between the definitions of the keyword bool in 
// different libraries, especially LEDA and STL. LEDA defines the type bool 
// as unsigned char. If you want to use both libraries in combination you 
// have to make some modifications (either in LEDA or in STL):
//
//---------------------------------------------------------------------------//
// 1) modify STL
//---------------------------------------------------------------------------//
//
// - Make sure that the flag CGAL_USE_LEDA_BOOL is set in your makefile.
//
// - Remove the definition of bool in the file bool.h from STL and replace 
//   it with #include <LEDA/bool.h>
//
//---------------------------------------------------------------------------//
// 2) modify LEDA
//---------------------------------------------------------------------------//
//
// - Make sure that the flag CGAL_USE_LEDA_BOOL is not set in your makefile
//
// - Remove the definition of bool in the file <LEDA/bool.h> and replace it 
//   with the definition of bool in the version of STL you use, e.g.
//
//   typedef int bool;
//   #define false 0
//   #define true 1
//
// - Recompile LEDA
//
//---------------------------------------------------------------------------//

#if !defined(CGAL_BOOL_KEYWORD) 
#if defined(CGAL_USE_LEDA_BOOL)
#include <LEDA/basic.h>
#else
#define LEDA_BOOL_H
#include <bool.h>
#endif
#endif // CGAL_BOOL_KEYWORD

#endif // CGAL_BOOL_H
