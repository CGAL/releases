//  -*- Mode: c++ -*-
// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/bops_dcel_face.h
// package       : bops (1.1.2)
// source        : include/CGAL/bops_dcel_face.h
// revision      : $Revision: 1.1.2 $
// revision_date : $Date: Wed Dec  9 13:28:52 MET 1998  $
// author(s)     :             Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_FACE_H
#define CGAL__DCEL_FACE_H

#include <CGAL/bops_dcel_element.h>

/*
  FACE in the DCEL:
  -----------------
  face_type:        header (HF), color
  face:             typedef const CGAL__Dcel_face_type*   CGAL__Dcel_face;
  container:        vector<CGAL__Dcel_face_type>
  face_iterator:    typedef vector<CGAL__Dcel_face_type>::const_iterator
  conversion:       face and face_iterator are type-identical
*/


template<class I>
class CGAL__Dcel_face_type : public CGAL__Dcel_element_type {
public:
#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_4
  typedef CGAL__Dcel_edge_type<I>* edge;
#else
  typedef typename I::const_edges_iterator  edge;
#endif

  CGAL__Dcel_face_type(int ind, CGAL__Dcel_Color col = CGAL__NO_COLOR)
        : CGAL__Dcel_element_type(ind, col), _header(NULL) {}
  CGAL__Dcel_face_type( CGAL__Dcel_Color col = CGAL__NO_COLOR )
        : CGAL__Dcel_element_type(col), _header(NULL) {}

  edge  header() const { return _header; }

protected:
  edge&  header()  { return _header; }

private:
  edge _header;
  friend class CGAL__Dcel_base<I>;
};


#endif /* CGAL__DCEL_FACE_H */
