// Copyright (c) 2007 Inria Lorraine (France). All rights reserved.
// 
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
// 
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// 
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Algebraic_kernel_d/include/CGAL/RS/pagealloc.h $
// $Id: pagealloc.h 53360 2009-12-09 14:51:58Z penarand $
// 
// Author: Luis Pe�aranda <luis.penaranda@loria.fr>

#ifndef CGAL_RS__PAGEALLOC_H
#define CGAL_RS__PAGEALLOC_H

#include <cstdlib>
#include <cstring>

namespace CGAL{
namespace RS_MGCD{

#define PAGESIZE        4194304
#define TABLESIZE       2048
#define PAGES           8
#define VOIDSCAST       unsigned long

struct pinfo{
    void *start;
    size_t size;
};

RS_THREAD_ATTR void**  pages_startptr;
RS_THREAD_ATTR size_t  pages_max;//=PAGES;
RS_THREAD_ATTR size_t  pages_allocated;
RS_THREAD_ATTR size_t  pages_current;

RS_THREAD_ATTR size_t  page_remainingbytes;
RS_THREAD_ATTR void*   page_currentptr;

RS_THREAD_ATTR struct pinfo    *nodes_allocated;
RS_THREAD_ATTR size_t          nodes_total;
RS_THREAD_ATTR size_t          nodes_assigned;

class Page_alloc{

    protected:
        static
        void* meminit(){
            pages_startptr=(void**)malloc(PAGES*sizeof(void*));
            pages_startptr[0]=malloc(PAGESIZE);
            pages_allocated=1;
            pages_current=0;
            page_remainingbytes=PAGESIZE;
            page_currentptr=pages_startptr[0];
            nodes_total=TABLESIZE;
            nodes_allocated=
                (struct pinfo*)malloc(TABLESIZE*sizeof(struct pinfo));
            nodes_assigned=0;
            return page_currentptr;
        };

        static
        void* newpage(){
            void *r;
            if(pages_allocated>pages_current+1){
                ++pages_current;
                r=pages_startptr[pages_current];
                page_currentptr=r;
                page_remainingbytes=PAGESIZE;
                return r;
            }
            // iso c++ forbids to initialize a static member (pages_max),
            // so we have to start using pages_max when the amount of
            // allocated pages reaches the value PAGES (this is not of
            // course the cleanest way to do it)
            if(pages_allocated==PAGES)
                pages_max=2*PAGES;
            else
                pages_max=0;
            if(pages_allocated==pages_max){
                pages_max*=2;
                pages_startptr=
                    (void**)realloc(pages_startptr,pages_max*sizeof(void*));
            }
            r=malloc(PAGESIZE);
            pages_startptr[pages_allocated]=r;
            page_currentptr=r;
            ++pages_allocated;
            page_remainingbytes=PAGESIZE;
            return r;
        };

        // if they ask us to allocate a memory size bigger than the page,
        // we are lost (we could in that case make a bigger page)
        static
        void* palloc(size_t size){
            void* r;
            if(size>page_remainingbytes){
                newpage();
                return palloc(size);
            }
            if(nodes_assigned==nodes_total){
                nodes_total*=2;
                nodes_allocated=(struct pinfo*)realloc
                    (nodes_allocated,nodes_total*sizeof(struct pinfo));
            }
            page_remainingbytes-=size;
            r=page_currentptr;
            page_currentptr=(void*)((VOIDSCAST)page_currentptr+size);
            // c++ does not support nodes_allocated[nodes_assigned]={r,s}
            nodes_allocated[nodes_assigned].start=r;
            nodes_allocated[nodes_assigned].size=size;
            ++nodes_assigned;
            return r;
        };

        static
        void* prealloc(void *ptr,size_t size){
            void *dest;
            size_t i=0;
            while(nodes_allocated[i].start!=ptr)
                ++i;
            if(nodes_allocated[i].size<size){
                dest=palloc(size);
                nodes_allocated[i].start=dest;
                nodes_allocated[i].size=size;
                return memcpy(dest,ptr,nodes_allocated[i].size);
            }
            return ptr;
        };

        #define pfree(X)        {}
        //void pfree(void* ptr){
        //  size_t i=0;
        //  while(nodes_allocated[i].start!=ptr)
        //      ++i;
        //  nodes_allocated[i].start=0;
        //  return;
        //};

        static
        void* memclear(){
            pages_current=0;
            page_remainingbytes=PAGESIZE;
            page_currentptr=pages_startptr[0];
            nodes_assigned=0;
            return page_currentptr;
        }

        static
        void memrelease(){
            size_t i;
            for(i=0;i<pages_allocated;++i)
                free(pages_startptr[i]);
            return;
        };

}; // class Page_alloc

} // namespace RS_MGCD
} // namespace CGAL

#endif  // CGAL_RS__PAGEALLOC_H

// vim: tabstop=4: softtabstop=4: smarttab: shiftwidth=4: expandtab
