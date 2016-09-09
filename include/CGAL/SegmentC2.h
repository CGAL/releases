// Source: SegmentC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_SEGMENTC2_H
#define CGAL_SEGMENTC2_H

#include <CGAL/LineC2.h>

template < class FT >
class CGAL_SegmentC2 : public handle_base
{
public:
                       CGAL_SegmentC2();
                       CGAL_SegmentC2(const CGAL_SegmentC2<FT>  &s);
                       CGAL_SegmentC2(const CGAL_PointC2<FT> &sp,
                                    const CGAL_PointC2<FT> &ep);
                       CGAL_SegmentC2(const FT &sx, const FT &sy, 
                                      const FT &ex, const FT &ey);
                       ~CGAL_SegmentC2();

#ifdef CGAL_TO_DOUBLE
                       operator CGAL_SegmentC2<double>() const;
#endif // CGAL_TO_DOUBLE

  CGAL_SegmentC2<FT>   &operator=(const CGAL_SegmentC2<FT> &s);

  bool                 is_horizontal() const;
  bool                 is_vertical() const;
  bool                 is_on(const CGAL_PointC2<FT> &p) const;
  bool                 collinear_is_on(const CGAL_PointC2<FT> &p) const;

  bool                 operator==(const CGAL_SegmentC2<FT> &s) const;
  bool                 operator!=(const CGAL_SegmentC2<FT> &s) const;
  bool                 identical(const CGAL_SegmentC2<FT> &s) const;

  CGAL_PointC2<FT>     start() const;
  CGAL_PointC2<FT>     end() const;
  CGAL_PointC2<FT>     vertex(int i) const;
  CGAL_PointC2<FT>     operator[](int i) const;

  FT                   squared_length() const;

  CGAL_DirectionC2<FT> direction() const;
  CGAL_LineC2<FT>      supporting_line() const;
  CGAL_SegmentC2<FT>   opposite() const;
  CGAL_SegmentC2<FT>   transform(const CGAL_Aff_transformationC2<FT> &t) const;

  bool                 is_degenerate() const;
  CGAL_Bbox_2          bbox() const;

#ifdef CGAL_CHECK_PRECONDITIONS
  bool                 is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

private:
  CGAL__Twotuple< CGAL_PointC2<FT> >*   ptr() const
  {
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
  }
};


#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT >
inline bool CGAL_SegmentC2<FT>::is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_CHECK_PRECONDITIONS



template < class FT >
CGAL_SegmentC2<FT>::CGAL_SegmentC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT >
CGAL_SegmentC2<FT>::CGAL_SegmentC2(const CGAL_SegmentC2<FT>  &s) :
  handle_base((handle_base&)s)
{}

template < class FT >
CGAL_SegmentC2<FT>::CGAL_SegmentC2(const CGAL_PointC2<FT> &sp,
                                 const CGAL_PointC2<FT> &ep)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, ep);

  CGAL_nondegeneracy_assertion;
}


template < class FT >
CGAL_SegmentC2<FT>::CGAL_SegmentC2(const FT &sx, const FT &sy, 
                                   const FT &ex, const FT &ey)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(CGAL_PointC2<FT>(sx,sy),
                                               CGAL_PointC2<FT>(ex,ey) );
  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_SegmentC2<FT>::~CGAL_SegmentC2()
{}

#ifdef  CGAL_TO_DOUBLE
template < class FT >
CGAL_SegmentC2<FT>::operator CGAL_SegmentC2<double>() const
{
  return CGAL_SegmentC2<double>(start(), end());
}
#endif // CGAL_TO_DOUBLE

template < class FT >
CGAL_SegmentC2<FT> &CGAL_SegmentC2<FT>::operator=(const CGAL_SegmentC2<FT> &s)
{
  CGAL_kernel_precondition(s.is_defined());
  handle_base::operator=(s);
  return *this;
}
template < class FT >
bool  CGAL_SegmentC2<FT>::operator==(const CGAL_SegmentC2<FT> &s) const
{
  CGAL_kernel_precondition(is_defined() && s.is_defined());
  return ( (start() == s.start())  && (end() == s.end()) );
}

template < class FT >
bool  CGAL_SegmentC2<FT>::operator!=(const CGAL_SegmentC2<FT> &s) const
{
  return !(*this == s);
}

template < class FT >
bool CGAL_SegmentC2<FT>::identical(const CGAL_SegmentC2<FT> &s) const
{
  CGAL_kernel_precondition(is_defined() && s.is_defined());
  return (PTR == s.PTR);
}
template < class FT >
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::start() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::end() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e1;
}

template < class FT >
CGAL_PointC2<FT> CGAL_SegmentC2<FT>::vertex(int i) const
{
  CGAL_kernel_precondition(is_defined());
  switch (i%2) {
  case 0: return start();
  case 1: return end();
  }
  return start();  // otherwise the SGI compiler complains
}

template < class FT >
CGAL_PointC2<FT> CGAL_SegmentC2<FT>::operator[](int i) const
{
  CGAL_kernel_precondition(is_defined());
  return vertex(i);
}
template < class FT >
FT CGAL_SegmentC2<FT>::squared_length() const
{
  CGAL_kernel_precondition(is_defined());
  return  ( (end() - start()) * (end() - start()));
}

template < class FT >
CGAL_DirectionC2<FT> CGAL_SegmentC2<FT>::direction() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_DirectionC2<FT>( end() - start() );
}

template < class FT >
CGAL_LineC2<FT> CGAL_SegmentC2<FT>::supporting_line() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_LineC2<FT>(*this);
}

template < class FT >
CGAL_SegmentC2<FT> CGAL_SegmentC2<FT>::opposite() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_SegmentC2<FT>(end(), start());
}

template < class FT >
CGAL_SegmentC2<FT> CGAL_SegmentC2<FT>::transform(
                               const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition(is_defined() && t.is_defined());
  return CGAL_SegmentC2<FT>(t.transform(start()),
                           t.transform(end()));
}

template < class FT >
CGAL_Bbox_2 CGAL_SegmentC2<FT>::bbox() const
{
  CGAL_kernel_precondition(is_defined());
  return start().bbox() + end().bbox();
}

template < class FT >
bool  CGAL_SegmentC2<FT>::is_degenerate() const
{
  CGAL_kernel_precondition(is_defined());
  return (start() == end());
}

template < class FT >
bool CGAL_SegmentC2<FT>::is_horizontal() const
{
  CGAL_kernel_precondition(is_defined());
  return (start().y() == end().y());
}

template < class FT >
bool CGAL_SegmentC2<FT>::is_vertical() const
{
  CGAL_kernel_precondition(is_defined());
  return (start().x() == end().x());
}

template < class FT >
bool CGAL_SegmentC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition(is_defined() && p.is_defined());
  return(( p == start() )
         || ( p == end() )
         || ( CGAL_collinear(start(), p, end())
              &&( CGAL_DirectionC2<FT>(p - start())
                  !=
                  CGAL_DirectionC2<FT> (p - end()))
             )
         );
}


template < class FT >
bool CGAL_SegmentC2<FT>::collinear_is_on(const CGAL_PointC2<FT> &p)
const
{
  CGAL_kernel_precondition ( CGAL_collinear(start(), p, end()) );
    if (abs(end().x()-start().x()) > abs(end().y()-start().y())) { // C1
        if (p.x() < start().x())
            return (p.x() >= end().x());
        if (p.x() <= end().x())
            return true;
        return (p.x() == start().x());
    } else {
        if (p.y() < start().y())
            return (p.y() >= end().y());
        if (p.y() <= end().y())
            return true;
        return (p.y() == start().y());
    }
}



#ifdef CGAL_IO

template < class FT >
ostream &operator<<(ostream &os, const CGAL_SegmentC2<FT> &s)
{
  CGAL_kernel_precondition(s.is_defined());
  os << "SegmentC2(" << s.start() <<  ", " << s.end() << ")";
  return os;
}

#endif

#endif
