// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/workaround_return_type.h
// package       : Configuration (1.54)
// source        :
// revision      :
// revision_date :
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Utrecht University
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_WORKAROUND_RETURN_TYPE_H
#define CGAL_WORKAROUND_RETURN_TYPE_H

/*
This is a workaround for compilers that do not allow to return a type derived
in a special way from a template parameter:
template <class A>
A::X foo(A a) {}

gcc 2.7.2 and a Sun compiler have this feature.
*/

#ifdef CGAL_CFG_RETURN_TYPE_BUG_1
template <class R>
struct R_FT_Return_type
{
    R_FT_Return_type(typename R::FT xt) {_xt = xt; }
    operator typename R::FT() const { return _xt; }
private:
   typename R::FT _xt;
};

#define R_FT_return(template_parameter) R_FT_Return_type<template_parameter>

template <class R>
struct R_RT_Return_type
{
    R_RT_Return_type(typename R::RT xt) {_xt = xt; }
    operator typename R::RT() const { return _xt; }
private:
    typename R::RT _xt;
};

#define R_RT_return(template_parameter) R_RT_Return_type<template_parameter>

#else
#define R_FT_return(template_parameter) typename template_parameter::FT

#define R_RT_return(template_parameter) typename template_parameter::RT
#endif

#endif // CGAL_WORKAROUND_RETURN_TYPE_H

