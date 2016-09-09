// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/IO/File_header.h
// package       : Planar_map (5.113)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Eti Ezra
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_FILE_HEADER_H
#define CGAL_IO_FILE_HEADER_H 1

#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif

CGAL_BEGIN_NAMESPACE

// Info structure for PM file headers
// ===================================
class  File_header {
private:
  // Publicly accessible file informations.
  std::size_t   n_vertices;
  std::size_t   n_halfedges;
  std::size_t   n_faces;
  
  bool m_verbose;       // printing a format that a 'human' can read.
  bool m_no_comments;   // no comments in output.
  bool m_ascii;         // ascii format.
  
  int  m_offset;       // index offset for vertices, usually 0.  
  // Publicly accessible but not that well supported file informations.
  bool m_colors;      // COFF detected.
  
  // More privately used file informations to scan the file.
  int  m_dim;         // dimension for PM (will not be supported).

public:
  typedef  File_header           Self;
  
  File_header(bool verbose = false, bool no_comments = false, 
              bool ascii = true, int offset = 0, bool colors = false,
              int dim = 2) :
    n_vertices(0),
    n_halfedges(0),
    n_faces(0),
    m_verbose(verbose),
    m_no_comments(no_comments),
    m_ascii(ascii),
    m_offset(offset),
    m_colors(colors),
    m_dim(dim)
  {}
 
  // copy constructor
  File_header(const Self & file_header):
    n_vertices(file_header.number_of_vertices()),
    n_halfedges(file_header.number_of_halfedges()),
    n_faces(file_header.number_of_faces()),
    m_verbose(file_header.verbose()),
    m_no_comments(file_header.no_comments()),
    m_ascii(file_header.ascii()),
    m_offset(file_header.index_offset()),
    m_colors(file_header.has_colors()),
    m_dim(file_header.dimension())
  {}
  /*Self& operator= ( const Base& base) { (Base&)(*this) = base;
    return *this;
    }*/
  
  std::size_t   number_of_vertices()   const { return n_vertices; }
  std::size_t   number_of_halfedges()  const { return n_halfedges; }
  std::size_t   number_of_faces()     const { return n_faces; }

  bool verbose()            const { return m_verbose; }
  bool ascii()              const { return m_ascii; } // ASCII format.
  bool no_comments()        const { return m_no_comments; }
  bool comments()           const { return ! m_no_comments; }
  int  index_offset()       const { return m_offset; }
  bool has_colors()         const { return m_colors; } // COFF detected.
  int  dimension()          const { return m_dim; }
  
  void set_number_of_vertices( std::size_t  n)      { n_vertices = n; }
  void set_number_of_halfedges( std::size_t  n)     { n_halfedges = n; }
  void set_number_of_faces( std::size_t  n)         { n_faces   = n; }

  void set_verbose( bool b)       { m_verbose            = b; }
  void set_ascii( bool b)         { m_ascii      = b; }
  void set_no_comments( bool b)   { m_no_comments = b; }
  void set_index_offset( int i)   { m_offset      = i; }  
  void set_colors( bool b)        { m_colors      = b; }
  void set_dimension( int i)      { m_dim         = i; }

  // ---- io functions for header file ----
  // istream modifier skips chars until end of line.
  inline std::istream& skip_until_EOL( std::istream& in) {
    char c;
    while ( in.get(c) && c != '\n')
      ;
    return in;
  }
  
  // istream modifier that checks for OFF comments and removes them.
  inline std::istream& skip_comment_OFF( std::istream& in) {
    char c;
    while( (in >> c) && c == '#')
      skip_until_EOL(in);
    in.putback(c);
    return in;
  }
};

CGAL_END_NAMESPACE

#endif // CGAL_IO_FILE_HEADER_PM_H //
