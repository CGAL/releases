// Source: TriangleC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_TRIANGLEC2_H
#define CGAL_TRIANGLEC2_H

#include <CGAL/Threetuple.h>
#include <CGAL/OrdertypeC2.h>

template <class FT>
class CGAL_TriangleC2 : public handle_base
{
public:
                      CGAL_TriangleC2();
                      CGAL_TriangleC2(const CGAL_TriangleC2<FT> &);
                      CGAL_TriangleC2(const CGAL_PointC2<FT> &p,
                                     const CGAL_PointC2<FT> &q,
                                     const CGAL_PointC2<FT> &r);
                      ~CGAL_TriangleC2();
                      operator CGAL_TriangleC2<double>() const;
  CGAL_TriangleC2<FT>  &operator=(const CGAL_TriangleC2<FT> &t);

  bool                operator==(const CGAL_TriangleC2<FT> &s) const;
  bool                operator!=(const CGAL_TriangleC2<FT> &s) const;
  bool                identical(const CGAL_TriangleC2<FT> &s) const;

  CGAL_PointC2<FT>     vertex(int i) const;
  CGAL_PointC2<FT>     operator[](int i) const;

  CGAL_TriangleC2      transform(const CGAL_Aff_transformation_baseC2<FT> &t) const;

  CGAL_Side           where_is(const CGAL_PointC2<FT> &p) const;
  bool                is_on(const CGAL_PointC2<FT> &p) const;
  bool                is_inside(const CGAL_PointC2<FT> &p) const;
  bool                is_outside(const CGAL_PointC2<FT> &p) const;
  bool                is_degenerate() const;

  CGAL_Bbox_2           bbox() const;

private:
  CGAL__Threetuple< CGAL_PointC2<FT> >*   ptr() const;
};


template < class FT >
inline CGAL__Threetuple< CGAL_PointC2<FT> > *CGAL_TriangleC2<FT>::ptr() const
{
  return (CGAL__Threetuple< CGAL_PointC2<FT> >*)PTR;
}


template < class FT >
CGAL_TriangleC2<FT>::CGAL_TriangleC2()
{
  PTR = new CGAL__Threetuple< CGAL_PointC2<FT> >;
}

template < class FT >
CGAL_TriangleC2<FT>::CGAL_TriangleC2(const CGAL_TriangleC2<FT> &t) :
  handle_base(t)
{}

template < class FT >
CGAL_TriangleC2<FT>::CGAL_TriangleC2(const CGAL_PointC2<FT> &p,
                                   const CGAL_PointC2<FT> &q,
                                   const CGAL_PointC2<FT> &r)
{
  PTR = new CGAL__Threetuple< CGAL_PointC2<FT> >(p, q, r);
  assert( ! is_degenerate() );
}

template < class FT >
inline CGAL_TriangleC2<FT>::~CGAL_TriangleC2()
{}

template < class FT >
CGAL_TriangleC2<FT>::operator CGAL_TriangleC2<double>() const
{
  return CGAL_TriangleC2<double>(vertex(0), vertex(1), vertex(2));
}

template < class FT >
CGAL_TriangleC2<FT> &CGAL_TriangleC2<FT>::operator=(const CGAL_TriangleC2<FT> &p)
{
  handle_base::operator=(p);
  return *this;
}
template < class FT >
bool CGAL_TriangleC2<FT>::operator==(const CGAL_TriangleC2<FT> &t) const
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
inline bool CGAL_TriangleC2<FT>::operator!=(const CGAL_TriangleC2<FT> &t) const
{
  return !(*this == t);
}

template < class FT >
bool CGAL_TriangleC2<FT>::identical(const CGAL_TriangleC2<FT> &t) const
{
  return (PTR == t.PTR);
}
template < class FT >
CGAL_PointC2<FT> CGAL_TriangleC2<FT>::vertex(int i) const
{
  switch (i)
    {
    case 0: return ptr()->e0;
    case 1: return ptr()->e1;
    case 2: return ptr()->e2;
    default:switch (i%3)
             {
             case 0: return ptr()->e0;
             case 1: return ptr()->e1;
             default: return ptr()->e2;
             }
    }
}

template < class FT >
inline CGAL_PointC2<FT> CGAL_TriangleC2<FT>::operator[](int i) const
{
  return vertex(i);
}
template < class FT >
CGAL_Side CGAL_TriangleC2<FT>::where_is(const CGAL_PointC2<FT> &p) const
{// depends on the orientation of the vertices
  CGAL_Ordertype o1 = CGAL_ordertype(vertex(0), vertex(1), p),
                 o2 = CGAL_ordertype(vertex(1), vertex(2), p),
                 o3 = CGAL_ordertype(vertex(2), vertex(3), p);

 if (o1 == CGAL_COLLINEAR || o2 == CGAL_COLLINEAR || o3 == CGAL_COLLINEAR)
    {
      if ((o1 == CGAL_COLLINEAR && CGAL_collinear_between(vertex(0), vertex(1), p)) ||
          (o2 == CGAL_COLLINEAR && CGAL_collinear_between(vertex(1), vertex(2), p)) ||
          (o3 == CGAL_COLLINEAR && CGAL_collinear_between(vertex(2), vertex(3), p)))
        {
          return CGAL_ON;
        }
      return CGAL_OUTSIDE;
    }
  if (CGAL_rightturn(vertex(0), vertex(1), vertex(2)))
    {
      if (o1 == CGAL_RIGHTTURN && o2 == CGAL_RIGHTTURN && o3 == CGAL_RIGHTTURN)
        {
          return CGAL_INSIDE;
        }
      return CGAL_OUTSIDE;
    }

  if (o1 == CGAL_LEFTTURN && o2 == CGAL_LEFTTURN && o3 == CGAL_LEFTTURN)
    {
      return CGAL_INSIDE;
    }
  return CGAL_OUTSIDE;
}

template < class FT >
inline bool CGAL_TriangleC2<FT>::is_on(const CGAL_PointC2<FT> &p) const
{
  return where_is(p) == CGAL_ON;
}

template < class FT >
inline bool CGAL_TriangleC2<FT>::is_inside(const CGAL_PointC2<FT> &p) const
{
  return where_is(p) == CGAL_INSIDE;
}

template < class FT >
inline bool CGAL_TriangleC2<FT>::is_outside(const CGAL_PointC2<FT> &p) const
{
  return where_is(p) == CGAL_OUTSIDE;
}

template < class FT >
bool CGAL_TriangleC2<FT>::is_degenerate() const
{
  return CGAL_collinear(vertex(0), vertex(1), vertex(2));
}
template < class FT >
inline CGAL_Bbox_2 CGAL_TriangleC2<FT>::bbox() const
{
  return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}

template < class FT >
inline CGAL_TriangleC2<FT> CGAL_TriangleC2<FT>::transform(const CGAL_Aff_transformation_baseC2<FT> &t) const
{
  return CGAL_TriangleC2<FT>(t.transform(vertex(0)),
                            t.transform(vertex(1)),
                            t.transform(vertex(2)));
}



#ifdef CGAL_IO

#include <stream.h>

template < class FT >
ostream &operator<<(ostream &os, CGAL_TriangleC2<FT> &t)
{
  os << "TriangleC2(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
  return os;
}

#endif

#endif
