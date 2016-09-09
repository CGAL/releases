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
// source        : RayH3.fw
// file          : include/CGAL/RayH3.h
// package       : H3 (2.2.1)
// revision      : 2.2.1
// revision_date : 26 May 1999 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_RAYH3_H
#define CGAL_RAYH3_H

#ifndef CGAL_LINEH3_H
#include <CGAL/LineH3.h>
#endif // CGAL_LINEH3_H

CGAL_BEGIN_NAMESPACE

template < class FT, class RT >
class _Ray_repH3 : public Rep
{
public:
  _Ray_repH3() {}
  _Ray_repH3(const PointH3<FT,RT>& p,
                  const DirectionH3<FT,RT>& d)
  {
      startpoint = p;
      direction  = d;
  }
  ~_Ray_repH3() {}

friend class RayH3<FT,RT>;

private:
  PointH3<FT,RT>      startpoint;
  DirectionH3<FT,RT>  direction;
};

template < class FT, class RT >
class RayH3 : public Handle
{
public:
        RayH3();
        RayH3( const RayH3<FT,RT>& tbc);
        RayH3( const PointH3<FT,RT>& sp,
                    const PointH3<FT,RT>& secondp);
        RayH3( const PointH3<FT,RT>& sp,
                    const DirectionH3<FT,RT>& d);
        ~RayH3();

    RayH3<FT,RT>&  operator=(const RayH3<FT,RT>& r);

    PointH3<FT,RT> start() const;
    PointH3<FT,RT> source() const;
    PointH3<FT,RT> second_point() const;
    PointH3<FT,RT> point(int i) const;
    DirectionH3<FT,RT>
                        direction() const;
    LineH3<FT,RT>  supporting_line() const;
    RayH3<FT,RT>   opposite() const;
    RayH3<FT,RT>   transform( const Aff_transformationH3<FT,RT> & t)
                                                                         const;
    bool                has_on(const PointH3<FT,RT> p) const;
    bool                collinear_has_on(const PointH3<FT,RT> p) const;
    bool                is_degenerate() const;

    bool                operator==(const RayH3<FT,RT>& r) const;
    bool                operator!=(const RayH3<FT,RT>& r) const;
    bool                identical( const RayH3<FT,RT>& r) const;

protected:
    _Ray_repH3<FT,RT>*  ptr() const;
};

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH3<FT,RT>::RayH3()
{ PTR = new _Ray_repH3<FT,RT>; }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH3<FT,RT>::RayH3(const RayH3<FT,RT>& tbc)
  : Handle(tbc)
{}

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH3<FT,RT>::RayH3( const PointH3<FT,RT>& sp,
                               const PointH3<FT,RT>& secondp)
{ PTR = new _Ray_repH3<FT,RT>(sp,(secondp - sp).direction() ); }

template < class FT, class RT >
CGAL_KERNEL_CTOR_INLINE
RayH3<FT,RT>::RayH3( const PointH3<FT,RT>& sp,
                               const DirectionH3<FT,RT>& d)
{ PTR = new _Ray_repH3<FT,RT>(sp, d ); }

template < class FT, class RT >
inline
RayH3<FT,RT>::~RayH3()
{}

template < class FT, class RT >
CGAL_KERNEL_INLINE
RayH3<FT,RT>&
RayH3<FT,RT>::operator=(const RayH3<FT,RT>& r)
{
  Handle::operator=(r);
  return *this;
}
template < class FT, class RT >
inline
PointH3<FT,RT>
RayH3<FT,RT>::source() const
{ return ptr()->startpoint; }

template < class FT, class RT >
inline
PointH3<FT,RT>
RayH3<FT,RT>::start() const
{ return ptr()->startpoint; }

template < class FT, class RT >
inline
DirectionH3<FT,RT>
RayH3<FT,RT>::direction() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return DirectionH3<FT,RT>( ptr()->direction );
}


template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH3<FT,RT>
RayH3<FT,RT>::second_point() const
{ return start() + direction().vector(); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
PointH3<FT,RT>
RayH3<FT,RT>::point(int i) const
{
  CGAL_kernel_precondition( i >= 0 );
  return start() + RT(i)*(direction().vector() ) ;
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
LineH3<FT,RT>
RayH3<FT,RT>::supporting_line() const
{
  CGAL_kernel_precondition( !is_degenerate() );
  return LineH3<FT,RT>(start(), second_point() );
}

template < class FT, class RT >
CGAL_KERNEL_INLINE
RayH3<FT,RT>
RayH3<FT,RT>::opposite() const
{ return RayH3<FT,RT>( start(), - direction() ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
RayH3<FT,RT>
RayH3<FT,RT>::transform( const Aff_transformationH3<FT,RT> & t) const
{ return RayH3<FT,RT>(t.transform(start()), t.transform(direction()) ); }


#ifndef NO_OSTREAM_INSERT_RAYH3
template < class FT, class RT >
std::ostream &operator<<(std::ostream &os, const RayH3<FT,RT> &r)
{
  switch(os.iword(IO::mode))
  {
      case IO::ASCII :
          return os << r.start() << ' ' << r.direction();
      case IO::BINARY :
          return os<< r.start() << r.direction();
      default:
          return os << "RayH3(" << r.start() <<  ", " << r.direction() << ")";
  }
}
#endif // NO_OSTREAM_INSERT_RAYH3

#ifndef NO_ISTREAM_EXTRACT_RAYH3
template < class FT, class RT  >
std::istream &operator>>(std::istream &is, RayH3<FT,RT> &r)
{
  PointH3<FT,RT> p;
  DirectionH3<FT,RT> d;
  is >> p >> d;
  r = RayH3<FT,RT>(p, d);
  return is;
}
#endif // NO_ISTREAM_EXTRACT_RAYH3
template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH3<FT,RT>::has_on(const PointH3<FT,RT> p) const
{
  return ( (  p == start() )
         ||(  DirectionH3<FT,RT>(p - start()) == direction() ) );
}

template < class FT, class RT >
inline                                      /* XXX */
bool
RayH3<FT,RT>::collinear_has_on(const PointH3<FT,RT> p) const
{ return has_on(p); }

template < class FT, class RT >
inline
bool
RayH3<FT,RT>::is_degenerate() const
{ return (ptr()->direction).is_degenerate() ; }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH3<FT,RT>::operator==(const RayH3<FT,RT>& r) const
{ return ( (start() == r.start() )&&( direction() == r.direction() ) ); }

template < class FT, class RT >
CGAL_KERNEL_INLINE
bool
RayH3<FT,RT>::operator!=( const RayH3<FT,RT>& r) const
{ return !operator==(r); }

template < class FT, class RT >
inline
bool
RayH3<FT,RT>::identical( const RayH3<FT,RT>& r) const
{ return ( PTR == r.PTR ); }

template < class FT, class RT >
inline
_Ray_repH3<FT,RT>*
RayH3<FT,RT>::ptr() const
{ return (_Ray_repH3<FT,RT>*) PTR; }


CGAL_END_NAMESPACE


#endif // CGAL_RAYH3_H
