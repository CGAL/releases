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
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : Point_conversion.fw
// file          : include/CGAL/cartesian_homogeneous_conversion.h
// package       : Kernel_basic (3.14)
// revision      : 3.14
// revision_date : 15 Sep 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_CARTESIAN_HOMOGENEOUS_CONVERSION_H
#define CGAL_CARTESIAN_HOMOGENEOUS_CONVERSION_H

CGAL_BEGIN_NAMESPACE

template <class RT>
Point_2< Cartesian<RT> >
homogeneous_to_cartesian(const Point_2< Homogeneous<RT> >& hp)
{
  return
  Point_2< Cartesian<RT> >(hp.hx(), hp.hy(), hp.hw() );
}

template <class RT>
Point_2< Homogeneous<RT> >
cartesian_to_homogeneous(const Point_2< Cartesian<RT> >& cp)
{
  return
  Point_2< Homogeneous<RT> >(cp.hx(), cp.hy());
}

template <class RT>
Point_3< Cartesian<RT> >
homogeneous_to_cartesian(const Point_3< Homogeneous<RT> >& hp)
{
  return
  Point_3< Cartesian<RT> >(hp.hx(), hp.hy(), hp.hz(), hp.hw() );
}

template <class RT>
Point_3< Homogeneous<RT> >
cartesian_to_homogeneous(const Point_3< Cartesian<RT> >& cp)
{
  return
  Point_3< Homogeneous<RT> >(cp.hx(), cp.hy(), cp.hz() );
}

template <class RT>
Point_2< Cartesian<Quotient<RT> > >
homogeneous_to_quotient_cartesian(
  const Point_2<Homogeneous<RT> >& hp)
{
  typedef Quotient<RT>  QT;
  return Point_2< Cartesian<QT> >( QT( hp.hx(), hp.hw() ),
                                             QT( hp.hy(), hp.hw() ) );
}

template <class RT>
Point_2< Homogeneous<RT> >
quotient_cartesian_to_homogeneous(
  const Point_2< Cartesian< Quotient<RT> > >& cp)
{
  typedef Point_2<Homogeneous<RT> >  HPoint;
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
Point_3< Cartesian<Quotient<RT> > >
homogeneous_to_quotient_cartesian(
  const Point_3<Homogeneous<RT> >& hp)
{
  typedef Quotient<RT>  QT;
  return Point_3< Cartesian<QT> >( QT( hp.hx(), hp.hw() ),
                                             QT( hp.hy(), hp.hw() ),
                                             QT( hp.hz(), hp.hw() ) );
}

template <class RT>
Point_3< Homogeneous<RT> >
quotient_cartesian_to_homogeneous(
  const Point_3< Cartesian< Quotient<RT> > >& cp)
{
  typedef Point_3<Homogeneous<RT> >  HPoint;
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

CGAL_END_NAMESPACE


#endif // CGAL_CARTESIAN_HOMOGENEOUS_CONVERSION_H
