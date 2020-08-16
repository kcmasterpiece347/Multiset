/*
 * Kenneth Howe
 * Lab Section: 06
 * Lab Instructor: Michelle Cheatham, Bin Wang
 * Lecture Instructor: Michelle Cheatham
 * 
 * Citations:
 * - I asked Michelle for debugging help during her office hours on Tuesday, 4/21
 *   at around 3pm. She helped point out some mistakes I was making and explained
 *   the need to get addresses of variables and dereference them. Places where she
 *   assisted are left initialed as "MC".
*/

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "Multiset.hpp"
#include "Tuple.hpp"

int main(int argc, char** argv) {
    
    // Initialize multisets
    cout << "MULTISETS" << endl;
    cout << "---------" << endl;

    Multiset<int> e = Multiset<int>(); // empty set

    Multiset<int> m1 = Multiset<int>();
    m1.add(Tuple<int>(1,1));
    m1.add(Tuple<int>(2,5));
    m1.add(Tuple<int>(6,1));
    
    cout << "M1: " + m1.display() << endl;
    
    Multiset<int> m2 = Multiset<int>();
    m2.add(Tuple<int>(1,1));
    m2.add(Tuple<int>(2,3));
    m2.add(Tuple<int>(3,1));

    cout << "M2: " + m2.display() << endl;

    //Test creating a multiset beyond initial capacity
    Multiset<int> m3 = Multiset<int>();
    for(int i=1; i<21; i++) {
        m3.add(Tuple<int>(i, i));
    }

    cout << "M3: " + m3.display() << endl;

    //Test single-element constructor, as well as generic capability
    Multiset<string> m4 = Multiset<string>("string");

    cout << "M4: " + m4.display() << endl;

    Multiset<string> m5 = Multiset<string>("string");
    m5.add(Tuple<string>("beans",2));

    cout << "M5: " + m5.display() << endl;

    cout << "" << endl;

    //Multiset operation testing

    cout << "MULTISET OPERATIONS" << endl;
    cout << "-------------------" << endl;

    cout << "M1 union M2: " + m1.conjunction(m2).display() << endl;
    cout << "M1 union {}: " + m1.conjunction(e).display() << endl;
    cout << "M1 - M2: " + m1.difference(m2).display() << endl;
    cout << "M2 - M1: " + m2.difference(m1).display() << endl;
    cout << "M1 - {}: " + m1.difference(e).display() << endl;
    cout << "{} - M1: " + e.difference(m1).display() << endl;
    cout << "M1 join M2: " + m1.join(m2).display() << endl;
    cout << "M1 join {}: " + m1.join(e).display() << endl;
    cout << "M1 intersect M2: " + m1.intersection(m2).display() << endl;
    cout << "M1 intersect {}: " + m1.intersection(e).display() << endl;

    cout << "" << endl;

    cout << "M4 union M5" + m4.conjunction(m5).display() << endl;
    cout << "M4 - M5: " + m4.difference(m5).display() << endl;
    cout << "M5 - M4: " + m5.difference(m4).display() << endl;
    cout << "M4 join M5: " + m4.join(m5).display() << endl;
    cout << "M4 intersect M5: " + m4.intersection(m5).display() << endl;

    cout << "" << endl;

    // Length and occurrence testing

    cout << "LENGTH AND OCCURRENCE" << endl;
    cout << "---------------------" << endl;

    cout << "M1 Length: " + to_string(m1.length()) << endl;
    cout << "M2 Length: " + to_string(m2.length()) << endl;
    cout << "M3 Length: " + to_string(m3.length()) << endl;
    cout << "M4 Length: " + to_string(m4.length()) << endl;
    cout << "M5 Length: " + to_string(m5.length()) << endl;

    cout << "" << endl;

    cout << "2 occurs in M1 " + to_string(m1.occurrence(2)) + " times." << endl;
    cout << "6 occurs in M1 " + to_string(m1.occurrence(6)) + " times." << endl;
    cout << "2 occurs in M2 " + to_string(m2.occurrence(2)) + " times." << endl;
    cout << "6 occurs in M2 " + to_string(m2.occurrence(6)) + " times." << endl;
    cout << "'beans' occurs in M4 " + to_string(m4.occurrence("beans")) + " times." << endl;
    cout << "'beans' occurs in M5 " + to_string(m5.occurrence("beans")) + " times." << endl;

    return 0;
}