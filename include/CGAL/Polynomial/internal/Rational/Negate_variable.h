// Copyright (c) 2005  Stanford University (USA).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/include/CGAL/Polynomial/internal/Rational/Negate_variable.h $
// $Id: Negate_variable.h 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_POLYNOMIAL_KERNEL_NEGATE_VARIABLE_H
#define CGAL_POLYNOMIAL_KERNEL_NEGATE_VARIABLE_H

#include <CGAL/Polynomial/basic.h>
#include <vector>

namespace CGAL { namespace POLYNOMIAL { namespace internal {
//------------------------------------------------------------------

template <class Polynomial>
class Negate_variable
{
    public:
        typedef typename Polynomial::NT NT;
        typedef NT          argument_type;
        typedef Polynomial  result_type;

        Negate_variable() {}

        void write(std::ostream &out) const
        {
            out << "negate_var";
        }

        result_type operator()(const Polynomial &f) const
        {
            int size = f.degree() + 1;
            std::vector<NT> coefs(size);

            for (int i = 0; i < size; i++) {
                if (i%2 == 1) {
		  coefs[i]= -f[i];
                }
                else {
                    coefs[i]= f[i];
                }
            }

            Polynomial ret(coefs.begin(), coefs.end());

            CGAL_Polynomial_assertion(ret.degree() == f.degree());

            return ret;
        }
};

} } } //namespace CGAL::POLYNOMIAL::internal
#endif                                            // CGAL_POLYNOMIAL_KERNEL_NEGATE_VARIABLE_H
