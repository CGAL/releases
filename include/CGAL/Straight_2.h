
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
// file          : include/CGAL/Straight_2.h
// package       : Intersections_2 (2.1.2)
// source        : straight_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : MPI, Saarbruecken
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_STRAIGHT_2_H
#define CGAL_STRAIGHT_2_H



CGAL_BEGIN_NAMESPACE

class _Straight_2_base {
public:
    enum states {EMPTY, POINT, SEGMENT, RAY, LINE};
protected:
    enum bound_states {NO_UNBOUNDED=0, MIN_UNBOUNDED=1, MAX_UNBOUNDED=2,
                        BOTH_UNBOUNDED = 3, LINE_EMPTY = 4};
                            _Straight_2_base() ;
    int                     _main_dir;  // _support is x or y directed (0/1).
    int                     _dir_sign;  // sign of main direction coord.
    unsigned int            _bound_state; // 0, 1, 2, 3, 4.
};

template <class R>
class _Straight_2: public _Straight_2_base {
public:
                            _Straight_2() ;
                            _Straight_2(Point_2<R> const &point) ;
                            _Straight_2(Line_2<R> const &line) ;
                            _Straight_2(Ray_2<R> const &ray) ;
                            _Straight_2(Segment_2<R> const &seg) ;
                            ~_Straight_2() {}
    void                    cut_right_off(Line_2<R> const & cutter) ;
    int                     collinear_order(Point_2<R> const & p1,
                                            Point_2<R> const &p2) const ;
    void                    current(Line_2<R> &line) const;
    void                    current(Ray_2<R> &ray) const;
    void                    current(Segment_2<R> &seg) const;
    void                    current(Point_2<R> &point) const;
    states                  current_state() const;
protected:
    Line_2<R>          _support;   // The supporting line.
    Point_2<R>         _min;
    Point_2<R>         _max;
};

CGAL_END_NAMESPACE


#include <CGAL/Line_2_Line_2_intersection.h>

CGAL_BEGIN_NAMESPACE

inline
_Straight_2_base::
_Straight_2_base()
{
    _bound_state = LINE_EMPTY;
}

template <class R>
_Straight_2_base::states
_Straight_2<R>::
current_state() const
{
    switch (_bound_state) {
    case BOTH_UNBOUNDED:
        return LINE;
    case MIN_UNBOUNDED:
    case MAX_UNBOUNDED:
        return RAY;
    case NO_UNBOUNDED:
        return (collinear_order(_min, _max) == 0) ? POINT : SEGMENT;
    case LINE_EMPTY:
    default:
        return EMPTY;
    }
}

template <class R>
_Straight_2<R>::
_Straight_2()
{
    _bound_state = LINE_EMPTY;
}

template <class R>
_Straight_2<R>::
_Straight_2(Line_2<R> const &line)
{
    _support = line;
    Vector_2<R> const &dir(_support.direction().vector());
    _main_dir = (abs(dir.x()) > abs(dir.y()) ) ? 0 : 1;
    _dir_sign = sign(_support.direction().vector().cartesian(_main_dir));
    _bound_state = BOTH_UNBOUNDED;
}

template <class R>
_Straight_2<R>::
_Straight_2(Point_2<R> const &point)
{
    _support = Line_2<R>(point, Direction_2<R>(R::RT(1),R::RT(0)));
    _main_dir = 0;
    _dir_sign = 1;
    _bound_state = NO_UNBOUNDED;
    _min = point;
    _max = point;
}

template <class R>
_Straight_2<R>::
_Straight_2(Ray_2<R> const &ray)
{
    _support = ray.supporting_line();
    Vector_2<R> const &dir(ray.direction().vector());
//    _main_dir = (abs(dir.hx()) > abs(dir.hy()) ) ? 0 : 1;
    _main_dir = (abs(dir.x()) > abs(dir.y()) ) ? 0 : 1;
    _dir_sign = sign(_support.direction().vector().cartesian(_main_dir));
    _bound_state = MAX_UNBOUNDED;
    _min = ray.start();
}

template <class R>
_Straight_2<R>::
_Straight_2(Segment_2<R> const &seg)
{
    _support = seg.supporting_line();
    Vector_2<R> const &dir(_support.direction().vector());
//    _main_dir = (abs(dir.hx()) > abs(dir.hy()) ) ? 0 : 1;
    _main_dir = (abs(dir.x()) > abs(dir.y()) ) ? 0 : 1;
    _dir_sign = sign(_support.direction().vector().cartesian(_main_dir));
    _bound_state = NO_UNBOUNDED;
    _min = seg.start();
    _max = seg.end();
}


template <class R>
void
_Straight_2<R>::
current(Line_2<R> &line) const
{
    CGAL_kernel_assertion(_bound_state == BOTH_UNBOUNDED);
    line = _support;
}

template <class R>
void
_Straight_2<R>::
current(Ray_2<R> &ray) const
{
    CGAL_kernel_assertion(_bound_state == MIN_UNBOUNDED
                        || _bound_state == MAX_UNBOUNDED);
    if (_bound_state == MIN_UNBOUNDED) {
        ray = Ray_2<R>(_max, -_support.direction());
    } else {
        ray = Ray_2<R>(_min, _support.direction());
    }
}

template <class R>
void
_Straight_2<R>::
current(Segment_2<R> &seg) const
{
    CGAL_kernel_assertion(_bound_state == NO_UNBOUNDED
                && collinear_order(_min, _max) != 0);
    seg = Segment_2<R>(_min, _max);
}

template <class R>
void
_Straight_2<R>::
current(Point_2<R> &pt) const
{
    CGAL_kernel_assertion(_bound_state == NO_UNBOUNDED
                && collinear_order(_min, _max) == 0);
    pt = _min;
}

/*
template <class R>
R::FT
cross(Vector_2<R> const &vec1, Vector_2<R> const &vec2)
{
    (vec1.hx() * vec2.hy() - vec1.hy() * vec2.hx()) / (vec1.hw()*vec2.hw());
}
*/

#if 0 // #ifdef CGAL_CARTESIAN_H
template <class FT>
FT
cross(Vector_2< Cartesian<FT> > const &vec1,
      Vector_2< Cartesian<FT> > const &vec2)
{
    return vec1.x() * vec2.y() - vec1.y() * vec2.x();
}

template <class R>
int
sign_of_cross(Direction_2<R> const &dir1,
            Direction_2<R> const &dir2)
{
    return sign(cross(dir1.vector(), dir2.vector()));
}
#endif

CGAL_END_NAMESPACE

#include <CGAL/squared_distance_utils.h>

CGAL_BEGIN_NAMESPACE

template <class R>
int
sign_of_cross(Direction_2<R> const &dir1,
            Direction_2<R> const &dir2)
{
    int result;
    switch(orientation(dir1.vector(), dir2.vector()))  {
    case COUNTERCLOCKWISE:
        result = 1;
        break;
    case CLOCKWISE:
        result = -1;
        break;
    case COLLINEAR:
        result = 0;
        break;
    }
    return result;
}

template <class R>
void
_Straight_2<R>::
cut_right_off(Line_2<R> const & cutter)
// cut off any part of this straight that is to the right of the cutter.
{
    if (_bound_state == LINE_EMPTY)
        return;
    Point_2<R> ispoint;
    bool new_point;
    Line_2_Line_2_pair<R> pair(&_support, &cutter);
    switch (pair.intersection_type()) {
    case Line_2_Line_2_pair<R>::NO:
        if (cutter.has_on_negative_side(_support.point()))
            _bound_state = LINE_EMPTY;
        break;
    case Line_2_Line_2_pair<R>::LINE:
        break;
    case Line_2_Line_2_pair<R>::POINT:
        pair.intersection(ispoint);
        new_point = false;
        switch (sign_of_cross(_support.direction(), cutter.direction())) {
        case -1: // new minimum.
            if (_bound_state & MIN_UNBOUNDED) {
                new_point = true;
                _bound_state ^= MIN_UNBOUNDED;  // exclusive or removes flag.
            } else {
                if (collinear_order(ispoint, _min) == -1)
                    new_point = true;
            }
            if (new_point) {
                if (!(_bound_state & MAX_UNBOUNDED)
                    && collinear_order(ispoint, _max) == -1)
                    _bound_state = LINE_EMPTY;
                else
                    _min = ispoint;
            }
            break;
        case 0: // should not happen
            CGAL_kernel_warning_msg(false, "Internal CGAL error.");
            break;
        case 1: // new maximum
            if (_bound_state & MAX_UNBOUNDED) {
                new_point = true;
                _bound_state ^= MAX_UNBOUNDED;  // exclusive or removes flag.
            } else {
                if (collinear_order(ispoint, _max) == 1)
                    new_point = true;
            }
            if (new_point) {
                if (!(_bound_state & MIN_UNBOUNDED)
                    && collinear_order(ispoint, _min) == 1)
                    _bound_state = LINE_EMPTY;
                else
                    _max = ispoint;
            }
            break;
        }
        break;
    }
}

template <class R>
int
_Straight_2<R>::
collinear_order(Point_2<R> const &pt1, Point_2<R> const & pt2) const
// Compare two points on the _support line.
// If the second point lies in the direction of the direction vector from
// the first point, the result is 1.
// Other results are -1 (other side) and 0 (coincidence).
{
    int diffsign;
    diffsign = sign(pt2.cartesian(_main_dir)-pt1.cartesian(_main_dir));
    if (diffsign == 0)
        return 0;
    return (diffsign == _dir_sign) ? 1 : -1;
}

CGAL_END_NAMESPACE






#endif
