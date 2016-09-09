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
// source        : PointVectorDirectionH3.fw
// file          : include/CGAL/PVDH3.h
// package       : H3 (1.3.1)
// revision      : 1.3.1
// revision_date : 30 Jun 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_PVDH3_H
#define CGAL_PVDH3_H
#define CGAL_POINTH3_H
#define CGAL_VECTORH3_H
#define CGAL_DIRECTIONH3_H

#ifndef CGAL_HOMOGENEOUS_CLASSES_H
#include <CGAL/homogeneous_classes.h>
#endif // CGAL_HOMOGENEOUS_CLASSES_H
#ifndef CGAL_ORIGIN_H
#include <CGAL/Origin.h>
#endif // CGAL_ORIGIN_H

#ifndef CGAL_REPH3_H
#include <CGAL/RepH3.h>
#endif // CGAL_REPH3_H

template <class FT, class RT>
CGAL_PointH3<FT,RT>
operator+  (const CGAL_Origin &, const CGAL_VectorH3<FT,RT> & v);

template <class FT, class RT>
CGAL_PointH3<FT,RT>
operator-  (const CGAL_Origin &, const CGAL_VectorH3<FT,RT> & v);

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator-   ( const CGAL_PointH3<FT,RT> &, const CGAL_Origin & );

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator-   ( const CGAL_Origin &, const CGAL_PointH3<FT,RT> & );

template <class FT, class RT>
CGAL_PointH3<FT,RT>
operator+   ( const CGAL_Origin &, const CGAL_VectorH3<FT,RT> & );

template <class FT, class RT>
CGAL_PointH3<FT,RT>
operator-   ( const CGAL_Origin &, const CGAL_VectorH3<FT,RT> & );

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator+   ( const CGAL_VectorH3<FT,RT> &, const CGAL_VectorH3<FT,RT> & );

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator-   ( const CGAL_VectorH3<FT,RT> &, const CGAL_VectorH3<FT,RT> & );

template <class FT, class RT>
FT
operator*   ( const CGAL_VectorH3<FT,RT> &, const CGAL_VectorH3<FT,RT> & );

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator*   ( const CGAL_VectorH3<FT,RT> &, const RT & );

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator*   ( const RT &, const CGAL_VectorH3<FT,RT> & );

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator/   ( const CGAL_VectorH3<FT,RT> &, const RT & );

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
CGAL_cross_product   (const CGAL_VectorH3<FT,RT>& a,
                      const CGAL_VectorH3<FT,RT>& b);



template < class FT, class RT >
class CGAL_PointH3 : public CGAL_Handle
{

public:
  CGAL_PointH3();
  CGAL_PointH3(const CGAL_PointH3<FT,RT> & tbc);
  CGAL_PointH3(const CGAL_Origin &);
  CGAL_PointH3(const CGAL_VectorH3<FT,RT>& v);
  CGAL_PointH3(const RT& x, const RT& y, const RT& z);
  CGAL_PointH3(const RT& x, const RT& y, const RT& z, const RT& w);
  ~CGAL_PointH3();

  CGAL_PointH3<FT,RT>&      operator=( const CGAL_PointH3<FT,RT> & p);

  FT    x()  const;
  FT    y()  const;
  FT    z()  const;
  RT    hx() const;
  RT    hy() const;
  RT    hz() const;
  RT    hw() const;
  FT    cartesian(int i) const;
  RT    homogeneous(int i) const;
  FT    operator[](int i) const;

  int   dimension() const;

  CGAL_DirectionH3<FT,RT>
        direction() const;
  CGAL_PointH3<FT,RT>
        transform( const CGAL_Aff_transformationH3<FT,RT> & t) const;
  CGAL_Bbox_3
        bbox() const;

  bool  operator==( const CGAL_PointH3<FT,RT>& p) const;
  bool  operator!=( const CGAL_PointH3<FT,RT>& p) const;
  bool  identical(  const CGAL_PointH3<FT,RT>& p) const;

friend CGAL_PointH3<FT,RT>
       operator+  CGAL_NULL_TMPL_ARGS (const CGAL_Origin &,
                                       const CGAL_VectorH3<FT,RT> & v);
friend CGAL_PointH3<FT,RT>
       operator-  CGAL_NULL_TMPL_ARGS (const CGAL_Origin &,
                                       const CGAL_VectorH3<FT,RT> & v);
protected:
  CGAL__RepH3<RT>*         ptr() const;
};


template < class FT, class RT >
class CGAL_VectorH3 : public CGAL_Handle
{
public:
  CGAL_VectorH3();
  CGAL_VectorH3(const CGAL_VectorH3<FT,RT> & tbc);
  CGAL_VectorH3(const CGAL_Null_vector&);
  CGAL_VectorH3(const RT& x, const RT& y, const RT& z);
  CGAL_VectorH3(const RT& w, const RT& x, const RT& y, const RT& z);
  ~CGAL_VectorH3();

  CGAL_VectorH3<FT,RT>&
        operator=( const CGAL_VectorH3<FT,RT>& v);

  FT    x()  const;
  FT    y()  const;
  FT    z()  const;
  RT    hx() const;
  RT    hy() const;
  RT    hz() const;
  RT    hw() const;
  FT    cartesian(int i) const;
  RT    homogeneous(int i) const;
  FT    operator[](int i) const;

  int   dimension() const;

  CGAL_DirectionH3<FT,RT>
        direction() const;
  CGAL_VectorH3<FT,RT>
        transform(const CGAL_Aff_transformationH3<FT,RT>& t ) const;

  CGAL_VectorH3<FT,RT>
        operator-() const;

  bool  operator==( const CGAL_VectorH3<FT,RT>& v) const;
  bool  operator!=( const CGAL_VectorH3<FT,RT>& v) const;
  bool  identical ( const CGAL_VectorH3<FT,RT>& v) const;

// undocumented:

  CGAL_VectorH3(const CGAL_PointH3<FT,RT> & p);
  CGAL_VectorH3(const CGAL_DirectionH3<FT,RT> & dir);   /* XXX */

// friends:

friend CGAL_VectorH3<FT,RT>
       operator-  CGAL_NULL_TMPL_ARGS ( const CGAL_PointH3<FT,RT> &,
                                        const CGAL_Origin & );
friend CGAL_VectorH3<FT,RT>
       operator-  CGAL_NULL_TMPL_ARGS ( const CGAL_Origin &,
                                        const CGAL_PointH3<FT,RT> & );
friend CGAL_PointH3<FT,RT>
       operator+  CGAL_NULL_TMPL_ARGS ( const CGAL_Origin &,
                                        const CGAL_VectorH3<FT,RT> & );
friend CGAL_PointH3<FT,RT>
       operator-  CGAL_NULL_TMPL_ARGS ( const CGAL_Origin &,
                                        const CGAL_VectorH3<FT,RT> & );
friend CGAL_VectorH3<FT,RT>
       operator+  CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH3<FT,RT> &,
                                        const CGAL_VectorH3<FT,RT> & );
friend CGAL_VectorH3<FT,RT>
       operator-  CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH3<FT,RT> &,
                                        const CGAL_VectorH3<FT,RT> & );
friend FT
       operator*  CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH3<FT,RT> &,
                                        const CGAL_VectorH3<FT,RT> & );
friend CGAL_VectorH3<FT,RT>
       operator*  CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH3<FT,RT> &,
                                        const RT & );
friend CGAL_VectorH3<FT,RT>
       operator*  CGAL_NULL_TMPL_ARGS ( const RT &,
                                        const CGAL_VectorH3<FT,RT> & );
friend CGAL_VectorH3<FT,RT>
       operator/  CGAL_NULL_TMPL_ARGS ( const CGAL_VectorH3<FT,RT> &,
                                        const RT & );
friend CGAL_VectorH3<FT,RT>
       CGAL_cross_product  CGAL_NULL_TMPL_ARGS (const CGAL_VectorH3<FT,RT>& a,
                                                const CGAL_VectorH3<FT,RT>& b);

protected:
  CGAL__RepH3<RT>*    ptr() const;
};


template < class FT, class RT >
class CGAL_DirectionH3 : public CGAL_Handle
{
public:
  CGAL_DirectionH3();
  CGAL_DirectionH3(const CGAL_DirectionH3<FT,RT>& tbc );
  CGAL_DirectionH3(const CGAL_PointH3<FT,RT> & p );
  CGAL_DirectionH3(const CGAL_VectorH3<FT,RT> & v );
  CGAL_DirectionH3(const RT& x, const RT& y,
                   const RT& z, const RT& w = RT(1) );
  ~CGAL_DirectionH3();

  CGAL_DirectionH3<FT,RT>&
               operator=(const CGAL_DirectionH3<FT,RT>& d);

  CGAL_DirectionH3<FT,RT>
        transform(const CGAL_Aff_transformationH3<FT,RT> &) const ;
  CGAL_DirectionH3<FT,RT>
        operator-() const;

  bool  is_degenerate() const;

  bool  operator==( const CGAL_DirectionH3<FT,RT>& d) const;
  bool  operator!=( const CGAL_DirectionH3<FT,RT>& d) const;
  bool  identical ( const CGAL_DirectionH3<FT,RT>& d) const;

  CGAL_VectorH3<FT,RT>    vector() const;

  RT    dx() const;
  RT    dy() const;
  RT    dz() const;
  RT    x()  const;
  RT    y()  const;
  RT    z()  const;
  RT    hx() const;
  RT    hy() const;
  RT    hz() const;

  RT    delta(int i) const;

friend
CGAL_DirectionH3<FT,RT>
CGAL_cross_product CGAL_NULL_TMPL_ARGS (const CGAL_DirectionH3<FT,RT>& d1,
                                        const CGAL_DirectionH3<FT,RT>& d2);

protected:
  CGAL__RepH3<RT>*    ptr()    const;
};




template < class FT, class RT >
inline
CGAL__RepH3<RT>*
CGAL_PointH3<FT,RT>::ptr() const
{ return (CGAL__RepH3<RT>*) PTR; }



template < class FT, class RT >
inline
CGAL__RepH3<RT>*
CGAL_VectorH3<FT,RT>::ptr() const
{ return (CGAL__RepH3<RT>*)PTR; }

template <class FT, class RT >
inline
CGAL__RepH3<RT>*
CGAL_DirectionH3<FT,RT>::ptr() const
{ return (CGAL__RepH3<RT>*) PTR; }


template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH3<FT,RT>::CGAL_PointH3()
{ PTR = new CGAL__RepH3<RT>(); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH3<FT,RT>::CGAL_PointH3(const CGAL_Origin&)
{
 const RT RT0(0);
 const RT RT1(1);
 PTR = new CGAL__RepH3<RT>( RT0, RT0, RT0, RT1 );
}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH3<FT,RT>::CGAL_PointH3(const CGAL_PointH3<FT,RT>& tbc)
  : CGAL_Handle(tbc)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH3<FT,RT>::CGAL_PointH3(const CGAL_VectorH3<FT,RT>& v)
  : CGAL_Handle(v)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH3<FT,RT>::CGAL_PointH3(const RT& x, const RT& y, const RT& z)
{ PTR = new CGAL__RepH3<RT>(x,y,z, RT(1)); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_PointH3<FT,RT>::CGAL_PointH3(const RT& x, const RT& y,
                                  const RT& z, const RT& w)
{
  if ( w < RT(0) )
  {
      PTR = new CGAL__RepH3<RT>(-x,-y,-z,-w);
  }
  else
  {
      PTR = new CGAL__RepH3<RT>(x,y,z,w);
  }
}

template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>::~CGAL_PointH3()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_PointH3<FT,RT>&
CGAL_PointH3<FT,RT>::operator=(const CGAL_PointH3<FT,RT>& p)
{
  CGAL_Handle::operator=(p);
  return *this;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_PointH3<FT,RT>::x()  const
{ return ( FT(ptr()->hx() ) / FT(ptr()->hw() )); }


template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_PointH3<FT,RT>::y()  const
{ return ( FT(ptr()->hy() ) / FT(ptr()->hw() )); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_PointH3<FT,RT>::z()  const
{ return ( FT(ptr()->hz() ) / FT(ptr()->hw() )); }

template < class FT, class RT >
inline
RT
CGAL_PointH3<FT,RT>::hx() const
{ return  ptr()->hx() ; }

template < class FT, class RT >
inline
RT
CGAL_PointH3<FT,RT>::hy() const
{ return  ptr()->hy() ; }

template < class FT, class RT >
inline
RT
CGAL_PointH3<FT,RT>::hz() const
{ return  ptr()->hz() ; }

template < class FT, class RT >
inline
RT
CGAL_PointH3<FT,RT>::hw() const
{ return  ptr()->hw(); }

template < class FT, class RT >
inline
int
CGAL_PointH3<FT,RT>::dimension() const
{ return 3; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_PointH3<FT,RT>::cartesian(int i) const
{
  switch (i)
  {
      case 0:  return x();
      case 1:  return y();
      case 2:  return z();
      default: return cartesian( i%3 );
  }
  // return FT( RT() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
RT
CGAL_PointH3<FT,RT>::homogeneous(int i) const
{
  CGAL_kernel_precondition(i == 0 || i == 1 || i == 2 || i == 3);
  switch (i)
  {
     case 0:   return hx();
     case 1:   return hy();
     case 2:   return hz();
  }
  return hw();
}

template < class FT, class RT >
inline
FT
CGAL_PointH3<FT,RT>::operator[](int i) const
{ return cartesian(i); }


template < class FT, class RT >
inline
CGAL_DirectionH3<FT,RT>
CGAL_PointH3<FT,RT>::direction() const
{ return CGAL_DirectionH3<FT,RT>(*this); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_PointH3<FT,RT>::operator==( const CGAL_PointH3<FT,RT> & p) const
{
  return ( (hx() * p.hw() == p.hx() * hw() )
         &&(hy() * p.hw() == p.hy() * hw() )
         &&(hz() * p.hw() == p.hz() * hw() ) );
}

template < class FT, class RT >
inline
bool
CGAL_PointH3<FT,RT>::operator!=( const CGAL_PointH3<FT,RT> & p) const
{ return !(*this == p); }

template < class FT, class RT >
inline
bool
CGAL_PointH3<FT,RT>::identical( const CGAL_PointH3<FT,RT>& p) const
{ return (PTR == p.PTR); }


#ifndef CGAL_NO_OSTREAM_INSERT_POINTH3
template < class FT, class RT >
ostream &operator<<(ostream &os, const CGAL_PointH3<FT,RT> &p)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << p.hx() << ' ' << p.hy() << ' ' << p.hz() << ' ' << p.hw();
    case CGAL_IO::BINARY :
        CGAL_write(os, p.hx());
        CGAL_write(os, p.hy());
        CGAL_write(os, p.hz());
        CGAL_write(os, p.hw());
        return os;
    default:
        return os << "PointH3(" << p.hx() << ", "
                                << p.hy() << ", "
                                << p.hz() << ", "
                                << p.hw() << ')';
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_POINTH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_POINTH3
template < class FT, class RT >
istream &operator>>(istream &is, CGAL_PointH3<FT,RT> &p)
{
  RT hx, hy, hz, hw;
  switch(is.iword(CGAL_IO::mode)) {
  case CGAL_IO::ASCII :
        is >> hx >> hy >> hz >> hw;
        break;
  case CGAL_IO::BINARY :
        CGAL_read(is, hx);
        CGAL_read(is, hy);
        CGAL_read(is, hz);
        CGAL_read(is, hw);
        break;
  default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
  }
  p = CGAL_PointH3<FT,RT>(hx, hy, hz, hw);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_POINTH3

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH3<FT,RT>::CGAL_VectorH3()
{ PTR = new CGAL__RepH3<RT>();
  // cout << "default ctor CGAL_VectorH3 allocates CGAL__RepH3"
  //      << (int)PTR << endl << flush;
}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const CGAL_VectorH3<FT,RT>& tbc)
  : CGAL_Handle((CGAL_Handle&) tbc)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const CGAL_Null_vector&)
{ PTR = new CGAL__RepH3<RT>( RT(0), RT(0), RT(0), RT(1) ); }


template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const CGAL_PointH3<FT,RT> & p)
  : CGAL_Handle( (CGAL_Handle&) p )
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const CGAL_DirectionH3<FT,RT> & d)
  : CGAL_Handle( (CGAL_Handle&) d )
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const RT& x, const RT& y,
                                    const RT& z, const RT& w)
{
  if ( w >= RT(0) )
  {
      PTR = new CGAL__RepH3<RT>(x, y, z, w);
  }
  else
  {
      PTR = new CGAL__RepH3<RT>(-x,-y,-z,-w);
  }
}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const RT& x, const RT& y, const RT& z)
{ PTR = new CGAL__RepH3<RT>(x, y, z, RT(1) ); }

template < class FT, class RT >
inline
CGAL_VectorH3<FT,RT>::~CGAL_VectorH3()
{}

template < class FT, class RT >
inline
CGAL_VectorH3<FT,RT> &
CGAL_VectorH3<FT,RT>::operator=(const CGAL_VectorH3<FT,RT>& v)
{
  CGAL_Handle::operator=(v);
  return *this;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_VectorH3<FT,RT>::x()  const
{ return FT(ptr()->hx() )/FT(ptr()->hw() ) ; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_VectorH3<FT,RT>::y()  const
{ return FT(ptr()->hy() )/FT(ptr()->hw() ) ; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_VectorH3<FT,RT>::z()  const
{ return FT(ptr()->hz() )/FT(ptr()->hw() ) ; }

template < class FT, class RT >
inline
RT
CGAL_VectorH3<FT,RT>::hx() const
{ return  ptr()->hx() ; }

template < class FT, class RT >
inline
RT
CGAL_VectorH3<FT,RT>::hy() const
{ return  ptr()->hy() ; }

template < class FT, class RT >
inline
RT
CGAL_VectorH3<FT,RT>::hz() const
{ return  ptr()->hz() ; }

template < class FT, class RT >
inline
RT
CGAL_VectorH3<FT,RT>::hw() const
{ return  ptr()->hw() ; }

template < class FT, class RT >
inline
int
CGAL_VectorH3<FT,RT>::dimension() const
{ return 3; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
FT
CGAL_VectorH3<FT,RT>::cartesian(int i) const
{
  switch (i)
  {
      case 0:   return x();
      case 1:   return y();
      case 2:   return z();
      default:  cartesian( i%3 );
  }
  // return FT( RT() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
RT
CGAL_VectorH3<FT,RT>::homogeneous(int i) const
{
  CGAL_kernel_precondition(i == 0 || i == 1 || i == 2 || i == 3);
  switch (i)
  {
      case 0:   return hx();
      case 1:   return hy();
      case 2:   return hz();
  }
  return hw() ;
}
template < class FT, class RT >
inline
CGAL_DirectionH3<FT,RT>
CGAL_VectorH3<FT,RT>::direction() const
{ return CGAL_DirectionH3<FT,RT>(*this); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_VectorH3<FT,RT>::operator==( const CGAL_VectorH3<FT,RT>& v) const
{
 return ( (hx() * v.hw() == v.hx() * hw() )
        &&(hy() * v.hw() == v.hy() * hw() )
        &&(hz() * v.hw() == v.hz() * hw() ) );
}

template < class FT, class RT >
inline
bool
CGAL_VectorH3<FT,RT>::operator!=( const CGAL_VectorH3<FT,RT>& v) const
{ return !(*this == v); }

template < class FT, class RT >
inline
bool
CGAL_VectorH3<FT,RT>::identical( const CGAL_VectorH3<FT,RT>& v) const
{ return ( PTR == v.PTR ); }

template < class FT, class RT >
inline
FT
CGAL_VectorH3<FT,RT>::operator[](int i) const
{ return cartesian(i); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
CGAL_VectorH3<FT,RT>
CGAL_VectorH3<FT,RT>::operator-() const
{ return CGAL_VectorH3<FT,RT>( - hx(), - hy(), -hz(), hw() ); }


template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3()
{ PTR = new CGAL__RepH3<RT>(); }

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3(const CGAL_DirectionH3<FT,RT>& tbc )
 : CGAL_Handle(tbc)
{}

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3(const CGAL_PointH3<FT,RT> & p )
 : CGAL_Handle( (CGAL_Handle&) p )
{}

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3(const CGAL_VectorH3<FT,RT> & v )
 : CGAL_Handle( (CGAL_Handle&) v )
{}

template <class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3(const RT& x, const RT& y,
                                          const RT& z, const RT& w)
{
  if ( w >= RT(0) )
  {
     PTR = new CGAL__RepH3<RT>(x,y,z,w);
  }
  else
  {
     PTR = new CGAL__RepH3<RT>(-x,-y,-z,-w);
  }
}

template <class FT, class RT >
inline
CGAL_DirectionH3<FT,RT>::~CGAL_DirectionH3()
{}

template < class FT, class RT >
inline
CGAL_DirectionH3<FT,RT> &
CGAL_DirectionH3<FT,RT>::operator=(const CGAL_DirectionH3<FT,RT> &d)
{
  CGAL_Handle::operator=(d);
  return *this;
}

template <class FT, class RT >
CGAL_KERNEL_INLINE
RT
CGAL_DirectionH3<FT,RT>::delta(int i) const
{
  switch (i)
  {
      case 0:  return x();
      case 1:  return y();
      case 2:  return z();
      default: return delta( i%3 );
  }
  // return  RT() ;
}

template <class FT, class RT >
inline
RT
CGAL_DirectionH3<FT,RT>::dx() const
{ return ptr()->e0; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH3<FT,RT>::x() const
{ return ptr()->e0; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH3<FT,RT>::hx() const
{ return ptr()->e0; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH3<FT,RT>::dy() const
{ return ptr()->e1; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH3<FT,RT>::y() const
{ return ptr()->e1; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH3<FT,RT>::hy() const
{ return ptr()->e1; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH3<FT,RT>::dz() const
{ return ptr()->e2; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH3<FT,RT>::z() const
{ return ptr()->e2; }

template <class FT, class RT >
inline
RT
CGAL_DirectionH3<FT,RT>::hz() const
{ return ptr()->e2; }
template <class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_DirectionH3<FT,RT>::operator==( const CGAL_DirectionH3<FT,RT>& d) const
{
  return ( ( ptr()->hx()*d.ptr()->hy() == ptr()->hy()*d.ptr()->hx() )
         &&( ptr()->hx()*d.ptr()->hz() == ptr()->hz()*d.ptr()->hx() )
         &&( ptr()->hy()*d.ptr()->hz() == ptr()->hz()*d.ptr()->hy() )
         &&( CGAL_sign( ptr()->hx() ) == CGAL_sign( d.ptr()->hx() ) )
         &&( CGAL_sign( ptr()->hy() ) == CGAL_sign( d.ptr()->hy() ) )
         &&( CGAL_sign( ptr()->hz() ) == CGAL_sign( d.ptr()->hz() ) ) );
}

template <class FT, class RT >
inline
bool
CGAL_DirectionH3<FT,RT>::operator!=( const CGAL_DirectionH3<FT,RT>& d) const
{ return !operator==(d); }

template <class FT, class RT >
CGAL_KERNEL_INLINE
bool
CGAL_DirectionH3<FT,RT>::is_degenerate() const
{ return ((hx() == RT(0)) && (hy() == RT(0)) && (hz() == RT(0))); }

template <class FT, class RT >
inline
bool
CGAL_DirectionH3<FT,RT>::identical( const CGAL_DirectionH3<FT,RT>& d) const
{ return ( PTR == d.PTR ); }

template <class FT, class RT >
inline
CGAL_DirectionH3<FT,RT>
CGAL_DirectionH3<FT,RT>::operator-() const
{ return CGAL_DirectionH3<FT,RT>(- ptr()->hx(),- ptr()->hy(),- ptr()->hz() ); }


template <class FT, class RT >
inline
CGAL_VectorH3<FT,RT>
CGAL_DirectionH3<FT,RT>::vector() const
{ return CGAL_VectorH3<FT,RT>(*this); }


template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH3<FT,RT>
operator+(const CGAL_VectorH3<FT,RT>& u, const CGAL_VectorH3<FT,RT>& v)
{
  return CGAL_VectorH3<FT,RT>(u.hx()*v.hw() + v.hx()*u.hw(),
                              u.hy()*v.hw() + v.hy()*u.hw(),
                              u.hz()*v.hw() + v.hz()*u.hw(),
                              u.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH3<FT,RT>
operator-(const CGAL_VectorH3<FT,RT>& u, const CGAL_VectorH3<FT,RT>& v)
{
  return CGAL_VectorH3<FT,RT>(u.hx()*v.hw() - v.hx()*u.hw(),
                              u.hy()*v.hw() - v.hy()*u.hw(),
                              u.hz()*v.hw() - v.hz()*u.hw(),
                              u.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
FT
operator*(const CGAL_VectorH3<FT,RT>& u, const CGAL_VectorH3<FT,RT>& v)
{
  CGAL_kernel_assertion( u.hw() != RT(0) );
  CGAL_kernel_assertion( v.hw() != RT(0) );
  return ( FT( u.hx()*v.hx() + u.hy()*v.hy() + u.hz()*v.hz() ) /
           FT( u.hw()*v.hw() ) );
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH3<FT,RT>
operator/(const CGAL_VectorH3<FT,RT>& v, const RT& f)
{ return CGAL_VectorH3<FT,RT>( v.hx(), v.hy(), v.hz(), v.hw()*f ); }

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH3<FT,RT>
operator*(const CGAL_VectorH3<FT,RT>& v, const RT& f)
{ return CGAL_VectorH3<FT,RT>( v.hx()*f, v.hy()*f, v.hz()*f, v.hw() ); }

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH3<FT,RT>
operator*(const RT& f, const CGAL_VectorH3<FT,RT>& v)
{ return CGAL_VectorH3<FT,RT>( v.hx()*f, v.hy()*f, v.hz()*f, v.hw() ); }

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH3<FT,RT>
CGAL_cross_product(const CGAL_VectorH3<FT,RT>& a, const CGAL_VectorH3<FT,RT>& b)
{
 return CGAL_VectorH3<FT,RT>(a.hy()*b.hz() - a.hz()*b.hy(),
                             a.hz()*b.hx() - a.hx()*b.hz(),
                             a.hx()*b.hy() - a.hy()*b.hx(),
                             a.hw()*b.hw() );
}

template <class FT, class RT>
inline
CGAL_PointH3<FT,RT>
operator+(const CGAL_Origin& , const CGAL_VectorH3<FT,RT>& v)
{ return CGAL_PointH3<FT,RT>( v ); }

template <class FT, class RT>
inline
CGAL_VectorH3<FT,RT>
operator-(const CGAL_PointH3<FT,RT>& p, const CGAL_Origin& )
{ return CGAL_VectorH3<FT,RT>( p ); }

template <class FT, class RT>
inline
CGAL_VectorH3<FT,RT>
operator-(const CGAL_Origin& , const CGAL_PointH3<FT,RT>& p)
{ return  - CGAL_VectorH3<FT,RT>( p ); }


template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_PointH3<FT,RT>
operator+(const CGAL_PointH3<FT,RT>& p, const CGAL_VectorH3<FT,RT>& v)
{
  return CGAL_PointH3<FT,RT>(p.hx()*v.hw() + v.hx()*p.hw(),
                             p.hy()*v.hw() + v.hy()*p.hw(),
                             p.hz()*v.hw() + v.hz()*p.hw(),
                             p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_PointH3<FT,RT>
operator-(const CGAL_PointH3<FT,RT>& p, const CGAL_VectorH3<FT,RT>& v)
{
  return CGAL_PointH3<FT,RT>( p.hx()*v.hw() - v.hx()*p.hw(),
                              p.hy()*v.hw() - v.hy()*p.hw(),
                              p.hz()*v.hw() - v.hz()*p.hw(),
                              p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_KERNEL_INLINE
CGAL_VectorH3<FT,RT>
operator-(const CGAL_PointH3<FT,RT>& p, const CGAL_PointH3<FT,RT>& q)
{
  return CGAL_PointH3<FT,RT>( p.hx()*q.hw() - q.hx()*p.hw(),
                              p.hy()*q.hw() - q.hy()*p.hw(),
                              p.hz()*q.hw() - q.hz()*p.hw(),
                              p.hw()*q.hw() );
}



template <class FT, class RT>
CGAL_DirectionH3<FT,RT>
CGAL_cross_product( const CGAL_DirectionH3<FT,RT>& d1,
                    const CGAL_DirectionH3<FT,RT>& d2)
{ return CGAL_cross_product(d1.vector(),d2.vector()).direction(); }


#ifndef CGAL_AFF_TRANSFORMATIONH3_H
#include <CGAL/Aff_transformationH3.h>
#endif // CGAL_AFF_TRANSFORMATIONH3_H

#ifndef CGAL_BBOX_3_H
#include <CGAL/Bbox_3.h>
#endif // CGAL_BBOX_3_H
#ifndef CGAL_MISC_H
#include <CGAL/misc.h>
#endif // CGAL_MISC_H


template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_PointH3<FT,RT>::transform(const CGAL_Aff_transformationH3<FT,RT>& t) const
{ return t.transform(*this); }

template < class FT, class RT >
CGAL_KERNEL_LARGE_INLINE
CGAL_Bbox_3
CGAL_PointH3<FT,RT>::bbox() const
{
  // double bx = CGAL_to_double(x());
  // double by = CGAL_to_double(y());
  // double bz = CGAL_to_double(z());
  // return CGAL_Bbox_3(bx, by, bz, bx, by, bz);

  double eps  = double(1.0) /(double(1<<26) * double(1<<26));
  double hxd  = CGAL_to_double( hx() );
  double hyd  = CGAL_to_double( hy() );
  double hzd  = CGAL_to_double( hz() );
  double hwd  = CGAL_to_double( hw() );
  double xmin = ( hxd - eps*hxd ) / ( hwd + eps*hwd );
  double xmax = ( hxd + eps*hxd ) / ( hwd - eps*hwd );
  double ymin = ( hyd - eps*hyd ) / ( hwd + eps*hwd );
  double ymax = ( hyd + eps*hyd ) / ( hwd - eps*hwd );
  double zmin = ( hzd - eps*hzd ) / ( hwd + eps*hwd );
  double zmax = ( hzd + eps*hzd ) / ( hwd - eps*hwd );
  if ( hx() < RT(0)   )
  {
      CGAL_swap(xmin, xmax);
  }
  if ( hy() < RT(0)   )
  {
      CGAL_swap(ymin, ymax);
  }
  if ( hz() < RT(0)   )
  {
      CGAL_swap(zmin, zmax);
  }
  return CGAL_Bbox_3(xmin, ymin, zmin, xmax, ymax, zmax);
}

template < class FT, class RT >
inline
CGAL_VectorH3<FT,RT>
CGAL_VectorH3<FT,RT>::transform(const CGAL_Aff_transformationH3<FT,RT>&t ) const
{ return t.transform(*this); }


#ifndef CGAL_NO_OSTREAM_INSERT_VECTORH3
template < class FT, class RT >
ostream& operator<<(ostream& os, const CGAL_VectorH3<FT,RT>& v)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << v.hx() << ' ' << v.hy() << ' ' << v.hz() << ' ' << v.hw();
    case CGAL_IO::BINARY :
        CGAL_write(os, v.hx());
        CGAL_write(os, v.hy());
        CGAL_write(os, v.hz());
        CGAL_write(os, v.hw());
        return os;
    default:
        return os << "VectorH3(" << v.hx() << ", "
                                 << v.hy() << ", "
                                 << v.hz() << ", "
                                 << v.hw() << ')';
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_VECTORH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_VECTORH3
template < class FT, class RT >
istream& operator>>(istream& is, CGAL_VectorH3<FT,RT>& v)
{
  RT hx, hy, hz, hw;
  switch(is.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        is >> hx >> hy >> hz >> hw;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, hx);
        CGAL_read(is, hy);
        CGAL_read(is, hz);
        CGAL_read(is, hw);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
  }
  v = CGAL_VectorH3<FT,RT>(hx, hy, hz, hw);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_VECTORH3

template <class FT, class RT >
inline
CGAL_DirectionH3<FT,RT>
CGAL_DirectionH3<FT,RT>::
transform(const CGAL_Aff_transformationH3<FT,RT>& t) const
{ return t.transform(*this); }


#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTIONH3
template < class FT, class RT >
ostream &operator<<(ostream &os, const CGAL_DirectionH3<FT,RT> &p)
{
  switch(os.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        return os << p.dx() << ' ' << p.dy() << ' ' << p.dz();
    case CGAL_IO::BINARY :
        CGAL_write(os, p.dx());
        CGAL_write(os, p.dy());
        CGAL_write(os, p.dz());
        return os;
    default:
        return os << "DirectionH3(" << p.dx() << ", "
                                    << p.dy() << ", "
                                    << p.dz() << ')';
  }
}
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTIONH3

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTIONH3
template < class FT, class RT >
istream &operator>>(istream &is, CGAL_DirectionH3<FT,RT> &p)
{
  RT x, y, z;
  switch(is.iword(CGAL_IO::mode))
  {
    case CGAL_IO::ASCII :
        is >> x >> y >> z;
        break;
    case CGAL_IO::BINARY :
        CGAL_read(is, x);
        CGAL_read(is, y);
        CGAL_read(is, z);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
  }
  p = CGAL_DirectionH3<FT,RT>(x, y, z);
  return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTIONH3


/*
template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator/(const CGAL_VectorH3<FT,RT>& v, const RT& f);
*/

#endif // CGAL_PVDH3_H
