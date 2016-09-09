// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// source        : webS2/S2.lw
// file          : include/CGAL/SimpleCartesian/basic_constructionsS2.h
// package       : S2 (1.7)
// revision      : 1.6
// revision_date : 27 Jun 2000
// author(s)     : Stefan Schirra
//                 based on code by
//                 Andreas Fabri and
//                 Herve Brönnimann
//
// coordinator   : MPI, Saarbrücken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONSS2_H
#define CGAL_BASIC_CONSTRUCTIONSS2_H 1

#include <utility>
#include <CGAL/SimpleCartesian/PointS2.h>

CGAL_BEGIN_NAMESPACE

template < class FT >
PointS2<FT>
midpoint( PointS2<FT> const& p,
          PointS2<FT> const& q )
{
  FT x,y;
  midpointC2(p.x(),p.y(),q.x(),q.y(),x,y);
  return PointS2<FT>(x,y);
}

template < class FT >
LineS2<FT>
bisector( PointS2<FT> const& p,
          PointS2<FT> const& q )
{
  FT a,b,c;
  bisector_of_pointsC2(p.x(),p.y(),q.x(),q.y(),a,b,c);
  return LineS2<FT>(a,b,c);
}

template < class FT >
PointS2<FT>
circumcenter( PointS2<FT> const& p,
              PointS2<FT> const& q,
              PointS2<FT> const& r)
{
  FT x,y;
  circumcenterC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),x,y);
  return PointS2<FT>(x,y);
}

template < class FT >
FT
squared_circumradius( PointS2<FT> const& p,
                      PointS2<FT> const& q,
                      PointS2<FT> const& r)
{
  return squared_circumradius(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}

template < class FT >
PointS2<FT>
squared_circumcircle( PointS2<FT> const& p,
                      PointS2<FT> const& q,
                      PointS2<FT> const& r,
                      FT &radius)
{
  FT x,y;
  radius = squared_circumradius(p.x(),p.y(),q.x(),q.y(),r.x(),r.y(),x,y);
  return PointS2<FT>(x,y);
}


template < class FT >
FT
squared_distance( PointS2<FT> const& p,
                  PointS2<FT> const& q)
{
  return squared_distanceC2(p.x(),p.y(),q.x(),q.y());
}

template < class FT >
FT
scaled_distance_to_line( LineS2<FT> const& l,
                         PointS2<FT> const& p)
{
  return squared_distance_to_lineC2(l.a(),l.b(),l.c(),p.x(),p.y());
}

template < class FT >
FT
scaled_distance_to_line( PointS2<FT> const& p,
                         PointS2<FT> const& q,
                         PointS2<FT> const& r)
{
  return squared_distance_to_lineC2(p.x(),p.y(),q.x(),q.y(),r.x(),r.y());
}


CGAL_END_NAMESPACE

#endif // CGAL_BASIC_CONSTRUCTIONS_2_H
