# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Combinatorial_map_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "map_3_dynamic_onmerge.cpp" )
  create_single_source_cgal_program( "map_3_foreach.cpp" )
  create_single_source_cgal_program( "map_3_marks.cpp" )
  create_single_source_cgal_program( "map_3_operations.cpp" )
  create_single_source_cgal_program( "map_3_simple_example.cpp" )
  create_single_source_cgal_program( "map_3_with_colored_facets.cpp" )
  create_single_source_cgal_program( "map_4_simple_example.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

