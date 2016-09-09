# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( STL_Extension_example )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE "../../include")

  create_single_source_cgal_program( "Default.cpp" )
  create_single_source_cgal_program( "Dispatch_output_iterator.cpp" )
  create_single_source_cgal_program( "in_place_list_prog.cpp" )
  create_single_source_cgal_program( "min_element_if_example.cpp" )
  create_single_source_cgal_program( "min_max_element_example.cpp" )
  create_single_source_cgal_program( "unordered_map.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

