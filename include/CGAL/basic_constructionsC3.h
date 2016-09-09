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
// file          : include/CGAL/basic_constructionsC3.h
// package       : C3 (1.6)
// source        : web/basic_constructionsC3.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1998/12/04 12:24:07 $
// author(s)     : Herve.Bronnimann
//
// coordinator   : INRIA Sophia-Antipolis
//
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

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_PointC3<FT>
CGAL_midpoint( CGAL_PointC3<FT> const& p,
               CGAL_PointC3<FT> const& q )
{
  FT x,y,z;
  CGAL_midpointC3(p.x(),p.y(),p.z(),q.x(),q.y(),q.z(),x,y,z);
  return CGAL_PointC3<FT>(x,y,z);
}

template < class FT >
CGAL_PointC3<FT>
CGAL_circumcenter( CGAL_PointC3<FT> const& p,
                   CGAL_PointC3<FT> const& q,
                   CGAL_PointC3<FT> const& r,
                   CGAL_PointC3<FT> const& s)
{
  FT x,y,z;
  CGAL_circumcenterC3(p.x(),p.y(),p.z(),
                      q.x(),q.y(),q.z(),
                      r.x(),r.y(),r.z(),
                      s.x(),s.y(),s.z(),
                      x,y,z);
  return CGAL_PointC3<FT>(x,y,z);
}

template <class FT>
CGAL_KERNEL_LARGE_INLINE
CGAL_PointC3<FT>
CGAL_projection(const CGAL_PointC3<FT>& p, const CGAL_PlaneC3<FT>& h)
{
  FT x,y,z;
  CGAL_projectionC3(h.a(),h.b(),h.c(),h.d(),
                    p.x(),p.y(),p.z(),
                    x,y,z);
  return CGAL_PointC3<FT>(x,y,z);
}


template < class FT >
inline
FT
CGAL_squared_distance(const CGAL_PointC3<FT> &p, const CGAL_PointC3<FT> &q)
{
  return CGAL_squared_distanceC3(p.x(),p.y(),p.z(),q.x(),q.y(),q.z());
}

template < class FT >
inline
FT
CGAL_scaled_distance_to_plane(const CGAL_PlaneC3<FT> &h,
                              const CGAL_PointC3<FT> &p)
{
  return CGAL_scaled_distance_to_planeC3(h.a(),h.b(),h.c(),h.d(),
                                         p.x(),p.y(),p.z());
}

template < class FT >
FT
CGAL_scaled_distance_to_plane(const CGAL_PointC3<FT> &hp,
                              const CGAL_PointC3<FT> &hq,
                              const CGAL_PointC3<FT> &hr,
                              const CGAL_PointC3<FT> &p)
{
  return CGAL_scaled_distance_to_planeC3(hp.x(),hp.y(),hp.z(),
                                         hq.x(),hq.y(),hq.z(),
                                         hr.x(),hr.y(),hr.z(),
                                         p.x(),p.y(),p.z());
}



#endif // CGAL_BASIC_CONSTRUCTIONSC3_H
