// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Partition_opt_cvx_vertex.h
// package       : Partition_2 (1.38)
// chapter       : Planar Polygon Partitioning
//
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/01/19 10:08:54 $
//
// author(s)     : Susan Hert
//
// coordinator   : MPI (Susan Hert)
//
// implementation: Vertex used in optimal convex partitioning algorithm
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_PARTITION_OPT_CVX_VERTEX_H
#define CGAL_PARTITION_OPT_CVX_VERTEX_H

#include <list>
#include <CGAL/Partition_opt_cvx_diagonal_list.h>

namespace CGAL {

class Partition_opt_cvx_stack_record 
{
public:

   Partition_opt_cvx_stack_record() {}

   Partition_opt_cvx_stack_record(unsigned int old,  int value) : 
       _old(old), _value(value), _solution(Partition_opt_cvx_diagonal_list()) 
   {}

   Partition_opt_cvx_stack_record(unsigned int old,  int value, 
                            const Partition_opt_cvx_diagonal_list& solution) : 
       _old(old), _value(value), _solution(solution) 
   {}

   unsigned int vertex_num() { return _old; }

   int value() {return _value; }

   Partition_opt_cvx_diagonal_list solution() { return _solution; }

private:
   unsigned int _old;
   int _value;
   Partition_opt_cvx_diagonal_list _solution;
};

class Partition_opt_cvx_vertex 
{
public:

   Partition_opt_cvx_vertex() {}

   Partition_opt_cvx_vertex(unsigned int v_num): _v_num(v_num), 
                      _stack(std::list<Partition_opt_cvx_stack_record>()),
                      _best_so_far(Partition_opt_cvx_stack_record(0, 0))
   {}

   unsigned int vertex_num( ) { return _v_num; }

   Partition_opt_cvx_stack_record best_so_far( ) 
   { 
      return _best_so_far;
   }

   bool stack_empty() { return _stack.empty(); }

   // Pre:  stack is not empty
   Partition_opt_cvx_stack_record stack_top()
   {
      return _stack.back();
   }

   void stack_push(unsigned int vertex, int value, 
                   const Partition_opt_cvx_diagonal_list& diag_list) 
   {
      _best_so_far = Partition_opt_cvx_stack_record(vertex, value, diag_list);
      _stack.push_back(_best_so_far);
   }
   
   // Pre:  stack is not empty
   void stack_pop() 
   {
       _best_so_far = _stack.back();
       _stack.pop_back();
   }

private:
   unsigned int                               _v_num;
   std::list<Partition_opt_cvx_stack_record>  _stack;
   Partition_opt_cvx_stack_record             _best_so_far;
};

}

#endif // CGAL_PARTITION_OPT_CVX_VERTEX_H
