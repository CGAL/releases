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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : SegmentH3.fw
// file          : include/CGAL/SegmentH3.h
// package       : H3 (1.3.1)
// revision      : 1.3.1
// revision_date : 30 Jun 1998 
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


template < class FT, class RT >
class CGAL__Segment_repH3 : public CGAL_Rep
{
public:
   CGAL__Segment_repH3() {}
   CGAL__Segment_repH3(const CGAL_PointH3<FT,RT>& sp,
                       const CGAL_PointH3<FT,RT>& ep)
   {
     startpoint = sp;
     endpoint   = ep;
   }
   ~CGAL__Segment_repH3() {}

   CGAL_PointH3<FT,RT>  start() const;
   CGAL_PointH3<FT,RT>  end()   const;

private:
   CGAL_PointH3<FT,RT>  startpoint;
   CGAL_PointH3<FT,RT>  endpoint;

};

template < class FT, class RT >
class CGAL_SegmentH3 : public CGAL_Handle
{
public:
  CGAL_SegmentH3();
  CGAL_SegmentH3( const CGAL_SegmentH3<FT,RT> & tbc);
  CGAL_SegmentH3( const CGAL_PointH3<FT,RT>& sp,
                   const CGAL_PointH3<FT,RT>& ep);
  ~CGAL_SegmentH3();

  CGAL_SegmentH3<FT,RT>& operator=( const CGAL_SegmentH3<FT,RT>& s);

  CGAL_PointH3<FT,RT>    source() const;
  CGAL_PointH3<FT,RT>    target() const;

  CGAL_PointH3<FT,RT>    start() const;
  CGAL_PointH3<FT,RT>    end() const;
  CGAL_PointH3<FT,RT>    min() const;
  CGAL_PointH3<FT,RT>    max() const;
  CGAL_PointH3<FT,RT>    vertex(int i) const;
  CGAL_PointH3<FT,RT>    point(int i) const;
  CGAL_PointH3<FT,RT>    operator[](int i) const;

  FT                     squared_length() const;
  CGAL_DirectionH3<FT,RT>
                         direction() const;
  CGAL_LineH3<FT,RT>     supporting_line() const;
  CGAL_SegmentH3<FT,RT>  opposite() const;
  CGAL_SegmentH3<FT,RT>
       transform( const CGAL_Aff_transformationH3<FT,RT> & t) const;
  CGAL_Bbox_3            bbox() const;
  bool                   has_on(const CGAL_PointH3<FT,RT> p) const;
  bool                   collinear_has_on(const CGAL_PointH3<FT,RT> p) const;
  bool                   is_degenerate() const;

  bool                   operator==(const CGAL_SegmentH3<FT,RT>& s) const;
  bool                   operator!=(const CGAL_SegmentH3<FT,RT>& s) const;
  bool                   identical (const CGAL_SegmentH3<FT,RT>& s) const;
  int                    id() const;

protected:
  CGAL__Segment_repH3<FT,RT>*   ptr() const;

};

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL__Segment_repH3<FT,RT>::start() const
{ return startpoint; }

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL__Segment_repH3<FT,RT>::end() const
{ return endpoint; }


template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentH3<FT,RT>::CGAL_SegmentH3()
{ PTR = new CGAL__Segment_repH3<FT,RT>; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentH3<FT,RT>::CGAL_SegmentH3(const CGAL_SegmentH3<FT,RT>& tbc)
  : CGAL_Handle( (CGAL_Handle&) tbc)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_SegmentH3<FT,RT>::CGAL_SegmentH3( const CGAL_PointH3<FT,RT>& sp,
                                       const CGAL_PointH3<FT,RT>& ep)
{ PTR = new CGAL__Segment_repH3<FT,RT>(sp,ep); }

template < class FT, class RT >
inline
CGAL_SegmentH3<FT,RT>::~CGAL_SegmentH3()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_SegmentH3<FT,RT> &
CGAL_SegmentH3<FT,RT>::operator=(const CGAL_SegmentH3<FT,RT>& s)
{
  CGAL_Handle::operator=((CGAL_Handle&) s);
  return *this;
}

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::source() const
{ return ptr()->start(); }

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::target() const
{ return ptr()->end(); }

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::start() const
{ return ptr()->start(); }

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::end() const
{ return ptr()->end(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::min() const
{
  return
  CGAL_lexicographically_xyz_smaller(target(),source()) ? target() : source();
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::max() const
{
  return
  CGAL_lexicographically_xyz_smaller_or_equal(source(),target()) ?
                                                         target() : source();
}

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::vertex(int i) const
{ return ( i%2 == 0 ) ? start() : end() ; }

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::point(int i) const
{ return ( i%2 == 0 ) ? start() : end() ; }

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::operator[](int i) const
{ return ( i%2 == 0 ) ? start() : end() ; }


template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_SegmentH3<FT,RT>::squared_length() const
{
  return  (ptr()->end() - ptr()->start()) *
          (ptr()->end() - ptr()->start())   ;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_DirectionH3<FT,RT>
CGAL_SegmentH3<FT,RT>::direction() const
{ return CGAL_DirectionH3<FT,RT>( ptr()->end() - ptr()->start() ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_LineH3<FT,RT>
CGAL_SegmentH3<FT,RT>::supporting_line() const
{ return CGAL_LineH3<FT,RT>(ptr()->start(), ptr()->end()); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_SegmentH3<FT,RT>
CGAL_SegmentH3<FT,RT>::opposite() const
{ return CGAL_SegmentH3<FT,RT>(ptr()->end(), ptr()->start()); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_SegmentH3<FT,RT>
CGAL_SegmentH3<FT,RT>::
transform( const CGAL_Aff_transformationH3<FT,RT>& t) const
{
  return CGAL_SegmentH3<FT,RT>(t.transform(ptr()->start()),
                               t.transform(ptr()->end())   );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_Bbox_3
CGAL_SegmentH3<FT,RT>::bbox() const
{ return source().bbox() + target().bbox(); }


#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENTH3
template < class FT, class RT >
ostream &operator<<(ostream &os, const CGAL_SegmentH3<FT,RT> &s)
{
  switch(os.iword(CGAL_IO::mode))
  {
      case CGAL_IO::ASCII :
          return os << s.source() << ' ' << s.target();
      case CGAL_IO::BINARY :
          return os << s.source() << s.target();
      default:
          return os << "SegmentH3(" << s.source() <<  ", " << s.target() << ")";
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENTH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENTH3
template < class FT, class RT >
istream &operator>>(istream &is, CGAL_SegmentH3<FT,RT> &s)
{
  CGAL_PointH3<FT,RT> p, q;
  is >> p >> q;
  s = CGAL_SegmentH3<FT,RT>(p, q);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENTH3
template < class FT, class RT >
inline
bool
CGAL_SegmentH3<FT,RT>::is_degenerate() const
{ return  source()==target(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_SegmentH3<FT,RT>::has_on(const CGAL_PointH3<FT,RT> p) const
{
  return( ( p == start() )
       || ( p == end() )
       || (  ( CGAL_collinear(p,source(),target() )
           &&( CGAL_DirectionH3<FT,RT>( p - ptr()->start())
               !=
               CGAL_DirectionH3<FT,RT>( p - ptr()->end()))
             )
          )
       );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_SegmentH3<FT,RT>::collinear_has_on(const CGAL_PointH3<FT,RT> p) const
{
  return( ( p == start() )
       || ( p == end() )
       || ( CGAL_DirectionH3<FT,RT>( p - ptr()->start())
            !=
            CGAL_DirectionH3<FT,RT>( p - ptr()->end())
          )
        );
}
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_SegmentH3<FT,RT>::operator==(const CGAL_SegmentH3<FT,RT>& s) const
{
  return ( (start() == s.start() )
         &&(end()   == s.end()   ) );
}

template < class FT, class RT >
inline
bool
CGAL_SegmentH3<FT,RT>::identical(const CGAL_SegmentH3<FT,RT>& s) const
{ return  PTR == s.PTR; }

template < class FT, class RT >
inline
int
CGAL_SegmentH3<FT,RT>::id() const
{ return (int) PTR; }

template < class FT, class RT >
inline
bool
CGAL_SegmentH3<FT,RT>::operator!=(const CGAL_SegmentH3<FT,RT>& s) const
{ return ( !operator==(s) ); }

template < class FT, class RT >
inline
CGAL__Segment_repH3<FT,RT>*
CGAL_SegmentH3<FT,RT>::ptr() const
{ return (CGAL__Segment_repH3<FT,RT>*)PTR; }


#endif // CGAL_SEGMENTH3_H
