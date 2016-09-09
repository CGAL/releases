// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/Homogeneous/Iso_cuboidH3.h
// package       : H3 (2.49)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/02/06 12:35:26 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_ISO_CUBOIDH3_H
#define CGAL_ISO_CUBOIDH3_H

#include <CGAL/Twotuple.h>

CGAL_BEGIN_NAMESPACE

template <class R_>
class Iso_cuboidH3
  : public R_::Iso_cuboid_handle_3
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::RT                   RT;
  typedef typename R_::FT                   FT;
  typedef typename R_::Point_3              Point_3;
  typedef typename R_::Aff_transformation_3 Aff_transformation_3;

public:
  typedef R_                 R;

  typedef typename R::Iso_cuboid_handle_3             Iso_cuboid_handle_3_;
  typedef typename Iso_cuboid_handle_3_::element_type Iso_cuboid_ref_3;

  Iso_cuboidH3()
    : Iso_cuboid_handle_3_(Iso_cuboid_ref_3()) {}

  Iso_cuboidH3(const Point_3& p, const Point_3& q);

  Iso_cuboidH3(const RT& min_hx, const RT& min_hy, const RT& min_hz,
               const RT& max_hx, const RT& max_hy, const RT& max_hz, 
               const RT& hw);

  Iso_cuboidH3(const RT& min_hx, const RT& min_hy, const RT& min_hz,
               const RT& max_hx, const RT& max_hy, const RT& max_hz);

  bool      operator==(const Iso_cuboidH3<R>& s) const;
  bool      operator!=(const Iso_cuboidH3<R>& s) const;

  const Point_3 & min() const;
  const Point_3 & max() const;
  Point_3  vertex(int i) const;
  Point_3  operator[](int i) const;

  Iso_cuboidH3<R>
            transform(const Aff_transformation_3& t) const;
  Bounded_side
            bounded_side(const Point_3& p) const;
  bool      has_on(const Point_3& p) const;
  bool      has_on_boundary(const Point_3& p) const;
  bool      has_on_bounded_side(const Point_3& p) const;
  bool      has_on_unbounded_side(const Point_3& p) const;
  bool      is_degenerate() const;
  Bbox_2    bbox() const;
  FT        xmin() const;
  FT        ymin() const;
  FT        zmin() const;
  FT        xmax() const;
  FT        ymax() const;
  FT        zmax() const;
  FT        min_coord(int i) const;
  FT        max_coord(int i) const;

  FT        volume() const;

};

template < class R >
CGAL_KERNEL_LARGE_INLINE
Iso_cuboidH3<R>::
Iso_cuboidH3(const typename Iso_cuboidH3<R>::Point_3& p,
	     const typename Iso_cuboidH3<R>::Point_3& q)
{
  bool px_k_qx = ( p.hx()*q.hw() < q.hx()*p.hw() );
  bool py_k_qy = ( p.hy()*q.hw() < q.hy()*p.hw() );
  bool pz_k_qz = ( p.hz()*q.hw() < q.hz()*p.hw() );

  RT minx;
  RT miny;
  RT minz;
  RT maxx;
  RT maxy;
  RT maxz;
  RT minw = p.hw()*q.hw();
  RT maxw = p.hw()*q.hw();
  if ( px_k_qx )
  {
      minx = p.hx()*q.hw();
      maxx = q.hx()*p.hw();
  }
  else
  {
      minx = q.hx()*p.hw();
      maxx = p.hx()*q.hw();
  }
  if ( py_k_qy )
  {
      miny = p.hy()*q.hw();
      maxy = q.hy()*p.hw();
  }
  else
  {
      miny = q.hy()*p.hw();
      maxy = p.hy()*q.hw();
  }
  if ( pz_k_qz )
  {
      minz = p.hz()*q.hw();
      maxz = q.hz()*p.hw();
  }
  else
  {
      minz = q.hz()*p.hw();
      maxz = p.hz()*q.hw();
  }
  initialize_with( Iso_cuboid_ref_3 ( Point_3(minx, miny, minz, minw),
                                      Point_3(maxx, maxy, maxz, maxw) ));
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
Iso_cuboidH3<R>::
Iso_cuboidH3(const RT& min_hx, const RT& min_hy, const RT& min_hz,
             const RT& max_hx, const RT& max_hy, const RT& max_hz)
{
  initialize_with( 
     Iso_cuboid_ref_3 ( Point_3(min_hx, min_hy, min_hz, RT(1)),
                        Point_3(max_hx, max_hy, max_hz, RT(1)) ));
}

template < class R >
CGAL_KERNEL_LARGE_INLINE
Iso_cuboidH3<R>::
Iso_cuboidH3(const RT& min_hx, const RT& min_hy, const RT& min_hz,
             const RT& max_hx, const RT& max_hy, const RT& max_hz, 
             const RT& hw)
{
  initialize_with( Iso_cuboid_ref_3( Point_3(min_hx, min_hy, min_hz, hw),
                                     Point_3(max_hx, max_hy, max_hz, hw) ));
}

template < class R >
CGAL_KERNEL_INLINE
bool
Iso_cuboidH3<R>::
operator==(const Iso_cuboidH3<R>& r) const
{ return  (min() == r.min()) && (max() == r.max()); }

template < class R >
inline
bool
Iso_cuboidH3<R>::
operator!=(const Iso_cuboidH3<R>& r) const
{ return !(*this == r); }

template < class R >
inline
const typename Iso_cuboidH3<R>::Point_3 &
Iso_cuboidH3<R>::min() const
{ return  Ptr()->e0; }

template < class R >
inline
const typename Iso_cuboidH3<R>::Point_3 &
Iso_cuboidH3<R>::max() const
{ return  Ptr()->e1; }

template < class R >
inline
typename Iso_cuboidH3<R>::FT
Iso_cuboidH3<R>::xmin() const
{ return  FT( min().hx() ) / FT( min().hw() ); }

template < class R >
inline
typename Iso_cuboidH3<R>::FT
Iso_cuboidH3<R>::ymin() const
{ return  FT( min().hy() ) / FT( min().hw() ); }

template < class R >
inline
typename Iso_cuboidH3<R>::FT
Iso_cuboidH3<R>::zmin() const
{ return  FT( min().hz() ) / FT( min().hw() ); }

template < class R >
inline
typename Iso_cuboidH3<R>::FT
Iso_cuboidH3<R>::xmax() const
{ return  FT( max().hx() ) / FT( max().hw() ); }

template < class R >
inline
typename Iso_cuboidH3<R>::FT
Iso_cuboidH3<R>::ymax() const
{ return  FT( max().hy() ) / FT( max().hw() ); }

template < class R >
inline
typename Iso_cuboidH3<R>::FT
Iso_cuboidH3<R>::zmax() const
{ return  FT( max().hz() ) / FT( max().hw() ); }

template < class R >
inline
typename Iso_cuboidH3<R>::FT
Iso_cuboidH3<R>::min_coord(int i) const
{ 
   CGAL_kernel_precondition(i == 0 || i == 1 || i == 2);
   if ( i == 0 )
       return xmin();
   else if (i == 1)
       return ymin();
   return zmin();
}

template < class R >
inline
typename Iso_cuboidH3<R>::FT
Iso_cuboidH3<R>::max_coord(int i) const
{ 
   CGAL_kernel_precondition(i == 0 || i == 1 || i == 2);
   if ( i == 0 )
      return xmax();
   else if ( i == 1 )
      return ymax();
   return zmax();
}

template < class R >
inline
typename Iso_cuboidH3<R>::FT
Iso_cuboidH3<R>::volume() const
{ return  (xmax() - xmin()) * (ymax() - ymin()) * (zmax() - zmin()); }

template < class R >
CGAL_KERNEL_LARGE_INLINE
typename Iso_cuboidH3<R>::Point_3
Iso_cuboidH3<R>::vertex(int i) const
{
  switch (i%8)
  {
    case 0: return min();
    case 1: return Point_3( max().hx(), min().hy(),
		                   min().hz(), min().hw() );
    case 2: return Point_3( max().hx(), max().hy(),
		                   min().hz(), min().hw() );
    case 3: return Point_3( min().hx(), max().hy(),
		                   min().hz(), min().hw() );
    case 4: return Point_3( min().hx(), max().hy(),
		                   max().hz(), min().hw() );
    case 5: return Point_3( min().hx(), min().hy(),
		                   max().hz(), min().hw() );
    case 6: return Point_3( max().hx(), min().hy(),
		                   max().hz(), min().hw() );
    default: /*case 7:*/ return max();
  }
}

template < class R >
inline
typename Iso_cuboidH3<R>::Point_3
Iso_cuboidH3<R>::operator[](int i) const
{ return vertex(i); }

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
Bounded_side
Iso_cuboidH3<R>::
bounded_side(const typename Iso_cuboidH3<R>::Point_3& p) const
{
  if (    (p.hx()*min().hw() < min().hx()*p.hw() )
        ||(p.hy()*min().hw() < min().hy()*p.hw() )
        ||(p.hz()*min().hw() < min().hz()*p.hw() )
        ||(p.hx()*max().hw() > max().hx()*p.hw() )
        ||(p.hy()*max().hw() > max().hy()*p.hw() )
        ||(p.hz()*max().hw() > max().hz()*p.hw() )  )
  { return ON_UNBOUNDED_SIDE; }
  if (    (p.hx()*min().hw() == min().hx()*p.hw() )
        ||(p.hy()*min().hw() == min().hy()*p.hw() )
        ||(p.hz()*min().hw() == min().hz()*p.hw() )
        ||(p.hx()*max().hw() == max().hx()*p.hw() )
        ||(p.hy()*max().hw() == max().hy()*p.hw() )
        ||(p.hz()*max().hw() == max().hz()*p.hw() )  )
  { return ON_BOUNDARY; }
  else
  { return ON_BOUNDED_SIDE; }
}

template < class R >
inline
bool
Iso_cuboidH3<R>::
has_on_boundary(const typename Iso_cuboidH3<R>::Point_3& p) const
{ return ( bounded_side(p) == ON_BOUNDARY ); }

template < class R >
inline
bool
Iso_cuboidH3<R>::has_on(const typename Iso_cuboidH3<R>::Point_3& p) const
{ return ( bounded_side(p) == ON_BOUNDARY ); }

template < class R >
inline
bool
Iso_cuboidH3<R>::
has_on_bounded_side(const typename Iso_cuboidH3<R>::Point_3& p) const
{ return ( bounded_side(p) == ON_BOUNDED_SIDE ); }

template < class R >
CGAL_KERNEL_INLINE
bool
Iso_cuboidH3<R>::
has_on_unbounded_side(const typename Iso_cuboidH3<R>::Point_3& p) const
{
  return (   ( lexicographically_xyz_smaller(p,min() ))
           ||( lexicographically_xyz_smaller(max(),p ))  );
}

template < class R >
CGAL_KERNEL_INLINE
bool
Iso_cuboidH3<R>::is_degenerate() const
{
  return (  ( min().hx() == max().hx() )
         || ( min().hy() == max().hy() )
         || ( min().hz() == max().hz() ) );
}

template < class R >
inline
Bbox_2
Iso_cuboidH3<R>::bbox() const
{ return  min().bbox() + max().bbox(); }

template < class R >
CGAL_KERNEL_INLINE
Iso_cuboidH3<R>
Iso_cuboidH3<R>::
transform(const typename Iso_cuboidH3<R>::Aff_transformation_3&t) const
{
  return Iso_cuboidH3<R>(t.transform(min() ),
                             t.transform(max() ) );
}

#ifndef CGAL_NO_OSTREAM_INSERT_ISO_CUBOIDH3
template < class R >
std::ostream& operator<<(std::ostream& os, const Iso_cuboidH3<R>& r)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << r.min() << ' ' << r.max();
    case IO::BINARY :
        return os << r.min() << r.max();
    default:
        return os << "Iso_cuboidH3(" << r.min() << ", " << r.max() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_ISO_CUBOIDH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOIDH3
template < class R >
std::istream& operator>>(std::istream& is, Iso_cuboidH3<R>& r)
{
  typename R::Point_3 p, q;
  is >> p >> q;
  r = Iso_cuboidH3<R>(p, q);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_ISO_CUBOIDH3

CGAL_END_NAMESPACE

#endif // CGAL_ISO_CUBOIDH3_H
