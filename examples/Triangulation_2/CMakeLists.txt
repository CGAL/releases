# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Triangulation_2_example )

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
 
if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()
 
find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  include_directories (BEFORE ../../include)

  create_single_source_cgal_program( "adding_handles.cpp" )
  create_single_source_cgal_program( "colored_face.cpp" )
  create_single_source_cgal_program( "constrained.cpp" )
  create_single_source_cgal_program( "constrained_hierarchy_plus.cpp" )
  create_single_source_cgal_program( "constrained_plus.cpp" )
  create_single_source_cgal_program( "hierarchy.cpp" )
  create_single_source_cgal_program( "regular.cpp" )
  create_single_source_cgal_program( "terrain.cpp" )
  create_single_source_cgal_program( "triangulation_prog1.cpp" )
  create_single_source_cgal_program( "voronoi.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()
