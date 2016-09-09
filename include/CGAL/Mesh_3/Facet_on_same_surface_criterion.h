// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/include/CGAL/Mesh_3/Facet_on_same_surface_criterion.h $
// $Id: Facet_on_same_surface_criterion.h 60688 2011-01-10 15:43:22Z lrineau $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : 
//******************************************************************************

#ifndef CGAL_MESH_3_FACET_ON_SAME_SURFACE_CRITERION_H
#define CGAL_MESH_3_FACET_ON_SAME_SURFACE_CRITERION_H

#include <CGAL/basic.h>
#include <CGAL/Mesh_3/mesh_standard_criteria.h>

namespace CGAL {

namespace Mesh_3 {
    
    
//template <typename Tr, typename Visitor_>
//class Facet_on_same_surface_criterion :
//public Mesh_3::Abstract_criterion<Tr, Visitor_>
//{
//private:
//  typedef typename Tr::Facet Facet;
//  
//  typedef Mesh_3::Abstract_criterion<Tr,Visitor_> Base;
//  typedef typename Base::Quality Quality;
//  typedef typename Base::Badness Badness;
//  
//  typedef Facet_on_same_surface_criterion<Tr,Visitor_> Self;
//  
//public:
//  /// Constructor
//  Facet_on_same_surface_criterion() {};
//  /// Destructor
//  virtual ~Facet_on_same_surface_criterion() {};
//  
//protected:
//  virtual void do_accept(Visitor_& v) const
//  {
//    v.visit(*this);
//  }
//  
//  virtual Self* do_clone() const
//  {
//    // Call copy ctor on this
//    return new Self(*this);
//  }
//  
//  virtual Badness do_is_bad (const Facet& f) const
//  {
//    typedef typename Tr::Vertex_handle  Vertex_handle;
//    typedef typename Tr::Cell_handle    Cell_handle;
//    typedef typename Tr::Vertex::Index  Index;
//
//    const Cell_handle& ch = f.first;
//    const int& i = f.second;
//    
//    const Vertex_handle& v1 = ch->vertex((i+1)&3);
//    const Vertex_handle& v2 = ch->vertex((i+2)&3);
//    const Vertex_handle& v3 = ch->vertex((i+3)&3);
//    
//    Index index = Index();
//    bool is_index_initialized = false;
//    
//    if ( v1->in_dimension() == 2 )
//    { 
//      index = v1->index();
//      is_index_initialized = true;
//    }
//    
//    if ( v2->in_dimension() == 2 )
//    {
//      if ( is_index_initialized )
//      {
//        if ( !(v2->index() == index) )
//        {
//          return Badness(Quality(1));
//        }
//      }
//      else
//      {
//        index = v2->index();
//        is_index_initialized = true;        
//      }
//    }
//    
//    if ( v3->in_dimension() == 2 )
//    {
//      if ( is_index_initialized && !(v3->index() == index) )
//      {
//        return Badness(Quality(1));
//      } 
//    }
//    
//    return  Badness();			
//  }
//  
//}; // end class Facet_on_same_surface_criterion
    
} // end namespace Mesh_3


} //namespace CGAL

#endif // CGAL_MESH_3_FACET_ON_SAME_SURFACE_CRITERION_H
