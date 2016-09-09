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


// file  : include/CGAL/Member_function_pointer.h
// source: include/CGAL/Member_function_pointer.h
// author: Gabriele Neyer
// $Revision: 1.2 $
// $Date: 1997/05/21 14:54:05 $

#ifndef __CGAL_Member_function_pointer__
#define __CGAL_Member_function_pointer__

#include <CGAL/config.h>    // line added by Wieger

#ifdef  CGAL_TEMPLATE_FUNCTION_POINTER_WORKAROUND
// Macro for the definition of a Member Function Pointer.
#define CGAL_Member_function_pointer(structName, str,type,name) \
struct structName \
{ \
    typedef type (str::*pmfi)() const;\
    typedef type value_type; \
    typedef str  struct_type; \
    static inline pmfi member() { return &str::name; } \
};
#define CGAL_Use_member_function_pointer(structName, str,type,name) structName

#else

#define CGAL_Member_function_pointer(structName, str,type,name)
#define CGAL_Use_member_function_pointer(structName, str,type,name) \
  str::name

#endif


// Macro for the definition of a Member Pointer.
#define CGAL_Member_pointer(structName, str,type,name) \
struct structName \
{ \
    static inline type str::* member() { return &str::name; } \
};

#endif
