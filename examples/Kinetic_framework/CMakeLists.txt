# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Kinetic_framework_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "adding_a_certificate.cpp" )
  create_single_source_cgal_program( "defining_a_simulation_traits.cpp" )
  create_single_source_cgal_program( "listener.cpp" )
  create_single_source_cgal_program( "pointer_queue.cpp" )
  create_single_source_cgal_program( "ref_counted.cpp" )
  create_single_source_cgal_program( "trivial_kds.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

