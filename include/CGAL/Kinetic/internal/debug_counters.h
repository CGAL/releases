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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/include/CGAL/Kinetic/internal/debug_counters.h $
// $Id: debug_counters.h 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#include <CGAL/Kinetic/basic.h>

namespace CGAL { namespace Kinetic {
namespace internal {
  extern unsigned int zero_certificates__;
  extern unsigned int function_degeneracies__;
  extern unsigned int io_errors__;
  extern unsigned int audit_failures__;

  void write_debug_counters(std::ostream &out);
}
} } //namespace CGAL::Kinetic
