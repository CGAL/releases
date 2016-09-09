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
// file          : include/CGAL/Homogeneous/DirectionH3.h
// package       : H3 (2.49)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2002/02/06 12:35:26 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken  
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_HOMOGENEOUS_DIRECTION_3_H
#define CGAL_HOMOGENEOUS_DIRECTION_3_H

CGAL_BEGIN_NAMESPACE

template < class R_ >
class DirectionH3
  : public R_::Direction_handle_3
{
CGAL_VC7_BUG_PROTECTED
   typedef typename R_::RT                   RT;
   typedef typename R_::FT                   FT;
   typedef typename R_::Point_3              Point_3;
   typedef typename R_::Vector_3             Vector_3;
   typedef typename R_::Segment_3            Segment_3;
   typedef typename R_::Line_3               Line_3;
   typedef typename R_::Ray_3                Ray_3;
   typedef typename R_::Aff_transformation_3 Aff_transformation_3;

   typedef typename R_::Direction_handle_3            Direction_handle_3_;
   typedef typename Direction_handle_3_::element_type Direction_ref_3;

  public:
   typedef R_                 R;

  DirectionH3()
    : Direction_handle_3_(Direction_ref_3()) {}

  DirectionH3(const Point_3 & p )
    : Direction_handle_3_(p) {}

  DirectionH3(const Vector_3 & v )
    : Direction_handle_3_(v) {}

  DirectionH3(const Line_3 & l )
    : Direction_handle_3_(l.direction()) {}

  DirectionH3(const Ray_3 & r )
    : Direction_handle_3_(r.direction()) {}

  DirectionH3(const Segment_3 & s )
    : Direction_handle_3_(s.direction()) {}

  // the fourth argument is not documented.  Should go away ?
  DirectionH3(const RT& x, const RT& y,
              const RT& z, const RT& w = RT(1) )
  {
    if ( w >= RT(0) )
    { initialize_with( Direction_ref_3(x,y,z,w)); }
    else
    { initialize_with( Direction_ref_3(-x,-y,-z,-w)); }
  }

  DirectionH3<R>
        transform(const Aff_transformation_3 &) const ;
  DirectionH3<R>
        operator-() const;

  bool  is_degenerate() const;

  bool  operator==( const DirectionH3<R>& d) const;
  bool  operator!=( const DirectionH3<R>& d) const;

  Vector_3    to_vector() const;
  Vector_3    vector() const { return to_vector(); }

  const RT & dx() const { return Ptr()->e0; }
  const RT & dy() const { return Ptr()->e1; }
  const RT & dz() const { return Ptr()->e2; }
  const RT & x()  const { return Ptr()->e0; }
  const RT & y()  const { return Ptr()->e1; }
  const RT & z()  const { return Ptr()->e2; }
  const RT & hx() const { return Ptr()->e0; }
  const RT & hy() const { return Ptr()->e1; }
  const RT & hz() const { return Ptr()->e2; }

  const RT & delta(int i) const;
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template <class R >
CGAL_KERNEL_INLINE
const typename DirectionH3<R>::RT &
DirectionH3<R>::delta(int i) const
{
  switch (i)
  {
      case 0:  return x();
      case 1:  return y();
      case 2:  return z();
      default: return delta( i%3 );
  }
}

template <class R >
CGAL_KERNEL_INLINE
bool
DirectionH3<R>::operator==( const DirectionH3<R>& d) const
{
  return ( ( hx()*d.hy() == hy()*d.hx() )
        &&( hx()*d.hz() == hz()*d.hx() )
        &&( hy()*d.hz() == hz()*d.hy() )
        &&( CGAL_NTS sign( hx() ) == CGAL_NTS sign( d.hx() ) )
        &&( CGAL_NTS sign( hy() ) == CGAL_NTS sign( d.hy() ) )
        &&( CGAL_NTS sign( hz() ) == CGAL_NTS sign( d.hz() ) ) );
}

template <class R >
inline
bool
DirectionH3<R>::operator!=( const DirectionH3<R>& d) const
{ return !operator==(d); }

template <class R >
CGAL_KERNEL_INLINE
bool
DirectionH3<R>::is_degenerate() const
{ return ((hx() == RT(0)) && (hy() == RT(0)) && (hz() == RT(0))); }

template <class R >
inline
DirectionH3<R>
DirectionH3<R>::operator-() const
{ return DirectionH3<R>(- hx(),- hy(),- hz() ); }

template <class R >
inline
typename DirectionH3<R>::Vector_3
DirectionH3<R>::to_vector() const
{ return Vector_3(dx(), dy(), dz(), RT(1)); }

template <class R>
CGAL_KERNEL_INLINE
DirectionH3<R>
cross_product( const DirectionH3<R>& d1,
               const DirectionH3<R>& d2)
{ return cross_product(d1.to_vector(),d2.to_vector()).direction(); }

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

template <class R >
inline
DirectionH3<R>
DirectionH3<R>::
transform(const typename DirectionH3<R>::Aff_transformation_3& t) const
{ return t.transform(*this); }

#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTIONH3
template < class R >
std::ostream &operator<<(std::ostream &os, const DirectionH3<R> &p)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << p.dx() << ' ' << p.dy() << ' ' << p.dz();
    case IO::BINARY :
        write(os, p.dx());
        write(os, p.dy());
        write(os, p.dz());
        return os;
    default:
        return os << "DirectionH3(" << p.dx() << ", "
                                    << p.dy() << ", "
                                    << p.dz() << ')';
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTIONH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTIONH3
template < class R >
std::istream &operator>>(std::istream &is, DirectionH3<R> &p)
{
  typename R::RT x, y, z;
  switch(is.iword(IO::mode))
  {
    case IO::ASCII :
        is >> x >> y >> z;
        break;
    case IO::BINARY :
        read(is, x);
        read(is, y);
        read(is, z);
        break;
    default:
        std::cerr << "" << std::endl;
        std::cerr << "Stream must be in ascii or binary mode" << std::endl;
        break;
  }
  p = DirectionH3<R>(x, y, z);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTIONH3

CGAL_END_NAMESPACE

#endif // CGAL_HOMOGENEOUS_DIRECTION_3_H
