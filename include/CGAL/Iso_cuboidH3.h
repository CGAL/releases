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
// source        : Iso_cuboidH3.fw
// file          : include/CGAL/Iso_cuboidH3.h
// package       : H3 (2.2.1)
// revision      : 2.2.1
// revision_date : 26 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_ISO_CUBOIDH3_H
#define CGAL_ISO_CUBOIDH3_H

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
class Iso_cuboidH3 : public Handle
{
public:
  Iso_cuboidH3();
  Iso_cuboidH3(const Iso_cuboidH3<FT,RT>& );
  Iso_cuboidH3(const PointH3<FT,RT>& p,
                    const PointH3<FT,RT>& q);
  ~Iso_cuboidH3();

  Iso_cuboidH3<FT,RT>&
            operator=(const Iso_cuboidH3<FT,RT>& r);

  bool      operator==(const Iso_cuboidH3<FT,RT>& s) const;
  bool      operator!=(const Iso_cuboidH3<FT,RT>& s) const;
  bool      identical(const Iso_cuboidH3<FT,RT>& s) const;
  int       id() const;

  PointH3<FT,RT>  min() const;
  PointH3<FT,RT>  max() const;
  PointH3<FT,RT>  vertex(int i) const;
  PointH3<FT,RT>  operator[](int i) const;

  Iso_cuboidH3<FT,RT>
            transform(const Aff_transformationH3<FT,RT>& t) const;
  Bounded_side
            bounded_side(const PointH3<FT,RT>& p) const;
  bool      has_on(const PointH3<FT,RT>& p) const;
  bool      has_on_boundary(const PointH3<FT,RT>& p) const;
  bool      has_on_bounded_side(const PointH3<FT,RT>& p) const;
  bool      has_on_unbounded_side(const PointH3<FT,RT>& p) const;
  bool      is_degenerate() const;
  Bbox_2
            bbox() const;
  FT        xmin() const;
  FT        ymin() const;
  FT        zmin() const;
  FT        xmax() const;
  FT        ymax() const;
  FT        zmax() const;


protected:
  _Twotuple< PointH3<FT,RT> >*  ptr() const;
};

template < class FT, class RT >
inline
_Twotuple< PointH2<FT,RT> > *
Iso_cuboidH3<FT,RT>::ptr() const
{ return (_Twotuple< PointH2<FT,RT> >*)PTR; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
Iso_cuboidH3<FT,RT>::Iso_cuboidH3()
{ PTR = new _Twotuple< PointH2<FT,RT> >; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
Iso_cuboidH3<FT,RT>::
Iso_cuboidH3(const Iso_cuboidH3<FT,RT>& r)
  : Handle((Handle&)r)
{}
template < class FT, class RT >
CGAL_KERNEL_CTOR_LARGE_INLINE
Iso_cuboidH3<FT,RT>::
Iso_cuboidH3(const PointH3<FT,RT>& p,
                  const PointH3<FT,RT>& q)
{
  bool px_g_qx = ( p.hx()*q.hw() > q.hx()*p.hw() );
  bool py_g_qy = ( p.hy()*q.hw() > q.hy()*p.hw() );
  bool pz_g_qz = ( p.hz()*q.hw() > q.hz()*p.hw() );

  RT minx;
  RT miny;
  RT minz;
  RT maxx;
  RT maxy;
  RT maxz;
  RT minw = p.hw()*q.hw();
  RT maxw = p.hw()*q.hw();
  if ( px_g_qx )
  {
      minx = p.hx()*q.hw();
      maxx = q.hx()*p.hw();
  }
  else
  {
      minx = q.hx()*p.hw();
      maxx = p.hx()*q.hw();
  }
  if ( py_g_qy )
  {
      miny = p.hy()*q.hw();
      maxy = q.hy()*p.hw();
  }
  else
  {
      miny = q.hy()*p.hw();
      maxy = p.hy()*q.hw();
  }
  if ( pz_g_qz )
  {
      minz = p.hz()*q.hw();
      maxz = q.hz()*p.hw();
  }
  else
  {
      minz = q.hz()*p.hw();
      maxz = p.hz()*q.hw();
  }
  PTR = new _Twotuple<PointH3<FT,RT> >(
                 PointH3<FT,RT>(minx, miny, minz, minw),
                 PointH3<FT,RT>(maxx, maxy, maxz, maxw) );
}

template < class FT, class RT >
inline
Iso_cuboidH3<FT,RT>::~Iso_cuboidH3()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
Iso_cuboidH3<FT,RT>&
Iso_cuboidH3<FT,RT>::
operator=(const Iso_cuboidH3<FT,RT>& r)
{
 Handle::operator=(r);
 return *this;
}
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
Iso_cuboidH3<FT,RT>::
operator==(const Iso_cuboidH3<FT,RT>& r) const
{ return  (min() == r.min()) && (max() == r.max()); }

template < class FT, class RT >
inline
bool
Iso_cuboidH3<FT,RT>::
operator!=(const Iso_cuboidH3<FT,RT>& r) const
{ return !(*this == r); }

template < class FT, class RT >
inline
int
Iso_cuboidH3<FT,RT>::id() const
{ return (int) PTR; }

template < class FT, class RT >
inline
bool
Iso_cuboidH3<FT,RT>::
identical(const Iso_cuboidH3<FT,RT>& r) const
{ return (PTR == r.PTR); }

template < class FT, class RT >
inline
PointH2<FT,RT>
Iso_cuboidH3<FT,RT>::min() const
{ return  ptr()->e0; }

template < class FT, class RT >
inline
PointH2<FT,RT>
Iso_cuboidH3<FT,RT>::max() const
{ return  ptr()->e1; }

template < class FT, class RT >
inline
FT
Iso_cuboidH3<FT,RT>::xmin() const
{ return  FT( min().hx() ) / FT( min().hw() ); }

template < class FT, class RT >
inline
FT
Iso_cuboidH3<FT,RT>::ymin() const
{ return  FT( min().hy() ) / FT( min().hw() ); }

template < class FT, class RT >
inline
FT
Iso_cuboidH3<FT,RT>::zmin() const
{ return  FT( min().hz() ) / FT( min().hw() ); }

template < class FT, class RT >
inline
FT
Iso_cuboidH3<FT,RT>::xmax() const
{ return  FT( max().hx() ) / FT( max().hw() ); }

template < class FT, class RT >
inline
FT
Iso_cuboidH3<FT,RT>::ymax() const
{ return  FT( max().hy() ) / FT( max().hw() ); }

template < class FT, class RT >
inline
FT
Iso_cuboidH3<FT,RT>::zmax() const
{ return  FT( max().hz() ) / FT( max().hw() ); }
template < class FT, class RT >
CGAL_KERNEL_LARGE_INLINE
PointH3<FT,RT>
Iso_cuboidH3<FT,RT>::vertex(int i) const
{
  switch (i%8)
  {
    case 0: return min();
    case 1: return PointH3<FT,RT>( max.hx(), min.hy(), min.hz(),
                                        min.hw() );
    case 2: return PointH3<FT,RT>( max.hx(), max.hy(), min.hz(),
                                        min.hw() );
    case 3: return PointH3<FT,RT>( min.hx(), max.hy(), min.hz(),
                                        min.hw() );
    case 4: return PointH3<FT,RT>( min.hx(), max.hy(), max.hz(),
                                        min.hw() );
    case 5: return PointH3<FT,RT>( min.hx(), min.hy(), max.hz(),
                                        min.hw() );
    case 6: return PointH3<FT,RT>( max.hx(), min.hy(), max.hz(),
                                        min.hw() );
    case 7: return max();
  }
  return PointH2<FT,RT>();
}

template < class FT, class RT >
inline
PointH2<FT,RT>
Iso_cuboidH3<FT,RT>::operator[](int i) const
{ return vertex(i); }

template < class FT, class RT >
CGAL_KERNEL_MEDIUM_INLINE
Bounded_side
Iso_cuboidH3<FT,RT>::
bounded_side(const PointH2<FT,RT>& p) const
{
  if (   ( lexicographically_smaller(p,min() )
       ||( lexicographically_smaller(max(),p )
     )
  {
      return ON_UNBOUNDED_SIDE;
  }
  if (    (p.hx()*min.hw() == min.hx()*p.hw() )
        ||(p.hy()*min.hw() == min.hy()*p.hw() )
        ||(p.hz()*min.hw() == min.hz()*p.hw() )
        ||(p.hx()*max.hw() == max.hx()*p.hw() )
        ||(p.hy()*max.hw() == max.hy()*p.hw() )
        ||(p.hz()*max.hw() == max.hz()*p.hw() )
     )
  {
      return ON_BOUNDARY
  }
  else
  {
      return ON_BOUNDED_SIDE
  }
}

template < class FT, class RT >
inline
bool
Iso_cuboidH3<FT,RT>::has_on_boundary(const PointH2<FT,RT>& p) const
{ return ( bounded_side(p) == ON_BOUNDARY ); }

template < class FT, class RT >
inline
bool
Iso_cuboidH3<FT,RT>::has_on(const PointH2<FT,RT>& p) const
{ return ( bounded_side(p) == ON_BOUNDARY ); }

template < class FT, class RT >
inline
bool
Iso_cuboidH3<FT,RT>::
has_on_bounded_side(const PointH2<FT,RT>& p) const
{ return ( bounded_side(p) == ON_BOUNDED_SIDE ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
Iso_cuboidH3<FT,RT>::
has_on_unbounded_side(const PointH2<FT,RT>& p) const
{
  return (   ( lexicographically_smaller(p,min() )
           ||( lexicographically_smaller(max(),p )  );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
Iso_cuboidH3<FT,RT>::is_degenerate() const
{
  return (  ( min().hx() == max().hx() )
         || ( min().hy() == max().hy() )
         || ( min().hz() == max().hz() ) );
}
template < class FT, class RT >
inline
Bbox_2
Iso_cuboidH3<FT,RT>::bbox() const
{ return  min().bbox() + max().bbox(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
Iso_cuboidH3<FT,RT>
Iso_cuboidH3<FT,RT>::
transform(const Aff_transformationH2<FT,RT>&t) const
{
  return Iso_cuboidH3<FT,RT>(t.transform(min() ),
                                  t.transform(max() ) );
}

#ifndef NO_OSTREAM_INSERT_ISO_CUBOIDH3
template < class FT, class RT >
std::ostream& operator<<(std::ostream& os, const Iso_cuboidH3<FT,RT>& r)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << min() << ' ' << max();
    case IO::BINARY :
        return os << min() << max();
    default:
        return os << "Iso_cuboidH3(" << min() << ", " << max() << ")";
  }
}
#endif // NO_OSTREAM_INSERT_ISO_CUBOIDH3

#ifndef NO_ISTREAM_EXTRACT_ISO_CUBOIDH3
template < class FT, class RT >
std::istream& operator>>(std::istream& is, Iso_cuboidH3<FT,RT>& r)
{
  PointH3<FT,RT> p, q;
  is >> p >> q;
  r = Iso_cuboidH3<FT,RT>(p, q);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_ISO_CUBOIDH3

CGAL_END_NAMESPACE


#endif // CGAL_ISO_CUBOIDH3_H
