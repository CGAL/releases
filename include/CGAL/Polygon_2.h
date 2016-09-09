// Source: Polygon_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_POLYGON_2_H
#define CGAL_POLYGON_2_H

#include <LEDA/list.h>
#include <LEDA/array.h>

#include <CGAL/Segment_2.h>

template < class T >
class CGAL__Polygon : public handle_rep
{
public:
  array< T >  v_array;
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




template < class R >
class CGAL_Polygon_2 : public handle_base
{
public:
  // constructors, destructor, assignment
  CGAL_Polygon_2();
  CGAL_Polygon_2(const CGAL_Polygon_2<R> &p);

  CGAL_Polygon_2(const CGAL_Triangle_2<R> &t);
  CGAL_Polygon_2(const CGAL_Iso_rectangle_2<R> &r);
  CGAL_Polygon_2(const list<CGAL_Point_2<R> > &l);
  ~CGAL_Polygon_2();

  CGAL_Polygon_2<R> &operator=(const CGAL_Polygon_2<R> &p);

  bool operator==(const CGAL_Polygon_2<R> &p) const;
  bool operator!=(const CGAL_Polygon_2<R> &p) const;
  bool identical(const CGAL_Polygon_2<R> &p) const;

  // access
  list< CGAL_Segment_2<R> >    edges() const;
  list< CGAL_Point_2<R> >      vertices() const;
  CGAL_Segment_2<R>            edge(int i) const;
  CGAL_Point_2<R>              vertex(int i) const;
  CGAL_Point_2<R>              operator[] (int i) const;
  int                           leftmost_vertex() const;
  R::RT                         area() const
  {
    const int s = size();
    R::FT a = R::FT(0.0);
    for(int i=1; i<s; i++) {
      a += CGAL_area2(R::Point_2(vertex(0)), R::Point_2(vertex(i)), R::Point_2(vertex(i+1)));
    }
    if (a < R::FT(0.0)) {
      a = -a;
    }
    return a/R::FT(2.0);
  }

  int                           size() const{
  return vertex_array().high() + 1;
}

  // predicates and ordertype
  bool                          is_convex() const
  {
  const int s = size();
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
  CGAL_Ordertype                orientation() const
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

  CGAL_Side                     where_is(const CGAL_Point_2<R>  &p) const;
  bool                          is_inside(const CGAL_Point_2<R>  &p) const;
  bool                          is_outside(const CGAL_Point_2<R>  &p) const;
  bool                          is_on(const CGAL_Point_2<R>  &p) const;

  CGAL_Bbox_2                   bbox() const;
  CGAL_Polygon_2<R>            transform(const CGAL_Aff_transformation_2<R> &t) const;

  bool                          is_degenerate() const;
#ifdef CGAL_CHECK_PRECONDITIONS
  bool                          is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

private:
  typedef list<CGAL_Point_2<R> > List;
  array<CGAL_Point_2<R> > &vertex_array() const
  {
  return ptr()->v_array ;
}

  CGAL__Polygon<CGAL_Point_2<R> >             *ptr() const{
  return (CGAL__Polygon<CGAL_Point_2<R> >*)PTR;
};

};


/*
template < class R >
inline CGAL__Polygon<CGAL_Point_2<R> >* CGAL_Polygon_2<R>::ptr() const
{
  return (CGAL__Polygon<CGAL_Point_2<R> >*)PTR;
}

template < class R >
array<CGAL_Point_2<R> > &CGAL_Polygon_2<R>::vertex_array() const
{
  return ptr()->v_array ;
}
*/



template < class R >
CGAL_Polygon_2<R>::CGAL_Polygon_2()
{

#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Polygon<CGAL_Point_2<R> >;
#endif  // CGAL_CHECK_PRECONDITIONS
}

template < class R >
CGAL_Polygon_2<R>::CGAL_Polygon_2(const CGAL_Polygon_2<R> &p):
  handle_base(p)
{}

template < class R >
CGAL_Polygon_2<R>::CGAL_Polygon_2(const list< CGAL_Point_2<R> > &l)
{
  array<CGAL_Point_2<R> > ar(l.length());
  CGAL_Point_2<R> p;
  int i=0;
  forall(p, l) {
    ar[i] = p;
    i++;
  }
  PTR = new CGAL__Polygon<CGAL_Point_2<R> >(ar);

}

template < class R >
CGAL_Polygon_2<R>::CGAL_Polygon_2(const CGAL_Triangle_2<R> &t)
{
  array<CGAL_Point_2<R> >  ar(3);
  for(int i=0; i<3; i++) {
    ar[i] = t[i];
  }
  PTR = new CGAL__Polygon<CGAL_Point_2<R> >(ar);
}

template < class R >
CGAL_Polygon_2<R>::CGAL_Polygon_2(const CGAL_Iso_rectangle_2<R> &r)
{
  array<CGAL_Point_2<R> >  ar(4);
  for(int i=0; i<4; i++) {
    ar[i] = r[i];
  }
  PTR = new CGAL__Polygon<CGAL_Point_2<R> >(ar);
}


template < class R >
CGAL_Polygon_2<R> &CGAL_Polygon_2<R>::operator=(const CGAL_Polygon_2<R> &p)
{
  handle_base::operator=(p);
  return *this;
}

template < class R >
CGAL_Polygon_2<R>::~CGAL_Polygon_2()
{}
template < class R >
bool CGAL_Polygon_2<R>::operator==(const CGAL_Polygon_2<R>& p) const
{
  const int s = size();
  if(s == p.size())
    {
      CGAL_Point_2<R> point = vertex(0);
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

template < class R >
inline bool CGAL_Polygon_2<R>::operator!=(const CGAL_Polygon_2<R>& p) const
{
  return !(*this == p) ;
}

template < class R >
bool CGAL_Polygon_2<R>::identical(const CGAL_Polygon_2<R>& p) const
{

  return PTR == p.PTR ;
}
template < class R >
list< CGAL_Point_2<R> > CGAL_Polygon_2<R>::vertices() const
{
  list< CGAL_Point_2<R> > l;
  for(int i= vertex_array().low(); i<= vertex_array().high(); i++) {
    l.push(vertex(i));
  }
  return l;
}

template < class R >
list< CGAL_Segment_2<R> > CGAL_Polygon_2<R>::edges() const
{
  list< CGAL_Segment_2<R> > l;

  for(int i= vertex_array().low(); i< vertex_array().high(); i++) {
    l.push(CGAL_Segment_2<R>(vertex(i), vertex(i+1)));
  }
  l.push(CGAL_Segment_2<R>(vertex(vertex_array().high()), vertex(0)));

  return l;
}


/*
template < class R >
int CGAL_Polygon_2<R>::size() const
{
  return vertex_array().high() + 1;
}
*/
template < class R >
CGAL_Point_2<R> CGAL_Polygon_2<R>::vertex(int i) const
{ const int s = size();

  if (i>=s || i < 0){
    i = i %s;   // division is expensive
    if(i<0) {
      i += s;   // for negative wraparound
    }
  }
  return vertex_array().operator[](i);
}

template < class R >
CGAL_Point_2<R> CGAL_Polygon_2<R>::operator[](int i) const
{
  return vertex(i);
}

template < class R >
int CGAL_Polygon_2<R>::leftmost_vertex() const
{
  const int s = size();
  int lm_i = 0;
  for(int i=1; i<s; i++) {
    if (compare(vertex(i), vertex(lm_i)) == CGAL_SMALLER) {
      lm_i = i;
    }
  }
  return lm_i;
}
/*
template < class R >
bool CGAL_Polygon_2<R>::is_convex() const
{
  const int s = size();
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
*/
/*
template < class R >
CGAL_Ordertype CGAL_Polygon_2<R>::orientation() const
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
*/
template < class R >
CGAL_Side CGAL_Polygon_2<R>::where_is(const CGAL_Point_2<R> &p) const
{

}

template < class R >
bool CGAL_Polygon_2<R>::is_inside(const CGAL_Point_2<R>  &p) const
{
  return where_is(p) == CGAL_INSIDE;
}

template < class R >
bool CGAL_Polygon_2<R>::is_outside(const CGAL_Point_2<R>  &p) const
{
  return where_is(p) == CGAL_OUTSIDE;
}

template < class R >
bool CGAL_Polygon_2<R>::is_on(const CGAL_Point_2<R>  &p) const
{
  return where_is(p) == CGAL_ON;
}

template < class R >
CGAL_Bbox_2 CGAL_Polygon_2<R>::bbox() const
{
  CGAL_Bbox_2 b = vertex(0).bbox();

  for(int i= 1; i<= size(); i++) {
    b = b + vertex(i).bbox();
  }
  return b;
}

template < class R >
CGAL_Polygon_2<R> CGAL_Polygon_2<R>::transform(const CGAL_Aff_transformation_2<R> &t) const
{
  List vertexlist;
  for(int i= 1; i<= size(); i++) {
    vertexlist.append(t(vertex(i)));
  }
  return CGAL_Polygon_2<R>(vertexlist);
}

template < class R >
bool CGAL_Polygon_2<R>::is_degenerate() const
{
  cerr << "CGAL_Polygon_2<R>::is_degenerate() -- not yet implemented" << endl;
  exit(-1);
}

#ifdef CGAL_CHECK_PRECONDITIONS
template < class R >
bool CGAL_Polygon_2<R>::is_defined() const
{
  return size() >= 3;
}
#endif // CGAL_CHECK_PRECONDITIONS




#ifdef CGAL_IO

#include <stream.h>
template < class R >
ostream &operator<<(ostream &os, CGAL_Polygon_2<R> &p)
{
  int s = p.size() - 1;
  os << "Polygon_2(" ;
  for(int i = 0; i<= s; i++) {
    os << p.vertex(i) << ", ";
  }
  os  << p.vertex(s+1) << ")";
  return os;
}

#endif  // CGAL_IO


#endif  // CGAL_POLYGON_2_H
