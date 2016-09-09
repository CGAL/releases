// ---------------------------------------
// Example program from Getting Started with CGAL
// Chapter: Appendix (A short introduction to C++)
// Author: Geert-Jan Giezeman
// June 1997
// ---------------------------------------

typedef int bool;

template <class T>
class stack {
public:
                stack() ;
    bool        is_empty() const ;
    T           top() const ;
    void        push(T i) ;
    void        pop() ;
};

class Customer { /* ... */ };

main()
{
    Customer c;
    stack<Customer> cstack;
    cstack.push(c);
    c = cstack.top();
    while (!cstack.is_empty())
	cstack.pop();
}
