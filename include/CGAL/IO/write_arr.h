// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/IO/write_arr.h
// package       : Arrangement (2.52)
// author(s)     : Eti Ezra
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.4-I-90 $
// release_date  : $CGAL_Date: 2002/05/15 $
//
// file          : include/CGAL/IO/write_arr.h
// package       : pm (1.81)
// maintainer    : Eyal Flato <flato@math.tau.ac.il>
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Eti Ezra <estere@post.tau.ac.il>
//
//
// coordinator   : Tel-Aviv University (Dan Halperin <halperin@math.tau.ac.il>)
//
// Chapter       : 
// ======================================================================

#ifndef CGAL_IO_WRITE_ARR_H
#define CGAL_IO_WRITE_ARR_H 

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

//#ifndef CGAL_ARRANGEMENT_2_H
//#include <CGAL/Arrangement_2.h>
//#endif

#include <CGAL/Inverse_index.h>
#include <CGAL/IO/write_pm.h>
#include <iostream>
#include <vector>

CGAL_BEGIN_NAMESPACE


template <class Arr, class Writer>
void write_arr(const Arr & arr, 
               Writer & writer, 
               std::ostream & o) 
{
  typedef typename Arr::Planar_map              PM;

  typedef typename Arr::Vertex                  Vertex;
  typedef typename Arr::Face                    Face;
  typedef typename Arr::Halfedge                Halfedge;
  typedef typename Arr::Curve_iterator          Curve_iterator;
  typedef typename Arr::Subcurve_iterator       Subcurve_iterator;
  typedef typename Arr::Edge_iterator           Edge_iterator;
  typedef typename Arr::Curve_const_iterator    Curve_const_iterator;
  typedef typename Arr::Subcurve_const_iterator Subcurve_const_iterator;
  typedef typename Arr::Edge_const_iterator     Edge_const_iterator;
  typedef typename Arr::Vertex_handle           Vertex_handle;
  typedef typename Arr::Halfedge_handle         Halfedge_handle;
  typedef typename Arr::Face_handle             Face_handle;
  typedef typename Arr::Vertex_const_handle     Vertex_const_handle;
  typedef typename Arr::Halfedge_const_handle   Halfedge_const_handle;
  typedef typename Arr::Face_const_handle       Face_const_handle;
  typedef typename Arr::Vertex_iterator         Vertex_iterator;
  typedef typename Arr::Vertex_const_iterator   Vertex_const_iterator;
  typedef typename Arr::Halfedge_iterator       Halfedge_iterator;
  typedef typename Arr::Halfedge_const_iterator Halfedge_const_iterator;
  typedef typename Arr::Face_iterator           Face_iterator;
  typedef typename Arr::Face_const_iterator     Face_const_iterator;
  typedef typename Arr::Ccb_halfedge_circulator Ccb_halfedge_circulator;
  typedef typename Arr::Ccb_halfedge_const_circulator              
                                                Ccb_halfedge_const_circulator;
  typedef typename Arr::Holes_iterator          Holes_iterator;
  typedef typename Arr::Holes_const_iterator    Holes_const_iterator;
  typedef typename Arr::Overlap_circulator      Overlap_circulator;
  typedef typename Arr::Overlap_const_circulator  
                                                Overlap_const_circulator;
  typedef typename Arr::Locate_type             Locate_type;
  
  typedef Inverse_index<Halfedge_const_iterator>                  H_index;
  typedef Inverse_index<Curve_const_iterator>                     Cn_index;
  typedef Inverse_index<Subcurve_const_iterator>                  Scv_index;
  typedef Inverse_index<Edge_const_iterator>                      En_index;

  H_index h_index(arr.halfedges_begin(), arr.halfedges_end()); 
  
  writer.write_title("Printing Arrangement");

  write_pm(arr.get_planar_map(), writer, o);

  writer.write_comment("Printing curve hierachy");

  std::vector<En_index> en_index_table;
  // creating curve indices.
  Cn_index cn_index(arr.curve_node_begin(), arr.curve_node_end()); 
  
  // creating the edge node indices table.
  Curve_const_iterator cv_iter;
  for (cv_iter = arr.curve_node_begin(); 
       cv_iter != arr.curve_node_end(); cv_iter++){
     En_index en_index(cv_iter->edges_begin(), cv_iter->edges_end());

     en_index_table.push_back(en_index);
  }
  
  int number_of_curves = 0;
  for (cv_iter = arr.curve_node_begin(); 
       cv_iter != arr.curve_node_end(); cv_iter++, number_of_curves++);
  writer.write_comment("number of curves");
  writer.write_value(number_of_curves);
  
  unsigned int curve_index = 0;
  for (cv_iter = arr.curve_node_begin(); 
       cv_iter != arr.curve_node_end(); cv_iter++, curve_index++){
    unsigned int number_of_edge_nodes = 0;
    
    writer.write_comment("'th curve", curve_index+1);
    //cout<<cv_iter->curve()<<std::endl;
    writer.write_curve(cv_iter);
    
    writer.write_comment("number of levels");
    writer.write_value(cv_iter->number_of_sc_levels());
    
    // making a table of indices for all scv levels.
    std::vector<Scv_index> scv_index;  
    unsigned int i;
    for (i = 0; i < cv_iter->number_of_sc_levels(); i++){
      //Subcurve_const_iterator tmp_begin, tmp_end; // for debug.  
      //tmp_begin = cv_iter->level_begin(i);
      //tmp_end = cv_iter->level_end(i);
      
      Scv_index one_scv_index(cv_iter->level_begin(i), cv_iter->level_end(i));
      scv_index.push_back(one_scv_index);
    }

    En_index en_index(cv_iter->edges_begin(), cv_iter->edges_end());
    
    for (i = 0; i < cv_iter->number_of_sc_levels(); i++){
      writer.write_comment("'th level", i+1);
      
      unsigned int  number_of_subcurves = 0;
      Subcurve_const_iterator sc_iter;
      for (sc_iter = cv_iter->level_begin(i); 
           sc_iter != cv_iter->level_end(i); 
           sc_iter++, number_of_subcurves++);
      writer.write_value(number_of_subcurves);
      
      for (sc_iter = cv_iter->level_begin(i); 
           sc_iter != cv_iter->level_end(i); sc_iter++){
        
        if (i+1 < cv_iter->number_of_sc_levels()){
          if (!writer.verbose()){
            writer.write_comment(
            "begin and past end indices of children subcurve nodes");
            
            Subcurve_const_iterator last_child = sc_iter->children_end();
            
            writer.write_value((scv_index[i+1])[sc_iter->children_begin()],
                               ' ');
            writer.write_value((scv_index[i+1])[--last_child] + 1);
          }
          else {
            writer.write_comment("All children subcurve nodes");

            Subcurve_const_iterator child_iter;
            for (child_iter = sc_iter->children_begin();
                 child_iter != sc_iter->children_end(); 
                 child_iter++)
              writer.write_subcurve (child_iter);
          }
        }
          
        else{  // getting to the edge nodes.
          if (!writer.verbose()){
            writer.write_comment
              ("begin and past end indices of children edge nodes");
            
            Edge_const_iterator last_child = sc_iter->edges_end();

            writer.write_value(en_index[sc_iter->edges_begin()], ' ');
            writer.write_value(en_index[--last_child] + 1);
          }
          else{
            writer.write_comment("All children edge nodes");
            for (Edge_const_iterator child_iter = sc_iter->edges_begin();
                 child_iter != sc_iter->edges_end(); child_iter++)
              writer.write_edge(child_iter);
          }
        }

        //writer.skip_line();
        
        writer.write_comment("subcurve of current level");
        writer.write_subcurve(sc_iter);
      }
    }
  
    writer.write_comment("number of edge nodes");
    for (Edge_const_iterator edge_count_iter = cv_iter->edges_begin(); 
         edge_count_iter != cv_iter->edges_end(); 
         edge_count_iter++,  number_of_edge_nodes++);
    
    writer.write_value(number_of_edge_nodes);
    
    writer.write_comment("----------------------- Edge nodes childrens:");
    for (Edge_const_iterator edge_iter = cv_iter->edges_begin(); 
         edge_iter != cv_iter->edges_end(); edge_iter++){
      if (!writer.verbose()){
        // printing next overlapping edge node.
        writer.write_comment("pair indices (curve node and its edge node) "
                             "for next overlapping edge node :");
        
        //cout<<"edge_iter->curve()"<<edge_iter->curve()<<endl;
        
        Edge_const_iterator edge_past_end_child = 
          Edge_const_iterator(edge_iter->children_end());
               
        std::size_t j = cn_index[edge_past_end_child->curve_node()];
        std::size_t k = (en_index_table[j])[edge_past_end_child];
        
        writer.write_value(j, ' ');
        writer.write_value(k);
        

        //cout<<edge_iter->children_begin()->curve();
        //writer.write_index(en_index[edge_iter->children_begin()]);
        //writer.write_index(en_index[edge_iter->children_end()]);
        
        writer.write_comment("Halfedge indices associated with edge nodes");
        writer.write_value
          (h_index[Halfedge_const_iterator(edge_iter->halfedge())]);
      }
      else{
        writer.write_comment("Halfedge associated with edge nodes");
        writer.write_halfedge_verbose(edge_iter->halfedge());
      }
      
      //writer.skip_line();
      writer.write_comment("Edge node curve");
      writer.write_edge(edge_iter);
     
    }

    writer.write_comment("finished current level");
    //writer.write_edge_nodes_end();
  }

  writer.write_title("End of Arrangement");
}

CGAL_END_NAMESPACE

#endif
