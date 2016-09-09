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
// file          : include/CGAL/SegmentC3.h
// package       : C3 (2.1.5)
// source        : web/SegmentC3.fw
// revision      : $Revision: 1.11 $
// revision_date : $Date: 1999/05/24 06:41:38 $
// author(s)     : Andreas.Fabri
//
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_SEGMENTC3_H
#define CGAL_SEGMENTC3_H

#ifndef CGAL_LINEC3_H
#include <CGAL/LineC3.h>
#endif // CGAL_LINEC3_H

#ifndef CGAL_TWOTUPLE_H
#include <CGAL/Twotuple.h>
#endif // CGAL_TWOTUPLE_H
#ifndef CGAL_PREDICATES_ON_POINTSC3_H
#include <CGAL/predicates_on_pointsC3.h>
#endif // CGAL_PREDICATES_ON_POINTSC3_H
#ifndef CGAL_BASIC_CONSTRUCTIONSC3_H
#include <CGAL/basic_constructionsC3.h>
#endif // CGAL_BASIC_CONSTRUCTIONSC3_H

CGAL_BEGIN_NAMESPACE

template < class FT >
class SegmentC3 : public Handle
{
public:
                  SegmentC3();
                  SegmentC3(const SegmentC3<FT>  &s);
                  SegmentC3(const PointC3<FT> &sp, const PointC3<FT> &ep);
                  ~SegmentC3();

  SegmentC3<FT>   &operator=(const SegmentC3<FT> &s);

  bool            has_on(const PointC3<FT> &p) const;
  bool            collinear_has_on(const PointC3<FT> &p) const;

  bool            operator==(const SegmentC3<FT> &s) const;
  bool            operator!=(const SegmentC3<FT> &s) const;
  long            id() const;

  PointC3<FT>     start() const;
  PointC3<FT>     end() const;

  PointC3<FT>     source() const;
  PointC3<FT>     target() const;

  PointC3<FT>     min() const;
  PointC3<FT>     max() const;
  PointC3<FT>     vertex(int i) const;
  PointC3<FT>     point(int i) const;
  PointC3<FT>     operator[](int i) const;

  FT              squared_length() const;

  DirectionC3<FT> direction() const;
  LineC3<FT>      supporting_line() const;
  SegmentC3       opposite() const;
  SegmentC3       transform(const Aff_transformationC3<FT> &t) const;

  bool            is_degenerate() const;
  Bbox_3          bbox() const;

private:
  _Twotuple< PointC3<FT> >*   ptr() const;
};

template < class FT >
inline _Twotuple< PointC3<FT> > *SegmentC3<FT>::ptr() const
{
  return (_Twotuple< PointC3<FT> >*)PTR;
}

template < class FT >
SegmentC3<FT>::SegmentC3()
{
  PTR = new _Twotuple< PointC3<FT> >;
}


template < class FT >
SegmentC3<FT>::SegmentC3(const SegmentC3<FT>  &s) :
  Handle((Handle&)s)
{}

template < class FT >
SegmentC3<FT>::SegmentC3(const PointC3<FT> &sp, const PointC3<FT> &ep)
{
  PTR = new _Twotuple< PointC3<FT> >(sp, ep);
}


template < class FT >
inline SegmentC3<FT>::~SegmentC3()
{}


template < class FT >
SegmentC3<FT> &SegmentC3<FT>::operator=(const SegmentC3<FT> &s)
{
  Handle::operator=(s);
  return *this;
}
template < class FT >
inline
bool
SegmentC3<FT>::operator==(const SegmentC3<FT> &s) const
{
  return (source() == s.source())  && (target() == s.target());
}


template < class FT >
inline
bool
SegmentC3<FT>::operator!=(const SegmentC3<FT> &s) const
{
  return !(*this == s);
}


template < class FT >
long  SegmentC3<FT>::id() const
{
  return (long) PTR;
}
template < class FT >
PointC3<FT>  SegmentC3<FT>::start() const
{
  return ptr()->e0;
}


template < class FT >
PointC3<FT>  SegmentC3<FT>::end() const
{
  return ptr()->e1;
}


template < class FT >
PointC3<FT>  SegmentC3<FT>::source() const
{
  return ptr()->e0;
}


template < class FT >
PointC3<FT>  SegmentC3<FT>::target() const
{
  return ptr()->e1;
}


template < class FT >
inline
PointC3<FT>
SegmentC3<FT>::min() const
{
  return (lexicographically_xyz_smaller(source(),target())) ? source()
                                                            : target();
}


template < class FT >
inline
PointC3<FT>
SegmentC3<FT>::max() const
{
  return (lexicographically_xyz_smaller(source(),target())) ? target()
                                                            : source();
}


template < class FT >
inline
PointC3<FT>
SegmentC3<FT>::vertex(int i) const
{
  return (i%2 == 0) ? source() : target();
}


template < class FT >
inline
PointC3<FT>
SegmentC3<FT>::point(int i) const
{
  return (i%2 == 0) ? source() : target();
}


template < class FT >
inline
PointC3<FT>
SegmentC3<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
inline
FT
SegmentC3<FT>::squared_length() const
{
  return squared_distance(target(), source());
}


template < class FT >
inline
DirectionC3<FT>
SegmentC3<FT>::direction() const
{
  return DirectionC3<FT>( target() - source() );
}


template < class FT >
inline
LineC3<FT>
SegmentC3<FT>::supporting_line() const
{
  return LineC3<FT>(*this);
}


template < class FT >
inline
SegmentC3<FT>
SegmentC3<FT>::opposite() const
{
  return SegmentC3<FT>(target(), source());
}


template < class FT >
inline
SegmentC3<FT>
SegmentC3<FT>::transform(const Aff_transformationC3<FT> &t) const
{
  return SegmentC3<FT>(t.transform(source()), t.transform(target()));
}


template < class FT >
inline
bool
SegmentC3<FT>::is_degenerate() const
{
  return source() == target();
}


template < class FT >
inline
Bbox_3
SegmentC3<FT>::bbox() const
{
  return source().bbox() + target().bbox();
}


#ifndef CGAL_NO_OSTREAM_INSERT_SEGMENTC3
template < class FT >
ostream &operator<<(ostream &os, const SegmentC3<FT> &s)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << s.source() << ' ' << s.target();
    case IO::BINARY :
        return os << s.source() << s.target();
    default:
        return os << "SegmentC3(" << s.source() <<  ", " << s.target() << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_SEGMENTC3

#ifndef CGAL_NO_ISTREAM_EXTRACT_SEGMENTC3
template < class FT >
istream &operator>>(istream &is, SegmentC3<FT> &s)
{
    PointC3<FT> p, q;

    is >> p >> q;

    s = SegmentC3<FT>(p, q);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_SEGMENTC3
template < class FT >
bool SegmentC3<FT>::has_on(const PointC3<FT> &p) const
{
  return are_ordered_along_line(source(), p, target());
}

template < class FT >
inline
bool
SegmentC3<FT>::collinear_has_on(const PointC3<FT> &p) const
{
  return collinear_are_ordered_along_line(source(), p, target());
}


CGAL_END_NAMESPACE

#endif
