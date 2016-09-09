# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Periodic_2_triangulation_2_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "p2t2_adding_handles.cpp" )
  create_single_source_cgal_program( "p2t2_colored_vertices.cpp" )
  create_single_source_cgal_program( "p2t2_covering.cpp" )
  create_single_source_cgal_program( "p2t2_find_conflicts.cpp" )
  create_single_source_cgal_program( "p2t2_geometric_access.cpp" )
  create_single_source_cgal_program( "p2t2_hierarchy.cpp" )
  create_single_source_cgal_program( "p2t2_info_insert_with_pair_iterator_2.cpp" )
  create_single_source_cgal_program( "p2t2_info_insert_with_transform_iterator_2.cpp" )
  create_single_source_cgal_program( "p2t2_info_insert_with_zip_iterator_2.cpp" )
  create_single_source_cgal_program( "p2t2_large_point_set.cpp" )
  create_single_source_cgal_program( "p2t2_simple_example.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

