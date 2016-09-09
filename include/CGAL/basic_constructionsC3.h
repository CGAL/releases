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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/basic_constructionsC3.h
// package       : C3 (1.4)
// source        : web/basic_constructionsC3.fw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/04/28 13:25:04 $
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

template < class FT >
CGAL_KERNEL_MEDIUM_INLINE
CGAL_PointC3<FT>
CGAL_midpoint( CGAL_PointC3<FT> const& p,
               CGAL_PointC3<FT> const& q )
{
    return( CGAL_PointC3<FT>( ( p.x()+q.x()) / FT(2),
                              ( p.y()+q.y()) / FT(2),
                              ( p.z()+q.z()) / FT(2)));
}

template < class FT >
CGAL_PointC3<FT>
CGAL_circumcenter( CGAL_PointC3<FT> const& p,
                   CGAL_PointC3<FT> const& q,
                   CGAL_PointC3<FT> const& r,
                   CGAL_PointC3<FT> const& s)
{
    FT px( p.x());
    FT py( p.y());
    FT pz( p.z());
    FT qx( q.x());
    FT qy( q.y());
    FT qz( q.z());
    FT rx( r.x());
    FT ry( r.y());
    FT rz( r.z());
    FT sx( s.x());
    FT sy( s.y());
    FT sz( s.z());

    FT p2( px*px + py*py + pz*pz );
    FT q2( qx*qx + qy*qy + qz*qz );
    FT r2( rx*rx + ry*ry + rz*rz );
    FT s2( sx*sx + sy*sy + sz*sz );

    FT num_x( CGAL_det4x4_by_formula(py,pz,p2,FT(1),
                                      qy,qz,q2,FT(1),
                                      ry,rz,r2,FT(1),
                                      sy,sz,s2,FT(1)));
    FT num_y( CGAL_det4x4_by_formula(px,pz,p2,FT(1),
                                      qx,qz,q2,FT(1),
                                      rx,rz,r2,FT(1),
                                      sx,sz,s2,FT(1)));
    FT num_z( CGAL_det4x4_by_formula(px,py,p2,FT(1),
                                      qx,qy,q2,FT(1),
                                      rx,ry,r2,FT(1),
                                      sx,sy,s2,FT(1)));

    FT den( CGAL_det4x4_by_formula(px,py,pz,FT(1),
                                    qx,qy,qz,FT(1),
                                    rx,ry,rz,FT(1),
                                    sx,sy,sz,FT(1)) * FT(2) );

    return( CGAL_PointC3<FT>( num_x/den, - num_y/den, num_z/den) );
}

template <class FT>
CGAL_KERNEL_LARGE_INLINE
CGAL_PointC3<FT>
CGAL_projection(const CGAL_PointC3<FT>& p, const CGAL_PlaneC3<FT>& pl)
{
  // the equation of the plane is Ax+By+Cz+D=0
  // the normal direction is (A,B,C)
  // the projected point is p-lambda(A,B,C) where
  // A(x-lambda A) + B(y-lambda B) + C(z-lambda C) + D = 0

  if ( pl.has_on_boundary(p) ) return p;

  FT A = pl.a();
  FT B = pl.b();
  FT C = pl.c();
  FT D = pl.d();
  FT phx = p.hx();
  FT phy = p.hy();
  FT phz = p.hz();

  FT num = A * phx  +  B * phy  +  C * phz  +  D;
  FT den = A * A    +  B * B    +  C * C;
  FT lambda = num / den;

  return CGAL_PointC3<FT>( phx - lambda * A,
                           phy - lambda * B,
                           phz - lambda * C);
}


#endif // CGAL_BASIC_CONSTRUCTIONSC3_H
