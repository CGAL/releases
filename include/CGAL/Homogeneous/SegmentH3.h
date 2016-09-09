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
// file          : include/CGAL/Homogeneous/SegmentH3.h
// package       : H3 (2.49)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2002/02/06 12:35:28 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_SEGMENTH3_H
#define CGAL_SEGMENTH3_H

CGAL_BEGIN_NAMESPACE

template < class R_ >
class SegmentH3
  : public R_::Segment_handle_3
{
CGAL_VC7_BUG_PROTECTED
  typedef typename R_::RT                   RT;
  typedef typename R_::FT                   FT;
  typedef typename R_::Point_3              Point_3;
  typedef typename R_::Direction_3          Direction_3;
  typedef typename R_::Line_3               Line_3;
  typedef typename R_::Aff_transformation_3 Aff_transformation_3;

  typedef typename R_::Segment_handle_3            Segment_handle_3_;
  typedef typename Segment_handle_3_::element_type Segment_ref_3;

public:
  typedef R_               R;
 
  SegmentH3()
    : Segment_handle_3_(Segment_ref_3()) {}

  SegmentH3( const Point_3& sp, const Point_3& ep)
    : Segment_handle_3_(Segment_ref_3(sp, ep)) {}

  const Point_3 &  source() const;
  const Point_3 &  target() const;

  const Point_3 &  start() const;
  const Point_3 &  end() const;
  const Point_3 &  min() const;
  const Point_3 &  max() const;
  const Point_3 &  vertex(int i) const;
  const Point_3 &  point(int i) const;
  const Point_3 &  operator[](int i) const;

  FT                squared_length() const;
  Direction_3   direction() const;
  Line_3        supporting_line() const;
  SegmentH3<R>  opposite() const;
  SegmentH3<R>  transform( const Aff_transformation_3& t) const;
  Bbox_3            bbox() const;
  bool              has_on(const Point_3& p) const;
  bool              collinear_has_on(const Point_3& p) const;
  bool              is_degenerate() const;

  bool              operator==(const SegmentH3<R>& s) const;
  bool              operator!=(const SegmentH3<R>& s) const;
};


template < class R >
inline
const typename SegmentH3<R>::Point_3 &
SegmentH3<R>::source() const
{ return Ptr()->e0; }

template < class R >
inline
const typename SegmentH3<R>::Point_3 &
SegmentH3<R>::target() const
{ return Ptr()->e1; }

template < class R >
inline
const typename SegmentH3<R>::Point_3 &
SegmentH3<R>::start() const
{ return source(); }

template < class R >
inline
const typename SegmentH3<R>::Point_3 &
SegmentH3<R>::end() const
{ return target(); }

template < class R >
CGAL_KERNEL_INLINE
const typename SegmentH3<R>::Point_3 &
SegmentH3<R>::min() const
{
  return
  lexicographically_xyz_smaller(target(),source()) ? target() : source();
}

template < class R >
CGAL_KERNEL_INLINE
const typename SegmentH3<R>::Point_3 &
SegmentH3<R>::max() const
{
  return lexicographically_xyz_smaller_or_equal(source(),target()) ?
                                                         target() : source();
}

template < class R >
inline
const typename SegmentH3<R>::Point_3 &
SegmentH3<R>::vertex(int i) const
{ return ( i%2 == 0 ) ? start() : end() ; }

template < class R >
inline
const typename SegmentH3<R>::Point_3 &
SegmentH3<R>::point(int i) const
{ return ( i%2 == 0 ) ? start() : end() ; }

template < class R >
inline
const typename SegmentH3<R>::Point_3 &
SegmentH3<R>::operator[](int i) const
{ return ( i%2 == 0 ) ? start() : end() ; }


template < class R >
CGAL_KERNEL_INLINE
typename SegmentH3<R>::FT
SegmentH3<R>::squared_length() const
{
  return  (end() - start()) *
          (end() - start())   ;
}

template < class R >
CGAL_KERNEL_INLINE
typename SegmentH3<R>::Direction_3
SegmentH3<R>::direction() const
{ return Direction_3( end() - start() ); }

template < class R >
CGAL_KERNEL_INLINE
typename SegmentH3<R>::Line_3
SegmentH3<R>::supporting_line() const
{ return Line_3(start(), end()); }

template < class R >
CGAL_KERNEL_INLINE
SegmentH3<R>
SegmentH3<R>::opposite() const
{ return SegmentH3<R>(end(), start()); }

template < class R >
CGAL_KERNEL_INLINE
SegmentH3<R>
SegmentH3<R>::
transform( const typename SegmentH3<R>::Aff_transformation_3& t) const
{
  return SegmentH3<R>(t.transform(start()),
                      t.transform(end())   );
}

template < class R >
CGAL_KERNEL_INLINE
Bbox_3
SegmentH3<R>::bbox() const
{ return source().bbox() + target().bbox(); }


#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENTH3
template < class R >
std::ostream &operator<<(std::ostream &os, const SegmentH3<R> &s)
{
  switch(os.iword(IO::mode))
  {
      case IO::ASCII :
          return os << s.source() << ' ' << s.target();
      case IO::BINARY :
          return os << s.source() << s.target();
      default:
          return os << "SegmentH3(" << s.source()
	            <<  ", " << s.target() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENTH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENTH3
template < class R >
std::istream &operator>>(std::istream &is, SegmentH3<R> &s)
{
  typename R::Point_3 p, q;
  is >> p >> q;
  s = SegmentH3<R>(p, q);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENTH3

template < class R >
inline
bool
SegmentH3<R>::is_degenerate() const
{ return  source()==target(); }

template < class R >
CGAL_KERNEL_INLINE
bool
SegmentH3<R>::has_on(const typename SegmentH3<R>::Point_3 &p) const
{
  return( ( p == start() )
       || ( p == end() )
       || (  ( collinear(p,source(),target() )
           &&( Direction_3( p - start())
               !=
               Direction_3( p - end()))
             )
          )
       );
}

template < class R >
CGAL_KERNEL_INLINE
bool
SegmentH3<R>::collinear_has_on(const typename SegmentH3<R>::Point_3 &p) const
{
  return( ( p == start() )
       || ( p == end() )
       || ( Direction_3( p - start())
            !=
            Direction_3( p - end())
          )
        );
}

template < class R >
CGAL_KERNEL_INLINE
bool
SegmentH3<R>::operator==(const SegmentH3<R>& s) const
{
  return ( (start() == s.start() )
         &&(end()   == s.end()   ) );
}

template < class R >
inline
bool
SegmentH3<R>::operator!=(const SegmentH3<R>& s) const
{ return ( !operator==(s) ); }

CGAL_END_NAMESPACE

#endif // CGAL_SEGMENTH3_H
