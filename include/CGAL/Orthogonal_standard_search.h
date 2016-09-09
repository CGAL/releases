// Copyright (c) 2002  Utrecht University (The Netherlands).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Spatial_searching/include/CGAL/Orthogonal_standard_search.h,v $
// $Revision: 1.17 $ $Date: 2003/09/18 10:25:44 $
// $Name: current_submission $
//
// Authors       : Hans Tangelder (<hanst@cs.uu.nl>)

#ifndef  ORTHOGONAL_STANDARD_SEARCH_H
#define  ORTHOGONAL_STANDARD_SEARCH_H
#include <cstring>
#include <list>
#include <queue>
#include <memory>
#include <CGAL/Kd_tree_node.h>
#include <CGAL/Euclidean_distance.h>

namespace CGAL {

template <class TreeTraits, 
	  class Distance=Euclidean_distance<typename TreeTraits::Point>, 
	  class Tree=Kd_tree<TreeTraits> >
class Orthogonal_standard_search {

public:

typedef typename TreeTraits::Point Point;
typedef typename TreeTraits::Point Query_item;
typedef typename TreeTraits::NT NT;
typedef std::pair<Point*,NT> Point_with_distance;

typedef typename Tree::Node_handle Node_handle;

typedef typename Kd_tree<TreeTraits>::Point_iterator Point_iterator;
typedef Kd_tree_rectangle<NT> Rectangle; 

private:

int number_of_internal_nodes_visited;
int number_of_leaf_nodes_visited;
int number_of_items_visited;

bool search_nearest;

NT multiplication_factor;
Query_item* query_object;
int total_item_number;
NT distance_to_root;   

typedef std::list<Point_with_distance> NN_list;

NN_list l;
int max_k;
int actual_k;


Distance* distance_instance;

	inline bool branch(NT distance) {
		if (actual_k<max_k) return true;
		else 
		  if (search_nearest) return 
		  ( distance * multiplication_factor < l.rbegin()->second);
		  else return 
		  ( distance > 
		    l.begin()->second * multiplication_factor);
	};

	inline void insert(Point* I, NT dist) {
		bool insert;
		if (actual_k<max_k) insert=true;
		else 
			if (search_nearest) insert=
			( dist < l.rbegin()->second ); 
			else insert=(dist > l.begin()->second);
        if (insert) {
	   		actual_k++;	 	
			typename NN_list::iterator it=l.begin();
			for (; (it != l.end()); ++it) 
			{ if (dist < it->second) break;}
        		Point_with_distance NN_Candidate(I,dist);
        		l.insert(it,NN_Candidate);
        		if (actual_k > max_k) {
				actual_k--;
                if (search_nearest) l.pop_back();
				else l.pop_front();
        	};
  		}

	};

	
	public:

	template<class OutputIterator>  
	OutputIterator  the_k_neighbors(OutputIterator res)
	{   
		typename NN_list::iterator it=l.begin(); 
		for (; it != l.end(); it++) { *res= *it; res++; }
		return res;     
	}


    // constructor
    Orthogonal_standard_search(Tree& tree, Query_item& q,  
    const Distance& d=Distance(), int k=1, NT Eps=NT(0.0), bool Search_nearest=true) {
   
	distance_instance=new Distance(d);

	multiplication_factor=
	d.transformed_distance(1.0+Eps);
        
	max_k=k;
	actual_k=0;
	search_nearest = Search_nearest; 
		
        // if (search_nearest) 
		distance_to_root=
        	d.min_distance_to_queryitem(q,
						*(tree.bounding_box()));
        // else 
	//	distance_to_root=
        //	distance_instance->max_distance_to_queryitem(q,
	//					*(tree.bounding_box()));

        query_object = &q;

        total_item_number=tree.item_number();

        number_of_leaf_nodes_visited=0;
        number_of_internal_nodes_visited=0;
        number_of_items_visited=0;
       
        compute_neighbors_orthogonally(tree.root(), distance_to_root);
       
    }

    
    // Print statistics of the standard search process.
    std::ostream& statistics (std::ostream& s) {
    	s << "Standard search statistics:" << std::endl;
    	s << "Number of internal nodes visited:" 
	<< number_of_internal_nodes_visited << std::endl;
    	s << "Number of leaf nodes visited:" 
	<< number_of_leaf_nodes_visited << std::endl;
    	s << "Number of items visited:" 
	<< number_of_items_visited << std::endl;
        return s;
    }

    // destructor
    ~Orthogonal_standard_search() { 
		l.clear();  
		delete distance_instance;
    };

    private:
   
    void compute_neighbors_orthogonally(Node_handle N, NT rd) {
		
                if (!(N->is_leaf())) {
                        number_of_internal_nodes_visited++;
                        int new_cut_dim=N->cutting_dimension();
                        NT old_off, new_rd;
                        NT new_off =
                        (*query_object)[new_cut_dim] - 
					N->cutting_value();
                        if ( ((new_off < NT(0.0)) && (search_nearest)) ||
                        (( new_off >= NT(0.0)) && (!search_nearest))  ) {
				compute_neighbors_orthogonally(N->lower(),rd);
                                if (search_nearest) {
                                	old_off= (*query_object)[new_cut_dim]-
							N->low_value();
                                	if (old_off>NT(0.0)) old_off=NT(0.0);
                                }
				else 
				{	
                                	old_off= (*query_object)[new_cut_dim] 
					- N->high_value();
					if (old_off<NT(0.0)) old_off=NT(0.0);
                                }
                                new_rd=
                                distance_instance->
				new_distance(rd,old_off,new_off,new_cut_dim);
				if (branch(new_rd)) 
				compute_neighbors_orthogonally(N->upper(),
								new_rd);                               
                        }
                        else { // compute new distance
                                compute_neighbors_orthogonally(N->upper(),rd); 
				if (search_nearest) {
                                	old_off= N->high_value() - 
					(*query_object)[new_cut_dim];
                                	if (old_off>NT(0.0)) old_off=NT(0.0);
				}
                                else 
                                {       
                                	old_off= N->low_value() - 
					(*query_object)[new_cut_dim];
					if (old_off<NT(0.0)) old_off=NT(0.0);
				}  
                                new_rd=
                                distance_instance->
				new_distance(rd,old_off,new_off,new_cut_dim);
				if (branch(new_rd)) 
				compute_neighbors_orthogonally(N->lower(),
								new_rd);       
                        }
                }
                else
				{
                  // n is a leaf
                  number_of_leaf_nodes_visited++;
                  if (N->size() > 0)
                  for (Point_iterator it=N->begin(); it != N->end(); it++) {
                        number_of_items_visited++;
			NT distance_to_query_object=
                        distance_instance->
                        distance(*query_object,**it);
                        insert(*it,distance_to_query_object);
                  }
		}
    }

    
    


    
   

}; // class 



} // namespace CGAL


#endif  // ORTHOGONAL_STANDARD_SEARCH
