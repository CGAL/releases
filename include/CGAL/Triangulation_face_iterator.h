// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Triangulation_face_iterator.h
// package       : Triangulation (1.23)
// source        : web/Triangulation_face_iterator.fw
// revision      : $Revision: 1.13 $
// revision_date : $Date: 1998/07/15 14:07:01 $
// author(s)     : Olivier Devillers
//
// coordinator   : Herve Bronnimann
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_TRIANGULATION_FACE_ITERATOR_H
#define CGAL_TRIANGULATION_FACE_ITERATOR_H

template<class I>
class CGAL_Triangulation_2;


template<class I>
class CGAL_Triangulation_face_iterator
    : public bidirectional_iterator<typename I::Face,ptrdiff_t>
    , public I::Face::Face_handle
 {
    public:
    typedef typename I::Vertex Vertex;
    typedef typename I::Vertex_handle Vertex_handle;
    typedef typename I::Face Face;
    typedef typename I::Face_handle Face_handle;
    typedef CGAL_Triangulation_face_iterator<I> Face_iterator;

    protected:
        Face_handle pos;
        CGAL_Triangulation_2<I>* triangulation;
        
    public:
        CGAL_Triangulation_face_iterator()
            : I::Face::Face_handle(), pos(NULL), triangulation(NULL)
        {}
        CGAL_Triangulation_face_iterator(CGAL_Triangulation_2<I> *T)
            : I::Face::Face_handle(), pos(NULL), triangulation(T)
        {
            if(T->number_of_vertices() < 2){
                return;
            }
            pos = T->infinite_face();
            Face_handle start = pos;
            while (T->is_infinite(pos)){
                increment();
                if(pos == start){
                    pos.clear();
                    ptr() = NULL;                   // there is no finite triangle
                    return;
                }
            }
            ptr() = &(*pos) ;
        }
        CGAL_Triangulation_face_iterator(CGAL_Triangulation_2<I> *T, int)
            : I::Face::Face_handle(), pos(NULL), triangulation(T)
        {}
        CGAL_Triangulation_face_iterator(const Face_iterator& fi)
          : I::Face::Face_handle(fi), pos(fi.pos), triangulation(fi.triangulation)
        {}
        
        
        Face_iterator&
        operator=(const Face_iterator& fi)
        {
            ptr() = fi.ptr();
            pos = fi.pos;
            triangulation = fi.triangulation;
            return *this;
        }
        
        bool
        operator==(const Face_iterator& fi) const
        {
            return ((pos == fi.pos )&&(triangulation==fi.triangulation));
        }
        
        
        bool
        operator!=(const Face_iterator& fi)
        {
            return !(*this == fi);
        }
        Face_iterator&
        operator++()
        {
            if ( pos == NULL ){
                return *this;    //  past-the-end iterator cannot advance
            }
            do{
                increment();
                if ( pos == (triangulation->infinite_face()) ){
                    pos = NULL;  // complete tour
                    ptr() = &(*pos) ;
                    return *this;
                }
            }while (triangulation->is_infinite(pos));
            ptr() = &(*pos) ;
            return *this;           // next finite triangle found
        }
        Face_iterator&
        operator--()
        {
            if ( pos == NULL ){//  past the end iterator can decrease
                *this = Face_iterator(triangulation); // first finite triangle
            }              //next loop will go to last finite triangle
        
            do{
                decrement();
                if ( pos == triangulation->infinite_face()){
                    pos = NULL;  // complete tour
                    ptr() = &(*pos) ;
                    return *this;
                }
           }while (triangulation->is_infinite(pos));
           ptr() = &(*pos) ;
           return *this;           // next finite triangle found
        }
        
        Face_iterator
        operator++(int)
        {
            Face_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        
        Face_iterator
        operator--(int)
        {
            Face_iterator tmp(*this);
            --(*this);
            return tmp;
        }
        
        
    protected:
        
        static
        int
        ccw(int i)
        {
            return (i+1) % 3;
        }
        
        
        static
        int
        cw(int i)
        {
            return (i+2) % 3;
        }
        
        void
        increment()
        {
            int max = maximum(pos);
            Face_handle next=pos->neighbor(max);         // tentatative first child
            Face_handle parent;
            int max2 = maximum(next);
            if ( next->neighbor(cw(max2))== pos){
              // next is the first child of pos
              pos = next;
              return;
            }
            // look for the second child of an ancestor of pos
            next=pos->neighbor(ccw(max));          // tentatative second child
            while (1){
                max2 = maximum(next);
                if ( next->neighbor(cw(max2))== pos) // next is the second child of pos
                    { pos = next; return;}
                while (1){
                    parent = pos->neighbor(cw(max));        // go to parent
                    max = maximum(parent);
                    next=parent->neighbor(ccw(max));       // tentatative second child
                    if (next==pos)              // already coming back from this child
                        { pos = parent; continue; }
                    else
                        { pos = parent; break; }
                }
            }
        }
        
        
        void
        decrement()
        {
            int max = maximum(pos);
            Face_handle next=pos->neighbor(cw(max));     // parent of pos
            int max2 = maximum(next);
            if ( next->neighbor(max2) == pos)      // pos is the first child of next
                { pos = next; return;}
            pos = next->neighbor(max2);         // tentative first child
            max = maximum(pos);
            if ( pos->neighbor(cw(max))!=next)   // pos is not the first child of next
                { pos = next; return;}
            // look for "last" node in first subtree of next
            while (1){
                next = pos->neighbor(ccw(max));       // tentatative second child
                max2 = maximum(next);
                if (next->neighbor(cw(max2))!= pos){
                    //next is not the second child of pos
                    next=pos->neighbor(max);         // tentative first child
                    max2 = maximum(next);
                    if ( next->neighbor(cw(max2))!= pos){
                        //next is not first child of pos
                        return;
                    }
                }
                pos=next;
                max=max2;
            }
        }
        
        
        int maximum(const Face_handle& f) const
        {
            if ( triangulation->is_infinite(f) ){
                return f->index( triangulation->infinite_vertex() );
            }
            if(triangulation->traits().compare_y(f->vertex(0)->point(),
                                               f->vertex(1)->point()) == CGAL_SMALLER)
                //  v0 < v1
                if(triangulation->traits().compare_y(f->vertex(2)->point(),
                                                   f->vertex(1)->point())==CGAL_SMALLER)
                    //  v0,v2 < v1
                    { return 1; }
                else
                    //  v0 < v1 <= v2
                    { return 2; }
            else
                //  v1 <= v0
        
                if(triangulation->traits().compare_y(f->vertex(1)->point(),
                                                   f->vertex(2)->point())!=CGAL_SMALLER)
                    //  v2 <= v1 <= v0
                    if(triangulation->traits().compare_y(
                                                   f->vertex(0)->point(),
                                                   f->vertex(1)->point()) == CGAL_EQUAL)
                        //  v2 <= v1 == v0
                        { return 1; }
                    else
                        //  v2 <= v1 < v0
                        { return 0; }
                else
                    //  v1<=v0, v1<v2
                    if(triangulation->traits().compare_y(f->vertex(0)->point(),
                                                       f->vertex(2)->point())
                       ==CGAL_SMALLER)
                        //  v1 <= v0 < v2
                        { return 2; }
                    else
                        //  v1 < v2 <= v0
                        { return 0; }
        
        }
        
        
        
    };

#endif // CGAL_TRIANGULATION_FACE_ITERATOR_H
