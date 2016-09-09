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
// file          : include/CGAL/LEDA/pixmaps/texture.h
// package       : cgal_window (1.0.8)
// revision      : 0.9.8
// revision_date : 12 June 2001
// author(s)     : Matthias Baesken, Algorithmic Solutions
//
// coordinator   : Matthias Baesken, Trier  (<baesken>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#include <CGAL/LEDA/pixmaps/texture/blue.xpm>
#include <CGAL/LEDA/pixmaps/texture/clouds.xpm>
#include <CGAL/LEDA/pixmaps/texture/dirt.xpm>
#include <CGAL/LEDA/pixmaps/texture/pool.xpm>
#include <CGAL/LEDA/pixmaps/texture/sharks.xpm>
#include <CGAL/LEDA/pixmaps/texture/slate.xpm>
#include <CGAL/LEDA/pixmaps/texture/space.xpm>
#include <CGAL/LEDA/pixmaps/texture/wall.xpm>
#include <CGAL/LEDA/pixmaps/texture/waves.xpm>
#include <CGAL/LEDA/pixmaps/texture/wood.xpm>

#include <CGAL/LEDA/pixmaps/leda.xpm>
#include <CGAL/LEDA/pixmaps/algosol.xpm>

#define num_texture 12

static const char** xpm_texture[] = {
algosol_xpm,
leda_xpm,
blue_xpm,
clouds_xpm,
dirt_xpm,
pool_xpm,
sharks_xpm,
slate_xpm,
space_xpm,
wall_xpm,
waves_xpm,
wood_xpm
};

static const char* name_texture[] = {
"algosol",
"leda",
"blue",
"clouds",
"dirt",
"pool",
"sharks",
"slate",
"space",
"wall",
"waves",
"wood"
};

#if defined(__GNUC__)
inline char texture_unused_warning()
{ return xpm_texture[0][0][0] + name_texture[0][0]; }
#endif


