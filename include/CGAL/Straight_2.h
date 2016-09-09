
// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/Straight_2.h
// package       : Intersections_2 (2.8)
// source        : straight_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : MPI, Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_STRAIGHT_2_H
#define CGAL_STRAIGHT_2_H



CGAL_BEGIN_NAMESPACE

class Straight_2_base_ {
public:
    enum states {EMPTY, POINT, SEGMENT, RAY, LINE};
    enum bound_states {NO_UNBOUNDED=0, MIN_UNBOUNDED=1, MAX_UNBOUNDED=2,
                        BOTH_UNBOUNDED = 3, LINE_EMPTY = 4};
protected:
                            Straight_2_base_() ;
    int                     main_dir_;  // support_ is x or y directed (0/1).
    int                     dir_sign_;  // sign of main direction coord.
    unsigned int            bound_state_; // 0, 1, 2, 3, 4.
public:
inline unsigned int            bound_state() const {return bound_state_;}
};

template <class R>
class Straight_2_: public Straight_2_base_ {
public:
                            Straight_2_() ;
                            Straight_2_(Point_2<R> const &point) ;
                            Straight_2_(Line_2<R> const &line) ;
                            Straight_2_(Ray_2<R> const &ray) ;
                            Straight_2_(Ray_2<R> const &ray,bool cooriented) ;
                            Straight_2_(Segment_2<R> const &seg) ;
                            ~Straight_2_() {}
    void                    cut_right_off(Line_2<R> const & cutter) ;
    int                     collinear_order(Point_2<R> const & p1,
                                            Point_2<R> const &p2) const ;
    void                    current(Line_2<R> &line) const;
    void                    current(Ray_2<R> &ray) const;
    void                    current(Segment_2<R> &seg) const;
    void                    current(Point_2<R> &point) const;
    states                  current_state() const;
    bool                    operator==(const Straight_2_<R>&) const;
    bool                    operator!=(const Straight_2_<R>&other) const
                { return !(*this == other);}
protected:
    Line_2<R>          support_;   // The supporting line.
    Point_2<R>         min_;
    Point_2<R>         max_;
};

CGAL_END_NAMESPACE


#include <CGAL/Line_2_Line_2_intersection.h>

CGAL_BEGIN_NAMESPACE

inline
Straight_2_base_::
Straight_2_base_()
{
    bound_state_ = LINE_EMPTY;
}

template <class R>
Straight_2_base_::states
Straight_2_<R>::
current_state() const
{
    switch (bound_state_) {
    case BOTH_UNBOUNDED:
        return LINE;
    case MIN_UNBOUNDED:
    case MAX_UNBOUNDED:
        return RAY;
    case NO_UNBOUNDED:
        return (collinear_order(min_, max_) == 0) ? POINT : SEGMENT;
    case LINE_EMPTY:
    default:
        return EMPTY;
    }
}

template <class R>
Straight_2_<R>::
Straight_2_()
{
    bound_state_ = LINE_EMPTY;
}

template <class R>
Straight_2_<R>::
Straight_2_(Line_2<R> const &line)
{
    support_ = line;
    Vector_2<R> const &dir = support_.direction().to_vector();
    main_dir_ = (CGAL_NTS abs(dir.x()) > CGAL_NTS abs(dir.y()) ) ? 0 : 1;
    dir_sign_ =
        CGAL_NTS sign(support_.direction().to_vector().cartesian(main_dir_));
    bound_state_ = BOTH_UNBOUNDED;
}

template <class R>
Straight_2_<R>::
Straight_2_(Point_2<R> const &point)
{
    support_ = Line_2<R>(point, Direction_2<R>(R::RT(1),R::RT(0)));
    main_dir_ = 0;
    dir_sign_ = 1;
    bound_state_ = NO_UNBOUNDED;
    min_ = point;
    max_ = point;
}

template <class R>
Straight_2_<R>::
Straight_2_(Ray_2<R> const &ray)
{
    support_ = ray.supporting_line();
    Vector_2<R> const &dir = ray.direction().to_vector();
//    main_dir_ = (CGAL_NTS abs(dir.hx()) > CGAL_NTS abs(dir.hy()) ) ? 0 : 1;
    main_dir_ = (CGAL_NTS abs(dir.x()) > CGAL_NTS abs(dir.y()) ) ? 0 : 1;
    dir_sign_ =
        CGAL_NTS sign(support_.direction().to_vector().cartesian(main_dir_));
    bound_state_ = MAX_UNBOUNDED;
    min_ = ray.start();
}

template <class R>
Straight_2_<R>::
Straight_2_(Ray_2<R> const &ray_,bool cooriented)
{
        Ray_2<R> const &ray = cooriented ? ray_ : ray_.opposite();
        support_ = ray.supporting_line();
        /* the supporting line is cooriented with the input ray iff
        cooriented is true */
    Vector_2<R> const &dir = ray.direction().to_vector();
//    main_dir_ = (CGAL_NTS abs(dir.hx()) > CGAL_NTS abs(dir.hy()) ) ? 0 : 1;
    main_dir_ = (CGAL_NTS abs(dir.x()) > CGAL_NTS abs(dir.y()) ) ? 0 : 1;
    dir_sign_ =
        CGAL_NTS sign(support_.direction().to_vector().cartesian(main_dir_));
    if (cooriented)
        {
            bound_state_ = MAX_UNBOUNDED;
                min_ = ray.start();
        }
        else
        {
                bound_state_ = MIN_UNBOUNDED;
                max_ = ray.start();
        }
}

template <class R>
Straight_2_<R>::
Straight_2_(Segment_2<R> const &seg)
{
    support_ = seg.supporting_line();
    Vector_2<R> const &dir = support_.direction().to_vector();
    main_dir_ = (CGAL_NTS abs(dir.x()) > CGAL_NTS abs(dir.y()) ) ? 0 : 1;
    dir_sign_ =
        CGAL_NTS sign(support_.direction().to_vector().cartesian(main_dir_));
    bound_state_ = NO_UNBOUNDED;
    min_ = seg.start();
    max_ = seg.end();
}


template <class R>
void
Straight_2_<R>::
current(Line_2<R> &line) const
{
    CGAL_kernel_assertion(bound_state_ == BOTH_UNBOUNDED);
    line = support_;
}

template <class R>
void
Straight_2_<R>::
current(Ray_2<R> &ray) const
{
    CGAL_kernel_assertion(bound_state_ == MIN_UNBOUNDED
                        || bound_state_ == MAX_UNBOUNDED);
    if (bound_state_ == MIN_UNBOUNDED) {
        ray = Ray_2<R>(max_, -support_.direction());
    } else {
        ray = Ray_2<R>(min_, support_.direction());
    }
}

template <class R>
void
Straight_2_<R>::
current(Segment_2<R> &seg) const
{
    CGAL_kernel_assertion(bound_state_ == NO_UNBOUNDED
                && collinear_order(min_, max_) != 0);
    seg = Segment_2<R>(min_, max_);
}

template <class R>
void
Straight_2_<R>::
current(Point_2<R> &pt) const
{
    CGAL_kernel_assertion(bound_state_ == NO_UNBOUNDED
                && collinear_order(min_, max_) == 0);
    pt = min_;
}


template <class R>
bool Straight_2_<R>::operator==(const Straight_2_<R>& s) const
{
  typedef Straight_2_<R> Straight_2;
  //    enum bound_states {NO_UNBOUNDED=0, MIN_UNBOUNDED=1, MAX_UNBOUNDED=2,
  //                    BOTH_UNBOUNDED = 3, LINE_EMPTY = 4};
  if (bound_state_!=s.bound_state()) return false;
  if (bound_state_==Straight_2::LINE_EMPTY) return true; // empty
  if (support_!=s.support_)
    return false; // on different lines, even if both are points.
  switch (bound_state_)
    {
    case Straight_2::NO_UNBOUNDED:
      return min_==s.min_ && max_==s.max_;
    case Straight_2::MAX_UNBOUNDED:
      return min_==s.min_;
    case Straight_2::MIN_UNBOUNDED:
      return max_==s.max_;
    case Straight_2::BOTH_UNBOUNDED:
      return true;
    }
  return false;
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
    return CGAL_NTS sign(cross(dir1.to_vector(), dir2.to_vector()));
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
    switch(orientation(dir1.to_vector(), dir2.to_vector()))  {
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
Straight_2_<R>::
cut_right_off(Line_2<R> const & cutter)
// cut off any part of this straight that is to the right of the cutter.
{
    if (bound_state_ == LINE_EMPTY)
        return;
    Point_2<R> ispoint;
    bool new_point;
    Line_2_Line_2_pair<R> pair(&support_, &cutter);
    switch (pair.intersection_type()) {
    case Line_2_Line_2_pair<R>::NO:
        if (cutter.has_on_negative_side(support_.point()))
            bound_state_ = LINE_EMPTY;
        break;
    case Line_2_Line_2_pair<R>::LINE:
        break;
    case Line_2_Line_2_pair<R>::POINT:
        pair.intersection(ispoint);
        new_point = false;
        switch (sign_of_cross(support_.direction(), cutter.direction())) {
        case -1: // new minimum.
            if (bound_state_ & MIN_UNBOUNDED) {
                new_point = true;
                bound_state_ ^= MIN_UNBOUNDED;  // exclusive or removes flag.
            } else {
                if (collinear_order(ispoint, min_) == -1)
                    new_point = true;
            }
            if (new_point) {
                if (!(bound_state_ & MAX_UNBOUNDED)
                    && collinear_order(ispoint, max_) == -1)
                    bound_state_ = LINE_EMPTY;
                else
                    min_ = ispoint;
            }
            break;
        case 0: // should not happen
            CGAL_kernel_warning_msg(false, "Internal CGAL error.");
            break;
        case 1: // new maximum
            if (bound_state_ & MAX_UNBOUNDED) {
                new_point = true;
                bound_state_ ^= MAX_UNBOUNDED;  // exclusive or removes flag.
            } else {
                if (collinear_order(ispoint, max_) == 1)
                    new_point = true;
            }
            if (new_point) {
                if (!(bound_state_ & MIN_UNBOUNDED)
                    && collinear_order(ispoint, min_) == 1)
                    bound_state_ = LINE_EMPTY;
                else
                    max_ = ispoint;
            }
            break;
        }
        break;
    }
}

template <class R>
int
Straight_2_<R>::
collinear_order(Point_2<R> const &pt1, Point_2<R> const & pt2) const
// Compare two points on the support_ line.
// If the second point lies in the direction of the direction vector from
// the first point, the result is 1.
// Other results are -1 (other side) and 0 (coincidence).
{
    int diffsign;
    diffsign = CGAL_NTS sign(pt2.cartesian(main_dir_)-pt1.cartesian(main_dir_));
    if (diffsign == 0)
        return 0;
    return (diffsign == dir_sign_) ? 1 : -1;
}

CGAL_END_NAMESPACE






#endif
