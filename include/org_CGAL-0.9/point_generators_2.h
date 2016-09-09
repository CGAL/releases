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

// +--------------------------------------------------------------------+
// | 2D Point Generators
// | Extracted from generators.fw
// | $Revision: 1.4 $
// | $Date: 1997/06/27 21:30:01 $
// |
// | 1997   Lutz Kettner 
// +--------------------------------------------------------------------+

#ifdef  CGAL_CARTESIAN_H
#ifndef CGAL_BUILD_POINT_CARTESIAN_H
#define CGAL_BUILD_POINT_CARTESIAN_H 1

// Builds a point (x,y) in p. `Point' is the point type in question.
inline
CGAL_Point_2< CGAL_Cartesian<double> >&
CGAL_build_point( double x, double y,
                  CGAL_Point_2< CGAL_Cartesian<double> >&  p) {
    p = CGAL_Point_2< CGAL_Cartesian<double> >( x, y);
    return p;
}
inline
CGAL_Point_2< CGAL_Cartesian<float> >&
CGAL_build_point( double x, double y,
                       CGAL_Point_2< CGAL_Cartesian<float> >&  p) {
    p = CGAL_Point_2< CGAL_Cartesian<float> >( float(x), float(y));
    return p;
}

#endif
#endif

#ifdef  CGAL_HOMOGENEOUS_H
#ifndef CGAL_BUILD_POINT_HOMOGENEOUS_H
#define CGAL_BUILD_POINT_HOMOGENEOUS_H 1
// To be filt in later.
#endif
#endif
// #line 122 "generators.any"
      
#ifndef CGAL_POINT_GENERATORS_2_H
#define CGAL_POINT_GENERATORS_2_H 1
/#line 149 "generators.any"
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef __STDDEF_H__
#include <stddef.h>
#endif
#ifndef __MATH_H__
#include <math.h>
#endif
#ifndef ITERATOR_H
#include <iterator.h>
#endif
#ifndef CGAL_RANDOM_H
#include <CGAL/Random.h>
#endif

// #line 203 "generators.any"
template < class P >
class CGAL__Random_points_base : public input_iterator<P,size_t> {
protected:
    CGAL_Random& _rnd;
public:
    CGAL__Random_points_base() : _rnd( CGAL_random) {}
    CGAL__Random_points_base( const CGAL__Random_points_base<P>& rb)
        : _rnd( rb._rnd) {}
    CGAL__Random_points_base( CGAL_Random& rnd)
        : _rnd( rnd) {}
    bool operator==( const CGAL__Random_points_base<P>& rb) const {
        return (_rnd == rb._rnd);
    }
    bool operator!=( const CGAL__Random_points_base<P>& rb) const {
        return ! operator==( rb);
    }
};

template < class P >
class CGAL_Random_points_in_disc_2 : public CGAL__Random_points_base<P> {
    double _r;
public:
    CGAL_Random_points_in_disc_2() {}
    CGAL_Random_points_in_disc_2(
        const CGAL_Random_points_in_disc_2<P>& rp)
        : CGAL__Random_points_base<P>(rp), _r( rp._r) {}
    CGAL_Random_points_in_disc_2( double r, CGAL_Random& rnd = CGAL_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed in the open disc with radius r, i.e. |`*g'| < r .
        // Two random numbers are needed from `rnd' for each point.
        // Precondition: a function `CGAL_build_point()' for the point
        // type `P'.
    : CGAL__Random_points_base<P>(rnd) , _r(r) {}
    CGAL_Random_points_in_disc_2<P>& operator++()    { return *this; }
    CGAL_Random_points_in_disc_2<P>  operator++(int) { return *this; }
    P operator*() const;
};

template < class P >
P
CGAL_Random_points_in_disc_2<P>::
operator*() const {
    P p;
    double alpha = _rnd.get_double() * 2.0 * M_PI;
    double r     = _r * sqrt( _rnd.get_double());
    CGAL_build_point( r * cos(alpha), r * sin(alpha), p);
    return p;
}


template < class P >
class CGAL_Random_points_on_circle_2 : public CGAL__Random_points_base<P> {
    double _r;
public:
    CGAL_Random_points_on_circle_2() {}
    CGAL_Random_points_on_circle_2(
        const CGAL_Random_points_on_circle_2<P>& rp)
        : CGAL__Random_points_base<P>(rp), _r( rp._r) {}
    CGAL_Random_points_on_circle_2( double r,
                                    CGAL_Random& rnd = CGAL_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed on the circle with radius r, i.e. |`*g'| == r . A
        // single random number is needed from `rnd' for each point.
        // Precondition: a function `CGAL_build_point()' for the point
        // type `P'.
    : CGAL__Random_points_base<P>(rnd) , _r(r) {}
    CGAL_Random_points_on_circle_2<P>& operator++()    { return *this; }
    CGAL_Random_points_on_circle_2<P>  operator++(int) { return *this; }
    P operator*() const;
};

template < class P >
P
CGAL_Random_points_on_circle_2<P>::
operator*() const {
    P p;
    double alpha = _rnd.get_double() * 2.0 * M_PI;
    CGAL_build_point( _r * cos(alpha), _r * sin(alpha), p);
    return p;
}


template < class P >
class CGAL_Random_points_in_square_2 : public CGAL__Random_points_base<P> {
    double _a;
public:
    CGAL_Random_points_in_square_2() {}
    CGAL_Random_points_in_square_2(
        const CGAL_Random_points_in_square_2<P>& rp)
        : CGAL__Random_points_base<P>(rp), _a( rp._a) {}
    CGAL_Random_points_in_square_2( double a,
                                    CGAL_Random& rnd = CGAL_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed in the half-open square with side length a,
        // centered around the origin, i.e. \forall p = `*g': -\frac{a}{2}
        // <= p.x() < \frac{a}{2} and -\frac{a}{2} <= p.y() < \frac{a}{2}
        // . Two random numbers are needed from `rnd' for each point.
        // Precondition: a function `CGAL_build_point()' for the point
        // type `P'.
    : CGAL__Random_points_base<P>(rnd) , _a(a) {}
    CGAL_Random_points_in_square_2<P>& operator++()    { return *this; }
    CGAL_Random_points_in_square_2<P>  operator++(int) { return *this; }
    P operator*() const;
};

template < class P >
P
CGAL_Random_points_in_square_2<P>::
operator*() const {
    P p;
    CGAL_build_point( _a * _rnd.get_double() - _a/2.0,
                      _a * _rnd.get_double() - _a/2.0,
                      p);
    return p;
}


template < class P >
class CGAL_Random_points_on_square_2 : public CGAL__Random_points_base<P> {
    double _a;
public:
    CGAL_Random_points_on_square_2() {}
    CGAL_Random_points_on_square_2(
        const CGAL_Random_points_on_square_2<P>& rp)
        : CGAL__Random_points_base<P>(rp), _a( rp._a) {}
    CGAL_Random_points_on_square_2( double a,
                                    CGAL_Random& rnd = CGAL_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed on the boundary of the square with side length a,
        // centered around the origin, i.e. \forall p = `*g': one
        // coordinate is either \frac{a}{2} or -\frac{a}{2} and for the
        // other coordinate c holds -\frac{a}{2} <= c < \frac{a}{2} . A
        // single random number is needed from `rnd' for each point.
        // Precondition: a function `CGAL_build_point()' for the point
        // type `P'.
    : CGAL__Random_points_base<P>(rnd) , _a(a) {}
    CGAL_Random_points_on_square_2<P>& operator++()    { return *this; }
    CGAL_Random_points_on_square_2<P>  operator++(int) { return *this; }
    P operator*() const;
};

template < class P >
P
CGAL_Random_points_on_square_2<P>::
operator*() const {
    double d = _rnd.get_double() * 4.0;
    int    k = int(d);
    d = _a * (d - k) - _a/2.0;
    assert( -_a/2.0 <= d && d < _a/2.0);
    P p;
    switch (k) {
    case 0:
        CGAL_build_point(       d, -_a/2.0, p);
        break;
    case 1:
        CGAL_build_point(       d,  _a/2.0, p);
        break;
    case 2:
        CGAL_build_point( -_a/2.0,       d, p);
        break;
    case 3:
        CGAL_build_point(  _a/2.0,       d, p);
        break;
    }
    return p;
}


template < class P >
class CGAL_Random_points_on_segment_2 : public CGAL__Random_points_base<P> {
    const P& _p;
    const P& _q;
public:
    CGAL_Random_points_on_segment_2() {}
    CGAL_Random_points_on_segment_2(
        const CGAL_Random_points_on_segment_2<P>& rp)
        : CGAL__Random_points_base<P>(rp), _p( rp._p), _q( rp._q) {}
    CGAL_Random_points_on_segment_2( const P& p, const P& q,
                                     CGAL_Random& rnd = CGAL_random)
        // g is an input iterator creating points of type `P' uniformly
        // distributed on the segment from p to q except q, i.e. `*g' ==
        // \lambda p + (1-\lambda)\, q where 0 <= \lambda < 1 . A single
        // random numberis needed from `rnd' for each point. Precondition:
        // a function `CGAL_build_point()' for the point type `P'. The
        // expression `CGAL_to_double((*begin).x())' must be legal.
    : CGAL__Random_points_base<P>(rnd) , _p(p), _q(q) {}
    CGAL_Random_points_on_segment_2<P>& operator++()    { return *this; }
    CGAL_Random_points_on_segment_2<P>  operator++(int) { return *this; }
    P operator*() const;
};

template < class P >
P
CGAL_Random_points_on_segment_2<P>::
operator*() const {
    P p;
    double la = _rnd.get_double();
    double mu = 1.0 - la;
    CGAL_build_point( mu * CGAL_to_double(_p.x()) +
                      la * CGAL_to_double(_q.x()),
                      mu * CGAL_to_double(_p.y()) +
                      la * CGAL_to_double(_q.y()),
                      p);
    return p;
}
// #line 147 "generators.any"
 
// #line 414 "generators.any"
template <class OutputIterator, class P>
OutputIterator
CGAL_points_on_square_grid_2( double a, size_t n, OutputIterator o,
                              const P*)
    // creates the n first points on the regular \lceil\sqrt{n}\rceil
    // \times \lceil \sqrt{n}\rceil grid within the square [-\frac{a}{2}
    // ,\frac{a}{2}]\times[-\frac{a}{2},\frac{a}{2}]. Precondition: a
    // function `CGAL_build_point()' for the point type `P' and `P' must
    // be assignable to the value type of `OutputIterator'.
{
    if  (n == 0)
        return o;
    int m = int(ceil(sqrt(n)));
    double base = -a/2;  // Left and bottom boundary.
    double step = a/(m - 1);
    int j = 0;
    double px = base;
    double py = base;
    P p;
    *o++ = CGAL_build_point( px, py, p);
    for (size_t i = 1; i < n; i++) {
        j++;
        if ( j == m) {
            px = base;
            py = py + step;
            j = 0;
        } else {
            px = px + step;
        }
        *o++ = CGAL_build_point( px, py, p);
    }
    return o;
}

template <class P, class OutputIterator>
OutputIterator
CGAL_points_on_segment_2( const P& p, const P& q, size_t n,
                          OutputIterator o)
    // creates n points regular spaced on the segment from p to q, i.e.
    // \forall i: 0 <= i < n: o[i] := \frac{n-i-1}{n-1} p + \frac{i}{n-1
    // } q.
{
    for (size_t i = 0; i < n; i++) {
        *o++ = p + (q-p) * i / (n-1);
    }
    return o;
}
// #line 148 "generators.any"
 
// #line 467 "generators.any"
template <class ForwardIterator>
void CGAL_perturb_points_2( ForwardIterator first,
                            ForwardIterator last,
                            double xeps,
                            double yeps,
                            CGAL_Random& rnd)
    // perturbs the points in the range [`first',`last') by replacing
    // each point with a random point from the rectangle `xeps' \times
    // `yeps' centered around the original point. Two random numbers are
    // needed from `rnd' for each point. Precondition: a function
    // `CGAL_build_point()' for the value type of the `ForwardIterator'.
    // The expression `CGAL_to_double((*first).x())' and `CGAL_to_double((
// *begin).y())' must be legal.
{
    xeps *= 2.0;
    yeps *= 2.0;
    for ( ; first != last; ++first) {
        double x = CGAL_to_double( (*first).x());
        double y = CGAL_to_double( (*first).y());
        x += xeps * (rnd.get_double() - 0.5);
        y += yeps * (rnd.get_double() - 0.5);
        CGAL_build_point( x, y, *first);
    }
}

template <class ForwardIterator>
inline
void CGAL_perturb_points_2( ForwardIterator first,
                            ForwardIterator last,
                            double xeps,
                            CGAL_Random& rnd)
{
    CGAL_perturb_points_2( first, last, xeps, xeps, rnd);
}

template <class ForwardIterator>
void CGAL_perturb_points_2( ForwardIterator first,
                            ForwardIterator last,
                            double xeps,
                            double yeps)
{
    CGAL_perturb_points_2( first, last, xeps, yeps, CGAL_random);
}

template <class ForwardIterator>
void CGAL_perturb_points_2( ForwardIterator first,
                            ForwardIterator last,
                            double xeps)
{
    CGAL_perturb_points_2( first, last, xeps, xeps, CGAL_random);
}
//#line 167 "generators.any"
 
// #line 507 "generators.any"
template <class RandomAccessIterator, class OutputIterator, class P>
OutputIterator CGAL__random_collinear_points_2(
                       RandomAccessIterator first,
                       RandomAccessIterator last,
                       size_t n,
                       OutputIterator first2,
                       CGAL_Random& rnd,
                       P*)
{
    int m = last - first;
    for ( size_t i = 0; i < n; i++) {
        const P& p = first[ rnd.get_int( 0, m-1)];
        const P& q = first[ rnd.get_int( 0, m-1)];
        P r;
        double la = rnd.get_double();
        double mu = 1.0 - la;
        CGAL_build_point( mu * CGAL_to_double(p.x()) +
                          la * CGAL_to_double(q.x()),
                          mu * CGAL_to_double(p.y()) +
                          la * CGAL_to_double(q.y()),
                          r);
        *first2++ = r;
    }
    return first2;
}

template <class RandomAccessIterator, class OutputIterator>
OutputIterator CGAL_random_collinear_points_2(
                       RandomAccessIterator first,
                       RandomAccessIterator last,
                       size_t n,
                       OutputIterator first2,
                       CGAL_Random& rnd)
    // choose two random points from the range [`first',`last'), create a
    // random third point on the segment connecting this two points, and
    // write it to `first2'. Repeat this n times, thus writing n points to
    // `first2' that are collinear with points in the range [`first',
    // `last'). Three random numbers are needed from `rnd' for each point.
    // Returns the value of `first2' after inserting the n points.
    // Precondition: a function `CGAL_build_point()' for the value type of
    // the `ForwardIterator'. The expression `CGAL_to_double((*first).x()
    // )' and `CGAL_to_double((*first).y())' must be legal.
{
    return  CGAL__random_collinear_points_2( first, last, n, first2, rnd,
                                             value_type( first));
}

template <class RandomAccessIterator, class OutputIterator>
OutputIterator CGAL_random_collinear_points_2(
                       RandomAccessIterator first,
                       RandomAccessIterator last,
                       size_t n,
                       OutputIterator first2)
{
    return  CGAL_random_collinear_points_2( first, last, n, first2,
                                            CGAL_random);
}

//#line 143 "generators.any"

#endif // CGAL_POINT_GENERATORS_2_H //
// EOF //
