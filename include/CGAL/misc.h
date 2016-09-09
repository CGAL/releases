// Source: misc.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_MISC_H
#define CGAL_MISC_H

template < class T >
inline
void 
CGAL_swap(T& a, T& b)
{
 T c;
 c = a;
 a = b;
 b = c;
}

#endif // CGAL_MISC_H
