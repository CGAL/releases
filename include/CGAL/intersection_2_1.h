
#ifndef CGAL_INTERSECTION_2_1_H
#define CGAL_INTERSECTION_2_1_H

#include <CGAL/cartesian_classes.h>
#include <CGAL/doublefield.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/utils.h>
#include <CGAL/intermediate_result.h>



template <class R>
extern CGAL_Intersection_result  CGAL_intersectiontype(
        const CGAL_Line_2<R> &line,
        const CGAL_Bbox_2 &box,
        CGAL_intermediate_result &imr);


template <class R>
extern CGAL_Segment_2<R>
CGAL_intersection_segment(
        const CGAL_Line_2<R> &line,
        const CGAL_Bbox_2 &box,
        CGAL_intermediate_result &imr);


template <class R>
extern CGAL_Point_2<R>
CGAL_intersection_point(
        const CGAL_Line_2<R> &line,
        const CGAL_Bbox_2 &box,
        CGAL_intermediate_result &imr);


template <class R>
struct CGAL__bbox2_line2_imr : public CGAL__imresult_base {
    CGAL_Point_2<R> ref_point;
    CGAL_Vector_2<R> dir;
    R::FT min, max;
};

template <class R>
CGAL_Intersection_result  CGAL_intersectiontype(
        const CGAL_Line_2<R> &line,
        const CGAL_Bbox_2 &box,
        CGAL_intermediate_result &imr)
{
    CGAL__bbox2_line2_imr<R> *imdata = new CGAL__bbox2_line2_imr<R>;
    imr.new_pointer(imdata);
    imdata->ref_point = line.point();
    imdata->dir = line.direction().vector();
    bool all_values = true;
// first on x value
    if (imdata->dir.x() == R::FT(0)) {
        if (imdata->ref_point.x() < R::FT(box.xmin()))
            return CGAL_NO_INTERSECTION;
        if (imdata->ref_point.x() > R::FT(box.xmax()))
            return CGAL_NO_INTERSECTION;
    } else {
        R::FT newmin, newmax;
        if (imdata->dir.x() > R::FT(0)) {
            newmin = (R::FT(box.xmin())-imdata->ref_point.x())/imdata->dir.x();
            newmax = (R::FT(box.xmax())-imdata->ref_point.x())/imdata->dir.x();
        } else {
            newmin = (R::FT(box.xmax())-imdata->ref_point.x())/imdata->dir.x();
            newmax = (R::FT(box.xmin())-imdata->ref_point.x())/imdata->dir.x();
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
    if (imdata->dir.y() == R::FT(0)) {
        if (imdata->ref_point.y() < R::FT(box.ymin()))
            return CGAL_NO_INTERSECTION;
        if (imdata->ref_point.y() > R::FT(box.ymax()))
            return CGAL_NO_INTERSECTION;
    } else {
        R::FT newmin, newmax;
        if (imdata->dir.y() > R::FT(0)) {
            newmin = (R::FT(box.ymin())-imdata->ref_point.y())/imdata->dir.y();
            newmax = (R::FT(box.ymax())-imdata->ref_point.y())/imdata->dir.y();
        } else {
            newmin = (R::FT(box.ymax())-imdata->ref_point.y())/imdata->dir.y();
            newmax = (R::FT(box.ymin())-imdata->ref_point.y())/imdata->dir.y();
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
CGAL_Segment_2<R>
CGAL_intersection_segment(
        const CGAL_Line_2<R> &,
        const CGAL_Bbox_2 &,
        CGAL_intermediate_result &imr)
{
    CGAL__bbox2_line2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__bbox2_line2_imr<R> *, imr.ptr());
    CGAL_kernel_assertion(imdata != 0);
    CGAL_Point_2<R> p1(imdata->ref_point + imdata->min*imdata->dir);
    CGAL_Point_2<R> p2(imdata->ref_point + imdata->max*imdata->dir);
    return CGAL_Segment_2<R>(p1, p2);
}

template <class R>
CGAL_Point_2<R>
CGAL_intersection_point(
        const CGAL_Line_2<R> &,
        const CGAL_Bbox_2 &,
        CGAL_intermediate_result &imr)
{
    CGAL__bbox2_line2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__bbox2_line2_imr<R> *, imr.ptr());
    CGAL_kernel_assertion(imdata != 0);
    return (imdata->ref_point + imdata->min*imdata->dir);
}



template <class R>
inline CGAL_Intersection_result
CGAL_intersectiontype(
        const CGAL_Bbox_2 &box,
        const CGAL_Line_2<R> &line,
        CGAL_intermediate_result &imr)
{
    return CGAL_intersectiontype(line, box, imr);
}

template <class R>
inline CGAL_Segment_2<R>
CGAL_intersection_segment(
        const CGAL_Bbox_2 &box,
        const CGAL_Line_2<R> &line,
        CGAL_intermediate_result &imr)
{
    return CGAL_intersection_segment(line, box, imr);
}



template <class R>
CGAL_Intersection_result
CGAL_intersectiontype(
        const CGAL_Line_2<R> &l1,
        const CGAL_Line_2<R> &l2,
        CGAL_intermediate_result &imr);

template <class R>
CGAL_Point_2<R>
CGAL_intersection_point(
        const CGAL_Line_2<R> &,
        const CGAL_Line_2<R> &,
        const CGAL_intermediate_result &imr);


template <class R>
struct CGAL__line2_line2_imr : public CGAL__imresult_base {
    ~CGAL__line2_line2_imr() {}
    CGAL_Point_2<R> intersectionpoint;
};
template <class R>
CGAL_Intersection_result  CGAL_intersectiontype(
        const CGAL_Line_2<R> &l1,
        const CGAL_Line_2<R> &l2,
        CGAL_intermediate_result &imr)
{
    R::FT n1, n2, denom;
    denom = l1.a()*l2.b() - l2.a()*l1.b();
    if (denom == R::FT(0)) {
        if (R::FT(0) == (l1.a()*l2.c() - l2.a()*l1.c()) &&
            R::FT(0) == (l1.b()*l2.c() - l2.b()*l1.c()))
            return CGAL_SEGMENT_INTERSECTION;
        else
            return CGAL_NO_INTERSECTION;
    }
    n1 = (l1.b()*l2.c() - l2.b()*l1.c())/denom;
    if (!is_finite(n1))
        return CGAL_NO_INTERSECTION;
    n2 = (l2.a()*l1.c() - l1.a()*l2.c())/denom;
    if (!is_finite(n2))
        return CGAL_NO_INTERSECTION;
    CGAL__line2_line2_imr<R> *imdata;
    imdata = new CGAL__line2_line2_imr<R>;
    imr.new_pointer(imdata);
    imdata->intersectionpoint = CGAL_Point_2<R>(n1, n2);
    return CGAL_POINT_INTERSECTION;
}

template <class R>
CGAL_Point_2<R>
CGAL_intersection_point(
        const CGAL_Line_2<R> &,
        const CGAL_Line_2<R> &,
        const CGAL_intermediate_result &imr)
{
    CGAL__line2_line2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__line2_line2_imr<R> *, imr.ptr());
    return imdata->intersectionpoint;
}




template <class R>
CGAL_Intersection_result
CGAL_intersectiontype(
    const CGAL_Segment_2<R> &s1,
    const CGAL_Segment_2<R> &s2,
    CGAL_intermediate_result &imr);

template <class R>
CGAL_Point_2<R>
CGAL_intersection_point(
    const CGAL_Segment_2<R> &,
    const CGAL_Segment_2<R> &,
    const CGAL_intermediate_result &imr);


template <class R>
struct CGAL__segment2_segment2_imr : public CGAL__imresult_base {
    ~CGAL__segment2_segment2_imr() {}
    CGAL_Point_2<R> intersectionpoint;
};

template <class R>
CGAL_Intersection_result
CGAL_intersectiontype(
    const CGAL_Segment_2<R> &s1,
    const CGAL_Segment_2<R> &s2,
    CGAL_intermediate_result &imr)
{
    if (!do_overlap(s1.bbox(), s2.bbox()))
        return CGAL_NO_INTERSECTION;
    CGAL_intermediate_result llresult;
    const CGAL_Line_2<R> &l1 = s1.supporting_line();
    const CGAL_Line_2<R> &l2 = s2.supporting_line();
    switch ( CGAL_intersectiontype(l1, l2, imr)) {
    case CGAL_NO_INTERSECTION:
        return CGAL_NO_INTERSECTION;
    case CGAL_POINT_INTERSECTION: {
        const CGAL_Point_2<R> &intersectionpoint
                        = CGAL_intersection_point(l1, l2, imr);
        if (s1.collinear_is_on(intersectionpoint)
                && s2.collinear_is_on(intersectionpoint) ) {
            CGAL__segment2_segment2_imr<R> *imdata;
            imdata = new CGAL__segment2_segment2_imr<R>;
            imdata->intersectionpoint = intersectionpoint;
            imr.new_pointer(imdata);
            return CGAL_POINT_INTERSECTION;
        } else {
            return CGAL_NO_INTERSECTION;
        }
    }
    case CGAL_SEGMENT_INTERSECTION:
        return CGAL_SEGMENT_INTERSECTION;
        //not_implemented();

    }
    return CGAL_NO_INTERSECTION;
}

template <class R>
inline CGAL_Point_2<R>
CGAL_intersection_point(
    const CGAL_Segment_2<R> &,
    const CGAL_Segment_2<R> &,
        const CGAL_intermediate_result &imr)
{
    CGAL__segment2_segment2_imr<R> *imdata;
    imdata = DYNAMIC_CAST(CGAL__segment2_segment2_imr<R> *, imr.ptr());
    return imdata->intersectionpoint;
}



#endif
