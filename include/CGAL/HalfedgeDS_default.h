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
// file          : include/CGAL/HalfedgeDS_default.h
// package       : HalfedgeDS (3.21)
// chapter       : $CGAL_Chapter: Halfedge Data Structures $
// source        : hds.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/07/02 20:53:58 $
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

#include <CGAL/HalfedgeDS_items_2.h>
#include <CGAL/HalfedgeDS_list.h>
#include <CGAL/memory.h>

CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM

template <class Traits_, class HalfedgeDSItems = HalfedgeDS_items_2, 
          class Alloc = CGAL_ALLOCATOR(int)>
class HalfedgeDS_default 
    : public HalfedgeDS_list< Traits_, HalfedgeDSItems, Alloc> {
public:
    typedef Traits_                                          Traits;
    typedef HalfedgeDS_list<Traits_, HalfedgeDSItems, Alloc> DS;
    typedef typename DS::size_type                           size_type;
    HalfedgeDS_default() {}
    HalfedgeDS_default( size_type v, size_type h, size_type f)
        : HalfedgeDS_list< Traits_, HalfedgeDSItems, Alloc>(v,h,f) {}
};
#define CGAL_HALFEDGEDS_DEFAULT  ::CGAL::HalfedgeDS_default

#else //  CGAL_CFG_NO_TMPL_IN_TMPL_PARAM //

struct HalfedgeDS_default {
  template <class Traits_, class HalfedgeDSItems = HalfedgeDS_items_2, 
            class Alloc = CGAL_ALLOCATOR(int)>
  class HDS : public HalfedgeDS_list::HDS<Traits_, HalfedgeDSItems, Alloc> {
  public:
      typedef Traits_                                               Traits;
      typedef HalfedgeDS_list::HDS<Traits_, HalfedgeDSItems, Alloc> DS;
      typedef typename DS::size_type                                size_type;
      HDS();
      HDS( size_type v, size_type h, size_type f);
  };
};

template <class Traits_, class HalfedgeDSItems, class Alloc>
HalfedgeDS_default::HDS<Traits_, HalfedgeDSItems, Alloc>:: HDS() {}

template <class Traits_, class HalfedgeDSItems, class Alloc>
HalfedgeDS_default::HDS<Traits_, HalfedgeDSItems, Alloc>::
HDS( size_type v, size_type h, size_type f)
    : HalfedgeDS_list::HDS<Traits_, HalfedgeDSItems, Alloc>(v,h,f) {}

#define CGAL_HALFEDGEDS_DEFAULT  ::CGAL::HalfedgeDS_default::HDS

#endif // CGAL_CFG_NO_TMPL_IN_TMPL_PARAM //

CGAL_END_NAMESPACE
#endif // CGAL_HALFEDGEDS_DEFAULT_H //
// EOF //
