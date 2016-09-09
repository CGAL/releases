// Copyright (c) 2002  Max-Planck-Institute Saarbruecken (Germany)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Nef_3/demo/Nef_3/nef_3_filtered.cpp $
// $Id: nef_3_filtered.cpp 44870 2008-08-11 13:43:58Z hachenb $
// 
//
// Author(s)     : Lutz Kettner
//                 Peter Hachenberger
//
// Demo program maintaining a stack of Nef polyhedra in the space and
// a manipulation language for stack ops, file loading and saving, etc.
// ============================================================================
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Nef_3/demo_stack.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;

int main(  int argc, char* argv[]) {    
 
  CGAL::demo_stack<Kernel> ds;
  if ( argc < 2
       || strcmp( argv[1], "-h") == 0
       || strcmp( argv[1], "-help") == 0 )
    {
      ds.help_message( cerr);
      exit(1);
    }
  CGAL::set_pretty_mode(std::cerr);
  
  return ds.eval( argc-1, argv+1);
}
