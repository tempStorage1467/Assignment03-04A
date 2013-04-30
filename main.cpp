/* File: subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
using namespace std;

/* Function to produce a Vector of all the subsets of the master
 * set of integers.
 */
Vector<Set<string> > subsetsOf(Set<string> masterSet);

/* Function to list, but not return, all subsets of the master set. */
void listSubsetsOf(Set<int> masterSet);

Vector<Set<string> > subsetsOf(Set<string> masterSet) {
	Vector<Set<string> > result;
	
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
		string elem = masterSet.first();
		
		foreach (Set<string> subset in subsetsOf(masterSet - elem)) {
			result += subset;
			result += subset + elem;
		}
		return result;
	}
}

string deflateSetOfStrs(Set<string> toCompress) {
    string compressed;
    if (toCompress.size() == 0) {
        return compressed;
    } else {
        string elem = toCompress.first();
        return elem + deflateSetOfStrs(toCompress - elem);
    }
}

Set<string> deflateVecOfSets(Vector<Set<string> > locations) {
    Set<string> result;
    if (locations.size() == 0) {
        return result;
    } else {
        Set<string> singleHospitalCoverage = locations[0];
        string compressed = deflateSetOfStrs(singleHospitalCoverage);
        locations.remove(0);
        result.add(compressed);
        return result + deflateVecOfSets(locations);
    }
}

Set<string> enflateString(string location) {
    Set<string> result;
    if (location.size() == 1) {
        result.add(location.substr(0, 1));
        return result;
    } else {
        result.add(location.substr(0, 1));
        return result + enflateString(location.substr(1));
    }
}

Vector<Set<string > > enflateLocationCombination(Set<string> locationCombo) {
    Vector<Set<string > > result;
    if (locationCombo.size() == 0) {
        return result;
    } else {
        string elem = locationCombo.first();
        locationCombo.remove(elem);
        result.add(enflateString(elem));
        return result + enflateLocationCombination(locationCombo);
    }
}

Vector< Vector< Set<string> > > enflateCombos(
                            Vector<Set<string > > compressedLocationCombos) {
    Vector< Vector< Set<string> > > result;
    if (compressedLocationCombos.size() == 0) {
        return result;
    } else {
        Set<string> elem = compressedLocationCombos[0];
        Vector<Set<string > > enflatedLocationCombination =
          enflateLocationCombination(elem);
        compressedLocationCombos.remove(0);
        result.add(enflatedLocationCombination);
        return result + enflateCombos(compressedLocationCombos);
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

    Set<string> compressed = deflateVecOfSets(locations);

    Vector<Set<string> > compressedLocationCombos = subsetsOf(compressed);
    cout << compressedLocationCombos << endl;
    
    Vector< Vector< Set<string> > > locationCombos =
      enflateCombos(compressedLocationCombos);
    cout << "---" << endl;
    cout << locationCombos << endl;
}
