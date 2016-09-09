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

// Source: TriangleC3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_TRIANGLEC3_H
#define CGAL_TRIANGLEC3_H

#include <CGAL/PlaneC3.h>
#include <CGAL/solve.h>

template <class FT>
class CGAL_TriangleC3 : public CGAL_Handle
{
public:
                      CGAL_TriangleC3();
                      CGAL_TriangleC3(const CGAL_TriangleC3<FT> &t);
                      CGAL_TriangleC3(const CGAL_PointC3<FT> &p,
                                      const CGAL_PointC3<FT> &q,
                                      const CGAL_PointC3<FT> &r);

                      ~CGAL_TriangleC3();

  CGAL_TriangleC3<FT> &operator=(const CGAL_TriangleC3<FT> &t);

  bool                operator==(const CGAL_TriangleC3<FT> &t) const;
  bool                operator!=(const CGAL_TriangleC3<FT> &t) const;
  int                 id() const;

  CGAL_PlaneC3<FT>    supporting_plane() const;


  CGAL_TriangleC3     transform(const CGAL_Aff_transformationC3<FT> &t) const;

  bool                has_on(const CGAL_PointC3<FT> &p) const;
  bool                is_degenerate() const;


  CGAL_PointC3<FT>    vertex(int i) const;
  CGAL_PointC3<FT>    operator[](int i) const;

  CGAL_Bbox_3         bbox() const;

private:
  CGAL__Threetuple< CGAL_PointC3<FT> >*   ptr() const;
};


template < class FT >
inline CGAL__Threetuple< CGAL_PointC3<FT> > *CGAL_TriangleC3<FT>::ptr() const
{
  return (CGAL__Threetuple< CGAL_PointC3<FT> >*)PTR;
}


template < class FT >
CGAL_TriangleC3<FT>::CGAL_TriangleC3()
{
  PTR = new CGAL__Threetuple< CGAL_PointC3<FT> >;
}

template < class FT >
CGAL_TriangleC3<FT>::CGAL_TriangleC3(const CGAL_TriangleC3<FT> &t) :
  CGAL_Handle(t)
{}

template < class FT >
CGAL_TriangleC3<FT>::CGAL_TriangleC3(const CGAL_PointC3<FT> &p,
                                 const CGAL_PointC3<FT> &q,
                                 const CGAL_PointC3<FT> &r)
{
  PTR = new CGAL__Threetuple< CGAL_PointC3<FT> >(p, q, r);
   CGAL_nondegeneracy_assertion;
}

template < class FT >
inline CGAL_TriangleC3<FT>::~CGAL_TriangleC3()
{}


template < class FT >
CGAL_TriangleC3<FT> &CGAL_TriangleC3<FT>::operator=(
                                                const CGAL_TriangleC3<FT> &t)
{
  CGAL_Handle::operator=(t);
  return *this;
}
template < class FT >
bool CGAL_TriangleC3<FT>::operator==(const CGAL_TriangleC3<FT> &t) const
{
  int i;
  bool eq = false;
  for(i = 0; i <= 2; i++)
    {
      if( vertex(0) == t.vertex(i) )
        {
          eq = true;
          break;
        }
    }
  if ( eq )
    {
      return ( vertex(1) == t.vertex(i+1) && vertex(2) == t.vertex(i+2) );
    }
  return false;
}

template < class FT >
inline bool CGAL_TriangleC3<FT>::operator!=(const CGAL_TriangleC3<FT> &t) const
{
  return !(*this == t);
}

template < class FT >
int CGAL_TriangleC3<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
CGAL_PointC3<FT> CGAL_TriangleC3<FT>::vertex(int i) const
{

  switch (i)
    {
    case 0: return ptr()->e0;
    case 1: return ptr()->e1;
    case 2: return ptr()->e2;
    default: switch (i%3)
               {
               case 0: return ptr()->e0;
               case 1: return ptr()->e1;
               }
    }
  return ptr()->e2;
}

template < class FT >
inline CGAL_PointC3<FT> CGAL_TriangleC3<FT>::operator[](int i) const
{

  return vertex(i);
}

template < class FT >
inline CGAL_PlaneC3<FT> CGAL_TriangleC3<FT>::supporting_plane() const
{

  return CGAL_PlaneC3<FT>(vertex(0), vertex(1), vertex(2));
}

template < class FT >
CGAL_Bbox_3 CGAL_TriangleC3<FT>::bbox() const
{

  return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}


template < class FT >
inline CGAL_TriangleC3<FT> CGAL_TriangleC3<FT>::transform(
                                 const CGAL_Aff_transformationC3<FT> &t) const
{
  return CGAL_TriangleC3<FT>(t.transform(vertex(0)),
                             t.transform(vertex(1)),
                             t.transform(vertex(2)));
}
template < class FT >
bool CGAL_TriangleC3<FT>::has_on(const CGAL_PointC3<FT> &p) const
{
  CGAL_PointC3<FT> o = vertex(0) + supporting_plane().orthogonal_vector();
  CGAL_VectorC3<FT> v0 = vertex(0)-o,
                    v1 = vertex(1)-o,
                    v2 = vertex(2)-o;

  FT alpha, beta, gamma;

  CGAL_solve(v0, v1, v2, p-o, alpha, beta, gamma);

  return ((alpha >= FT(0)) && (beta >= FT(0))
          && (gamma >= FT(0)) && ((alpha+beta+gamma == FT(1))));
}

template < class FT >
bool CGAL_TriangleC3<FT>::is_degenerate() const
{
  return CGAL_collinear(vertex(0),vertex(1),vertex(2));
}



#endif
