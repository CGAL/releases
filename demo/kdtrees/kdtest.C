/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 * kdtest.C -
 *    Test the CGAL KD-tree module.
 *
 * Written by Sariel Har-Peled
 *------------------------------------------------------------------------
 *    The following works in various dimensions.  To compile it,
 * use -D_DIM=2,3,4,5,... to specify what dimension to use. 
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
 
//#ifdef  __GNUG__ 
//#include  <typeinfo>
//#endif  /* __GNUG__ */ 

#include  <iostream.h>
#include  <fstream.h>
#include  <iomanip.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/timeb.h>
#include  <time.h>
#include  <unistd.h>
#include  <assert.h>

#include  <CGAL/Cartesian.h>
#include  <CGAL/Point_2.h>
#include  <CGAL/Iso_rectangle_2.h>

//#define _BOOL
//#define _G_HAVE_BOOL 1
//#undef __NEED_BOOL

//#define _BOOL
// stl
#include  <vector.h>
//#include  <bool.h>
#include  <tempbuf.h>
#include  <list.h>
#include  <iterator.h> 

//#define  __BUILTIN_BOOL__
//#define  LEDA_COMPARE_TEMPLATE


#include  <LEDA/window.h>
#include  <CGAL/IO/Window_stream.h>

#include  "mygeneric.h"   


//#include  <LEDA/UNDEFINE_NAMES.h>

#include  <CGAL/kdtree_d.h>

#include  "point_float_d.h"
#include  "tester.h"

// windowing system...
#include  <CGAL/Cartesian.h>
#include  <CGAL/Point_2.h>
#include  <CGAL/Iso_rectangle_2.h>
//#include  <CGAL/IO/Window_stream.h>

/*=========================================================================
 * Start of Code
\*=========================================================================*/
#define  DIM  _DIM
 
typedef rt_kd_tester<DIM>   cTester; 
#ifndef  __GNUG__
cTester   CC_create_code;
#endif

//typedef Point_float_d_hidden<DIM>  point;
typedef Point_float_d<DIM>  point;
typedef CGAL_Kdtree_interface<point>  kd_interface;
typedef CGAL_Kdtree_d<kd_interface>  kd_tree;
typedef kd_tree::Box  box;
typedef list<point>  points_list; 
typedef list<point *>  points_ptr_list;

/* the windowing class */
 
#include  "window_d.h"


/*=========================================================================
 * Static variable
\*=========================================================================*/
static Window_d      * p_window = NULL;
static bool            f_window = true;
static int             tests, empty_tests, correctness_tests;
 

/*=========================================================================
 * Start of Code
\*=========================================================================*/

static void   window_start()
{
    if  ( ! f_window )
        return;

    p_window = new  Window_d( DIM, 600, 600, 600 );
    assert( p_window != NULL );    
}


static void   window_term()
{
    if  ( ! f_window )
        return;

    delete  p_window;
    p_window = NULL;
}


static void   window_draw_list( list<point>   & lst,
                                bool   f_mark )
{
    if  ( ! f_window )
        return;

    if (f_mark )
        *p_window << CGAL_BLUE;
    else
         *p_window << CGAL_RED;
    for ( list<point>::iterator j = lst.begin(); 
          j != lst.end(); 
          j++ ) 
    {
         *p_window << (*j);
    }
}

static void   window_draw_hit_list( list<point>   & lst,
                                    box           & r,
                                    bool   f_mark )
{
    if  ( ! f_window )
        return;

    //print_rect( r );
    //cout << "\n";
    if  ( f_mark )
         *p_window << CGAL_BLUE;
    else
         *p_window << CGAL_WHITE;

    *p_window << r;

    window_draw_list( lst, f_mark );

    // delete rectangle
     p_window->flush();
}


static void   window_start_draw( list<point>   & lst )
{
    if  ( ! f_window )
        return;

    p_window->clear();
    p_window->Lines();
    window_draw_list( lst, false );
}


static void  test_kd_worst( int  points ) 
{
    int  ind, side, counter, total;
    Timer  tm, tmQuery, tmQuery_l;
    CGAL_Kdtree_d<kd_interface>  tree(DIM);
    box  r( DIM );
    points_list  l;

    total = 0;

    side = kd_worst_set( points, l );

    tm.start();
    tree.build( l );
    tm.end();
    if  ( ! tree.is_valid() )
        tree.dump();
    assert( tree.is_valid() );

    tmQuery.start();
    ind = 0;
    for  ( counter = 0; counter < tests; counter++ )
        {
            points_list  res;
                 
            set_grid_query_rect( r, ind, side );

            tree.search( back_inserter( res ), r );
            ind++;
            if  ( ind >= side )
                ind = 0;
               
            if ( res.size() != 0 ) {
                print_list( res.begin(), res.end() );
                assert( false );
            }
            
            total += res.size();
        }
    tmQuery.end();

    printf( "%9.3f |", tmQuery.seconds() );
    fflush( stdout );
 
    // kd_worst_query test for a list
    tmQuery_l.start();
    ind = 0;
    for  ( counter = 0; counter < tests; counter++ )
        {
            points_list  * res1;

            set_grid_query_rect( r, ind, side );
            
            res1 = &list_query( l, r );

            if ( res1->size() != 0 ) {
                print_list( res1->begin(), res1->end() );
                assert( false );
            }
            delete  res1;

            ind++;
            if  ( ind >= side )
                ind = 0;
        }
    tmQuery_l.end();

    printf( "%9.3f |", tmQuery_l.seconds() );
    fflush( stdout );
       
    tree.delete_all();

    assert( total == 0 );

    printf( "\n" );
}


static void  regular_test( int  points ) 
{
    int  ind;
    Timer  tm, tmQuery, tmQueryEmpty, tmQuery_l, tmQueryEmpty_l;
    CGAL_Kdtree_d<kd_interface>  tree(DIM);
    box  r( DIM );
    points_list  l;
    int  count;

    printf( "| %7d | ", points );
    fflush( stdout );

    random_points( points, l, DIM);

    window_start_draw( l );

    tm.start();
    tree.build( l );
    tm.end();
    if  ( ! tree.is_valid() )
        tree.dump();
    assert( tree.is_valid() );

    printf( "%9.3f |", (float)tm.seconds() );
    fflush( stdout );

    // Brute force query speed test...
    count = 0;
    tmQuery.start();
    for  ( ind = 0; ind < tests; ind++ ) 
        {
            points_list  res;

            random_rect(r, DIM);
            
            tree.search( back_inserter( res ), r );
            
            if  ( f_window ) {            
                window_draw_hit_list( res, r, true );
                //sleep( 1 );
                window_draw_hit_list( res, r, false );
            }

            count += res.size();
        }
    tmQuery.end();
    printf( "%9.3f |", tmQuery.seconds() );
    //printf( "%9d |", count );

    // Brute force query speed test for a list...
    tmQuery_l.start();
    for  ( ind = 0; ind < tests; ind++ ) 
        {
            points_list  res;

            random_rect(r, DIM);

            delete  (&list_query( l, r ));
 
            tree.search( back_inserter( res ), r );
        }
    tmQuery_l.end();
    printf( "%9.3f |", tmQuery_l.seconds() );
    fflush( stdout );

    // Brute force almost empty query speed test...
    tmQueryEmpty.start();
    for  ( ind = 0; ind < empty_tests; ind++ ) 
        {
            points_list  res;

            // get a very small random rectangle
            random_rect( r, points, true );

            tree.search( back_inserter( res ), r );
        }
    tmQueryEmpty.end();

    printf( "%9.3f |", tmQueryEmpty.seconds() );
    fflush( stdout );

    // Brute force almost empty query speed test for list...
    tmQueryEmpty_l.start();
    for  ( ind = 0; ind < empty_tests; ind++ ) 
        {
            points_list  res;

            // get a very small random rectangle
            random_rect( r, points, true );
            delete  (&list_query( l, r ));
        }
    tmQueryEmpty_l.end();

    printf( "%9.3f |", tmQueryEmpty_l.seconds() );
    fflush( stdout );

    for  ( ind = 0; ind <  correctness_tests; ind++ ) 
        {
            points_list  res, * res1;
 
            random_rect(r, DIM);

            tree.search( back_inserter( res ), r );
            res.sort();

            res1 = &list_query( l, r );
            res1->sort();

            if  ( ! is_lists_identical( res, *res1 ) ) {
                print_rect( r );
                cout << "\n";

                cout << "ERROR: results are not identical!\n";
                cout << "Res: " << "(" << res.size() << ")\n";
                print_list( res.begin(), res.end() );
                cout << "Res1:"  << "(" << res1->size() << ")\n";
                print_list( res1->begin(), res1->end() );
                   
                cout << "tree:\n";
                tree.dump();
                exit( -1 );
            } 

            delete  res1;
        }

    tree.delete_all();
}


int   main( int   argc, char   ** argv )
{
    int  points, ind;

    points = 2; //1<<20; //2;
    
    printf( "KD-tree test. %d dimensions\n", DIM );
    printf( "---------------------------\n" );

    for  ( ind = 1; ind < argc; ind++ ) {
        if  ( strcmp( argv[ ind ], "-t" ) == 0 ) {
            f_window = false;
            continue;
        }
        if  ( strcmp( argv[ ind ], "-n" ) == 0 ) {
            assert( (ind + 1) < argc );
            points = atoi( argv[ ind + 1 ] );
            ind++;
            continue;
        }

        printf( "%s [-t] [-n points_num]\n", argv[ 0 ] );
        printf( "\t -t - text mode. No fancy windows\n" );
        printf( "\t -n points_num  - number of points to use\n" );
        exit( -1 );
    }

    srand( (unsigned)time(NULL) );

    window_start();
    
    printf( "This program picks randomly points inside a cube in %d"
            " dimensions,\nand construct their KD-tree. It also"
            " performs a sequence of\nrandom rectangular queries, and"
            " verifies the correctness of the results.\n\n", DIM );

    printf( "All entries titled by \"List\" were"
            " performed naively using a list instead of KD tree\n" ); 

    tests = 10;
    empty_tests = 10;
    correctness_tests = 10;

    printf( "Rand Rect Query - chooses a rectangle randomally and query\n"
            "\tfor all the points inside the rectangle.\n" );
    printf( "Rand ERect Query - chooses a small (probably empty) rectangle\n"
            "\trandomally and query for all the points inside the rectangle\n" );

  
    printf( "\nFor each entry in the table - tests performed:\n" );
    printf( "\tRand Rect Query   : %d\n", tests );
    printf( "\tRand ERect Query  : %d\n", empty_tests );
    printf( "\tRand Correctness  : %d\n", correctness_tests );
  
    printf( "\n" );

    printf( "Rand Rect Query - chooses a rectangle randomally and query\n" );
    printf( "Each entry is table is the overall running time in seconds.\n" );

    //  printf( "RandERect
    printf( "\n" );

    printf( "+---------+-----------+----------+----------+----------+----------+----------+----------+\n" );
    printf( "|         |           | Rand     | List-Rand| Rand     | List-Rand| KD       | List-KD  |\n" );
    printf( "|         |Construct' | Rect     | Rect     | ERect    | ERect    | worst    | worst    |\n" ); 
    printf( "| Points  | Time      | Query    | Query    | Query    | Query    | EQuery   | EQuery   |\n" );
    printf( "+---------+-----------+----------+----------+----------+----------+----------+----------+\n" );

    assert( points >= 2 );
 
    for  ( ind = 1; ind < 20; ind++ ) {
        regular_test( points );
        test_kd_worst( points );
        fflush( stdout );

        points <<= 1;
    }

    printf( "+---------+-----------+----------+----------+----------+\n" );

    window_term();

    return  0;
}

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 *     
 * kdtest.C - End of File
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
