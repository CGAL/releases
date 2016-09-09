/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 * tester.h -
 *    A few generic procuedres used in the testing of the programs...  
 \*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef  __TESTER__H
#define  __TESTER__H 


template <class II> 
void  print_list( const II &begin, const II &end)
{
    flush( cout );

    for (II i = begin; i !=end; i++)
        cout << *i << endl;

    flush( cout ); 
}

template  <int  DIM>
class   rt_kd_tester
{
    //  enum    { SIDE = 10.0 };
#define  SIDE  10.0

public:
    typedef Point_float_d<DIM>  point;
    typedef CGAL_Kdtree_interface<point>  kd_interface;
    typedef CGAL_Kdtree_d<kd_interface>  kd_tree_d;
    
    typedef typename kd_tree_d::ExtPoint  Extended_point;
    typedef typename kd_tree_d::Box  box;
    typedef list<box>    box_list;
    typedef list<point>  points_list; 
    typedef list<point *>  points_ptr_list;
  
    friend void random_points( int  num, points_list &l, int dim,
                               bool  f_degenerate = false )
    {
        point p;
        double  val;
      
        for  (int j = 0;  j < num; j++)
            {
                for  (int i = 0; i < dim; i++) {
                    val = dblRand() * SIDE;
                    if  ( f_degenerate )
                        val = (int)val;
        
                    p.set_coord(i, val );
                }

                l.push_front(p);
            }
    }
      

    friend void random_boxes( int  num, box_list  & l,
                              bool  f_degenerate = false )
    {
        point p, q;
        double  left, right, x1, x2;
    
        for  (int j = 0;  j < num; j++)
            {
                for  (int i = 0; i < DIM; i++) {
                    x1 = dblRand() * SIDE;
                    x2 = dblRand() * SIDE;
          
                    if  ( f_degenerate ) {
                        x1 = (int)x1;
                        x2 = (int)x2;
                    }
          
                    left = min( x1, x2 );
                    right = max( x1, x2 );

                    p.set_coord( i, left );
                    q.set_coord( i, right );
                }

                l.push_front( box( p, q, DIM ) );
            }
    }

    friend void   advance_to_next( int    * a, int limit )
    {
        int  pos;

        pos = 0;
        while  ( pos < DIM ) {
            ++a[ pos ];
            if  ( a[ pos ] < limit ) 
                return;
            a[ pos ] = 0;
            pos++;
        }

        assert( false );  /* we should not arrive to this point */
    }

    //-------------------------------------------------------------------
    // kd_worst_set 
    //
    //It is easy to verify that the worst possible setting for kd-tree is
    //the case where the points are placed in a grid, and a query is a
    //rectangle between two lines of the grid, from one side of the grid
    //to to the other side.
    //
    // Return: the number of points on each side of the grid.
    //-------------------------------------------------------------------
    friend int   kd_worst_set( int  num, points_list  & l )
    {
        int  side = 1 + (int)(pow( num, 1.0/DIM ));
        int  point_d[ DIM ];
        point p;
        int  ind, count;
 
        count = 0; 
        memset( point_d, 0, sizeof( point_d ) );
        for (;;) 
            {
                for  ( ind = 0; ind < DIM; ind++ )
                    p.set_coord( ind, point_d[ind] + dblRand() / 100 );
        
                l.push_front(p);
                count++;
                if  ( count >= num )
                    break;

                advance_to_next( point_d, side );        
            }
  
        return  side;
    }

    friend point  create_point( const Extended_point   & pnt )
    {
        int  ind, status;
        point  out_pnt;

        for  ( ind = 0; ind < pnt.dimension(); ind++ ) {
            status = pnt.get_coord_status( ind );
            if  ( status == Extended_point::MINUS_INFINITY )
                out_pnt.set_coord( ind, - DOUBLE_INFINITY );
            else
                if  ( status == Extended_point::PLUS_INFINITY )
                    out_pnt.set_coord( ind, DOUBLE_INFINITY );
                else {
                    out_pnt.set_coord( ind, (*pnt.get_coord_point( ind ))[ ind ] );
                }
        }

        return  out_pnt;
    }

    friend void  print_rect( const box  & r )
    {
        flush( cout );
        cout << r.get_left().dimension() << ":";
        flush( cout );
        cout << "[" << create_point( r.get_left() ) << " - " 
             << create_point( r.get_right() ) << "]";
        flush( cout );
    }
  
   
    friend void   random_rect( box  & r, 
                               int  points = 0, 
                               bool  f_empty = false,
                               bool  f_degenerate = false )
    {
        double  x, y;
        double  delta = 0;
    
        if  ( f_empty  &&  ( ! f_degenerate ) )
            delta = (double)SIDE / (double)points;

        point l1, r1;
        for (int i = 0; i < DIM; i++) {
            x = dblRand() * SIDE ;

            if  ( f_degenerate )
                x = (int)x;

            if  ( f_empty ) {
                l1.set_coord(i, (double)x);
                r1.set_coord(i, (double)x + delta );
            } else {
                y = dblRand() * SIDE ;
                if  ( f_degenerate )
                    y = (int)y;

                l1.set_coord(i, (double)min(x,y));
                r1.set_coord(i, (double)max(x,y));
            }
        }
        
        r.set_left( l1 );
        r.set_right( r1 );
        //printf( "a" );
        fflush( stdout );

        //r = box( l1, r1, DIM );
    }

    friend points_list     & list_query( points_list    & l, box    & r,
                                         bool   f_collect = true )
    {
        typename points_list::iterator  curr = l.begin();
        points_list  * p_list = new  points_list();
  
        assert( p_list != NULL );

        while  ( curr != l.end() ) {
            if  ( r.is_in( (*curr) )  &&  f_collect )
                p_list->push_back( (*curr) );
     
            curr++;
        }

        return  *p_list;
    }


    // report all the boxes that intersects r
    friend box_list     & list_query_boxes( box_list    & l, box    & r, 
                                            bool   f_collect = true )
    {
        typename box_list::iterator  curr = l.begin();
        box_list  * p_list = new  box_list();
  
        assert( p_list != NULL );

        while  ( curr != l.end() ) {
            if  ( r.is_intersect( (*curr) )  &&  f_collect )
                p_list->push_back( (*curr) );
     
            curr++;
        }

        return  *p_list;
    }


    // report all the boxes that contains r inside them
    friend box_list     & list_query_enclose_boxes( box_list    & l, 
                                                    const  box    & r, 
                                                    bool   f_collect = true )
    {
        typename box_list::iterator  curr = l.begin();
        box_list  * p_list = new  box_list();
  
        assert( p_list != NULL );

        if  ( r.is_empty_open() ) 
            return  *p_list;

        while  ( curr != l.end() ) {
            if  ( (*curr).is_in( r )  &&  f_collect )
                p_list->push_back( (*curr) );
     
            curr++;
        } 

        return  *p_list;
    }


    friend  bool   is_lists_identical( points_list  & l1,
                                       points_list  & l2 )
    {
        if  ( l1.size() != l2.size() )
            return  false;

        typename points_list::iterator  curr1 = l1.begin();
        typename points_list::iterator  curr2 = l2.begin();

        while  ( curr1 != l1.end() ) {
            if  ( (*curr1).compare_vector( 0, *curr2 ) != 0 ) {
                flush(cout) << "not equal!\n";
                flush(cout) << *curr1 << " != " << *curr2;
                flush( cout );

                return  false;
            }
            curr1++;
            curr2++;
        }

        return  true;
    }
    friend  bool   is_box_lists_identical( box_list  & l1,
                                           box_list  & l2 )
    {
        if  ( l1.size() != l2.size() )
            return  false;

        typename box_list::iterator  curr1 = l1.begin();
        typename box_list::iterator  curr2 = l2.begin();

        while  ( curr1 != l1.end() ) {
            if  ( (*curr1).comp( *curr2 ) != 0 ) { 
                flush(cout) << "not equal!\n";
                flush( cout) << *curr1 << " != " << *curr2;
                flush( cout ); 
                return  false;
            }
            curr1++;
            curr2++;
        }

        return  true;
    }

    friend void  set_grid_query_rect( box    & r, int  ind, int  side )
    {
        point  l1, r1;
        int  d;
   
        for  ( d = 0; d < DIM-1; d++ ) {
            l1.set_coord( d, -1 );
            r1.set_coord( d, side + 1 );
        }
        l1.set_coord( DIM-1, 0.25 + ind );
        r1.set_coord( DIM-1, 0.75 + ind );
    
        r = box( l1, r1, DIM );
    }  

    friend ostream &operator<<(ostream &os, const box & b)
    {
        flush(cout) << "[" 
                    << create_point( b.get_left() ) << " - " 
                    << create_point( b.get_right() ) << "]";
        flush( cout );
        return os;
    }

    friend inline bool operator<(const box & x, 
                                 const box & y) 
    {                                                   
        return  ( x.comp( y ) < 0 );
    } 

    friend double  realize_coord( const Extended_point   & pnt, int  coord )
    {
        int  status;

        status = pnt.get_coord_status( coord );
        if  ( status == Extended_point::MINUS_INFINITY )
            return  - DOUBLE_INFINITY;
        else
            if  ( status == Extended_point::PLUS_INFINITY )
                return  DOUBLE_INFINITY;
            else 
                return  (*pnt.get_coord_point( coord ))[ coord ];
    }



};


#else   /* __TESTER__H */
#error  Header file tester.h included twice
#endif  /* __TESTER__H */

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 *     
 * tester.h - End of File
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
