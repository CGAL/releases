#ifndef _POINT_FLOAT_D_H
#define _POINT_FLOAT_D_H

/****************************  demo  object_d ************************/
#define DOUBLE_INFINITY 999999999999.0

template <int  DIM>
class Point_float_d 
{
private:
    double   vec[ DIM ];
    
public:
    Point_float_d()
    {
        for  ( int ind = 0; ind < DIM; ind++ )
            vec[ ind ] = 0;
    }
	
//iddo    int dimensions()  const
    int dimension() const
    {
        return  DIM;
    }
	
    void set_coord(int k, double x)
    {
        assert( 0 <= k  &&  k < DIM );

        vec[ k ] = x;
    }
	
    double get_coord(int k)  const
    {
        assert( 0 <= k  &&  k < DIM );

        return  vec[ k ];
    }

    double  & operator[](int k)  
    {
        assert( 0 <= k  &&  k < DIM );

        return  vec[ k ];
    }
    double  operator[](int k) const
    {
        assert( 0 <= k  &&  k < DIM );

        return  vec[ k ];
    }
	
    int compare(int k, const Point_float_d &p)  const
    {
        if (get_coord(k) < p.get_coord(k))
            return -1;
        if (get_coord(k) == p.get_coord(k))
            return 0;
        return 1;
    }
	
    int compare_vector( int k, const Point_float_d  & p )  const
    {
        int j, res;
                
        //Sariel: optimized the code a little...
        j = k % DIM;
        for (int i=0; i < DIM; i++)
            {
                res = compare(j, p);
                if (res != 0) return res;
                // if the j-th coord are not equal continue

                j++;
                if  ( j >= DIM )
                    j = 0;
            }
        return 0;
    }
	
	
    void copy(int k, const Point_float_d &src)
    {
        set_coord( k, src.get_coord( k ) );
    }
	
    void assign_infinity(int k, bool plus)  
    {
        if (plus)
            vec[k] = DOUBLE_INFINITY;
        else
            vec[k]  = -1*DOUBLE_INFINITY;
    }
	
    void report(bool f = true)  const;

    friend inline bool operator<(const Point_float_d<DIM>& x, 
                                 const Point_float_d<DIM> & y) 
    {                                                   
        return  ( x.compare_vector( 0, y) < 0 );    
    } 

    friend ostream &operator<<(ostream &os, const Point_float_d<DIM> &p)
    {
        cout << "(";
        for(int i = 0; i < DIM; i++)
            {
                cout << p.get_coord(i);
                //iddo                if (i < p.dimensions() - 1) cout << ", ";
                if (i < p.dimension() - 1) cout << ", ";
            }
        cout << ")";
        return os;
    }
};

/*
template <int  DIM>
class Point_float_d_hidden
{ 
public:
    Point_fload_d<DIM>  pnt;

    Point_float_d_hidden( Point_fload_d<DIM>  & _pnt )
    {
        pnt = _pnt;
    }

    int compare(int k, const Point_float_d_hidden &p)  const
    {
        return  pnt.compare( k, p.pnt );
    }
    
    int dimensions()  const
    {
        return  DIM;
    }
};*/


/* for sorting list of points.... */
/* the ocmpiler on SGI does not support the follwoing:
template <int  DIM>
inline bool operator<(const Point_float_d<DIM>& x, const Point_float_d<DIM> 
& y) 
{
   return  ( x.compare_vector( 0, y) < 0 );
   }
*/
/*
#define  POINT_COMPERATOR(DIM) \
   */

#endif




