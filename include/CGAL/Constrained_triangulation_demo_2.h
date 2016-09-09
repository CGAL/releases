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
// file          : include/CGAL/Constrained_triangulation_demo_2.h
// package       : Triangulation (3.17)
// source        : $RCSfile: Constrained_triangulation_demo_2.h,v $
// revision      : $Revision: 1.1.1.4 $
// revision_date : $Date: 1999/03/11 16:48:11 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CONSTRAINED_TRIANGULATION_DEMO_2_H
#define CGAL_CONSTRAINED_TRIANGULATION_DEMO_2_H

#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Constrained_triangulation_sweep_demo_2.h>
#include <CGAL/IO/Window_stream.h>

CGAL_BEGIN_NAMESPACE

template < class Gt,class Tds>
class Constrained_triangulation_demo_2
  : public Constrained_triangulation_2<Gt,Tds>
{
public:
  typedef Constrained_triangulation_2<Gt,Tds> Constrained_triangulation;
  typedef Constrained_triangulation_sweep_demo_2<Gt,Tds>  Sweep_demo;
  typedef typename Gt::Segment Segment;
  typedef Window_stream Window_stream;

Constrained_triangulation_demo_2() :  
  Constrained_triangulation_2<Gt,Tds>() {} 
  
Constrained_triangulation_demo_2(const Gt& gt=Gt()) 
  : Constrained_triangulation_2<Gt,Tds>(gt) {}
  

Constrained_triangulation_demo_2(Window_stream& W,
				     list<Constraint>& lc, const Gt& gt=Gt()) 
  : Constrained_triangulation_2<Gt,Tds>(gt)
{
  Sweep_demo  sweep(W,lc, gt);
  Constrained_triangulation_2<Gt,Tds> Tr( sweep.vertex(), gt);
  swap(Tr);
  CGAL_triangulation_postcondition( is_valid() );
}

};

CGAL_END_NAMESPACE

#endif //CGAL_CONSTRAINED_TRIANGULATION_DEMO_2_H
