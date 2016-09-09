 


// Source: TriangleH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_TRIANGLEH2_H
#define CGAL_TRIANGLEH2_H

#include <CGAL/PointH2.h>
#include <CGAL/predicates_on_pointsH2.h>

 


template <class FT, class RT>
class CGAL_Triangle_repH2 : public handle_rep
{

friend class CGAL_TriangleH2<FT,RT>;

            CGAL_Triangle_repH2()
            {
            }
            CGAL_Triangle_repH2(const CGAL_PointH2<FT,RT> v1,
                                const CGAL_PointH2<FT,RT> v2,
                                const CGAL_PointH2<FT,RT> v3)
            {
              A[0] = v1;
              A[1] = v2;
              A[2] = v3;
              orientation = CGAL_ordertype(v1,v2,v3);
            }
            CGAL_Triangle_repH2(const CGAL_Triangle_repH2& tbc)
            {
              A[0] = tbc.A[0];
              A[1] = tbc.A[1];
              A[2] = tbc.A[2];
              orientation = tbc.orientation;
            }

            CGAL_PointH2<FT,RT>   A[3];
            CGAL_Ordertype        orientation;
};
 

 


template <class FT, class RT>
class CGAL_TriangleH2 : public handle_base
{
public:
                       CGAL_TriangleH2();
                       CGAL_TriangleH2(const CGAL_TriangleH2& t) :
                       handle_base((handle_base&) t)
                       {
                         CGAL_kernel_precondition( t.is_defined() );
                       }
                       CGAL_TriangleH2(const CGAL_PointH2<FT,RT>& p,
                                       const CGAL_PointH2<FT,RT>& q,
                                       const CGAL_PointH2<FT,RT>& r)
                       {
                         CGAL_kernel_precondition((   p.is_defined()
                                                   && q.is_defined()
                                                   && r.is_defined() ));
                         PTR = new CGAL_Triangle_repH2<FT,RT>(p,q,r);
                       }
    CGAL_TriangleH2&   operator=(const CGAL_TriangleH2<FT,RT>& t);

    CGAL_Bbox_2        bbox() const;

    CGAL_TriangleH2    transform(const CGAL_Aff_transformationH2<FT,RT>&) const;

    CGAL_Side          where_is  ( const CGAL_PointH2<FT,RT>& ) const;
    bool               is_on     ( const CGAL_PointH2<FT,RT>& ) const;
    bool               is_inside ( const CGAL_PointH2<FT,RT>& ) const;
    bool               is_outside( const CGAL_PointH2<FT,RT>& ) const;
    bool               is_in_bounded_region( const CGAL_PointH2<FT,RT>& ) const;
    bool               is_in_unbounded_region(const CGAL_PointH2<FT,RT>& )const;
    bool               is_degenerate() const;

    bool               operator==( const CGAL_TriangleH2<FT,RT>& ) const;
    bool               operator!=( const CGAL_TriangleH2<FT,RT>& ) const;
    bool               identical ( const CGAL_TriangleH2<FT,RT>& ) const;
    bool               oriented_equal( const CGAL_TriangleH2<FT,RT>& ) const;
    bool               unoriented_equal( const CGAL_TriangleH2<FT,RT>& ) const;

    CGAL_PointH2<FT,RT>
                       vertex(int i) const;
    CGAL_PointH2<FT,RT>
                       operator[](int i) const;

#ifdef CGAL_CHECK_PRECONDITIONS
    bool               is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

protected:
    CGAL_Triangle_repH2<FT,RT>*
                       ptr() const;
};
 

 
#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT, class RT >
inline
CGAL_Triangle_repH2<FT,RT>*
CGAL_TriangleH2<FT,RT>::ptr() const
{
 CGAL_kernel_precondition( is_defined() );
 return (CGAL_Triangle_repH2<FT,RT>*)PTR;
}

template < class FT, class RT >
inline
bool
CGAL_TriangleH2<FT,RT>::is_defined() const
{
  return !(PTR == NULL);
}
#endif // CGAL_CHECK_PRECONDITIONS

template < class FT, class RT >
inline
CGAL_TriangleH2<FT,RT>::CGAL_TriangleH2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL_Triangle_repH2<FT,RT>();
#endif  // CGAL_CHECK_PRECONDITIONS
}

template < class FT, class RT >
CGAL_TriangleH2<FT,RT>&
CGAL_TriangleH2<FT,RT>::operator=(const CGAL_TriangleH2<FT,RT> &t)
{
 CGAL_kernel_precondition( t.is_defined() );
 handle_base::operator=(t);
 return *this;
}
 
template <class FT, class RT>
CGAL_PointH2<FT,RT>
CGAL_TriangleH2<FT,RT>::vertex(int i) const
{
 CGAL_kernel_precondition( is_defined() );
 return ptr()->A[ i % 3 ];
}

template <class FT, class RT>
CGAL_PointH2<FT,RT>
CGAL_TriangleH2<FT,RT>::operator[](int i) const
{
 CGAL_kernel_precondition( is_defined() );
 return vertex(i);
}
 
template <class FT, class RT>
CGAL_Side
CGAL_TriangleH2<FT,RT>::where_is( const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 CGAL_Ordertype o12 = CGAL_ordertype( vertex(1), vertex(2), p);
 CGAL_Ordertype o23 = CGAL_ordertype( vertex(2), vertex(3), p);
 CGAL_Ordertype o31 = CGAL_ordertype( vertex(3), vertex(1), p);

 if (ptr()->orientation == CGAL_CLOCKWISE)
 {
    if (  (o12 == CGAL_COUNTERCLOCKWISE)
        ||(o23 == CGAL_COUNTERCLOCKWISE)
        ||(o31 == CGAL_COUNTERCLOCKWISE) )
    {
        return CGAL_INSIDE;
    }
    if (  (o12 == CGAL_COLLINEAR)
        ||(o23 == CGAL_COLLINEAR)
        ||(o31 == CGAL_COLLINEAR) )
    {
        return CGAL_ON;
    }
    else
    {
        return CGAL_OUTSIDE;
    }
 }
 else       // COUNTERCLOCKWISE
 {
    if (  (o12 == CGAL_CLOCKWISE)
        ||(o23 == CGAL_CLOCKWISE)
        ||(o31 == CGAL_CLOCKWISE) )
    {
        return CGAL_OUTSIDE;
    }
    if (  (o12 == CGAL_COLLINEAR)
        ||(o23 == CGAL_COLLINEAR)
        ||(o31 == CGAL_COLLINEAR) )
    {
        return CGAL_ON;
    }
    else
    {
        return CGAL_INSIDE;
    }
 }
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::is_inside( const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 return ( where_is(p) == CGAL_INSIDE );
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::is_on(const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 return where_is(p) == CGAL_ON;
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::is_outside( const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 return ( where_is(p) == CGAL_OUTSIDE );
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::is_in_bounded_region(const CGAL_PointH2<FT,RT>& p)
                                                                          const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 if (ptr()->orientation == CGAL_COUNTERCLOCKWISE )
 {
    return ( where_is(p) == CGAL_INSIDE );
 }
 else
 {
    return ( where_is(p) == CGAL_OUTSIDE );
 }
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::is_in_unbounded_region(const CGAL_PointH2<FT,RT>& p)
                                                                          const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 if (ptr()->orientation == CGAL_CLOCKWISE )
 {
    return ( where_is(p) == CGAL_INSIDE );
 }
 else
 {
    return ( where_is(p) == CGAL_OUTSIDE );
 }
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::is_degenerate() const
{
 CGAL_kernel_precondition( is_defined() );
 return (ptr()->orientation == CGAL_COLLINEAR);
}

template <class FT, class RT>
inline
CGAL_Bbox_2
CGAL_TriangleH2<FT,RT>::bbox() const
{
 CGAL_kernel_precondition( is_defined() );
 return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}
 


template <class FT, class RT>
CGAL_TriangleH2<FT,RT>
CGAL_TriangleH2<FT,RT>::transform( const CGAL_Aff_transformationH2<FT,RT>& t)
                                                                          const
{
 CGAL_kernel_precondition( is_defined() && t.is_defined() );
 return CGAL_TriangleH2<FT,RT>(t.transform(ptr()->A[0]),
                               t.transform(ptr()->A[1]),
                               t.transform(ptr()->A[2]) );
}
 


template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::operator==(const CGAL_TriangleH2<FT,RT>& t) const
{
 CGAL_kernel_precondition( is_defined() && t.is_defined() );
 int j = 0;
 while ( (t.vertex(0) != vertex(j)) && (j < 3) ) j++;
 if ( j == 3)
 {
    return false;
 }
 if ( (t.vertex(1) == vertex(j+1)) && (t.vertex(2) == vertex(j+2)) )
 {
    return true;
 }
 return false;
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::operator!=(const CGAL_TriangleH2<FT,RT>& t) const
{
 CGAL_kernel_precondition( is_defined() && t.is_defined() );
 return !(*this == t);
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::identical(const CGAL_TriangleH2<FT,RT>& t) const
{
 CGAL_kernel_precondition( is_defined() && t.is_defined() );
 return (PTR == t.PTR) ;
}
 


#endif // CGAL_TRIANGLEH2_H
