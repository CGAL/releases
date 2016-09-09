#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/leda_rational.h>

#include <iostream.h>
#include <fstream.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "read_inp.h"
#include "inter.h"


typedef PM_input< CGAL_Cartesian<double> > pminpD;
typedef pminpD::Point pntD;

typedef PM_input< CGAL_Cartesian<leda_rational> > pminpR;
typedef pminpR::Point pntR;

void print_help()
{
	cout << "Utilities program for CGAL Planar Map package" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "The program handles input files for the Planar Map" << endl;
	cout << "example program dctest." << endl;
	cout << "The Input file should be at the following format:" << endl;
	cout << "       <n = number of points>" << endl;
	cout << "       <x1> <y1> " << endl;
	cout << "       ..." << endl;
	cout << "       <xn> <yn>" << endl;
	cout << "       <k = number of curves>" << endl;
	cout << "       <s1> <t1>" << endl;
	cout << "       ..." << endl;
	cout << "       <sk> <tk>" << endl;
	cout << "       Where xi, yi are the coordinates of point i (for " << endl;
	cout << "       rational version in rational format), and si, ti " << endl;
	cout << "       are the indeces (in the the above list of points) " << endl;
	cout << "       of the source and the target of curve i." << endl;
	cout << "" << endl;
	cout << "Usages:" << endl;
	cout << "* The first parameter is always 'e' or 'f' indicates that " << endl;
	cout << "  the input file is:" << endl;
	cout << "  'e' --- exact calculations (leda_rationals)." << endl;
	cout << "  'f' --- floating point (double)." << endl;
	cout << "" << endl;
	cout << "1. Intersect Line Segments:" << endl;
	cout << "   ****  helputil <e/f> i <input_file> <output_file>" << endl;
	cout << "       		" << endl;
	cout << "2. Convert rationals file to doubles file (and vice versa)" << endl;
	cout << "   ****  helputil <e/f> c <input_file> <output_file>" << endl;
	cout << "" << endl;
	cout << "3. Create random (not intersected) file with <num> segments" << endl;
	cout << "   ****  helputil <e/f> r <num> <output_file>" << endl;

	cin.get();
	exit(1);
}

void convert(const pminpR &i1, pminpD &i2)
// convert from rationals to doubles
{
	i2.alloc(i1.get_num_pnts(), i1.get_num_cvs());
	pntD pD;
	pntR pR;
	int i,k, j;

        
	for(i = 0; i < i1.get_num_pnts(); i++)
	{
		i1.get(i, pR);
		pD = pntD(CGAL_to_double(pR.x()), CGAL_to_double(pR.y()));
		i2.set(i, pD);
	}

	for(i = 0; i < i1.get_num_cvs(); i++)
	{
		i1.get(i, k, j);
		i2.set(i, k, j);
	}
}

void convert(const pminpD &i1, pminpR &i2)
// convert from rationals to doubles
{
	i2.alloc(i1.get_num_pnts(), i1.get_num_cvs());
	pntD pD;
	pntR pR;
	int i,k, j;

	for(i = 0; i < i1.get_num_pnts(); i++)
	{
		i1.get(i, pD);
		pR = pntR(leda_rational(pD.x()), leda_rational(pD.y()));
		i2.set(i, pR);
	}

	for(i = 0; i < i1.get_num_cvs(); i++)
	{
		i1.get(i, k, j);
		i2.set(i, k, j);
	}
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

	Lines<double>::pmcurve *cvs = new Lines<double>::pmcurve[nc];
	Lines<double>::pmpoint *pnts = new Lines<double>::pmpoint[np];
	
	Lines<double>::pmcurve *intr_cvs;
	Lines<double>::pmpoint *intr_pnts;

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

void intersect(const pminpR &in, pminpR &out)
{
	pntR p;
	int k, j;
	Lines<leda_rational> l(0);
	int nc, np;
	int intr_nc, intr_np;

	nc = in.get_num_cvs();
	np = in.get_num_pnts();

	Lines<leda_rational>::pmcurve *cvs = new Lines<leda_rational>::pmcurve[nc];
	Lines<leda_rational>::pmpoint *pnts = new Lines<leda_rational>::pmpoint[np];
	
	Lines<leda_rational>::pmcurve *intr_cvs;
	Lines<leda_rational>::pmpoint *intr_pnts;

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
		p = pntR(intr_pnts[i].x, intr_pnts[i].y);
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

void random(int num, pminpR &out, int max = 200)
{
	srand( (unsigned)time( NULL ) );
	out.alloc(num*2, num);
	pntR p;

        int i;
	for (i =0; i < num*2; i++)
	{
		p = pntR(leda_rational(rand() % max), 
			     leda_rational(rand() % max));
		out.set(i, p);
	}

	for (i =0; i < num; i++)
	{
		out.set(i, i*2, i*2+1);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
		print_help();

	bool use_rational;

	switch (argv[1][0])
	{
	case 'e':
		use_rational = true;
		break;
	case 'f':
		use_rational = false;
		break;
	default:
		print_help();
	};


	switch (argv[2][0])
	{
	case 'r': // generate random file argv[4] with argv[3] curves
		if (argc < 5)
			print_help();

		if (use_rational)
		{
			cout << "Create random file using rationals with " << atoi(argv[3]) 
				 << "segments" << endl;
			cout << "Attention: the segments are not intersected" << endl;
			pminpR rnd;
			random(atoi(argv[3]), rnd);
			ofstream f(argv[4]);
			f << rnd;
			f.close();
		}
		else
		{
			cout << "Create random file using doubles with " << atoi(argv[3]) 
				 << " segments" << endl;
			cout << "Attention: the segments are not intersected" << endl;
			pminpD rnd;
			random(atoi(argv[3]), rnd);
			ofstream f(argv[4]);
			f << rnd;
			f.close();
		}
		break;

	case 'i': // intersect argv[3] to argv[4]
		if (argc < 5)
			print_help();
		cout << "Intersect the segments in " << argv[3] 
			 << " and write the intersected segments in " << argv[4] << endl;

		if (use_rational)
		{
			pminpR inpR1;
			pminpR inpR2;
			
			ifstream in(argv[3]);
			in >> inpR1;
			in.close();
			
			intersect(inpR1, inpR2);

			ofstream out(argv[4]);
			out << inpR2;
			out.close();
		}
		else
		{
			pminpD inpD1;
			pminpD inpD2;
			
			ifstream in(argv[3]);
			in >> inpD1;
			in.close();
			
			intersect(inpD1, inpD2);

			ofstream out(argv[4]);
			out << inpD2;
			out.close();
		}
		break;

	case 'c': // convert argv[3] to argv[4] switching from rationals to doubles
		if (argc < 5)
			print_help();

		cout << "Convert the numbers in " << argv[3] 
			 << " and write the new file " << argv[4] << endl;

		if (use_rational)
		{
			pminpR inpR;
			pminpD inpD;
			
			ifstream in(argv[3]);
			in >> inpR;
			in.close();
			
			convert(inpR, inpD);

			ofstream out(argv[4]);
			out << inpD;
			out.close();
		}
		else
		{
			pminpR inpR;
			pminpD inpD;
			
			ifstream in(argv[3]);
			in >> inpD;
			in.close();
			
			convert(inpD, inpR);

			ofstream out(argv[4]);
			out << inpR;
			out.close();
		}

		break;

	default:
		print_help();
		break;
	};
	

	return 0;
}

















