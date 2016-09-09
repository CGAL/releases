// Copyright (c) 2004  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Mesh_2/include/CGAL/Meshes/Simple_set_container.h $
// $Id: Simple_set_container.h 42968 2008-04-21 16:07:38Z lrineau $
// 
//
// Author(s)     : Laurent RINEAU

#ifndef CGAL_MESHES_SIMPLE_SET_CONTAINER_H
#define CGAL_MESHES_SIMPLE_SET_CONTAINER_H

#include <set>

namespace CGAL {

  namespace Meshes {

    template <typename Element>
    class Simple_set_container 
    {
    public:
      typedef std::set<Element> Set;
      typedef typename Set::size_type size_type;

    protected:
      // --- protected datas ---
      Set s;

    public:
      bool no_longer_element_to_refine_impl() const
      {
        return s.empty();
      }

      Element get_next_element_impl()
      {
        CGAL_assertion(!s.empty());
        
        return *(s.begin());

      }

      void add_bad_element(const Element& e)
      {
        s.insert(e);
      }

      void pop_next_element_impl()
      {
        s.erase(s.begin());
      }

      void remove_element(const Element& e)
      {
        s.erase(e);
      }

      size_type size() const
      {
	return s.size();
      }
    }; // end Simple_set_container
    
  }; // end namespace Meshes
}; // end namespace CGAL

#endif // CGAL_MESHES_SIMPLE_SET_CONTAINER_H
