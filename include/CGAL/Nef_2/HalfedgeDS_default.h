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
// file          : include/CGAL/Nef_2/HalfedgeDS_default.h
// package       : Nef_2 (0.9.25)
// chapter       : $CGAL_Chapter: Halfedge Data Structures $
// source        : hds.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/20 15:51:25 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI Saarbruecken (Stefan Schirra)
//
// Halfedge Data Structure Default Implementation for CGAL.
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HALFEDGEDS_DEFAULT_H
#define CGAL_HALFEDGEDS_DEFAULT_H 1

#include <CGAL/Nef_2/HalfedgeDS_using_in_place_list.h>

CGAL_BEGIN_NAMESPACE

template <class p_Traits, class p_Items> // = HalfedgeDS_items>
class HalfedgeDS_default
  : public HalfedgeDS_using_in_place_list< p_Traits, p_Items> {
public:
  typedef p_Traits Traits;
  typedef size_t size_type;
  HalfedgeDS_default() {}
  HalfedgeDS_default( size_type v, size_type h, size_type f)
    : HalfedgeDS_using_in_place_list< p_Traits, p_Items>(v,h,f) {}
};

CGAL_END_NAMESPACE

#endif // CGAL_HALFEDGEDS_DEFAULT_H //
// EOF //
