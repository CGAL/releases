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

// Source: SegmentH3.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_SEGMENTH3_H
#define CGAL_SEGMENTH3_H

#include <CGAL/LineH3.h>


template < class FT, class RT >
class CGAL__Segment_repH3 : public CGAL_Rep
{
public:
                         CGAL__Segment_repH3()
                         {
                         }
                         CGAL__Segment_repH3(const CGAL_PointH3<FT,RT>& sp,
                                             const CGAL_PointH3<FT,RT>& ep)
                         {
                           startpoint = sp;
                           endpoint   = ep;
                         }
                         ~CGAL__Segment_repH3()
                         {
                         }

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

    CGAL_SegmentH3<FT,RT>&
                         operator=( const CGAL_SegmentH3<FT,RT>& s);

    CGAL_PointH3<FT,RT>  source() const;
    CGAL_PointH3<FT,RT>  target() const;

    CGAL_PointH3<FT,RT>  start() const;
    CGAL_PointH3<FT,RT>  end() const;
    CGAL_PointH3<FT,RT>  min() const;
    CGAL_PointH3<FT,RT>  max() const;
    CGAL_PointH3<FT,RT>  vertex(int i) const;
    CGAL_PointH3<FT,RT>  point(int i) const;
    CGAL_PointH3<FT,RT>  operator[](int i) const;

    FT                   squared_length() const;
    CGAL_DirectionH3<FT,RT>
                         direction() const;
    CGAL_LineH3<FT,RT>   supporting_line() const;
    CGAL_SegmentH3       opposite() const;
    CGAL_SegmentH3       transform( const CGAL_Aff_transformationH3<FT,RT> & t)
                                                                         const;
    CGAL_Bbox_3          bbox() const;
    bool                 has_on(const CGAL_PointH3<FT,RT> p) const;
    bool                 collinear_has_on(const CGAL_PointH3<FT,RT> p) const;
    bool                 is_degenerate() const;

    bool                 operator==(const CGAL_SegmentH3& s) const;
    bool                 operator!=(const CGAL_SegmentH3& s) const;
    bool                 identical (const CGAL_SegmentH3& s) const;
    int                  id() const;

protected:

    CGAL__Segment_repH3<FT,RT>*   ptr() const;

};

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL__Segment_repH3<FT,RT>::start() const
{
 return startpoint;
}

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL__Segment_repH3<FT,RT>::end() const
{
 return endpoint;
}

template < class FT, class RT >
inline
bool
CGAL_SegmentH3<FT,RT>::operator!=(const CGAL_SegmentH3<FT,RT>& s) const
{
return ( !operator==(s) );
}
template < class FT, class RT >
inline
CGAL__Segment_repH3<FT,RT>*
CGAL_SegmentH3<FT,RT>::ptr() const
{
 return (CGAL__Segment_repH3<FT,RT>*)PTR;
}

template < class FT, class RT >
CGAL_SegmentH3<FT,RT>::CGAL_SegmentH3()
{
 PTR = new CGAL__Segment_repH3<FT,RT>;
}

template < class FT, class RT >
CGAL_SegmentH3<FT,RT>::CGAL_SegmentH3(const CGAL_SegmentH3 & tbc)
 : CGAL_Handle( (CGAL_Handle&) tbc)
{
}

template < class FT, class RT >
CGAL_SegmentH3<FT,RT>::CGAL_SegmentH3( const CGAL_PointH3<FT,RT>& sp,
                                       const CGAL_PointH3<FT,RT>& ep)
{
 PTR = new CGAL__Segment_repH3<FT,RT>(sp,ep);
}

template < class FT, class RT >
CGAL_SegmentH3<FT,RT>::~CGAL_SegmentH3()
{
}

template < class FT, class RT >
CGAL_SegmentH3<FT,RT> &
CGAL_SegmentH3<FT,RT>::operator=(const CGAL_SegmentH3 & s)
{
 CGAL_Handle::operator=((CGAL_Handle&) s);
 return *this;
}
template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::source() const
{
 return ptr()->start();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::target() const
{
 return ptr()->end();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::start() const
{
 return ptr()->start();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::end() const
{
 return ptr()->end();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::min() const
{
 return
 CGAL_lexicographically_xyz_smaller(target(),source()) ? target() : source();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::max() const
{
 return
 CGAL_lexicographically_xyz_smaller_or_equal(source(),target()) ?
                                                         target() : source();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::vertex(int i) const
{
 return ( i%2 == 0 ) ? start() : end() ;
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::point(int i) const
{
 return ( i%2 == 0 ) ? start() : end() ;
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_SegmentH3<FT,RT>::operator[](int i) const
{
 return ( i%2 == 0 ) ? start() : end() ;
}

template < class FT, class RT >
FT
CGAL_SegmentH3<FT,RT>::squared_length() const
{
 return  (ptr()->end() - ptr()->start()) *
         (ptr()->end() - ptr()->start())   ;
}

template < class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL_SegmentH3<FT,RT>::direction() const
{
 return CGAL_DirectionH3<FT,RT>( ptr()->end() - ptr()->start() );
}

template < class FT, class RT >
CGAL_LineH3<FT,RT>
CGAL_SegmentH3<FT,RT>::supporting_line() const
{
 return CGAL_LineH3<FT,RT>(ptr()->start(), ptr()->end());
}

template < class FT, class RT >
CGAL_SegmentH3<FT,RT>
CGAL_SegmentH3<FT,RT>::opposite() const
{
 return CGAL_SegmentH3(ptr()->end(), ptr()->start());
}

template < class FT, class RT >
CGAL_SegmentH3<FT,RT>
CGAL_SegmentH3<FT,RT>::transform( const CGAL_Aff_transformationH3<FT,RT>& t)
                                                                          const
{
 return CGAL_SegmentH3(t.transform(ptr()->start()),
                       t.transform(ptr()->end())   );
}

template < class FT, class RT >
CGAL_Bbox_3
CGAL_SegmentH3<FT,RT>::bbox() const
{
 return source().bbox() + target().bbox();
}
template < class FT, class RT >
bool
CGAL_SegmentH3<FT,RT>::is_degenerate() const
{
 return  source()==target();
}

template < class FT, class RT >
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
bool
CGAL_SegmentH3<FT,RT>::operator==(const CGAL_SegmentH3<FT,RT>& s) const
{
 return ( (start() == s.start() )
        &&(end()   == s.end()   ) );
}

template < class FT, class RT >
bool
CGAL_SegmentH3<FT,RT>::identical(const CGAL_SegmentH3<FT,RT>& s) const
{
 return  PTR == s.PTR;
}

template < class FT, class RT >
int
CGAL_SegmentH3<FT,RT>::id() const
{
 return (int)PTR;
}


#endif // CGAL_SEGMENTH3_H
