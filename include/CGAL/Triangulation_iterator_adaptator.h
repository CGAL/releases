// Copyright (c) 1997  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Triangulation_2/include/CGAL/Triangulation_iterator_adaptator.h $
// $Id: Triangulation_iterator_adaptator.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Mariette Yvinec
//                 Menelaos Karavelas <mkaravel@cse.nd.edu>

#ifndef CGAL_TRIANGULATION_ITERATOR_ADAPTATOR_H
#define CGAL_TRIANGULATION_ITERATOR_ADAPTATOR_H

#include <CGAL/triangulation_assertions.h>

namespace CGAL {

template <class Base, class Handle>
struct Triangulation_iterator_handle_adaptor
  : public Base
{
  typedef Triangulation_iterator_handle_adaptor<Base, Handle>  Self;
  Triangulation_iterator_handle_adaptor() : Base() {}
   
  Triangulation_iterator_handle_adaptor(const Base & b) 
    : Base(b) {}

  // MK: added this to satisfy the mips_CC-7.40 compiler
  Self& operator=(const Self& other) {
    static_cast<Base &>(*this) = static_cast<const Base&>(other); 
    return *this;
  }

  operator Handle() const {return Base::base();}
  Self&  operator++() { Base::operator++(); return *this;}
  Self&  operator--() { Base::operator--(); return *this;}
  Self   operator++(int) { Self tmp(*this); ++(*this); return tmp; }
  Self   operator--(int) { Self tmp(*this); --(*this); return tmp; }
};



} //namespace CGAL

#endif //CGAL_TRIANGULATION_ITERATOR_ADAPTATOR_H
