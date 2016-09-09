// ======================================================================
//
// Copyright (c) 1999,2000 The CGAL Consortium

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
// file          : include/CGAL/CLN/common.h
// package       : CLN (2.0)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2000/08/03 15:13:45 $
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CLN_COMMON_H
#define CGAL_CLN_COMMON_H

// This file is included by all CLN/cl_*.h files and gathers the common code
// and includes.

#include <CGAL/number_utils.h>
#include <CGAL/number_type_tags.h>
#include <CGAL/IO/io_tags.h>

// So that CLN defines the operators += -= *= /=
#define WANT_OBFUSCATING_OPERATORS

#include <cl_number.h>
#include <cl_io.h>
#include <cl_output.h> // for cl_default_print_flags

CGAL_BEGIN_NAMESPACE

inline bool        is_valid        (const cl_number&) { return true; } 
inline bool        is_finite       (const cl_number&) { return true; } 
inline io_Operator io_tag          (const cl_number&) { return io_Operator(); }
inline Number_tag  number_type_tag (const cl_number&) { return Number_tag(); }


// The following is a workaround for a bug that happens on Solaris 2.6 with
// gcc 2.95, and libcln.so (not .a).  It doesn't happen on Linux with gcc 2.95.
//  
// Namely, the default base for printing should be 10, but it's not
// initialized as it should for some reason...
//   
// So we make a static object that we initialize here instead.
// We put this code here instead of src/CLN.C so that libCGAL doesn't depend
// on CLN.

struct workaround_4_CLN
{
  workaround_4_CLN() { cl_default_print_flags.rational_base = 10; }
};
 
static workaround_4_CLN workaroung_4_CLN_object;                                

CGAL_END_NAMESPACE

#endif // CGAL_CLN_COMMON_H
