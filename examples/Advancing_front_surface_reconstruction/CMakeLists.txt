# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Advancing_front_surface_reconstruction_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "boundaries.cpp" )
  create_single_source_cgal_program( "reconstruction_class.cpp" )
  create_single_source_cgal_program( "reconstruction_fct.cpp" )
  create_single_source_cgal_program( "reconstruction_surface_mesh.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

