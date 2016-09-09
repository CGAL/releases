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


#ifndef CGAL_BASIC_H
#define CGAL_BASIC_H
#include <CGAL/workaround.h>
#include <CGAL/workaround_10.h>

// compilers that have rtti need the following file
#ifndef CGAL_WORKAROUND_012
#include <std/typeinfo.h>
#endif  // CGAL_WORKAROUND_012

#ifdef CGAL_LEDA_BASIC
#include <LEDA/basic.h>
#endif  // CGAL_LEDA_BASIC


#include <CGAL/bool.h>
#include <CGAL/enum.h>
#include <CGAL/utils.h>
#include <CGAL/misc.h>
#include <CGAL/Handle.h>
#include <CGAL/number_utils.h>
#include <CGAL/Double.h>
#include <CGAL/Float.h>
#include <CGAL/Quotient.h>
#include <CGAL/Object.h>

#endif // CGAL_BASIC_H
