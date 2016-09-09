// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// source        : Point_conversion.fw
// file          : include/CGAL/cartesian_homogeneous_conversion.h
// package       : Kernel_basic (1.2.12)
// revision      : 1.2.12
// revision_date : 08 Jan 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_CARTESIAN_HOMOGENEOUS_CONVERSION_H
#define CGAL_CARTESIAN_HOMOGENEOUS_CONVERSION_H

template <class RT>
CGAL_Point_2< CGAL_Cartesian<RT> >
CGAL_homogeneous_to_cartesian(const CGAL_Point_2< CGAL_Homogeneous<RT> >& hp)
{
  return
  CGAL_Point_2< CGAL_Cartesian<RT> >(hp.hx(), hp.hy(), hp.hw() );
}

template <class RT>
CGAL_Point_2< CGAL_Homogeneous<RT> >
CGAL_cartesian_to_homogeneous(const CGAL_Point_2< CGAL_Cartesian<RT> >& cp)
{
  return
  CGAL_Point_2< CGAL_Homogeneous<RT> >(cp.hx(), cp.hy());
}

template <class RT>
CGAL_Point_3< CGAL_Cartesian<RT> >
CGAL_homogeneous_to_cartesian(const CGAL_Point_3< CGAL_Homogeneous<RT> >& hp)
{
  return
  CGAL_Point_3< CGAL_Cartesian<RT> >(hp.hx(), hp.hy(), hp.hz(), hp.hw() );
}

template <class RT>
CGAL_Point_3< CGAL_Homogeneous<RT> >
CGAL_cartesian_to_homogeneous(const CGAL_Point_3< CGAL_Cartesian<RT> >& cp)
{
  return
  CGAL_Point_3< CGAL_Homogeneous<RT> >(cp.hx(), cp.hy(), cp.hz() );
}

template <class RT>
CGAL_Point_2< CGAL_Cartesian<CGAL_Quotient<RT> > >
CGAL_homogeneous_to_quotient_cartesian(
  const CGAL_Point_2<CGAL_Homogeneous<RT> >& hp)
{
  typedef CGAL_Quotient<RT>  QT;
  return CGAL_Point_2< CGAL_Cartesian<QT> >( QT( hp.hx(), hp.hw() ),
                                             QT( hp.hy(), hp.hw() ) );
}

template <class RT>
CGAL_Point_2< CGAL_Homogeneous<RT> >
CGAL_quotient_cartesian_to_homogeneous(
  const CGAL_Point_2< CGAL_Cartesian< CGAL_Quotient<RT> > >& cp)
{
  typedef CGAL_Point_2<CGAL_Homogeneous<RT> >  HPoint;
  if ( cp.x().denominator() != cp.y().denominator() )
  {
      return HPoint( cp.x().numerator()  * cp.y().denominator(),
                     cp.y().numerator()  * cp.x().denominator(),
                     cp.x().denominator()* cp.y().denominator());
  }
  else
  {
      return HPoint( cp.x().numerator(),
                     cp.y().numerator(),
                     cp.x().denominator());
  }
}

template <class RT>
CGAL_Point_3< CGAL_Cartesian<CGAL_Quotient<RT> > >
CGAL_homogeneous_to_quotient_cartesian(
  const CGAL_Point_3<CGAL_Homogeneous<RT> >& hp)
{
  typedef CGAL_Quotient<RT>  QT;
  return CGAL_Point_3< CGAL_Cartesian<QT> >( QT( hp.hx(), hp.hw() ),
                                             QT( hp.hy(), hp.hw() ),
                                             QT( hp.hz(), hp.hw() ) );
}

template <class RT>
CGAL_Point_3< CGAL_Homogeneous<RT> >
CGAL_quotient_cartesian_to_homogeneous(
  const CGAL_Point_3< CGAL_Cartesian< CGAL_Quotient<RT> > >& cp)
{
  typedef CGAL_Point_3<CGAL_Homogeneous<RT> >  HPoint;
  if (  (cp.x().denominator() != cp.y().denominator() )
      ||(cp.x().denominator() != cp.z().denominator() ) )
  {
      return
      HPoint(cp.x().numerator()  *cp.y().denominator()*cp.z().denominator(),
             cp.y().numerator()  *cp.x().denominator()*cp.z().denominator(),
             cp.z().numerator()  *cp.x().denominator()*cp.y().denominator(),
             cp.x().denominator()*cp.y().denominator()*cp.z().denominator());
  }
  else
  {
      return HPoint( cp.x().numerator(),
                     cp.y().numerator(),
                     cp.z().numerator(),
                     cp.x().denominator());
  }
}


#endif // CGAL_CARTESIAN_HOMOGENEOUS_CONVERSION_H
