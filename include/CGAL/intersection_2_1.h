
#ifndef CGAL_INTERSECTION_2_1_H
#define CGAL_INTERSECTION_2_1_H

#include <CGAL/cartesian_classes.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/utils.h>
#include <CGAL/intermediate_result.h>


template <class R>
struct CGAL__Point2_imr : public CGAL__Imresult_base {
    ~CGAL__Point2_imr() {}
    CGAL_Point_2<R> point;
};

template <class R>
struct CGAL__Segment2_imr : public CGAL__Imresult_base {
    ~CGAL__Segment2_imr() {}
    CGAL_Segment_2<R> seg;
};

template <class R>
struct CGAL__Ray2_imr : public CGAL__Imresult_base {
    ~CGAL__Ray2_imr() {}
    CGAL_Ray_2<R> ray;
};

template <class R>
struct CGAL__Bbox2_line2_imr : public CGAL__Imresult_base {
    CGAL_Point_2<R> ref_point;
    CGAL_Vector_2<R> dir;
     R::FT min, max;
};





template <class R>
extern CGAL_Intersection_result  CGAL_intersection_type(
        const CGAL_Line_2<R> &line,
        const CGAL_Bbox_2 &box,
        CGAL_Intermediate_result &imr);


template <class R>
extern void
CGAL_intersection(
        const CGAL_Line_2<R> &line,
        const CGAL_Bbox_2 &box,
        CGAL_Intermediate_result &imr,
        CGAL_Segment_2<R> &seg);


template <class R>
extern void
CGAL_intersection(
        const CGAL_Line_2<R> &line,
        const CGAL_Bbox_2 &box,
        CGAL_Intermediate_result &imr,
        CGAL_Point_2<R> &pt);



template <class R>
CGAL_Intersection_result  CGAL_intersection_type(
        const CGAL_Line_2<R> &line,
        const CGAL_Bbox_2 &box,
        CGAL_Intermediate_result &imr)
{
    typedef  R::FT FT;
    CGAL__Bbox2_line2_imr<R> *imdata = new CGAL__Bbox2_line2_imr<R>;
    imr.new_pointer(imdata);
    imdata->ref_point = line.point();
    imdata->dir = line.direction().vector();
    bool all_values = true;
// first on x value
    if (imdata->dir.x() == FT(0)) {
        if (imdata->ref_point.x() < FT(box.xmin()))
            return CGAL_NO_INTERSECTION;
        if (imdata->ref_point.x() > FT(box.xmax()))
            return CGAL_NO_INTERSECTION;
    } else {
        FT newmin, newmax;
        if (imdata->dir.x() > FT(0)) {
            newmin = (FT(box.xmin())-imdata->ref_point.x())/imdata->dir.x();
            newmax = (FT(box.xmax())-imdata->ref_point.x())/imdata->dir.x();
        } else {
            newmin = (FT(box.xmax())-imdata->ref_point.x())/imdata->dir.x();
            newmax = (FT(box.xmin())-imdata->ref_point.x())/imdata->dir.x();
        }
        if (all_values) {
            imdata->min = newmin;
            imdata->max = newmax;
        } else {
            if (newmin > imdata->min)
                imdata->min = newmin;
            if (newmax < imdata->max)
                imdata->max = newmax;
            if (imdata->max < imdata->min)
                return CGAL_NO_INTERSECTION;
        }
        all_values = false;
    }
// now on y value
    if (imdata->dir.y() == FT(0)) {
        if (imdata->ref_point.y() < FT(box.ymin()))
            return CGAL_NO_INTERSECTION;
        if (imdata->ref_point.y() > FT(box.ymax()))
            return CGAL_NO_INTERSECTION;
    } else {
        FT newmin, newmax;
        if (imdata->dir.y() > FT(0)) {
            newmin = (FT(box.ymin())-imdata->ref_point.y())/imdata->dir.y();
            newmax = (FT(box.ymax())-imdata->ref_point.y())/imdata->dir.y();
        } else {
            newmin = (FT(box.ymax())-imdata->ref_point.y())/imdata->dir.y();
            newmax = (FT(box.ymin())-imdata->ref_point.y())/imdata->dir.y();
        }
        if (all_values) {
            imdata->min = newmin;
            imdata->max = newmax;
        } else {
            if (newmin > imdata->min)
                imdata->min = newmin;
            if (newmax < imdata->max)
                imdata->max = newmax;
            if (imdata->max < imdata->min)
                return CGAL_NO_INTERSECTION;
        }
        all_values = false;
    }
    CGAL_kernel_assertion(!all_values);
    if (imdata->max == imdata->min)
        return CGAL_POINT_INTERSECTION;
    return CGAL_SEGMENT_INTERSECTION;
}


template <class R>
void
CGAL_intersection(
        const CGAL_Line_2<R> &,
        const CGAL_Bbox_2 &,
        CGAL_Intermediate_result &imr,
        CGAL_Segment_2<R> &seg)
{
    CGAL__Bbox2_line2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Bbox2_line2_imr<R> *, imr.ptr());
    CGAL_kernel_assertion(imdata != 0);
    CGAL_Point_2<R> p1(imdata->ref_point + imdata->min*imdata->dir);
    CGAL_Point_2<R> p2(imdata->ref_point + imdata->max*imdata->dir);
    seg = CGAL_Segment_2<R>(p1, p2);
}

template <class R>
void
CGAL_intersection(
        const CGAL_Line_2<R> &,
        const CGAL_Bbox_2 &,
        CGAL_Intermediate_result &imr,
        CGAL_Point_2<R> &pt)
{
    CGAL__Bbox2_line2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Bbox2_line2_imr<R> *, imr.ptr());
    CGAL_kernel_assertion(imdata != 0);
    pt = (imdata->ref_point + imdata->min*imdata->dir);
}



template <class R>
inline CGAL_Intersection_result
CGAL_intersection_type(
        const CGAL_Bbox_2 &box,
        const CGAL_Line_2<R> &line,
        CGAL_Intermediate_result &imr)
{
    return CGAL_intersection_type(line, box, imr);
}

template <class R>
inline void
CGAL_intersection(
        const CGAL_Bbox_2 &box,
        const CGAL_Line_2<R> &line,
        CGAL_Intermediate_result &imr,
        CGAL_Segment_2<R> &seg)
{
    return CGAL_intersection(line, box, imr, seg);
}


/*
template <class R>
CGAL_Intersection_result
CGAL_intersection_type(
        const CGAL_Line_2<R> &l1,
        const CGAL_Line_2<R> &l2,
        CGAL_Intermediate_result &imr);

template <class R>
CGAL_Point_2<R>
CGAL_intersection_point(
        const CGAL_Line_2<R> &,
        const CGAL_Line_2<R> &,
        const CGAL_Intermediate_result &imr);
*/



template <class R, class POINT, class RT>
bool construct_if_finite(POINT &pt, RT x, RT y, RT w, R &)
{
    typedef  R::FT FT;
    CGAL_kernel_precondition(is_finite(x) && is_finite(y) && w != RT(0));
    if (!is_finite(FT(x)/FT(w)) || !is_finite(FT(y)/FT(w)))
        return false;
    pt = POINT(x, y, w);
    return true;
}

template <class R>
CGAL_Intersection_result  CGAL_intersection_type(
        const CGAL_Line_2<R> &l1,
        const CGAL_Line_2<R> &l2,
        CGAL_Intermediate_result &imr)
{
    typedef  R::RT RT;
    RT nom1, nom2, denom;
    denom = l1.a()*l2.b() - l2.a()*l1.b();
    if (denom == RT(0)) {
        if (RT(0) == (l1.a()*l2.c() - l2.a()*l1.c()) &&
            RT(0) == (l1.b()*l2.c() - l2.b()*l1.c()))
            return CGAL_LINE_INTERSECTION;
        else
            return CGAL_NO_INTERSECTION;
    }
    nom1 = (l1.b()*l2.c() - l2.b()*l1.c());
    if (!is_finite(nom1))
        return CGAL_NO_INTERSECTION;
    nom2 = (l2.a()*l1.c() - l1.a()*l2.c());
    if (!is_finite(nom2))
        return CGAL_NO_INTERSECTION;
    CGAL_Point_2<R> intersectionpoint;
    R dummyR;


//    if (!construct_if_finite<R>( intersectionpoint, nom1, nom2, denom) )
//        return CGAL_NO_INTERSECTION;
    if (!construct_if_finite( intersectionpoint, nom1, nom2, denom, dummyR) )
        return CGAL_NO_INTERSECTION;
// Store the intersection point in the intermediate result and return.
    CGAL__Point2_imr<R> *imdata;
    imdata = new CGAL__Point2_imr<R>;
    imr.new_pointer(imdata);
    imdata->point = intersectionpoint;
    return CGAL_POINT_INTERSECTION;
}

template <class R>
void
CGAL_intersection(
        const CGAL_Line_2<R> &,
        const CGAL_Line_2<R> &,
        const CGAL_Intermediate_result &imr,
        CGAL_Point_2<R> &pt)
{
    CGAL__Point2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Point2_imr<R> *, imr.ptr());
    pt = imdata->point;
}

template <class R>
void
CGAL_intersection(
        const CGAL_Line_2<R> &a,
        const CGAL_Line_2<R> &,
        const CGAL_Intermediate_result &,
        CGAL_Line_2<R> &l)
{
    l = a;
}



/*
template <class R>
extern CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Segment_2<R> &s1,
    const CGAL_Line_2<R> &s2,
    CGAL_Intermediate_result &imr);

template <class R>
extern void
CGAL_intersection(
    const CGAL_Segment_2<R> &,
    const CGAL_Line_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt);

template <class R>
extern void
CGAL_intersection(
    const CGAL_Segment_2<R> &,
    const CGAL_Line_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Segment_2<R> &result);
*/



template <class R>
CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Line_2<R> &line,
    CGAL_Intermediate_result &imr)
{
    CGAL_Intermediate_result llresult;
    const CGAL_Line_2<R> &l1 = seg.supporting_line();
    switch ( CGAL_intersection_type(l1, line, imr)) {
    case CGAL_NO_INTERSECTION:
        return CGAL_NO_INTERSECTION;
    case CGAL_POINT_INTERSECTION: {
        CGAL_Point_2<R> intersectionpoint;
        CGAL_intersection(l1, line, imr, intersectionpoint);
        if (seg.collinear_is_on(intersectionpoint) ) {
            CGAL__Point2_imr<R> *imdata;
            imdata = new CGAL__Point2_imr<R>;
            imdata->point = intersectionpoint;
            imr.new_pointer(imdata);
            return CGAL_POINT_INTERSECTION;
        } else {
            return CGAL_NO_INTERSECTION;
        }
    }
    case CGAL_LINE_INTERSECTION: {
        return CGAL_SEGMENT_INTERSECTION;
    }
    }
    return CGAL_NO_INTERSECTION;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Segment_2<R> &,
    const CGAL_Line_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt)
{
    CGAL__Point2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Point2_imr<R> *, imr.ptr());
    pt = imdata->point;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Line_2<R> &,
    const CGAL_Intermediate_result &,
    CGAL_Segment_2<R> &result)
{
    result = seg;
}


template <class R>
inline CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Line_2<R> &line,
    const CGAL_Segment_2<R> &seg,
    CGAL_Intermediate_result &imr)
{
    return CGAL_intersection_type(seg, line, imr);
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Line_2<R> &line,
    const CGAL_Segment_2<R> &seg,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &result)
{
    CGAL_intersection(seg, line, imr, result);
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Line_2<R> &line,
    const CGAL_Segment_2<R> &seg,
    const CGAL_Intermediate_result &imr,
    CGAL_Segment_2<R> &result)
{
    CGAL_intersection(seg, line, imr, result);
}


/*
template <class R>
CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Segment_2<R> &s1,
    const CGAL_Segment_2<R> &s2,
    CGAL_Intermediate_result &imr);

template <class R>
void
CGAL_intersection(
    const CGAL_Segment_2<R> &,
    const CGAL_Segment_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt);
*/


template <class R>
CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Segment_2<R> &s1,
    const CGAL_Segment_2<R> &s2,
    CGAL_Intermediate_result &imr)
{
    if (!do_overlap(s1.bbox(), s2.bbox()))
        return CGAL_NO_INTERSECTION;
    CGAL_Intermediate_result llresult;
    const CGAL_Line_2<R> &l1 = s1.supporting_line();
    const CGAL_Line_2<R> &l2 = s2.supporting_line();
    switch ( CGAL_intersection_type(l1, l2, imr)) {
    case CGAL_NO_INTERSECTION:
        return CGAL_NO_INTERSECTION;
    case CGAL_POINT_INTERSECTION: {
        CGAL_Point_2<R> intersectionpoint;
        CGAL_intersection(l1, l2, imr, intersectionpoint);
        if (s1.collinear_is_on(intersectionpoint)
                && s2.collinear_is_on(intersectionpoint) ) {
            CGAL__Point2_imr<R> *imdata;
            imdata = new CGAL__Point2_imr<R>;
            imdata->point = intersectionpoint;
            imr.new_pointer(imdata);
            return CGAL_POINT_INTERSECTION;
        } else {
            return CGAL_NO_INTERSECTION;
        }
    }
    case CGAL_LINE_INTERSECTION: {
        typedef  R::RT RT;
        const CGAL_Point_2<R> &start1 = s1.start();
        const CGAL_Point_2<R> &end1 = s1.end();
        const CGAL_Point_2<R> &start2 = s2.start();
        const CGAL_Point_2<R> &end2 = s2.end();
        CGAL_Vector_2<R> diff1 = end1-start1;
        const CGAL_Point_2<R> *minpt,  *maxpt;
        if (abs(diff1.x()) > abs(diff1.y())) {
            if (start1.x() < end1.x()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.x() < end2.x()) {
                if (start2.x() > minpt->x()) {
                    minpt = &start2;
                }
                if (end2.x() < maxpt->x()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.x() > minpt->x()) {
                    minpt = &end2;
                }
                if (start2.x() < maxpt->x()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->x() < minpt->x())
                return CGAL_NO_INTERSECTION;
            if (maxpt->x() == minpt->x()) {
                CGAL__Point2_imr<R> *imdata;
                imdata = new CGAL__Point2_imr<R>;
                imdata->point = *minpt;
                imr.new_pointer(imdata);
                return CGAL_POINT_INTERSECTION;
            }
            CGAL__Segment2_imr<R> *imdata;
            imdata = new CGAL__Segment2_imr<R>;
            imdata->seg = CGAL_Segment_2<R>(*minpt, *maxpt);
            imr.new_pointer(imdata);
            return CGAL_SEGMENT_INTERSECTION; 
        } else {
            if (start1.y() < end1.y()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (start2.y() < end2.y()) {
                if (start2.y() > minpt->y()) {
                    minpt = &start2;
                }
                if (end2.y() < maxpt->y()) {
                    maxpt = &end2;
                }
            } else {
                if (end2.y() > minpt->y()) {
                    minpt = &end2;
                }
                if (start2.y() < maxpt->y()) {
                    maxpt = &start2;
                }
            }
            if (maxpt->y() < minpt->y())
                return CGAL_NO_INTERSECTION;
            if (maxpt->y() == minpt->y()) {
                CGAL__Point2_imr<R> *imdata;
                imdata = new CGAL__Point2_imr<R>;
                imdata->point = *minpt;
                imr.new_pointer(imdata);
                return CGAL_POINT_INTERSECTION;
            }
            CGAL__Segment2_imr<R> *imdata;
            imdata = new CGAL__Segment2_imr<R>;
            imdata->seg = CGAL_Segment_2<R>(*minpt, *maxpt);
            imr.new_pointer(imdata);
            return CGAL_SEGMENT_INTERSECTION; 
        } 
    }
    }
    return CGAL_NO_INTERSECTION;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Segment_2<R> &,
    const CGAL_Segment_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt)
{
    CGAL__Point2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Point2_imr<R> *, imr.ptr());
    pt = imdata->point;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Segment_2<R> &,
    const CGAL_Segment_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Segment_2<R> &seg)
{
    CGAL__Segment2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Segment2_imr<R> *, imr.ptr());
    seg = imdata->seg;
}



/*
template <class R>
extern CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Line_2<R> &line,
    CGAL_Intermediate_result &imr);

template <class R>
extern void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Line_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &result);

template <class R>
extern void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Line_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Ray_2<R> &result);
*/



template <class R>
CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Line_2<R> &line,
    CGAL_Intermediate_result &imr)
{
    CGAL_Intermediate_result llresult;
    const CGAL_Line_2<R> &l1 = ray.supporting_line();
    switch ( CGAL_intersection_type(l1, line, imr)) {
    case CGAL_NO_INTERSECTION:
        return CGAL_NO_INTERSECTION;
    case CGAL_POINT_INTERSECTION: {
        CGAL_Point_2<R> intersectionpoint;
        CGAL_intersection(l1, line, imr, intersectionpoint);
        if (ray.collinear_is_on(intersectionpoint) ) {
            CGAL__Point2_imr<R> *imdata;
            imdata = new CGAL__Point2_imr<R>;
            imdata->point = intersectionpoint;
            imr.new_pointer(imdata);
            return CGAL_POINT_INTERSECTION;
        } else {
            return CGAL_NO_INTERSECTION;
        }
    }
    case CGAL_LINE_INTERSECTION: {
        return CGAL_RAY_INTERSECTION;
    }
    }
    return CGAL_NO_INTERSECTION;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Line_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt)
{
    CGAL__Point2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Point2_imr<R> *, imr.ptr());
    pt = imdata->point;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Line_2<R> &,
    const CGAL_Intermediate_result &,
    CGAL_Ray_2<R> &result)
{
    result = ray;
}


template <class R>
inline CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Line_2<R> &line,
    const CGAL_Ray_2<R> &ray,
    CGAL_Intermediate_result &imr)
{
    return CGAL_intersection_type(ray, line, imr);
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Line_2<R> &line,
    const CGAL_Ray_2<R> &ray,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &result)
{
    CGAL_intersection(ray, line, imr, result);
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Line_2<R> &line,
    const CGAL_Ray_2<R> &ray,
    const CGAL_Intermediate_result &imr,
    CGAL_Ray_2<R> &result)
{
    CGAL_intersection(ray, line, imr, result);
}



/*
template <class R>
extern CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Ray_2<R> &s1,
    const CGAL_Segment_2<R> &s2,
    CGAL_Intermediate_result &imr);

template <class R>
extern void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Segment_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt);

template <class R>
extern void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Segment_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Segment_2<R> &seg);
*/


template <class R>
CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Ray_2<R> &ray,
    const CGAL_Segment_2<R> &seg,
    CGAL_Intermediate_result &imr)
{
//    if (!do_overlap(ray.bbox(), seg.bbox()))
//        return CGAL_NO_INTERSECTION;
    CGAL_Intermediate_result llresult;
    const CGAL_Line_2<R> &l1 = ray.supporting_line();
    const CGAL_Line_2<R> &l2 = seg.supporting_line();
    switch ( CGAL_intersection_type(l1, l2, imr)) {
    case CGAL_NO_INTERSECTION:
        return CGAL_NO_INTERSECTION;
    case CGAL_POINT_INTERSECTION: {
        CGAL_Point_2<R> intersectionpoint;
        CGAL_intersection(l1, l2, imr, intersectionpoint);
        if (ray.collinear_is_on(intersectionpoint)
                && seg.collinear_is_on(intersectionpoint) ) {
            CGAL__Point2_imr<R> *imdata;
            imdata = new CGAL__Point2_imr<R>;
            imdata->point = intersectionpoint;
            imr.new_pointer(imdata);
            return CGAL_POINT_INTERSECTION;
        } else {
            return CGAL_NO_INTERSECTION;
        }
    }
    case CGAL_LINE_INTERSECTION: {
        typedef  R::RT RT;
        const CGAL_Point_2<R> &start1 = seg.start();
        const CGAL_Point_2<R> &end1 = seg.end();
        const CGAL_Point_2<R> &start2 = ray.start();
        const CGAL_Point_2<R> *minpt,  *maxpt;
        CGAL_Vector_2<R> diff1 = end1-start1;
        if (abs(diff1.x()) > abs(diff1.y())) {
            if (start1.x() < end1.x()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (ray.direction().vector().x() > R::FT(0)) {
                if (maxpt->x() < start2.x())
                    return CGAL_NO_INTERSECTION;
                if (maxpt->x() == start2.x()) {
                    CGAL__Point2_imr<R> *imdata;
                    imdata = new CGAL__Point2_imr<R>;
                    imdata->point = *maxpt;
                    imr.new_pointer(imdata);
                    return CGAL_POINT_INTERSECTION;
                }
                CGAL__Segment2_imr<R> *imdata;
                imdata = new CGAL__Segment2_imr<R>;
                if (minpt->x() < start2.x()) {
                    imdata->seg = CGAL_Segment_2<R> (start2, *maxpt);
                } else {
                    imdata->seg = seg;
                }
                imr.new_pointer(imdata);
                return CGAL_SEGMENT_INTERSECTION;
            } else {
                if (minpt->x() > start2.x())
                    return CGAL_NO_INTERSECTION;
                if (minpt->x() == start2.x()) {
                    CGAL__Point2_imr<R> *imdata;
                    imdata = new CGAL__Point2_imr<R>;
                    imdata->point = *minpt;
                    imr.new_pointer(imdata);
                    return CGAL_POINT_INTERSECTION;
                }
                CGAL__Segment2_imr<R> *imdata;
                imdata = new CGAL__Segment2_imr<R>;
                if (maxpt->x() > start2.x()) {
                    imdata->seg = CGAL_Segment_2<R> (start2, *minpt);
                } else {
                    imdata->seg = seg;
                }
                imr.new_pointer(imdata);
                return CGAL_SEGMENT_INTERSECTION;
            }
        } else {
            if (start1.y() < end1.y()) {
                minpt = &start1;
                maxpt = &end1;
            } else {
                minpt = &end1;
                maxpt = &start1;
            }
            if (ray.direction().vector().y() > R::FT(0)) {
                if (maxpt->y() < start2.y())
                    return CGAL_NO_INTERSECTION;
                if (maxpt->y() == start2.y()) {
                    CGAL__Point2_imr<R> *imdata;
                    imdata = new CGAL__Point2_imr<R>;
                    imdata->point = *maxpt;
                    imr.new_pointer(imdata);
                    return CGAL_POINT_INTERSECTION;
                }
                CGAL__Segment2_imr<R> *imdata;
                imdata = new CGAL__Segment2_imr<R>;
                if (minpt->y() < start2.y()) {
                    imdata->seg = CGAL_Segment_2<R> (start2, *maxpt);
                } else {
                    imdata->seg = seg;
                }
                imr.new_pointer(imdata);
                return CGAL_SEGMENT_INTERSECTION;
            } else {
                if (minpt->y() > start2.y())
                    return CGAL_NO_INTERSECTION;
                if (minpt->y() == start2.y()) {
                    CGAL__Point2_imr<R> *imdata;
                    imdata = new CGAL__Point2_imr<R>;
                    imdata->point = *minpt;
                    imr.new_pointer(imdata);
                    return CGAL_POINT_INTERSECTION;
                }
                CGAL__Segment2_imr<R> *imdata;
                imdata = new CGAL__Segment2_imr<R>;
                if (maxpt->y() > start2.y()) {
                    imdata->seg = CGAL_Segment_2<R> (start2, *minpt);
                } else {
                    imdata->seg = seg;
                }
                imr.new_pointer(imdata);
                return CGAL_SEGMENT_INTERSECTION;
            }
        } 
    }
    }
    return CGAL_NO_INTERSECTION;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Segment_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt)
{
    CGAL__Point2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Point2_imr<R> *, imr.ptr());
    pt = imdata->point;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Segment_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Segment_2<R> &seg)
{
    CGAL__Segment2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Segment2_imr<R> *, imr.ptr());
    seg = imdata->seg;
}


template <class R>
inline CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Ray_2<R> &ray,
    CGAL_Intermediate_result &imr)
{
    return CGAL_intersection_type(ray, seg, imr);
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Ray_2<R> &ray,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt)
{
    CGAL_intersection(ray, seg, imr, pt);
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Segment_2<R> &seg,
    const CGAL_Ray_2<R> &ray,
    const CGAL_Intermediate_result &imr,
    CGAL_Segment_2<R> &result)
{
    CGAL_intersection(ray, seg, imr, result);
}
#endif

/*
template <class R>
extern CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Ray_2<R> &s1,
    const CGAL_Ray_2<R> &s2,
    CGAL_Intermediate_result &imr);

template <class R>
extern void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Ray_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt);

template <class R>
extern void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Ray_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Segment_2<R> &pt);

template <class R>
extern void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Ray_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Ray_2<R> &pt);
*/


template <class R>
CGAL_Intersection_result
CGAL_intersection_type(
    const CGAL_Ray_2<R> &r1,
    const CGAL_Ray_2<R> &r2,
    CGAL_Intermediate_result &imr)
{
//    if (!do_overlap(r1.bbox(), r2.bbox()))
//        return CGAL_NO_INTERSECTION;
    CGAL_Intermediate_result llresult;
    const CGAL_Line_2<R> &l1 = r1.supporting_line();
    const CGAL_Line_2<R> &l2 = r2.supporting_line();
    switch ( CGAL_intersection_type(l1, l2, imr)) {
    case CGAL_NO_INTERSECTION:
        return CGAL_NO_INTERSECTION;
    case CGAL_POINT_INTERSECTION: {
        CGAL_Point_2<R> intersectionpoint;
        CGAL_intersection(l1, l2, imr, intersectionpoint);
        if (r1.collinear_is_on(intersectionpoint)
                && r2.collinear_is_on(intersectionpoint) ) {
            CGAL__Point2_imr<R> *imdata;
            imdata = new CGAL__Point2_imr<R>;
            imdata->point = intersectionpoint;
            imr.new_pointer(imdata);
            return CGAL_POINT_INTERSECTION;
        } else {
            return CGAL_NO_INTERSECTION;
        }
    }
    case CGAL_LINE_INTERSECTION: {
        typedef  R::RT RT;
        const CGAL_Vector_2<R> &dir1 = r1.direction().vector();
        const CGAL_Vector_2<R> &dir2 = r2.direction().vector();
        if (abs(dir1.x()) > abs(dir1.y())) {
            if (dir1.x() > 0) {
                if (dir2.x() > 0) {
                    CGAL__Ray2_imr<R> *imdata;
                    imdata = new CGAL__Ray2_imr<R>;
                    imdata->ray = (r1.start().x() < r2.start().x()) ? r2 : r1;
                    imr.new_pointer(imdata);
                    return CGAL_RAY_INTERSECTION;
                } else {
                    if (r1.start().x() > r2.start().x())
                        return CGAL_NO_INTERSECTION;
                    if (r1.start().x() == r2.start().x()) {
                        CGAL__Point2_imr<R> *imdata;
                        imdata = new CGAL__Point2_imr<R>;
                        imdata->point = r1.start();
                        imr.new_pointer(imdata);
                        return CGAL_POINT_INTERSECTION;
                    }
                    CGAL__Segment2_imr<R> *imdata;
                    imdata = new CGAL__Segment2_imr<R>;
                    imdata->seg = CGAL_Segment_2<R>(r1.start(), r2.start());
                    imr.new_pointer(imdata);
                    return CGAL_SEGMENT_INTERSECTION;
                }
            } else {
                if (dir2.x() < 0) {
                    CGAL__Ray2_imr<R> *imdata;
                    imdata = new CGAL__Ray2_imr<R>;
                    imdata->ray = (r1.start().x() > r2.start().x()) ? r2 : r1;
                    imr.new_pointer(imdata);
                    return CGAL_RAY_INTERSECTION;
                } else {
                    if (r1.start().x() < r2.start().x())
                        return CGAL_NO_INTERSECTION;
                    if (r1.start().x() == r2.start().x()) {
                        CGAL__Point2_imr<R> *imdata;
                        imdata = new CGAL__Point2_imr<R>;
                        imdata->point = r1.start();
                        imr.new_pointer(imdata);
                        return CGAL_POINT_INTERSECTION;
                    }
                    CGAL__Segment2_imr<R> *imdata;
                    imdata = new CGAL__Segment2_imr<R>;
                    imdata->seg = CGAL_Segment_2<R>(r1.start(), r2.start());
                    imr.new_pointer(imdata);
                    return CGAL_SEGMENT_INTERSECTION;
                }
            }
            
        } else {
            if (dir1.y() > 0) {
                if (dir2.y() > 0) {
                    CGAL__Ray2_imr<R> *imdata;
                    imdata = new CGAL__Ray2_imr<R>;
                    imdata->ray = (r1.start().y() < r2.start().y()) ? r2 : r1;
                    imr.new_pointer(imdata);
                    return CGAL_RAY_INTERSECTION;
                } else {
                    if (r1.start().y() > r2.start().y())
                        return CGAL_NO_INTERSECTION;
                    if (r1.start().y() == r2.start().y()) {
                        CGAL__Point2_imr<R> *imdata;
                        imdata = new CGAL__Point2_imr<R>;
                        imdata->point = r1.start();
                        imr.new_pointer(imdata);
                        return CGAL_POINT_INTERSECTION;
                    }
                    CGAL__Segment2_imr<R> *imdata;
                    imdata = new CGAL__Segment2_imr<R>;
                    imdata->seg = CGAL_Segment_2<R>(r1.start(), r2.start());
                    imr.new_pointer(imdata);
                    return CGAL_SEGMENT_INTERSECTION;
                }
            } else {
                if (dir2.y() < 0) {
                    CGAL__Ray2_imr<R> *imdata;
                    imdata = new CGAL__Ray2_imr<R>;
                    imdata->ray = (r1.start().y() > r2.start().y()) ? r2 : r1;
                    imr.new_pointer(imdata);
                    return CGAL_RAY_INTERSECTION;
                } else {
                    if (r1.start().y() < r2.start().y())
                        return CGAL_NO_INTERSECTION;
                    if (r1.start().y() == r2.start().y()) {
                        CGAL__Point2_imr<R> *imdata;
                        imdata = new CGAL__Point2_imr<R>;
                        imdata->point = r1.start();
                        imr.new_pointer(imdata);
                        return CGAL_POINT_INTERSECTION;
                    }
                    CGAL__Segment2_imr<R> *imdata;
                    imdata = new CGAL__Segment2_imr<R>;
                    imdata->seg = CGAL_Segment_2<R>(r1.start(), r2.start());
                    imr.new_pointer(imdata);
                    return CGAL_SEGMENT_INTERSECTION;
                }
            }
            
        } 
    }
    }
    return CGAL_NO_INTERSECTION;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Ray_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Point_2<R> &pt)
{
    CGAL__Point2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Point2_imr<R> *, imr.ptr());
    pt = imdata->point;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Ray_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Segment_2<R> &result)
{
    CGAL__Segment2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Segment2_imr<R> *, imr.ptr());
    result = imdata->seg;
}

template <class R>
inline void
CGAL_intersection(
    const CGAL_Ray_2<R> &,
    const CGAL_Ray_2<R> &,
    const CGAL_Intermediate_result &imr,
    CGAL_Ray_2<R> &result)
{
    CGAL__Ray2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__Ray2_imr<R> *, imr.ptr());
    result = imdata->ray;
}


