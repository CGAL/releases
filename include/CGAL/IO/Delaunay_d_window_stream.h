// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// file          : include/CGAL/IO/Delaunay_d_window_stream.h
// package       : Kernel_d (0.9.47)
// chapter       : Basic
//
// source        : ddgeo/Delaunay_d.lw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/07/05 08:22:37 $
//
// author(s)     : Michael Seel
// coordinator   : Susan Hert
//
// implementation: Higher dimensional geometry
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_DELAUNAY_D_WINDOW_STREAM_H
#define CGAL_DELAUNAY_D_WINDOW_STREAM_H

#include <CGAL/Delaunay_d.h>
#include <CGAL/IO/Convex_hull_d_window_stream.h>
#include <CGAL/IO/Window_stream.h>

CGAL_BEGIN_NAMESPACE

/*{\Mtext \headerline{Low Dimensional Output Routines}
include |<CGAL/IO/Delaunay_d_window_stream.h>|
\setopdims{2cm}{1cm}}*/

template <typename R, typename Lifted_R>
void d2_show(const Delaunay_d<R,Lifted_R>& D,
             CGAL::Window_stream& W, 
             typename Delaunay_d<R,Lifted_R>::Delaunay_voronoi_kind k = 
             Delaunay_d<R,Lifted_R>::NEAREST)
/*{\Mfunc draws the underlying simplicial complex |D| into window |W|.\\
\precond |dim == 2|. }*/
{ 
  CGAL_assertion_msg(D.dimension() == 2, "d2_map: dim != 2.");
  Regular_complex_d<R> RC(2);
  D.project(RC, (k == Delaunay_d<R,Lifted_R>::NEAREST ? -1 : +1));
  CGAL::d2_show(RC,W);
}

template <typename R, typename Lifted_R>
void d2_map(const Delaunay_d<R,Lifted_R>& D, 
            GRAPH< typename Delaunay_d<R,Lifted_R>::Point_d, int >& DTG, 
            typename Delaunay_d<R,Lifted_R>::Delaunay_voronoi_kind k = 
            Delaunay_d<R,Lifted_R>::NEAREST)
/*{\Mfunc constructs a LEDA graph representation of the nearest 
(|kind = NEAREST| or the furthest (|kind = FURTHEST|) site
Delaunay triangulation.\\ \precond |dim() == 2|. }*/
{ 
  CGAL_assertion_msg(D.dimension() == 2, "d2_map: dim != 2.");
  Regular_complex_d<R> RC(2);
  D.project(RC, (k == NEAREST ? -1 : +1));
  d2_map(RC,DTG);
}


CGAL_END_NAMESPACE
#endif //CGAL_DELAUNAY_D_WINDOW_STREAM_H


