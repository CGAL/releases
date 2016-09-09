 

#ifndef CGAL_STRAIGHT_2_H
#define CGAL_STRAIGHT_2_H

 

template <class R>
class CGAL__Straight_2 {
public:
    enum states {EMPTY, POINT, SEGMENT, RAY, LINE};
                            CGAL__Straight_2() ;
                            CGAL__Straight_2(CGAL_Line_2<R> const &line) ;
                            CGAL__Straight_2(CGAL_Ray_2<R> const &ray) ;
                            CGAL__Straight_2(CGAL_Segment_2<R> const &seg) ;
                            ~CGAL__Straight_2() {}
    void                    cut_right_off(CGAL_Line_2<R> const & cutter) ;
    int                     collinear_order(CGAL_Point_2<R> const & p1,
                                            CGAL_Point_2<R> const &p2) const ;
    states                  current_state() const;
    void                    current(CGAL_Line_2<R> &line) const;
    void                    current(CGAL_Ray_2<R> &ray) const;
    void                    current(CGAL_Segment_2<R> &seg) const;
    void                    current(CGAL_Point_2<R> &point) const;
protected:
    enum bound_states {NO_UNBOUNDED=0, MIN_UNBOUNDED=1, MAX_UNBOUNDED=2,
                        BOTH_UNBOUNDED = 3, LINE_EMPTY = 4};
    CGAL_Line_2<R>          _support;   // The supporting line.
    int                     _main_dir;  // _support is x or y directed (0/1).
    int                     _dir_sign;  // sign of main direction coord.
    unsigned int            _bound_state; // 0, 1, 2, 3, 4.
    CGAL_Point_2<R>         _min;
    CGAL_Point_2<R>         _max;
};


 

#include <CGAL/Line_2_Line_2_pair.h>

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
//    _main_dir = (CGAL_abs(dir.hx()) > CGAL_abs(dir.hy()) ) ? 0 : 1;
    _main_dir = (CGAL_abs(dir.x()) > CGAL_abs(dir.y()) ) ? 0 : 1;
    _dir_sign = CGAL_sign(_support.direction().vector().cartesian(_main_dir));
    _bound_state = BOTH_UNBOUNDED;
}

template <class R>
CGAL__Straight_2<R>::
CGAL__Straight_2(CGAL_Ray_2<R> const &ray)
{
    _support = ray.supporting_line();
    CGAL_Vector_2<R> const &dir(ray.direction().vector());
//    _main_dir = (CGAL_abs(dir.hx()) > CGAL_abs(dir.hy()) ) ? 0 : 1;
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
//    _main_dir = (CGAL_abs(dir.hx()) > CGAL_abs(dir.hy()) ) ? 0 : 1;
    _main_dir = (CGAL_abs(dir.x()) > CGAL_abs(dir.y()) ) ? 0 : 1;
    _dir_sign = CGAL_sign(_support.direction().vector().cartesian(_main_dir));
    _bound_state = NO_UNBOUNDED;
    _min = seg.start();
    _max = seg.end();
}

template <class R>
CGAL__Straight_2<R>::states
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

template <class FT>
FT
cross(CGAL_Vector_2< C<FT> > const &vec1, CGAL_Vector_2< C<FT> > const &vec2)
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
        if (cutter.where_is(_support.point()) == CGAL_RIGHT)
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
