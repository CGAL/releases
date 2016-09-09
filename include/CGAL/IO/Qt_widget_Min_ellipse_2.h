// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// Copyright (c) 2002 ENS de Paris
//
// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// The Qt widget we provide for CGAL is distributed under the QPL,
// which is Trolltech's open source license. For more information see 
//     http://www.trolltech.com/developer/licensing/qpl.html
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// file          : include/CGAL/IO/Qt_widget_Min_ellipse_2.h
// package       : Qt_widget (1.2.30)
// author(s)     : Radu Ursu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_QT_WIDGET_MIN_ELLIPSE_2_H
#define CGAL_QT_WIDGET_MIN_ELLIPSE_2_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/Min_ellipse_2.h>

namespace CGAL{

template< class Traits_ >
Qt_widget&
operator<<(Qt_widget &ws,
              const CGAL::Min_ellipse_2<Traits_>& min_ellipse)
{
    typedef CGAL::Min_ellipse_2<Traits_>::Point_iterator  Point_iterator;

    Point_iterator  first( min_ellipse.points_begin());
    Point_iterator  last ( min_ellipse.points_end());
    for ( ; first != last; ++first)
        ws << *first;
    return ws;
}

}//end namespace CGAL

#endif
