/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 * window_d.h -
 *     Display $d$ dimensional space. Stolen from a code written by
 * Eyal Flato. 
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef  __WINDOW_D__H
#define  __WINDOW_D__H


#define PROJ_SPACE  8

// preset projection of object in a d-dimensional box on each parallel plane
// the box edges are all equal and its center is on the origin
class Window_d : public CGAL_Window_stream
{
public:
    typedef double T;
    typedef CGAL_Point_2< CGAL_Cartesian<double> > _CGALIO_Point;
    typedef CGAL_Segment_2< CGAL_Cartesian<double> > _CGALIO_Line;
    typedef CGAL_Iso_rectangle_2< CGAL_Cartesian<double> > _CGALIO_Rect;

	
    Window_d(int dim, double size, int width, int height) :
        CGAL_Window_stream(width, height)
    {
        Space = PROJ_SPACE;
        Size = 1;
        Dim = dim;
        Size = size; 
        Size = 1.0;
        Width = width;
        Height = height;
        // window is initialized to be 1 unit per pixel
        // another internal initialization will be done in Init
        init(0, Width, 0); 

        if  ( Dim == 2 ) 
        {
            ProjWidth = (Width - 2 * Space);
            ProjHeight = (Height - 2 * Space);
        }
        else 
        {
            ProjWidth = (Width - (Dim + 1)*Space) / Dim;
            ProjHeight = (Height - (Dim + 1)*Space) / Dim;
        }
    }

	
    void Lines()
    {
        // draw lines
        int i, j;
        double x1, y1, x2, y2;
		
        (*this) << CGAL_BLACK;
        for (i = 0; i < Dim; i++)
        {
            for (j = 0; j < Dim; j++)
            {
                GetCenter(i, j, x1, y1);
                x1 = x1 - ProjWidth/2;
                y1 = y1 - ProjHeight/2;
                x2 = x1 + ProjWidth;
                y2 = y1 + ProjHeight;
                (*this) << _CGALIO_Rect( _CGALIO_Point(x1, y1), 
                                         _CGALIO_Point(x2, y2));
            }
        }
	
    };
	
    // get the center of the coord1-coord2 projection rect 
    // (the projection of (0,0, ... , 0) on this plane)
    void GetCenter(int coord1, int coord2, double &x, double &y)
    {
        coord2 = Dim - 1 - coord2;
        x = Space + coord1 * (ProjWidth + Space) + ProjWidth / 2;
        y = Space + coord2 * (ProjHeight + Space) + ProjHeight / 2;
    };
	
    // return the projection of the point on coord1-coord2 plane
    // in x1 and x2.
    // return nonzero when error
    int ProjectPoint(point &p, int coord1, int coord2, 
                     double &x, double &y)
    {
        if  ( Dim == 2 ) {
            coord1 = 0;
            coord2 = 1;
        }
        double  x1 = p[ coord1 ];
        double  x2 = p[ coord2 ];
        
        x1 = (x1 - 5.0) / 10.0;
        x2 = -(x2 - 5.0) / 10.0;

        if ((fabs(x1) >= Size/2) || (fabs(x2) >= Size/2))
        {
            x1 = x2 = 0;
            return 1;
        }
		
        double x0, y0;
        if  ( Dim == 2 ) 
            GetCenter( 0, 1, x0, y0 );
        else
            GetCenter( coord1, coord2, x0, y0 );

        //printf( "dim: %d, center: %g %g\n", Dim, x0, y0 );

        x = x1 * ProjWidth / Size + x0;
        y = x2 * ProjHeight / Size + y0;
		
        return 0;
    };
	
    friend Window_d &operator<<(Window_d &w, point &p)
    {
        double x, y;
        int i, j;
		
        for (i = 0; i < w.GetDim(); i++)
        {
            for (j = 0; j < w.GetDim(); j++)
            {
                if (w.ProjectPoint(p, i, j, x, y) == 0)
                    //printf( "%g %g\n", x, y );
                    w << _CGALIO_Point(x, y);
            }
        }
		
        return w;	
    };

    friend Window_d &operator<<(Window_d &w, box &r)
    {
        double x1, y1, x2, y2;
        int i, j;
        point mn, mx;

        mn = create_point( r.get_left() );
        mx = create_point( r.get_right() );
		
        for (i = 0; i < w.GetDim(); i++)
        {
            for (j = 0; j < w.GetDim(); j++)
            {
                if ((w.ProjectPoint(mn, i, j, x1, y1) == 0) &&
                    (w.ProjectPoint(mx, i, j, x2, y2) == 0) )
                {
                    w << _CGALIO_Rect(_CGALIO_Point(x1, y1),
                                      _CGALIO_Point(x2, y2));
                }
            }
        }
		
        return w;	
    };
	
    int GetDim() { return Dim; };

protected:
    int Width, Height;
    int Dim;
    T Size;
    int Space; // space between proj-windows
    int ProjWidth, ProjHeight; // size of each projection window
};


#else   /* __WINDOW_D__H */
#error  Header file Window_d.h included twice
#endif  /* __WINDOW_D__H */

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 *     
 * window_d.h - End of File
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
