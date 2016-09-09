#ifndef POLYHEDRON_TYPE_FWD_H
#define POLYHEDRON_TYPE_FWD_H

#include <memory>

#ifdef USE_FORWARD_DECL

namespace CGAL {

  template <class CK>
  struct Filtered_kernel;

  template < typename FT_ >
  struct Simple_cartesian;

  class Polyhedron_items_3;

#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM
  template < class T, class I, class A>
#endif
  class HalfedgeDS_default;

  template < class PolyhedronTraits_3,
             class PolyhedronItems_3,
#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM
             template < class T, class I, class A>
#endif
             class T_HDS, 
             class Alloc
             >
  class Polyhedron_3;
  
} // end namespace CGAL

// kernel
typedef CGAL::Filtered_kernel< CGAL::Simple_cartesian<double> > Kernel;

// surface mesh
typedef CGAL::Polyhedron_3<Kernel,
                           CGAL::Polyhedron_items_3,
                           CGAL::HalfedgeDS_default,
                           std::allocator<int> > Polyhedron;

#else // USE_FORWARD_DECL

#include "Polyhedron_type.h"

#endif // USE_FORWARD_DECL

#endif // POLYHEDRON_TYPE_FWD_H
