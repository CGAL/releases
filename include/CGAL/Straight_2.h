// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Straight_2.h
// author(s)     : Geert-Jan Giezeman
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_STRAIGHT_2_H
#define CGAL_STRAIGHT_2_H



class CGAL__Straight_2_base {
public:
    enum states {EMPTY, POINT, SEGMENT, RAY, LINE};
protected:
    enum bound_states {NO_UNBOUNDED=0, MIN_UNBOUNDED=1, MAX_UNBOUNDED=2,
                        BOTH_UNBOUNDED = 3, LINE_EMPTY = 4};
                            CGAL__Straight_2_base() ;
    int                     _main_dir;  // _support is x or y directed (0/1).
    int                     _dir_sign;  // sign of main direction coord.
    unsigned int            _bound_state; // 0, 1, 2, 3, 4.
};

template <class R>
class CGAL__Straight_2: public CGAL__Straight_2_base {
public:
                            CGAL__Straight_2() ;
                            CGAL__Straight_2(CGAL_Point_2<R> const &point) ;
                            CGAL__Straight_2(CGAL_Line_2<R> const &line) ;
                            CGAL__Straight_2(CGAL_Ray_2<R> const &ray) ;
                            CGAL__Straight_2(CGAL_Segment_2<R> const &seg) ;
                            ~CGAL__Straight_2() {}
    void                    cut_right_off(CGAL_Line_2<R> const & cutter) ;
    int                     collinear_order(CGAL_Point_2<R> const & p1,
                                            CGAL_Point_2<R> const &p2) const ;
    void                    current(CGAL_Line_2<R> &line) const;
    void                    current(CGAL_Ray_2<R> &ray) const;
    void                    current(CGAL_Segment_2<R> &seg) const;
    void                    current(CGAL_Point_2<R> &point) const;
    states                  current_state() const;
protected:
    CGAL_Line_2<R>          _support;   // The supporting line.
    CGAL_Point_2<R>         _min;
    CGAL_Point_2<R>         _max;
};



#include <CGAL/Line_2_Line_2_intersection.h>

CGAL__Straight_2_base::
CGAL__Straight_2_base()
{
    _bound_state = LINE_EMPTY;
}

template <class R>
CGAL__Straight_2_base::states
CGAL__Straight_2<R>::
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
CGAL__Straight_2<R>::
CGAL__Straight_2()
{
    _bound_state = LINE_EMPTY;
}

template <class R>
CGAL__Straight_2<R>::
CGAL__Straight_2(CGAL_Line_2<R> const &line)
{
    _support = line;
    CGAL_Vector_2<R> const &dir(_support.direction().vector());
    _main_dir = (CGAL_abs(dir.x()) > CGAL_abs(dir.y()) ) ? 0 : 1;
    _dir_sign = CGAL_sign(_support.direction().vector().cartesian(_main_dir));
    _bound_state = BOTH_UNBOUNDED;
}

template <class R>
CGAL__Straight_2<R>::
CGAL__Straight_2(CGAL_Point_2<R> const &point)
{
    _support = CGAL_Line_2<R>(point, CGAL_Direction_2<R>(R::RT(1),R::RT(0)));
    _main_dir = 0;
    _dir_sign = 1;
    _bound_state = NO_UNBOUNDED;
    _min = point;
    _max = point;
}

template <class R>
CGAL__Straight_2<R>::
CGAL__Straight_2(CGAL_Ray_2<R> const &ray)
{
    _support = ray.supporting_line();
    CGAL_Vector_2<R> const &dir(ray.direction().vector());
//    _main_dir = (abs(dir.hx()) > abs(dir.hy()) ) ? 0 : 1;
    _main_dir = (CGAL_abs(dir.x()) > CGAL_abs(dir.y()) ) ? 0 : 1;
    _dir_sign = CGAL_sign(_support.direction().vector().cartesian(_main_dir));
    _bound_state = MAX_UNBOUNDED;
    _min = ray.start();
}

template <class R>
CGAL__Straight_2<R>::
CGAL__Straight_2(CGAL_Segment_2<R> const &seg)
{
    _support = seg.supporting_line();
    CGAL_Vector_2<R> const &dir(_support.direction().vector());
//    _main_dir = (abs(dir.hx()) > abs(dir.hy()) ) ? 0 : 1;
    _main_dir = (CGAL_abs(dir.x()) > CGAL_abs(dir.y()) ) ? 0 : 1;
    _dir_sign = CGAL_sign(_support.direction().vector().cartesian(_main_dir));
    _bound_state = NO_UNBOUNDED;
    _min = seg.start();
    _max = seg.end();
}


template <class R>
void
CGAL__Straight_2<R>::
current(CGAL_Line_2<R> &line) const
{
    CGAL_kernel_assertion(_bound_state == BOTH_UNBOUNDED);
    line = _support;
}

template <class R>
void
CGAL__Straight_2<R>::
current(CGAL_Ray_2<R> &ray) const
{
    CGAL_kernel_assertion(_bound_state == MIN_UNBOUNDED
                        || _bound_state == MAX_UNBOUNDED);
    if (_bound_state == MIN_UNBOUNDED) {
        ray = CGAL_Ray_2<R>(_max, -_support.direction());
    } else {
        ray = CGAL_Ray_2<R>(_min, _support.direction());
    }
}

template <class R>
void
CGAL__Straight_2<R>::
current(CGAL_Segment_2<R> &seg) const
{
    CGAL_kernel_assertion(_bound_state == NO_UNBOUNDED
                && collinear_order(_min, _max) != 0);
    seg = CGAL_Segment_2<R>(_min, _max);
}

template <class R>
void
CGAL__Straight_2<R>::
current(CGAL_Point_2<R> &pt) const
{
    CGAL_kernel_assertion(_bound_state == NO_UNBOUNDED
                && collinear_order(_min, _max) == 0);
    pt = _min;
}

/*
template <class R>
R::FT
cross(CGAL_Vector_2<R> const &vec1, CGAL_Vector_2<R> const &vec2)
{
    (vec1.hx() * vec2.hy() - vec1.hy() * vec2.hx()) / (vec1.hw()*vec2.hw());
}
*/

#if 0 // #ifdef CGAL_CARTESIAN_H
template <class FT>
FT
cross(CGAL_Vector_2< CGAL_Cartesian<FT> > const &vec1,
      CGAL_Vector_2< CGAL_Cartesian<FT> > const &vec2)
{
    return vec1.x() * vec2.y() - vec1.y() * vec2.x();
}

template <class R>
int
CGAL_sign_of_cross(CGAL_Direction_2<R> const &dir1,
            CGAL_Direction_2<R> const &dir2)
{
    return CGAL_sign(cross(dir1.vector(), dir2.vector()));
}
#endif

#include <CGAL/squared_distance_utils.h>

template <class R>
int
CGAL_sign_of_cross(CGAL_Direction_2<R> const &dir1,
            CGAL_Direction_2<R> const &dir2)
{
    int result;
    switch(CGAL_orientation(dir1.vector(), dir2.vector()))  {
    case CGAL_COUNTERCLOCKWISE:
        result = 1;
        break;
    case CGAL_CLOCKWISE:
        result = -1;
        break;
    case CGAL_COLLINEAR:
        result = 0;
        break;
    }
    return result;
}

template <class R>
void
CGAL__Straight_2<R>::
cut_right_off(CGAL_Line_2<R> const & cutter)
// cut off any part of this straight that is to the right of the cutter.
{
    if (_bound_state == LINE_EMPTY)
        return;
    CGAL_Point_2<R> ispoint;
    bool new_point;
    CGAL_Line_2_Line_2_pair<R> pair(&_support, &cutter);
    switch (pair.intersection_type()) {
    case CGAL_Line_2_Line_2_pair<R>::NO:
        if (cutter.has_on_negative_side(_support.point()))
            _bound_state = LINE_EMPTY;
        break;
    case CGAL_Line_2_Line_2_pair<R>::LINE:
        break;
    case CGAL_Line_2_Line_2_pair<R>::POINT:
        pair.intersection(ispoint);
        new_point = false;
        switch (CGAL_sign_of_cross(_support.direction(), cutter.direction())) {
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
CGAL__Straight_2<R>::
collinear_order(CGAL_Point_2<R> const &pt1, CGAL_Point_2<R> const & pt2) const
// Compare two points on the _support line.
// If the second point lies in the direction of the direction vector from
// the first point, the result is 1.
// Other results are -1 (other side) and 0 (coincidence).
{
    int diffsign;
    diffsign = CGAL_sign(pt2.cartesian(_main_dir)-pt1.cartesian(_main_dir));
    if (diffsign == 0)
        return 0;
    return (diffsign == _dir_sign) ? 1 : -1;
}




#endif
