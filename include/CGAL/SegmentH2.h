 
// Source: SegmentH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_SEGMENTH2_H
#define CGAL_SEGMENTH2_H

#include <CGAL/PointH2.h>
#include <CGAL/LineH2.h>

 

template < class FT, class RT >
class CGAL__Segment_repH2 : public handle_rep
{
public:
            CGAL__Segment_repH2();
            CGAL__Segment_repH2(const CGAL_PointH2<FT,RT>& sp,
                                const CGAL_PointH2<FT,RT>& ep);
            ~CGAL__Segment_repH2(){}

    CGAL_PointH2<FT,RT>  start;
    CGAL_PointH2<FT,RT>  end;

};
 

 



template < class FT, class RT >
class CGAL_SegmentH2 : public handle_base
{

public:
            CGAL_SegmentH2();
            CGAL_SegmentH2( const CGAL_SegmentH2 & s);
            CGAL_SegmentH2( const CGAL_PointH2<FT,RT>& sp,
                            const CGAL_PointH2<FT,RT>& ep);
            CGAL_SegmentH2(const RT& sw, const RT& sx, const RT& sy,
                           const RT& ew, const RT& ex, const RT& ey);
            ~CGAL_SegmentH2();
    CGAL_SegmentH2<FT,RT>&
            operator=(const CGAL_SegmentH2<FT,RT>& s);

    bool    operator==(const CGAL_SegmentH2& s) const;
    bool    operator!=(const CGAL_SegmentH2& s) const;
    bool    identical (const CGAL_SegmentH2& s) const;

    CGAL_PointH2<FT,RT>  start() const;
    CGAL_PointH2<FT,RT>  end()   const;
    CGAL_PointH2<FT,RT>  vertex(int i) const;
    CGAL_PointH2<FT,RT>  operator[](int i) const;
    CGAL_PointH2<FT,RT>  min()   const;
    CGAL_PointH2<FT,RT>  max()   const;
    CGAL_PointH2<FT,RT>  other_vertex(const CGAL_PointH2<FT,RT>& p) const;

    bool    is_horizontal() const;
    bool    is_vertical() const;
    bool    is_on(const CGAL_PointH2<FT,RT>& p) const;
    bool    collinear_is_on(const CGAL_PointH2<FT,RT>& p) const;
    bool    is_degenerate() const;

    FT      squared_length() const;

    CGAL_DirectionH2<FT,RT> direction() const;
    CGAL_LineH2<FT,RT>      supporting_line() const;
    CGAL_SegmentH2          opposite() const;
    CGAL_Bbox_2             bbox() const;

    CGAL_SegmentH2
            transform( const CGAL_Aff_transformationH2<FT,RT> & t) const;

#ifdef CGAL_CHECK_PRECONDITIONS
    bool    is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

protected:

    CGAL__Segment_repH2<FT,RT>*   ptr() const;

};
 

 
template < class FT, class RT >
CGAL__Segment_repH2<FT,RT>::CGAL__Segment_repH2()
{
}

template < class FT, class RT >
CGAL__Segment_repH2<FT,RT>::CGAL__Segment_repH2(const CGAL_PointH2<FT,RT>& sp,
                                              const CGAL_PointH2<FT,RT>& ep) :
start(sp), end(ep)
{
}
 

 



template < class FT, class RT >
CGAL_SegmentH2<FT,RT>::CGAL_SegmentH2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
 PTR = NULL;
#else
 PTR = new CGAL__Segment_repH2<FT,RT>;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT, class RT >
CGAL_SegmentH2<FT,RT>::CGAL_SegmentH2(const CGAL_SegmentH2<FT,RT>& s) :
  handle_base( (handle_base&) s)
{
 CGAL_kernel_precondition( s.is_defined() );
}

template < class FT, class RT >
CGAL_SegmentH2<FT,RT>::CGAL_SegmentH2( const CGAL_PointH2<FT,RT>& sp,
                                       const CGAL_PointH2<FT,RT>& ep)
{
 PTR = new CGAL__Segment_repH2<FT,RT>(sp,ep);
 CGAL_nondegeneracy_assertion;
}

template < class FT, class RT >
CGAL_SegmentH2<FT,RT>::CGAL_SegmentH2(const RT& sx, const RT& sy, const RT& sw,
                                      const RT& ex, const RT& ey, const RT& ew)
{
 PTR = new CGAL__Segment_repH2<FT,RT> (CGAL_PointH2<FT,RT>(sx,sy,sw),
                                       CGAL_PointH2<FT,RT>(ex,ey,ew) );
 CGAL_nondegeneracy_assertion;
}


template < class FT, class RT >
CGAL_SegmentH2<FT,RT>::~CGAL_SegmentH2()
{
}

template < class FT, class RT >
CGAL_SegmentH2<FT,RT>&
CGAL_SegmentH2<FT,RT>::operator=(const CGAL_SegmentH2<FT,RT>& s)
{
 CGAL_kernel_precondition( s.is_defined() );
 handle_base::operator=(s);
 return *this;
}
 



template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::start() const
{
 CGAL_kernel_precondition( is_defined() );
 return ptr()->start;
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::end() const
{
 CGAL_kernel_precondition( is_defined() );
 return ptr()->end;
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::min() const
{
 CGAL_kernel_precondition( is_defined() );
 return
   CGAL_lexicographically_xy_smaller_or_equal(start(),end()) ? start() : end();
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::max() const
{
 CGAL_kernel_precondition( is_defined() );
 return
   CGAL_lexicographically_xy_smaller_or_equal(start(),end()) ? end() : start();
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::other_vertex(const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition(   is_defined()
                          && ( p == end() || p == start() ) );
 return ( p == start() ) ? end() : start() ;
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::vertex(int i) const
{
 CGAL_kernel_precondition( is_defined() );
 switch (i%2)
 {
    case 0:  return ptr()->start;
    case 1:  return ptr()->end;
 };
 return CGAL_PointH2<FT,RT>(); // otherwise the SGI compiler complains
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_SegmentH2<FT,RT>::operator[](int i) const
{
 return vertex(i);
}
 

template < class FT, class RT >
FT
CGAL_SegmentH2<FT,RT>::squared_length() const
{
 CGAL_kernel_precondition( is_defined() );
 return  (ptr()->end - ptr()->start) * (ptr()->end - ptr()->start);
}

template < class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_SegmentH2<FT,RT>::direction() const
{
 CGAL_kernel_precondition( is_defined() );
 CGAL_nondegeneracy_precondition( !is_degenerate() );
 return CGAL_DirectionH2<FT,RT>( ptr()->end - ptr()->start );
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>
CGAL_SegmentH2<FT,RT>::supporting_line() const
{
 CGAL_kernel_precondition( is_defined() );
 CGAL_nondegeneracy_precondition( !is_degenerate() );
 return CGAL_LineH2<FT,RT>(ptr()->start, ptr()->end);
}

template < class FT, class RT >
CGAL_SegmentH2<FT,RT>
CGAL_SegmentH2<FT,RT>::opposite() const
{
 CGAL_kernel_precondition( is_defined() );
 return CGAL_SegmentH2<FT,RT>(ptr()->end, ptr()->start);
}

template < class FT, class RT >
CGAL_SegmentH2<FT,RT>
CGAL_SegmentH2<FT,RT>::transform(
                           const CGAL_Aff_transformationH2<FT,RT>& t) const
{
 CGAL_kernel_precondition( is_defined() && t.is_defined() );
 return CGAL_SegmentH2<FT,RT>(t.transform(ptr()->start),
                              t.transform(ptr()->end)   );
}

template < class FT, class RT >
CGAL_Bbox_2
CGAL_SegmentH2<FT,RT>::bbox() const
{
 CGAL_kernel_precondition( is_defined() );
 return start().bbox() + end().bbox();
}
 

template < class FT, class RT >
bool
CGAL_SegmentH2<FT,RT>::is_horizontal() const
{
 CGAL_kernel_precondition( is_defined() );
 return (     ptr()->start.hy() * ptr()->end.hw()
           == ptr()->end.hy() * ptr()->start.hw() );
}

template < class FT, class RT >
bool
CGAL_SegmentH2<FT,RT>::is_vertical() const
{
 CGAL_kernel_precondition( is_defined() );
 return (     ptr()->start.hx() * ptr()->end.hw()
           == ptr()->end.hx() * ptr()->start.hw() );
}

template < class FT, class RT >
bool
CGAL_SegmentH2<FT,RT>::is_degenerate() const
{
  CGAL_kernel_precondition( is_defined() );
  return (start() == end());
}
 
template < class FT, class RT >
bool
CGAL_SegmentH2<FT,RT>::is_on(const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 if ( CGAL_collinear(ptr()->start, p, ptr()->end ) )
 {
    return collinear_is_on(p);
 }
 else
 {
    return false;
 }
}

template < class FT, class RT >
bool
CGAL_SegmentH2<FT,RT>::collinear_is_on(const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 return (  CGAL_lexicographically_xy_smaller_or_equal(p, max() )
        && CGAL_lexicographically_xy_smaller_or_equal(min(),p) );
}
 



template < class FT, class RT >
bool
CGAL_SegmentH2<FT,RT>::operator==(const CGAL_SegmentH2<FT,RT>& s) const
{
 CGAL_kernel_precondition( is_defined() && s.is_defined() );
 return (  (start() == s.start() )
         &&(end()   == s.end()   ) );
}

template < class FT, class RT >
bool
CGAL_SegmentH2<FT,RT>::operator!=(const CGAL_SegmentH2<FT,RT>& s) const
{
 return ( !operator==(s) );
}

template < class FT, class RT >
bool
CGAL_SegmentH2<FT,RT>::identical(const CGAL_SegmentH2<FT,RT>& s) const
{
 CGAL_kernel_precondition( is_defined() && s.is_defined() );
 return  PTR == s.PTR;
}
 



template < class FT, class RT >
inline
CGAL__Segment_repH2<FT,RT>*
CGAL_SegmentH2<FT,RT>::ptr() const
{
return (CGAL__Segment_repH2<FT,RT>*)PTR;
}

#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT, class RT >
inline
bool
CGAL_SegmentH2<FT,RT>::is_defined() const
{
  return !(PTR == NULL);
}
#endif // CGAL_CHECK_PRECONDITIONS
 


#endif // CGAL_SEGMENTH2_H
