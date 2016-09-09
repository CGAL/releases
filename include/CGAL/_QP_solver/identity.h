// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.2-I-51 $
// release_date  : $CGAL_Date: 2000/10/01 $
//
// file          : include/CGAL/_QP_solver/identity.h
// package       : _QP_solver (0.9)
// maintainer    : Sven Schönherr <sven@inf.ethz.ch>
//
// revision      : 0.1
// revision_date : 2000/08/11 00:00:00
//
// author(s)     : Sven Schönherr
// coordinator   : ETH Zürich (Bernd Gärtner <gaertner@inf.ethz.ch>)
//
// implementation: identity function class
// ======================================================================

#ifndef CGAL_IDENTITY_H
#define CGAL_IDENTITY_H

#include <CGAL/basic.h>
#include <functional>

CGAL_BEGIN_NAMESPACE

template < class T >
class identity
    : public CGAL_STD::unary_function<T,T> {
  public:
    T  operator () ( T t) const { return t; }
};

CGAL_END_NAMESPACE
  
#endif // CGAL_IDENTITY_H

// ===== EOF ==================================================================
