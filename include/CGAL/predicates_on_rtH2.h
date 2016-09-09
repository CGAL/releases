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
// source        : predicates_on_rtH2.fw
// file          : include/CGAL/predicates_on_rtH2.h
// package       : H2 (1.3.1)
// revision      : 1.3.1
// revision_date : 02 Jan 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PREDICATES_ON_RTH2_H
#define CGAL_PREDICATES_ON_RTH2_H

template <class RT>
CGAL_KERNEL_INLINE
CGAL_Orientation
CGAL_orientationH2( const RT& phx, const RT& phy, const RT& phw,
                    const RT& qhx, const RT& qhy, const RT& qhw,
                    const RT& rhx, const RT& rhy, const RT& rhw )
{
  const RT  RT0 = RT(0);
  
  // | A B |
  // | C D |
  
  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;
  
  RT  det =  A*D - B*C;
  
  
  if (det < RT0  )
  {
      return CGAL_CLOCKWISE;
  }
  else
  {
      return (RT0 < det) ? CGAL_COUNTERCLOCKWISE : CGAL_COLLINEAR;
  }
}

template <class RT>
CGAL_KERNEL_INLINE
bool
CGAL_leftturnH2( const RT& phx, const RT& phy, const RT& phw,
                 const RT& qhx, const RT& qhy, const RT& qhw,
                 const RT& rhx, const RT& rhy, const RT& rhw )
{
  const RT  RT0 = RT(0);
  
  // | A B |
  // | C D |
  
  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;
  
  RT  det =  A*D - B*C;
  
  
  return ( RT0 < det );
}

template <class RT>
CGAL_KERNEL_INLINE
bool
CGAL_rightturnH2(const RT& phx, const RT& phy, const RT& phw,
                 const RT& qhx, const RT& qhy, const RT& qhw,
                 const RT& rhx, const RT& rhy, const RT& rhw )
{
  const RT  RT0 = RT(0);
  
  // | A B |
  // | C D |
  
  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;
  
  RT  det =  A*D - B*C;
  
  
  return ( det < RT0 );
}

template <class RT>
CGAL_KERNEL_INLINE
bool
CGAL_collinearH2(const RT& phx, const RT& phy, const RT& phw,
                 const RT& qhx, const RT& qhy, const RT& qhw,
                 const RT& rhx, const RT& rhy, const RT& rhw )
{
  const RT  RT0 = RT(0);
  
  // | A B |
  // | C D |
  
  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;
  
  RT  det =  A*D - B*C;
  
  
  return ( det == RT0 );
}
template <class RT>
CGAL_KERNEL_INLINE
CGAL_Bounded_side
CGAL_side_of_bounded_circleH2( const RT& qhx, const RT& qhy, const RT& qhw,
                               const RT& rhx, const RT& rhy, const RT& rhw,
                               const RT& shx, const RT& shy, const RT& shw,
                               const RT& thx, const RT& thy, const RT& thw )
{
  CGAL_kernel_precondition( ! CGAL_collinearH2(qhx, qhy, ghw,
                                               rhx, rhy, rhw,
                                               shx, shy, shw) );
  
  // compute sign of      |qx  qy  qx^2+qy^2  1 |   | a b c d |
  //                      |      --  r  --      | = | e f g h |
  //     determinant      |      --  s  --      | = | i j k l |
  //                      |      --  t  --      |   | m n o p |
  //           where
  
  RT a = qhx*qhw;
  RT b = qhy*qhw;
  RT c = qhx*qhx + qhy*qhy;
  RT d = qhw*qhw;
  
  RT e = rhx*rhw;
  RT f = rhy*rhw;
  RT g = rhx*rhx + rhy*rhy;
  RT h = rhw*rhw;
  
  RT i = shx*shw;
  RT j = shy*shw;
  RT k = shx*shx + shy*shy;
  RT l = shw*shw;
  
  RT m = thx*thw;
  RT n = thy*thw;
  RT o = thx*thx + thy*thy;
  RT p = thw*thw;
  RT det =   a * ( f*(k*p - l*o) + j*(h*o - g*p) + n*(g*l - h*k) )
           - e * ( b*(k*p - l*o) + j*(d*o - c*p) + n*(c*l - d*k) )
           + i * ( b*(g*p - h*o) + f*(d*o - c*p) + n*(c*h - d*g) )
           - m * ( b*(g*l - h*k) + f*(d*k - c*l) + j*(c*h - d*g) );
  
  if ( det == RT0 )
  {
      return CGAL_ON_BOUNDARY;
  }
  else
  {
      if (CGAL_orientation(q,r,s) == CGAL_CLOCKWISE)
      {
          det = -det;
      }
      return (RT0 < det ) ? CGAL_ON_BOUNDED_SIDE : CGAL_ON_UNBOUNDED_SIDE;
  }
}

template <class RT>
CGAL_KERNEL_INLINE
CGAL_Oriented_side
CGAL_side_of_oriented_circleH2(const RT& qhx, const RT& qhy, const RT& qhw,
                               const RT& rhx, const RT& rhy, const RT& rhw,
                               const RT& shx, const RT& shy, const RT& shw,
                               const RT& thx, const RT& thy, const RT& thw )
{
  CGAL_kernel_precondition( ! CGAL_collinearH2(qhx, qhy, ghw,
                                               rhx, rhy, rhw,
                                               shx, shy, shw) );
  
  // compute sign of      |qx  qy  qx^2+qy^2  1 |   | a b c d |
  //                      |      --  r  --      | = | e f g h |
  //     determinant      |      --  s  --      | = | i j k l |
  //                      |      --  t  --      |   | m n o p |
  //           where
  
  RT a = qhx*qhw;
  RT b = qhy*qhw;
  RT c = qhx*qhx + qhy*qhy;
  RT d = qhw*qhw;
  
  RT e = rhx*rhw;
  RT f = rhy*rhw;
  RT g = rhx*rhx + rhy*rhy;
  RT h = rhw*rhw;
  
  RT i = shx*shw;
  RT j = shy*shw;
  RT k = shx*shx + shy*shy;
  RT l = shw*shw;
  
  RT m = thx*thw;
  RT n = thy*thw;
  RT o = thx*thx + thy*thy;
  RT p = thw*thw;
  RT det =   a * ( f*(k*p - l*o) + j*(h*o - g*p) + n*(g*l - h*k) )
           - e * ( b*(k*p - l*o) + j*(d*o - c*p) + n*(c*l - d*k) )
           + i * ( b*(g*p - h*o) + f*(d*o - c*p) + n*(c*h - d*g) )
           - m * ( b*(g*l - h*k) + f*(d*k - c*l) + j*(c*h - d*g) );
  
  if ( det < RT0 )  return CGAL_ON_NEGATIVE_SIDE;
  else return (RT0 < det ) ? CGAL_ON_POSITIVE_SIDE :
                             CGAL_ON_ORIENTED_BOUNDARY;
}
template <class RT>
CGAL_KERNEL_INLINE
CGAL_Comparison_result
CGAL_compare_lexicographically_xyH2(const RT& phx, const RT& phy, const RT& phw,
                                    const RT& qhx, const RT& qhy, const RT& qhw)
{
  RT pV = phx*qhw;
  RT qV = qhx*phw;
  if ( pV == qV )
  {
      pV = phy*qhw;
      qV = qhy*phw;
  }
  if ( pV < qV )
  {
      return CGAL_SMALLER;
  }
  else
  {
      return (qV < pV) ? CGAL_LARGER : CGAL_EQUAL;
  }
}

template <class RT>
CGAL_KERNEL_INLINE
CGAL_Comparison_result
CGAL_compare_xH2( const RT& phx, const RT& phw,
                  const RT& qhx, const RT& qhw )
{
  RT com = phx * qhw - qhx * phw;
  if ( com < RT0 )
  {
      return CGAL_SMALLER;
  }
  else if ( RT0 < com )
  {
      return CGAL_LARGER;
  }
  return CGAL_EQUAL;
}

// No CGAL_compare_yH2; use CGAL_compare_xH2( py, pw, qy, qw)

template < class RT >
CGAL_KERNEL_INLINE
CGAL_Comparison_result
CGAL_compare_deltax_deltayH2(const RT& phx, const RT& phw,
                             const RT& qhx, const RT& qhw,
                             const RT& rhy, const RT& rhw,
                             const RT& shy, const RT& shw )
  const RT  tbc1 = CGAL_abs(phx*qhw - qhx*phw) * rhw*shw;
  const RT  tbc2 = CGAL_abs(rhy*shw - shy*rhw) * phw*qhw;
  return (tbc2 < tbc1) ? CGAL_LARGER
                       : (tbc1 == tbc2) ? CGAL_EQUAL : CGAL_SMALLER;

}

template <class RT>
CGAL_KERNEL_INLINE
bool
CGAL_collinear_are_ordered_along_lineH2(
     const RT& phx, const RT& phy, const RT& phw,
     const RT& qhx, const RT& qhy, const RT& qhw,
     const RT& rhx, const RT& rhy, const RT& rhw
                                       )
{
  if ( !(phx * rhw == rhx * phw ) )          // non-vertical ?
  {
     return !( (  ( phx * qhw < qhx * phw)
                &&( rhx * qhw < qhx * rhw))
             ||(  ( qhx * phw < phx * qhw)
                &&( qhx * rhw < rhx * qhw)) );
  }
  else if ( !(phy * rhw == rhy * phw ) )
  {
     return !( (  ( phy * qhw < qhy * phw)
                &&( rhy * qhw < qhy * rhw))
             ||(  ( qhy * phw < phy * qhw)
                &&( qhy * rhw < rhy * qhw)) );
  }
  else
     return (( phx*qhw == qhx*phw) && ( phy*qhw == qhy*phw));
}

template <class RT>
CGAL_KERNEL_INLINE
bool
CGAL_collinear_are_strictly_ordered_along_lineH2(
     const RT& phx, const RT& phy, const RT& phw,
     const RT& qhx, const RT& qhy, const RT& qhw,
     const RT& rhx, const RT& rhy, const RT& rhw)
{
  if ( !(phx * rhw == rhx * phw ) )
  {
     return (   ( phx * qhw < qhx * phw)
              &&( qhx * rhw < rhx * qhw))
          ||(   ( qhx * phw < phx * qhw)    // ( phx * qhw > qhx * phw)
              &&( rhx * qhw < qhx * rhw));  // ( qhx * rhw > rhx * qhw)
  }
  else
  {
     return (   ( phy * qhw < qhy * phw)
              &&( qhy * rhw < rhy * qhw))
          ||(   ( qhy * phw < phy * qhw)    // ( phy * qhw > qhy * phw)
              &&( rhy * qhw < qhy * rhw));  // ( qhy * rhw > rhy * qhw)
  }
}




#ifdef CGAL_ARITHMETIC_FILTER_H
#include <CGAL/Arithmetic_filter/predicates_on_rtH2.h>
#endif // CGAL_ARITHMETIC_FILTER_H

#endif // CGAL_PREDICATES_ON_RTH2_H
