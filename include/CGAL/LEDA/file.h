// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/LEDA/file.h
// package       : cgal_window (1.0.4)
// revision      : 1.0.3
// revision_date : 25 June 2001
// author(s)     : Matthias Baesken, Algorithmic Solutions
//
// coordinator   : Matthias Baesken, Trier  (<baesken>) 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef __CGAL_WINDOW_FILE__
#define __CGAL_WINDOW_FILE__

#if defined(CGAL_USE_CGAL_HEADERS)
#include <CGAL/basic.h>
#endif

#include <CGAL/LEDA/basic.h>
#include <list>


namespace CGAL {



extern __exportF void message_box(const char* msg, const char* label);



extern __exportF std::string set_directory(std::string new_dir);
/*{\Xfuncl     sets the current working directory to |new_dir| and 
               returns the name of the old cwd. }*/

extern __exportF std::string get_directory();
/*{\Xfuncl     returns the name of the current working directory. }*/


extern __exportF std::list<std::string> get_directories(std::string dir);
/*{\Xfuncl     returns the list of names of all sub-directories in 
               directory |dir|. }*/

extern __exportF std::list<std::string> get_files(std::string dir);
/*{\Xfuncl     returns the list of names of all regular files in 
               directory |dir|. }*/

extern __exportF std::list<std::string> get_files(std::string dir, std::string pattern);
/*{\Xfuncl     returns the list of names of all regular files in 
               directory |dir| matching pattern. }*/

extern __exportF std::list<std::string> get_entries(std::string dir);
/*{\Xfuncl     returns the list of all entries (directory and files) of 
               directory |dir|. }*/


extern __exportF bool is_directory(std::string fname);
/*{\Xfuncl     returns true if |fname| is the path name of a directory
               and false otherwise. }*/

extern __exportF bool is_file(std::string fname);
/*{\Xfuncl     returns true if |fname| is the path name of a regular file
               and false otherwise. }*/

extern __exportF bool is_link(std::string fname);
/*{\Xfuncl     returns true if |fname| is the path name of a symbolic link
               and false otherwise. }*/


extern __exportF std::string tmp_file_name();
/*{\Xfuncl     returns a unique name for a temporary file. }*/

}

#endif
