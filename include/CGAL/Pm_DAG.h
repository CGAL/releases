// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/Pm_DAG.h
// package       : pm (2.052)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//                 Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
/*
Directed acyclic binary graph template class
*/
#ifndef CGAL_PM_DAG_H
#define CGAL_PM_DAG_H

#ifndef CGAL_PM_CONFIG_H
#include <CGAL/Pm_config.h>
#endif

#include <stdlib.h>
#include <iostream.h>
#include <list.h>
#include <function.h>
#ifndef CGAL_NUMBER_UTILS_H
#include <CGAL/number_utils.h>
#endif
#ifndef CGAL_KERNEL_ASSERTIONS_H
#include <CGAL/kernel_assertions.h>
#endif
#ifndef CGAL_HANDLE_H
#include <CGAL/Handle.h>
#endif

template<class T,class Pred>
class CGAL_DAG;

template<class T>
class CGAL_DAG_handle : public CGAL_Handle
{
public: //iddo (for CC-7.2) maybe protected?
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
protected:
	void init() {PTR=0;}
public:
	CGAL_DAG_handle() {init();}
	CGAL_DAG_handle(const CGAL_DAG_handle<T>& x) : CGAL_Handle(x) {}
	CGAL_DAG_handle& operator=(const CGAL_DAG_handle<T>& x) {CGAL_Handle::operator=(x);return *this;}
	bool operator!() const {return PTR==0;}
};

template<class T,class Pred>
class CGAL_DAG : public CGAL_DAG_handle<T>
{
public:
	typedef CGAL_DAG<T,Pred> DAG;
	typedef CGAL_DAG_handle<T> DAG_handle;
	typedef Pred Predicate;
	typedef list<pointer> list_pointer;
protected:	
	static const DAG dummy_DAG;
	class node : public CGAL_Rep
	{
		friend class CGAL_DAG<T,Pred>;
	public:
		node(const T& e) : data(e),leftPtr(),rightPtr(){}
		node(const T& e, const DAG_handle& left, const DAG_handle& right)
			: data(e),leftPtr(left),rightPtr(right) {}
		~node(){}
		bool is_inner_node() const {return !!leftPtr && !!rightPtr;}
		bool visited() const {return visited_;}
	protected:
		T data;			// information stored in node
		DAG_handle leftPtr,rightPtr;
		mutable bool visited_;
	};
	
	public:
		
		/* -------constructors destructors -----*/
		CGAL_DAG(){}
		CGAL_DAG(const DAG_handle& dag):DAG_handle(dag){}
		CGAL_DAG(const DAG& dag):DAG_handle(dag){}
		CGAL_DAG(const T& rootValue){PTR = new node(rootValue);}
		CGAL_DAG(const T& rootValue, const DAG& left, const DAG& right)
		{PTR= new node(rootValue, left, right);}
		~CGAL_DAG(){}
		/* --------information retrieval -------*/
		const DAG& left() const
		{
			CGAL_precondition(!operator!());
                        //const DAG_handle& x=ptr()->leftPtr;
/*			if (!!x) return *(const DAG*)&x;
			return dummy_DAG;*/
			return *(const DAG*)&ptr()->leftPtr;

		}
		const DAG& right() const
		{
			CGAL_precondition(!operator!());
/*			const DAG_handle& x=ptr()->rightPtr;	
			if (!!x) return *(const DAG*)&x;
			return dummy_DAG;*/
			return *(const DAG*)&ptr()->rightPtr;
		}
		reference operator*() const
		{
			CGAL_precondition(!operator!());
			return ptr()->data;
		}
		pointer operator->() const
		{
			CGAL_precondition(!operator!());
			return &operator*();
		}
		bool is_inner_node() const {return !operator!() && ptr()->is_inner_node();}
		unsigned long size() const
		{
			visit_none();
			return recursive_size();
		}
		unsigned long depth() const
		{
			visit_none();
			return recursive_depth();
		}
		bool operator==(const DAG& b) const
		{
			return PTR==b.PTR;
		}
		bool operator!=(const DAG& b) const
		{
			return !operator==(b);
		}
		/* dynamic management ---------*/
		
		/* description:
		Shallow copy	*/
		DAG& operator=(const DAG& b)
		{
			CGAL_Handle::operator=(b);
			return *this;
		}
/*
		DAG& deep_copy(const DAG& b)
		{
			if (this != &b)
			{
				clear();
				operator=(b);
			}
			return *this;
		}
*/
/*
		void clear()
		{
			if (!operator!())
			{
				left().clear();
				right().clear();
				operator=(DAG());
			}
		}
*/
/*
		void detach_left()
		{
			if (!operator!())
			{
				// create dummy DAG
				T tmp;
				DAG dummy(tmp);
				// detach left son,redirect to dummy
				set_left(dummy);
				// set left son pointer to 0
				ptr()->leftPtr.PTR=0;
				// delete dummy DAG
				delete dummy.ptr();
			}
		}
		void detach_right()
		{
			if (!operator!())
			{
				// create dummy DAG
				T tmp;
				DAG dummy(tmp);
				// detach right son,redirect to dummy
				set_right(dummy);
				// set right son pointer to 0
				ptr()->rightPtr.PTR=0;
				// delete dummy DAG
				delete dummy.ptr();
			}
		}
		void detach()
		{
			detach_left();
			detach_right();
		}
*/
		void set_data(const T& data)
		{
			if (!operator!()) ptr()->data=data;
			else operator=(DAG(data));
		}
		void set_left(const DAG& left)
		{
			CGAL_precondition(!operator!());
			ptr()->leftPtr=left;
		}
		void set_right(const DAG& right)
		{
			CGAL_precondition(!operator!());
			ptr()->rightPtr=right;
		}
		void replace(const T& data,const DAG& left,const DAG& right)
		{
			set_data(data);
			set_left(left);
			set_right(right);
		}
		void visit_none() const
		{
			if (!operator!())
			{
				ptr()->visited_=false;
				left().visit_none();
				right().visit_none();
			}
		}
		void visit_one() const
		{
			if (!operator!())
				ptr()->visited_=true;
		}
		/* -----output ---------------*/
#ifdef CGAL_PRE_IN_POST_ORDER
		void preorder() const
		{
			if (!operator!())
			{
				cout << operator*() << '\t';
				left().preorder();
				right().preorder();
			}
		}
		void inorder() const
		{
			if (!operator!())
			{
				left().inorder();
				cout << operator*() << '\t';
				right().inorder();
			}
		}
		void postorder() const
		{
			if (!operator!())
			{
				left().postorder();
				right().postorder();
				cout << operator*() << '\t';
			}
		}
#endif

#if _MSC_VER>=1100
		friend CGAL_STD_IO_ ostream& operator<<(CGAL_STD_IO_ ostream&  cout, const DAG& t);
#endif

		list_pointer& filter(const Predicate& p,list_pointer& l) const
		{
			visit_none();
			return recursive_filter(p,l);
		}
protected:
		unsigned long recursive_size() const
		{
			if (!operator!() && !ptr()->visited())
				return 1+left().recursive_size()+right().recursive_size();
			else
				return 0;
		}
		unsigned long recursive_depth() const
		{
			if (!operator!() && !ptr()->visited())
				return 1+ CGAL_max(left().recursive_depth(),right().recursive_depth());
			else
				return 0;
		}
		list_pointer& recursive_filter(const Predicate& p,list_pointer& l) const
		{
			if (!operator!() && !ptr()->visited())
			{
				if (p(operator*())) 
					l.insert(l.end(),operator->());
				visit_one();
				left().recursive_filter(p,l);
				right().recursive_filter(p,l);
			}
			return l;
		}
private:
	node* ptr() const {return (node*)PTR;}
};

template<class T,class Pred> CGAL_STD_IO_ ostream& operator<<(CGAL_STD_IO_ ostream&  cout, const CGAL_DAG<T,Pred>& t)
{
	typedef CGAL_DAG<T,Pred> DAG; 
	static int depth;
	int i;
	if (!!t)
	{
		cout << "\n";
		for(i=0;i<depth;i++)cout << ">";
		cout << "Data=" << *t;
		{
			depth++;
			cout << "\n";
			for(i=0;i<depth;i++)cout << ">";
			cout << "left=" << t.left();
			cout << "\n";
			for(i=0;i<depth;i++)cout << ">";
			cout << "right=" <<t.right();
			depth--;
		}
	}
	else
	{
		cout << "Empty";
	}
	return cout ;
}

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
//#include <CGAL/Pm_DAG.C>
#endif

#endif
/* 
	tech notes:
		The code is Handle designed.
		left(),right() are designed to cope with Handle(Handle& x) precondition x.PTR!=0
		operator=() performs shallow copy
		operator*() returns data type
		output is done as a binary tree.
*/
