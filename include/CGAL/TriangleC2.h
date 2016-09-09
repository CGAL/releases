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

#ifdef CGAL_TO_DOUBLE
                      operator CGAL_TriangleC2<double>() const;
#endif // CGAL_TO_DOUBLE

  CGAL_TriangleC2<FT> &operator=(const CGAL_TriangleC2<FT> &t);

  bool                operator==(const CGAL_TriangleC2<FT> &s) const;
  bool                operator!=(const CGAL_TriangleC2<FT> &s) const;
  bool                identical(const CGAL_TriangleC2<FT> &s) const;

  CGAL_PointC2<FT>    vertex(int i) const;
  CGAL_PointC2<FT>    operator[](int i) const;


  CGAL_TriangleC2     transform(const CGAL_Aff_transformationC2<FT> &t) const;

  CGAL_Side           where_is(const CGAL_PointC2<FT> &p) const;
  bool                is_on(const CGAL_PointC2<FT> &p) const;
  bool                is_inside(const CGAL_PointC2<FT> &p) const;
  bool                is_outside(const CGAL_PointC2<FT> &p) const;
  bool                is_degenerate() const;

  CGAL_Bbox_2         bbox() const;

#ifdef CGAL_CHECK_PRECONDITIONS
  bool             is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

private:
  CGAL__Threetuple< CGAL_PointC2<FT> >*   ptr() const;
};


#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT >
inline bool CGAL_TriangleC2<FT>::is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_CHECK_PRECONDITIONS

template < class FT >
inline CGAL__Threetuple< CGAL_PointC2<FT> > *CGAL_TriangleC2<FT>::ptr() const
{
  return (CGAL__Threetuple< CGAL_PointC2<FT> >*)PTR;
}


template < class FT >
CGAL_TriangleC2<FT>::CGAL_TriangleC2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Threetuple< CGAL_PointC2<FT> >;
#endif  // CGAL_CHECK_PRECONDITIONS
}

template < class FT >
CGAL_TriangleC2<FT>::CGAL_TriangleC2(const CGAL_TriangleC2<FT> &t) :
  handle_base((handle_base&)t)
{
  CGAL_kernel_precondition(t.is_defined());
}

template < class FT >
CGAL_TriangleC2<FT>::CGAL_TriangleC2(const CGAL_PointC2<FT> &p,
                                     const CGAL_PointC2<FT> &q,
                                     const CGAL_PointC2<FT> &r)
{
  CGAL_kernel_precondition(p.is_defined() && q.is_defined() && r.is_defined());
  PTR = new CGAL__Threetuple< CGAL_PointC2<FT> >(p, q, r);
  CGAL_nondegeneracy_assertion;
}

template < class FT >
inline CGAL_TriangleC2<FT>::~CGAL_TriangleC2()
{}

#ifdef CGAL_TO_DOUBLE
template < class FT >
CGAL_TriangleC2<FT>::operator CGAL_TriangleC2<double>() const
{
  return CGAL_TriangleC2<double>(vertex(0), vertex(1), vertex(2));
}
#endif // CGAL_TO_DOUBLE

template < class FT >
CGAL_TriangleC2<FT> &CGAL_TriangleC2<FT>::operator=(
                                               const CGAL_TriangleC2<FT> &t)
{
  CGAL_kernel_precondition( t.is_defined() );
  handle_base::operator=(t);
  return *this;
}
template < class FT >
bool CGAL_TriangleC2<FT>::operator==(const CGAL_TriangleC2<FT> &t) const
{
  CGAL_kernel_precondition( is_defined() && t.is_defined() );
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
  CGAL_kernel_precondition( is_defined() && t.is_defined() );
  return !(*this == t);
}

template < class FT >
bool CGAL_TriangleC2<FT>::identical(const CGAL_TriangleC2<FT> &t) const
{
  CGAL_kernel_precondition( is_defined() && t.is_defined() );
  return (PTR == t.PTR);
}
template < class FT >
CGAL_PointC2<FT> CGAL_TriangleC2<FT>::vertex(int i) const
{
  CGAL_kernel_precondition( is_defined() );
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
  CGAL_kernel_precondition( is_defined() );
  return vertex(i);
}
template < class FT >
CGAL_Side CGAL_TriangleC2<FT>::where_is(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );

  // depends on the orientation of the vertices
  CGAL_Ordertype o1 = CGAL_ordertype(vertex(0), vertex(1), p),
                 o2 = CGAL_ordertype(vertex(1), vertex(2), p),
                 o3 = CGAL_ordertype(vertex(2), vertex(3), p);

 if (o1 == CGAL_COLLINEAR || o2 == CGAL_COLLINEAR || o3 == CGAL_COLLINEAR)
    {
      if ((o1 == CGAL_COLLINEAR && CGAL_collinear_between(
                                                  vertex(0), p, vertex(1))) ||
          (o2 == CGAL_COLLINEAR && CGAL_collinear_between(
                                                  vertex(1), p, vertex(2))) ||
          (o3 == CGAL_COLLINEAR && CGAL_collinear_between(
                                                  vertex(2), p, vertex(3))))
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
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  return where_is(p) == CGAL_ON;
}

template < class FT >
inline bool CGAL_TriangleC2<FT>::is_inside(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  return where_is(p) == CGAL_INSIDE;
}

template < class FT >
inline bool CGAL_TriangleC2<FT>::is_outside(const CGAL_PointC2<FT> &p) const
{
  CGAL_kernel_precondition( is_defined() && p.is_defined() );
  return where_is(p) == CGAL_OUTSIDE;
}

template < class FT >
bool CGAL_TriangleC2<FT>::is_degenerate() const
{
  CGAL_kernel_precondition( is_defined() );
  return CGAL_collinear(vertex(0), vertex(1), vertex(2));
}
template < class FT >
inline CGAL_Bbox_2 CGAL_TriangleC2<FT>::bbox() const
{
  CGAL_kernel_precondition( is_defined() );
  return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}


template < class FT >
inline CGAL_TriangleC2<FT> CGAL_TriangleC2<FT>::transform(
                                 const CGAL_Aff_transformationC2<FT> &t) const
{
  CGAL_kernel_precondition( is_defined() && t.is_defined() );
  return CGAL_TriangleC2<FT>(t.transform(vertex(0)),
                            t.transform(vertex(1)),
                            t.transform(vertex(2)));
}




#ifdef CGAL_IO

template < class FT >
ostream &operator<<(ostream &os, const CGAL_TriangleC2<FT> &t)
{
  os << "TriangleC2(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<")";
  return os;
}

#endif

#endif
