// Source:RayC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_RAYC2_H
#define CGAL_RAYC2_H

#include <CGAL/LineC2.h>

template < class FT >
class CGAL_RayC2 : public handle_base
{
public:
                      CGAL_RayC2();
                      CGAL_RayC2(const CGAL_RayC2<FT> &r);
                      CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                                const CGAL_PointC2<FT> &secondp);
                      CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                                const CGAL_DirectionC2<FT> &d);
                      ~CGAL_RayC2();
                      operator CGAL_RayC2<double>() const;

  CGAL_RayC2<FT>       &operator=(const CGAL_RayC2<FT> &r);

  bool                operator==(const CGAL_RayC2<FT> &r) const;
  bool                operator!=(const CGAL_RayC2<FT> &r) const;
  bool                identical(const CGAL_RayC2<FT> &r) const;

  CGAL_PointC2<FT>     start() const;
  CGAL_PointC2<FT>     second_point() const;

  CGAL_DirectionC2<FT> direction() const;
  CGAL_LineC2<FT>      supporting_line() const;
  CGAL_RayC2           opposite() const;

  CGAL_RayC2           transform(const CGAL_Aff_transformation_baseC2<FT> &t) const;

  bool                is_horizontal() const;
  bool                is_vertical() const;
  bool                is_degenerate() const;
  bool                is_on(const CGAL_PointC2<FT> &p) const;
  bool                collinear_is_on(const CGAL_PointC2<FT> &p) const;

#ifdef CGAL_KERNEL_PRECONDITION
  bool                is_defined() const
  {
    return (PTR == NULL) ? false : true;
  }
#endif // CGAL_KERNEL_PRECONDITION

private:
CGAL__Twotuple< CGAL_PointC2<FT> > *ptr() const;
};


template < class FT >
inline CGAL__Twotuple< CGAL_PointC2<FT> > *CGAL_RayC2<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}


template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2()
{
#ifdef CGAL_KERNEL_PRECONDITION
  PTR = NULL;
#else
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
#endif // CGAL_KERNEL_PRECONDITION
}

template < class FT >
inline CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_RayC2<FT>  &r) :
  handle_base(r)
{}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_PointC2<FT> &sp, const CGAL_PointC2<FT> &secondp)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, secondp);
  assert ( !is_degenerate() );
}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_PointC2<FT> &sp, const CGAL_DirectionC2<FT> &d)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, sp + d.vector());
  assert ( !is_degenerate() );
}

template < class FT >
inline CGAL_RayC2<FT>::~CGAL_RayC2()
{}

template < class FT >
CGAL_RayC2<FT>::operator CGAL_RayC2<double>() const
{
  return CGAL_RayC2<double>(start(), second_point());
}

template < class FT >
CGAL_RayC2<FT> &CGAL_RayC2<FT>::operator=(const CGAL_RayC2<FT> &r)
{
  handle_base::operator=(r);
  return *this;
}
template < class FT >
inline bool CGAL_RayC2<FT>::operator==(const CGAL_RayC2<FT> &r) const
{
  return ((start() == r.start()) && (direction() == r.direction()) );
}

template < class FT >
inline bool CGAL_RayC2<FT>::operator!=(const CGAL_RayC2<FT> &r) const
{
  return !(*this == r);
}

template < class FT >
bool CGAL_RayC2<FT>::identical(const CGAL_RayC2<FT> &r) const
{
  return ( PTR == r.PTR );
}
template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::start() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::second_point() const
{
  return ptr()->e1;
}

template < class FT >
inline CGAL_DirectionC2<FT> CGAL_RayC2<FT>::direction() const
{
  return CGAL_DirectionC2<FT>(  second_point() - start() );
}

template < class FT >
inline CGAL_LineC2<FT> CGAL_RayC2<FT>::supporting_line() const
{
  return CGAL_LineC2<FT>(*this);
}

template < class FT >
inline CGAL_RayC2<FT> CGAL_RayC2<FT>::opposite() const
{
  return CGAL_RayC2<FT>( start(), - direction() );
}

template < class FT >
inline CGAL_RayC2<FT> CGAL_RayC2<FT>::transform(const CGAL_Aff_transformation_baseC2<FT> &t) const
{
  return CGAL_RayC2<FT>(t.transform(start()),
                       t.transform(second_point()));
}

template < class FT >
inline bool CGAL_RayC2<FT>::is_horizontal() const
{
  return (start().y() ==  second_point().y());
}

template < class FT >
inline bool CGAL_RayC2<FT>::is_vertical() const
{
  return  (start().x() == second_point().x());
}

template < class FT >
bool CGAL_RayC2<FT>::is_degenerate() const
{
  return (start() == second_point());
}

template < class FT >
bool CGAL_RayC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
  return ( p == start()
           || ( CGAL_collinear(start(), p, second_point())
                && ( CGAL_DirectionC2<FT>(p - start()) == direction() )));

}

template < class FT >
bool CGAL_RayC2<FT>::collinear_is_on(const CGAL_PointC2<FT> &p) const
{
  assert( CGAL_collinear(start(), p, second_point()) );
  return ( p == start()
           || ( CGAL_DirectionC2<FT>(p - start()) == direction()) );

}



#ifdef CGAL_IO

#include <stream.h>

template < class FT >
ostream &operator<<(ostream &os, CGAL_RayC2<FT> &r)
{
  os << "RayC2(" << r.start() <<  ", " << r.direction() << ")";
  return os;
}

#endif


#endif
