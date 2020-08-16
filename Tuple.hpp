#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;

/**
* Represents a generic tuple (element, multiplicity) for use in the Multiset class.
*/
template <class E> class Tuple {
    
    public:
        Tuple() {
            multiplicity = 0;
        }
        
        Tuple(E element, int multiplicity) {
            if(multiplicity > 0) {
                this->multiplicity = multiplicity;
            }
            else {
                throw "Invalid Multiplicity: Tuple multiplicity must be positive.";
            }
            
            this->element = element;
        }
        
        Tuple(const Tuple<E>& other) {
            element = other.element;
            multiplicity = other.multiplicity;
        }
        
        E getElement() {
            return element;
        }
        
        int getMultiplicity() {
            return multiplicity;
        }
        
        void setMultiplicity(int multiplicity) {
            this->multiplicity = multiplicity;
        }
        
        string display() {
            string display = "(";
            stringstream ss;

            ss << element;
            display += ss.str();
            ss.str(string());

            display += ", ";

            ss << multiplicity;
            display += ss.str();
            ss.str(string());

            display += ")";
            
            return display;
        }
        
    private:
        E element;
        int multiplicity;

};

#endif /* TUPLE_HPP */