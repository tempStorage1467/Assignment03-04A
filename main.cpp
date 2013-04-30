/* File: subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
using namespace std;

Vector<Vector<Set<string> > > subsetsOf2(Vector<Set<string> > masterSet) {
	Vector<Vector<Set<string> > > result;
    Vector<Set<string> > pruned = masterSet;
    
	/* Base case: The only subset of the empty set is the empty set itself. */
	if (masterSet.isEmpty()) {
		result += masterSet;
		return result;
	}
	/* Recursive step: Pull out a single element and obtain all subsets of
	 * the remaining elements.  All of those subsets are subsets of the
	 * master set, as are all sets formed by taking one of those sets
	 * and adding the original element back in.
	 */
	else {
		Set<string> elem = masterSet[0];
        pruned.remove(0);
        
		foreach (Vector<Set<string> > subset in subsetsOf2(pruned)) {
			result += subset;
            
            subset.add(elem);
			result += subset;
		}
		return result;
	}
}

int main() {    
    Set<string> cities1;
    cities1 += "A", "B", "C", "D", "E", "F";
    
    Set<string> hospitalCoverage1;
    hospitalCoverage1 += "A", "B", "C";
    
    Set<string> hospitalCoverage2;
    hospitalCoverage2 += "A", "C", "D";
    
    Set<string> hospitalCoverage3;
    hospitalCoverage3 += "B", "F";
    
    Set<string> hospitalCoverage4;
    hospitalCoverage4 += "C", "E", "F";
    
    Vector< Set<string> > locations;
    locations.add(hospitalCoverage1);
    locations.add(hospitalCoverage2);
    locations.add(hospitalCoverage3);
    locations.add(hospitalCoverage4);

    Vector< Vector< Set<string> > > comboLocations = subsetsOf2(locations);
    cout << "---**---" << endl;
    cout << comboLocations << endl;
}
