
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

// Source: PVDH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_PVDH2
#define CGAL_PVDH2
#define CGAL_POINTH2_H
#define CGAL_VECTORH2_H
#define CGAL_DIRECTIONH2_H

#include <CGAL/Threetuple.h>
#include <CGAL/homogeneous_classes.h>
#include <CGAL/Origin.h>

template < class FT, class RT >
class CGAL_PointH2 : public CGAL_Handle
{

public:
            CGAL_PointH2();
            CGAL_PointH2(const CGAL_Origin & o);
            CGAL_PointH2(const CGAL_PointH2<FT,RT> & p);
            CGAL_PointH2(const RT& hx, const RT& hy );
            CGAL_PointH2(const RT& hx, const RT& hy, const RT& hw );
            ~CGAL_PointH2();

    CGAL_PointH2<FT,RT> &
            operator=( const CGAL_PointH2& p);

    bool    operator==( const CGAL_PointH2<FT,RT>& p) const;
    bool    operator!=( const CGAL_PointH2<FT,RT>& p) const;
    bool    identical(  const CGAL_PointH2<FT,RT>& p) const;
    int     id() const;

    FT      x()  const;
    FT      y()  const;

    RT      hx() const;
    RT      hy() const;
    RT      hw() const;

    FT      cartesian(int i)   const;
    FT      operator[](int i)  const;
    RT      homogeneous(int i) const;

    int     dimension() const;
    CGAL_Bbox_2
            bbox() const;

    CGAL_PointH2<FT,RT>
            transform( const CGAL_Aff_transformationH2<FT,RT> & t) const;
    CGAL_DirectionH2<FT,RT>
            direction() const;

            CGAL_PointH2(const CGAL_VectorH2<FT,RT>& v);
 friend CGAL_PointH2<FT,RT> operator+(const CGAL_Origin & o,
                                      const CGAL_VectorH2<FT,RT> & v);
 friend CGAL_PointH2<FT,RT> operator-(const CGAL_Origin & o,
                                      const CGAL_VectorH2<FT,RT> & v);
protected:
    CGAL__Threetuple<RT>*
        ptr() const;
};



template < class FT, class RT >
class CGAL_VectorH2 : public CGAL_Handle
{
public:
            CGAL_VectorH2();
            CGAL_VectorH2(const CGAL_VectorH2& v);
            CGAL_VectorH2(const CGAL_Null_vector &);
            CGAL_VectorH2(const RT& x, const RT& y);
            CGAL_VectorH2(const RT& x, const RT& y, const RT& w );
            ~CGAL_VectorH2();
    CGAL_VectorH2<FT,RT> &
            operator=(const CGAL_VectorH2<FT,RT>& v);

    bool    operator==( const CGAL_VectorH2<FT,RT>& v) const;
    bool    operator!=( const CGAL_VectorH2<FT,RT>& v) const;
    bool    operator==( const CGAL_Null_vector&) const;
    bool    operator!=( const CGAL_Null_vector& v) const;
    bool    identical ( const CGAL_VectorH2<FT,RT>& v) const;
    int     id() const;

    FT      x()  const;
    FT      y()  const;
    RT      hx() const;
    RT      hy() const;
    RT      hw() const;
    FT      cartesian(int i)   const;
    RT      homogeneous(int i) const;
    FT      operator[](int i)  const;

    int     dimension() const;
    CGAL_DirectionH2<FT,RT>
            direction() const;
    CGAL_VectorH2<FT,RT>
            transform(const CGAL_Aff_transformationH2<FT,RT>& t ) const;
    CGAL_VectorH2<FT,RT>
            perpendicular(const CGAL_Orientation& o ) const;

    CGAL_VectorH2<FT,RT>
            operator-() const;

// undocumented:

            CGAL_VectorH2(const CGAL_PointH2<FT,RT> & p);
            CGAL_VectorH2(const CGAL_DirectionH2<FT,RT> & dir);
// friends:

friend CGAL_VectorH2<FT,RT> operator-( const CGAL_PointH2<FT,RT> &,
                                       const CGAL_Origin & );
friend CGAL_VectorH2<FT,RT> operator-( const CGAL_Origin &,
                                       const CGAL_PointH2<FT,RT> & );
friend CGAL_PointH2<FT,RT>  operator+( const CGAL_Origin &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_PointH2<FT,RT>  operator-( const CGAL_Origin &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_VectorH2<FT,RT> operator+( const CGAL_VectorH2<FT,RT> &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_VectorH2<FT,RT> operator-( const CGAL_VectorH2<FT,RT> &,
                                       const CGAL_VectorH2<FT,RT> & );
friend FT                   operator*( const CGAL_VectorH2<FT,RT> &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_VectorH2<FT,RT> operator*( const CGAL_VectorH2<FT,RT> &,
                                       const RT & );
friend CGAL_VectorH2<FT,RT> operator*( const RT &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_VectorH2<FT,RT> operator/( const CGAL_VectorH2<FT,RT> &,
                                       const RT & );

protected:

    CGAL__Threetuple<RT>*
            ptr() const;
};




template < class FT, class RT >
class CGAL_DirectionH2 : public CGAL_Handle
{
public:
            CGAL_DirectionH2();
            CGAL_DirectionH2(const CGAL_DirectionH2 & d );
            CGAL_DirectionH2(const CGAL_PointH2<FT,RT> & p );
            CGAL_DirectionH2(const CGAL_VectorH2<FT,RT> & v );
            CGAL_DirectionH2(const RT& x, const RT& y);
            CGAL_DirectionH2(const RT& x, const RT& y, const RT& w );
            ~CGAL_DirectionH2();
    CGAL_DirectionH2<FT,RT> &
            operator=(const CGAL_DirectionH2 & d);

    bool    operator==( const CGAL_DirectionH2& d) const;
    bool    operator!=( const CGAL_DirectionH2& d) const;
    bool    operator< ( const CGAL_DirectionH2& d) const;
    bool    operator<=( const CGAL_DirectionH2& d) const;
    bool    operator> ( const CGAL_DirectionH2& d) const;
    bool    operator>=( const CGAL_DirectionH2& d) const;
    bool    counterclockwise_in_between( const CGAL_DirectionH2& d1,
                                         const CGAL_DirectionH2& d2 ) const;
    bool    identical ( const CGAL_DirectionH2& d) const;
    int     id() const;

    CGAL_DirectionH2<FT,RT>
            operator-() const;


    CGAL_VectorH2<FT,RT>    vector() const;

    RT      x() const;
    RT      y() const;

    RT      delta(int i) const;
    RT      dx() const;
    RT      dy() const;

    CGAL_DirectionH2<FT,RT>
          perpendicular(const CGAL_Orientation &o) const;
    CGAL_DirectionH2<FT,RT>
          transform(const CGAL_Aff_transformationH2<FT,RT> &) const ;

protected:

    CGAL__Threetuple<RT>*
          ptr() const;
};


template < class FT, class RT >
inline
CGAL__Threetuple<RT>*
CGAL_PointH2<FT,RT>::ptr() const
{
 return (CGAL__Threetuple<RT>*)PTR;
}

template < class FT, class RT >
inline
CGAL__Threetuple<RT>*
CGAL_VectorH2<FT,RT>::ptr() const
{
 return (CGAL__Threetuple<RT>*)PTR;
}


template <class FT, class RT >
inline
CGAL__Threetuple<RT>*
CGAL_DirectionH2<FT,RT>::ptr() const
{
 return (CGAL__Threetuple<RT>*)PTR;
}



template < class FT, class RT >
CGAL_PointH2<FT,RT>::CGAL_PointH2()
{
 PTR = new CGAL__Threetuple<RT>();
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>::CGAL_PointH2(const CGAL_Origin&)
{
 PTR = new CGAL__Threetuple<RT>( RT(0)  , RT(0)  , RT(1)   );
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>::CGAL_PointH2(const CGAL_PointH2<FT,RT>& p) :
 CGAL_Handle(p)
{
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>::CGAL_PointH2(const RT& hx, const RT& hy)
{
 PTR = new CGAL__Threetuple<RT>( hx, hy, RT(1) );
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>::CGAL_PointH2(const RT& hx, const RT& hy, const RT& hw)
{
 if ( hw >= RT(0)   )
 {
    PTR = new CGAL__Threetuple<RT>( hx, hy, hw);
 }
 else
 {
    PTR = new CGAL__Threetuple<RT>(-hx,-hy,-hw);
 }
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>::~CGAL_PointH2()
{
}
template < class FT, class RT >
CGAL_PointH2<FT,RT>::CGAL_PointH2(const CGAL_VectorH2<FT,RT>& v) :
 CGAL_Handle( (CGAL_Handle&) v)
{
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>&
CGAL_PointH2<FT,RT>::operator=(const CGAL_PointH2<FT,RT>& p)
{
 CGAL_Handle::operator=(p);
 return *this;
}
template < class FT, class RT >
bool
CGAL_PointH2<FT,RT>::operator==( const CGAL_PointH2<FT,RT>& p) const
{
 return (  (hx() * p.hw() == p.hx() * hw() )
         &&(hy() * p.hw() == p.hy() * hw() ) );
}

template < class FT, class RT >
bool
CGAL_PointH2<FT,RT>::operator!=( const CGAL_PointH2<FT,RT>& p) const
{
 return !(*this == p);
}

template < class FT, class RT >
bool
CGAL_PointH2<FT,RT>::identical( const CGAL_PointH2<FT,RT>& p) const
{
 return ( PTR == p.PTR );
}

template < class FT, class RT >
int
CGAL_PointH2<FT,RT>::id() const
{
 return (int)PTR;
}
template < class FT, class RT >
FT
CGAL_PointH2<FT,RT>::x()  const
{
 return ( FT( hx() ) / FT( hw() ));
}

template < class FT, class RT >
FT
CGAL_PointH2<FT,RT>::y()  const
{
 return ( FT( hy() ) / FT( hw() ));
}

template < class FT, class RT >
RT
CGAL_PointH2<FT,RT>::hx() const
{
 return  ptr()->e0 ;
}

template < class FT, class RT >
RT
CGAL_PointH2<FT,RT>::hy() const
{
 return  ptr()->e1 ;
}

template < class FT, class RT >
RT
CGAL_PointH2<FT,RT>::hw() const
{
 return  ptr()->e2;
}

template < class FT, class RT >
FT
CGAL_PointH2<FT,RT>::cartesian(int i) const
{
 CGAL_kernel_precondition( (i==0 || i==1) );
 switch (i)
 {
    case 0:  return x();
    case 1:  return y();
 }
 return FT(RT());
}

template < class FT, class RT >
RT
CGAL_PointH2<FT,RT>::homogeneous(int i) const
{
 CGAL_kernel_precondition( (i>=0) && (i<=2) );
 switch (i)
 {
    case 0:   return hx();
    case 1:   return hy();
    case 2:   return hw();
 }
 return RT();
}

template < class FT, class RT >
FT
CGAL_PointH2<FT,RT>::operator[](int i) const
{
 return cartesian(i);
}

template < class FT, class RT >
int
CGAL_PointH2<FT,RT>::dimension() const
{
 return 2;
}

template < class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_PointH2<FT,RT>::direction() const
{
 return CGAL_DirectionH2<FT,RT>(*this);
}



template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2()
{
 PTR = new CGAL__Threetuple<RT>();
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_Null_vector &)
{
 PTR = new CGAL__Threetuple<RT>(RT(0), RT(0), RT(1) );
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_VectorH2<FT,RT>& v) :
 CGAL_Handle(v)
{
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const RT& x, const RT& y)
{
 PTR = new CGAL__Threetuple<RT>( x,  y,  RT(1) );
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const RT& x, const RT& y, const RT& w)
{
 if ( w >= RT(0)   )
 {
    PTR = new CGAL__Threetuple<RT>( x,  y,  w);
 }
 else
 {
    PTR = new CGAL__Threetuple<RT>(-x, -y, -w);
 }
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>::~CGAL_VectorH2()
{
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_PointH2<FT,RT> & p) :
 CGAL_Handle( (CGAL_Handle&) p)
{
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_DirectionH2<FT,RT> & dir) :
 CGAL_Handle( (CGAL_Handle &) dir)
{
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT> &
CGAL_VectorH2<FT,RT>::operator=(const CGAL_VectorH2<FT,RT> &v)
{
 CGAL_Handle::operator=(v);
 return *this;
}
template < class FT, class RT >
bool
CGAL_VectorH2<FT,RT>::operator==( const CGAL_Null_vector&) const
{
 return (hx() == RT(0)) && (hy() == RT(0));
}

template < class FT, class RT >
bool
CGAL_VectorH2<FT,RT>::operator!=( const CGAL_Null_vector& v) const
{
  return !(*this == v);
}

template < class FT, class RT >
bool
CGAL_VectorH2<FT,RT>::operator==( const CGAL_VectorH2<FT,RT>& v) const
{
 return (  (hx() * v.hw() == v.hx() * hw() )
         &&(hy() * v.hw() == v.hy() * hw() ) );
}

template < class FT, class RT >
bool
CGAL_VectorH2<FT,RT>::operator!=( const CGAL_VectorH2<FT,RT>& v) const
{
 return !(*this == v);
}

template < class FT, class RT >
bool
CGAL_VectorH2<FT,RT>::identical( const CGAL_VectorH2<FT,RT>& v) const
{
 return ( PTR == v.PTR );
}

template < class FT, class RT >
int
CGAL_VectorH2<FT,RT>::id() const
{
 return (int)PTR;
}
template < class FT, class RT >
FT
CGAL_VectorH2<FT,RT>::x()  const
{
 return FT(ptr()->e0 )/FT(ptr()->e2 ) ;
}


template < class FT, class RT >
FT
CGAL_VectorH2<FT,RT>::y()  const
{
 return FT(ptr()->e1 )/FT(ptr()->e2 ) ;
}

template < class FT, class RT >
RT
CGAL_VectorH2<FT,RT>::hx() const
{
 return  ptr()->e0 ;
}

template < class FT, class RT >
RT
CGAL_VectorH2<FT,RT>::hy() const
{
 return  ptr()->e1 ;
}

template < class FT, class RT >
RT
CGAL_VectorH2<FT,RT>::hw() const
{
 return  ptr()->e2 ;
}

template < class FT, class RT >
FT
CGAL_VectorH2<FT,RT>::cartesian(int i) const
{
 CGAL_kernel_precondition( (i==0 || i==1) );
 switch (i)
 {
    case 0:  return x();
    case 1:  return y();
 }
 return FT(RT());
}

template < class FT, class RT >
RT
CGAL_VectorH2<FT,RT>::homogeneous(int i) const
{
 CGAL_kernel_precondition( (i>=0) && (i<=2) );
 switch (i)
 {
    case 0:  return hx();
    case 1:  return hy();
    case 2:  return hw();
 }
 return RT();
}

template < class FT, class RT >
FT
CGAL_VectorH2<FT,RT>::operator[](int i) const
{
 return cartesian(i);
}

template < class FT, class RT >
int
CGAL_VectorH2<FT,RT>::dimension() const
{
 return 2;
}

template < class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_VectorH2<FT,RT>::direction() const
{
 return CGAL_DirectionH2<FT,RT>(*this);
}
template < class FT, class RT >
CGAL_VectorH2<FT,RT>
CGAL_VectorH2<FT,RT>::operator-() const
{
 return CGAL_VectorH2<FT,RT>(- hx(), - hy(), hw() );
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2()
{
 PTR = new CGAL__Threetuple<RT>();
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const CGAL_DirectionH2<FT,RT>& d ) :
 CGAL_Handle( (CGAL_Handle&) d )
{
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const CGAL_PointH2<FT,RT> & p ) :
 CGAL_Handle( (CGAL_Handle&) p)
{
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const CGAL_VectorH2<FT,RT> & v ) :
 CGAL_Handle( (CGAL_Handle&) v)
{
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const RT& x, const RT& y)
{
 PTR = new CGAL__Threetuple<RT>( x, y, RT(1) );
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const RT& x,
                                          const RT& y,
                                          const RT& w )
{
 if (w > RT(0)   )
 {
    PTR = new CGAL__Threetuple<RT>( x, y, w);
 }
 else
 {
    PTR = new CGAL__Threetuple<RT>(-x,-y,-w);
 }
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::~CGAL_DirectionH2()
{
}

template < class FT, class RT >
CGAL_DirectionH2<FT,RT> &
CGAL_DirectionH2<FT,RT>::operator=(const CGAL_DirectionH2<FT,RT> &d)
{
 CGAL_Handle::operator=(d);
 return *this;
}

template <class FT, class RT >
bool
CGAL_DirectionH2<FT,RT>::operator==( const CGAL_DirectionH2<FT,RT>& d) const
{
 return (  ( x() * d.y() == y() * d.x() )
         &&( CGAL_sign( x() ) == CGAL_sign( d.x() ) )
         &&( CGAL_sign( y() ) == CGAL_sign( d.y() ) ) );
}

template <class FT, class RT >
bool
CGAL_DirectionH2<FT,RT>::operator!=( const CGAL_DirectionH2<FT,RT>& d) const
{
 return !(*this == d);
}

template <class FT, class RT >
bool
CGAL_DirectionH2<FT,RT>::identical( const CGAL_DirectionH2<FT,RT>& d) const
{
 return ( PTR == d.PTR );
}

template <class FT, class RT >
int
CGAL_DirectionH2<FT,RT>::id() const
{
 return (int)PTR;
}
template <class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_DirectionH2<FT,RT>::operator-() const
{
 return CGAL_DirectionH2<FT,RT>( - x(), - y() );
}
template <class FT, class RT >
RT
CGAL_DirectionH2<FT,RT>::dx() const
{
 return ptr()->e0;
}

template <class FT, class RT >
RT
CGAL_DirectionH2<FT,RT>::dy() const
{
 return ptr()->e1;
}

template <class FT, class RT >
RT
CGAL_DirectionH2<FT,RT>::delta(int i) const
{
 CGAL_kernel_precondition( ( i == 0 ) || ( i == 1 ) );
 if (i == 0)
 {
    return dx();
 }
 return dy();
}

template <class FT, class RT >
RT
CGAL_DirectionH2<FT,RT>::x() const
{
 return ptr()->e0;
}

template <class FT, class RT >
RT
CGAL_DirectionH2<FT,RT>::y() const
{
 return ptr()->e1;
}


template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator+(const CGAL_VectorH2<FT,RT>& u, const CGAL_VectorH2<FT,RT>& v)
{
 return CGAL_VectorH2<FT,RT>( u.hx()*v.hw() + v.hx()*u.hw(),
                              u.hy()*v.hw() + v.hy()*u.hw(),
                              u.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator-(const CGAL_VectorH2<FT,RT>& u, const CGAL_VectorH2<FT,RT>& v)
{
 return CGAL_VectorH2<FT,RT>( u.hx()*v.hw() - v.hx()*u.hw(),
                              u.hy()*v.hw() - v.hy()*u.hw(),
                              u.hw()*v.hw() );
}

template <class FT, class RT>
FT
operator*(const CGAL_VectorH2<FT,RT>& u, const CGAL_VectorH2<FT,RT>& v)
{

 return (   FT( RT(u.hx()*v.hx() + u.hy()*v.hy()) )  /
            FT( RT(u.hw()*v.hw() ) )    );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator/(const CGAL_VectorH2<FT,RT>& v, const RT& f)
{
 return CGAL_VectorH2<FT,RT>( v.hx(), v.hy(), v.hw()*f );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator*(const CGAL_VectorH2<FT,RT>& v, const RT& f)
{
 return CGAL_VectorH2<FT,RT>( v.hx()*f, v.hy()*f, v.hw() );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator*(const RT& f, const CGAL_VectorH2<FT,RT>& v)
{
 return CGAL_VectorH2<FT,RT>( v.hx()*f, v.hy()*f, v.hw() );
}



template <class FT, class RT>
CGAL_PointH2<FT,RT>
operator+(const CGAL_Origin&, const CGAL_VectorH2<FT,RT>& v)
{
 return CGAL_PointH2<FT,RT>( v );
}

template <class FT, class RT>
CGAL_PointH2<FT,RT>
operator-(const CGAL_Origin&, const CGAL_VectorH2<FT,RT>& v)
{
 return CGAL_PointH2<FT,RT>( -v );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator-(const CGAL_PointH2<FT,RT>& p, const CGAL_Origin&)
{
 return CGAL_VectorH2<FT,RT>( p );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator-(const CGAL_Origin&, const CGAL_PointH2<FT,RT>& p)
{
 return  - CGAL_VectorH2<FT,RT>( p );
}




template <class FT, class RT>
CGAL_PointH2<FT,RT>
operator+(const CGAL_PointH2<FT,RT>& p, const CGAL_VectorH2<FT,RT>& v)
{
 return CGAL_PointH2<FT,RT>( p.hx()*v.hw() + v.hx()*p.hw(),
                             p.hy()*v.hw() + v.hy()*p.hw(),
                             p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_PointH2<FT,RT>
operator-(const CGAL_PointH2<FT,RT>& p, const CGAL_VectorH2<FT,RT>& v)
{
 return CGAL_PointH2<FT,RT>( p.hx()*v.hw() - v.hx()*p.hw(),
                             p.hy()*v.hw() - v.hy()*p.hw(),
                             p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator-(const CGAL_PointH2<FT,RT>& p, const CGAL_PointH2<FT,RT>& q)
{
 return CGAL_VectorH2<FT,RT>( p.hx()*q.hw() - q.hx()*p.hw(),
                              p.hy()*q.hw() - q.hy()*p.hw(),
                              p.hw()*q.hw() );
}


#include <CGAL/predicates_on_directionsH2.h>
template <class FT, class RT >
bool
CGAL_DirectionH2<FT,RT>::operator< (const CGAL_DirectionH2<FT,RT>& d) const
{
 return (CGAL_compare_angles_with_x_axis(*this,d) == CGAL_SMALLER);
}

template <class FT, class RT >
bool
CGAL_DirectionH2<FT,RT>::operator> (const CGAL_DirectionH2<FT,RT>& d) const
{
 return (CGAL_compare_angles_with_x_axis(*this,d) == CGAL_LARGER);
}

template <class FT, class RT >
bool
CGAL_DirectionH2<FT,RT>::operator>= (const CGAL_DirectionH2<FT,RT>& d) const
{
 return !(CGAL_compare_angles_with_x_axis(*this,d) == CGAL_SMALLER);
}

template <class FT, class RT >
bool
CGAL_DirectionH2<FT,RT>::operator<= (const CGAL_DirectionH2<FT,RT>& d) const
{
 return !(CGAL_compare_angles_with_x_axis(*this,d) == CGAL_LARGER);
}

template <class FT, class RT >
bool
CGAL_DirectionH2<FT,RT>::counterclockwise_in_between(
                           const CGAL_DirectionH2<FT,RT>& d1,
                           const CGAL_DirectionH2<FT,RT>& d2) const
{
 if ( d1 <= *this)
 {
    return ( *this <= d2 )||( d2 <= d1 );
 }
 else
 {
    return ( *this <= d2 )&&( d2 <= d1 );
 }
}


#include <CGAL/Aff_transformationH2.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/misc.h>


template < class FT, class RT >
CGAL_Bbox_2
CGAL_PointH2<FT,RT>::bbox() const
{
 // double eps  = exp2(-52);
 // the following is faster as it can be evaluated at compile time
 // and it is machine independent
 double eps  = double(1.0) /(double(1<<26) * double(1<<26));
 double hxd  = CGAL_to_double( hx() );
 double hyd  = CGAL_to_double( hy() );
 double hwd  = CGAL_to_double( hw() );
 double xmin = ( hxd - eps*hxd ) / ( hwd + eps*hwd );
 double xmax = ( hxd + eps*hxd ) / ( hwd - eps*hwd );
 double ymin = ( hyd - eps*hyd ) / ( hwd + eps*hwd );
 double ymax = ( hyd + eps*hyd ) / ( hwd - eps*hwd );
 if ( hx() < RT(0)   )
 {
    CGAL_swap(xmin, xmax);
 }
 if ( hy() < RT(0)   )
 {
    CGAL_swap(ymin, ymax);
 }
 return CGAL_Bbox_2(xmin, ymin, xmax, ymax);
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_PointH2<FT,RT>::transform(const CGAL_Aff_transformationH2<FT,RT>& t) const
{
 return t.transform(*this);
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>
CGAL_VectorH2<FT,RT>::perpendicular(const CGAL_Orientation& o) const
{
 CGAL_kernel_precondition(o != CGAL_COLLINEAR);
 if (o == CGAL_COUNTERCLOCKWISE)
 {
    return CGAL_VectorH2<FT,RT>(-hy(), hx(), hw());
 }
 else
 {
    return CGAL_VectorH2<FT,RT>(hy(), -hx(), hw());
 }
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>
CGAL_VectorH2<FT,RT>::transform(const CGAL_Aff_transformationH2<FT,RT>& t) const
{
 return t.transform(*this);
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_DirectionH2<FT,RT>::perpendicular(const CGAL_Orientation& o) const
{
 CGAL_kernel_precondition(o != CGAL_COLLINEAR);
 if (o == CGAL_COUNTERCLOCKWISE)
 {
    return CGAL_DirectionH2<FT,RT>(-dy(), dx());
 }
 else
 {
    return CGAL_DirectionH2<FT,RT>(dy(), -dx());
 }
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_DirectionH2<FT,RT>::transform(
                           const CGAL_Aff_transformationH2<FT,RT>& t) const
{
 return t.transform(*this);
}

template <class FT, class RT >
CGAL_VectorH2<FT,RT>
CGAL_DirectionH2<FT,RT>::vector() const
{
 return CGAL_VectorH2<FT,RT>( x(), y() );
}



#endif // CGAL_PVDH2
