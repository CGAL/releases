// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Pm_tentuple.h
// package       : pm (3.07)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//                 Iddo Hanniel
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_PM_TENTUPLE_H
#define CGAL_PM_TENTUPLE_H


CGAL_BEGIN_NAMESPACE


template <class F0,class F1,class F2,class F3,class F4,class F5,class F6,class F7,class F8,class F9>
class Pm_tentuple : public Rep
{
public:
	F0 e0;
	F1 e1;
	F2 e2;
	F3 e3;
	F4 e4;
	F5 e5;
	F6 e6;
	F7 e7;
	F8 e8;
	F9 e9;
	
	Pm_tentuple()
	{}
	Pm_tentuple(const F0 & a0, const F1 & a1, const F2 & a2, const F3 & a3,const F4 & a4, const F5 & a5, const F6 & a6, const F7 & a7, const F8 & a8, const F9 & a9)
		: e0(a0),e1(a1),e2(a2),e3(a3),e4(a4),e5(a5),e6(a6),e7(a7),e8(a8),e9(a9)
	{}
	Pm_tentuple(const Pm_tentuple<F0,F1,F2,F3,F4,F5,F6,F7,F8,F9> & a)
		: e0(a.e0),e1(a.e1),e2(a.e2),e3(a.e3),e4(a.e4),e5(a.e5),e6(a.e6),e7(a.e7),e8(a.e8),e9(a.e9)
	{}
	~Pm_tentuple()
	{}
};


CGAL_END_NAMESPACE

#endif











