// Copyright (c) 2005 Rijksuniversiteit Groningen (Netherlands)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Skin_surface_3/include/CGAL/Voronoi_triangulator_3.h $
// $Id: Voronoi_triangulator_3.h 33412 2006-08-18 13:35:28Z nicokruithof $
// 
//
// Author(s)     : Nico Kruithof <Nico@cs.rug.nl>

#ifndef CGAL_VORONOI_TRIANGULATOR_3_H
#define CGAL_VORONOI_TRIANGULATOR_3_H

#include <CGAL/Unique_hash_map.h>
#include <CGAL/Compute_anchor_3.h>
#include <CGAL/Triangulation_simplex_3.h>

#include <CGAL/Marching_tetrahedra_3.h>

#include <map>

CGAL_BEGIN_NAMESPACE


template < class SkinSurfaceTraits_3 >
class Voronoi_triangulator_visitor_default {
public:
  typedef SkinSurfaceTraits_3                               Skin_traits_3;
  typedef typename SkinSurfaceTraits_3::Regular             Regular;
  typedef typename SkinSurfaceTraits_3::Simplicial          Simplicial;
  typedef typename SkinSurfaceTraits_3::Mesh_K              Mesh_K;

  typedef typename Regular::Vertex_handle            Rt_Vertex_handle;
  typedef typename Regular::Edge                     Rt_Edge;
  typedef typename Regular::Facet                    Rt_Facet;
  typedef typename Regular::Cell_handle              Rt_Cell_handle;
  typedef Simplex_3<Regular>                         Rt_Simplex;

  typedef typename Regular::Bare_point               Rt_Point;
  typedef typename Regular::Geom_traits              Rt_Geom_traits;
  typedef typename Rt_Geom_traits::RT                Rt_RT;
  typedef typename Regular::Weighted_point           Rt_Weighted_point;

  typedef typename Simplicial::Vertex_handle    TVD_Vertex_handle;
  typedef typename Simplicial::Edge             TVD_Edge;
  typedef typename Simplicial::Facet            TVD_Facet;
  typedef typename Simplicial::Cell_handle      TVD_Cell_handle;
  typedef typename Skin_traits_3::Triangulated_mixed_complex_kernel  Triangulated_mixed_complex_kernel;
  typedef typename Triangulated_mixed_complex_kernel::Point_3        TVD_Point;
  typedef typename Triangulated_mixed_complex_kernel::RT             TVD_RT;
  typedef Weighted_point<TVD_Point,TVD_RT>        TVD_Weighted_point;
  typedef Skin_surface_quadratic_surface_3<Mesh_K> QuadrSurface;
  typedef Skin_surface_sphere_3<Mesh_K>         Sphere_surface;
  typedef Skin_surface_hyperboloid_3<Mesh_K>    Hyperboloid_surface;

  typedef typename Skin_traits_3::Mesh_K        Mesh_K;
  typedef typename Mesh_K::RT                   Mesh_RT;
  typedef typename Mesh_K::Point_3              Mesh_Point;
  typedef Weighted_point<Mesh_Point,Mesh_RT>    Mesh_Weighted_point;
  
  typedef typename Skin_traits_3::R2P_converter R2P_converter;
  typedef typename Skin_traits_3::T2P_converter T2P_converter;

  Voronoi_triangulator_visitor_default() 
  : r2p_converter(SkinSurfaceTraits_3().r2p_converter_object())
  {
  }

  void after_vertex_insertion(
    Rt_Simplex &sDel, Rt_Simplex &sVor, TVD_Vertex_handle &vh)
  {
    vh->sDel = sDel;
    vh->sVor = sVor;
  }

  void after_cell_insertion(Rt_Simplex &s, TVD_Cell_handle &ch) 
  {
    CGAL_assertion(s.dimension() == 0);
    Rt_Vertex_handle vh = s;
    // Use the same surface as many times as possible:
    if (vh != vh_old) {
      vh_old = vh;
      surf = new Sphere_surface(r2p_converter(vh->point()), 1, 1);
    }
    ch->surf = surf;
  }

  Rt_Vertex_handle vh_old;
  QuadrSurface *surf;
  
  R2P_converter r2p_converter;
};

template < 
  class SkinSurfaceTraits_3,
  class VoronoiTriangulatorVisitor_ = 
    Voronoi_triangulator_visitor_default<SkinSurfaceTraits_3> >
class Voronoi_triangulator_3 {
public:
  typedef SkinSurfaceTraits_3                          Skin_traits_3;
  typedef VoronoiTriangulatorVisitor_           Visitor;
  typedef typename Skin_traits_3::Regular       Regular;
  typedef typename Skin_traits_3::Simplicial    Simplicial;

  typedef typename Skin_traits_3::R2T_converter R2T_converter;
private:
  typedef typename Regular::Vertex_handle            Rt_Vertex_handle;
  typedef typename Regular::Edge                     Rt_Edge;
  typedef typename Regular::Facet                    Rt_Facet;
  typedef typename Regular::Cell_handle              Rt_Cell_handle;
	
  typedef typename Regular::Finite_vertices_iterator Rt_Finite_vertices_iterator;
  typedef typename Regular::Finite_edges_iterator    Rt_Finite_edges_iterator;
  typedef typename Regular::Finite_facets_iterator   Rt_Finite_facets_iterator;
  typedef typename Regular::All_cells_iterator       Rt_All_cells_iterator;
  typedef typename Regular::Finite_cells_iterator    Rt_Finite_cells_iterator;
	
  typedef typename Regular::Cell_circulator          Rt_Cell_circulator;

  typedef Simplex_3<Regular>                    Rt_Simplex;
  typedef typename Skin_traits_3::Regular_kernel       Rt_Geom_traits;
  typedef typename Regular::Bare_point          Rt_Point;
  typedef typename Regular::Geom_traits::RT     Rt_RT;
  typedef typename Regular::Weighted_point      Rt_Weighted_point;

  typedef typename Simplicial::Vertex_handle    TVD_Vertex_handle;
  typedef typename Simplicial::Edge             TVD_Edge;
  typedef typename Simplicial::Facet            TVD_Facet;
  typedef typename Simplicial::Cell_handle      TVD_Cell_handle;

  typedef typename Simplicial::Finite_vertices_iterator TVD_Finite_vertices_iterator;
  typedef typename Simplicial::Finite_edges_iterator    TVD_Finite_edges_iterator;
  typedef typename Simplicial::Finite_facets_iterator   TVD_Finite_facets_iterator;
  typedef typename Simplicial::All_cells_iterator       TVD_All_cells_iterator;
  typedef typename Simplicial::Finite_cells_iterator    TVD_Finite_cells_iterator;
  typedef typename Simplicial::Cell_circulator          TVD_Cell_circulator;
	
  typedef typename Skin_traits_3::Triangulated_mixed_complex_kernel          TVD_Geom_traits;
  typedef typename TVD_Geom_traits::Point_3              TVD_Point;
  typedef typename TVD_Geom_traits::RT                   TVD_RT;
  //   typedef Weighted_point<TVD_Point>                TVD_Weighted_point;

  typedef Triangulation_incremental_builder_3<Simplicial>
  Triangulation_incremental_builder;

  //   typedef typename Skin_Traits::Mesh_K               M_traits;
  //   typedef Skin_surface_quadratic_surface_3< M_traits > Quadratic_surface;
  //   typedef Skin_surface_sphere_3< M_traits >            Sphere_surface;
  //   typedef Skin_surface_hyperboloid_3< M_traits >       Hyperboloid_surface;
  //   typedef typename M_traits::RT                        M_RT;
public:

  Voronoi_triangulator_3(Regular &T, Simplicial &sc)
    : T(T), sc(sc), triangulation_incr_builder(sc), 
      visitor(), compute_anchor_obj(T) {
    edge_index[0][0] = -1; edge_index[0][1] =  0;
    edge_index[0][2] =  1; edge_index[0][3] =  2;
    edge_index[1][0] =  0; edge_index[1][1] = -1;
    edge_index[1][2] =  3; edge_index[1][3] =  4;
    edge_index[2][0] =  1; edge_index[2][1] =  3;
    edge_index[2][2] = -1; edge_index[2][3] =  5;
    edge_index[3][0] =  2; edge_index[3][1] =  4;
    edge_index[3][2] =  5; edge_index[3][3] = -1;

    build();
  }

  Voronoi_triangulator_3(Regular &T, Simplicial &sc, Visitor &visitor)
    : T(T), sc(sc), triangulation_incr_builder(sc), 
      visitor(visitor), compute_anchor_obj(T) {
    edge_index[0][0] = -1; edge_index[0][1] =  0;
    edge_index[0][2] =  1; edge_index[0][3] =  2;
    edge_index[1][0] =  0; edge_index[1][1] = -1;
    edge_index[1][2] =  3; edge_index[1][3] =  4;
    edge_index[2][0] =  1; edge_index[2][1] =  3;
    edge_index[2][2] = -1; edge_index[2][3] =  5;
    edge_index[3][0] =  2; edge_index[3][1] =  4;
    edge_index[3][2] =  5; edge_index[3][3] = -1;
	  
    build();
  }


private:
  void build() {

    triangulation_incr_builder.begin_triangulation(3);

    construct_vertices();
    construct_cells();

    triangulation_incr_builder.end_triangulation();
  }

  TVD_Vertex_handle add_vertex(Rt_Simplex &sVor); 
  TVD_Cell_handle add_cell(TVD_Vertex_handle vh[], int orient, Rt_Simplex s);
	
  TVD_Vertex_handle get_vertex(Rt_Simplex &sVor);


  void construct_vertices();
  TVD_Point get_anchor(Rt_Simplex &sVor);

  // triangulate Voronoi cells:
  void construct_cells();
  void compute_value_on_vertices();

//  typedef std::map<Rt_Simplex, typename TVD_Geom_traits::Point_3> Focus_map;
//  Focus_map foc_map;

  // Reference back to the regular triangulation
//  std::map<TVD_Cell_handle, Rt_Simplex> backRef;
	
private:
  Regular &T;
  Simplicial &sc;
  Triangulation_incremental_builder triangulation_incr_builder;
  R2T_converter r2s_converter;
  Visitor visitor;

  Construct_weighted_circumcenter_3<
    Regular_triangulation_euclidean_traits_3<
    TVD_Geom_traits> >                                orthocenter_obj;
  Compute_squared_radius_smallest_orthogonal_sphere_3<
    Regular_triangulation_euclidean_traits_3<
    typename Simplicial::Geom_traits> >              orthoweight_obj;
  Compute_anchor_3<Regular> compute_anchor_obj;

  int edge_index[4][4];
  struct Index_c4 { TVD_Vertex_handle V[4]; };
  struct Index_c6 { TVD_Vertex_handle V[6]; };
  struct Index_c44 { TVD_Vertex_handle V[4][4]; };
  struct Index_v {
    Unique_hash_map < Rt_Vertex_handle, TVD_Vertex_handle > V;
  };
  // Facets on the border of the simplicial complex:

  // name is given by dimension of the Delaunay siplex
  // index to vertex
  Unique_hash_map < Rt_Cell_handle, TVD_Vertex_handle > index_3;
  // index points to facet
  Unique_hash_map < Rt_Cell_handle, Index_c4 > index_2;
  // From the vertex to the adjacent vertex
  Unique_hash_map < Rt_Vertex_handle, Index_v > index_1;
  // One for every vertex
  Unique_hash_map < Rt_Vertex_handle, TVD_Vertex_handle > index_0;

  //std::list<TVD_Vertex_handle> degenerate_vertices;
  TVD_Vertex_handle debug_vh;
};

// Constructs the vertices of the simplicial complex
template <class SkinSurfaceTraits_3, class Mixed_complex_visitor_>
void
Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::
construct_vertices() {
  Rt_All_cells_iterator acit;
  Rt_Finite_cells_iterator cit;
  Rt_Finite_facets_iterator fit;
  Rt_Finite_edges_iterator eit;
  Rt_Finite_vertices_iterator vit;
  Rt_Cell_circulator ccir, cstart;
  Rt_Vertex_handle v1, v2, v3;
  Rt_Edge e;
  Rt_Cell_handle c1, c2;
  Rt_Simplex sVor;
  TVD_Vertex_handle vh;

  // dimVor=3
  for (cit=T.finite_cells_begin(); cit!=T.finite_cells_end(); cit++) {
    sVor = compute_anchor_obj.anchor_vor(cit);
    vh = add_vertex(sVor);
    index_3[cit] = vh;
    CGAL_assertion(vh == get_vertex(sVor));
  }
  // dimVor=2
  for (fit=T.finite_facets_begin(); fit!=T.finite_facets_end(); fit++) {
    sVor = compute_anchor_obj.anchor_vor(*fit);
    if (sVor.dimension() == 2) {
      vh = add_vertex(sVor);
    } else {
      vh = get_vertex(sVor);
    }
    Rt_Cell_handle nb = fit->first->neighbor(fit->second);
    if (fit->first < nb) {
      index_2[fit->first].V[fit->second] = vh;
    } else {
      index_2[nb].V[nb->index(fit->first)] = vh;
    }
  }
	
  // dimVor=1
  for (eit=T.finite_edges_begin(); eit!=T.finite_edges_end(); eit++) {
    sVor = compute_anchor_obj.anchor_vor(*eit);

    if (sVor.dimension() == 1) {
      vh = add_vertex(sVor);
    } else {
      vh = get_vertex(sVor);
    }

    v1 = eit->first->vertex(eit->second);
    v2 = eit->first->vertex(eit->third);
    if (v2 < v1) std::swap(v1,v2);
    index_1[v1].V[v2] = vh;
    assert(vh == get_vertex(sVor));
  }
	
  // dimVor=0
  for (vit=T.finite_vertices_begin(); vit!=T.finite_vertices_end(); vit++) {
    sVor = compute_anchor_obj.anchor_vor(vit);
    if (sVor.dimension() == 0) {
      vh = add_vertex(sVor);
    } else {
      vh = get_vertex(sVor);
      debug_vh = vh;
    }
    index_0[vit] = vh;
    assert(vh == get_vertex(sVor));
  }

}

// Constructs 3-cells of the mixed complex corresponding to cells
// of the regular triangulation
template <class SkinSurfaceTraits_3, class Mixed_complex_visitor_>
void
Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::
construct_cells() {
  Rt_Simplex sVor;
  TVD_Vertex_handle vh[4];
  std::list<TVD_Cell_handle> inserted_cells;

  for (Rt_Finite_vertices_iterator vit=T.finite_vertices_begin();
       vit!=T.finite_vertices_end(); vit++) {
    Rt_Simplex simplex(vit);
//     sDel = compute_anchor_obj.anchor_del(vit);
    sVor = compute_anchor_obj.anchor_vor(vit);
    vh[0] = get_vertex(sVor);

    std::list<Rt_Cell_handle> adj_cells;
    typename std::list<Rt_Cell_handle>::iterator adj_cell;
    T.incident_cells(vit, std::back_inserter(adj_cells));

    // Construct cells:
    for (adj_cell = adj_cells.begin();
	 adj_cell != adj_cells.end();
	 adj_cell ++) {
      if (!T.is_infinite(*adj_cell)) {
	sVor = compute_anchor_obj.anchor_vor(*adj_cell);
	vh[3] = get_vertex(sVor);
	int index = (*adj_cell)->index(vit);
	for (int i=1; i<4; i++) {
	  sVor=compute_anchor_obj.anchor_vor(Rt_Facet(*adj_cell,(index+i)&3));
	  vh[2] = get_vertex(sVor);

	  for (int j=1; j<4; j++) {
	    if (j!=i) {
	      sVor = compute_anchor_obj.anchor_vor(Rt_Edge(*adj_cell,index,(index+j)&3));
	      vh[1] = get_vertex(sVor);
		  
	      if ((vh[0] != vh[1]) && (vh[1] != vh[2]) && (vh[2] != vh[3])) {
		
		TVD_Cell_handle ch;
								
		ch = add_cell(vh,(index + (j==(i%3+1)? 1:0))&1,simplex);
		inserted_cells.push_back(ch);
	      }
	    }
	  }
	}
      }
    }
  }
}

// Adds a vertex to the simplicial complex
template <class SkinSurfaceTraits_3, class Mixed_complex_visitor_>
typename Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::TVD_Vertex_handle
Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::
add_vertex (Rt_Simplex &sVor)
{
  TVD_Vertex_handle vh = triangulation_incr_builder.add_vertex();
  vh->point() = get_anchor(sVor);
  visitor.after_vertex_insertion(sVor,sVor,vh); 

  return vh;
}

// Gets a vertex from the simplicial complex based on the anchors
template <class SkinSurfaceTraits_3, class Mixed_complex_visitor_>
typename Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::TVD_Vertex_handle
Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::get_vertex (
  Rt_Simplex &sVor)
{
  Rt_Vertex_handle vh;
  Rt_Edge e;
  Rt_Facet f;
  Rt_Cell_handle ch;
  switch (sVor.dimension()) {
    case 0:
      vh=sVor;
      return index_0[vh];
    case 1:
      e=sVor;
      if (e.first->vertex(e.second) < e.first->vertex(e.third)) {
        return index_1[e.first->vertex(e.second)].V[e.first->vertex(e.third)];
      } else {
        return index_1[e.first->vertex(e.third)].V[e.first->vertex(e.second)];
      }
    case 2:
      f=sVor;
      ch = f.first->neighbor(f.second);
      if (f.first < ch) {
        return index_2[f.first].V[f.second];
      } else {
        return index_2[ch].V[ch->index(f.first)];
      }
    case 3:
      ch=sVor;
      return index_3[ch];
    default:
      assert(false);
  }
  assert(false);
  return TVD_Vertex_handle();
}

// Adds a cell to the simplicial complex
template <class SkinSurfaceTraits_3, class Mixed_complex_visitor_>
typename Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::TVD_Cell_handle
Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::
add_cell(TVD_Vertex_handle vh[], int orient, Rt_Simplex s) {
  assert((orient==0) || (orient==1));
  assert(vh[0] != TVD_Vertex_handle()); assert(vh[1] != TVD_Vertex_handle());
  assert(vh[2] != TVD_Vertex_handle()); assert(vh[3] != TVD_Vertex_handle());
  assert(vh[1] != vh[2]); assert(vh[1] != vh[3]); assert(vh[1] != vh[4]);
  assert(vh[2] != vh[3]); assert(vh[2] != vh[4]); assert(vh[3] != vh[4]);
  TVD_Cell_handle ch;

// NGHK: DEBUG:
  Orientation o = orientation(
    vh[0]->point(), vh[1]->point(),
    vh[2]->point(), vh[3]->point());
  if (((orient) &&(o!=POSITIVE))||((!orient)&&(o!=NEGATIVE)))  {
    Rt_Vertex_handle  r_vh;
    Rt_Edge           r_e;
    Rt_Facet          r_f;
    Rt_Cell_handle    r_ch;
    TVD_Point vert[4];
    for (int i=0; i<4; i++) {
      switch (vh[i]->sVor.dimension()) {
        case 0:
          r_vh=vh[i]->sVor;
          vert[i] = r2s_converter(r_vh->point());
        break;
        case 1:
          r_e=vh[i]->sVor;
          vert[i] = orthocenter_obj(
            r2s_converter(r_e.first->vertex(r_e.second)->point()),
            r2s_converter(r_e.first->vertex(r_e.third)->point()));
          break;
        case 2:
          r_f=vh[i]->sVor;
          vert[i] = orthocenter_obj(
            r2s_converter(r_f.first->vertex((r_f.second+1)&3)->point()),
            r2s_converter(r_f.first->vertex((r_f.second+2)&3)->point()),
            r2s_converter(r_f.first->vertex((r_f.second+3)&3)->point()));
          break;
        case 3:
          r_ch=vh[i]->sVor;
          vert[i] = orthocenter_obj(
            r2s_converter(r_ch->vertex(0)->point()),
            r2s_converter(r_ch->vertex(1)->point()),
            r2s_converter(r_ch->vertex(2)->point()),
            r2s_converter(r_ch->vertex(3)->point()));
          break;
      }
    }
    o = orientation(vert[0],vert[1],vert[2],vert[3]);
  }

  if (orient) {
    ch = triangulation_incr_builder.add_cell(vh[0], vh[1], vh[2], vh[3]);
  } else {
    ch = triangulation_incr_builder.add_cell(vh[0], vh[1], vh[3], vh[2]);
  }
  //backRef[ch] = s;
  visitor.after_cell_insertion(s, ch);
  return ch;
}

template <class SkinSurfaceTraits_3, class Mixed_complex_visitor_>
typename Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::TVD_Point
Voronoi_triangulator_3<SkinSurfaceTraits_3,Mixed_complex_visitor_>::get_anchor(Rt_Simplex &sVor)
{
  Rt_Vertex_handle vh;
  Rt_Edge           e;
  Rt_Facet          f;
  Rt_Cell_handle   ch;
	
  TVD_Point vfoc, dfoc;
  switch (sVor.dimension()) {
    case 0:
      vh=sVor;
      vfoc = r2s_converter(vh->point());
      break;
    case 1:
      e=sVor;
      vfoc = orthocenter_obj(
	r2s_converter(e.first->vertex(e.second)->point()),
	r2s_converter(e.first->vertex(e.third)->point()));
      break;
    case 2:
      f=sVor;
      vfoc = orthocenter_obj(
	r2s_converter(f.first->vertex((f.second+1)&3)->point()),
	r2s_converter(f.first->vertex((f.second+2)&3)->point()),
	r2s_converter(f.first->vertex((f.second+3)&3)->point()));
      break;
    case 3:
      ch=sVor;
      vfoc = orthocenter_obj(
	r2s_converter(ch->vertex(0)->point()),
	r2s_converter(ch->vertex(1)->point()),
	r2s_converter(ch->vertex(2)->point()),
	r2s_converter(ch->vertex(3)->point()));
      break;
  }
	
  return vfoc;
}

CGAL_END_NAMESPACE

#endif // CGAL_VORONOI_TRIANGULATOR_3_H
