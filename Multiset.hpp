#ifndef MULTISET_HPP
#define MULTISET_HPP

#include <cstdlib>
#include <sstream>
#include <string>

#include "Tuple.hpp"

using namespace std;

/**
* Represents a multiset as a set (array) of generic Tuples.
*/
template <class E> class Multiset {

    public:

        Multiset() {
            capacity = 16;
            tupleSet = new Tuple<E>[capacity];
            size = 0;
        }

        Multiset(E element) {
            capacity = 16;
            tupleSet = new Tuple<E>[capacity];
            tupleSet[0] = Tuple<E>(element, 1);
            size = 1;
        }
        
        Multiset(const Multiset<E>& other) {
            tupleSet = new Tuple<E>[other.capacity];
            capacity = other.capacity; // MC
            size = other.size;
            
            for(int i=0; i<other.size; i++) {
                tupleSet[i] = Tuple<E>(other.tupleSet[i]);
            }
        }
        
        /**
        * Computes the union of this multiset and another.
        *
        * @param other The multiset to be unioned with.
        * @return Returns the union as a multiset object.
        */
        Multiset<E> conjunction(const Multiset<E>& other) {
            Multiset<E> conjunction = Multiset<E>(other);
            Tuple<E> t;
            for(int i=0; i<size; i++) {
                t = tupleSet[i];
                if(conjunction.setMaxMultiplicity(t.getElement(), t.getMultiplicity()) == 0) {
                    conjunction.add(Tuple<E>(t));
                }
            }
            return conjunction;
        }
        
        /**
        * Computes the intersection between this multiset and another.
        *
        * @param other The multiset to be intersected with.
        * @return Returns the intersection as a multiset object.
        */
        Multiset<E> intersection(Multiset<E> other) {
            return this->difference(this->difference(other));
        }
        
        /**
        * Computes the difference between this multiset and another.
        *
        * @param other The multiset serving as the subtrahend.
        * @return Returns the difference (this - other) as a multiset object.
        */
        Multiset<E> difference(Multiset<E> other) {
            Multiset<E> difference = this->copy();
            Tuple<E> t;

            for(int i=0; i<other.size; i++) {
                t = other.tupleSet[i];
                difference.remove(t.getElement(), t.getMultiplicity());
            }
            return difference;
        }
        
        /**
        * Computes the join of this multiset and another.
        *
        * @param other The multiset to be joined with.
        * @return Returns the join as a multiset object.
        */
        Multiset<E> join(const Multiset<E>& other) {
            Multiset join = Multiset(other);
            Tuple<E> t;
            for(int i=0; i<size; i++) {
                t = tupleSet[i];
                join.add(Tuple<E>(t));
            }
            return join;
        }
        
        /**
        * Attempts to set the multiplicity of an element in the multiset to the max
        * of its current multiplicity and a given multiplicity; if the element is
        * not found in the multiset, returns 0.
        * 
        * @param element The element to find in the set
        * @param multiplicity The multiplicity to attempt to set on the given element
        * @return The max multiplicity of the element, or 0 if element not in set.
        */
        int setMaxMultiplicity(E element, int multiplicity) {
            Tuple<E>* t; // MC need a pointer to the tuple, not a copy
            for(int i=0; i<size; i++) {
                t = &tupleSet[i];
                if(t->getElement() == element) {
                    if(t->getMultiplicity() < multiplicity) {
                        t->setMultiplicity(multiplicity);
                        return multiplicity;
                    }
                    return t->getMultiplicity();
                }
            }
            return 0;
        }
        
        /**
        * Attempts to set the multiplicity of an element in the multiset to the min
        * of its current multiplicity and a given multiplicity; if the element is
        * not found in the multiset, returns 0.
        * 
        * @param element The element to find in the set
        * @param multiplicity The multiplicity to attempt to set on the given element
        * @return The min multiplicity of the element, or 0 if the element not in set.
        */
        int setMinMultiplicity(E element, int multiplicity) {
            Tuple<E>* t;
            for(int i=0; i<size; i++) {
                t = tupleSet[i];
                if(t->getElement() == element) {
                    if(t->getMultiplicity > multiplicity) {
                        t->setMultiplicity(multiplicity);
                        return multiplicity;
                    }
                    return t->getMultiplicity();
                }
            }
            return 0;
        }
        
        /**
        * Adds a given amount to the multiplicity of an element in the multiset; if
        * element is not in set, returns 0.
        * 
        * @param element The element to find in set
        * @param multiplicity The amount to add to the given element's multiplicity
        * @return The total multiplicity of the element after adding, or 0 if element
        * not found in set
        * 
        */
        int addMultiplicity(E element, int addend) {
            Tuple<E> t;
            for(int i=0; i<size; i++) {
                t = tupleSet[i];
                if(t.getElement() == element) {
                    t.setMultiplicity(t.getMultiplicity() + addend);
                    return t.getMultiplicity() + addend;
                }
            }
            return 0;
        }
        
        /**
        * Adds an element to the multiset.
        * 
        * If a tuple with matching element is already in the multiset, increases
        * the multiplicity of the extant tuple correspondingly.
        * 
        * If multiset is at capacity, creates a copy of the tupleSet array with
        * doubled length and adds element to the end.
        * 
        * @param t The tuple to add to the multiset
        */
        void add(Tuple<E> t) {
            bool isInMultiset = false;
            Tuple<E>* s;
            
            for(int i=0; i<size; i++) {
                s = &tupleSet[i];
                if(s->getElement() == t.getElement()) {
                    s->setMultiplicity(t.getMultiplicity() + s->getMultiplicity());
                    isInMultiset = true;
                }
            }
            
            if(!isInMultiset) {
                if(size < capacity) {
                    tupleSet[size] = t;
                }
                else {
                    Tuple<E>* newTupleSet = new Tuple<E>[capacity*2];
                    for(int i=0; i<capacity; i++) {
                        newTupleSet[i] = tupleSet[i];
                    }
                    delete[] tupleSet;
                    newTupleSet[capacity] = t;
                    tupleSet = newTupleSet;
                    capacity *= 2;
                }
                size++;
            }
        }
        

        /**
        * Removes a number of elements of a given value from the multiset.
        * 
        * If possible, subtracts from the multiplicity of the element with given
        * value in the multiset. If elements of the given value are removed in
        * excess of their multiplicity, will remove the corresponding tuple from
        * the tupleSet.
        * 
        * @param element The element to remove from the set
        * @param multiplicity The number of elements to remove
        */
        void remove(E element, int subtrahend) {
            Tuple<E>* t; // MC: need a pointer to the tuple, not a copy
            int difference;
            for(int i=0; i<size; i++) {
                t = &tupleSet[i];
                if((t->getMultiplicity() > 0) && (t->getElement() == element)) {
                    if(t->getMultiplicity() > subtrahend) {
                        difference = t->getMultiplicity() - subtrahend;
                        t->setMultiplicity(difference);
                    }
                    else {
                        remove(i);
                    }
                }
            }
        }
        
        /**
        * Removes the tuple at a given index from the multiset.
        * 
        * Shifts all other tuples in tupleSet to the left.
        * 
        * @param index Index of tuple to remove
        */
        void remove(int index) {
            if(index < size-1) {
                for(int i=index; i<size-1; i++) {
                    tupleSet[i] = tupleSet[i+1];
                }
                tupleSet[size-1] = Tuple<E>();
            }
            size--;
        }
        
        /**
        * Computes length of this multiset, where length is defined to be the total
        * number of elements in the multiset (i.e. the sum of the multiplicities of
        * each element in the set)
        * 
        * @return The length of the multiset
        */
        int length() {
            int length = 0;
            Tuple<E> t;
            
            for(int i=0; i<size; i++) {
                t = tupleSet[i];
                length += t.getMultiplicity();
            }
            
            return length;
        }
        
        /**
        * Computes the occurrence of an element of type E, where occurrence is
        * defined to be the multiplicity of that element in the multiset if it is
        * contained in the multiset, or 0 otherwise.
        * 
        * @param element The element to find the occurrence of
        * @return The occurence of the element in this multiset
        */
        int occurrence(E element) {
            Tuple<E> t;
            
            for(int i=0; i<size; i++) {
                t = tupleSet[i];
                if(t.getElement() == element) {
                    return t.getMultiplicity();
                }
            }
            return 0;
        }
        
        /**
        * Prints elements in the multiset
        * 
        * @return String of the form {(e1, m1), (e2, m2), ... }
        */
        string display() {
            string display = "{";
            stringstream ss;
            
            for(int i=0; i<size-1; i++) {
                display += (tupleSet[i].display() + ", ");
            }
            if(size > 0) {
              display += tupleSet[size-1].display();
            }

            ss << "}";
            display += ss.str();
            ss.str(string());

            return display;
        }
        
        /**
        * Creates a copy of this multiset.
        *
        * @return A copy of this multiset.
        */
        Multiset<E> copy() {
            /*  
              I don't really like that I have this, but I struggled to get functioning
              code that made use of the copy constructor on the argument "this".
            */
            Multiset<E> copy = Multiset<E>();
            copy.tupleSet = new Tuple<E>[capacity];
            copy.size = size;
            
            for(int i=0; i<size; i++) {
                copy.tupleSet[i] = Tuple<E>(tupleSet[i]);
            }

            return copy;
        }
        

    private:
    
        Tuple<E>* tupleSet;
        int capacity;
        int size;

};

#endif /* MULTISET_HPP */