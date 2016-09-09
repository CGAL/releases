// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/intersection_3_1.C
// package       : Intersections_3 (2.3)
// source        : web/intersection_3.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================





CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Plane_3<R> &plane1, const Plane_3<R>&plane2)
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
    Point_3<R> is_pt;
    Direction_3<R> is_dir;

    det = a*q-p*b;
    if (det != zero) {
        is_pt = Point_3<R>(b*s-d*q, p*d-a*s, zero, det);
        is_dir = Direction_3<R>(b*r-c*q, p*c-a*r, det);
        return make_object(Line_3<R>(is_pt, is_dir));
    }
    det = a*r-p*c;
    if (det != zero) {
        is_pt = Point_3<R>(c*s-d*r, zero, p*d-a*s, det);
        is_dir = Direction_3<R>(c*q-b*r, det, p*b-a*q);
        return make_object(Line_3<R>(is_pt, is_dir));
    }
    det = b*r-c*q;
    if (det != zero) {
        is_pt = Point_3<R>(zero, c*s-d*r, d*q-b*s, det);
        is_dir = Direction_3<R>(det, c*p-a*r, a*q-b*p);
        return make_object(Line_3<R>(is_pt, is_dir));
    }
// degenerate case
    if (a!=zero || p!=zero) {
        if (a*s == p*d)
            return make_object(plane1);
        else
            return Object();
    }
    if (b!=zero || q!=zero) {
        if (b*s == q*d)
            return make_object(plane1);
        else
            return Object();
    }
    if (c!=zero || r!=zero) {
        if (c*s == r*d)
            return make_object(plane1);
        else
            return Object();
    }
    return make_object(plane1);
}

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Plane_3<R> &plane, const Line_3<R>&line)
{
    typedef typename R::RT RT;
    const Point_3<R> &line_pt = line.point();
    const Direction_3<R> &line_dir = line.direction();
    RT num,  den;
    num = plane.a()*line_pt.hx() + plane.b()*line_pt.hy()
        + plane.c()*line_pt.hz() + plane.d()*line_pt.hw();
    den = plane.a()*line_dir.dx() + plane.b()*line_dir.dy()
        + plane.c()*line_dir.dz();
    if (den == RT(0)) {
        if (num == RT(0)) {
            // all line
            return make_object(line);
        } else {
            // no intersection
            return Object();
        }
    }
    return make_object(Point_3<R>(
        den*line_pt.hx()-num*line_dir.dx(),
        den*line_pt.hy()-num*line_dir.dy(),
        den*line_pt.hz()-num*line_dir.dz(),
        line_pt.hw()*den));
}

template <class R>
bool
do_intersect(const Plane_3<R> &plane, const Line_3<R>&line)
{
    typedef typename R::RT RT;
    const Point_3<R> &line_pt = line.point();
    const Direction_3<R> &line_dir = line.direction();
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
CGAL_END_NAMESPACE




CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Plane_3<R> &plane, const Ray_3<R>&ray)
{
    const Object line_intersection =
            intersection(plane, ray.supporting_line());
    Point_3<R> isp;
    if (assign(isp, line_intersection)) {
        if (ray.collinear_has_on(isp))
            return line_intersection;
        else
            return Object();
    }
    if (line_intersection.is_empty())
        return line_intersection;
    return make_object(ray);
}

template <class R>
bool
do_intersect(const Plane_3<R> &plane, const Ray_3<R>&ray)
{
    const Object line_intersection =
            intersection(plane, ray.supporting_line());
    if (line_intersection.is_empty())
        return false;
    Point_3<R> isp;
    if (assign(isp, line_intersection)) {
        if (ray.collinear_has_on(isp))
            return true;
        else
            return false;
    }
    return true;
}
CGAL_END_NAMESPACE




CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Plane_3<R> &plane, const Segment_3<R>&seg)
{
    const Point_3<R> &source = seg.source();
    const Point_3<R> &target = seg.target();
    Oriented_side source_side,target_side;
    source_side = plane.oriented_side(source);
    target_side = plane.oriented_side(target);
    switch (source_side) {
    case ON_ORIENTED_BOUNDARY:
        if (target_side == ON_ORIENTED_BOUNDARY)
            return make_object(seg);
        else
            return make_object(source);
    case ON_POSITIVE_SIDE:
        switch (target_side) {
        case ON_ORIENTED_BOUNDARY:
            return make_object(target);
        case ON_POSITIVE_SIDE:
            return Object();
        case ON_NEGATIVE_SIDE:
            return intersection(plane, seg.supporting_line());
        }
    case ON_NEGATIVE_SIDE:
        switch (target_side) {
        case ON_ORIENTED_BOUNDARY:
            return make_object(target);
        case ON_POSITIVE_SIDE:
            return intersection(plane, seg.supporting_line());
        case ON_NEGATIVE_SIDE:
            return Object();
        }
    }
    CGAL_kernel_assertion_msg(false, "Supposedly unreachable code.");
    return Object();
}

template <class R>
bool
do_intersect(const Plane_3<R> &plane, const Segment_3<R>&seg)
{
    const Point_3<R> &source = seg.source();
    const Point_3<R> &target = seg.target();
    Oriented_side source_side,target_side;
    source_side = plane.oriented_side(source);
    target_side = plane.oriented_side(target);
    if ( source_side == target_side
       && target_side != ON_ORIENTED_BOUNDARY) {
        return false;
    }
    return true;
}
CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Line_3<R> &line,
        const Bbox_3 &box)
{
    const Point_3<R> &linepoint = line.point();
    const Direction_3<R> &linedir = line.direction();
    return intersection_bl(box,
        CGAL::to_double(linepoint.x()),
        CGAL::to_double(linepoint.y()),
        CGAL::to_double(linepoint.z()),
        CGAL::to_double(linedir.dx()),
        CGAL::to_double(linedir.dy()),
        CGAL::to_double(linedir.dz()),
        true, true
        );
}

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Ray_3<R> &ray,
        const Bbox_3 &box)
{
    const Point_3<R> &linepoint = ray.source();
    const Direction_3<R> &linedir = ray.direction();
    return intersection_bl(box,
        CGAL::to_double(linepoint.x()),
        CGAL::to_double(linepoint.y()),
        CGAL::to_double(linepoint.z()),
        CGAL::to_double(linedir.dx()),
        CGAL::to_double(linedir.dy()),
        CGAL::to_double(linedir.dz()),
        false, true
        );
}

CGAL_END_NAMESPACE



CGAL_BEGIN_NAMESPACE

template <class R>
Object
intersection(const Segment_3<R> &seg,
        const Bbox_3 &box)
{
    const Point_3<R> &linepoint = seg.source();
    const Vector_3<R> &diffvec = seg.target()-linepoint;
    return intersection_bl(box,
        CGAL::to_double(linepoint.x()),
        CGAL::to_double(linepoint.y()),
        CGAL::to_double(linepoint.z()),
        CGAL::to_double(diffvec.x()),
        CGAL::to_double(diffvec.y()),
        CGAL::to_double(diffvec.z()),
        false, false
        );
}

CGAL_END_NAMESPACE


