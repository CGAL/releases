/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

// Implementation: miscellaneous things for optimisation algorithms
// file  : include/CGAL/optimisation_misc.h
// source: web/optimisation/optimisation_misc.aw
// author: Sven Schönherr
// ----------------------------------------------------------------------------
// $Revision: 3.1 $
// $Date: 1997/06/27 12:58:00 $
// ============================================================================

#ifndef CGAL_OPTIMISATION_MISC_H
#define CGAL_OPTIMISATION_MISC_H

// Function declarations
// =====================

// is_valid failure function
// -------------------------
#include <CGAL/IO/Verbose_ostream.h>

bool
CGAL__optimisation_is_valid_fail( CGAL_Verbose_ostream& verr,
                                  const char*           message);

#endif // CGAL_OPTIMISATION_MISC_H

// ===== EOF ==================================================================
