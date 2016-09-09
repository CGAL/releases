// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Triangulations
// Author: Remco Veltkamp
// June 1997
// ---------------------------------------

#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/point_generators_2.h>
#include <iostream.h>

typedef Triangulation_2::Edge_iterator  Edge_iterator;
typedef Triangulation_2::Face  Face;
typedef Triangulation_2::Vertex  Vertex;

void main()
{
    const int numPoints = 50;
    CGAL_Random_points_in_square_2<Point_2> g(100.0);    // random points generator
    Triangulation_2 tr;                                           // empty triangulation 

    // construct a triangulation 
    for (int i=0; i<numPoints; ++i) {
        tr.insert( *g );                                       // take next point from generator
    }

    Edge_iterator it = tr.edges_begin(),            // initialize with begin value
                      beyond = tr.edges_end();         // past the end value

    while (it != beyond) {
       pair<Face*,int> edge = *it;                    // take `edge'
       ++it;                                                // advance iterator

       Face *face = edge.first;                                       // take the face
       int nbIndex = edge.second;
       Face *neighbor = face->neighbor(nbIndex);                 // take neighbor

       Vertex *edgev1 = face->vertex(face->cw(nbIndex));       // edges vertices
       Vertex *edgev2 = face->vertex(face->ccw(nbIndex));

       // two opposite vertices of adjacent face
       Vertex *opposite1 = face->vertex(nbIndex);
       Vertex *opposite2 = neighbor->vertex(neighbor->index(face));

       // smallest circle through edge vertices
       Circle_2 circle(edgev1->point(), edgev2->point());    

       if ( ! tr.is_infinite(opposite1) ) {    // opposite1 infinite?
          if (circle.bounded_side(opposite1->point()) == CGAL_ON_BOUNDED_SIDE) {
             // opposite vertex 1 lies inside circle, continue with next edge
             continue;
          }
       }
       if ( ! tr.is_infinite(opposite2)) {    // opposite2 infinite?
          if (circle.bounded_side(opposite2->point()) == CGAL_ON_BOUNDED_SIDE) {
             // opposite vertex 2 inside circle, continue with next edge
             continue;
          }
       }

       // opposite vertex 1 and 2 not inside circle, output edge as segment
       cout << Segment_2(edgev1->point(), edgev2->point()) << endl;
    }
}


