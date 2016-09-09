# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Spatial_sorting_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "example_delaunay_2.cpp" )
  create_single_source_cgal_program( "hilbert.cpp" )
  create_single_source_cgal_program( "hilbert_policies.cpp" )
  create_single_source_cgal_program( "hilbert_sort_on_sphere.cpp" )
  create_single_source_cgal_program( "myPoint.cpp" )
  create_single_source_cgal_program( "small_example_delaunay_2.cpp" )
  create_single_source_cgal_program( "sort_indices.cpp" )
  create_single_source_cgal_program( "sp_sort_using_property_map_2.cpp" )
  create_single_source_cgal_program( "sp_sort_using_property_map_3.cpp" )
  create_single_source_cgal_program( "sp_sort_using_property_map_d.cpp" )
  create_single_source_cgal_program( "spatial_sort_on_sphere.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

