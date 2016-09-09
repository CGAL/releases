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
// file          : include/CGAL/IO/Trapezoidal_decomposition_2_iostream.h
// package       : Trapezoidal_decomposition (1.17)
// author(s)	 : Oren Nechushtan
//
//
// maintainer(s) : Oren Nechushtan
//
//
// coordinator	 : Tel-Aviv University (Dan Halperin)
//
// Chapter		 : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_IOSTREAM_H
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_IOSTREAM_H

#ifndef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_H
#include <CGAL/Trapezoidal_decomposition_2.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class Traits>
std::ostream& operator<<(
  std::ostream &out,
  const typename Trapezoidal_decomposition_2<Traits>::In_face_iterator& it)
{
	out << "In_face_iterator(";
	if (it.operator->()) out << *it; else out <<"end";
	return out << ")" << std::flush;
}

template < class Traits>
std::ostream& write(
   std::ostream &out,const Trapezoidal_decomposition_2<Traits>& td)
{
	return out << td;
}

template < class Traits>
std::ostream& operator<<(
   std::ostream &out,const Trapezoidal_decomposition_2<Traits>& td)
{
	return write(out,td.get_data_structure(),td.get_traits());
}

template < class Traits>
std::ostream& write(std::ostream &out,const Td_X_trapezoid<Traits>& t,
					const Traits& traits,bool validate=true)
{
	typedef Trapezoidal_decomposition_2<Traits> TD;
	typedef Td_X_trapezoid<Traits> X_trapezoid;
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
		if (traits.is_degenerate_point(t) && value[j])
			out << "=" << value[j]->top();
		out << " ";
	}
	out << ")" << std::flush;
	
	if (t.is_active())
	{
		if (!traits.is_degenerate(t))
		{
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
		}
		else if (traits.is_degenerate_curve(t))
			out << ",C";
		else // if (t.is_degenerate_point())
			out << ",P";
	}
	else
		out << ",D";
	
/*	Calling t.is_valid requires the traits to be initialized with the proper 
bounding box */
	if (validate)
	{
		if (t.is_valid(&traits))
			out << ",+";
		else
			out << ",-";
	}
	
	out << ")" << std::flush;
	
	return out;
}

template < class Traits>
std::ostream& operator<<(std::ostream &out,const Td_X_trapezoid<Traits>& t)
{
	typedef Trapezoidal_decomposition_2<Traits> TD;
	typedef Td_X_trapezoid<Traits> X_trapezoid;
	typedef X_trapezoid* pointer;
	Traits traits;

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
		if (traits.is_degenerate_point(t) && value[j])
			out << "=" << value[j]->top();
		out << " ";
	}
	out << ")" << std::flush;
	
	if (t.is_active())
	{
		if (!traits.is_degenerate(t))
		{
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
		}
		else if (traits.is_degenerate_curve(t))
			out << ",C";
		else // if (t.is_degenerate_point())
			out << ",P";
	}
	else
		out << ",D";
	
/*	Calling t.is_valid requires the traits to be initialized with the proper 
bounding box
	if (traits)
	{
		if (t.is_valid(traits))
			out << ",+";
		else
			out << ",-";
	}
*/	
	out << ")" << std::flush;
	
	return out;
}

CGAL_END_NAMESPACE

#endif //CGAL_TRAPEZOIDAL_DECOMPOSITION_2_IOSTREAM_H
