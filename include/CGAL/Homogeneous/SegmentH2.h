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
// file          : include/CGAL/Homogeneous/SegmentH2.h
// package       : H2 (2.67)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/02/06 12:34:07 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_SEGMENTH2_H
#define CGAL_SEGMENTH2_H

CGAL_BEGIN_NAMESPACE

template < class R_ >
class SegmentH2
  : public R_::Segment_handle_2
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::FT                   FT;
  typedef typename R_::RT                   RT;
  typedef typename R_::Point_2              Point_2;
  typedef typename R_::Line_2               Line_2;
  typedef typename R_::Direction_2          Direction_2;
  typedef typename R_::Aff_transformation_2 Aff_transformation_2;

  typedef typename R_::Segment_handle_2            Segment_handle_2_;
  typedef typename Segment_handle_2_::element_type Segment_ref_2;

public:
  typedef R_                                    R;

    SegmentH2()
      : Segment_handle_2_(Segment_ref_2()) {}

    SegmentH2( const Point_2& sp, const Point_2& ep)
      : Segment_handle_2_(Segment_ref_2(sp, ep)) {}

#if 1 // FIXME : should this exist at all ?
    SegmentH2( const RT& sx, const RT& sy, const RT& sw,
               const RT& ex, const RT& ey, const RT& ew)
      : Segment_handle_2_( Segment_ref_2( Point_2(sx,sy,sw),
                                          Point_2(ex,ey,ew) ) ) {}
#endif

    bool    operator==(const SegmentH2<R>& s) const;
    bool    operator!=(const SegmentH2<R>& s) const;

    const Point_2 & source() const;
    const Point_2 & target() const;
    const Point_2 & start() const;
    const Point_2 & end()   const;
    const Point_2 & vertex(int i) const;
    const Point_2 & point(int i) const;
    const Point_2 & operator[](int i) const;
    const Point_2 & min()   const;
    const Point_2 & max()   const;
    const Point_2 & other_vertex(const Point_2& p) const;

    bool    is_horizontal() const;
    bool    is_vertical() const;
    bool    has_on(const Point_2& p) const;
    bool    collinear_has_on(const Point_2& p) const;
    bool    is_degenerate() const;

    FT      squared_length() const;

    Direction_2    direction() const;
    Line_2         supporting_line() const;
    SegmentH2<R>   opposite() const;
    Bbox_2         bbox() const;

    SegmentH2<R> transform( const Aff_transformation_2 & t) const;
};

#ifdef CGAL_CFG_TYPENAME_BUG
#define typename
#endif

template < class R >
inline
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::source() const
{ return Ptr()->e0; }

template < class R >
inline
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::start() const
{ return source(); }

template < class R >
inline
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::target() const
{ return Ptr()->e1; }

template < class R >
inline
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::end() const
{ return target(); }

template < class R >
CGAL_KERNEL_INLINE
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::min() const
{
  return
  lexicographically_xy_smaller_or_equal(start(),end()) ? start() : end();
}

template < class R >
CGAL_KERNEL_INLINE
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::max() const
{
  return
  lexicographically_xy_smaller_or_equal(start(),end()) ? end() : start();
}

template < class R >
CGAL_KERNEL_INLINE
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::other_vertex(const typename SegmentH2<R>::Point_2& p) const
{
  CGAL_kernel_precondition( (p == end()) || (p == start()) );
  return ( p == start() ) ? end() : start() ;
}

template < class R >
CGAL_KERNEL_INLINE
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::vertex(int i) const
{
    return (i%2 == 0) ? start() : end();
}

template < class R >
inline
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::point(int i) const
{ return vertex(i); }

template < class R >
inline
const typename SegmentH2<R>::Point_2 &
SegmentH2<R>::operator[](int i) const
{ return vertex(i); }

template < class R >
CGAL_KERNEL_INLINE
typename SegmentH2<R>::FT
SegmentH2<R>::squared_length() const
{ return  (end() - start()) * (end() - start()); }

template < class R >
CGAL_KERNEL_INLINE
typename SegmentH2<R>::Direction_2
SegmentH2<R>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return Direction_2( end() - start() );
}

template < class R >
CGAL_KERNEL_INLINE
typename SegmentH2<R>::Line_2
SegmentH2<R>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return Line_2(start(), end());
}

template < class R >
CGAL_KERNEL_INLINE
SegmentH2<R>
SegmentH2<R>::opposite() const
{ return SegmentH2<R>(end(), start()); }

template < class R >
CGAL_KERNEL_INLINE
SegmentH2<R>
SegmentH2<R>::
transform(const typename SegmentH2<R>::Aff_transformation_2& t) const
{
  return SegmentH2<R>(t.transform(start()), t.transform(end()) );
}

template < class R >
inline
Bbox_2
SegmentH2<R>::bbox() const
{ return start().bbox() + end().bbox(); }

#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENTH2
template < class R >
std::ostream &
operator<<(std::ostream &os, const SegmentH2<R> &s)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << s.source() << ' ' << s.target();
    case IO::BINARY :
        return os << s.source() << s.target();
    default:
        return os << "SegmentH2(" << s.source() <<  ", " << s.target() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENTH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENTH2
template < class R >
std::istream &
operator>>(std::istream &is, SegmentH2<R> &s)
{
  typename R::Point_2 p, q;
  is >> p >> q;
  s = SegmentH2<R>(p, q);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENTH2

template < class R >
CGAL_KERNEL_INLINE
bool
SegmentH2<R>::is_horizontal() const
{
  return (    start().hy() * end().hw()
           == end().hy() * start().hw() );
}

template < class R >
CGAL_KERNEL_INLINE
bool
SegmentH2<R>::is_vertical() const
{
  return (    start().hx() * end().hw()
           == end().hx() * start().hw() );
}

template < class R >
CGAL_KERNEL_INLINE
bool
SegmentH2<R>::is_degenerate() const
{ return (start() == end()); }
template < class R >
CGAL_KERNEL_INLINE
bool
SegmentH2<R>::has_on(const typename SegmentH2<R>::Point_2& p) const
{
  if ( collinear(start(), p, end() ) )
  {
      return collinear_has_on(p);
  }
  else
  {
      return false;
  }
}

template < class R >
CGAL_KERNEL_INLINE
bool
SegmentH2<R>::collinear_has_on(const typename SegmentH2<R>::Point_2& p) const
{
  return (  lexicographically_xy_smaller_or_equal(p, max() )
         && lexicographically_xy_smaller_or_equal(min(),p) );
}
template < class R >
CGAL_KERNEL_INLINE
bool
SegmentH2<R>::operator==(const SegmentH2<R>& s) const
{
  return (  (start() == s.start() )
          &&(end()   == s.end()   ) );
}

template < class R >
inline
bool
SegmentH2<R>::operator!=(const SegmentH2<R>& s) const
{ return ( !operator==(s) ); }

#ifdef CGAL_CFG_TYPENAME_BUG
#undef typename
#endif

CGAL_END_NAMESPACE

#endif // CGAL_SEGMENTH2_H
