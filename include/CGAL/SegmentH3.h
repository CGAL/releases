// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.0
// release_date  : 1999, June 03
// 
// source        : SegmentH3.fw
// file          : include/CGAL/SegmentH3.h
// package       : H3 (2.2.1)
// revision      : 2.2.1
// revision_date : 26 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SEGMENTH3_H
#define CGAL_SEGMENTH3_H

#ifndef CGAL_LINEH3_H
#include <CGAL/LineH3.h>
#endif // CGAL_LINEH3_H

CGAL_BEGIN_NAMESPACE


template < class FT, class RT >
class _Segment_repH3 : public Rep
{
public:
   _Segment_repH3() {}
   _Segment_repH3(const PointH3<FT,RT>& sp,
                       const PointH3<FT,RT>& ep)
   {
     startpoint = sp;
     endpoint   = ep;
   }
   ~_Segment_repH3() {}

   PointH3<FT,RT>  start() const;
   PointH3<FT,RT>  end()   const;

private:
   PointH3<FT,RT>  startpoint;
   PointH3<FT,RT>  endpoint;

};

template < class FT, class RT >
class SegmentH3 : public Handle
{
public:
  SegmentH3();
  SegmentH3( const SegmentH3<FT,RT> & tbc);
  SegmentH3( const PointH3<FT,RT>& sp,
                   const PointH3<FT,RT>& ep);
  ~SegmentH3();

  SegmentH3<FT,RT>& operator=( const SegmentH3<FT,RT>& s);

  PointH3<FT,RT>    source() const;
  PointH3<FT,RT>    target() const;

  PointH3<FT,RT>    start() const;
  PointH3<FT,RT>    end() const;
  PointH3<FT,RT>    min() const;
  PointH3<FT,RT>    max() const;
  PointH3<FT,RT>    vertex(int i) const;
  PointH3<FT,RT>    point(int i) const;
  PointH3<FT,RT>    operator[](int i) const;

  FT                     squared_length() const;
  DirectionH3<FT,RT>
                         direction() const;
  LineH3<FT,RT>     supporting_line() const;
  SegmentH3<FT,RT>  opposite() const;
  SegmentH3<FT,RT>
       transform( const Aff_transformationH3<FT,RT> & t) const;
  Bbox_3            bbox() const;
  bool                   has_on(const PointH3<FT,RT> p) const;
  bool                   collinear_has_on(const PointH3<FT,RT> p) const;
  bool                   is_degenerate() const;

  bool                   operator==(const SegmentH3<FT,RT>& s) const;
  bool                   operator!=(const SegmentH3<FT,RT>& s) const;
  bool                   identical (const SegmentH3<FT,RT>& s) const;
  int                    id() const;

protected:
  _Segment_repH3<FT,RT>*   ptr() const;

};

template < class FT, class RT >
inline
PointH3<FT,RT>
_Segment_repH3<FT,RT>::start() const
{ return startpoint; }

template < class FT, class RT >
inline
PointH3<FT,RT>
_Segment_repH3<FT,RT>::end() const
{ return endpoint; }


template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
SegmentH3<FT,RT>::SegmentH3()
{ PTR = new _Segment_repH3<FT,RT>; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
SegmentH3<FT,RT>::SegmentH3(const SegmentH3<FT,RT>& tbc)
  : Handle( (Handle&) tbc)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
SegmentH3<FT,RT>::SegmentH3( const PointH3<FT,RT>& sp,
                                       const PointH3<FT,RT>& ep)
{ PTR = new _Segment_repH3<FT,RT>(sp,ep); }

template < class FT, class RT >
inline
SegmentH3<FT,RT>::~SegmentH3()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
SegmentH3<FT,RT> &
SegmentH3<FT,RT>::operator=(const SegmentH3<FT,RT>& s)
{
  Handle::operator=((Handle&) s);
  return *this;
}

template < class FT, class RT >
inline
PointH3<FT,RT>
SegmentH3<FT,RT>::source() const
{ return ptr()->start(); }

template < class FT, class RT >
inline
PointH3<FT,RT>
SegmentH3<FT,RT>::target() const
{ return ptr()->end(); }

template < class FT, class RT >
inline
PointH3<FT,RT>
SegmentH3<FT,RT>::start() const
{ return ptr()->start(); }

template < class FT, class RT >
inline
PointH3<FT,RT>
SegmentH3<FT,RT>::end() const
{ return ptr()->end(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH3<FT,RT>
SegmentH3<FT,RT>::min() const
{
  return
  lexicographically_xyz_smaller(target(),source()) ? target() : source();
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH3<FT,RT>
SegmentH3<FT,RT>::max() const
{
  return
  lexicographically_xyz_smaller_or_equal(source(),target()) ?
                                                         target() : source();
}

template < class FT, class RT >
inline
PointH3<FT,RT>
SegmentH3<FT,RT>::vertex(int i) const
{ return ( i%2 == 0 ) ? start() : end() ; }

template < class FT, class RT >
inline
PointH3<FT,RT>
SegmentH3<FT,RT>::point(int i) const
{ return ( i%2 == 0 ) ? start() : end() ; }

template < class FT, class RT >
inline
PointH3<FT,RT>
SegmentH3<FT,RT>::operator[](int i) const
{ return ( i%2 == 0 ) ? start() : end() ; }


template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
SegmentH3<FT,RT>::squared_length() const
{
  return  (ptr()->end() - ptr()->start()) *
          (ptr()->end() - ptr()->start())   ;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
DirectionH3<FT,RT>
SegmentH3<FT,RT>::direction() const
{ return DirectionH3<FT,RT>( ptr()->end() - ptr()->start() ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
LineH3<FT,RT>
SegmentH3<FT,RT>::supporting_line() const
{ return LineH3<FT,RT>(ptr()->start(), ptr()->end()); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
SegmentH3<FT,RT>
SegmentH3<FT,RT>::opposite() const
{ return SegmentH3<FT,RT>(ptr()->end(), ptr()->start()); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
SegmentH3<FT,RT>
SegmentH3<FT,RT>::
transform( const Aff_transformationH3<FT,RT>& t) const
{
  return SegmentH3<FT,RT>(t.transform(ptr()->start()),
                               t.transform(ptr()->end())   );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
Bbox_3
SegmentH3<FT,RT>::bbox() const
{ return source().bbox() + target().bbox(); }


#ifndef NO_OSTREAM_INSERT_SEGMENTH3
template < class FT, class RT >
std::ostream &operator<<(std::ostream &os, const SegmentH3<FT,RT> &s)
{
  switch(os.iword(IO::mode))
  {
      case IO::ASCII :
          return os << s.source() << ' ' << s.target();
      case IO::BINARY :
          return os << s.source() << s.target();
      default:
          return os << "SegmentH3(" << s.source() <<  ", " << s.target() << ")";
  }
}
#endif // NO_OSTREAM_INSERT_SEGMENTH3

#ifndef NO_ISTREAM_EXTRACT_SEGMENTH3
template < class FT, class RT >
std::istream &operator>>(std::istream &is, SegmentH3<FT,RT> &s)
{
  PointH3<FT,RT> p, q;
  is >> p >> q;
  s = SegmentH3<FT,RT>(p, q);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_SEGMENTH3
template < class FT, class RT >
inline
bool
SegmentH3<FT,RT>::is_degenerate() const
{ return  source()==target(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
SegmentH3<FT,RT>::has_on(const PointH3<FT,RT> p) const
{
  return( ( p == start() )
       || ( p == end() )
       || (  ( collinear(p,source(),target() )
           &&( DirectionH3<FT,RT>( p - ptr()->start())
               !=
               DirectionH3<FT,RT>( p - ptr()->end()))
             )
          )
       );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
SegmentH3<FT,RT>::collinear_has_on(const PointH3<FT,RT> p) const
{
  return( ( p == start() )
       || ( p == end() )
       || ( DirectionH3<FT,RT>( p - ptr()->start())
            !=
            DirectionH3<FT,RT>( p - ptr()->end())
          )
        );
}
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
SegmentH3<FT,RT>::operator==(const SegmentH3<FT,RT>& s) const
{
  return ( (start() == s.start() )
         &&(end()   == s.end()   ) );
}

template < class FT, class RT >
inline
bool
SegmentH3<FT,RT>::identical(const SegmentH3<FT,RT>& s) const
{ return  PTR == s.PTR; }

template < class FT, class RT >
inline
int
SegmentH3<FT,RT>::id() const
{ return (int) PTR; }

template < class FT, class RT >
inline
bool
SegmentH3<FT,RT>::operator!=(const SegmentH3<FT,RT>& s) const
{ return ( !operator==(s) ); }

template < class FT, class RT >
inline
_Segment_repH3<FT,RT>*
SegmentH3<FT,RT>::ptr() const
{ return (_Segment_repH3<FT,RT>*)PTR; }

CGAL_END_NAMESPACE


#endif // CGAL_SEGMENTH3_H
