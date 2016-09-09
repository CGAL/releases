#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
//#include <CGAL/Double.h>
#include <iostream.h>
#include <fstream.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "read_inp.h"
#include "inter.h"


typedef PM_input< CGAL_Cartesian<double> > pminpD;
typedef typename pminpD::Point pntD;

void print_help()
{
	/*
	Utilities program for CGAL Planar Map package demo
	--------------------------------------------------
	The program handles input files for the Planar Map
        demo program .
	The Input file should be at the following format:
			<n = number of points>
			<x1> <y1> 
			...
			<xn> <yn>
			<k = number of curves>
			<s1> <t1>
			...
			<sk> <tk>
		    Where xi, yi are the coordinates of point i  and si, ti 
			are the indices (in the the above list of points) 
			of the source and the target of curve i. The number
                        type assumed is double (this is the number type the 
                        demo program works with).

	Usages:

	1. Intersect Line Segments:
	   ****  helputil  i <input_file> <output_file>

	2. Create random (not intersected) file with <num> segments
	   ****  helputil  r <num> <output_file>

  */

	cout << "Utilities program for CGAL Planar Map package demo" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "The program handles input files for the Planar Map" << endl;
	cout << "demo program ." << endl;
	cout << "The Input file should be at the following format:" << endl;
	cout << "       <n = number of points>" << endl;
	cout << "       <x1> <y1> " << endl;
	cout << "       ..." << endl;
	cout << "       <xn> <yn>" << endl;
	cout << "       <k = number of curves>" << endl;
	cout << "       <s1> <t1>" << endl;
	cout << "       ..." << endl;
	cout << "       <sk> <tk>" << endl;
	cout << "       Where xi, yi are the coordinates of point i and si,ti" << endl;
	cout << "       are the indices (in the the above list of points) " << endl;
	cout << "       of the source and the target of curve i." << endl;
	cout << "" << endl;
	cout << "Usages:" << endl;
	cout << "" << endl;
	cout << "1. Intersect Line Segments:" << endl;
	cout << "   ****  helputil  i <input_file> <output_file>" << endl;
	cout << "       		" << endl;
	cout << "" << endl;
	cout << "2. Create random (not intersected) file with <num> segments" << endl;
	cout << "   ****  helputil  r <num> <output_file>" << endl;

	cin.get();
	exit(1);
}


void intersect(const pminpD &in, pminpD &out)
{
	pntD p;
	int k, j;
	Lines<double> l(1);
	int nc, np;
	int intr_nc, intr_np;

	nc = in.get_num_cvs();
	np = in.get_num_pnts();

	typename Lines<double>::pmcurve *cvs = new Lines<double>::pmcurve[nc];
	typename Lines<double>::pmpoint *pnts = new Lines<double>::pmpoint[np];
	
	typename Lines<double>::pmcurve *intr_cvs;
	typename Lines<double>::pmpoint *intr_pnts;

        int i;
	for(i = 0; i < in.get_num_pnts(); i++)
	{
		in.get(i, p);
		pnts[i].x = p.x();
		pnts[i].y = p.y();
		pnts[i].n = i;
	}

	for(i = 0; i < in.get_num_cvs(); i++)
	{
		in.get(i, k, j);
		cvs[i].s = pnts[k];
		cvs[i].t = pnts[j];
	}

	l.Intersect(pnts, np, cvs, nc, intr_pnts, intr_np, intr_cvs, intr_nc);

	out.alloc(intr_np, intr_nc);

	for(i = 0; i < intr_np; i++)
	{
		p = pntD(intr_pnts[i].x, intr_pnts[i].y);
		out.set(i, p);
	}

	for(i = 0; i < intr_nc; i++)
	{
		out.set(i, intr_cvs[i].s.n, intr_cvs[i].t.n);
	}

	if (cvs != NULL) delete[] cvs;
	if (pnts != NULL) delete[] pnts;
	if (intr_cvs != NULL) delete[] intr_cvs;
	if (intr_pnts != NULL) delete[] intr_pnts;

}



void random(int num, pminpD &out, int max = 200)
{
	srand( (unsigned)time( NULL ) );
	out.alloc(num*2, num);
	pntD p;

        int i;
	for (i =0; i < num*2; i++)
	{
		p = pntD(rand() % max, rand() % max);
		out.set(i, p);
	}

	for (i =0; i < num; i++)
	{
		out.set(i, i*2, i*2+1);
	}
}



int main(int argc, char *argv[])
{
  if (argc < 2)
    print_help();

  
  switch (argv[1][0])
    {
    case 'r': // generate random file argv[3] with argv[2] curves
      if (argc < 4 )
        print_help();
      else
        {
          cout << "Create random file using doubles with " << atoi(argv[2]) 
               << " segments" << endl;
          cout << "Attention: the segments are not intersected" << endl;
          pminpD rnd;
          random(atoi(argv[2]), rnd);
          ofstream f(argv[3]);
          f << rnd;
          f.close();
        }
      break;
          
    case 'i': // intersect argv[2] to argv[3]
      if (argc < 4)
        print_help();
      else
        {
          cout << "Intersect the segments in " << argv[2] 
               << " and write the intersected segments in " << argv[3] << endl;
          pminpD inpD1;
          pminpD inpD2;
          ifstream in(argv[2]);
          in >> inpD1;
          in.close();
          intersect(inpD1, inpD2);
          ofstream out(argv[3]);
          out << inpD2;
          out.close();
        }
      break;

    default:
      print_help();
      break;
    };
  
  
  return 0;
}









