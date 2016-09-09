 


#ifndef CGAL_RAYH2_H
#define CGAL_RAYH2_H

 



template < class FT, class RT >
class CGAL__Ray_repH2 : public handle_rep
{
public:
                        CGAL__Ray_repH2();
                        CGAL__Ray_repH2(const CGAL_PointH2<FT,RT>& fp,
                                        const CGAL_PointH2<FT,RT>& sp);
                        ~CGAL__Ray_repH2(){}

    CGAL_PointH2<FT,RT>  start;
    CGAL_PointH2<FT,RT>  second;
};
 

 



template < class FT, class RT >
class CGAL_RayH2 : public handle_base
{
public:
            CGAL_RayH2();
            CGAL_RayH2( const CGAL_RayH2& r);
            CGAL_RayH2( const CGAL_PointH2<FT,RT>& sp,
                        const CGAL_PointH2<FT,RT>& secondp);
            CGAL_RayH2( const CGAL_PointH2<FT,RT>& sp,
                        const CGAL_DirectionH2<FT,RT>& d);
            ~CGAL_RayH2();

    CGAL_RayH2<FT,RT>&
            operator=(const CGAL_RayH2<FT,RT>& r);

    bool    operator==(const CGAL_RayH2& r) const;
    bool    operator!=(const CGAL_RayH2& r) const;
    bool    identical( const CGAL_RayH2& r) const;

    CGAL_PointH2<FT,RT>     start() const;
    CGAL_PointH2<FT,RT>     second_point() const;
    CGAL_DirectionH2<FT,RT> direction() const;
    CGAL_LineH2<FT,RT>      supporting_line() const;
    CGAL_RayH2              opposite() const;

    bool    is_horizontal() const;
    bool    is_vertical() const;
    bool    is_on(const CGAL_PointH2<FT,RT> p) const;
    bool    collinear_is_on(const CGAL_PointH2<FT,RT> p) const;
    bool    is_degenerate() const;

#ifdef CGAL_CHECK_PRECONDITIONS
    bool    is_defined() const
            {
              return !(PTR == NULL);
            }
#endif // CGAL_CHECK_PRECONDITIONS

    CGAL_RayH2<FT,RT>
            transform( const CGAL_Aff_transformationH2<FT,RT> & t) const;
protected:

    CGAL__Ray_repH2<FT,RT>*
            ptr() const;
};
 

 


template < class FT, class RT >
CGAL__Ray_repH2<FT,RT>::CGAL__Ray_repH2()
{
}


template < class FT, class RT >
CGAL__Ray_repH2<FT,RT>::CGAL__Ray_repH2(const CGAL_PointH2<FT,RT>& fp,
                                        const CGAL_PointH2<FT,RT>& sp) :
  start(fp), second(sp)
{
}
 

 



template < class FT, class RT >
CGAL_RayH2<FT,RT>::CGAL_RayH2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
 PTR = new CGAL__Ray_repH2<FT,RT>;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT, class RT >
CGAL_RayH2<FT,RT>::CGAL_RayH2(const CGAL_RayH2<FT,RT>& r) :
  handle_base(r)
{
 CGAL_kernel_precondition( r.is_defined() );
}

template < class FT, class RT >
CGAL_RayH2<FT,RT>::CGAL_RayH2( const CGAL_PointH2<FT,RT>& sp,
                               const CGAL_PointH2<FT,RT>& secondp)
{
 CGAL_kernel_precondition( sp.is_defined() && secondp.is_defined() );
 PTR = new CGAL__Ray_repH2<FT,RT>(sp,secondp);
 CGAL_nondegeneracy_assertion;
}

template < class FT, class RT >
CGAL_RayH2<FT,RT>::CGAL_RayH2( const CGAL_PointH2<FT,RT>& sp,
                               const CGAL_DirectionH2<FT,RT>& d)
{
 CGAL_kernel_precondition( sp.is_defined() && d.is_defined() );
 PTR = new CGAL__Ray_repH2<FT,RT>(sp, sp + d.vector());
 CGAL_nondegeneracy_assertion;
}

template < class FT, class RT >
CGAL_RayH2<FT,RT>::~CGAL_RayH2()
{
}

template < class FT, class RT >
CGAL_RayH2<FT,RT>&
CGAL_RayH2<FT,RT>::operator=(const CGAL_RayH2<FT,RT>& r)
{
 CGAL_kernel_precondition( r.is_defined() );
 handle_base::operator=(r);
 return *this;
}
 
template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_RayH2<FT,RT>::start() const
{
 CGAL_kernel_precondition( is_defined() );
 return ptr()->start;
}


template < class FT, class RT >
CGAL_DirectionH2<FT,RT>
CGAL_RayH2<FT,RT>::direction() const
{
 CGAL_kernel_precondition( is_defined() );
 CGAL_nondegeneracy_precondition( !is_degenerate() );
 return CGAL_DirectionH2<FT,RT>( ptr()->second - ptr()->start );
}
 
template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_RayH2<FT,RT>::second_point() const
{
 CGAL_kernel_precondition( is_defined() );
 CGAL_nondegeneracy_precondition( !is_degenerate() );
 return ptr()->second;
}

template < class FT, class RT >
CGAL_LineH2<FT,RT>
CGAL_RayH2<FT,RT>::supporting_line() const
{
 CGAL_kernel_precondition( is_defined() );
 CGAL_nondegeneracy_precondition( !is_degenerate() );
 return CGAL_LineH2<FT,RT>(*this);
}

template < class FT, class RT >
CGAL_RayH2<FT,RT>
CGAL_RayH2<FT,RT>::opposite() const
{
 CGAL_kernel_precondition( is_defined() );
 return CGAL_RayH2<FT,RT>( ptr()->start, - direction() );
}

template < class FT, class RT >
CGAL_RayH2<FT,RT>
CGAL_RayH2<FT,RT>::transform(
                       const CGAL_Aff_transformationH2<FT,RT> & t) const
{
 CGAL_kernel_precondition( is_defined() && t.is_defined() );
 return CGAL_RayH2<FT,RT>(t.transform(ptr()->start),
                          t.transform(ptr()->second) );
}
 


template < class FT, class RT >
bool
CGAL_RayH2<FT,RT>::is_horizontal() const
{
 CGAL_kernel_precondition( is_defined() );
 return start().hy()*second_point().hw() == second_point().hy()*start().hw();
}

template < class FT, class RT >
bool
CGAL_RayH2<FT,RT>::is_vertical() const
{
 CGAL_kernel_precondition( is_defined() );
 return start().hx()*second_point().hw() == second_point().hx()*start().hw();
}

template < class FT, class RT >
bool
CGAL_RayH2<FT,RT>::is_on(const CGAL_PointH2<FT,RT> p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 return ( (  p == start() )
        ||(CGAL_DirectionH2<FT,RT>(p - ptr()->start) == direction() ) );
}

template < class FT, class RT >
bool
CGAL_RayH2<FT,RT>::is_degenerate() const
{
 CGAL_kernel_precondition( is_defined() );
 return ( (ptr()->start == ptr()->second) );
}

template < class FT, class RT >
bool
CGAL_RayH2<FT,RT>::collinear_is_on(const CGAL_PointH2<FT,RT> p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 return is_on(p);
}
 

template < class FT, class RT >
bool
CGAL_RayH2<FT,RT>::operator==(const CGAL_RayH2<FT,RT>& r) const
{
 CGAL_kernel_precondition( is_defined() && r.is_defined() );
 return ( (start() == r.start() )&&( direction() == r.direction() ) );
}

template < class FT, class RT >
bool
CGAL_RayH2<FT,RT>::operator!=( const CGAL_RayH2<FT,RT>& r) const
{
 return !(*this == r);
}


template < class FT, class RT >
bool
CGAL_RayH2<FT,RT>::identical( const CGAL_RayH2<FT,RT>& r) const
{
 CGAL_kernel_precondition( is_defined() && r.is_defined() );
 return ( PTR == r.PTR );
}
 


template < class FT, class RT >
inline
CGAL__Ray_repH2<FT,RT>*
CGAL_RayH2<FT,RT>::ptr() const
{
 return (CGAL__Ray_repH2<FT,RT>*)PTR;
}
 


#endif // CGAL_RAYH2_H
