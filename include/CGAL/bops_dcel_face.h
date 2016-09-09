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
// file          : include/CGAL/bops_dcel_face.h
// package       : bops (2.4)
// source        : include/CGAL/bops_dcel_face.h
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/10/11 13:50:32 $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_FACE_H
#define CGAL__DCEL_FACE_H

#include <CGAL/bops_dcel_element.h>

CGAL_BEGIN_NAMESPACE

/*
  FACE in the DCEL:
  -----------------
  face_type:        header (HF), color
  face:             typedef const _Dcel_face_type*   _Dcel_face;
  container:        vector<_Dcel_face_type>
  face_iterator:    typedef vector<_Dcel_face_type>::const_iterator
  conversion:       face and face_iterator are type-identical
*/


template<class I>
class _Dcel_face_type : public _Dcel_element_type {
public:
#ifdef CGAL_CFG_INCOMPLETE_TYPE_BUG_4
  typedef _Dcel_edge_type<I>* edge;
#else
  typedef typename I::const_edges_iterator  edge;
#endif

  _Dcel_face_type(int ind, _Dcel_Color col = _NO_COLOR)
        : _Dcel_element_type(ind, col), _header(NULL) {}
  _Dcel_face_type( _Dcel_Color col = _NO_COLOR )
        : _Dcel_element_type(col), _header(NULL) {}

  edge  header() const { return _header; }

protected:
  edge&  header()  { return _header; }

private:
  edge _header;
  friend class _Dcel_base<I>;
};

CGAL_END_NAMESPACE

#endif /* CGAL__DCEL_FACE_H */
