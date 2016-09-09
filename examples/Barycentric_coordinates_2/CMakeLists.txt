# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Barycentric_coordinates_2_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "Discrete_harmonic_coordinates_example.cpp" )
  create_single_source_cgal_program( "Mean_value_coordinates_example.cpp" )
  create_single_source_cgal_program( "Segment_coordinates_example.cpp" )
  create_single_source_cgal_program( "Terrain_height_modeling.cpp" )
  create_single_source_cgal_program( "Triangle_coordinates_example.cpp" )
  create_single_source_cgal_program( "Triangle_coordinates_speed_test.cpp" )
  create_single_source_cgal_program( "Wachspress_coordinates_example.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

