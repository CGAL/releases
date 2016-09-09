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
// file          : include/CGAL/bops_dcel_element.h
// package       : bops (2.1.5)
// source        : include/CGAL/bops_dcel_element.h
// revision      : $Revision: WIP $
// revision_date : $Date: Wed Dec  9 13:28:52 MET 1998  $
// author(s)     : Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL__DCEL_ELEMENT_H
#define CGAL__DCEL_ELEMENT_H

#include <CGAL/bops_dcel_defs.h>

CGAL_BEGIN_NAMESPACE

/*
  ELEMENT in the DCEL:
  ---------------------
*/


class _Dcel_element_type {
public:
  _Dcel_element_type( int ind, _Dcel_Color col = _NO_COLOR )
        : _index(ind), _color(col) {}
  _Dcel_element_type( _Dcel_Color col = _NO_COLOR )
        : _index(-1), _color(col) {}

  _Dcel_Color    color() const  { return _color; }
  _Dcel_Color    set_color(const _Dcel_Color& c) {
    _color= c;
    return c;
  }
  bool    has_color(const _Dcel_Color& c) const {
    return color()& c ? true : false;
  }

  _Dcel_Color&   color()   { return _color; }
  int              index() const  { return _index; }

private:
  int _index;
  _Dcel_Color _color;
};

CGAL_END_NAMESPACE

#endif /* CGAL__DCEL_ELEMENT_H */
