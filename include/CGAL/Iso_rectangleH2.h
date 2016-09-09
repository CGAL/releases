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
// source        : Iso_rectangleH2.fw
// file          : include/CGAL/Iso_rectangleH2.h
// package       : H2 (2.1.3)
// revision      : 2.1.3
// revision_date : 21 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_ISO_RECTANGLEH2_H
#define CGAL_ISO_RECTANGLEH2_H

#ifndef TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // TWOTUPLE_H
#ifndef CGAL_POINTH2_H
#include <CGAL/PointH2.h>
#endif // CGAL_POINTH2_H
#ifndef CGAL_PREDICATES_ON_POINTSH2_H
#include <CGAL/predicates_on_pointsH2.h>
#endif // CGAL_PREDICATES_ON_POINTSH2_H

CGAL_BEGIN_NAMESPACE

template <class FT, class RT>
class Iso_rectangleH2 : public Handle
{
public:
            Iso_rectangleH2();
            Iso_rectangleH2(const Iso_rectangleH2<FT,RT> &);
            Iso_rectangleH2(const PointH2<FT,RT> &p,
                                 const PointH2<FT,RT> &q);
            ~Iso_rectangleH2();

  Iso_rectangleH2<FT,RT>&
            operator=(const Iso_rectangleH2<FT,RT> &r);

  bool      operator==(const Iso_rectangleH2<FT,RT> &s) const;
  bool      operator!=(const Iso_rectangleH2<FT,RT> &s) const;
  bool      identical(const Iso_rectangleH2<FT,RT> &s) const;
  int       id() const;

  PointH2<FT,RT>  min() const;
  PointH2<FT,RT>  max() const;
  PointH2<FT,RT>  vertex(int i) const;
  PointH2<FT,RT>  operator[](int i) const;

  Iso_rectangleH2<FT,RT>
            transform(const Aff_transformationH2<FT,RT> &t) const;

  Bounded_side
            bounded_side(const PointH2<FT,RT> &p) const;
  bool      has_on(const PointH2<FT,RT> &p) const;
  bool      has_on_boundary(const PointH2<FT,RT> &p) const;
  bool      has_on_bounded_side(const PointH2<FT,RT> &p) const;
  bool      has_on_unbounded_side(const PointH2<FT,RT> &p) const;
  bool      is_degenerate() const;

  Bbox_2
            bbox() const;

  FT        xmin() const;
  FT        ymin() const;
  FT        xmax() const;
  FT        ymax() const;


protected:

  _Twotuple< PointH2<FT,RT> >*
            ptr() const;
};

template < class FT, class RT >
inline
_Twotuple< PointH2<FT,RT> > *
Iso_rectangleH2<FT,RT>::ptr() const
{ return (_Twotuple< PointH2<FT,RT> >*)PTR; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
Iso_rectangleH2<FT,RT>::Iso_rectangleH2()
{ PTR = new _Twotuple< PointH2<FT,RT> >; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
Iso_rectangleH2<FT,RT>::
Iso_rectangleH2( const Iso_rectangleH2<FT,RT> &r)
 : Handle((Handle&)r)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_MEDIUM_INLINE
Iso_rectangleH2<FT,RT>::Iso_rectangleH2(const PointH2<FT,RT> &p,
                                                  const PointH2<FT,RT> &q)
{
  bool px_g_qx = ( p.hx()*q.hw() > q.hx()*p.hw() );
  bool py_g_qy = ( p.hy()*q.hw() > q.hy()*p.hw() );
  if ( px_g_qx || py_g_qy)
  {
      if ( px_g_qx && py_g_qy )
      {
          PTR = new _Twotuple<PointH2<FT,RT> >(q,p);
      }
      else
      {
         if ( px_g_qx )
         {
             PTR = new _Twotuple<PointH2<FT,RT> >(
             PointH2<FT,RT>(q.hx()*p.hw(), p.hy()*q.hw(), q.hw()*p.hw() ),
             PointH2<FT,RT>(p.hx()*q.hw(), q.hy()*p.hw(), q.hw()*p.hw() ));
         }
         if ( py_g_qy )
         {
             PTR = new _Twotuple<PointH2<FT,RT> >(
             PointH2<FT,RT>(p.hx()*q.hw(), q.hy()*p.hw(), q.hw()*p.hw() ),
             PointH2<FT,RT>(q.hx()*p.hw(), p.hy()*q.hw(), q.hw()*p.hw() ));
         }
      }
  }
  else
  {
      PTR = new _Twotuple< PointH2<FT,RT> >(p,q);
  }
}

template < class FT, class RT >
inline
Iso_rectangleH2<FT,RT>::~Iso_rectangleH2()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
Iso_rectangleH2<FT,RT>&
Iso_rectangleH2<FT,RT>::
operator=(const Iso_rectangleH2<FT,RT> &r)
{
  Handle::operator=(r);
  return *this;
}
template < class FT, class RT >
inline
bool
Iso_rectangleH2<FT,RT>::
operator==(const Iso_rectangleH2<FT,RT> &r) const
{ return  vertex(0) == r.vertex(0) && vertex(2) == r.vertex(2); }

template < class FT, class RT >
inline
bool
Iso_rectangleH2<FT,RT>::
operator!=(const Iso_rectangleH2<FT,RT> &r) const
{ return !(*this == r); }  /* XXX */

template < class FT, class RT >
inline
int
Iso_rectangleH2<FT,RT>::id() const
{ return (int)PTR; }

template < class FT, class RT >
inline
bool
Iso_rectangleH2<FT,RT>::
identical(const Iso_rectangleH2<FT,RT> &r) const
{ return (PTR == r.PTR); }
template < class FT, class RT >
inline
PointH2<FT,RT>
Iso_rectangleH2<FT,RT>::min() const
{ return  ptr()->e0; }

template < class FT, class RT >
inline
PointH2<FT,RT>
Iso_rectangleH2<FT,RT>::max() const
{ return  ptr()->e1; }

template < class FT, class RT >
inline
FT
Iso_rectangleH2<FT,RT>::xmin() const
{ return  FT( min().hx() ) / FT( min().hw() ); }

template < class FT, class RT >
inline
FT
Iso_rectangleH2<FT,RT>::ymin() const
{ return  FT( min().hy() ) / FT( min().hw() ); }

template < class FT, class RT >
inline
FT
Iso_rectangleH2<FT,RT>::xmax() const
{ return  FT( max().hx() ) / FT( max().hw() ); }

template < class FT, class RT >
inline
FT
Iso_rectangleH2<FT,RT>::ymax() const
{ return  FT( max().hy() ) / FT( max().hw() ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH2<FT,RT>
Iso_rectangleH2<FT,RT>::vertex(int i) const
{
  switch (i%4)
  {
    case 0:
        return min();
    case 1:
        return PointH2<FT,RT>( max().hx()*min().hw(),
                                    min().hy()*max().hw(),
                                    min().hw()*max().hw() );
    case 2:
        return max();
    case 3:
        return PointH2<FT,RT>( min().hx()*max().hw(),
                                    max().hy()*min().hw(),
                                    min().hw()*max().hw() );
  }
  return PointH2<FT,RT>();
}

template < class FT, class RT >
inline
PointH2<FT,RT>
Iso_rectangleH2<FT,RT>::operator[](int i) const
{ return vertex(i); }
template < class FT, class RT >
CGAL_KERNEL_INLINE
Bounded_side
Iso_rectangleH2<FT,RT>::bounded_side(const PointH2<FT,RT> &p) const
{
  Oriented_side wrt_min = _where_wrt_L_wedge(min(),p);
  Oriented_side wrt_max = _where_wrt_L_wedge(p,max());
  if (( wrt_min == ON_NEGATIVE_SIDE )||( wrt_max == ON_NEGATIVE_SIDE))
  {
      return ON_UNBOUNDED_SIDE;
  }
  if (  ( wrt_min == ON_ORIENTED_BOUNDARY )
      ||( wrt_max == ON_ORIENTED_BOUNDARY ) )
  {
      return ON_BOUNDARY;
  }
  return ON_BOUNDED_SIDE;
}

template < class FT, class RT >
inline
bool
Iso_rectangleH2<FT,RT>::has_on_boundary(const PointH2<FT,RT> &p) const
{ return ( bounded_side(p) == ON_BOUNDARY ); }

template < class FT, class RT >
inline
bool
Iso_rectangleH2<FT,RT>::has_on(const PointH2<FT,RT> &p) const
{ return ( bounded_side(p) == ON_BOUNDARY ); }

template < class FT, class RT >
inline
bool
Iso_rectangleH2<FT,RT>::
has_on_bounded_side(const PointH2<FT,RT> &p) const
{ return ( bounded_side(p) == ON_BOUNDED_SIDE ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
Iso_rectangleH2<FT,RT>::
has_on_unbounded_side(const PointH2<FT,RT> &p) const
{
  return (  (_where_wrt_L_wedge(min(),p) == ON_NEGATIVE_SIDE)
          ||(_where_wrt_L_wedge(p,max()) == ON_NEGATIVE_SIDE) );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
Iso_rectangleH2<FT,RT>::is_degenerate() const
{
 return (   ( min().hx()*max().hw() == max().hx()*min().hw() )
         || ( min().hy()*max().hw() == max().hy()*min().hw() ) );
}
template < class FT, class RT >
inline
Bbox_2
Iso_rectangleH2<FT,RT>::bbox() const
{ return  min().bbox() + max().bbox(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
Iso_rectangleH2<FT,RT>
Iso_rectangleH2<FT,RT>::
transform(const Aff_transformationH2<FT,RT>&t) const
{
  return Iso_rectangleH2<FT,RT>(t.transform(min() ),
                                     t.transform(max() ) );
}

#ifndef NO_OSTREAM_INSERT_ISO_RECTANGLEH2
template < class FT, class RT >
std::ostream &operator<<(std::ostream &os, const Iso_rectangleH2<FT,RT> &r)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << r[0] << ' ' << r[2];
    case IO::BINARY :
        return os << r[0] << r[2];
    default:
        return os << "Iso_rectangleH2(" << r[0] << ", " << r[2] << ")";
  }
}
#endif // NO_OSTREAM_INSERT_ISO_RECTANGLEH2

#ifndef NO_ISTREAM_EXTRACT_ISO_RECTANGLEH2
template < class FT, class RT >
std::istream &operator>>(std::istream &is, Iso_rectangleH2<FT,RT> &r)
{
  PointH2<FT,RT> p, q;
  is >> p >> q;
  r = Iso_rectangleH2<FT,RT>(p, q);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_ISO_RECTANGLEH2

CGAL_END_NAMESPACE


#endif // CGAL_ISO_RECTANGLEH2_H
