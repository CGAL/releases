// ============================================================================
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/PVDH2.h
// author(s)     : Stefan Schirra 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_PVDH2
#define CGAL_PVDH2

#define CGAL_POINTH2_H
#define CGAL_VECTORH2_H
#define CGAL_DIRECTIONH2_H

#ifndef CGAL_THREETUPLE_H
#include <CGAL/Threetuple.h>
#endif // CGAL_THREETUPLE_H
#ifndef CGAL_HOMOGENEOUS_CLASSES_H
#include <CGAL/homogeneous_classes.h>
#endif // CGAL_HOMOGENEOUS_CLASSES_H
#ifndef CGAL_ORIGIN_H
#include <CGAL/Origin.h>
#endif // CGAL_ORIGIN_H

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
            operator=( const CGAL_PointH2<FT,RT>& p);

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

    // and for efficiency in the predicates:

    int     dimension() const;
    CGAL_Bbox_2
            bbox() const;

    CGAL_PointH2<FT,RT>
            transform( const CGAL_Aff_transformationH2<FT,RT> & t) const;
    CGAL_DirectionH2<FT,RT>
            direction() const;

            CGAL_PointH2(const CGAL_VectorH2<FT,RT>& v);
 friend CGAL_PointH2<FT,RT>
        operator+ CGAL_NULL_TMPL_ARGS (const CGAL_Origin & o,
                                       const CGAL_VectorH2<FT,RT> & v);
 friend CGAL_PointH2<FT,RT>
        operator- CGAL_NULL_TMPL_ARGS (const CGAL_Origin & o,
                                       const CGAL_VectorH2<FT,RT> & v);
protected:
    CGAL__Threetuple<RT>*   ptr() const;
};

template < class FT, class RT >
class CGAL_VectorH2 : public CGAL_Handle
{
public:
            CGAL_VectorH2();
            CGAL_VectorH2(const CGAL_VectorH2<FT,RT>& v);
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

friend CGAL_VectorH2<FT,RT>
       operator- CGAL_NULL_TMPL_ARGS ( const CGAL_PointH2<FT,RT> &,
                                       const CGAL_Origin & );
friend CGAL_VectorH2<FT,RT>
       operator- CGAL_NULL_TMPL_ARGS ( const CGAL_Origin &,
                                       const CGAL_PointH2<FT,RT> & );
friend CGAL_PointH2<FT,RT>
       operator+ CGAL_NULL_TMPL_ARGS ( const CGAL_Origin &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_PointH2<FT,RT>
       operator- CGAL_NULL_TMPL_ARGS ( const CGAL_Origin &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_VectorH2<FT,RT>
       operator+ CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH2<FT,RT> &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_VectorH2<FT,RT>
       operator- CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH2<FT,RT> &,
                                       const CGAL_VectorH2<FT,RT> & );
friend FT
       operator* CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH2<FT,RT> &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_VectorH2<FT,RT>
       operator* CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH2<FT,RT> &,
                                       const RT & );
friend CGAL_VectorH2<FT,RT>
       operator* CGAL_NULL_TMPL_ARGS ( const RT &,
                                       const CGAL_VectorH2<FT,RT> & );
friend CGAL_VectorH2<FT,RT>
       operator/ CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH2<FT,RT> &,
                                       const RT & );
protected:
    CGAL__Threetuple<RT>* ptr() const;
};

template < class FT, class RT >
class CGAL_DirectionH2 : public CGAL_Handle
{
public:
            CGAL_DirectionH2();
            CGAL_DirectionH2(const CGAL_DirectionH2<FT,RT>& d );
            CGAL_DirectionH2(const CGAL_PointH2<FT,RT> & p );
            CGAL_DirectionH2(const CGAL_VectorH2<FT,RT> & v );
            CGAL_DirectionH2(const RT& x, const RT& y);
            CGAL_DirectionH2(const RT& x, const RT& y, const RT& w );
            ~CGAL_DirectionH2();
    CGAL_DirectionH2<FT,RT> &
            operator=(const CGAL_DirectionH2<FT,RT>& d);

    bool    operator==( const CGAL_DirectionH2<FT,RT>& d) const;
    bool    operator!=( const CGAL_DirectionH2<FT,RT>& d) const;
    bool    operator< ( const CGAL_DirectionH2<FT,RT>& d) const;
    bool    operator<=( const CGAL_DirectionH2<FT,RT>& d) const;
    bool    operator> ( const CGAL_DirectionH2<FT,RT>& d) const;
    bool    operator>=( const CGAL_DirectionH2<FT,RT>& d) const;
    bool    counterclockwise_in_between( const CGAL_DirectionH2<FT,RT>& d1,
                                     const CGAL_DirectionH2<FT,RT>& d2 ) const;
    bool    identical ( const CGAL_DirectionH2<FT,RT>& d) const;
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

    CGAL__Threetuple<RT>*    ptr() const;
};


template < class FT, class RT >
inline
CGAL__Threetuple<RT>*
CGAL_PointH2<FT,RT>::ptr() const
{ return (CGAL__Threetuple<RT>*)PTR; }

template < class FT, class RT >
inline
CGAL__Threetuple<RT>*
CGAL_VectorH2<FT,RT>::ptr() const
{ return (CGAL__Threetuple<RT>*)PTR; }


template <class FT, class RT >
inline
CGAL__Threetuple<RT>*
CGAL_DirectionH2<FT,RT>::ptr() const
{ return (CGAL__Threetuple<RT>*)PTR; }



template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH2<FT,RT>::CGAL_PointH2()
{ PTR = new CGAL__Threetuple<RT>(); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH2<FT,RT>::CGAL_PointH2(const CGAL_Origin&)
{ PTR = new CGAL__Threetuple<RT>( RT(0)  , RT(0)  , RT(1)   ); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH2<FT,RT>::CGAL_PointH2(const CGAL_PointH2<FT,RT>& p)
  : CGAL_Handle(p)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH2<FT,RT>::CGAL_PointH2(const RT& hx, const RT& hy)
{ PTR = new CGAL__Threetuple<RT>( hx, hy, RT(1) ); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
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
inline
CGAL_PointH2<FT,RT>::~CGAL_PointH2()
{}
template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH2<FT,RT>::CGAL_PointH2(const CGAL_VectorH2<FT,RT>& v)
  : CGAL_Handle( (CGAL_Handle&) v)
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH2<FT,RT>&
CGAL_PointH2<FT,RT>::operator=(const CGAL_PointH2<FT,RT>& p)
{
  CGAL_Handle::operator=(p);
  return *this;
}
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_PointH2<FT,RT>::operator==( const CGAL_PointH2<FT,RT>& p) const
{
  return (  (hx() * p.hw() == p.hx() * hw() )
          &&(hy() * p.hw() == p.hy() * hw() ) );
}

template < class FT, class RT >
inline
bool
CGAL_PointH2<FT,RT>::operator!=( const CGAL_PointH2<FT,RT>& p) const
{ return !(*this == p); }   /* XXX */

template < class FT, class RT >
inline
bool
CGAL_PointH2<FT,RT>::identical( const CGAL_PointH2<FT,RT>& p) const
{ return ( PTR == p.PTR ); }

template < class FT, class RT >
inline
int
CGAL_PointH2<FT,RT>::id() const
{ return (int)PTR; }
template < class FT, class RT >
inline
FT
CGAL_PointH2<FT,RT>::x()  const
{ return ( FT( hx() ) / FT( hw() )); }

template < class FT, class RT >
inline
FT
CGAL_PointH2<FT,RT>::y()  const
{ return ( FT( hy() ) / FT( hw() )); }

template < class FT, class RT >
inline
RT
CGAL_PointH2<FT,RT>::hx() const
{ return  ptr()->e0 ; }

template < class FT, class RT >
inline
RT
CGAL_PointH2<FT,RT>::hy() const
{ return  ptr()->e1 ; }

template < class FT, class RT >
inline
RT
CGAL_PointH2<FT,RT>::hw() const
{ return  ptr()->e2; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
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
CGAL_KERNEL_INLINE
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
inline
FT
CGAL_PointH2<FT,RT>::operator[](int i) const
{ return cartesian(i); }

template < class FT, class RT >
inline
int
CGAL_PointH2<FT,RT>::dimension() const
{ return 2; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_DirectionH2<FT,RT>
CGAL_PointH2<FT,RT>::direction() const
{ return CGAL_DirectionH2<FT,RT>(*this); }



template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH2<FT,RT>::CGAL_VectorH2()
{ PTR = new CGAL__Threetuple<RT>(); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_Null_vector &)
{ PTR = new CGAL__Threetuple<RT>(RT(0), RT(0), RT(1) ); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_VectorH2<FT,RT>& v)
  : CGAL_Handle(v)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const RT& x, const RT& y)
{ PTR = new CGAL__Threetuple<RT>( x,  y,  RT(1) ); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
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
inline
CGAL_VectorH2<FT,RT>::~CGAL_VectorH2()
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_PointH2<FT,RT> & p)
  : CGAL_Handle( (CGAL_Handle&) p)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH2<FT,RT>::CGAL_VectorH2(const CGAL_DirectionH2<FT,RT> & dir)
  : CGAL_Handle( (CGAL_Handle &) dir)
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_VectorH2<FT,RT> &
CGAL_VectorH2<FT,RT>::operator=(const CGAL_VectorH2<FT,RT> &v)
{
  CGAL_Handle::operator=(v);
  return *this;
}
template < class FT, class RT >
inline
bool
CGAL_VectorH2<FT,RT>::operator==( const CGAL_Null_vector&) const
{ return (hx() == RT(0)) && (hy() == RT(0)); }

template < class FT, class RT >
inline
bool
CGAL_VectorH2<FT,RT>::operator!=( const CGAL_Null_vector& v) const
{ return !(*this == v); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_VectorH2<FT,RT>::operator==( const CGAL_VectorH2<FT,RT>& v) const
{
  return (  (hx() * v.hw() == v.hx() * hw() )
          &&(hy() * v.hw() == v.hy() * hw() ) );
}

template < class FT, class RT >
inline
bool
CGAL_VectorH2<FT,RT>::operator!=( const CGAL_VectorH2<FT,RT>& v) const
{ return !(*this == v); }  /* XXX */

template < class FT, class RT >
inline
bool
CGAL_VectorH2<FT,RT>::identical( const CGAL_VectorH2<FT,RT>& v) const
{ return ( PTR == v.PTR ); }

template < class FT, class RT >
inline
int
CGAL_VectorH2<FT,RT>::id() const
{ return (int)PTR; }
template < class FT, class RT >
inline
FT
CGAL_VectorH2<FT,RT>::x()  const
{ return FT(ptr()->e0 )/FT(ptr()->e2 ) ; }


template < class FT, class RT >
inline
FT
CGAL_VectorH2<FT,RT>::y()  const
{ return FT(ptr()->e1 )/FT(ptr()->e2 ) ; }

template < class FT, class RT >
inline
RT
CGAL_VectorH2<FT,RT>::hx() const
{ return  ptr()->e0 ; }

template < class FT, class RT >
inline
RT
CGAL_VectorH2<FT,RT>::hy() const
{ return  ptr()->e1 ; }

template < class FT, class RT >
inline
RT
CGAL_VectorH2<FT,RT>::hw() const
{ return  ptr()->e2 ; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
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
CGAL_KERNEL_INLINE
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
inline
FT
CGAL_VectorH2<FT,RT>::operator[](int i) const
{ return cartesian(i); }

template < class FT, class RT >
inline
int
CGAL_VectorH2<FT,RT>::dimension() const
{ return 2; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_DirectionH2<FT,RT>
CGAL_VectorH2<FT,RT>::direction() const
{ return CGAL_DirectionH2<FT,RT>(*this); }
template < class FT, class RT >
inline
CGAL_VectorH2<FT,RT>
CGAL_VectorH2<FT,RT>::operator-() const
{ return CGAL_VectorH2<FT,RT>(- hx(), - hy(), hw() ); }

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2()
{ PTR = new CGAL__Threetuple<RT>(); }

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const CGAL_DirectionH2<FT,RT>& d )
  : CGAL_Handle( (CGAL_Handle&) d )
{}

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const CGAL_PointH2<FT,RT> & p )
  : CGAL_Handle( (CGAL_Handle&) p)
{}

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const CGAL_VectorH2<FT,RT> & v )
  : CGAL_Handle( (CGAL_Handle&) v)
{}

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH2<FT,RT>::CGAL_DirectionH2(const RT& x, const RT& y)
{ PTR = new CGAL__Threetuple<RT>( x, y, RT(1) ); }

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
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
inline
CGAL_DirectionH2<FT,RT>::~CGAL_DirectionH2()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_DirectionH2<FT,RT> &
CGAL_DirectionH2<FT,RT>::operator=(const CGAL_DirectionH2<FT,RT> &d)
{
  CGAL_Handle::operator=(d);
  return *this;
}

template <class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_DirectionH2<FT,RT>::operator==( const CGAL_DirectionH2<FT,RT>& d) const
{
  return (  ( x() * d.y() == y() * d.x() )
          &&( CGAL_sign( x() ) == CGAL_sign( d.x() ) )
          &&( CGAL_sign( y() ) == CGAL_sign( d.y() ) ) );
}

template <class FT, class RT >
inline
bool
CGAL_DirectionH2<FT,RT>::operator!=( const CGAL_DirectionH2<FT,RT>& d) const
{ return !(*this == d); }

template <class FT, class RT >
inline
bool
CGAL_DirectionH2<FT,RT>::identical( const CGAL_DirectionH2<FT,RT>& d) const
{ return ( PTR == d.PTR ); }

template <class FT, class RT >
inline
int
CGAL_DirectionH2<FT,RT>::id() const
{ return (int)PTR; }
template <class FT, class RT >
inline
CGAL_DirectionH2<FT,RT>
CGAL_DirectionH2<FT,RT>::operator-() const
{ return CGAL_DirectionH2<FT,RT>( - x(), - y() ); }
template <class FT, class RT >
inline
RT
CGAL_DirectionH2<FT,RT>::dx() const
{ return ptr()->e0; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH2<FT,RT>::dy() const
{ return ptr()->e1; }

template <class FT, class RT >
CGAL_KERNEL_INLINE
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
inline
RT
CGAL_DirectionH2<FT,RT>::x() const
{ return ptr()->e0; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH2<FT,RT>::y() const
{ return ptr()->e1; }


template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH2<FT,RT>
operator+(const CGAL_VectorH2<FT,RT>& u, const CGAL_VectorH2<FT,RT>& v)
{
  return CGAL_VectorH2<FT,RT>( u.hx()*v.hw() + v.hx()*u.hw(),
                               u.hy()*v.hw() + v.hy()*u.hw(),
                               u.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_VectorH2<FT,RT>
CGAL_KERNEL_INLINE
operator-(const CGAL_VectorH2<FT,RT>& u, const CGAL_VectorH2<FT,RT>& v)
{
  return CGAL_VectorH2<FT,RT>( u.hx()*v.hw() - v.hx()*u.hw(),
                               u.hy()*v.hw() - v.hy()*u.hw(),
                               u.hw()*v.hw() );
}

template <class FT, class RT>
FT
CGAL_KERNEL_INLINE
operator*(const CGAL_VectorH2<FT,RT>& u, const CGAL_VectorH2<FT,RT>& v)
{
  return (   FT( RT(u.hx()*v.hx() + u.hy()*v.hy()) )  /
             FT( RT(u.hw()*v.hw() ) )    );
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH2<FT,RT>
operator/(const CGAL_VectorH2<FT,RT>& v, const RT& f)
{ return CGAL_VectorH2<FT,RT>( v.hx(), v.hy(), v.hw()*f ); }

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH2<FT,RT>
operator*(const CGAL_VectorH2<FT,RT>& v, const RT& f)
{ return CGAL_VectorH2<FT,RT>( v.hx()*f, v.hy()*f, v.hw() ); }

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH2<FT,RT>
operator*(const RT& f, const CGAL_VectorH2<FT,RT>& v)
{ return CGAL_VectorH2<FT,RT>( v.hx()*f, v.hy()*f, v.hw() ); }

template <class FT, class RT>
inline
CGAL_PointH2<FT,RT>
operator+(const CGAL_Origin&, const CGAL_VectorH2<FT,RT>& v)
{ return CGAL_PointH2<FT,RT>( v ); }

template <class FT, class RT>
inline
CGAL_PointH2<FT,RT>
operator-(const CGAL_Origin&, const CGAL_VectorH2<FT,RT>& v)
{ return CGAL_PointH2<FT,RT>( -v ); }

template <class FT, class RT>
inline
CGAL_VectorH2<FT,RT>
operator-(const CGAL_PointH2<FT,RT>& p, const CGAL_Origin&)
{ return CGAL_VectorH2<FT,RT>( p ); }

template <class FT, class RT>
inline
CGAL_VectorH2<FT,RT>
operator-(const CGAL_Origin&, const CGAL_PointH2<FT,RT>& p)
{ return  - CGAL_VectorH2<FT,RT>( p ); }


template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_PointH2<FT,RT>
operator+(const CGAL_PointH2<FT,RT>& p, const CGAL_VectorH2<FT,RT>& v)
{
  return CGAL_PointH2<FT,RT>( p.hx()*v.hw() + v.hx()*p.hw(),
                              p.hy()*v.hw() + v.hy()*p.hw(),
                              p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_PointH2<FT,RT>
operator-(const CGAL_PointH2<FT,RT>& p, const CGAL_VectorH2<FT,RT>& v)
{
  return CGAL_PointH2<FT,RT>( p.hx()*v.hw() - v.hx()*p.hw(),
                              p.hy()*v.hw() - v.hy()*p.hw(),
                              p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH2<FT,RT>
operator-(const CGAL_PointH2<FT,RT>& p, const CGAL_PointH2<FT,RT>& q)
{
  return CGAL_VectorH2<FT,RT>( p.hx()*q.hw() - q.hx()*p.hw(),
                               p.hy()*q.hw() - q.hy()*p.hw(),
                               p.hw()*q.hw() );
}


#ifndef CGAL_PREDICATES_ON_DIRECTIONSH2_H
#include <CGAL/predicates_on_directionsH2.h>
#endif // CGAL_PREDICATES_ON_DIRECTIONSH2_H
template <class FT, class RT >
inline
bool
CGAL_DirectionH2<FT,RT>::operator< (const CGAL_DirectionH2<FT,RT>& d) const
{ return (CGAL_compare_angles_with_x_axis(*this,d) == CGAL_SMALLER); }

template <class FT, class RT >
inline
bool
CGAL_DirectionH2<FT,RT>::operator> (const CGAL_DirectionH2<FT,RT>& d) const
{ return (CGAL_compare_angles_with_x_axis(*this,d) == CGAL_LARGER); }

template <class FT, class RT >
inline
bool
CGAL_DirectionH2<FT,RT>::operator>= (const CGAL_DirectionH2<FT,RT>& d) const
{ return !(CGAL_compare_angles_with_x_axis(*this,d) == CGAL_SMALLER); }

template <class FT, class RT >
inline
bool
CGAL_DirectionH2<FT,RT>::operator<= (const CGAL_DirectionH2<FT,RT>& d) const
{ return !(CGAL_compare_angles_with_x_axis(*this,d) == CGAL_LARGER); }

template <class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_DirectionH2<FT,RT>::
counterclockwise_in_between( const CGAL_DirectionH2<FT,RT>& d1,
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


#ifndef CGAL_AFF_TRANSFORMATIONH2_H
#include <CGAL/Aff_transformationH2.h>
#endif // CGAL_AFF_TRANSFORMATIONH2_H
#ifndef CGAL_BBOX_2_H
#include <CGAL/Bbox_2.h>
#endif // CGAL_BBOX_2_H
#ifndef CGAL_MISC_H
#include <CGAL/misc.h>
#endif // CGAL_MISC_H

template < class FT, class RT >
CGAL_KERNEL_MEDIUM_INLINE
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
  if ( hx() < RT(0)   ) { CGAL_swap(xmin, xmax); }
  if ( hy() < RT(0)   ) { CGAL_swap(ymin, ymax); }
  return CGAL_Bbox_2(xmin, ymin, xmax, ymax);
}

template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_PointH2<FT,RT>::transform(const CGAL_Aff_transformationH2<FT,RT>& t) const
{ return t.transform(*this); }


#ifndef CGAL_NO_OSTREAM_INSERT_POINTH2
template < class FT, class RT >
ostream &
operator<<(ostream &os, const CGAL_PointH2<FT,RT> &p)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << p.hx() << ' ' << p.hy() << ' ' << p.hw();
    case CGAL_IO::BINARY :
        CGAL_write(os, p.hx());
        CGAL_write(os, p.hy());
        CGAL_write(os, p.hw());
        return os;
    default:
        return os << "PointH2(" << p.hx() << ", "
                                << p.hy() << ", "
                                << p.hw() << ')';
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_POINTH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINTH2
template < class FT, class RT >
istream &
operator>>(istream &is, CGAL_PointH2<FT,RT> &p)
{
  RT hx, hy, hw;
  switch(is.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        is >> hx >> hy >> hw;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, hx);
        CGAL_read(is, hy);
        CGAL_read(is, hw);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
  }
  p = CGAL_PointH2<FT,RT>(hx, hy, hw);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINTH2

template < class FT, class RT >
CGAL_KERNEL_INLINE
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
inline
CGAL_VectorH2<FT,RT>
CGAL_VectorH2<FT,RT>::transform(const CGAL_Aff_transformationH2<FT,RT>& t) const
{ return t.transform(*this); }


#ifndef CGAL_NO_OSTREAM_INSERT_VECTORH2
template < class FT, class RT >
ostream &
operator<<(ostream &os, const CGAL_VectorH2<FT,RT> &p)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << p.hx() << ' ' << p.hy() << ' ' << p.hw();
    case CGAL_IO::BINARY :
        CGAL_write(os, p.hx());
        CGAL_write(os, p.hy());
        CGAL_write(os, p.hw());
        return os;
    default:
        return os << "VectorH2(" << p.hx() << ", "
                                << p.hy() << ", "
                                << p.hw() << ')';
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTORH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTORH2
template < class FT, class RT >
istream &
operator>>(istream &is, CGAL_VectorH2<FT,RT> &p)
{
  RT hx, hy, hw;
  switch(is.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        is >> hx >> hy >> hw;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, hx);
        CGAL_read(is, hy);
        CGAL_read(is, hw);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
  }
  p = CGAL_VectorH2<FT,RT>(hx, hy, hw);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTORH2

template <class FT, class RT >
CGAL_KERNEL_INLINE
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
inline
CGAL_DirectionH2<FT,RT>
CGAL_DirectionH2<FT,RT>::
transform(const CGAL_Aff_transformationH2<FT,RT>& t) const
{ return t.transform(*this); }

template <class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_VectorH2<FT,RT>
CGAL_DirectionH2<FT,RT>::vector() const
{ return CGAL_VectorH2<FT,RT>( x(), y() ); }


#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTIONH2
template < class FT, class RT >
ostream &
operator<<(ostream &os, const CGAL_DirectionH2<FT,RT> &p)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << p.dx() << ' ' << p.dy();
    case CGAL_IO::BINARY :
        CGAL_write(os, p.dx());
        CGAL_write(os, p.dy());
        return os;
    default:
        return os << "DirectionH2(" << p.dx() << ", "
                                    << p.dy() << ')';
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTIONH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTIONH2
template < class FT, class RT >
istream &
operator>>(istream &is, CGAL_DirectionH2<FT,RT> &p)
{
  RT x, y;
  switch(is.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        is >> x >> y;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, x);
        CGAL_read(is, y);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
  }
  p = CGAL_DirectionH2<FT,RT>(x, y);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTIONH2



#endif // CGAL_PVDH2
