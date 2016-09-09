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


// Source: Integer.h
// Author: Stefan Schirra

#ifndef CGAL_INTEGER_H
#define CGAL_INTEGER_H

#include <CGAL/IO/io_tags.h>
#include <CGAL/number_type_tags.h>

#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 349063
#include <LEDA/REDEFINE_NAMES.h>
#endif

#include <LEDA/integer.h>

inline
double
CGAL_to_double(const integer & i)
{
  return i.todouble();
}

inline
CGAL_Number_tag
CGAL_number_type_tag(const integer& )
{
  return CGAL_Number_tag();
}

inline
bool
CGAL_is_finite(const integer &)
{
  return true;
}

inline
bool
CGAL_is_valid(const integer &)
{
  return true;
}

inline
CGAL_io_Operator
CGAL_io_tag(const integer &)
{
  return CGAL_io_Operator(); 
}

#if LEDA_ROOT_INCL_ID == 349063
#undef LEDA_ROOT_INCL_ID
#include <LEDA/UNDEFINE_NAMES.h>
#endif

#endif // CGAL_INTEGER_H
