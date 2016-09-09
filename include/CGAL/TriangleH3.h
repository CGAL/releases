//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: TriangleH3.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_TRIANGLEH3_H
#define CGAL_TRIANGLEH3_H

#include <CGAL/predicates_on_pointsH3.h>
#include <CGAL/PlaneH3.h>
#include <CGAL/TetrahedronH3.h>

template < class FT, class RT >
class CGAL_TriangleH3 : public CGAL_Handle
{
public:
                      CGAL_TriangleH3();
                      CGAL_TriangleH3(const CGAL_TriangleH3<FT,RT> &t);
                      CGAL_TriangleH3(const CGAL_PointH3<FT,RT> &p,
                                      const CGAL_PointH3<FT,RT> &q,
                                      const CGAL_PointH3<FT,RT> &r);

                      ~CGAL_TriangleH3();

  CGAL_TriangleH3<FT,RT> &
                      operator=(const CGAL_TriangleH3<FT,RT> &t);

  bool                operator==(const CGAL_TriangleH3<FT,RT> &t) const;
  bool                operator!=(const CGAL_TriangleH3<FT,RT> &t) const;
  bool                identical(const CGAL_TriangleH3<FT,RT> &t) const;
  int                 id() const;

  CGAL_PlaneH3<FT,RT> supporting_plane() const;

  CGAL_TriangleH3     transform(const CGAL_Aff_transformationH3<FT,RT> &t)
                                                                         const;
  bool                has_on(const CGAL_PointH3<FT,RT> &p) const;
  bool                nondegenerate_has_on(const CGAL_PointH3<FT,RT> &p) const;
  bool                is_degenerate() const;


  CGAL_PointH3<FT,RT> vertex(int i) const;
  CGAL_PointH3<FT,RT> operator[](int i) const;

  CGAL_Bbox_3         bbox() const;

private:
  CGAL__Threetuple< CGAL_PointH3<FT,RT> >*   ptr() const;
};


template < class FT, class RT >
inline
CGAL__Threetuple< CGAL_PointH3<FT,RT> > *
CGAL_TriangleH3<FT,RT>::ptr() const
{
 return (CGAL__Threetuple< CGAL_PointH3<FT,RT> >*)PTR;
}

template < class FT, class RT >
inline
CGAL_TriangleH3<FT,RT>::~CGAL_TriangleH3()
{
}
template < class FT, class RT >
inline
bool
CGAL_TriangleH3<FT,RT>::operator!=(const CGAL_TriangleH3<FT,RT> &t) const
{
 return !(*this == t);
}
template < class FT, class RT >
inline
CGAL_PointH3<FT,RT>
CGAL_TriangleH3<FT,RT>::operator[](int i) const
{
 return vertex(i);
}

template < class FT, class RT >
CGAL_TriangleH3<FT,RT>::CGAL_TriangleH3()
{
 PTR = new CGAL__Threetuple< CGAL_PointH3<FT,RT> >;
}

template < class FT, class RT >
CGAL_TriangleH3<FT,RT>::CGAL_TriangleH3(const CGAL_TriangleH3<FT,RT> &t)
 : CGAL_Handle( (CGAL_Handle&) t)
{
}

template < class FT, class RT >
CGAL_TriangleH3<FT,RT>::CGAL_TriangleH3(const CGAL_PointH3<FT,RT> &p,
                                        const CGAL_PointH3<FT,RT> &q,
                                        const CGAL_PointH3<FT,RT> &r)
{
 PTR = new CGAL__Threetuple< CGAL_PointH3<FT,RT> >(p, q, r);
}

template < class FT, class RT >
CGAL_TriangleH3<FT,RT> &
CGAL_TriangleH3<FT,RT>::operator=(const CGAL_TriangleH3<FT,RT> &t)
{
 CGAL_Handle::operator=(t);
 return *this;
}
template < class FT, class RT >
bool
CGAL_TriangleH3<FT,RT>::operator==(const CGAL_TriangleH3<FT,RT> &t) const
{
 int i;
 for(i = 0; (i< 3) && (vertex(0) != t.vertex(i) ); i++)
 {
 }
 if (i==3)
 {
    return false;
 }
 return ( vertex(1) == t.vertex(i+1) && vertex(2) == t.vertex(i+2) );
}

template < class FT, class RT >
bool
CGAL_TriangleH3<FT,RT>::identical(const CGAL_TriangleH3<FT,RT> &t) const
{
 return PTR == t.PTR;
}

template < class FT, class RT >
int
CGAL_TriangleH3<FT,RT>::id() const
{
 return (int) PTR ;
}
template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_TriangleH3<FT,RT>::vertex(int i) const
{
 switch (i)
 {
    case 0:  return ptr()->e0;
    case 1:  return ptr()->e1;
    case 2:  return ptr()->e2;
    default: return vertex(i%3);
 }
 return CGAL_PointH3<FT,RT>();
}
template < class FT, class RT >
CGAL_PlaneH3<FT,RT>
CGAL_TriangleH3<FT,RT>::supporting_plane() const
{
 return CGAL_PlaneH3<FT,RT>(vertex(0), vertex(1), vertex(2));
}

template < class FT, class RT >
CGAL_Bbox_3
CGAL_TriangleH3<FT,RT>::bbox() const
{
  return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}

template < class FT, class RT >
CGAL_TriangleH3<FT,RT>
CGAL_TriangleH3<FT,RT>::transform(const CGAL_Aff_transformationH3<FT,RT> &t)
                                                                         const
{
  return CGAL_TriangleH3<FT,RT>(t.transform(vertex(0)),
                                t.transform(vertex(1)),
                                t.transform(vertex(2)));
}
template < class FT, class RT >
bool
CGAL_TriangleH3<FT,RT>::nondegenerate_has_on(const CGAL_PointH3<FT,RT> &p) const
{
 CGAL_kernel_precondition( !is_degenerate() );
 CGAL_PlaneH3<FT,RT> sup_pl = supporting_plane();
 if ( !sup_pl.has_on(p) )
 {
    return false;
 }
 CGAL_TetrahedronH3<FT,RT> tetrapak( vertex(0),
                                     vertex(1),
                                     vertex(2),
                                     vertex(0) + sup_pl.orthogonal_vector() );
 return tetrapak.has_on_boundary(p);
}

template < class FT, class RT >
bool
CGAL_TriangleH3<FT,RT>::has_on(const CGAL_PointH3<FT,RT> &p) const
{
 if (!is_degenerate() )
 {
    return nondegenerate_has_on(p);
 }
 CGAL_PointH3<FT,RT> minp( vertex(0) );
 CGAL_PointH3<FT,RT> maxp( vertex(1) );
 if (CGAL_lexicographically_xyz_smaller(vertex(1),vertex(0)) )
 {
    minp = vertex(1);
    maxp = vertex(0);
 }
 if (CGAL_lexicographically_xyz_smaller(vertex(2),minp ) )
 {
    minp = vertex(2);
 }
 if (CGAL_lexicographically_xyz_smaller(maxp, vertex(2)) )
 {
    maxp = vertex(2);
 }
 if (minp == maxp)
 {
    return (p == maxp);
 }
 CGAL_SegmentH3<FT,RT> s(minp,maxp);
 return s.has_on(p);
}

template < class FT, class RT >
bool
CGAL_TriangleH3<FT,RT>::is_degenerate() const
{
 return CGAL_collinear(vertex(0),vertex(1),vertex(2));
}


#endif // CGAL_TRIANGLEH3_H
