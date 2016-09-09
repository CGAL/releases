// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/intersection_3_1.C
// package       : Intersections_3 (1.3)
// source        : web/intersection_3.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================




template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Plane_3<R> &plane1, const CGAL_Plane_3<R>&plane2)
{
    typedef typename R::RT RT;
    const RT &a = plane1.a();
    const RT &b = plane1.b();
    const RT &c = plane1.c();
    const RT &d = plane1.d();
    const RT &p = plane2.a();
    const RT &q = plane2.b();
    const RT &r = plane2.c();
    const RT &s = plane2.d();
    const RT zero = RT(0);
    RT det;
    CGAL_Point_3<R> is_pt;
    CGAL_Direction_3<R> is_dir;

    det = a*q-p*b;
    if (det != zero) {
        is_pt = CGAL_Point_3<R>(b*s-d*q, p*d-a*s, zero, det);
        is_dir = CGAL_Direction_3<R>(b*r-c*q, p*c-a*r, det);
        return CGAL_make_object(CGAL_Line_3<R>(is_pt, is_dir));
    }
    det = a*r-p*c;
    if (det != zero) {
        is_pt = CGAL_Point_3<R>(c*s-d*r, zero, p*d-a*s, det);
        is_dir = CGAL_Direction_3<R>(c*q-b*r, det, p*b-a*q);
        return CGAL_make_object(CGAL_Line_3<R>(is_pt, is_dir));
    }
    det = b*r-c*q;
    if (det != zero) {
        is_pt = CGAL_Point_3<R>(zero, c*s-d*r, d*q-b*s, det);
        is_dir = CGAL_Direction_3<R>(det, c*p-a*r, a*q-b*p);
        return CGAL_make_object(CGAL_Line_3<R>(is_pt, is_dir));
    }
// degenerate case
    if (a!=zero || p!=zero) {
        if (a*s == p*d)
            return CGAL_make_object(plane1);
        else
            return CGAL_Object();
    }
    if (b!=zero || q!=zero) {
        if (b*s == q*d)
            return CGAL_make_object(plane1);
        else
            return CGAL_Object();
    }
    if (c!=zero || r!=zero) {
        if (c*s == r*d)
            return CGAL_make_object(plane1);
        else
            return CGAL_Object();
    }
    return CGAL_make_object(plane1);
}


template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Plane_3<R> &plane, const CGAL_Line_3<R>&line)
{
    typedef typename R::RT RT;
    const CGAL_Point_3<R> &line_pt = line.point();
    const CGAL_Direction_3<R> &line_dir = line.direction();
    RT num,  den;
    num = plane.a()*line_pt.hx() + plane.b()*line_pt.hy()
        + plane.c()*line_pt.hz() + plane.d()*line_pt.hw();
    den = plane.a()*line_dir.dx() + plane.b()*line_dir.dy()
        + plane.c()*line_dir.dz();
    if (den == RT(0)) {
        if (num == RT(0)) {
            // all line
            return CGAL_make_object(line);
        } else {
            // no intersection
            return CGAL_Object();
        }
    }
    return CGAL_make_object(CGAL_Point_3<R>(
        den*line_pt.hx()-num*line_dir.dx(),
        den*line_pt.hy()-num*line_dir.dy(),
        den*line_pt.hz()-num*line_dir.dz(),
        line_pt.hw()*den));
}

template <class R>
bool
CGAL_do_intersect(const CGAL_Plane_3<R> &plane, const CGAL_Line_3<R>&line)
{
    typedef typename R::RT RT;
    const CGAL_Point_3<R> &line_pt = line.point();
    const CGAL_Direction_3<R> &line_dir = line.direction();
    RT num,  den;
    den = plane.a()*line_dir.dx() + plane.b()*line_dir.dy()
        + plane.c()*line_dir.dz();
    if (den !=  RT(0))
        return true;
    num = plane.a()*line_pt.hx() + plane.b()*line_pt.hy()
        + plane.c()*line_pt.hz() + plane.d()*line_pt.hw();
    if (num == RT(0)) {
        // all line
        return true;
    } else {
        // no intersection
        return false;
    }
}


template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Plane_3<R> &plane, const CGAL_Ray_3<R>&ray)
{
    const CGAL_Object line_intersection =
            CGAL_intersection(plane, ray.supporting_line());
    CGAL_Point_3<R> isp;
    if (CGAL_assign(isp, line_intersection)) {
        if (ray.collinear_has_on(isp))
            return line_intersection;
        else
            return CGAL_Object();
    }
    if (line_intersection.is_empty())
        return line_intersection;
    return CGAL_make_object(ray);
}

template <class R>
bool
CGAL_do_intersect(const CGAL_Plane_3<R> &plane, const CGAL_Ray_3<R>&ray)
{
    const CGAL_Object line_intersection =
            CGAL_intersection(plane, ray.supporting_line());
    if (line_intersection.is_empty())
        return false;
    CGAL_Point_3<R> isp;
    if (CGAL_assign(isp, line_intersection)) {
        if (ray.collinear_has_on(isp))
            return true;
        else
            return false;
    }
    return true;
}


template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Plane_3<R> &plane, const CGAL_Segment_3<R>&seg)
{
    const CGAL_Point_3<R> &source = seg.source();
    const CGAL_Point_3<R> &target = seg.target();
    CGAL_Oriented_side source_side,target_side;
    source_side = plane.oriented_side(source);
    target_side = plane.oriented_side(target);
    switch (source_side) {
    case CGAL_ON_ORIENTED_BOUNDARY:
        if (target_side == CGAL_ON_ORIENTED_BOUNDARY)
            return CGAL_make_object(seg);
        else
            return CGAL_make_object(source);
    case CGAL_ON_POSITIVE_SIDE:
        switch (target_side) {
        case CGAL_ON_ORIENTED_BOUNDARY:
            return CGAL_make_object(target);
        case CGAL_ON_POSITIVE_SIDE:
            return CGAL_Object();
        case CGAL_ON_NEGATIVE_SIDE:
            return CGAL_intersection(plane, seg.supporting_line());
        }
    case CGAL_ON_NEGATIVE_SIDE:
        switch (target_side) {
        case CGAL_ON_ORIENTED_BOUNDARY:
            return CGAL_make_object(target);
        case CGAL_ON_POSITIVE_SIDE:
            return CGAL_intersection(plane, seg.supporting_line());
        case CGAL_ON_NEGATIVE_SIDE:
            return CGAL_Object();
        }
    }
    CGAL_kernel_assertion_msg(false, "Supposedly unreachable code.");
    return CGAL_Object();
}

template <class R>
bool
CGAL_do_intersect(const CGAL_Plane_3<R> &plane, const CGAL_Segment_3<R>&seg)
{
    const CGAL_Point_3<R> &source = seg.source();
    const CGAL_Point_3<R> &target = seg.target();
    CGAL_Oriented_side source_side,target_side;
    source_side = plane.oriented_side(source);
    target_side = plane.oriented_side(target);
    if ( source_side == target_side
       && target_side != CGAL_ON_ORIENTED_BOUNDARY) {
        return false;
    }
    return true;
}


template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Line_3<R> &line,
        const CGAL_Bbox_3 &box)
{
    const CGAL_Point_3<R> &linepoint = line.point();
    const CGAL_Direction_3<R> &linedir = line.direction();
    return CGAL_intersection_bl(box,
        CGAL_to_double(linepoint.x()),
        CGAL_to_double(linepoint.y()),
        CGAL_to_double(linepoint.z()),
        CGAL_to_double(linedir.dx()),
        CGAL_to_double(linedir.dy()),
        CGAL_to_double(linedir.dz()),
        true, true
        );
}


template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Ray_3<R> &ray,
        const CGAL_Bbox_3 &box)
{
    const CGAL_Point_3<R> &linepoint = ray.source();
    const CGAL_Direction_3<R> &linedir = ray.direction();
    return CGAL_intersection_bl(box,
        CGAL_to_double(linepoint.x()),
        CGAL_to_double(linepoint.y()),
        CGAL_to_double(linepoint.z()),
        CGAL_to_double(linedir.dx()),
        CGAL_to_double(linedir.dy()),
        CGAL_to_double(linedir.dz()),
        false, true
        );
}


template <class R>
CGAL_Object
CGAL_intersection(const CGAL_Segment_3<R> &seg,
        const CGAL_Bbox_3 &box)
{
    const CGAL_Point_3<R> &linepoint = seg.source();
    const CGAL_Vector_3<R> &diffvec = seg.target()-linepoint;
    return CGAL_intersection_bl(box,
        CGAL_to_double(linepoint.x()),
        CGAL_to_double(linepoint.y()),
        CGAL_to_double(linepoint.z()),
        CGAL_to_double(diffvec.x()),
        CGAL_to_double(diffvec.y()),
        CGAL_to_double(diffvec.z()),
        false, false
        );
}


