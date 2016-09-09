// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/DirectionC3.h
// package       : C3 (2.1.5)
// source        : web/DirectionC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:37 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_DIRECTIONC3_H
#define CGAL_DIRECTIONC3_H

#ifndef CGAL_THREETUPLE_H
#include <CGAL/Threetuple.h>
#endif // CGAL_THREETUPLE_H
#ifndef CGAL_VECTORC3_H
#include <CGAL/VectorC3.h>
#endif // CGAL_VECTORC3_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class DirectionC3 : public Handle
{
public:
                 DirectionC3();
                 DirectionC3(const DirectionC3<FT> &d);
                 DirectionC3(const VectorC3<FT> &v);
                 DirectionC3(const FT &x, const FT &y, const FT &z);
                 ~DirectionC3();

  DirectionC3<FT> &operator=(const DirectionC3<FT> &d);

  bool           operator==(const DirectionC3<FT> &d) const;
  bool           operator!=(const DirectionC3<FT> &d) const;
  long           id() const;

  VectorC3<FT>   vector() const;


  DirectionC3    transform(const Aff_transformationC3<FT> &t) const;


  DirectionC3    operator-() const;

  FT             delta(int i) const;
  FT             dx() const;
  FT             dy() const;
  FT             dz() const;

  FT             hdx() const;
  FT             hdy() const;
  FT             hdz() const;
  FT             hw() const;


private:
  _Threetuple<FT>*   ptr() const;
};

template < class FT >
inline _Threetuple<FT>*   DirectionC3<FT>::ptr() const
{
  return (_Threetuple<FT>*)PTR;
}

template < class FT >
DirectionC3<FT>::DirectionC3()
{
  PTR = new _Threetuple<FT>();
}

template < class FT >
DirectionC3<FT>::DirectionC3(const DirectionC3<FT> &d) :
  Handle(d)
{

}

template < class FT >
DirectionC3<FT>::DirectionC3(const VectorC3<FT> &v) :
  Handle(v)
{

}

template < class FT >
DirectionC3<FT>::DirectionC3(const FT &x, const FT &y, const FT &z)
{
  PTR = new _Threetuple<FT>(x, y, z);
}


template < class FT >
DirectionC3<FT>:: ~DirectionC3()
{}

template < class FT >
DirectionC3<FT> &DirectionC3<FT>::operator=(const DirectionC3<FT> &d)
{

  Handle::operator=(d);
  return *this;
}
template < class FT >
bool DirectionC3<FT>::operator==(const DirectionC3<FT> &d) const
{
  return  ( dx()*d.dy() == dy()*d.dx() )
        &&( dx()*d.dz() == dz()*d.dx() )
        &&( dy()*d.dz() == dz()*d.dy() )
        &&( CGAL::sign( dx() ) == CGAL::sign( d.dx() ) )
        &&( CGAL::sign( dy() ) == CGAL::sign( d.dy() ) )
        &&( CGAL::sign( dz() ) == CGAL::sign( d.dz() ) );
}

template < class FT >
inline bool  DirectionC3<FT>::operator!=(const DirectionC3<FT> &d) const
{
  return !(*this == d);
}

template < class FT >
long  DirectionC3<FT>::id() const
{
  return (long) PTR;
}
template < class FT >
inline VectorC3<FT> DirectionC3<FT>::vector() const
{
  return VectorC3<FT>(*this);
}


template < class FT >
inline
DirectionC3<FT>
DirectionC3<FT>::transform(const Aff_transformationC3<FT> &t) const
{
  return t.transform(*this);
}


template < class FT >
inline DirectionC3<FT> DirectionC3<FT>::operator-() const
{
  return DirectionC3<FT>(-dx(), -dy(), -dz());
}


template < class FT >
FT DirectionC3<FT>::delta(int i) const
{
  CGAL_kernel_precondition( i >= 0 && i <= 2 );
  return (i==0) ? dx() :
         (i==1) ? dy() : dz() ;
}


template < class FT >
inline FT DirectionC3<FT>::dx() const
{
  return ptr()->e0;
}


template < class FT >
inline FT DirectionC3<FT>::dy() const
{
  return ptr()->e1;
}


template < class FT >
inline FT DirectionC3<FT>::dz() const
{
  return ptr()->e2;
}


template < class FT >
inline FT DirectionC3<FT>::hdx() const
{
  return ptr()->e0;
}


template < class FT >
inline FT DirectionC3<FT>::hdy() const
{
  return ptr()->e1;
}


template < class FT >
inline FT DirectionC3<FT>::hdz() const
{
  return ptr()->e2;
}

template < class FT >
inline FT DirectionC3<FT>::hw() const
{
  return FT(1);
}



#ifndef CGAL_NO_OSTREAM_INSERT_DIRECTIONC3
template < class FT >
ostream &operator<<(ostream &os, const DirectionC3<FT> &d)
{
  VectorC3<FT> v = d.vector();
  switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << v.x() << ' ' << v.y()  << ' ' << v.z();
    case IO::BINARY :
        write(os, v.x());
        write(os, v.y());
        write(os, v.z());
        return os;
    default:
        os << "DirectionC3(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
        return os;
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_DIRECTIONC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_DIRECTIONC3
template < class FT >
istream &operator>>(istream &is, DirectionC3<FT> &p)
{
    FT x, y, z;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
        is >> x >> y >> z;
        break;
    case IO::BINARY :
        read(is, x);
        read(is, y);
        read(is, z);
        break;
    default:
        cerr << "" << endl;
        cerr << "Stream must be in ascii or binary mode" << endl;
        break;
    }
    p = DirectionC3<FT>(x, y, z);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_DIRECTIONC3



CGAL_END_NAMESPACE

#endif
