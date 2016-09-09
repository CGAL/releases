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
// file          : include/CGAL/basic_constructionsC2.h
// package       : C2 (2.1.4)
// source        : web/basic_constructionsC2.fw
// revision      : $Revision: 1.20 $
// revision_date : $Date: 1999/05/24 06:43:33 $
// author(s)     : Herve Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONSC2_H
#define CGAL_BASIC_CONSTRUCTIONSC2_H 1

#include <utility>

#ifndef CGAL_POINTC2_H
#include <CGAL/PointC2.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class FT >
PointC2<FT>
midpoint( PointC2<FT> const& p,
          PointC2<FT> const& q )
{
  FT x,y;
  midpointC2(p.x(),p.y(),q.x(),q.y(),x,y);
  return PointC2<FT>(x,y);
}
template < class FT >
PointC2<FT>
circumcenter( PointC2<FT> const& p,
              PointC2<FT> const& q,
              PointC2<FT> const& r)
{
  FT x,y;
  circumcenterC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),x,y);
  return PointC2<FT>(x,y);
}

template < class FT >
FT
squared_circumradius( PointC2<FT> const& p,
                      PointC2<FT> const& q,
                      PointC2<FT> const& r)
{
  return squared_circumradius(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}

template < class FT >
PointC2<FT>
squared_circumcircle( PointC2<FT> const& p,
                      PointC2<FT> const& q,
                      PointC2<FT> const& r,
                      FT &radius)
{
  FT x,y;
  radius = squared_circumradius(p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),x,y);
  return PointC2<FT>(x,y);
}


template < class FT >
FT
squared_distance( PointC2<FT> const& p,
                  PointC2<FT> const& q)
{
  return squared_distanceC2(p.x(),p.y(),q.x(),q.y());
}

template < class FT >
FT
scaled_distance_to_line( LineC2<FT> const& l,
                         PointC2<FT> const& p)
{
  return squared_distance_to_lineC2(l.a(),l.b(),l.c(),p.x(),p.y());
}

template < class FT >
FT
scaled_distance_to_line( PointC2<FT> const& p,
                         PointC2<FT> const& q,
                         PointC2<FT> const& r)
{
  return squared_distance_to_lineC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}


CGAL_END_NAMESPACE

#endif // CGAL_BASIC_CONSTRUCTIONS_2_H
