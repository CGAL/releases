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
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// source        : TriangleH2.fw
// file          : include/CGAL/TriangleH2.h
// package       : H2 (2.4.8)
// revision      : 2.4.8
// revision_date : 10 Dec 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
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

CGAL_BEGIN_NAMESPACE

template <class FT, class RT>
class Triangle_repH2 : public Rep
{

friend class TriangleH2<FT,RT>;

            Triangle_repH2()
            {
            }
            Triangle_repH2(const PointH2<FT,RT> v1,
                                const PointH2<FT,RT> v2,
                                const PointH2<FT,RT> v3)
            {
              A[0] = v1;
              A[1] = v2;
              A[2] = v3;
              _orientation = CGAL::orientation(v1,v2,v3);
            }
            Triangle_repH2(const Triangle_repH2<FT,RT>& tbc)
            {
              A[0] = tbc.A[0];
              A[1] = tbc.A[1];
              A[2] = tbc.A[2];
              _orientation = tbc._orientation;
            }

            PointH2<FT,RT>   A[3];
            Orientation      _orientation;
};

template <class FT, class RT>
class TriangleH2 : public Handle
{
public:
                       TriangleH2();
                       TriangleH2(const TriangleH2<FT,RT>& t);
                       TriangleH2(const PointH2<FT,RT>& p,
                                       const PointH2<FT,RT>& q,
                                       const PointH2<FT,RT>& r);

    TriangleH2<FT,RT>&
                       operator=(const TriangleH2<FT,RT>& t);

    Bbox_2        bbox() const;

    TriangleH2<FT,RT>
                       transform(const Aff_transformationH2<FT,RT>&) const;

    Orientation   orientation() const;

    Oriented_side oriented_side(const PointH2<FT,RT>& ) const;
    Bounded_side  bounded_side(const PointH2<FT,RT>& ) const;
    bool               has_on_positive_side( const PointH2<FT,RT>& ) const;
    bool               has_on_negative_side( const PointH2<FT,RT>& ) const;
    bool               has_on_boundary( const PointH2<FT,RT>& ) const;
    bool               has_on_bounded_side( const PointH2<FT,RT>& ) const;
    bool               has_on_unbounded_side(const PointH2<FT,RT>& )const;
    bool               is_degenerate() const;

    bool               operator==( const TriangleH2<FT,RT>& ) const;
    bool               operator!=( const TriangleH2<FT,RT>& ) const;
    bool               identical ( const TriangleH2<FT,RT>& ) const;
    int                id() const;

    // bool            oriented_equal( const TriangleH2<FT,RT>& ) const;
    // bool            unoriented_equal( const TriangleH2<FT,RT>& ) const;

    PointH2<FT,RT>
                       vertex(int i) const;
    PointH2<FT,RT>
                       operator[](int i) const;

protected:
    Triangle_repH2<FT,RT>*    ptr() const;
};

template < class FT, class RT >
inline
Triangle_repH2<FT,RT>*
TriangleH2<FT,RT>::ptr() const
{ return (Triangle_repH2<FT,RT>*)PTR; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
TriangleH2<FT,RT>::TriangleH2()
{ PTR = new Triangle_repH2<FT,RT>(); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
TriangleH2<FT,RT>::TriangleH2(const TriangleH2<FT,RT>& t)
 : Handle((Handle&) t)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
TriangleH2<FT,RT>::TriangleH2(const PointH2<FT,RT>& p,
                                        const PointH2<FT,RT>& q,
                                        const PointH2<FT,RT>& r)
{ PTR = new Triangle_repH2<FT,RT>(p,q,r); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
TriangleH2<FT,RT>&
TriangleH2<FT,RT>::operator=(const TriangleH2<FT,RT> &t)
{
  Handle::operator=(t);
  return *this;
}
template <class FT, class RT>
CGAL_KERNEL_INLINE
PointH2<FT,RT>
TriangleH2<FT,RT>::vertex(int i) const
{ return ptr()->A[ i % 3 ]; }

template <class FT, class RT>
inline
PointH2<FT,RT>
TriangleH2<FT,RT>::operator[](int i) const
{ return vertex(i); }

template <class FT, class RT>
inline
Orientation
TriangleH2<FT,RT>::orientation() const
{ return ptr()->_orientation; }
template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
Oriented_side
TriangleH2<FT,RT>::oriented_side( const PointH2<FT,RT>& p) const
{
  Orientation o12 = CGAL::orientation( vertex(1), vertex(2), p);
  Orientation o23 = CGAL::orientation( vertex(2), vertex(3), p);
  Orientation o31 = CGAL::orientation( vertex(3), vertex(1), p);

  if (ptr()->_orientation == CLOCKWISE)
  {
      if (  (o12 == COUNTERCLOCKWISE)
          ||(o23 == COUNTERCLOCKWISE)
          ||(o31 == COUNTERCLOCKWISE) )
      {
          return ON_POSITIVE_SIDE;
      }
      if (  (o12 == COLLINEAR)
          ||(o23 == COLLINEAR)
          ||(o31 == COLLINEAR) )
      {
          return ON_ORIENTED_BOUNDARY;
      }
      else
      {
          return ON_NEGATIVE_SIDE;
      }
  }
  else       // COUNTERCLOCKWISE
  {
      if (  (o12 == CLOCKWISE)
          ||(o23 == CLOCKWISE)
          ||(o31 == CLOCKWISE) )
      {
          return ON_NEGATIVE_SIDE;
      }
      if (  (o12 == COLLINEAR)
          ||(o23 == COLLINEAR)
          ||(o31 == COLLINEAR) )
      {
          return ON_ORIENTED_BOUNDARY;
      }
      else
      {
          return ON_POSITIVE_SIDE;
      }
  }
}

template <class FT, class RT>
inline
bool
TriangleH2<FT,RT>::
has_on_positive_side( const PointH2<FT,RT>& p) const
{ return ( oriented_side(p) == ON_POSITIVE_SIDE ); }

template <class FT, class RT>
inline
bool
TriangleH2<FT,RT>::has_on_boundary(const PointH2<FT,RT>& p) const
{ return oriented_side(p) == ON_ORIENTED_BOUNDARY; }

template <class FT, class RT>
inline
bool
TriangleH2<FT,RT>::
has_on_negative_side( const PointH2<FT,RT>& p) const
{ return  oriented_side(p) == ON_NEGATIVE_SIDE; }

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
Bounded_side
TriangleH2<FT,RT>::bounded_side(const PointH2<FT,RT>& p) const
{
  CGAL_kernel_precondition( ! is_degenerate() );

  Orientation o12 = CGAL::orientation( vertex(1), vertex(2), p);
  Orientation o23 = CGAL::orientation( vertex(2), vertex(3), p);
  Orientation o31 = CGAL::orientation( vertex(3), vertex(1), p);
  Orientation ori = orientation();
  Orientation opp = opposite( ori);

  if ( (o12 == opp) || (o23 == opp) || (o31 == opp) )
  {
      return ON_UNBOUNDED_SIDE;
  }
  if ( (o12 == ori) && (o23 == ori) && (o31 == ori) )
  {
      return ON_BOUNDED_SIDE;
  }
  return ON_BOUNDARY;
}

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
TriangleH2<FT,RT>::has_on_bounded_side(const PointH2<FT,RT>& p) const
{
  CGAL_kernel_precondition( ! is_degenerate() );

  Orientation o12 = CGAL::orientation( vertex(1), vertex(2), p);
  Orientation o23 = CGAL::orientation( vertex(2), vertex(3), p);
  Orientation o31 = CGAL::orientation( vertex(3), vertex(1), p);
  Orientation ori = ptr()->_orientation;

  return  ( (o12 == ori) && (o23 == ori) && (o31 == ori) );
}

template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
TriangleH2<FT,RT>::has_on_unbounded_side(const PointH2<FT,RT>& p)
                                                                          const
{
  CGAL_kernel_precondition( ! is_degenerate() );

  Orientation o12 = CGAL::orientation( vertex(1), vertex(2), p);
  Orientation o23 = CGAL::orientation( vertex(2), vertex(3), p);
  Orientation o31 = CGAL::orientation( vertex(3), vertex(1), p);
  Orientation opp = opposite( ptr()->_orientation );

  return  ( (o12 == opp) || (o23 == opp) || (o31 == opp) );
}

template <class FT, class RT>
inline
bool
TriangleH2<FT,RT>::is_degenerate() const
{ return (ptr()->_orientation == COLLINEAR); }

template <class FT, class RT>
inline
Bbox_2
TriangleH2<FT,RT>::bbox() const
{ return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox(); }
template <class FT, class RT>
TriangleH2<FT,RT>
TriangleH2<FT,RT>::
transform( const Aff_transformationH2<FT,RT>& t) const
{
  return TriangleH2<FT,RT>(t.transform(ptr()->A[0]),
                                t.transform(ptr()->A[1]),
                                t.transform(ptr()->A[2]) );
}
template <class FT, class RT>
CGAL_KERNEL_MEDIUM_INLINE
bool
TriangleH2<FT,RT>::operator==(const TriangleH2<FT,RT>& t) const
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
TriangleH2<FT,RT>::operator!=(const TriangleH2<FT,RT>& t) const
{ return !(*this == t); }    /* XXX */

template <class FT, class RT>
inline
bool
TriangleH2<FT,RT>::identical(const TriangleH2<FT,RT>& t) const
{ return (PTR == t.PTR) ; }

template <class FT, class RT>
inline
int
TriangleH2<FT,RT>::id() const
{ return (int)PTR; }

#ifndef NO_OSTREAM_INSERT_TRIANGLEH2
template < class FT, class RT >
std::ostream &
operator<<(std::ostream &os, const TriangleH2<FT,RT> &t)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << t[0] << ' ' << t[1] << ' ' << t[2];
    case IO::BINARY :
        return os << t[0] << t[1]  << t[2];
    default:
        return os<< "TriangleH2(" << t[0] << ", " << t[1] << ", " << t[2] <<")";
  }
}
#endif // NO_OSTREAM_INSERT_TRIANGLEH2

#ifndef NO_ISTREAM_EXTRACT_TRIANGLEH2
template < class FT, class RT >
std::istream &
operator>>(std::istream &is, TriangleH2<FT,RT> &t)
{
  PointH2<FT,RT> p, q, r;
  is >> p >> q >> r;
  t = TriangleH2<FT,RT>(p, q, r);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_TRIANGLEH2

CGAL_END_NAMESPACE


#endif // CGAL_TRIANGLEH2_H
