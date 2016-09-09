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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kinetic_data_structures/include/CGAL/Kinetic/internal/Kernel/Certificate.h $
// $Id: Certificate.h 40832 2007-11-08 00:27:20Z ameyer $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KINETIC_IO_KERNEL_CERTIFICATE_H
#define CGAL_KINETIC_IO_KERNEL_CERTIFICATE_H
#include <CGAL/Kinetic/basic.h>
#include <limits>

CGAL_KINETIC_BEGIN_INTERNAL_NAMESPACE

template <class Function_kernel_t>
class Certificate {
public:
  typedef typename Function_kernel_t::Function Function;
  typedef typename Function_kernel_t::Root Time;
  Certificate(const Function &f, const Function_kernel_t& fk, const Time &b, const Time &e): rs_(fk.root_stack_object(f, b, e)) {
    /*typename Function_kernel_t::Lower_bound_root lbr= fk.lower_bound_root_object();
      estimate_= lbr(f, b);*/
    /*if (f.degree() > 0) {
      std::cout << "Certificate function is " << f << std::endl;
      }*/
  }
  Certificate(){}

  bool will_fail() const {
    return !rs_.empty();
  }

  const Time &failure_time() const {
    if (rs_.empty()) {
      std::cerr << "You now must check if the certificate will fail before calling top.\n";
      CGAL_error();
      static Time t(1000000);
      return t;
    }
    return rs_.top();
  }
  void pop_failure_time() {
    if (!rs_.empty()) rs_.pop();
  }

  const typename Function_kernel_t::Root_stack& root_stack() const {
    return rs_;
  }
  /*double lower_bound() const {
    return estimate_;
    }*/

  std::ostream &write(std::ostream &out) const {
    out << rs_;
    return out;
  }
  /*bool operator==(const This &o) const {
    return rs_== o.rs_;
    }*/
private:
  typename Function_kernel_t::Root_stack rs_;
  //double estimate_;
};

template <class FK>
inline std::ostream& operator<<(std::ostream& out, const Certificate<FK> &c) {
  return c.write(out);
}

CGAL_KINETIC_END_INTERNAL_NAMESPACE


#endif
