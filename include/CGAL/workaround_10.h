
//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Author: Geert-Jan Giezeman

#ifndef CGAL_WORKAROUND_10_H
#define CGAL_WORKAROUND_10_H

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
    operator R::FT() { return _xt; }
private:
    R::FT _xt;
};

#define R_FT_return(template_parameter) R_FT_Return_type<template_parameter>

template <class R>
struct R_RT_Return_type
{
    R_RT_Return_type(R::RT xt) {_xt = xt; }
    operator R::RT() { return _xt; }
private:
    R::RT _xt;
};

#define R_RT_return(template_parameter) R_RT_Return_type<template_parameter>

#else
#define R_FT_return(template_parameter) template_parameter::FT

#define R_RT_return(template_parameter) template_parameter::RT
#endif

#endif

