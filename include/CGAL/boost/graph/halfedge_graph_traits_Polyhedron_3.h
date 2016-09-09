// Copyright (c) 2007  GeometryFactory (France).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/BGL/include/CGAL/boost/graph/halfedge_graph_traits_Polyhedron_3.h $
// $Id: halfedge_graph_traits_Polyhedron_3.h 37284 2007-03-19 19:36:49Z afabri $
// 
//
// Author(s)     : Andreas Fabri, Fernando Cacciola


#ifndef CGAL_BOOST_GRAPH_HALFEDGE_GRAPH_TRAITS_POLYHEDRON_3_H
#define CGAL_BOOST_GRAPH_HALFEDGE_GRAPH_TRAITS_POLYHEDRON_3_H

#include <CGAL/HalfedgeDS_items_decorator.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/boost/graph/halfedge_graph_traits.h>
#include <CGAL/boost/graph/halfedge_graph_traits_HalfedgeDS.h>

#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM
#  define CGAL_HDS_PARAM_ template < class Traits, class Items, class Alloc> class HDS
#else
#  define CGAL_HDS_PARAM_ class HDS
#endif

CGAL_BEGIN_NAMESPACE

//
// Const versions
// 
template<class Gt, class I, CGAL_HDS_PARAM_, class A>
struct halfedge_graph_traits< CGAL::Polyhedron_3<Gt,I,HDS,A> const > 
  : CGAL::HDS_halfedge_graph_traits< CGAL::Polyhedron_3<Gt,I,HDS,A> const>
{
};

template<class Gt, class I, CGAL_HDS_PARAM_, class A>
inline std::pair<typename halfedge_graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::undirected_edge_iterator
                ,typename halfedge_graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::undirected_edge_iterator 
                >  
undirected_edges( Polyhedron_3<Gt,I,HDS,A> const& p )
{
  typedef typename halfedge_graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::undirected_edge_iterator Iter;
  return std::make_pair( Iter(p.edges_begin()), Iter(p.edges_end()) );
}

template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor
next_edge( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor outedge
         , Polyhedron_3<Gt,I,HDS,A> const& 
         )
{
  return outedge->next();
}

template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor 
prev_edge( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor outedge
         , Polyhedron_3<Gt,I,HDS,A> const& 
         )
{
  HalfedgeDS_items_decorator< Polyhedron_3<Gt,I,HDS,A> > D ;
  return D.get_prev(outedge);
}

template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor
opposite_edge( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor e
             , Polyhedron_3<Gt,I,HDS,A> const& 
             )
{
  return e->opposite();
}

template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor
next_edge_ccw( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor outedge
             , Polyhedron_3<Gt,I,HDS,A> const& 
             )
{
  HalfedgeDS_items_decorator< Polyhedron_3<Gt,I,HDS,A> > D ;
  return D.get_prev(outedge)->opposite();
}

template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor
next_edge_cw( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> const>::edge_descriptor outedge
            , Polyhedron_3<Gt,I,HDS,A> const& 
            )
{
  return outedge->opposite()->next();
}


//
// Non-const versions
// 

template<class Gt, class I, CGAL_HDS_PARAM_, class A>
struct halfedge_graph_traits< CGAL::Polyhedron_3<Gt,I,HDS,A> > 
  : CGAL::HDS_halfedge_graph_traits< CGAL::Polyhedron_3<Gt,I,HDS,A> >
{
};

template<class Gt, class I, CGAL_HDS_PARAM_, class A>
inline std::pair<typename halfedge_graph_traits< Polyhedron_3<Gt,I,HDS,A> >::undirected_edge_iterator
                ,typename halfedge_graph_traits< Polyhedron_3<Gt,I,HDS,A> >::undirected_edge_iterator 
                >  
undirected_edges( Polyhedron_3<Gt,I,HDS,A>& p )
{
  typedef typename halfedge_graph_traits< Polyhedron_3<Gt,I,HDS,A> >::undirected_edge_iterator Iter;
  return std::make_pair( Iter(p.edges_begin()), Iter(p.edges_end()) );
}

template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor 
next_edge( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor outedge
         , Polyhedron_3<Gt,I,HDS,A>& 
         )
{
  return outedge->next();
}


template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor 
prev_edge( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor outedge
         , Polyhedron_3<Gt,I,HDS,A>&
         )
{
  CGAL::HalfedgeDS_items_decorator< Polyhedron_3<Gt,I,HDS,A> > D ;
  return D.get_prev(outedge);
}


template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor
opposite_edge( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor e
             , Polyhedron_3<Gt,I,HDS,A>& 
             )
{
  return e->opposite();
}


template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor 
next_edge_ccw( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor outedge
             , Polyhedron_3<Gt,I,HDS,A>& 
             )
{
  HalfedgeDS_items_decorator< Polyhedron_3<Gt,I,HDS,A> > D ;
  return D.get_prev(outedge)->opposite();
}


template<class Gt, class I, CGAL_HDS_PARAM_, class A>
typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor
next_edge_cw( typename boost::graph_traits< Polyhedron_3<Gt,I,HDS,A> >::edge_descriptor outedge
            , Polyhedron_3<Gt,I,HDS,A>& 
            )
{
  return outedge->opposite()->next();
}


CGAL_END_NAMESPACE

#undef CGAL_HDS_

#endif // CGAL_BOOST_GRAPH_HALFEDGE_GRAPH_TRAITS_POLYHEDRON_3_H
