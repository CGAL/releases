// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// file          : include/CGAL/LEDA/bitmaps/button32.h
// package       : cgal_window (1.0.8)
// revision      : 0.9.8
// revision_date : 12 June 2001
// author(s)     : Matthias Baesken, Algorithmic Solutions
// coordinator   : Matthias Baesken, Trier  (<baesken>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#include <CGAL/LEDA/bitmaps/button32/a_annulus.xbm>
#include <CGAL/LEDA/bitmaps/button32/w_annulus.xbm>
#include <CGAL/LEDA/bitmaps/button32/circle.xbm>
#include <CGAL/LEDA/bitmaps/button32/dice.xbm>
#include <CGAL/LEDA/bitmaps/button32/empty_circle.xbm>
#include <CGAL/LEDA/bitmaps/button32/encl_circle.xbm>
#include <CGAL/LEDA/bitmaps/button32/exit.xbm>
#include <CGAL/LEDA/bitmaps/button32/f_triang.xbm>
#include <CGAL/LEDA/bitmaps/button32/f_voro.xbm>
#include <CGAL/LEDA/bitmaps/button32/grid.xbm>
#include <CGAL/LEDA/bitmaps/button32/help.xbm>
#include <CGAL/LEDA/bitmaps/button32/hull.xbm>
#include <CGAL/LEDA/bitmaps/button32/inside.xbm>
#include <CGAL/LEDA/bitmaps/button32/intersect.xbm>
#include <CGAL/LEDA/bitmaps/button32/line.xbm>
#include <CGAL/LEDA/bitmaps/button32/point.xbm>
#include <CGAL/LEDA/bitmaps/button32/poly.xbm>
#include <CGAL/LEDA/bitmaps/button32/rect.xbm>
#include <CGAL/LEDA/bitmaps/button32/tree.xbm>
#include <CGAL/LEDA/bitmaps/button32/triang.xbm>
#include <CGAL/LEDA/bitmaps/button32/triangle.xbm>
#include <CGAL/LEDA/bitmaps/button32/union.xbm>
#include <CGAL/LEDA/bitmaps/button32/voro.xbm>

#define num_xbm_button32 23

static unsigned char* xbm_button32[] = {
a_annulus_bits,
w_annulus_bits,
circle_bits,
dice_bits,
empty_circle_bits,
encl_circle_bits,
exit_bits,
f_triang_bits,
f_voro_bits,
grid_bits,
help_bits,
hull_bits,
inside_bits,
intersect_bits,
line_bits,
point_bits,
poly_bits,
rect_bits,
tree_bits,
triang_bits,
triangle_bits,
union_bits,
voro_bits
};


static const char* name_xbm_button32[] = {
"a_annulus",
"w_annulus",
"circle",
"dice",
"empty_circle",
"encl_circle",
"exit",
"f_triang",
"f_voro",
"grid",
"help",
"hull",
"inside",
"intersect",
"line",
"point",
"poly",
"rect",
"tree",
"triang",
"triangle",
"union",
"voro"
};


#if defined(__GNUC__)
inline char xbm_button32_unused_warning()
{ return xbm_button32[0][0] + name_xbm_button32[0][0]; }
#endif
