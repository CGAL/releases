
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Ray_2_Bbox_2_intersection.h
// package       : Intersections_2 (2.11.3)
// source        : intersection_2_1.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_RAY_2_BBOX_2_INTERSECTION_H
#define CGAL_RAY_2_BBOX_2_INTERSECTION_H

#include <CGAL/Bbox_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/utils.h>
#include <CGAL/number_utils.h>

CGAL_BEGIN_NAMESPACE

class Bbox_2_Ray_2_pair_impl;

class Bbox_2_Ray_2_pair {
public:
    enum Intersection_results {NO, POINT, SEGMENT};
    ~Bbox_2_Ray_2_pair() ;
    Bbox_2_Ray_2_pair() ;
    Bbox_2_Ray_2_pair(Bbox_2_Ray_2_pair const &o) ;
    Bbox_2_Ray_2_pair(Bbox_2 const &box,
                      double x, double y, double dx, double dy) ;
    Bbox_2_Ray_2_pair& operator=(Bbox_2_Ray_2_pair const &o) ;
    Intersection_results intersection_type() const;
    bool intersection(double &x, double &y) const;
    bool intersection(double &x1, double &y1, double &x2, double &y2) const;
protected:
    Bbox_2_Ray_2_pair_impl *pimpl;
};

bool do_intersect_ray_2(
    const Bbox_2 &box, double x, double y, double dx, double dy);

template <class Ray>
bool do_intersect_ray_2(
    const Bbox_2 &box,
    const Ray &ray)
{
    double startx = to_double(ray->start().x());
    double starty = to_double(ray->start().y());
    double dx = to_double(ray->direction().to_vector().x());
    double dy = to_double(ray->direction().to_vector().y());
    return do_intersect_ray_2(box, startx, starty, dx, dy);
}

template <class Ray>
inline bool do_intersect_ray_2(
    const Ray &ray,
    const Bbox_2 &box)
{
    return do_intersect_ray_2(box, ray);
}
CGAL_END_NAMESPACE



#endif
