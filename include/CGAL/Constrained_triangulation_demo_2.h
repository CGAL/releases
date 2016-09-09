// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/Constrained_triangulation_demo_2.h
// package       : Triangulation_2 (5.18)
// source        : $RCSfile: Constrained_triangulation_demo_2.h,v $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/07/01 07:57:03 $
//
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
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
