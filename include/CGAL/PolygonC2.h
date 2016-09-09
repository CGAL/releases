#line 454 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"
// Source: PolygonC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_POLYGONC2_H
#define CGAL_POLYGONC2_H

#include <LEDA/list.h>
#include <LEDA/array.h>

#include <CGAL/SegmentC2.h>

#line 429 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"
template < class T >
class CGAL__Polygon : public handle_rep
{
public:
  array<T >  v_array;
  int convex;  // flag :  false(-1), undefined(0), true(1)
  int simple;  // flag
  CGAL_Ordertype orientation;

  CGAL__Polygon()
    : convex(0), simple(0), orientation(CGAL_COLLINEAR)
  {}

  CGAL__Polygon(const  array<T> &a)
    : v_array(a), convex(0), simple(0), orientation(CGAL_COLLINEAR)
  {}

  ~CGAL__Polygon()
  {}
};
#line 465 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"


#line 10 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"


template < class FT >
class CGAL_PolygonC2 : public handle_base
{
public:
  // constructors, destructor, assignment
  CGAL_PolygonC2();
  CGAL_PolygonC2(const CGAL_PolygonC2<FT> &p);

  CGAL_PolygonC2(const CGAL_TriangleC2<FT> &t);
  CGAL_PolygonC2(const CGAL_Iso_rectangleC2<FT> &r);
  CGAL_PolygonC2(const list<CGAL_PointC2<FT> > &l);
  ~CGAL_PolygonC2();

  CGAL_PolygonC2<FT> &operator=(const CGAL_PolygonC2<FT> &p);

  bool operator==(const CGAL_PolygonC2<FT> &p) const;
  bool operator!=(const CGAL_PolygonC2<FT> &p) const;
  bool identical(const CGAL_PolygonC2<FT> &p) const;

  // access
  list< CGAL_SegmentC2<FT> >    edges() const;
  list< CGAL_PointC2<FT> >      vertices() const;
  CGAL_SegmentC2<FT>            edge(int i) const;
  CGAL_PointC2<FT>              vertex(int i) const;
  CGAL_PointC2<FT>              operator[] (int i) const;
  int                           leftmost_vertex() const;
  FT                            area() const;
  int                           size() const;

  // predicates and ordertype
  bool                          is_convex() const;
  CGAL_Ordertype                orientation() const;

  CGAL_Side                     where_is(const CGAL_PointC2<FT>  &p) const;
  bool                          is_inside(const CGAL_PointC2<FT>  &p) const;
  bool                          is_outside(const CGAL_PointC2<FT>  &p) const;
  bool                          is_on(const CGAL_PointC2<FT>  &p) const;

  CGAL_Bbox_2                   bbox() const;
  CGAL_PolygonC2<FT>            transform(const CGAL_Aff_transformationC2<FT> &t) const;

  bool                          is_degenerate() const;
#ifdef CGAL_CHECK_PRECONDITIONS
  bool                          is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

protected:
  typedef array<CGAL_PointC2<FT> > Array;
  typedef list<CGAL_PointC2<FT> > List;
  Array &vertex_array() const;

private:
  CGAL__Polygon<CGAL_PointC2<FT> >             *ptr() const;

};
#line 467 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"


#line 392 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"

template < class FT >
inline CGAL__Polygon<CGAL_PointC2<FT> >* CGAL_PolygonC2<FT>::ptr() const
{
  return (CGAL__Polygon<CGAL_PointC2<FT> >*)PTR;
}

template < class FT >
inline array<CGAL_PointC2<FT> > &CGAL_PolygonC2<FT>::vertex_array() const
{
  return ptr()->v_array ;
}
#line 469 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"


#line 73 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"

template < class FT >
CGAL_PolygonC2<FT>::CGAL_PolygonC2()
{

#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Polygon<CGAL_PointC2<FT> >;
#endif  // CGAL_CHECK_PRECONDITIONS
}

template < class FT >
CGAL_PolygonC2<FT>::CGAL_PolygonC2(const CGAL_PolygonC2<FT> &p):
  handle_base(p)
{}

template < class FT >
CGAL_PolygonC2<FT>::CGAL_PolygonC2(const list< CGAL_PointC2<FT> > &l)
{
  Array ar(l.length());
  CGAL_PointC2<FT> p;
  int i=0;
  forall(p, l) {
    ar[i] = p;
    i++;
  }
  PTR = new CGAL__Polygon<CGAL_PointC2<FT> >(ar);

}

template < class FT >
CGAL_PolygonC2<FT>::CGAL_PolygonC2(const CGAL_TriangleC2<FT> &t)
{
  Array ar(3);
  for(int i=0; i<3; i++) {
    ar[i] = t[i];
  }
  PTR = new CGAL__Polygon<CGAL_PointC2<FT> >(ar);
}

template < class FT >
CGAL_PolygonC2<FT>::CGAL_PolygonC2(const CGAL_Iso_rectangleC2<FT> &r)
{
  Array ar(4);
  for(int i=0; i<4; i++) {
    ar[i] = r[i];
  }
  PTR = new CGAL__Polygon<CGAL_PointC2<FT> >(ar);
}


template < class FT >
CGAL_PolygonC2<FT> &CGAL_PolygonC2<FT>::operator=(const CGAL_PolygonC2<FT> &p)
{
  handle_base::operator=(p);
  return *this;
}

template < class FT >
CGAL_PolygonC2<FT>::~CGAL_PolygonC2()
{}
#line 140 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"
template < class FT >
bool CGAL_PolygonC2<FT>::operator==(const CGAL_PolygonC2<FT>& p) const
{
  const int &s = size();
  if(s == p.size())
    {
      CGAL_PointC2<FT> point = vertex(0);
      for(int i=0; i<s; i++) {
        if(point == p.vertex(i)) {
          // we have found a common point
          // because polygons are simple we only have to check the remaining
          for(int j = 1; j<s; j++) {
            if(vertex(j) != p.vertex((i+j)%s)) {
              return false;   // different in one point => not equal
            }
          }
          return true;  // because all points are equal
        }
      }
    }
  return false; // because already the # of vertices is different
}

template < class FT >
inline bool CGAL_PolygonC2<FT>::operator!=(const CGAL_PolygonC2<FT>& p) const
{
  return !(*this == p) ;
}

template < class FT >
bool CGAL_PolygonC2<FT>::identical(const CGAL_PolygonC2<FT>& p) const
{

  return PTR == p.PTR ;
}
#line 197 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"
template < class FT >
list< CGAL_PointC2<FT> > CGAL_PolygonC2<FT>::vertices() const
{
  list< CGAL_PointC2<FT> > l;
  for(int i= vertex_array().low(); i<= vertex_array().high(); i++) {
    l.push(vertex(i));
  }
  return l;
}

template < class FT >
list< CGAL_SegmentC2<FT> > CGAL_PolygonC2<FT>::edges() const
{
  list< CGAL_SegmentC2<FT> > l;
  for(int i= vertex_array().low(); i< vertex_array().high(); i++) {
    l.push(CGAL_SegmentC2(vertex(i), vertex(i+1)));
  }
  l.push(CGAL_SegmentC2(vertex(vertex_array().high()), vertex(0)));
  return l;
}

template < class FT >
FT CGAL_PolygonC2<FT>::area() const
{
  const int &s = size();
  FT a = FT(0.0);
  for(int i=1; i<s; i++) {
    a += CGAL_area2(vertex(0), vertex(i), vertex(i+1));
  }
  if (a < FT(0.0)) {
    a = -a;
  }
  return a/FT(2.0);
}


template < class FT >
int CGAL_PolygonC2<FT>::size() const
{
  return vertex_array().high() + 1;
}
#line 246 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"
template < class FT >
CGAL_PointC2<FT> CGAL_PolygonC2<FT>::vertex(int i) const
{ const int&s = size();

  if (i>=s || i < 0){
    i = i %s;   // division is expensive
    if(i<0) {
      i += s;   // for negative wraparound
    }
  }
  return vertex_array().operator[](i);
}

template < class FT >
CGAL_PointC2<FT> CGAL_PolygonC2<FT>::operator[](int i) const
{
  return vertex(i);
}

template < class FT >
int CGAL_PolygonC2<FT>::leftmost_vertex() const
{
  const int &s = size();
  int lm_i = 0;
  for(int i=1; i<s; i++) {
    if (compare(vertex(i), vertex(lm_i)) == CGAL_SMALLER) {
      lm_i = i;
    }
  }
  return lm_i;
}
#line 285 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"
template < class FT >
bool CGAL_PolygonC2<FT>::is_convex() const
{
  const int &s = size();
  if (ptr()->convex == 0)
    {
      CGAL_Ordertype ord = CGAL_ordertype(vertex(0), vertex(1), vertex(2));

      for(int i=1; i<s; i++) {
        if (CGAL_ordertype(vertex(i), vertex(i+1), vertex(i+2)) != ord) {
          ptr()->convex == -1;
          return false;
        }
      }
      // when we arrive here all vertices have the same orientation
      ptr()->convex == 1;
    }
  return true;
}

template < class FT >
CGAL_Ordertype CGAL_PolygonC2<FT>::orientation() const
{
  if (ptr()->orientation == CGAL_COLLINEAR) {
    int i = leftmost_vertex();
    CGAL_Ordertype ord;

    while( (ord = CGAL_ordertype(vertex(i - 1),
                                 vertex(i),
                                 vertex(i + 1)))
           == CGAL_COLLINEAR ) {
      i++;
    }
    ptr()->orientation = ord;
    }
  return ptr()->orientation;
}

template < class FT >
CGAL_Side CGAL_PolygonC2<FT>::where_is(const CGAL_PointC2<FT> &p) const
{

}

template < class FT >
bool CGAL_PolygonC2<FT>::is_inside(const CGAL_PointC2<FT>  &p) const
{
  return where_is(p) == CGAL_INSIDE;
}

template < class FT >
bool CGAL_PolygonC2<FT>::is_outside(const CGAL_PointC2<FT>  &p) const
{
  return where_is(p) == CGAL_OUTSIDE;
}

template < class FT >
bool CGAL_PolygonC2<FT>::is_on(const CGAL_PointC2<FT>  &p) const
{
  return where_is(p) == CGAL_ON;
}
#line 351 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"

template < class FT >
CGAL_Bbox_2 CGAL_PolygonC2<FT>::bbox() const
{
  CGAL_Bbox_2 b = vertex(0).bbox();

  for(int i= 1; i<= size(); i++) {
    b = b + vertex(i).bbox();
  }
  return b;
}

template < class FT >
CGAL_PolygonC2<FT> CGAL_PolygonC2<FT>::transform(const CGAL_Aff_transformationC2<FT> &t) const
{
  List vertexlist;
  for(int i= 1; i<= size(); i++) {
    vertexlist.append(t(vertex(i)));
  }
  return CGAL_PolygonC2<FT>(vertexlist);
}

template < class FT >
bool CGAL_PolygonC2<FT>::is_degenerate() const
{
  cerr << "CGAL_PolygonC2<FT>::is_degenerate() -- not yet implemented" << endl;
  exit(-1);
}

#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT >
bool CGAL_PolygonC2<FT>::is_defined() const
{
  return size() >= 3;
}
#endif // CGAL_CHECK_PRECONDITIONS

#line 471 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"


#line 407 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"

#ifdef CGAL_IO

#include <stream.h>
template < class FT >
ostream &operator<<(ostream &os, CGAL_PolygonC2<FT> &p)
{
  int s = p.size() - 1;
  os << "PolygonC2(" ;
  for(int i = 0; i<= s; i++) {
    os << p.vertex(i) << ", ";
  }
  os  << p.vertex(s+1) << ")";
  return os;
}

#endif  // CGAL_IO
#line 473 "/u/sargas/2/prisme/fabri/Cgal/Kernel/spec/PolygonC2.fw"


#endif  // CGAL_POLYGONC2_H
