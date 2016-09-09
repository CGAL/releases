/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: predicates_on_pointsH2.h
// Author: Stefan Schirra

#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#define CGAL_PREDICATES_ON_POINTSH2_H

#include <CGAL/PVDH2.h>

template < class FT, class RT>
CGAL_Comparison_result
CGAL_compare_lexicographically_xy(const CGAL_PointH2<FT,RT>& p,
                                  const CGAL_PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

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
      return (pV > qV) ? CGAL_LARGER : CGAL_EQUAL;
  }
}


template < class FT, class RT>
bool
CGAL_lexicographically_xy_smaller_or_equal(const CGAL_PointH2<FT,RT>& p,
                                           const CGAL_PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phx * qhw;
  RT qV = qhx * phw;
  if ( pV > qV )
  {
      return false;
  }
  else if ( pV < qV )
  {
      return true;
  }

  pV = phy * qhw;
  qV = qhy * phw;
  return ( pV <= qV );
}

template < class FT, class RT>
bool
CGAL_lexicographically_xy_smaller(const CGAL_PointH2<FT,RT>& p,
                                  const CGAL_PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phx * qhw;
  RT qV = qhx * phw;
  if ( pV > qV )
  {
      return false;
  }
  else if ( pV < qV )
  {
      return true;
  }
  pV = phy * qhw;
  qV = qhy * phw;
  return ( pV < qV );
}

template < class FT, class RT>
bool
CGAL_lexicographically_xy_larger(const CGAL_PointH2<FT,RT>& p,
                                 const CGAL_PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phx * qhw;
  RT qV = qhx * phw;
  if ( pV < qV )
  {
      return false;
  }
  else if ( pV > qV )
  {
      return true;
  }
  pV = phy * qhw;
  qV = qhy * phw;
  return ( pV > qV );
}
template < class FT, class RT>
CGAL_Comparison_result
CGAL_compare_lexicographically_yx(const CGAL_PointH2<FT,RT>& p,
                                  const CGAL_PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phy*qhw;
  RT qV = qhy*phw;
  if ( pV == qV )
  {
      pV = phx*qhw;
      qV = qhx*phw;
  }
  if ( pV < qV )
  {
      return CGAL_SMALLER;
  }
  else
  {
      return (pV > qV) ? CGAL_LARGER : CGAL_EQUAL;
  }
}

template < class FT, class RT>
bool
CGAL_lexicographically_yx_smaller_or_equal(const CGAL_PointH2<FT,RT>& p,
                                           const CGAL_PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phy * qhw;
  RT qV = qhy * phw;
  if ( pV > qV )
  {
      return false;
  }
  else if ( pV < qV )
  {
      return true;
  }
  pV = phx * qhw;
  qV = qhx * phw;
  return ( pV <= qV );
}

template < class FT, class RT>
bool
CGAL_lexicographically_yx_smaller(const CGAL_PointH2<FT,RT>& p,
                                  const CGAL_PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phy * qhw;
  RT qV = qhy * phw;
  if ( pV > qV )
  {
      return false;
  }
  else if ( pV < qV )
  {
      return true;
  }
  pV = phx * qhw;
  qV = qhx * phw;
  return ( pV < qV );
}

template < class FT, class RT>
bool
CGAL_lexicographically_yx_larger(const CGAL_PointH2<FT,RT>& p,
                                 const CGAL_PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  RT pV = phy * qhw;
  RT qV = qhy * phw;
  if ( pV < qV )
  {
      return false;
  }
  else if ( pV > qV )
  {
      return true;
  }
  pV = phx * qhw;
  qV = qhx * phw;
  return ( pV > qV );
}


template < class FT, class RT>
CGAL_Comparison_result
CGAL_compare_x(const CGAL_PointH2<FT,RT>& p,
               const CGAL_PointH2<FT,RT>& q)
{
  const RT& phx = p.hx();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhw = q.hw();
  const RT  RT0 = RT(0);
  RT com = phx * qhw - qhx * phw;
  if ( com < RT0 )
  {
      return CGAL_SMALLER;
  }
  else if ( com > RT0 )
  {
      return CGAL_LARGER;
  }
  return CGAL_EQUAL;
}

template < class FT, class RT>
CGAL_Comparison_result
CGAL_compare_y(const CGAL_PointH2<FT,RT>& p,
               const CGAL_PointH2<FT,RT>& q)
{
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT  RT0 = RT(0);
  RT com = phy * qhw - qhy * phw;
  if ( com < RT0 )
  {
      return CGAL_SMALLER;
  }
  else if ( com > RT0 )
  {
     return CGAL_LARGER;
  }
  return CGAL_EQUAL;
}

template < class FT, class RT>
CGAL_Orientation
CGAL_orientation( const CGAL_PointH2<FT,RT>& p,
                  const CGAL_PointH2<FT,RT>& q,
                  const CGAL_PointH2<FT,RT>& r)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT  RT0 = RT(0);

  // | A B |
  // | C D |

  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;

  RT  det =  A*D - B*C;

/*
  RT det_old =    p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
                + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
                + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );

  if ( !(CGAL_sign(det) == CGAL_sign(det_old)) )
  {
      cerr << "det: " << det << " det_old: " << det_old << flush;
  }
*/



  if (det < RT0  )
  {
      return CGAL_CLOCKWISE;
  }
  else
  {
      return (det > RT0) ? CGAL_COUNTERCLOCKWISE : CGAL_COLLINEAR;
  }
}

template < class FT, class RT>
bool
CGAL_leftturn( const CGAL_PointH2<FT,RT>& p,
               const CGAL_PointH2<FT,RT>& q,
               const CGAL_PointH2<FT,RT>& r)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT  RT0 = RT(0);

  // | A B |
  // | C D |

  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;

  RT  det =  A*D - B*C;

/*
  RT det_old =    p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
                + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
                + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );

  if ( !(CGAL_sign(det) == CGAL_sign(det_old)) )
  {
      cerr << "det: " << det << " det_old: " << det_old << flush;
  }
*/


  return ( det > RT0 );
}

template < class FT, class RT>
bool
CGAL_rightturn( const CGAL_PointH2<FT,RT>& p,
                const CGAL_PointH2<FT,RT>& q,
                const CGAL_PointH2<FT,RT>& r)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT  RT0 = RT(0);

  // | A B |
  // | C D |

  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;

  RT  det =  A*D - B*C;

/*
  RT det_old =    p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
                + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
                + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );

  if ( !(CGAL_sign(det) == CGAL_sign(det_old)) )
  {
      cerr << "det: " << det << " det_old: " << det_old << flush;
  }
*/


  return ( det < RT0 );
}

template < class FT, class RT>
bool
CGAL_collinear( const CGAL_PointH2<FT,RT>& p,
                const CGAL_PointH2<FT,RT>& q,
                const CGAL_PointH2<FT,RT>& r)
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT  RT0 = RT(0);

  // | A B |
  // | C D |

  RT  A = phx*rhw - phw*rhx;
  RT  B = phy*rhw - phw*rhy;
  RT  C = qhx*rhw - qhw*rhx;
  RT  D = qhy*rhw - qhw*rhy;

  RT  det =  A*D - B*C;

/*
  RT det_old =    p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
                + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
                + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );

  if ( !(CGAL_sign(det) == CGAL_sign(det_old)) )
  {
      cerr << "det: " << det << " det_old: " << det_old << flush;
  }
*/


  return ( det == RT0 );
}
template <class FT, class RT>
CGAL_Bounded_side
CGAL_side_of_bounded_circle( const CGAL_PointH2<FT,RT>& q,
                             const CGAL_PointH2<FT,RT>& r,
                             const CGAL_PointH2<FT,RT>& s,
                             const CGAL_PointH2<FT,RT>& t)
{

  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT& shx = s.hx();
  const RT& shy = s.hy();
  const RT& shw = s.hw();
  const RT& thx = t.hx();
  const RT& thy = t.hy();
  const RT& thw = t.hw();
  const RT  RT0 = RT(0);

  CGAL_kernel_precondition( ! CGAL_collinear(q,r,s) );

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
      return (det > RT0 ) ? CGAL_ON_BOUNDED_SIDE : CGAL_ON_UNBOUNDED_SIDE;
  }
}

template <class FT, class RT>
CGAL_Oriented_side
CGAL_side_of_oriented_circle( const CGAL_PointH2<FT,RT>& q,
                              const CGAL_PointH2<FT,RT>& r,
                              const CGAL_PointH2<FT,RT>& s,
                              const CGAL_PointH2<FT,RT>& t)
{

  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();
  const RT& shx = s.hx();
  const RT& shy = s.hy();
  const RT& shw = s.hw();
  const RT& thx = t.hx();
  const RT& thy = t.hy();
  const RT& thw = t.hw();
  const RT  RT0 = RT(0);

  CGAL_kernel_precondition( ! CGAL_collinear(q,r,s) );

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
      return CGAL_ON_ORIENTED_BOUNDARY;
  }
  else
  {
      return (det > RT0 ) ? CGAL_ON_POSITIVE_SIDE : CGAL_ON_NEGATIVE_SIDE;
  }
}
template <class FT, class RT>
bool
CGAL_collinear_are_ordered_along_line( const CGAL_PointH2<FT,RT>& p,
                        const CGAL_PointH2<FT,RT>& q,
                        const CGAL_PointH2<FT,RT>& r )
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();
  const RT& rhx = r.hx();
  const RT& rhy = r.hy();
  const RT& rhw = r.hw();

  if ( phx * rhw != rhx * phw )
  {
     return (   ( phx * qhw < qhx * phw)
              &&( qhx * rhw < rhx * qhw))
          ||(   ( phx * qhw > qhx * phw)
              &&( qhx * rhw > rhx * qhw));
  }
  else
  {
     return (   ( phy * qhw < qhy * phw)
              &&( qhy * rhw < rhy * qhw))
          ||(   ( phy * qhw > qhy * phw)
              &&( qhy * rhw > rhy * qhw));
  }
}


template <class FT, class RT>
bool
CGAL_are_ordered_along_line( const CGAL_PointH2<FT,RT>& p,
              const CGAL_PointH2<FT,RT>& q,
              const CGAL_PointH2<FT,RT>& r )
{
  if ( CGAL_collinear(p,q,r) )
  {
     return CGAL_collinear_are_ordered_along_line(p,q,r);
  }
  else
  {
     return false;
  }
}
template <class FT, class RT>
bool
CGAL_x_equal( const CGAL_PointH2<FT,RT>& p,
              const CGAL_PointH2<FT,RT>& q )
{
  return ( p.hx()*q.hw() == q.hx()*p.hw() );
}

template <class FT, class RT>
bool
CGAL_y_equal( const CGAL_PointH2<FT,RT>& p,
              const CGAL_PointH2<FT,RT>& q )
{
  return ( p.hy()*q.hw() == q.hy()*p.hw() );
}
template <class FT, class RT>
CGAL_Oriented_side
CGAL__where_wrt_L_wedge( const CGAL_PointH2<FT,RT>& p,
                         const CGAL_PointH2<FT,RT>& q )
{
  const RT& phx = p.hx();
  const RT& phy = p.hy();
  const RT& phw = p.hw();
  const RT& qhx = q.hx();
  const RT& qhy = q.hy();
  const RT& qhw = q.hw();

  int xs = CGAL_sign( qhx*phw - phx*qhw );  // sign( qx - px )
  int ys = CGAL_sign( qhy*phw - phy*qhw );  // sign( qy - py )

  if (( xs == -1 ) || ( ys == -1 ))
  {
      return CGAL_ON_NEGATIVE_SIDE;
  }
  if (( xs ==  1 ) && ( ys ==  1 ))
  {
      return CGAL_ON_POSITIVE_SIDE;
  }
  return CGAL_ON_ORIENTED_BOUNDARY;
}


#endif // CGAL_PREDICATES_ON_POINTSH2_H
