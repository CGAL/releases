
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
// file          : include/CGAL/Straight_2_stream.h
// package       : Intersections_2 (2.11.3)
// source        : straight_2.fw
// author(s)     : Oren Nechushtan
//
// coordinator   : MPI, Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_STRAIGHT_2_STREAM_H
#define CGAL_STRAIGHT_2_STREAM_H



CGAL_BEGIN_NAMESPACE

#ifndef CGAL_NO_OSTREAM_INSERT_STRAIGHT_2
template <class R>
std::ostream& operator<<(std::ostream& os,const Straight_2_<R>& cv)
{
        typedef Pm_straight_exact_traits<R> Traits;
        typedef Straight_2_<R> Curve;
        switch(cv.current_state())
        {
        case Curve::SEGMENT:
                {
                        Segment_2<R> seg;
                        cv.current(seg);
                        return os << seg;
                }
        case Curve::RAY:
                {
                        Ray_2<R> ray;
                        cv.current(ray);
                        return os << ray;
                }
        case Curve::LINE:
                {
                        Line_2<R> line;
                        cv.current(line);
                        return os << line;
                }
        case Curve::POINT:
                {
                        Point_2<R> p;
                        cv.current(p);
                        return os << p;
                }
        case Curve::EMPTY:
          break;
        }
        CGAL_assertion_msg(
                cv.current_state()==Curve::SEGMENT||
                cv.current_state()==Curve::RAY||
                cv.current_state()==Curve::LINE||
                cv.current_state()==Curve::POINT||
                cv.current_state()==Curve::EMPTY,
                "\nUnknown type in  std:: ostream& operator<<( \
                std:: ostream& os,const Straight_2&)");
        return os;
}
#endif //CGAL_NO_OSTREAM_INSERT_STRAIGHT_2
#ifndef CGAL_NO_ISTREAM_EXTRACT_STRAIGHT_2
template <class R>
std:: istream& operator>>(std:: istream& is,Straight_2_<R>& cv)
{
        typedef Pm_straight_exact_traits<R> Traits;
        typedef Straight_2_<R> Curve;
        switch(cv.current_state())
        {
        case Curve::SEGMENT:
                {
                        Segment_2<R> seg;
                        cv.current(seg);
                        return os >> seg;
                }
        case Curve::RAY:
                {
                        Ray_2<R> ray;
                        cv.current(ray);
                        return os >> ray;
                }
        case Curve::LINE:
                {
                        Line_2<R> line;
                        cv.current(line);
                        return os >> line;
                }
        case Curve::POINT:
                {
                        Point_2<R> p;
                        cv.current(p);
                        return os >> p;
                }
        case Curve::EMPTY:
          break;
        }
        CGAL_assertion_msg(
                cv.current_state()==Curve::SEGMENT||
                cv.current_state()==Curve::RAY||
                cv.current_state()==Curve::LINE||
                cv.current_state()==Curve::POINT||
                cv.current_state()==Curve::EMPTY,
                "\nUnknown type in  std:: ostream& operator>>( \
                std:: ostream& os,Straight_2&)");
        return os;
}
#endif //CGAL_NO_ISTREAM_EXTRACT_STRAIGHT_2

CGAL_END_NAMESPACE



#endif // CGAL_STRAIGHT_2_STREAM_H
