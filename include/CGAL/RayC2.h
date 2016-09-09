// Source:RayC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_RAYC2_H
#define CGAL_RAYC2_H

#include<CGAL/PointC2.h>

#include <CGAL/LineC2.h>

template < class FT >
class CGAL_RayC2 : public CGAL_Handle_base
{
public:
                       CGAL_RayC2();
                       CGAL_RayC2(const CGAL_RayC2<FT> &r);
                       CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                                  const CGAL_PointC2<FT> &secondp);
                       CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                                  const CGAL_DirectionC2<FT> &d);
                       ~CGAL_RayC2();



  CGAL_RayC2<FT>       &operator=(const CGAL_RayC2<FT> &r);

  bool                 operator==(const CGAL_RayC2<FT> &r) const;
  bool                 operator!=(const CGAL_RayC2<FT> &r) const;
  bool                 identical(const CGAL_RayC2<FT> &r) const;

  CGAL_PointC2<FT>     start() const;
  CGAL_PointC2<FT>     second_point() const;

  CGAL_DirectionC2<FT> direction() const;
  CGAL_LineC2<FT>      supporting_line() const;
  CGAL_RayC2<FT>       opposite() const;

  CGAL_RayC2<FT>       transform(const CGAL_Aff_transformationC2<FT> &t) const;

  bool                 is_horizontal() const;
  bool                 is_vertical() const;
  bool                 is_degenerate() const;
  bool                 is_on(const CGAL_PointC2<FT> &p) const;
  bool                 collinear_is_on(const CGAL_PointC2<FT> &p) const;

#ifdef CGAL_CHECK_PRECONDITIONS
  bool                is_defined() const
  {
    return (PTR == NULL) ? false : true;
  }
#endif // CGAL_CHECK_PRECONDITIONS

private:
CGAL__Twotuple< CGAL_PointC2<FT> > *ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}
};


/*
template < class FT >
inline CGAL__Twotuple< CGAL_PointC2<FT> > *CGAL_RayC2<FT>::ptr() const
{
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
}
*/


template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_RayC2<FT>  &r) :
  CGAL_Handle_base((CGAL_Handle_base&)r)
{}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                           const CGAL_PointC2<FT> &secondp)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, secondp);
  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_RayC2<FT>::CGAL_RayC2(const CGAL_PointC2<FT> &sp,
                           const CGAL_DirectionC2<FT> &d)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, sp + d.vector());
  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_RayC2<FT>::~CGAL_RayC2()
{}


template < class FT >
CGAL_RayC2<FT> &CGAL_RayC2<FT>::operator=(const CGAL_RayC2<FT> &r)
{
  CGAL_kernel_precondition(r.is_defined());
  CGAL_Handle_base::operator=(r);
  return *this;
}
template < class FT >
bool CGAL_RayC2<FT>::operator==(const CGAL_RayC2<FT> &r) const
{
  CGAL_kernel_precondition(is_defined() && r.is_defined());
  return ((start() == r.start()) && (direction() == r.direction()) );
}

template < class FT >
bool CGAL_RayC2<FT>::operator!=(const CGAL_RayC2<FT> &r) const
{
  CGAL_kernel_precondition(is_defined() && r.is_defined());
  return !(*this == r);
}

template < class FT >
bool CGAL_RayC2<FT>::identical(const CGAL_RayC2<FT> &r) const
{
  CGAL_kernel_precondition(is_defined() && r.is_defined());
  return ( PTR == r.PTR );
}
template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::start() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_RayC2<FT>::second_point() const
{
  CGAL_kernel_precondition(is_defined());
  return ptr()->e1;
}

template < class FT >
CGAL_DirectionC2<FT> CGAL_RayC2<FT>::direction() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_DirectionC2<FT>(  second_point() - start() );
}

template < class FT >
CGAL_LineC2<FT> CGAL_RayC2<FT>::supporting_line() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_LineC2<FT>(*this);
}

template < class FT >
CGAL_RayC2<FT> CGAL_RayC2<FT>::opposite() const
{
  CGAL_kernel_precondition(is_defined());
  return CGAL_RayC2<FT>( start(), - direction() );
}


template < class FT >
CGAL_RayC2<FT> CGAL_RayC2<FT>::transform(const
                                     CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition(is_defined() && t.is_defined());
  return CGAL_RayC2<FT>(t.transform(start()),
                        t.transform(second_point()));
}


template < class FT >
bool CGAL_RayC2<FT>::is_horizontal() const
{
  CGAL_kernel_precondition(is_defined());
  return (start().y() ==  second_point().y());
}

template < class FT >
bool CGAL_RayC2<FT>::is_vertical() const
{
  CGAL_kernel_precondition(is_defined());
  return  (start().x() == second_point().x());
}

template < class FT >
bool CGAL_RayC2<FT>::is_degenerate() const
{
  CGAL_kernel_precondition(is_defined());
  return (start() == second_point());
}

template < class FT >
bool CGAL_RayC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition(is_defined() && p.is_defined());
  return ( p == start()
           || ( CGAL_collinear(start(), p, second_point())
                && ( CGAL_DirectionC2<FT>(p - start()) == direction() )));

}

template < class FT >
bool CGAL_RayC2<FT>::collinear_is_on(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition(is_defined() && p.is_defined());
  CGAL_exactness_precondition( CGAL_collinear(start(), p, second_point()) );
  return ( p == start()
           || ( CGAL_DirectionC2<FT>(p - start()) == direction()) );

}



#endif
