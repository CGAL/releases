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
// source        : TriangleH2.fw
// file          : include/CGAL/TriangleH2.h
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


#ifndef CGAL_TRIANGLEH2_H
#define CGAL_TRIANGLEH2_H

#ifndef CGAL_POINTH2_H
#include <CGAL/PointH2.h>
#endif // CGAL_POINTH2_H
#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#include <CGAL/predicates_on_pointsH2.h>
#endif // CGAL_PREDICATES_ON_POINTSH2_H

template <class FT, class RT>
class CGAL_Triangle_repH2 : public CGAL_Rep
{

friend class CGAL_TriangleH2<FT,RT>;

            CGAL_Triangle_repH2()
            {
            }
            CGAL_Triangle_repH2(const CGAL_PointH2<FT,RT> v1,
                                const CGAL_PointH2<FT,RT> v2,
                                const CGAL_PointH2<FT,RT> v3)
            {
              A[0] = v1;
              A[1] = v2;
              A[2] = v3;
              orientation = CGAL_orientation(v1,v2,v3);
            }
            CGAL_Triangle_repH2(const CGAL_Triangle_repH2<FT,RT>& tbc)
            {
              A[0] = tbc.A[0];
              A[1] = tbc.A[1];
              A[2] = tbc.A[2];
              orientation = tbc.orientation;
            }

            CGAL_PointH2<FT,RT>   A[3];
            CGAL_Orientation      orientation;
};

template <class FT, class RT>
class CGAL_TriangleH2 : public CGAL_Handle
{
public:
                       CGAL_TriangleH2();
                       CGAL_TriangleH2(const CGAL_TriangleH2<FT,RT>& t);
                       CGAL_TriangleH2(const CGAL_PointH2<FT,RT>& p,
                                       const CGAL_PointH2<FT,RT>& q,
                                       const CGAL_PointH2<FT,RT>& r);

    CGAL_TriangleH2<FT,RT>&
                       operator=(const CGAL_TriangleH2<FT,RT>& t);

    CGAL_Bbox_2        bbox() const;

    CGAL_TriangleH2<FT,RT>
                       transform(const CGAL_Aff_transformationH2<FT,RT>&) const;

    CGAL_Orientation   orientation() const;

    CGAL_Oriented_side oriented_side(const CGAL_PointH2<FT,RT>& ) const;
    CGAL_Bounded_side  bounded_side(const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_positive_side( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_negative_side( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_boundary( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_bounded_side( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_unbounded_side(const CGAL_PointH2<FT,RT>& )const;
    bool               is_degenerate() const;

    bool               operator==( const CGAL_TriangleH2<FT,RT>& ) const;
    bool               operator!=( const CGAL_TriangleH2<FT,RT>& ) const;
    bool               identical ( const CGAL_TriangleH2<FT,RT>& ) const;
    int                id() const;

    // bool            oriented_equal( const CGAL_TriangleH2<FT,RT>& ) const;
    // bool            unoriented_equal( const CGAL_TriangleH2<FT,RT>& ) const;

    CGAL_PointH2<FT,RT>
                       vertex(int i) const;
    CGAL_PointH2<FT,RT>
                       operator[](int i) const;

protected:
    CGAL_Triangle_repH2<FT,RT>*    ptr() const;
};

template < class FT, class RT >
inline
CGAL_Triangle_repH2<FT,RT>*
CGAL_TriangleH2<FT,RT>::ptr() const
{ return (CGAL_Triangle_repH2<FT,RT>*)PTR; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_TriangleH2<FT,RT>::CGAL_TriangleH2()
{ PTR = new CGAL_Triangle_repH2<FT,RT>(); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_TriangleH2<FT,RT>::CGAL_TriangleH2(const CGAL_TriangleH2<FT,RT>& t)
 : CGAL_Handle((CGAL_Handle&) t)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_TriangleH2<FT,RT>::CGAL_TriangleH2(const CGAL_PointH2<FT,RT>& p,
                                        const CGAL_PointH2<FT,RT>& q,
                                        const CGAL_PointH2<FT,RT>& r)
{ PTR = new CGAL_Triangle_repH2<FT,RT>(p,q,r); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_TriangleH2<FT,RT>&
CGAL_TriangleH2<FT,RT>::operator=(const CGAL_TriangleH2<FT,RT> &t)
{
  CGAL_Handle::operator=(t);
  return *this;
}
template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_PointH2<FT,RT>
CGAL_TriangleH2<FT,RT>::vertex(int i) const
{ return ptr()->A[ i % 3 ]; }

template <class FT, class RT>
inline
CGAL_PointH2<FT,RT>
CGAL_TriangleH2<FT,RT>::operator[](int i) const
{ return vertex(i); }

template <class FT, class RT>
inline
CGAL_Orientation
CGAL_TriangleH2<FT,RT>::orientation() const
{ return ptr()->orientation; }
template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Oriented_side
CGAL_TriangleH2<FT,RT>::oriented_side( const CGAL_PointH2<FT,RT>& p) const
{
  CGAL_Orientation o12 = CGAL_orientation( vertex(1), vertex(2), p);
  CGAL_Orientation o23 = CGAL_orientation( vertex(2), vertex(3), p);
  CGAL_Orientation o31 = CGAL_orientation( vertex(3), vertex(1), p);

  if (ptr()->orientation == CGAL_CLOCKWISE)
  {
      if (  (o12 == CGAL_COUNTERCLOCKWISE)
          ||(o23 == CGAL_COUNTERCLOCKWISE)
          ||(o31 == CGAL_COUNTERCLOCKWISE) )
      {
          return CGAL_ON_POSITIVE_SIDE;
      }
      if (  (o12 == CGAL_COLLINEAR)
          ||(o23 == CGAL_COLLINEAR)
          ||(o31 == CGAL_COLLINEAR) )
      {
          return CGAL_ON_ORIENTED_BOUNDARY;
      }
      else
      {
          return CGAL_ON_NEGATIVE_SIDE;
      }
  }
  else       // COUNTERCLOCKWISE
  {
      if (  (o12 == CGAL_CLOCKWISE)
          ||(o23 == CGAL_CLOCKWISE)
          ||(o31 == CGAL_CLOCKWISE) )
      {
          return CGAL_ON_NEGATIVE_SIDE;
      }
      if (  (o12 == CGAL_COLLINEAR)
          ||(o23 == CGAL_COLLINEAR)
          ||(o31 == CGAL_COLLINEAR) )
      {
          return CGAL_ON_ORIENTED_BOUNDARY;
      }
      else
      {
          return CGAL_ON_POSITIVE_SIDE;
      }
  }
}

template <class FT, class RT>
inline
bool
CGAL_TriangleH2<FT,RT>::
has_on_positive_side( const CGAL_PointH2<FT,RT>& p) const
{ return ( oriented_side(p) == CGAL_ON_POSITIVE_SIDE ); }

template <class FT, class RT>
inline
bool
CGAL_TriangleH2<FT,RT>::has_on_boundary(const CGAL_PointH2<FT,RT>& p) const
{ return oriented_side(p) == CGAL_ON_ORIENTED_BOUNDARY; }

template <class FT, class RT>
inline
bool
CGAL_TriangleH2<FT,RT>::
has_on_negative_side( const CGAL_PointH2<FT,RT>& p) const
{ return  oriented_side(p) == CGAL_ON_NEGATIVE_SIDE; }

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
CGAL_Bounded_side
CGAL_TriangleH2<FT,RT>::bounded_side(const CGAL_PointH2<FT,RT>& p) const
{
  CGAL_kernel_precondition( ! is_degenerate() );

  CGAL_Orientation o12 = CGAL_orientation( vertex(1), vertex(2), p);
  CGAL_Orientation o23 = CGAL_orientation( vertex(2), vertex(3), p);
  CGAL_Orientation o31 = CGAL_orientation( vertex(3), vertex(1), p);
  CGAL_Orientation ori = orientation();
  CGAL_Orientation opp = CGAL_opposite( ori);

  if ( (o12 == opp) || (o23 == opp) || (o31 == opp) )
  {
      return CGAL_ON_UNBOUNDED_SIDE;
  }
  if ( (o12 == ori) && (o23 == ori) && (o31 == ori) )
  {
      return CGAL_ON_BOUNDED_SIDE;
  }
  return CGAL_ON_BOUNDARY;
}

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_TriangleH2<FT,RT>::has_on_bounded_side(const CGAL_PointH2<FT,RT>& p) const
{
  CGAL_kernel_precondition( ! is_degenerate() );

  CGAL_Orientation o12 = CGAL_orientation( vertex(1), vertex(2), p);
  CGAL_Orientation o23 = CGAL_orientation( vertex(2), vertex(3), p);
  CGAL_Orientation o31 = CGAL_orientation( vertex(3), vertex(1), p);
  CGAL_Orientation ori = ptr()->orientation;

  return  ( (o12 == ori) && (o23 == ori) && (o31 == ori) );
}

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_TriangleH2<FT,RT>::has_on_unbounded_side(const CGAL_PointH2<FT,RT>& p)
                                                                          const
{
  CGAL_kernel_precondition( ! is_degenerate() );

  CGAL_Orientation o12 = CGAL_orientation( vertex(1), vertex(2), p);
  CGAL_Orientation o23 = CGAL_orientation( vertex(2), vertex(3), p);
  CGAL_Orientation o31 = CGAL_orientation( vertex(3), vertex(1), p);
  CGAL_Orientation opp = CGAL_opposite( ptr()->orientation );

  return  ( (o12 == opp) || (o23 == opp) || (o31 == opp) );
}

template <class FT, class RT>
inline
bool
CGAL_TriangleH2<FT,RT>::is_degenerate() const
{ return (ptr()->orientation == CGAL_COLLINEAR); }

template <class FT, class RT>
inline
CGAL_Bbox_2
CGAL_TriangleH2<FT,RT>::bbox() const
{ return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox(); }
template <class FT, class RT>
CGAL_TriangleH2<FT,RT>
CGAL_TriangleH2<FT,RT>::
transform( const CGAL_Aff_transformationH2<FT,RT>& t) const
{
  return CGAL_TriangleH2<FT,RT>(t.transform(ptr()->A[0]),
                                t.transform(ptr()->A[1]),
                                t.transform(ptr()->A[2]) );
}
template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
CGAL_TriangleH2<FT,RT>::operator==(const CGAL_TriangleH2<FT,RT>& t) const
{
  int j = 0;
  while ( (t.vertex(0) != vertex(j)) && (j < 3) ) j++;
  if ( j == 3)
  {
      return false;
  }
  if ( (t.vertex(1) == vertex(j+1)) && (t.vertex(2) == vertex(j+2)) )
  {
      return true;
  }
  return false;
}

template <class FT, class RT>
inline
bool
CGAL_TriangleH2<FT,RT>::operator!=(const CGAL_TriangleH2<FT,RT>& t) const
{ return !(*this == t); }    /* XXX */

template <class FT, class RT>
inline
bool
CGAL_TriangleH2<FT,RT>::identical(const CGAL_TriangleH2<FT,RT>& t) const
{ return (PTR == t.PTR) ; }

template <class FT, class RT>
inline
int
CGAL_TriangleH2<FT,RT>::id() const
{ return (int)PTR; }

#ifndef CGAL_NO_OSTREAM_INSERT_TRIANGLEH2
template < class FT, class RT >
ostream &
operator<<(ostream &os, const CGAL_TriangleH2<FT,RT> &t)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << t[0] << ' ' << t[1] << ' ' << t[2];
    case CGAL_IO::BINARY :
        return os << t[0] << t[1]  << t[2];
    default:
        return os<< "TriangleH2(" << t[0] << ", " << t[1] << ", " << t[2] <<")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_TRIANGLEH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_TRIANGLEH2
template < class FT, class RT >
istream &
operator>>(istream &is, CGAL_TriangleH2<FT,RT> &t)
{
  CGAL_PointH2<FT,RT> p, q, r;
  is >> p >> q >> r;
  t = CGAL_TriangleH2<FT,RT>(p, q, r);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TRIANGLEH2


#endif // CGAL_TRIANGLEH2_H
