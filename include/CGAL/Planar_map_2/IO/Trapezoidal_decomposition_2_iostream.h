// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
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
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : include/CGAL/Planar_map_2/IO/Trapezoidal_decomposition_2_iostream.h
// package       : pm (4.20)
// author(s)     : ?
// coordinator   : ?
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_IOSTREAM
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_IOSTREAM
        
  template < class Traits,class X_curve_plus>
  std::ostream& operator<<(std::ostream &out,const typename Trapezoidal_decomposition_2<Traits,X_curve_plus>::In_face_iterator& it)
    {
      out << "In_face_iterator(";
      if (it.operator->()) out << *it; else out <<"end";
      return out << ")" << std::flush;
    }

template < class Traits,class X_curve_plus>
std::ostream& operator<<(std::ostream &out,const Trapezoidal_decomposition_2<Traits,X_curve_plus>& td)
{
  return out << td.get_trapezoid_tree() << std::flush;
}

template < class Traits,class X_curve_plus>
std::ostream& operator<<(std::ostream &out,const __X_trapezoid<Traits, X_curve_plus>& t)
{
  typedef Trapezoidal_decomposition_2<Traits,X_curve_plus> TD;
  typedef __X_trapezoid<Traits, X_curve_plus> X_trapezoid;
  typedef X_trapezoid* pointer;
  out << "(";
  if (!t.is_left_unbounded()) out << t.left(); else out << "-oo";
  out << ",";
	if (!t.is_right_unbounded()) out << t.right(); else out << "+oo";
	out << "," << std::flush;
	if (!t.is_bottom_unbounded()) out << t.bottom(); else out << "-oo";
	out << ",";
	if (!t.is_top_unbounded()) out << t.top(); else out << "+oo";
	out << ",neighbours(" << std::flush;

	// debug neighbours equivalence relation
	int max_size=4+1;
	int null_size=2,size=null_size,i,j;
        
	X_trapezoid* value[] =
	{
          0,
          (X_trapezoid*)CGAL_TRAPEZOIDAL_DECOMPOSITION_2_DELETE_SIGNATURE,
          t.left_bottom_neighbour(),
          t.left_top_neighbour(),
          t.right_bottom_neighbour(),
          t.right_top_neighbour()
	};
	typedef char debug_string[256];
	debug_string name[]=
	{
          "none",
          "deleted",
          "lb",
          "lt",
          "rb",
          "rt"
	};
	for (j=null_size;j<=max_size;j++)
          {
            for (i=0;i<size;i++)
              if (value[j]==value[i])
                {
                  CGAL_CLIB_STD::strcat(name[i],"=");
                  CGAL_CLIB_STD::strcat(name[i],name[j]);
                  break;
                }
            if (i==size)
              {
                value[size]=value[j];
                CGAL_CLIB_STD::strcpy(name[size++],name[j]);
              }
          }
	if (size==null_size) {out << "none";}
	for(j=null_size;j<size;j++)
          {
            out << name[j];
            // identify neighbours
            if (t.is_degenerate_point() && value[j])
              out << "=" << value[j]->top();
            out << " ";
          }
	out << ")" << std::flush;
	
	if (t.is_active())
          if (!t.is_degenerate())
            if (t.is_unbounded())
              {
                out << ",U";
                if (t.is_left_unbounded())
                  out << (char) 174;
                if (t.is_bottom_unbounded())
                  out << (char) 25;
                if (t.is_top_unbounded())
                  out << (char) 24;
                if (t.is_right_unbounded())
                  out << (char) 175;
              }
            else
              out << ",T";
          else if (t.is_degenerate_curve())
            out << ",C";
          else // if (t.is_degenerate_point())
            out << ",P";
			else
                          out << ",D";
        
        //#ifdef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_DEBUG
        
        if (t.is_valid())
          out << ",+";
        else
          out << ",-";
        
        //#endif
        
        out << ")"
          
          //#ifdef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_DEBUG
          
             << std::flush
				
          //#endif
				
          ;
        
        return out;
}
#endif#ifdef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_DEBUG
        
  template < class Traits,class X_curve_plus>
  std::ostream& operator<<(std::ostream &out,const typename Trapezoidal_decomposition_2<Traits,X_curve_plus>::In_face_iterator& it)
    {
      out << "In_face_iterator(";
      if (it.operator->()) out << *it; else out <<"end";
      return out << ")" << std::flush;
    }

template < class Traits,class X_curve_plus>
std::ostream& operator<<(std::ostream &out,const Trapezoidal_decomposition_2<Traits,X_curve_plus>& td)
{
  return out << td.get_trapezoid_tree() << std::flush;
}

template < class Traits,class X_curve_plus>
std::ostream& operator<<(std::ostream &out,const __X_trapezoid<Traits, X_curve_plus>& t)
{
  typedef Trapezoidal_decomposition_2<Traits,X_curve_plus> TD;
  typedef __X_trapezoid<Traits, X_curve_plus> X_trapezoid;
  typedef X_trapezoid* pointer;
  out << "(";
  if (!t.is_left_unbounded()) out << t.left(); else out << "-oo";
  out << ",";
	if (!t.is_right_unbounded()) out << t.right(); else out << "+oo";
	out << "," << std::flush;
	if (!t.is_bottom_unbounded()) out << t.bottom(); else out << "-oo";
	out << ",";
	if (!t.is_top_unbounded()) out << t.top(); else out << "+oo";
	out << ",neighbours(" << std::flush;

	// debug neighbours equivalence relation
	int max_size=4+1;
	int null_size=2,size=null_size,i,j;
        
	X_trapezoid* value[] =
	{
          0,
          (X_trapezoid*)CGAL_TRAPEZOIDAL_DECOMPOSITION_2_DELETE_SIGNATURE,
          t.left_bottom_neighbour(),
          t.left_top_neighbour(),
          t.right_bottom_neighbour(),
          t.right_top_neighbour()
	};
	typedef char debug_string[256];
	debug_string name[]=
	{
          "none",
          "deleted",
          "lb",
          "lt",
          "rb",
          "rt"
	};
	for (j=null_size;j<=max_size;j++)
          {
            for (i=0;i<size;i++)
              if (value[j]==value[i])
                {
                  CGAL_CLIB_STD::strcat(name[i],"=");
                  CGAL_CLIB_STD::strcat(name[i],name[j]);
                  break;
                }
            if (i==size)
              {
                value[size]=value[j];
                CGAL_CLIB_STD::strcpy(name[size++],name[j]);
              }
          }
	if (size==null_size) {out << "none";}
	for(j=null_size;j<size;j++)
          {
            out << name[j];
            // identify neighbours
            if (t.is_degenerate_point() && value[j])
              out << "=" << value[j]->top();
            out << " ";
          }
	out << ")" << std::flush;
	
	if (t.is_active())
          if (!t.is_degenerate())
            if (t.is_unbounded())
              {
                out << ",U";
                if (t.is_left_unbounded())
                  out << (char) 174;
                if (t.is_bottom_unbounded())
                  out << (char) 25;
                if (t.is_top_unbounded())
                  out << (char) 24;
                if (t.is_right_unbounded())
                  out << (char) 175;
              }
            else
              out << ",T";
          else if (t.is_degenerate_curve())
            out << ",C";
          else // if (t.is_degenerate_point())
            out << ",P";
			else
                          out << ",D";
        
        //#ifdef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_DEBUG
        
        if (t.is_valid())
          out << ",+";
        else
          out << ",-";
        
        //#endif
        
        out << ")"
          
          //#ifdef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_DEBUG
          
             << std::flush
				
          //#endif
				
          ;
        
        return out;
}

#endif //CGAL_TRAPEZOIDAL_DECOMPOSITION_2_IOSTREAM
