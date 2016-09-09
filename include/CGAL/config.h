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

#ifndef CGAL_CONFIG_H
#define CGAL_CONFIG_H

#define CGAL_VERSION 0.9

//----------------------------------------------------------------------//
//             flags for SGI/MIPSpro C++ x.x compilers
//----------------------------------------------------------------------//
#if defined(__sgi) && !defined(__GNUG__)
#define CGAL_WORKAROUND_001
#define CGAL_WORKAROUND_012
#define CGAL_WORKAROUND_017
#define CGAL_INCLUDE_TEMPLATE_CODE   // This should not be necessary!?!?!?
#define CGAL_NO_DEFAULTS_IN_FUNCTION_TEMPLATES

#include <sgidefs.h>

// SGI MIPSpro C++ 7.1 -32 compiler settings
#if _MIPS_SIM == _MIPS_SIM_ABI32
#endif

// SGI MIPSpro C++ 7.1 -n32 compiler settings
#if _MIPS_SIM == _MIPS_SIM_NABI32
#endif

// SGI MIPSpro C++ 7.1 -64 compiler settings
#if _MIPS_SIM == _MIPS_SIM_ABI64
#endif

// SGI MIPSpro C++ 4.0 compiler settings
#if _MIPS_SIM != _MIPS_SIM_ABI32 && _MIPS_SIM != _MIPS_SIM_NABI32 && _MIPS_SIM != _MIPS_SIM_ABI64
#define CGAL_TEMPLATE_FUNCTION_POINTER_WORKAROUND
#endif

#endif //  __sgi

//----------------------------------------------------------------------//
//             flags for g++ 2.7.2 compiler
//----------------------------------------------------------------------//
#ifdef __GNUG__
#define CGAL_BOOL_KEYWORD
#define CGAL_WORKAROUND_003
#define CGAL_WORKAROUND_004
#define CGAL_WORKAROUND_005
#define CGAL_WORKAROUND_007
#define CGAL_WORKAROUND_008
#define CGAL_WORKAROUND_010
#define CGAL_WORKAROUND_013
#define CGAL_WORKAROUND_015
#define CGAL_WORKAROUND_017
#define CGAL_INCLUDE_TEMPLATE_CODE
#define CGAL_TEMPLATE_FUNCTION_POINTER_WORKAROUND
#endif // __GNUG__

//----------------------------------------------------------------------//
//             flags for SunPro C++ 4.1 compiler
//----------------------------------------------------------------------//
#ifdef __SUNPRO_CC
#define CGAL_WORKAROUND_002
#define CGAL_WORKAROUND_006
#define CGAL_WORKAROUND_010
#define CGAL_WORKAROUND_012
#define CGAL_WORKAROUND_017
#define CGAL_INCLUDE_TEMPLATE_CODE   // This should not be necessary!?!?!?
#define CGAL_TEMPLATE_FUNCTION_POINTER_WORKAROUND
#define CGAL_DEFAULTS_IN_FUNCTION_TEMPLATES_WORKAROUND
#endif // __SUNPRO_CC

//----------------------------------------------------------------------//
//             flags for IBM C Set++ compiler (not supported)
//----------------------------------------------------------------------//
#if defined(__xlC__)
#define CGAL_WORKAROUND_012
#define CGAL_WORKAROUND_017
#define CGAL_NO_DEFAULTS_IN_FUNCTION_TEMPLATES
#endif

//----------------------------------------------------------------------//
//             include files
//----------------------------------------------------------------------//

#ifndef CGAL_WORKAROUND_012
#include <std/typeinfo.h>
#endif  // CGAL_WORKAROUND_012

#include <CGAL/workaround_010.h>
#include <CGAL/workaround_017.h>
#include <CGAL/workaround_stl.h>
#include <CGAL/bool.h>

//----------------------------------------------------------------------//
//             general macro's and typedefs
//----------------------------------------------------------------------//
#ifndef CGAL_TYPENAME
#define typename
#endif

#ifndef CGAL_EXPLICIT
#define explicit
#endif

#endif

