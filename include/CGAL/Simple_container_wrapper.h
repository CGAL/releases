// Copyright (c) 2003,2004  INRIA Sophia-Antipolis (France) and
// Notre Dame University (U.S.A.).  All rights reserved.
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
// $Source: /CVSROOT/CGAL/Packages/Segment_Voronoi_diagram_2/include/CGAL/Simple_container_wrapper.h,v $
// $Revision: 1.5 $ $Date: 2004/08/18 06:11:28 $
// $Name:  $
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>


#ifndef CGAL_SIMPLE_CONTAINER_WRAPPER_H
#define CGAL_SIMPLE_CONTAINER_WRAPPER_H

#include <CGAL/basic.h>
#include <list>


CGAL_BEGIN_NAMESPACE

template<class C>
class Simple_container_wrapper
{
public:
  typedef C                                    Container;
  typedef typename Container::value_type       value_type;
  typedef typename Container::iterator         iterator;
  typedef typename Container::const_iterator   const_iterator;
  typedef typename Container::size_type        size_type;

private:
  typedef Simple_container_wrapper<Container> Self;

public:
  Simple_container_wrapper(const Container& c = Container())
    : c(c) {}

  iterator begin() { return c.begin(); }
  iterator end()   { return c.end(); }

  std::pair<iterator,bool> insert(const value_type& t)
  {
    //    std::pair<iterator,bool> it_b = c.insert(t);
    //    return it_b.first;
#if 1
    return c.insert(t);
#else
    c.push_back(t);
    return std::pair<iterator,bool>(--c.end(), true);
#endif
  }

  void remove(iterator it)
  {
    c.erase(it);
  }

  void swap(Self& other)
  {
    c.swap(other.c);
  }

  void clear() {
    c.clear();
  }

  size_type size() const { return c.size(); }

private:
  Container c;
};


CGAL_END_NAMESPACE

#endif // CGAL_SIMPLE_CONTAINER_WRAPPER_H
