# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Box_intersection_d_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "box_grid.cpp" )
  create_single_source_cgal_program( "custom_box_grid.cpp" )
  create_single_source_cgal_program( "minimal.cpp" )
  create_single_source_cgal_program( "minimal_self.cpp" )
  create_single_source_cgal_program( "proximity_custom_box_traits.cpp" )
  create_single_source_cgal_program( "triangle_self_intersect.cpp" )
  create_single_source_cgal_program( "triangle_self_intersect_pointers.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

