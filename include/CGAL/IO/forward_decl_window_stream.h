// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// source        : leda_window.fw
// file          : include/CGAL/IO/forward_decl_window_stream.h
// package       : window (2.8.27)
// revision      : 2.8.1
// revision_date : 23 May 2001 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_IO_FORWARD_DECL_WINDOW_STREAM_H
#define CGAL_IO_FORWARD_DECL_WINDOW_STREAM_H

#if defined(CGAL_USE_CGAL_WINDOW)
CGAL_BEGIN_NAMESPACE
class window;
CGAL_END_NAMESPACE
#else
class leda_window;
#endif

CGAL_BEGIN_NAMESPACE

#if defined(CGAL_USE_CGAL_WINDOW)
typedef   CGAL::window    Window_stream;
#else
typedef   leda_window    Window_stream;
#endif

CGAL_END_NAMESPACE

#endif // CGAL_IO_FORWARD_DECL_WINDOW_STREAM_H
