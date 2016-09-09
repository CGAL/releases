/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: Iso_rectangleH2.h
// Author: Stefan Schirra

#ifndef CGAL_ISO_RECTANGLEH2_H
#define CGAL_ISO_RECTANGLEH2_H

#include <CGAL/Twotuple.h>
#include <CGAL/PointH2.h>
#include <CGAL/predicates_on_pointsH2.h>

template <class FT, class RT>
class CGAL_Iso_rectangleH2 : public CGAL_Handle
{
public:
            CGAL_Iso_rectangleH2();
            CGAL_Iso_rectangleH2(const CGAL_Iso_rectangleH2<FT,RT> &);
            CGAL_Iso_rectangleH2(const CGAL_PointH2<FT,RT> &p,
                                 const CGAL_PointH2<FT,RT> &q);
            ~CGAL_Iso_rectangleH2();

  CGAL_Iso_rectangleH2<FT,RT>&
            operator=(const CGAL_Iso_rectangleH2<FT,RT> &r);

  bool      operator==(const CGAL_Iso_rectangleH2<FT,RT> &s) const;
  bool      operator!=(const CGAL_Iso_rectangleH2<FT,RT> &s) const;
  bool      identical(const CGAL_Iso_rectangleH2<FT,RT> &s) const;
  int       id() const;

  CGAL_PointH2<FT,RT>  min() const;
  CGAL_PointH2<FT,RT>  max() const;
  CGAL_PointH2<FT,RT>  vertex(int i) const;
  CGAL_PointH2<FT,RT>  operator[](int i) const;

  CGAL_Iso_rectangleH2<FT,RT>
            transform(const CGAL_Aff_transformationH2<FT,RT> &t) const;

  CGAL_Bounded_side
            bounded_side(const CGAL_PointH2<FT,RT> &p) const;
  bool      has_on(const CGAL_PointH2<FT,RT> &p) const;
  bool      has_on_boundary(const CGAL_PointH2<FT,RT> &p) const;
  bool      has_on_bounded_side(const CGAL_PointH2<FT,RT> &p) const;
  bool      has_on_unbounded_side(const CGAL_PointH2<FT,RT> &p) const;
  bool      is_degenerate() const;

  CGAL_Bbox_2
            bbox() const;

  FT        xmin() const;
  FT        ymin() const;
  FT        xmax() const;
  FT        ymax() const;


protected:

  CGAL__Twotuple< CGAL_PointH2<FT,RT> >*
            ptr() const;
};


template < class FT, class RT >
inline
CGAL__Twotuple< CGAL_PointH2<FT,RT> > *
CGAL_Iso_rectangleH2<FT,RT>::ptr() const
{
 return (CGAL__Twotuple< CGAL_PointH2<FT,RT> >*)PTR;
}


template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>::CGAL_Iso_rectangleH2()
{
 PTR = new CGAL__Twotuple< CGAL_PointH2<FT,RT> >;
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>::CGAL_Iso_rectangleH2(
                                          const CGAL_Iso_rectangleH2<FT,RT> &r)
 : CGAL_Handle((CGAL_Handle&)r)
{
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>::CGAL_Iso_rectangleH2(const CGAL_PointH2<FT,RT> &p,
                                                  const CGAL_PointH2<FT,RT> &q)
{

 bool px_g_qx = ( p.hx()*q.hw() > q.hx()*p.hw() );
 bool py_g_qy = ( p.hy()*q.hw() > q.hy()*p.hw() );

 if ( px_g_qx || py_g_qy)
 {
    if ( px_g_qx && py_g_qy )
    {
        PTR = new CGAL__Twotuple<CGAL_PointH2<FT,RT> >(q,p);
    }
    else
    {
       if ( px_g_qx )
       {
           PTR = new CGAL__Twotuple<CGAL_PointH2<FT,RT> >(
             CGAL_PointH2<FT,RT>(q.hx()*p.hw(), p.hy()*q.hw(), q.hw()*p.hw() ),
             CGAL_PointH2<FT,RT>(p.hx()*q.hw(), q.hy()*p.hw(), q.hw()*p.hw() ));
       }
       if ( py_g_qy )
       {
           PTR = new CGAL__Twotuple<CGAL_PointH2<FT,RT> >(
             CGAL_PointH2<FT,RT>(p.hx()*q.hw(), q.hy()*p.hw(), q.hw()*p.hw() ),
             CGAL_PointH2<FT,RT>(q.hx()*p.hw(), p.hy()*q.hw(), q.hw()*p.hw() ));
       }
    }
 }
 else
 {
    PTR = new CGAL__Twotuple< CGAL_PointH2<FT,RT> >(p,q);
 }
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>::~CGAL_Iso_rectangleH2()
{
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT> &CGAL_Iso_rectangleH2<FT,RT>::operator=(
                                  const CGAL_Iso_rectangleH2<FT,RT> &r)
{
 CGAL_Handle::operator=(r);
 return *this;
}
template < class FT, class RT >
bool
CGAL_Iso_rectangleH2<FT,RT>::operator==(const CGAL_Iso_rectangleH2<FT,RT> &r)
                                                                          const
{
 return  vertex(0) == r.vertex(0) && vertex(2) == r.vertex(2);
}

template < class FT, class RT >
inline
bool
CGAL_Iso_rectangleH2<FT,RT>::operator!=(const CGAL_Iso_rectangleH2<FT,RT> &r)
                                                                          const
{
 return !(*this == r);
}

template < class FT, class RT >
int
CGAL_Iso_rectangleH2<FT,RT>::id() const
{
 return (int)PTR;
}

template < class FT, class RT >
bool
CGAL_Iso_rectangleH2<FT,RT>::identical(const CGAL_Iso_rectangleH2<FT,RT> &r)
                                                                          const
{
 return (PTR == r.PTR);
}
template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::min() const
{
 return  ptr()->e0;
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::max() const
{
 return  ptr()->e1;
}

template < class FT, class RT >
inline
FT
CGAL_Iso_rectangleH2<FT,RT>::xmin() const
{
 return  FT( min().hx() ) / FT( min().hw() );
}

template < class FT, class RT >
inline
FT
CGAL_Iso_rectangleH2<FT,RT>::ymin() const
{
 return  FT( min().hy() ) / FT( min().hw() );
}

template < class FT, class RT >
inline
FT
CGAL_Iso_rectangleH2<FT,RT>::xmax() const
{
 return  FT( max().hx() ) / FT( max().hw() );
}

template < class FT, class RT >
inline
FT
CGAL_Iso_rectangleH2<FT,RT>::ymax() const
{
 return  FT( max().hy() ) / FT( max().hw() );
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::vertex(int i) const
{
 switch (i%4)
 {
    case 0:
        return min();
    case 1:
        return CGAL_PointH2<FT,RT>( max().hx()*min().hw(),
                                    min().hy()*max().hw(),
                                    min().hw()*max().hw() );
    case 2:
        return max();
    case 3:
        return CGAL_PointH2<FT,RT>( min().hx()*max().hw(),
                                    max().hy()*min().hw(),
                                    min().hw()*max().hw() );
 }
 return CGAL_PointH2<FT,RT>();
}

template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::operator[](int i) const
{
 return vertex(i);
}
template < class FT, class RT >
CGAL_Bounded_side
CGAL_Iso_rectangleH2<FT,RT>::bounded_side(const CGAL_PointH2<FT,RT> &p) const
{
 CGAL_Oriented_side wrt_min = CGAL__where_wrt_L_wedge(min(),p);
 CGAL_Oriented_side wrt_max = CGAL__where_wrt_L_wedge(p,max());
 if (( wrt_min == CGAL_ON_NEGATIVE_SIDE )||( wrt_max == CGAL_ON_NEGATIVE_SIDE))
 {
    return CGAL_ON_UNBOUNDED_SIDE;
 }
 if (  ( wrt_min == CGAL_ON_ORIENTED_BOUNDARY )
     ||( wrt_max == CGAL_ON_ORIENTED_BOUNDARY ) )
 {
    return CGAL_ON_BOUNDARY;
 }
 return CGAL_ON_BOUNDED_SIDE;
}

template < class FT, class RT >
inline
bool
CGAL_Iso_rectangleH2<FT,RT>::has_on_boundary(const CGAL_PointH2<FT,RT> &p) const
{
 return ( bounded_side(p) == CGAL_ON_BOUNDARY );
}

template < class FT, class RT >
inline
bool
CGAL_Iso_rectangleH2<FT,RT>::has_on(const CGAL_PointH2<FT,RT> &p) const
{
 return ( bounded_side(p) == CGAL_ON_BOUNDARY );
}

template < class FT, class RT >
inline
bool
CGAL_Iso_rectangleH2<FT,RT>::has_on_bounded_side(const CGAL_PointH2<FT,RT> &p)
                                                                           const
{
 return ( bounded_side(p) == CGAL_ON_BOUNDED_SIDE );
}

template < class FT, class RT >
bool
CGAL_Iso_rectangleH2<FT,RT>::has_on_unbounded_side(const CGAL_PointH2<FT,RT> &p)
                                                                           const
{
 return (  (CGAL__where_wrt_L_wedge(min(),p) == CGAL_ON_NEGATIVE_SIDE)
         ||(CGAL__where_wrt_L_wedge(p,max()) == CGAL_ON_NEGATIVE_SIDE) );
}

template < class FT, class RT >
bool
CGAL_Iso_rectangleH2<FT,RT>::is_degenerate() const
{
 return (   ( min().hx()*max().hw() == max().hx()*min().hw() )
         || ( min().hy()*max().hw() == max().hy()*min().hw() ) );
}
template < class FT, class RT >
CGAL_Bbox_2
CGAL_Iso_rectangleH2<FT,RT>::bbox() const
{
 return  min().bbox() + max().bbox();
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::transform(const CGAL_Aff_transformationH2<FT,RT>&t)
                                                                          const
{
 return CGAL_Iso_rectangleH2<FT,RT>(t.transform(min() ),
                                    t.transform(max() ) );
}


#ifndef CGAL_NO_OSTREAM_INSERT_ISO_RECTANGLEH2
template < class FT, class RT >
ostream &operator<<(ostream &os, const CGAL_Iso_rectangleH2<FT,RT> &r)
{
    switch(os.iword(CGAL_IO::mode)) {
    case CGAL_IO::ASCII :
        return os << r[0] << ' ' << r[1];
    case CGAL_IO::BINARY :
        return os << r[0] << r[1];
    default:
        return os << "Iso_rectangleH2(" << r[0] << ", " << r[2] << ")";
    }
}
#endif // CGAL_NO_OSTREAM_INSERT_ISO_RECTANGLEH2

#ifndef CGAL_NO_ISTREAM_EXTRACT_ISO_RECTANGLEH2
template < class FT, class RT >
istream &operator>>(istream &is, CGAL_Iso_rectangleH2<FT,RT> &r)
{
    CGAL_PointH2<FT,RT> p, q;

    is >> p >> q;
      
    r = CGAL_Iso_rectangleH2<FT,RT>(p, q);
    return is;
}
#endif // CGAL_NO_ISTREAM_EXTRACT_ISO_RECTANGLEH2


#endif // CGAL_ISO_RECTANGLEH2_H
