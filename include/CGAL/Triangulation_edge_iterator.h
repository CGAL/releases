// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Triangulation_edge_iterator.h
// author(s)     : Olivier Devillers
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_TRIANGULATION_EDGE_ITERATOR_H
#define CGAL_TRIANGULATION_EDGE_ITERATOR_H

template<class I>
class CGAL_Triangulation_2;


template<class I>
class CGAL_Triangulation_edge_iterator
    : public bidirectional_iterator
            <pair<typename I::Face::Face_handle ,int>,ptrdiff_t>
{
public:
    typedef typename I::Vertex Vertex;
    typedef typename I::Face Face;
    typedef typename Vertex::Vertex_handle Vertex_handle;
    typedef typename Vertex::Face_handle Face_handle;
    typedef pair<Face_handle ,int> Edge;
    typedef CGAL_Triangulation_edge_iterator<I> Edge_iterator;

    
    CGAL_Triangulation_edge_iterator()
        : pos(), triangulation(NULL), status(0)
    {}
    
    
    CGAL_Triangulation_edge_iterator(CGAL_Triangulation_2<I> *T)
        : pos(), triangulation(T)
    {
        if (T->number_of_vertices()<2){
            pos = NULL;                   // there is no finite edge
            return;
        }
        pos = T->infinite_face();
        Face_handle start = pos;
        while ( ! compute_status(true) ){
            increment();
            if(pos == start){
                pos=NULL;                   // there is no finite triangle
                return;
            }
        }
    }
    
    
    CGAL_Triangulation_edge_iterator(CGAL_Triangulation_2<I> *T, int)
        : pos(), triangulation(T)
    {
      switch (T->number_of_vertices() ){
        case 0:
        case 1:
          pos = NULL;
          return;
        default:
        {
          pos = T->infinite_face();
          while (associated_vertex()==NULL){
            increment();
          }
          pos = NULL;
          return;
        }
      }
    }
    Edge_iterator&
    operator++()
    {
        if (pos==NULL){
            return *this;            // cannot advance past-the=end iteartor
        }
        if ( (status >=3) && (status <=5) ) {
            // current status is 3 + ccw(i), next status is 6+i
            status = 6 + cw( status -3);
        } else do{
            increment();
            if ( pos == triangulation->infinite_face()){
                pos = NULL;   // tour complete
                return *this;
            }
        }while (!compute_status(true));
        return *this;
    }
    
    
    Edge_iterator&
    operator--()
    {
        if (pos==NULL){
            *this = Edge_iterator(triangulation);
            --*this;
            return *this;            // can decrease past-the=end iteartor
        }
        if ( (status >=3) && (status <=5) ) {
            // current status is 6+i, next status is 3 + ccw(i)
            status = 3 + ccw( status -6);
        } else do{
            decrement();
            if ( pos == triangulation->infinite_face()){
                pos = NULL;   // tour complete
                return *this;
            }
        }while (compute_status(false));
        return *this;
    }
    
    
    Edge_iterator
    operator++(int)
    {
        Edge_iterator tmp(*this);
        ++(*this);
        return tmp;
    }
    
    
    Edge_iterator
    operator--(int)
    {
        Edge_iterator tmp(*this);
        --(*this);
        return tmp;
    }
    
    Edge
    operator*() const
    {
        int j = (status<3) ? status : (status<6) ? status-3 : status-6;
        return make_pair(pos, j);
    }
    
    bool
    operator==(const Edge_iterator& fi) const
    {
        if ((pos==fi.pos)&&(triangulation==fi.triangulation)){
            if (pos==NULL) {
                return true;
            }else{
                return (status==fi.status);
            }
        }else{
            return false;
        }
    }
    
    
    bool
    operator!=(const Edge_iterator& fi) const
    {
        return ! (*this == fi);
    }
    
private:
    Face_handle pos;
    CGAL_Triangulation_2<I> *triangulation;
    
    int status;
    
    
    bool
    compute_status(bool forward)
    {
        if (pos == NULL){
            return false;
        }
        int i = maximum(pos);            // higher point
        if ( ! triangulation->is_infinite(pos)){
            if(triangulation->traits().compare_y(pos->vertex(cw(i))->point(),
                                               pos->vertex(ccw(i))->point())
               == CGAL_LARGER){
                //  vccw(i) < vcw(i)
                // right edges = i cw(i)  cw(i) ccw(i)
                status = (forward) ? 3+ccw(i) : 6+i;
            } else {
                // right edge = i cw(i)
                status = ccw(i);
            }
            return true;
        }
        CGAL_Comparison_result comp = triangulation->traits().compare_y(
                                                      pos->vertex(cw(i))->point(),
                                                      pos->vertex(ccw(i))->point());
        if( comp==CGAL_SMALLER){
            return false;
        }
        if( comp==CGAL_LARGER){
            //  vccw(i) < vcw(i)
            // right edge =  cw(i) ccw(i)
            status = i;
            return true;
        }
        // comp = CGAL_EQUAL
        if ( triangulation->traits().compare_x(pos->vertex(cw(i))->point(),
                                             pos->vertex(ccw(i))->point())
             == CGAL_SMALLER){
            //  vccw(i) < vcw(i)
            // upper horizontal edge =  cw(i) ccw(i)
            status = i;
            return true;
        }
    
        return false;
    }
    
    
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
    
    
    Vertex_handle
    associated_vertex_handle() const
    {
        if(pos == NULL) {
            return NULL;
        }
        switch(triangulation->number_of_vertices() ){
        case 0:
            return NULL;
        case 1:
            return triangulation->finite_vertex();
        case 2:
            return pos->vertex(cw(maximum(pos)));
        default:
            {
                int i = cw(maximum(pos));            // candidate associate vertex
                if(triangulation->traits().compare_y(pos->vertex(i)->point(),
                                                   pos->vertex(cw(i))->point())
                   ==CGAL_LARGER){
                    //   vcw(i) < vi
                    return pos->vertex(i);
                }
                if ( triangulation->is_infinite(pos)){
                    Face_handle f=pos->neighbor(cw(i));
                                                 // next edge on the CH in cw order
                    int   j=f->index(triangulation->infinite_vertex() );
                    CGAL_Comparison_result comp =
                        triangulation->traits().compare_y(pos->vertex(i)->point(),
                                                        f->vertex(cw(j))->point());
                    if (comp == CGAL_SMALLER){         //  vi smaller vertex
                        return pos->vertex(i);
                    }
                    if(comp ==CGAL_EQUAL){            // horizontal part of CH
                        comp = triangulation->traits().compare_x(
                                                        pos->vertex(i)->point(),
                                                        f->vertex(cw(j))->point());
                        if(comp == CGAL_LARGER){        // lower hull
                            return pos->vertex(i);
                        }
                        if(pos->vertex(cw(i)) == f->vertex(cw(j))){ // 1 dim. horiz.
                            return pos->vertex(i);
                        }
                    }
                }
            }
        }
        return NULL;
    }
    
    Vertex*
    associated_vertex() const
    {
      return &(* associated_vertex_handle() );
    }
    
    
};

#endif // CGAL_TRIANGULATION_EDGE_ITERATOR_H
