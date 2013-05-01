/* File: combinations.cpp
 *
 * A program to list off all combinations of a master set.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
using namespace std;

void listCombinationsOf(Vector<Set<string> > s, int k,
                        Set<string>& cities,
                        Vector< Set<string> >& result);

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
    
    Vector< Set<string> > locations1;
    locations1.add(hospitalCoverage1);
    locations1.add(hospitalCoverage2);
    locations1.add(hospitalCoverage3);
    locations1.add(hospitalCoverage4);
	
    Vector< Set<string> > result;
	listCombinationsOf(locations1, 3, cities1, result);
}

bool doesLocationCombinationCoverCities(Set<string> cities,
                                        Vector< Set<string> > result) {
    if (cities.size() == 0) {
        // Base Case: Cities is empty; All cities covered
        return true;
    } else if (result.size() == 0) {
        // Base Case: All hospital locations taken into account
        return false;
    } else {
        Set<string> firstHospitalCoverage = result[0];
        result.remove(0);
        Set<string> uncoveredCities = cities - firstHospitalCoverage;
        return doesLocationCombinationCoverCities(uncoveredCities, result);
    }
}

/* Recursively lists off all combinations of k elements from the master
 * set s, under the assumption we've already built up the partial set
 * soFar.
 */
bool recListCombinationsOf(Vector<Set<string> > s,
                           int k,
                           Vector<Set<string> > soFar,
                           Set<string>& cities,
                           Vector< Set<string> >& result) {
	if (k == 0) {
        /* Base case 1: If there are no more elements to pick, output
         * what we have so far.
         */
        if (doesLocationCombinationCoverCities(cities, soFar)) {
            result = soFar;
            return true;
        }
	} else if (k != 0 && k <= s.size()) {
		/* Fix some element from the set. */
		Set<string> elem = s[0];
        Vector<Set<string> > soFarAdjusted = soFar;
        soFarAdjusted.add(elem);

		/* Option 1: Pick this element. Then we need k - 1 elements from
		 * the remainder of the set.
		 */
        Vector<Set<string> > sPruned = s;
        sPruned.remove(0);
		if (recListCombinationsOf(sPruned, k - 1, soFarAdjusted, cities, result)) {
            return true;
        }

		/* Option 2: Don't pick this element. Then we need k elements from
		 * the remainder of the set.
		 */
		if (recListCombinationsOf(sPruned, k, soFar, cities, result)) {
            return true;
        }
	}
}

void listCombinationsOf(Vector<Set<string> > s, int k,
                        Set<string>& cities,
                        Vector< Set<string> >& result) {
    Vector<Set<string> > emptySet;
    // Start at 1 so we find the most efficient solution first
    for (int i = 1; i <= k; i++) {
        if (recListCombinationsOf(s, i, emptySet, cities, result)) {
            cout << result << endl;
            break;
        }
    }
}
