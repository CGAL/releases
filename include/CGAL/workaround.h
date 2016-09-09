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

// Source: workaround.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifdef __sgi
#define CGAL_WORKAROUND_001
#define CGAL_WORKAROUND_012

#endif //  __sgi

#ifdef __GNUG__
#define CGAL_WORKAROUND_003
#define CGAL_WORKAROUND_004
#define CGAL_WORKAROUND_005
#define CGAL_WORKAROUND_007
#define CGAL_WORKAROUND_008
#define CGAL_WORKAROUND_010
#define CGAL_WORKAROUND_013
#define CGAL_WORKAROUND_015

#endif // __GNUG__


#ifdef __SUNPRO_CC
#define CGAL_WORKAROUND_002
#define CGAL_WORKAROUND_006
#define CGAL_WORKAROUND_010
#define CGAL_WORKAROUND_012

#endif // __SUNPRO_CC
