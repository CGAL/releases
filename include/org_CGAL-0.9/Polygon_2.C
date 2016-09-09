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


// Source: Polygon_2.C
// Author: Wieger Wesselink

#include <CGAL/Segment_2_Segment_2_intersection.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/number_utils.h>

#include <stdlib.h>
#include <algobase.h>
#include <algo.h>
#include <set.h>
#include <vector.h>

//-----------------------------------------------------------------------//
//                          CGAL_cross_product_2
//-----------------------------------------------------------------------//

#ifdef CGAL_CARTESIAN_H
template <class FT>
static inline
FT CGAL_cross_product_2(const CGAL_Vector_2<CGAL_Cartesian<FT> >& p,
                        const CGAL_Vector_2<CGAL_Cartesian<FT> >& q)
{
  return (p.x() * q.y() - q.x() * p.y());
}
#endif

//-----------------------------------------------------//
// This doesn't work on Sun/CC
//
// #ifdef CGAL_HOMOGENEOUS_H
// #include <CGAL/workaround_010.h>
// template <class RT>
// static inline
// R_FT_return(CGAL_Homogeneous<RT>)
// CGAL_cross_product_2(
//         const CGAL_Vector_2<CGAL_Homogeneous<RT> >& p,
//         const CGAL_Vector_2<CGAL_Homogeneous<RT> >& q)
// {
//   return R_FT_return(CGAL_Homogeneous<RT>)(p.x() * q.y() - q.x() * p.y());
// }
// #endif
//-----------------------------------------------------//

#ifdef CGAL_HOMOGENEOUS_H
template <class FT>
static inline
FT CGAL_cross_product_2(const CGAL_Vector_2<CGAL_Homogeneous<FT> >& p,
                        const CGAL_Vector_2<CGAL_Homogeneous<FT> >& q)
{
  return FT(p.hx()/p.hw()) * FT(q.hy()/q.hw()) -
         FT(q.hx()/q.hw()) * FT(p.hy()/p.hw());
}
#endif

//-----------------------------------------------------------------------//
//                          CGAL_determinant_2
//-----------------------------------------------------------------------//

#ifdef CGAL_CARTESIAN_H
template <class FT>
static inline
FT CGAL_determinant_2(const CGAL_Point_2<CGAL_Cartesian<FT> >& p,
                      const CGAL_Point_2<CGAL_Cartesian<FT> >& q,
                      const CGAL_Point_2<CGAL_Cartesian<FT> >& r)
{
  return CGAL_cross_product_2(p-q, p-r);
}
#endif

//-----------------------------------------------------//
// This doesn't work on Sun/CC
//
// #ifdef CGAL_HOMOGENEOUS_H
// #include <CGAL/workaround_010.h>
// template <class RT>
// static inline
// R_FT_return(CGAL_Homogeneous<RT>)
// CGAL_determinant_2(const CGAL_Point_2<CGAL_Homogeneous<RT> >& p,
//                    const CGAL_Point_2<CGAL_Homogeneous<RT> >& q,
//                    const CGAL_Point_2<CGAL_Homogeneous<RT> >& r)
// {
//   return CGAL_cross_product_2(p-q, p-r);
// }
// #endif
//-----------------------------------------------------//

#ifdef CGAL_HOMOGENEOUS_H
template <class FT>
static inline
FT CGAL_determinant_2(const CGAL_Point_2<CGAL_Homogeneous<FT> >& p,
                      const CGAL_Point_2<CGAL_Homogeneous<FT> >& q,
                      const CGAL_Point_2<CGAL_Homogeneous<FT> >& r)
{
  return CGAL_cross_product_2(p-q, p-r);
}
#endif

//-----------------------------------------------------------------------//
//                          Compare_X_at_Y
//-----------------------------------------------------------------------//
// Compares the x-coordinates of the intersections of the segments (p1,q1)
// and (p2,q2) with the horizontal line l = {y=y0}.
// PRECONDITION: the segments do intersect the line l
// N.B. If a segment is fully contained in l, then the leftmost intersection
// point is used for the comparison!.

template <class R, class FT>
bool Compare_X_at_Y(const CGAL_Point_2<R>& p1,
                    const CGAL_Point_2<R>& q1,
                    const CGAL_Point_2<R>& p2,
                    const CGAL_Point_2<R>& q2,
                    const FT& y0)
{
  R::FT n1, d1, n2, d2;
  d1 = q1.y() - p1.y();
  d2 = q2.y() - p2.y();

  if (d1 == R::FT(0))
    { d1 = R::FT(1); n1 = min(p1.x(), q1.x()); }
  else
    n1 = p1.x()*(q1.y() - y0) + q1.x()*(y0 - p1.y());

  if (d2 == R::FT(0))
    { d2 = R::FT(1); n2 = min(p2.x(), q2.x()); }
  else
    n2 = p2.x()*(q2.y() - y0) + q2.x()*(y0 - p2.y());

  return ((d1 < R::FT(0)) == (d2 < R::FT(0))) == (n1*d2 < n2*d1);
}

//-----------------------------------------------------------------------//
//                          DoIntersect
//-----------------------------------------------------------------------//
// Tests if the segments (p1,p2) and (q1,q2) intersect.

template <class R>
static inline bool DoIntersect(const CGAL_Point_2<R>& p1,
                               const CGAL_Point_2<R>& p2,
                               const CGAL_Point_2<R>& q1,
                               const CGAL_Point_2<R>& q2  )
{
  return CGAL_do_intersect(CGAL_Segment_2<R>(p1,p2), CGAL_Segment_2<R>(q1,q2));
}

//-----------------------------------------------------------------------//
//                          EqualDirection
//-----------------------------------------------------------------------//
// Tests if the vectors v1 and v2 point in the same direction.

template <class R>
static inline bool EqualDirection(const CGAL_Vector_2<R>& v1,
                                  const CGAL_Vector_2<R>& v2 )
{
  return CGAL_Direction_2<R>(v1) == CGAL_Direction_2<R>(v2);
}

//-----------------------------------------------------------------------//
//                          SimplicityTest
//-----------------------------------------------------------------------//
// The simplicity test is implemented as a class instead of a function,
// because inside a function it isn't possible to use the comparison
// classes VertexComp and EdgeComp.

template <class ForwardIterator, class Point>
class SimplicityTest {
  private:
    vector<ForwardIterator> d_index;
    // the attribute d_index is just a mapping between the integers and the
    // sequence of points

    int d_eventpoint;
    // the index of the current event point
    // the current sweepline is the horizontal line through this point

  public:
    SimplicityTest() {}
    ~SimplicityTest() {}

    const Point& Vertex(int i) const { return *d_index[i]; }
    int NumberOfVertices() const { return d_index.size(); }

    bool Test(ForwardIterator first, ForwardIterator last);
    // tests if the polygon with points in the range [first,last) is simple

    bool EdgeIntersection(int e1, int e2) const;
    // tests if the edges e1 and e2 have an intersection
    // N.B. the common vertex of two consecutive edges is not counted
    // as an intersection!
  
    bool VertexCompare(int i, int j) const;
    // computes the (lexicographical) order of vertex(i) and vertex(j)

    class VertexComp {
      private:
        const SimplicityTest<ForwardIterator, Point>* s;
      public:
        VertexComp() {}
        VertexComp(const SimplicityTest<ForwardIterator, Point>* s0): s(s0) {}
        bool operator() (int i, int j) const { return s->VertexCompare(i,j); }
    };

    bool EdgeCompare(int e1, int e2) const;
    // computes the order of two edges e1 and e2 on the current sweepline

    bool EdgeCompareShared(int e1, int e2) const;
    // computes the order of two edges e1 and e2 that share the current
    // event point

    bool EdgeCompareNonShared(int e1, int e2) const;
    // computes the order of two edges e1 and e2 that do not share the current
    // event point

    bool EdgesShareEventpoint(int e1, int e2) const;
    // true if the edges e1 and e2 share the current event point

    class EdgeComp {
      private:
        const SimplicityTest<ForwardIterator, Point>* s;
      public:
        EdgeComp() {}
        EdgeComp(const SimplicityTest<ForwardIterator, Point>* s0): s(s0) {}
        bool operator() (int i, int j) const { return s->EdgeCompare(i,j); }
    };

    class EventQueue {
      //-----------------------------------------------------------------//
      // g++ 2.7.2 seems to have problems with the following typedef
      //
      //  public:
      //    typedef set<int,VertexComp>::const_iterator const_iterator;
      //-----------------------------------------------------------------//

      private:
        set<int,VertexComp> queue;
      public:
        EventQueue(SimplicityTest<ForwardIterator, Point>* s): queue(VertexComp(s)) {}
        bool insert(int i) { return queue.insert(i).second; }
        bool empty() const      { return queue.empty(); }
        int pop() {
          int Result = *(queue.begin());
          queue.erase(queue.begin());
          return Result;
        }
#ifdef DEBUG
        void Show() const {
          cout << "event queue: ";

          set<int,VertexComp>::const_iterator i;
          for (i = queue.begin(); i != queue.end(); ++i)
            cout << *i << " ";
          cout << endl;
        }
#endif
    };

    class SweepStatus {
      //-----------------------------------------------------------------//
      // g++ 2.7.2 seems to have problems with the following typedef
      //
      //  public:
      //    typedef set<int,EdgeComp>::const_iterator const_iterator;
      //-----------------------------------------------------------------//

      private:
        set<int,EdgeComp> status;
        vector<set<int,EdgeComp>::const_iterator> index;
        // the iterators of the edges are stored to enable fast deletion
      public:
        SweepStatus(const SimplicityTest<ForwardIterator, Point>* s, int n)
          : status(EdgeComp(s)) { index.reserve(n); }
        void insert(int e)      { index[e] = status.insert(e).first; }
        void erase(int e)       { status.erase(index[e]); }
#ifdef DEBUG
        void Show() {
          cout << "sweep status: ";
          set<int,EdgeComp>::const_iterator i;
          for (i = status.begin(); i != status.end(); ++i)
            cout << *i << " ";
          cout << endl;
        }
#endif
        int replace(int e1, int e2) { erase(e1); insert(e2); return e2; }
        // Ideally we would like to directly replace edge e1 with edge e2 by
        // putting *(index[e1]) = e2. However, this is not supported by STL
        // sets.
        int left(int e) const
        { set<int,EdgeComp>::const_iterator i = index[e];
          return (i == status.begin()) ? -1 : *(--i);
        }
        int right(int e) const
        { set<int,EdgeComp>::const_iterator i = index[e]; ++i;
          return (i == status.end()) ? -1 : *i;
        }
  };

  bool ConsecutiveEdges(int e1, int e2) const;
  // returns true if the edges e1 and e2 are consecutive
};

template <class ForwardIterator, class Point>
inline bool SimplicityTest<ForwardIterator, Point>::VertexCompare(int i, int j) const
{
  return ( Vertex(i).y()  > Vertex(j).y() ) ||
         ( (Vertex(i).y() == Vertex(j).y()) &&
           (Vertex(i).x()  > Vertex(j).x()) );
}

template <class ForwardIterator, class Point>
inline bool SimplicityTest<ForwardIterator, Point>::EdgeCompare(int e1, int e2) const
{
  if (EdgesShareEventpoint(e1,e2))
    return EdgeCompareShared(e1,e2);
  else
    return EdgeCompareNonShared(e1,e2);
}

template <class ForwardIterator, class Point>
bool SimplicityTest<ForwardIterator, Point>::EdgeCompareShared(int e1, int e2) const
{
  int n = NumberOfVertices();
  int f1 = (e1<n-1) ? e1+1 : e1+1-n;  // edge(e1) = (vertex(e1), vertex(f1))
  int f2 = (e2<n-1) ? e2+1 : e2+1-n;  // edge(e2) = (vertex(e2), vertex(f2))

#ifdef DEBUG
  cout << "    comparing edges (shared) " << e1 << " and " << e2 << flush;
  bool b = CGAL_is_negative( CGAL_cross_product_2( Vertex(f1) - Vertex(e1),
                                                   Vertex(f2) - Vertex(e2)  ) );
  cout << ": " << (b ? 1 : 0) << endl;
#endif

  return CGAL_is_negative( CGAL_cross_product_2( Vertex(f1) - Vertex(e1),
                                                 Vertex(f2) - Vertex(e2)  ) );
}

template <class ForwardIterator, class Point>
bool SimplicityTest<ForwardIterator, Point>::EdgeCompareNonShared(int e1, int e2) const
{
  int n = NumberOfVertices();
  int f1 = (e1<n-1) ? e1+1 : e1+1-n;  // edge(e1) = (vertex(e1), vertex(f1))
  int f2 = (e2<n-1) ? e2+1 : e2+1-n;  // edge(e2) = (vertex(e2), vertex(f2))

#ifdef DEBUG
  cout << "    comparing edges (nonshared) " << e1 << " and " << e2 << flush;
  bool b = Compare_X_at_Y(Vertex(e1),
                          Vertex(f1),
                          Vertex(e2),
                          Vertex(f2),
                          Vertex(d_eventpoint).y());
  cout << ": " << (b ? 1 : 0) << endl;
#endif

  return Compare_X_at_Y(Vertex(e1),
                        Vertex(f1),
                        Vertex(e2),
                        Vertex(f2),
                        Vertex(d_eventpoint).y());
}

template <class ForwardIterator, class Point>
bool SimplicityTest<ForwardIterator, Point>::Test(ForwardIterator first,
                                                  ForwardIterator last)
{
  int n = 0;

  EventQueue events(this);
  while (first != last) {
    d_index.push_back(first);
    if (!events.insert(n++)) // if two vertices coincide...
      return false;
    ++first;
  }

#ifdef DEBUG
events.Show();
#endif

  SweepStatus status(this,n);

#ifdef DEBUG
status.Show();
#endif

  while (!events.empty()) {
    int i = events.pop();
    d_eventpoint = i;
#ifdef DEBUG
cout << "event point: " << d_eventpoint << endl;
#endif
    int prev = (i>0) ? i-1 : i-1+n;
    int next = (i<n-1) ? i+1 : i+1-n;

    bool prev_less_than_i = VertexCompare(i,prev);
    bool next_less_than_i = VertexCompare(i,next);
    if (prev_less_than_i != next_less_than_i) {
        int e = prev_less_than_i ? status.replace(i,prev) : status.replace(prev,i);
#ifdef DEBUG
status.Show();
#endif
        // check for intersections of newly inserted edge e with neighbors
        int left = status.left(e);
        if ((left >= 0) && (EdgeIntersection(left,e))) return false;

        int right = status.right(e);
        if ((right >= 0) && (EdgeIntersection(e,right))) return false;
    }
    else if (prev_less_than_i) {
      status.insert(prev);
      status.insert(i);
#ifdef DEBUG
status.Show();
#endif
      int e1 = prev;
      int e2 = i;
      // check for intersections of edges e1 and e2 with neighbors

      int left, right;
      left = status.left(e1);
      if ((left >= 0) && (EdgeIntersection(left,e1))) return false;

      right = status.right(e1);
      if ((right >= 0) && (EdgeIntersection(e1,right))) return false;

      left = status.left(e2);
      if ((left >= 0) && (left != e1) && (EdgeIntersection(left,e2))) return false;

      right = status.right(e2);
      if ((right >= 0) && (right != e1) &&(EdgeIntersection(e2,right))) return false;
    }
    else {
      status.erase(prev);
      status.erase(i);
#ifdef DEBUG
status.Show();
#endif
    }
  }

  return true;
}

template <class ForwardIterator, class Point>
bool SimplicityTest<ForwardIterator, Point>::EdgeIntersection(int e1, int e2) const
{
#ifdef DEBUG
cout << "    intersecting edges " << e1 << " and " << e2 << endl;
#endif

  int n = NumberOfVertices();
  int f1 = (e1<n-1) ? e1+1 : e1+1-n;  // edge(e1) = (vertex(e1), vertex(f1))
  int f2 = (e2<n-1) ? e2+1 : e2+1-n;  // edge(e2) = (vertex(e2), vertex(f2))

  if (ConsecutiveEdges(e1,e2))
    return EqualDirection(Vertex(f1) - Vertex(e1), Vertex(f2) - Vertex(e2));
  else
    return DoIntersect(Vertex(e1), Vertex(f1), Vertex(e2), Vertex(f2));
}

template <class ForwardIterator, class Point>
inline bool SimplicityTest<ForwardIterator, Point>::EdgesShareEventpoint(int e1, int e2) const
{
  int n = NumberOfVertices();
  return ((d_eventpoint == e1) || (d_eventpoint == e1 + 1) || (d_eventpoint == e1+1-n)) &&
         ((d_eventpoint == e2) || (d_eventpoint == e2 + 1) || (d_eventpoint == e2+1-n));
}

template <class ForwardIterator, class Point>
inline bool SimplicityTest<ForwardIterator, Point>::ConsecutiveEdges(int e1, int e2) const
{
  int n = NumberOfVertices();
  int diff = (e1<e2) ? e2-e1 : e1-e2;
  return (diff == 1) || (diff == n-1);
}

//-----------------------------------------------------------------------//
//                          CGAL_is_simple_2
//-----------------------------------------------------------------------//

template <class ForwardIterator, class Point>
bool CGAL_is_simple_2_aux(ForwardIterator first,
                          ForwardIterator last,
                          const Point&)
{
  SimplicityTest<ForwardIterator, Point> test;
  return test.Test(first, last);
}

template <class ForwardIterator>
bool CGAL_is_simple_2(ForwardIterator first, ForwardIterator last)
{
  return CGAL_is_simple_2_aux(first, last, *first);
}

//-----------------------------------------------------------------------//
//                     CGAL_Compare_lexicographically_xy/yx
//-----------------------------------------------------------------------//
// function objects for lexicographical comparison of points

template <class Point>
class CGAL_Compare_lexicographically_xy {
  public:
    bool operator()(const Point &p, const Point &q)
      { return (p.x() < q.x()) || (p.x() == q.x() && p.y() < q.y()); }
};

template <class Point>
class CGAL_Compare_lexicographically_yx {
  public:
    bool operator()(const Point &p, const Point &q)
      { return (p.y() < q.y()) || (p.y() == q.y() && p.x() < q.x()); }
};

//-----------------------------------------------------------------------//
//                          CGAL_left_vertex_2
//-----------------------------------------------------------------------//

template <class ForwardIterator, class Point>
ForwardIterator CGAL_left_vertex_2_aux( ForwardIterator first,
                                        ForwardIterator last,
                                        Point const&
                                      )
{
  return min_element(first, last, CGAL_Compare_lexicographically_xy<Point>());
}

template <class ForwardIterator>
ForwardIterator CGAL_left_vertex_2(ForwardIterator first, ForwardIterator last)
{
  CGAL_kernel_precondition(first != last);
  return CGAL_left_vertex_2_aux(first, last, *first);
}

//-----------------------------------------------------------------------//
//                          CGAL_right_vertex_2
//-----------------------------------------------------------------------//

template <class ForwardIterator, class Point>
ForwardIterator CGAL_right_vertex_2_aux( ForwardIterator first,
                                         ForwardIterator last,
                                         Point const&
                                       )
{
  return max_element(first, last, CGAL_Compare_lexicographically_xy<Point>());
}

template <class ForwardIterator>
ForwardIterator CGAL_right_vertex_2(ForwardIterator first, ForwardIterator last)
{
  CGAL_kernel_precondition(first != last);
  return CGAL_right_vertex_2_aux(first, last, *first);
}

//-----------------------------------------------------------------------//
//                          CGAL_top_vertex_2
//-----------------------------------------------------------------------//

template <class ForwardIterator, class Point>
ForwardIterator CGAL_top_vertex_2_aux( ForwardIterator first,
                                       ForwardIterator last,
                                       Point const&
                                     )
{
  return max_element(first, last, CGAL_Compare_lexicographically_yx<Point>());
}

template <class ForwardIterator>
ForwardIterator CGAL_top_vertex_2(ForwardIterator first, ForwardIterator last)
{
  CGAL_kernel_precondition(first != last);
  return CGAL_top_vertex_2_aux(first, last, *first);
}

//-----------------------------------------------------------------------//
//                          CGAL_bottom_vertex_2
//-----------------------------------------------------------------------//

template <class ForwardIterator, class Point>
ForwardIterator CGAL_bottom_vertex_2_aux( ForwardIterator first,
                                          ForwardIterator last,
                                          Point const&
                                        )
{
  return min_element(first, last, CGAL_Compare_lexicographically_yx<Point>());
}

template <class ForwardIterator>
ForwardIterator CGAL_bottom_vertex_2(ForwardIterator first, ForwardIterator last)
{
  CGAL_kernel_precondition(first != last);
  return CGAL_bottom_vertex_2_aux(first, last, *first);
}

//-----------------------------------------------------------------------//
//                          CGAL_bbox_2
//-----------------------------------------------------------------------//

template <class InputIterator>
CGAL_Bbox_2 CGAL_bbox_2(InputIterator first, InputIterator last)
{
  CGAL_kernel_precondition(first != last);
  CGAL_Bbox_2 result = (*first).bbox();

  while (++first != last)
    result = result + (*first).bbox();

  return result;
}

//-----------------------------------------------------------------------//
//                          CGAL_area_2
//-----------------------------------------------------------------------//

template <class ForwardIterator, class Numbertype>
void CGAL_area_2(ForwardIterator first, ForwardIterator last, Numbertype& result)
{
  result = Numbertype(0);

  // check if the polygon is empty
  if (first == last) return;

  ForwardIterator second = first; ++second;

  // check if the polygon has only one point
  if (second == last) return;

  ForwardIterator third = second;

  while (++third != last) {
    result = result + CGAL_determinant_2(*first, *second, *third);
    first = second;
    second = third;
  }

  result = result / Numbertype(2);
}

//-----------------------------------------------------------------------//
//                          CGAL_is_convex_2
//-----------------------------------------------------------------------//

template <class ForwardIterator>
bool CGAL_is_convex_2(ForwardIterator first, ForwardIterator last)
{
  ForwardIterator previous = first;
  if (previous == last) return true;

  ForwardIterator current = previous; ++current;
  if (current == last) return true;

  ForwardIterator next = current; ++next;
  if (next == last) return true;

  // initialization
  bool HasClockwiseTriples = false;
  bool HasCounterClockwiseTriples = false;
  bool Order = CGAL_lexicographically_xy_smaller(*previous, *current);
  int NumOrderChanges = 0;

  do {
    // due to a bug in CGAL, it is not possible to use a switch statement here...
    CGAL_Orientation o = CGAL_orientation(*previous, *current, *next);
    if (o == CGAL_CLOCKWISE)        HasClockwiseTriples = true;
    if (o == CGAL_COUNTERCLOCKWISE) HasCounterClockwiseTriples = true;

    bool NewOrder = CGAL_lexicographically_xy_smaller(*current, *next);
    if (Order != NewOrder) NumOrderChanges++;

    if (NumOrderChanges > 2) {
#ifdef DEBUG
cout << "too many order changes: not convex!" << endl;
#endif
      return false;
    }

    if (HasClockwiseTriples && HasCounterClockwiseTriples) {
#ifdef DEBUG
cout << "polygon not locally convex!" << endl;
#endif
      return false;
    }

    previous = current;
    current = next;
    ++next;
    if (next == last) next = first;
    Order = NewOrder;
  }
  while (previous != first);

  return true;
}

//-----------------------------------------------------------------------//
//                          CGAL_oriented_side_2
//-----------------------------------------------------------------------//

template <class ForwardIterator, class Point>
CGAL_Oriented_side CGAL_oriented_side_2(ForwardIterator first,
                                        ForwardIterator last,
                                        const Point& point)
{
  CGAL_Oriented_side result;

  CGAL_Orientation o = CGAL_orientation_2(first, last);
  CGAL_kernel_assertion(o != CGAL_COLLINEAR);

  CGAL_Bounded_side b = CGAL_bounded_side_2(first, last, point);
  switch (b) {
    case CGAL_ON_BOUNDARY:
      result = CGAL_ON_ORIENTED_BOUNDARY;
      break;

    case CGAL_ON_BOUNDED_SIDE:
      result = (o == CGAL_CLOCKWISE) ? CGAL_ON_NEGATIVE_SIDE : CGAL_ON_POSITIVE_SIDE;
      break;

    case CGAL_ON_UNBOUNDED_SIDE:
      result = (o == CGAL_CLOCKWISE) ? CGAL_ON_POSITIVE_SIDE : CGAL_ON_NEGATIVE_SIDE;
      break;
  }

  return result;
}

//-----------------------------------------------------------------------//
//                          CGAL_bounded_side_2
//-----------------------------------------------------------------------//
// returns CGAL_ON_BOUNDED_SIDE, CGAL_ON_BOUNDARY or CGAL_ON_UNBOUNDED_SIDE

template <class ForwardIterator, class Point>
CGAL_Bounded_side CGAL_bounded_side_2(ForwardIterator first,
                                      ForwardIterator last,
                                      const Point& point)
{
  ForwardIterator current = first;
  if (current == last) return CGAL_ON_UNBOUNDED_SIDE;

  ForwardIterator next = current; ++next;
  if (next == last) return CGAL_ON_UNBOUNDED_SIDE;

  bool IsInside = false;
  CGAL_Comparison_result CompareCurrent = CGAL_compare((*current).y(), point.y());

  do // check if the segment (current,next) intersects the ray { (t,y) | t >= point.x() }
  {
    CGAL_Comparison_result CompareNext = CGAL_compare((*next).y(), point.y());

    switch (CompareCurrent) {
      case CGAL_SMALLER:
        switch (CompareNext) {
          case CGAL_SMALLER:
            break;
          case CGAL_EQUAL:
            switch (CGAL_compare(point.x(), (*next).x())) {
              case CGAL_SMALLER: IsInside = !IsInside; break;
              case CGAL_EQUAL:   return CGAL_ON_BOUNDARY;
              case CGAL_LARGER:  break;
            }
            break;
          case CGAL_LARGER:
            if (point.x() < min((*current).x(), (*next).x())) {
              IsInside = !IsInside;
            }
            else if (point.x() <= max((*current).x(),(*next).x())) {
              switch (CGAL_sign(CGAL_determinant_2(point, *current, *next))) {
                case 0: return CGAL_ON_BOUNDARY;
                case 1: IsInside = !IsInside; break;
              }
            }
            break;
        }
        break;
      case CGAL_EQUAL:
        switch (CompareNext) {
          case CGAL_SMALLER:
            switch (CGAL_compare(point.x(), (*current).x())) {
              case CGAL_SMALLER: IsInside = !IsInside; break;
              case CGAL_EQUAL:   return CGAL_ON_BOUNDARY;
              case CGAL_LARGER:  break;
            }
            break;
          case CGAL_EQUAL:
            if ( (min((*current).x(), (*next).x()) <= point.x()) &&
                 (point.x() <= max((*current).x(), (*next).x()))    ) {
              return CGAL_ON_BOUNDARY;
            }
            break;
          case CGAL_LARGER:
            if (point.x() == (*current).x()) {
              return CGAL_ON_BOUNDARY;
            }
            break;
        }
        break;
      case CGAL_LARGER:
        switch (CompareNext) {
          case CGAL_SMALLER:
            if (point.x() < min((*current).x(), (*next).x())) {
              IsInside = !IsInside;
            }
            else if (point.x() <= max((*current).x(),(*next).x())) {
              switch (CGAL_sign(CGAL_determinant_2(point, *current, *next))) {
                case -1: IsInside = !IsInside; break;
                case  0: return CGAL_ON_BOUNDARY;
              }
            }
            break;
          case CGAL_EQUAL:
            if (point.x() == (*next).x()) {
              return CGAL_ON_BOUNDARY;
            }
            break;
          case CGAL_LARGER:
            break;
        }
        break;
    }

    current = next;
    CompareCurrent = CompareNext;
    ++next;
    if (next == last) next = first;   
  }
  while (current != first);

  return IsInside ? CGAL_ON_BOUNDED_SIDE : CGAL_ON_UNBOUNDED_SIDE;
}

//-----------------------------------------------------------------------//
//                          CGAL_orientation_2
//-----------------------------------------------------------------------//

template <class ForwardIterator, class Point>
CGAL_Orientation CGAL_orientation_2_aux(ForwardIterator first,
                                        ForwardIterator last,
                                        Point const&)
{
  ForwardIterator i = CGAL_left_vertex_2(first, last);

  ForwardIterator prev = (i == first) ? last : i; --prev;
  ForwardIterator next = i; ++next; if (next == last) next = first;

#ifdef DEBUG 
cout << "orientation: " << *prev << " " << *i << " " << *next << endl;
#endif

  // return the orientation of the triple (prev,i,next)
  return CGAL_orientation(*prev, *i, *next);
}

template <class ForwardIterator>
CGAL_Orientation CGAL_orientation_2(ForwardIterator first, ForwardIterator last)
{
  return CGAL_orientation_2_aux(first, last, *first);
}

