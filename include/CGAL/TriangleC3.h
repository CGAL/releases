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
// file          : include/CGAL/TriangleC3.h
// package       : C3 (2.1.5)
// source        : web/TriangleC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:38 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGLEC3_H
#define CGAL_TRIANGLEC3_H

#ifndef CGAL_THREETUPLE_H
#include <CGAL/Threetuple.h>
#endif // CGAL_THREETUPLE_H
#ifndef CGAL_PLANEC3_H
#include <CGAL/PlaneC3.h>
#endif // CGAL_PLANEC3_H
#ifndef CGAL_SOLVE_H
#include <CGAL/solve.h>
#endif // CGAL_SOLVE_H

CGAL_BEGIN_NAMESPACE

template <class FT>
class TriangleC3 : public Handle
{
public:
                 TriangleC3();
                 TriangleC3(const TriangleC3<FT> &t);
                 TriangleC3(const PointC3<FT> &p,
                            const PointC3<FT> &q,
                            const PointC3<FT> &r);

                 ~TriangleC3();

  TriangleC3<FT> &operator=(const TriangleC3<FT> &t);

  bool           operator==(const TriangleC3<FT> &t) const;
  bool           operator!=(const TriangleC3<FT> &t) const;
  long           id() const;

  PlaneC3<FT>    supporting_plane() const;


  TriangleC3     transform(const Aff_transformationC3<FT> &t) const;

  bool           has_on(const PointC3<FT> &p) const;
  bool           is_degenerate() const;


  PointC3<FT>    vertex(int i) const;
  PointC3<FT>    operator[](int i) const;

  Bbox_3         bbox() const;

private:
  _Threetuple< PointC3<FT> >*   ptr() const;
};

template < class FT >
inline _Threetuple< PointC3<FT> > *TriangleC3<FT>::ptr() const
{
  return (_Threetuple< PointC3<FT> >*)PTR;
}

template < class FT >
TriangleC3<FT>::TriangleC3()
{
  PTR = new _Threetuple< PointC3<FT> >;
}


template < class FT >
TriangleC3<FT>::TriangleC3(const TriangleC3<FT> &t) :
  Handle(t)
{}


template < class FT >
TriangleC3<FT>::TriangleC3(const PointC3<FT> &p,
                           const PointC3<FT> &q,
                           const PointC3<FT> &r)
{
  PTR = new _Threetuple< PointC3<FT> >(p, q, r);
}


template < class FT >
inline TriangleC3<FT>::~TriangleC3()
{}


template < class FT >
TriangleC3<FT> &TriangleC3<FT>::operator=(const TriangleC3<FT> &t)
{
  Handle::operator=(t);
  return *this;
}
template < class FT >
bool
TriangleC3<FT>::operator==(const TriangleC3<FT> &t) const
{
  int i;
  for(i=0; i<3; i++)
    if ( vertex(0) == t.vertex(i) )
       break;

  return (i<3) && vertex(1) == t.vertex(i+1) && vertex(2) == t.vertex(i+2);
}


template < class FT >
inline
bool
TriangleC3<FT>::operator!=(const TriangleC3<FT> &t) const
{
  return !(*this == t);
}


template < class FT >
inline
long
TriangleC3<FT>::id() const
{
  return (long) PTR;
}
template < class FT >
PointC3<FT>
TriangleC3<FT>::vertex(int i) const
{
  if (i<0) i=(i%3)+3;
  else if (i>3) i=i%3;
  return (i==0) ? ptr()->e0 :
         (i==1) ? ptr()->e1 :
                  ptr()->e2 ;
}


template < class FT >
inline
PointC3<FT>
TriangleC3<FT>::operator[](int i) const
{
  return vertex(i);
}

template < class FT >
inline
PlaneC3<FT>
TriangleC3<FT>::supporting_plane() const
{
  return PlaneC3<FT>(vertex(0), vertex(1), vertex(2));
}


template < class FT >
Bbox_3
TriangleC3<FT>::bbox() const
{
  return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}


template < class FT >
inline
TriangleC3<FT>
TriangleC3<FT>::transform(const Aff_transformationC3<FT> &t) const
{
  return TriangleC3<FT>(t.transform(vertex(0)),
                        t.transform(vertex(1)),
                        t.transform(vertex(2)));
}
template < class FT >
bool
TriangleC3<FT>::has_on(const PointC3<FT> &p) const
{
  PointC3<FT> o = vertex(0) + supporting_plane().orthogonal_vector();
  VectorC3<FT> v0 = vertex(0)-o,
               v1 = vertex(1)-o,
               v2 = vertex(2)-o;

  FT alpha, beta, gamma;
  solve(v0, v1, v2, p-o, alpha, beta, gamma);
  return (alpha >= FT(0)) && (beta >= FT(0)) && (gamma >= FT(0))
      && ((alpha+beta+gamma == FT(1)));
}


template < class FT >
bool
TriangleC3<FT>::is_degenerate() const
{
  return collinear(vertex(0),vertex(1),vertex(2));
}


#ifndef CGAL_NO_OSTREAM_INSERT_TRIANGLEC3
template < class FT >
ostream &operator<<(ostream &os, const TriangleC3<FT> &t)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << t[0] << ' ' << t[1] << ' ' << t[2];
    case IO::BINARY :
        return os << t[0]  << t[1]  << t[2];
    default:
        os << "TriangleC3(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
        return os;
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_TRIANGLEC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_TRIANGLEC3
template < class FT >
istream &operator>>(istream &is, TriangleC3<FT> &t)
{
    PointC3<FT> p, q, r;

    is >> p >> q >> r;

    t = TriangleC3<FT>(p, q, r);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_TRIANGLEC3


CGAL_END_NAMESPACE

#endif
