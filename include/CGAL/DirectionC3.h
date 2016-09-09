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
// file          : include/CGAL/DirectionC3.h
// author(s)     : Andreas Fabri
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_DIRECTIONC3_H
#define CGAL_DIRECTIONC3_H

#include <CGAL/Threetuple.h>
#include <CGAL/VectorC3.h>

template < class FT >
class CGAL_DirectionC3 : public CGAL_Handle
{
public:
                      CGAL_DirectionC3();
                      CGAL_DirectionC3(const CGAL_DirectionC3<FT> &d);
                      CGAL_DirectionC3(const CGAL_VectorC3<FT> &v);
                      CGAL_DirectionC3(const FT &x, const FT &y, const FT &z);
                      ~CGAL_DirectionC3();

  CGAL_DirectionC3<FT> &operator=(const CGAL_DirectionC3<FT> &d);

  bool                operator==(const CGAL_DirectionC3<FT> &d) const;
  bool                operator!=(const CGAL_DirectionC3<FT> &d) const;
  int                 id() const;

  CGAL_VectorC3<FT>   vector() const;


  CGAL_DirectionC3    transform(const CGAL_Aff_transformationC3<FT> &t) const;


  CGAL_DirectionC3    operator-() const;

  FT                  delta(int i) const;
  FT                  dx() const;
  FT                  dy() const;
  FT                  dz() const;

  FT                  hdx() const;
  FT                  hdy() const;
  FT                  hdz() const;
  FT                  hw() const;


private:
  CGAL__Threetuple<FT>*   ptr() const;
};


template < class FT >
inline CGAL__Threetuple<FT>*   CGAL_DirectionC3<FT>::ptr() const
{
  return (CGAL__Threetuple<FT>*)PTR;
}


template < class FT >
CGAL_DirectionC3<FT>::CGAL_DirectionC3()
{
  PTR = new CGAL__Threetuple<FT>();
}

template < class FT >
CGAL_DirectionC3<FT>::CGAL_DirectionC3(const CGAL_DirectionC3<FT> &d) :
  CGAL_Handle(d)
{

}

template < class FT >
CGAL_DirectionC3<FT>::CGAL_DirectionC3(const CGAL_VectorC3<FT> &v) :
  CGAL_Handle(v)
{

}

template < class FT >
CGAL_DirectionC3<FT>::CGAL_DirectionC3(const FT &x, const FT &y, const FT &z)
{
  PTR = new CGAL__Threetuple<FT>(x, y, z);
}


template < class FT >
CGAL_DirectionC3<FT>:: ~CGAL_DirectionC3()
{}

template < class FT >
CGAL_DirectionC3<FT> &CGAL_DirectionC3<FT>::operator=(
                                               const CGAL_DirectionC3<FT> &d)
{

  CGAL_Handle::operator=(d);
  return *this;
}
template < class FT >
bool CGAL_DirectionC3<FT>::operator==(const CGAL_DirectionC3<FT> &d) const
{
  return ( ( dx()*d.dy() == dy()*d.dx() )
        &&( dx()*d.dz() == dz()*d.dx() )
        &&( dy()*d.dz() == dz()*d.dy() )
        &&( CGAL_sign( dx() ) == CGAL_sign( d.dx() ) )
        &&( CGAL_sign( dy() ) == CGAL_sign( d.dy() ) )
        &&( CGAL_sign( dz() ) == CGAL_sign( d.dz() ) ) );
}

template < class FT >
inline bool  CGAL_DirectionC3<FT>::operator!=(
                                         const CGAL_DirectionC3<FT> &d) const
{
  return !(*this == d);
}

template < class FT >
int  CGAL_DirectionC3<FT>::id() const
{
  return (int) PTR;
}
template < class FT >
inline CGAL_VectorC3<FT> CGAL_DirectionC3<FT>::vector() const
{
  return CGAL_VectorC3<FT>(*this);
}


template < class FT >
inline CGAL_DirectionC3<FT> CGAL_DirectionC3<FT>::transform(
                               const CGAL_Aff_transformationC3<FT> &t) const
{
  return t.transform(*this);
}


template < class FT >
inline CGAL_DirectionC3<FT> CGAL_DirectionC3<FT>::operator-() const
{
  return CGAL_DirectionC3<FT>(-dx(), -dy(), -dz());
}


template < class FT >
FT CGAL_DirectionC3<FT>::delta(int i) const
{
  CGAL_kernel_precondition( i >= 0 && i <= 2 );
  if(i == 0) {
    return dx();
  }
  if(i == 1) {
    return dy();
  }
  return dz();
}


template < class FT >
inline FT CGAL_DirectionC3<FT>::dx() const
{
  return ptr()->e0;
}


template < class FT >
inline FT CGAL_DirectionC3<FT>::dy() const
{
  return ptr()->e1;
}


template < class FT >
inline FT CGAL_DirectionC3<FT>::dz() const
{
  return ptr()->e2;
}


template < class FT >
inline FT CGAL_DirectionC3<FT>::hdx() const
{
  return ptr()->e0;
}


template < class FT >
inline FT CGAL_DirectionC3<FT>::hdy() const
{
  return ptr()->e1;
}


template < class FT >
inline FT CGAL_DirectionC3<FT>::hdz() const
{
  return ptr()->e2;
}

template < class FT >
inline FT CGAL_DirectionC3<FT>::hw() const
{
  return FT(1);
}



#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTIONC3
template < class FT >
ostream &operator<<(ostream &os, const CGAL_DirectionC3<FT> &d)
{
  CGAL_VectorC3<FT> v = d.vector();
  switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << v.x() << ' ' << v.y()  << ' ' << v.z();
    case CGAL_IO::BINARY :
        CGAL_write(os, v.x());
        CGAL_write(os, v.y());
        CGAL_write(os, v.z());
        return os;
    default:
        os << "DirectionC3(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
        return os;
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTIONC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTIONC3
template < class FT >
istream &operator>>(istream &is, CGAL_DirectionC3<FT> &p)
{
    FT x, y, z;
    switch(is.iword(CGAL_IO::mode)) {
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
    p = CGAL_DirectionC3<FT>(x, y, z);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTIONC3



#endif
