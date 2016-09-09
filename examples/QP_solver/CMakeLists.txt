# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( QP_solver_example )

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
 
if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()
 
find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  create_single_source_cgal_program( "convex_hull_containment.cpp" )
  create_single_source_cgal_program( "convex_hull_containment2.cpp" )
  create_single_source_cgal_program( "convex_hull_containment_benchmarks.cpp" )
  create_single_source_cgal_program( "cycling.cpp" )
  create_single_source_cgal_program( "first_lp.cpp" )
  create_single_source_cgal_program( "first_lp_from_iterators.cpp" )
  create_single_source_cgal_program( "first_lp_from_mps.cpp" )
  create_single_source_cgal_program( "first_nonnegative_lp.cpp" )
  create_single_source_cgal_program( "first_nonnegative_lp_from_iterators.cpp" )
  create_single_source_cgal_program( "first_nonnegative_lp_from_mps.cpp" )
  create_single_source_cgal_program( "first_nonnegative_qp.cpp" )
  create_single_source_cgal_program( "first_nonnegative_qp_from_iterators.cpp" )
  create_single_source_cgal_program( "first_nonnegative_qp_from_mps.cpp" )
  create_single_source_cgal_program( "first_qp.cpp" )
  create_single_source_cgal_program( "first_qp_basic_constraints.cpp" )
  create_single_source_cgal_program( "first_qp_from_iterators.cpp" )
  create_single_source_cgal_program( "first_qp_from_mps.cpp" )
  create_single_source_cgal_program( "important_variables.cpp" )
  create_single_source_cgal_program( "infeasibility_certificate.cpp" )
  create_single_source_cgal_program( "invert_matrix.cpp" )
  create_single_source_cgal_program( "optimality_certificate.cpp" )
  create_single_source_cgal_program( "print_first_lp.cpp" )
  create_single_source_cgal_program( "print_first_nonnegative_lp.cpp" )
  create_single_source_cgal_program( "print_first_nonnegative_qp.cpp" )
  create_single_source_cgal_program( "print_first_qp.cpp" )
  create_single_source_cgal_program( "unboundedness_certificate.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

