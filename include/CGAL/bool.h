//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: bool.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_BOOL_H
#define CGAL_BOOL_H


#if !defined(__BUILTIN_BOOL__)


#ifndef CGAL_LEDA_BASIC

typedef char bool;

enum {false=0, true=1};

#else

#include <LEDA/basic.h>

#endif // CGAL_LEDA_BASIC

#endif  // __BUILTIN_BOOL__

#endif // CGAL_BOOL_H

