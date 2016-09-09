 

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
class CGAL_PointH2 : public handle_base
{

public:
            CGAL_PointH2();
            CGAL_PointH2(const CGAL_Origin & o);
            CGAL_PointH2(const CGAL_PointH2 & p);
            CGAL_PointH2(const RT& hx, const RT& hy, const RT& hw = RT(1)   );
            ~CGAL_PointH2();

    CGAL_PointH2 &
            operator=( const CGAL_PointH2& p);

    bool    operator==( const CGAL_PointH2& p) const;
    bool    operator!=( const CGAL_PointH2& p) const;
    bool    identical(  const CGAL_PointH2& p) const;

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
 
#ifdef CGAL_CHECK_PRECONDITIONS
    bool    is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS
 
 friend CGAL_PointH2<FT,RT> operator+(const CGAL_Origin & o,
                                      const CGAL_VectorH2<FT,RT> & v);
 friend CGAL_PointH2<FT,RT> operator-(const CGAL_Origin & o,
                                      const CGAL_VectorH2<FT,RT> & v);
 
protected:
    CGAL__Threetuple<RT>*
        ptr() const;
};
 

 


template < class FT, class RT >
class CGAL_VectorH2 : public handle_base
{
public:
            CGAL_VectorH2();
            CGAL_VectorH2(const CGAL_VectorH2& v);
            CGAL_VectorH2(const RT& x, const RT& y, const RT& w = RT(1)   );
            ~CGAL_VectorH2();
    CGAL_VectorH2 &
            operator=(const CGAL_VectorH2<FT,RT>& v);

    bool    operator==( const CGAL_VectorH2& v) const;
    bool    operator!=( const CGAL_VectorH2& v) const;
    bool    identical ( const CGAL_VectorH2& v) const;

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
    CGAL_VectorH2
            transform(const CGAL_Aff_transformationH2<FT,RT>& t ) const;

    CGAL_VectorH2
            operator-() const;

#ifdef CGAL_CHECK_PRECONDITIONS
    bool    is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

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
class CGAL_DirectionH2 : public handle_base
{
public:
            CGAL_DirectionH2();
            CGAL_DirectionH2(const CGAL_DirectionH2 & d );
            CGAL_DirectionH2(const CGAL_PointH2<FT,RT> & p );
            CGAL_DirectionH2(const CGAL_VectorH2<FT,RT> & v );
            CGAL_DirectionH2(const RT& x, const RT& y, const RT& w = RT(1)   );
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

    CGAL_DirectionH2<FT,RT>
            operator-() const;

#ifdef CGAL_CHECK_PRECONDITIONS
    bool    is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

    CGAL_VectorH2<FT,RT>    vector() const;

    RT      x() const;
    RT      y() const;

    CGAL_DirectionH2
          transform(const CGAL_Aff_transformationH2<FT,RT> &) const ;

protected:

    CGAL__Threetuple<RT>*
          ptr() const;
};
 


 
#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT, class RT >
inline
bool
CGAL_PointH2<FT,RT>::is_defined() const
{
  return !(PTR == NULL);
}
#endif // CGAL_CHECK_PRECONDITIONS

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

#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT, class RT >
inline
bool
CGAL_VectorH2<FT,RT>::is_defined() const
{
  return !(PTR == NULL);
}
#endif // CGAL_CHECK_PRECONDITIONS
 

 
template <class FT, class RT >
inline
CGAL__Threetuple<RT>*
CGAL_DirectionH2<FT,RT>::ptr() const
{
 return (CGAL__Threetuple<RT>*)PTR;
}

#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT, class RT >
inline
bool
CGAL_DirectionH2<FT,RT>::is_defined() const
{
  return !(PTR == NULL);
}
#endif // CGAL_CHECK_PRECONDITIONS
 


 
template < class FT, class RT >
CGAL_PointH2<FT,RT>::CGAL_PointH2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
 PTR = NULL;
#else
 PTR = new CGAL__Threetuple<RT>();
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>::CGAL_PointH2(const CGAL_Origin&)
{
 PTR = new CGAL__Threetuple<RT>( RT(0)  , RT(0)  , RT(1)   );
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>::CGAL_PointH2(const CGAL_PointH2<FT,RT>& p) :
 handle_base(p)
{
 CGAL_kernel_precondition( p.is_defined() );
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
 handle_base( (handle_base&) v)
{
 CGAL_kernel_precondition( v.is_defined() );
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>&
CGAL_PointH2<FT,RT>::operator=(const CGAL_PointH2<FT,RT>& p)
{
 CGAL_kernel_precondition(p.is_defined());
 handle_base::operator=(p);
 return *this;
}
 
template < class FT, class RT >
bool
CGAL_PointH2<FT,RT>::operator==( const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition(is_defined() && p.is_defined());
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
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 return ( PTR == p.PTR );
}
 
template < class FT, class RT >
FT
CGAL_PointH2<FT,RT>::x()  const
{
 CGAL_kernel_precondition( is_defined() );
 return ( FT( hx() ) / FT( hw() ));
}

template < class FT, class RT >
FT
CGAL_PointH2<FT,RT>::y()  const
{
 CGAL_kernel_precondition( is_defined() );
 return ( FT( hy() ) / FT( hw() ));
}

template < class FT, class RT >
RT
CGAL_PointH2<FT,RT>::hx() const
{
 CGAL_kernel_precondition( is_defined() );
 return  ptr()->e0 ;
}

template < class FT, class RT >
RT
CGAL_PointH2<FT,RT>::hy() const
{
 CGAL_kernel_precondition( is_defined() );
 return  ptr()->e1 ;
}

template < class FT, class RT >
RT
CGAL_PointH2<FT,RT>::hw() const
{
 CGAL_kernel_precondition( is_defined() );
 return  ptr()->e2;
}

template < class FT, class RT >
FT
CGAL_PointH2<FT,RT>::cartesian(int i) const
{
 CGAL_kernel_precondition( (i==0 || i==1) && is_defined() );
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
 CGAL_kernel_precondition( (i>=0) && (i<=2) && is_defined() );
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
 CGAL_kernel_precondition( is_defined() );
 return 2;
}

template < class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_PointH2<FT,RT>::direction() const
{
 CGAL_kernel_precondition( is_defined() );
 return CGAL_DirectionH2<FT,RT>(*this);
}
 

 


template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
 PTR = NULL;
#else
 PTR = new CGAL__Threetuple<RT>();
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_VectorH2<FT,RT>& v) :
 handle_base(v)
{
 CGAL_kernel_precondition( v.is_defined() );
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
 handle_base( (handle_base&) p)
{
 CGAL_kernel_precondition( p.is_defined() );
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_DirectionH2<FT,RT> & dir) :
 handle_base( (handle_base &) dir)
{
 CGAL_kernel_precondition( dir.is_defined() );
}

template < class FT, class RT >
CGAL_VectorH2<FT,RT> &
CGAL_VectorH2<FT,RT>::operator=(const CGAL_VectorH2<FT,RT> &v)
{
 CGAL_kernel_precondition(v.is_defined());
 handle_base::operator=(v);
 return *this;
}
 
template < class FT, class RT >
bool
CGAL_VectorH2<FT,RT>::operator==( const CGAL_VectorH2<FT,RT>& v) const
{
 CGAL_kernel_precondition(is_defined() && v.is_defined());
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
 CGAL_kernel_precondition(is_defined() && v.is_defined());
 return ( PTR == v.PTR );
}
 
template < class FT, class RT >
FT
CGAL_VectorH2<FT,RT>::x()  const
{
 CGAL_kernel_precondition( is_defined() );
 return FT(ptr()->e0 )/FT(ptr()->e2 ) ;
}


template < class FT, class RT >
FT
CGAL_VectorH2<FT,RT>::y()  const
{
 CGAL_kernel_precondition( is_defined() );
 return FT(ptr()->e1 )/FT(ptr()->e2 ) ;
}

template < class FT, class RT >
RT
CGAL_VectorH2<FT,RT>::hx() const
{
 CGAL_kernel_precondition( is_defined() );
 return  ptr()->e0 ;
}

template < class FT, class RT >
RT
CGAL_VectorH2<FT,RT>::hy() const
{
 CGAL_kernel_precondition( is_defined() );
 return  ptr()->e1 ;
}

template < class FT, class RT >
RT
CGAL_VectorH2<FT,RT>::hw() const
{
 CGAL_kernel_precondition( is_defined() );
 return  ptr()->e2 ;
}

template < class FT, class RT >
FT
CGAL_VectorH2<FT,RT>::cartesian(int i) const
{
 CGAL_kernel_precondition( (i==0 || i==1) && is_defined() );
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
 CGAL_kernel_precondition( (i>=0) && (i<=2) && is_defined() );
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
 CGAL_kernel_precondition( is_defined() );
 return 2;
}

template < class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_VectorH2<FT,RT>::direction() const
{
 CGAL_kernel_precondition( is_defined() );
 return CGAL_DirectionH2<FT,RT>(*this);
}
 
template < class FT, class RT >
CGAL_VectorH2<FT,RT>
CGAL_VectorH2<FT,RT>::operator-() const
{
 CGAL_kernel_precondition( is_defined() );
 return CGAL_VectorH2<FT,RT>(- hx(), - hy(), hw() );
}
 

 
template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
 PTR = NULL;
#else
 PTR = new CGAL__Threetuple<RT>();
#endif // CGAL_CHECK_PRECONDITIONS
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const CGAL_DirectionH2<FT,RT>& d ) :
 handle_base( (handle_base&) d )
{
 CGAL_kernel_precondition( d.is_defined() );
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const CGAL_PointH2<FT,RT> & p ) :
 handle_base( (handle_base&) p)
{
 CGAL_kernel_precondition( p.is_defined() );
}

template <class FT, class RT >
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const CGAL_VectorH2<FT,RT> & v ) :
 handle_base( (handle_base&) v)
{
 CGAL_kernel_precondition( v.is_defined() );
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
 CGAL_kernel_precondition(d.is_defined());
 handle_base::operator=(d);
 return *this;
}
 

template <class FT, class RT >
bool
CGAL_DirectionH2<FT,RT>::operator==( const CGAL_DirectionH2<FT,RT>& d) const
{
 CGAL_kernel_precondition( is_defined() && d.is_defined() );
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
 CGAL_kernel_precondition( is_defined() && d.is_defined() );
 return ( PTR == d.PTR );
}
 
template <class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_DirectionH2<FT,RT>::operator-() const
{
 CGAL_kernel_precondition( is_defined() );
 return CGAL_DirectionH2<FT,RT>( - x(), - y() );
}
 
template <class FT, class RT >
RT
CGAL_DirectionH2<FT,RT>::x() const
{
 CGAL_kernel_precondition( is_defined() );
 return ptr()->e0;
}

template <class FT, class RT >
RT
CGAL_DirectionH2<FT,RT>::y() const
{
 CGAL_kernel_precondition( is_defined() );
 return ptr()->e1;
}
 


 
template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator+(const CGAL_VectorH2<FT,RT>& u, const CGAL_VectorH2<FT,RT>& v)
{
 CGAL_kernel_precondition( u.is_defined() && v.is_defined() );
 return CGAL_VectorH2<FT,RT>( u.hx()*v.hw() + v.hx()*u.hw(),
                              u.hy()*v.hw() + v.hy()*u.hw(),
                              u.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator-(const CGAL_VectorH2<FT,RT>& u, const CGAL_VectorH2<FT,RT>& v)
{
 CGAL_kernel_precondition( u.is_defined() && v.is_defined() );
 return CGAL_VectorH2<FT,RT>( u.hx()*v.hw() - v.hx()*u.hw(),
                              u.hy()*v.hw() - v.hy()*u.hw(),
                              u.hw()*v.hw() );
}

template <class FT, class RT>
FT
operator*(const CGAL_VectorH2<FT,RT>& u, const CGAL_VectorH2<FT,RT>& v)
{
 CGAL_kernel_precondition( u.is_defined() && v.is_defined() );

 return (   FT( RT(u.hx()*v.hx() + u.hy()*v.hy()) )  /
            FT( RT(u.hw()*v.hw() ) )    );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator/(const CGAL_VectorH2<FT,RT>& v, const RT& f)
{
 CGAL_kernel_precondition( v.is_defined() );
 return CGAL_VectorH2<FT,RT>( v.hx(), v.hy(), v.hw()*f );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator*(const CGAL_VectorH2<FT,RT>& v, const RT& f)
{
 CGAL_kernel_precondition( v.is_defined() );
 return CGAL_VectorH2<FT,RT>( v.hx()*f, v.hy()*f, v.hw() );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator*(const RT& f, const CGAL_VectorH2<FT,RT>& v)
{
 CGAL_kernel_precondition( v.is_defined() );
 return CGAL_VectorH2<FT,RT>( v.hx()*f, v.hy()*f, v.hw() );
}
 

 


template <class FT, class RT>
CGAL_PointH2<FT,RT>
operator+(const CGAL_Origin&, const CGAL_VectorH2<FT,RT>& v)
{
 CGAL_kernel_precondition( v.is_defined() );
 return CGAL_PointH2<FT,RT>( v );
}

template <class FT, class RT>
CGAL_PointH2<FT,RT>
operator-(const CGAL_Origin&, const CGAL_VectorH2<FT,RT>& v)
{
 CGAL_kernel_precondition( v.is_defined() );
 return CGAL_PointH2<FT,RT>( -v );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator-(const CGAL_PointH2<FT,RT>& p, const CGAL_Origin&)
{
 CGAL_kernel_precondition( p.is_defined() );
 return CGAL_VectorH2<FT,RT>( p );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator-(const CGAL_Origin&, const CGAL_PointH2<FT,RT>& p)
{
 CGAL_kernel_precondition( p.is_defined() );
 return  - CGAL_VectorH2<FT,RT>( p );
}
 

 



template <class FT, class RT>
CGAL_PointH2<FT,RT>
operator+(const CGAL_PointH2<FT,RT>& p, const CGAL_VectorH2<FT,RT>& v)
{
 CGAL_kernel_precondition( p.is_defined() && v.is_defined() );
 return CGAL_PointH2<FT,RT>( p.hx()*v.hw() + v.hx()*p.hw(),
                             p.hy()*v.hw() + v.hy()*p.hw(),
                             p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_PointH2<FT,RT>
operator-(const CGAL_PointH2<FT,RT>& p, const CGAL_VectorH2<FT,RT>& v)
{
 CGAL_kernel_precondition( p.is_defined() && v.is_defined() );
 return CGAL_PointH2<FT,RT>( p.hx()*v.hw() - v.hx()*p.hw(),
                             p.hy()*v.hw() - v.hy()*p.hw(),
                             p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
operator-(const CGAL_PointH2<FT,RT>& p, const CGAL_PointH2<FT,RT>& q)
{
 CGAL_kernel_precondition( p.is_defined() && q.is_defined() );
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
 CGAL_kernel_precondition( is_defined() && d1.is_defined() && d2.is_defined() );
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
 CGAL_kernel_precondition( is_defined() );
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
 CGAL_kernel_precondition( is_defined() && t.is_defined() );
 return t.transform(*this);
}
 

 
template < class FT, class RT >
CGAL_VectorH2<FT,RT>
CGAL_VectorH2<FT,RT>::transform(const CGAL_Aff_transformationH2<FT,RT>& t) const
{
 CGAL_kernel_precondition( is_defined() && t.is_defined() );
 return t.transform(*this);
}
 

 
template <class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_DirectionH2<FT,RT>::transform(
                           const CGAL_Aff_transformationH2<FT,RT>& t) const
{
 CGAL_kernel_precondition( t.is_defined() );
 return t.transform(*this);
}

template <class FT, class RT >
CGAL_VectorH2<FT,RT>
CGAL_DirectionH2<FT,RT>::vector() const
{
 return CGAL_VectorH2<FT,RT>( x(), y() );
}
 



#endif // CGAL_PVDH2
