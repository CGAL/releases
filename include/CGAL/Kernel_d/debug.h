// Copyright (c) 1997-2000  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Kernel_d/include/CGAL/Kernel_d/debug.h $
// $Id: debug.h 38827 2007-05-23 13:36:07Z spion $
// 
//
// Author(s)     : Michael Seel <seel@mpi-sb.mpg.de>
//
#ifndef CGAL_KERNEL_D_DEBUG_H
#define CGAL_KERNEL_D_DEBUG_H

#include <iostream>
#include <string>
#include <sstream>

#undef CGAL_KD_TRACE
#undef CGAL_KD_TRACEN
#undef CGAL_KD_TRACEV
#undef CGAL_KD_CTRACE
#undef CGAL_KD_CTRACEN
#undef CGAL_KD_ASSERT

static int debugthread=3141592;
namespace {
    struct Avoid_warning_for_unused_debugthread { static int x; };
    int Avoid_warning_for_unused_debugthread::x = debugthread;
}

#if CGAL_KD_DEBUG>0
#define CGAL_KD_SETDTHREAD(l) debugthread=l
#else
#define CGAL_KD_SETDTHREAD(l)
#endif

#if CGAL_KD_DEBUG>0
#define CGAL_KD_TRACE(t)   if((debugthread%CGAL_KD_DEBUG)==0)\
 std::cerr<<" "<<t;std::cerr.flush()
#else
#define CGAL_KD_TRACE(t) 
#endif

#if CGAL_KD_DEBUG>0
#define CGAL_KD_TRACEV(t)  if((debugthread%CGAL_KD_DEBUG)==0)\
 std::cerr<<" "<<#t<<" = "<<(t)<<std::endl;std::cerr.flush()
#else
#define CGAL_KD_TRACEV(t) 
#endif

#if CGAL_KD_DEBUG>0
#define CGAL_KD_TRACEN(t)  if((debugthread%CGAL_KD_DEBUG)==0)\
 std::cerr<<" "<<t<<std::endl;std::cerr.flush()
#else
#define CGAL_KD_TRACEN(t) 
#endif

#if CGAL_KD_DEBUG>0
#define CGAL_KD_CTRACE(b,t)  if(b) std::cerr << " " << t; else std::cerr << " 0"
#else
#define CGAL_KD_CTRACE(b,t) 
#endif

#if CGAL_KD_DEBUG>0
#define CGAL_KD_CTRACEN(b,t)  if(b) std::cerr<< " " <<t<<"\n"; else std::cerr<<" 0\n"
#else
#define CGAL_KD_CTRACEN(b,t) 
#endif

#ifndef CGAL_KD__ASSERT
#define  CGAL_KD_ASSERT(cond,fstr) 
#else
#define CGAL_KD_ASSERT(cond,fstr)   \
  if (!(cond)) {       \
    std::cerr << "   ASSERT:   " << #fstr << endl; \
    std::cerr << "   COND:     " << #cond << endl; \
    std::cerr << "   POSITION: " << __FILE__ << " at line "<< __LINE__ \
              <<std::endl; \
    abort();           \
  }
#endif

#define forall_iterators(x,S)\
for(x = S.begin(); x != S.end(); ++x) 

namespace MSDEBUG {

template <typename C>
void print_elements(const C& container)
{ typename C::const_iterator it;
  forall_iterators(it,container)
    std::cerr << *it << " ";
}

template <typename I>
void print(I s, I e, std::ostream& os = std::cerr)
{ while(s!=e) os<<*s++<<" "; }

template <class T>
std::string make_std_string(const T& t)
{ std::ostringstream os;
  os << t;
  std::string res(os.str()); 
  return res; 
}
} // MSDEBUG


#endif //CGAL_KERNEL_D_DEBUG_H
