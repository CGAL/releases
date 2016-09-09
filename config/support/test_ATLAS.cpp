// Copyright (c) 2007  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/support/test_ATLAS.cpp $
// $Id: test_ATLAS.cpp 38442 2007-04-25 14:13:51Z lsaboret $
//
// Author(s)     : Laurent Saboret

// Test if the LAPACK subset in ATLAS is available


#include <iostream>

extern "C" {
    // Fortran interface taken from ATLAS/interfaces/lapack/F77/src/dpotrf.f
    extern void dpotrf_(char *uplo, int *n, double *a, int *lda, int *info);
}


int main()
{
    // Call dpotrf_() Lapack routine (Cholesky factorization)
    int sn_size = 0;
    int lda = 1;
    int info;
    dpotrf_((char*)"LOWER",
            &sn_size,
            NULL,
            &lda,
            &info);

    std::cout << "ok for ATLAS" << std::endl;

    return 0;
}
