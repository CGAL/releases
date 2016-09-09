// Copyright (c) 2006-2007  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Surface_mesher/include/CGAL/Surface_mesher/Types_generators.h $
// $Id: Types_generators.h 42968 2008-04-21 16:07:38Z lrineau $
// 
//
// Author(s)     : Laurent RINEAU

#ifndef CGAL_SURFACE_MESHER_TYPES_GENERATORS_H
#define CGAL_SURFACE_MESHER_TYPES_GENERATORS_H

#include <CGAL/Meshes/Triangulation_mesher_level_traits_3.h>

namespace CGAL {
  namespace Surface_mesher {
    namespace details {

      template <typename Base>
      class Triangulation_generator {
        typedef typename Base::Complex_2_in_triangulation_3 C2T3;
        typedef typename C2T3::Triangulation Triangulation;
      public:
	typedef Triangulation Type;
	typedef Type type;
      }; // end Triangulation_generator<Base>

      template <typename Base>
      class Facet_generator {
        typedef typename Triangulation_generator<Base>::type Tr;
      public:
	typedef typename Tr::Facet Type;
	typedef Type type;
      }; // end Facet_generator<Base>

      template <typename Base>
      class Edge_generator {
        typedef typename Triangulation_generator<Base>::type Tr;
      public:
	typedef typename Tr::Edge Type;
	typedef Type type;
      }; // end Edge_generator<Base>

      template <typename Base, typename Self, typename Element,
		typename PreviousLevel = Null_mesher_level>
      class Mesher_level_generator {
        typedef typename Base::Complex_2_in_triangulation_3 C2T3;
        typedef typename C2T3::Triangulation Triangulation;
        typedef Triangulation_mesher_level_traits_3<Triangulation> Tr_m_l_traits_3;
      public:
        typedef Mesher_level <Triangulation,
                              Self,
                              Element,
                              PreviousLevel,
                              Tr_m_l_traits_3> Type;
        typedef Type type;
      }; // end class Mesher_level_generator<Base, Self, Element>

    } // end namespace details
  } // end namespace Surface_mesher
} // end namespace CGAL

#endif // CGAL_SURFACE_MESHER_TYPES_GENERATORS_H
