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
// file          : include/CGAL/basic_constructionsC3.h
// package       : C3 (2.1.5)
// source        : web/basic_constructionsC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:38 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONSC3_H
#define CGAL_BASIC_CONSTRUCTIONSC3_H

#ifndef CGAL_POINTC3_H
#include <CGAL/PointC3.h>
#endif // CGAL_POINTC3_H
#ifndef CGAL_PLANEC3_H
#include <CGAL/PlaneC3.h>
#endif // CGAL_PLANEC3_H
#ifndef CGAL_BASIC_CONSTRUCTIONS_FTC3_H
#include <CGAL/basic_constructions_ftC3.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
PointC3<FT>
midpoint( PointC3<FT> const& p, PointC3<FT> const& q )
{
  FT x,y,z;
  midpointC3(p.x(),p.y(),p.z(),q.x(),q.y(),q.z(),x,y,z);
  return PointC3<FT>(x,y,z);
}

template < class FT >
PointC3<FT>
circumcenter( PointC3<FT> const& p,
              PointC3<FT> const& q,
              PointC3<FT> const& r,
              PointC3<FT> const& s)
{
  FT x,y,z;
  circumcenterC3(p.x(),p.y(),p.z(),
                 q.x(),q.y(),q.z(),
                 r.x(),r.y(),r.z(),
                 s.x(),s.y(),s.z(),
                 x,y,z);
  return PointC3<FT>(x,y,z);
}

template <class FT>
CGAL_KERNEL_LARGE_INLINE
PointC3<FT>
projection(const PointC3<FT>& p, const PlaneC3<FT>& h)
{
  FT x,y,z;
  projectionC3(h.a(),h.b(),h.c(),h.d(),
               p.x(),p.y(),p.z(),
               x,y,z);
  return PointC3<FT>(x,y,z);
}


template < class FT >
inline
FT
squared_distance(const PointC3<FT> &p, const PointC3<FT> &q)
{
  return squared_distanceC3(p.x(),p.y(),p.z(),q.x(),q.y(),q.z());
}

template < class FT >
inline
FT
scaled_distance_to_plane(const PlaneC3<FT> &h, const PointC3<FT> &p)
{
  return scaled_distance_to_planeC3(h.a(),h.b(),h.c(),h.d(),
                                    p.x(),p.y(),p.z());
}

template < class FT >
inline
FT
scaled_distance_to_plane(const PointC3<FT> &hp,
                         const PointC3<FT> &hq,
                         const PointC3<FT> &hr,
                         const PointC3<FT> &p)
{
  return scaled_distance_to_planeC3(hp.x(),hp.y(),hp.z(),
                                    hq.x(),hq.y(),hq.z(),
                                    hr.x(),hr.y(),hr.z(),
                                    p.x(),p.y(),p.z());
}


CGAL_END_NAMESPACE

#endif // CGAL_BASIC_CONSTRUCTIONSC3_H
