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


// Author: Geert-Jan Giezeman

#ifndef CGAL_WORKAROUND_010_H
#define CGAL_WORKAROUND_010_H

/*
This is a workaround for compilers that do not allow to return a type derived
in a special way from a template parameter:
template <class A>
A::X foo(A a) {}

gcc 2.7.2 and a Sun compiler have this feature.
*/

#ifdef CGAL_WORKAROUND_010
template <class R>
struct R_FT_Return_type
{
    R_FT_Return_type(R::FT xt) {_xt = xt; }
    operator R::FT() const { return _xt; }
private:
    R::FT _xt;
};

#define R_FT_return(template_parameter) R_FT_Return_type<template_parameter>

template <class R>
struct R_RT_Return_type
{
    R_RT_Return_type(R::RT xt) {_xt = xt; }
    operator R::RT() const { return _xt; }
private:
    R::RT _xt;
};

#define R_RT_return(template_parameter) R_RT_Return_type<template_parameter>

#else
#define R_FT_return(template_parameter) template_parameter::FT

#define R_RT_return(template_parameter) template_parameter::RT
#endif

#endif

