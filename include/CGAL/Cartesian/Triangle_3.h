// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Cartesian/Triangle_3.h
// package       : Cartesian_kernel (6.59)
// revision      : $Revision: 1.26 $
// revision_date : $Date: 2002/02/06 12:32:40 $
// author(s)     : Andreas Fabri
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_TRIANGLE_3_H
#define CGAL_CARTESIAN_TRIANGLE_3_H

CGAL_BEGIN_NAMESPACE

template <class R_>
class TriangleC3
  : public R_::Triangle_handle_3
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef typename R_::Point_3              Point_3;
  typedef typename R_::Vector_3             Vector_3;
  typedef typename R_::Plane_3              Plane_3;
  typedef typename R_::Triangle_3           Triangle_3;
  typedef typename R_::Aff_transformation_3 Aff_transformation_3;

  typedef typename R_::Triangle_handle_3         base;
  typedef typename base::element_type            rep;

public:
  typedef R_                                     R;

  TriangleC3()
    : base(rep()) {}

  TriangleC3(const Point_3 &p, const Point_3 &q, const Point_3 &r)
    : base(rep(p, q, r)) {}

  bool       operator==(const TriangleC3 &t) const;
  bool       operator!=(const TriangleC3 &t) const;

  Plane_3    supporting_plane() const;

  Triangle_3 transform(const Aff_transformation_3 &t) const
  {
    return TriangleC3<R>(t.transform(vertex(0)),
                t.transform(vertex(1)),
                t.transform(vertex(2)));
  }

  bool       has_on(const Point_3 &p) const;
  bool       is_degenerate() const;

  const Point_3 & vertex(int i) const;
  const Point_3 & operator[](int i) const;

  Bbox_3     bbox() const;
  
  FT         squared_area() const;
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template < class R >
bool
TriangleC3<R>::operator==(const TriangleC3<R> &t) const
{
  if (identical(t))
      return true;

  int i;
  for(i=0; i<3; i++)
    if ( vertex(0) == t.vertex(i) )
       break;

  return (i<3) && vertex(1) == t.vertex(i+1) && vertex(2) == t.vertex(i+2);
}

template < class R >
inline
bool
TriangleC3<R>::operator!=(const TriangleC3<R> &t) const
{
  return !(*this == t);
}

template < class R >
const typename TriangleC3<R>::Point_3 &
TriangleC3<R>::vertex(int i) const
{
  if (i<0) i=(i%3)+3;
  else if (i>2) i=i%3;
  return (i==0) ? Ptr()->e0 :
         (i==1) ? Ptr()->e1 :
                  Ptr()->e2;
}

template < class R >
inline
const typename TriangleC3<R>::Point_3 &
TriangleC3<R>::operator[](int i) const
{
  return vertex(i);
}

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
typename TriangleC3<R>::FT
TriangleC3<R>::squared_area() const
{
  typename R::Vector_3 v1 = vertex(1)-vertex(0);
  typename R::Vector_3 v2 = vertex(2)-vertex(0);
  typename R::Vector_3 v3 = cross_product(v1, v2);
  return (v3.squared_length())/FT(4);
}

template < class R >
inline
typename TriangleC3<R>::Plane_3
TriangleC3<R>::supporting_plane() const
{
  return Plane_3(vertex(0), vertex(1), vertex(2));
}

template < class R >
Bbox_3
TriangleC3<R>::bbox() const
{
  return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}

template < class R >
bool
TriangleC3<R>::
has_on(const typename TriangleC3<R>::Point_3 &p) const
{
  Point_3  o  = vertex(0) + supporting_plane().orthogonal_vector();
  Vector_3 v0 = vertex(0)-o,
           v1 = vertex(1)-o,
           v2 = vertex(2)-o;

  FT alpha, beta, gamma;
  solve(v0, v1, v2, p-o, alpha, beta, gamma);
  return (alpha >= FT(0)) && (beta >= FT(0)) && (gamma >= FT(0))
      && ((alpha+beta+gamma == FT(1)));
}

template < class R >
bool
TriangleC3<R>::is_degenerate() const
{
  return collinear(vertex(0),vertex(1),vertex(2));
}

#ifndef CGAL_NO_OSTREAM_INSERT_TRIANGLEC3
template < class R >
std::ostream &
operator<<(std::ostream &os, const TriangleC3<R> &t)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << t[0] << ' ' << t[1] << ' ' << t[2];
    case IO::BINARY :
        return os << t[0]  << t[1]  << t[2];
    default:
        os << "TriangleC3(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
        return os;
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_TRIANGLEC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TRIANGLEC3
template < class R >
std::istream &
operator>>(std::istream &is, TriangleC3<R> &t)
{
    typename R::Point_3 p, q, r;

    is >> p >> q >> r;

    if (is)
	t = TriangleC3<R>(p, q, r);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TRIANGLEC3

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_TRIANGLE_3_H
