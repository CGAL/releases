//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: SegmentC3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_SEGMENTC3_H
#define CGAL_SEGMENTC3_H

#include <CGAL/LineC3.h>

template < class FT >
class CGAL_SegmentC3 : public CGAL_Handle
{
public:
                       CGAL_SegmentC3();
                       CGAL_SegmentC3(const CGAL_SegmentC3<FT>  &s);
                       CGAL_SegmentC3(const CGAL_PointC3<FT> &sp,
                                      const CGAL_PointC3<FT> &ep);

                       ~CGAL_SegmentC3();

  CGAL_SegmentC3<FT>   &operator=(const CGAL_SegmentC3<FT> &s);

  bool                 has_on(const CGAL_PointC3<FT> &p) const;
  bool                 collinear_has_on(const CGAL_PointC3<FT> &p) const;

  bool                 operator==(const CGAL_SegmentC3<FT> &s) const;
  bool                 operator!=(const CGAL_SegmentC3<FT> &s) const;
  int                  id() const;

  CGAL_PointC3<FT>     start() const;
  CGAL_PointC3<FT>     end() const;

  CGAL_PointC3<FT>     source() const;
  CGAL_PointC3<FT>     target() const;

  CGAL_PointC3<FT>     min() const;
  CGAL_PointC3<FT>     max() const;
  CGAL_PointC3<FT>     vertex(int i) const;
  CGAL_PointC3<FT>     point(int i) const;
  CGAL_PointC3<FT>     operator[](int i) const;

  FT                   squared_length() const;

  CGAL_DirectionC3<FT> direction() const;
  CGAL_LineC3<FT>      supporting_line() const;
  CGAL_SegmentC3       opposite() const;
  CGAL_SegmentC3       transform(const CGAL_Aff_transformationC3<FT> &t) const;

  bool                 is_degenerate() const;
  CGAL_Bbox_3          bbox() const;

private:
  CGAL__Twotuple< CGAL_PointC3<FT> >*   ptr() const;
};


template < class FT >
inline CGAL__Twotuple< CGAL_PointC3<FT> > *CGAL_SegmentC3<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC3<FT> >*)PTR;
}


template < class FT >
CGAL_SegmentC3<FT>::CGAL_SegmentC3()
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >;
}

template < class FT >
CGAL_SegmentC3<FT>::CGAL_SegmentC3(const CGAL_SegmentC3<FT>  &s) :
  CGAL_Handle((CGAL_Handle&)s)
{}

template < class FT >
CGAL_SegmentC3<FT>::CGAL_SegmentC3(const CGAL_PointC3<FT> &sp,
                                   const CGAL_PointC3<FT> &ep)
{
  PTR = new CGAL__Twotuple< CGAL_PointC3<FT> >(sp, ep);
  CGAL_nondegeneracy_assertion;
}


template < class FT >
inline CGAL_SegmentC3<FT>::~CGAL_SegmentC3()
{}


template < class FT >
CGAL_SegmentC3<FT> &CGAL_SegmentC3<FT>::operator=(const CGAL_SegmentC3<FT> &s)
{
  CGAL_Handle::operator=(s);
  return *this;
}
template < class FT >
inline bool  CGAL_SegmentC3<FT>::operator==(const CGAL_SegmentC3<FT> &s) const
{
  return ( (source() == s.source())  && (target() == s.target()) );
}

template < class FT >
inline bool  CGAL_SegmentC3<FT>::operator!=(const CGAL_SegmentC3<FT> &s) const
{
  return !(*this == s);
}

template < class FT >
int  CGAL_SegmentC3<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::start() const
{

  return ptr()->e0;
}

template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::end() const
{
  return ptr()->e1;
}

template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::target() const
{
  return ptr()->e1;
}

template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::min() const
{
  return (CGAL_lexicographically_xyz_smaller(source(),target())) ? source()
                                                                 : target();
}

template < class FT >
CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::max() const
{
  return (CGAL_lexicographically_xyz_smaller(source(),target())) ? target()
                                                                 : source();
}

template < class FT >
inline CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::vertex(int i) const
{
  if (i%2 == 0) {
    return source();
  }
  return target();
}

template < class FT >
inline CGAL_PointC3<FT>  CGAL_SegmentC3<FT>::point(int i) const
{
  if (i%2 == 0) {
    return source();
  }
  return target();
}

template < class FT >
inline CGAL_PointC3<FT> CGAL_SegmentC3<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
inline FT CGAL_SegmentC3<FT>::squared_length() const
{
  return  ( (target() - source()) * (target() - source()));
}

template < class FT >
inline CGAL_DirectionC3<FT> CGAL_SegmentC3<FT>::direction() const
{
  return CGAL_DirectionC3<FT>( target() - source() );
}

template < class FT >
inline CGAL_LineC3<FT> CGAL_SegmentC3<FT>::supporting_line() const
{
  return CGAL_LineC3<FT>(*this);
}

template < class FT >
inline CGAL_SegmentC3<FT> CGAL_SegmentC3<FT>::opposite() const
{
  return CGAL_SegmentC3<FT>(target(), source());
}

template < class FT >
inline CGAL_SegmentC3<FT> CGAL_SegmentC3<FT>::transform(
                                const CGAL_Aff_transformationC3<FT> &t) const
{
  return CGAL_SegmentC3<FT>(t.transform(source()),
                            t.transform(target()));
}


template < class FT >
bool  CGAL_SegmentC3<FT>::is_degenerate() const
{
  return (source() == target());
}

template < class FT >
CGAL_Bbox_3 CGAL_SegmentC3<FT>::bbox() const
{
  return source().bbox() + target().bbox();
}
template < class FT >
bool CGAL_SegmentC3<FT>::has_on(const CGAL_PointC3<FT> &p) const
{
  return(( p == source() )
         || ( p == target() )
         || ( CGAL_collinear(source(), p, target())
              &&( CGAL_DirectionC3<FT>(p - source())
                  !=
                  CGAL_DirectionC3<FT> (p - target()))
             )
         );
}

template < class FT >
inline bool CGAL_SegmentC3<FT>::collinear_has_on(
                                             const CGAL_PointC3<FT> &p) const
{
  CGAL_exactness_precondition ( CGAL_collinear(source(), p, target()) );
  return(( p == source() )
         || ( p == target() )
         || ( CGAL_DirectionC3<FT>(p - source())
              !=
              CGAL_DirectionC3<FT> (p - target())) );
}


#endif
