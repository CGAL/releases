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
// source        : TriangleH3.fw
// file          : include/CGAL/TriangleH3.h
// package       : H3 (2.3.7)
// revision      : 2.3.7
// revision_date : 03 Dec 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGLEH3_H
#define CGAL_TRIANGLEH3_H

#ifndef PREDICATES_ON_POINTSH3_H
#include <CGAL/predicates_on_pointsH3.h>
#endif // PREDICATES_ON_POINTSH3_H
#ifndef CGAL_PLANEH3_H
#include <CGAL/PlaneH3.h>
#endif // CGAL_PLANEH3_H
#ifndef CGAL_TETRAHEDRONH3_H
#include <CGAL/TetrahedronH3.h>
#endif // CGAL_TETRAHEDRONH3_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT >
class TriangleH3 : public Handle
{
public:
  TriangleH3();
  TriangleH3(const TriangleH3<FT,RT> &t);
  TriangleH3(const PointH3<FT,RT> &p,
                  const PointH3<FT,RT> &q,
                  const PointH3<FT,RT> &r);

  ~TriangleH3();

  TriangleH3<FT,RT> &
                operator=(const TriangleH3<FT,RT> &t);

  bool          operator==(const TriangleH3<FT,RT> &t) const;
  bool          operator!=(const TriangleH3<FT,RT> &t) const;
  bool          identical(const TriangleH3<FT,RT> &t) const;
  int           id() const;

  PlaneH3<FT,RT>
                supporting_plane() const;

  TriangleH3<FT,RT>
                transform(const Aff_transformationH3<FT,RT> &t) const;
  bool          has_on(const PointH3<FT,RT> &p) const;
  bool          nondegenerate_has_on(const PointH3<FT,RT> &p) const;
  bool          is_degenerate() const;


  PointH3<FT,RT> vertex(int i) const;
  PointH3<FT,RT> operator[](int i) const;

  Bbox_3   bbox() const;

private:
  _Threetuple< PointH3<FT,RT> >*   ptr() const;
};


template < class FT, class RT >
inline
_Threetuple< PointH3<FT,RT> > *
TriangleH3<FT,RT>::ptr() const
{ return (_Threetuple< PointH3<FT,RT> >*)PTR; }

template < class FT, class RT >
inline
TriangleH3<FT,RT>::TriangleH3()
{ PTR = new _Threetuple< PointH3<FT,RT> >; }

template < class FT, class RT >
inline
TriangleH3<FT,RT>::TriangleH3(const TriangleH3<FT,RT> &t)
  : Handle( (Handle&) t)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
TriangleH3<FT,RT>::TriangleH3(const PointH3<FT,RT> &p,
                                        const PointH3<FT,RT> &q,
                                        const PointH3<FT,RT> &r)
{ PTR = new _Threetuple< PointH3<FT,RT> >(p, q, r); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
TriangleH3<FT,RT> &
TriangleH3<FT,RT>::operator=(const TriangleH3<FT,RT> &t)
{ Handle::operator=(t); return *this; }
template < class FT, class RT >
inline
TriangleH3<FT,RT>::~TriangleH3()
{}

template < class FT, class RT >
CGAL_KERNEL_LARGE_INLINE
bool
TriangleH3<FT,RT>::operator==(const TriangleH3<FT,RT> &t) const
{
  int i;
  for(i = 0; (i< 3) && (vertex(0) != t.vertex(i) ); i++) {}
  if (i==3)
  {
      return false;
  }
  return ( vertex(1) == t.vertex(i+1) && vertex(2) == t.vertex(i+2) );
}

template < class FT, class RT >
inline
bool
TriangleH3<FT,RT>::identical(const TriangleH3<FT,RT> &t) const
{ return PTR == t.PTR; }

template < class FT, class RT >
inline
int
TriangleH3<FT,RT>::id() const
{ return (int) PTR ; }
template < class FT, class RT >
inline
bool
TriangleH3<FT,RT>::operator!=(const TriangleH3<FT,RT> &t) const
{ return !(*this == t); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH3<FT,RT>
TriangleH3<FT,RT>::vertex(int i) const
{
  switch (i)
  {
      case 0:  return ptr()->e0;
      case 1:  return ptr()->e1;
      case 2:  return ptr()->e2;
      default: return vertex(i%3);
  }
  // return PointH3<FT,RT>();
}
template < class FT, class RT >
inline
PointH3<FT,RT>
TriangleH3<FT,RT>::operator[](int i) const
{ return vertex(i); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
PlaneH3<FT,RT>
TriangleH3<FT,RT>::supporting_plane() const
{ return PlaneH3<FT,RT>(vertex(0), vertex(1), vertex(2)); }

template < class FT, class RT >
inline
Bbox_3
TriangleH3<FT,RT>::bbox() const
{ return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
TriangleH3<FT,RT>
TriangleH3<FT,RT>::
transform(const Aff_transformationH3<FT,RT> &t) const
{
  return TriangleH3<FT,RT>(t.transform(vertex(0)),
                                t.transform(vertex(1)),
                                t.transform(vertex(2)));
}


#ifndef NO_OSTREAM_INSERT_TRIANGLEH3
template < class FT, class RT >
std::ostream &operator<<(std::ostream &os, const TriangleH3<FT,RT> &t)
{
  switch(os.iword(IO::mode))
  {
      case IO::ASCII :
          return os << t[0] << ' ' << t[1] << ' ' << t[2];
      case IO::BINARY :
          return os << t[0]  << t[1]  << t[2];
      default:
          os << "TriangleH3(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
          return os;
  }
}
#endif // NO_OSTREAM_INSERT_TRIANGLEH3

#ifndef NO_ISTREAM_EXTRACT_TRIANGLEH3
template < class FT, class RT >
std::istream &operator>>(std::istream &is, TriangleH3<FT,RT> &t)
{
  PointH3<FT,RT> p, q, r;
  is >> p >> q >> r;
  t = TriangleH3<FT,RT>(p, q, r);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_TRIANGLEH3
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
TriangleH3<FT,RT>::
nondegenerate_has_on(const PointH3<FT,RT> &p) const
{
  CGAL_kernel_precondition( !is_degenerate() );
  PlaneH3<FT,RT> sup_pl = supporting_plane();
  if ( !sup_pl.has_on(p) )
  {
      return false;
  }
  TetrahedronH3<FT,RT> tetrapak( vertex(0),
                                      vertex(1),
                                      vertex(2),
                                      vertex(0) + sup_pl.orthogonal_vector());
  return tetrapak.has_on_boundary(p);
}

template < class FT, class RT >
CGAL_KERNEL_LARGE_INLINE
bool
TriangleH3<FT,RT>::has_on(const PointH3<FT,RT> &p) const
{
  if (!is_degenerate() )
  {
      return nondegenerate_has_on(p);
  }
  PointH3<FT,RT> minp( vertex(0) );
  PointH3<FT,RT> maxp( vertex(1) );
  if (lexicographically_xyz_smaller(vertex(1),vertex(0)) )
  {
      minp = vertex(1);
      maxp = vertex(0);
  }
  if (lexicographically_xyz_smaller(vertex(2),minp ) )
  {
      minp = vertex(2);
  }
  if (lexicographically_xyz_smaller(maxp, vertex(2)) )
  {
      maxp = vertex(2);
  }
  if (minp == maxp)
  {
      return (p == maxp);
  }
  SegmentH3<FT,RT> s(minp,maxp);
  return s.has_on(p);
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
TriangleH3<FT,RT>::is_degenerate() const
{ return collinear(vertex(0),vertex(1),vertex(2)); }

CGAL_END_NAMESPACE


#endif // CGAL_TRIANGLEH3_H
