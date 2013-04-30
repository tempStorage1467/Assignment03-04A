/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include <vector>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

bool doesLocationCombinationCoverCities(Set<string> cities,
                                        Vector< Set<string> > result);
Vector< Set<string> > evaluateCombinations(const Set<string> cities,
                                           Vector< Vector< Set<string> > > coverageCombinations,
                                           const int numHospitals);
Vector< Vector< Set<string> > > getAllPossibleLocationCombinations(
                                                                   Vector< Set<string> > locations);

bool assertEquals(bool expected, bool actual) {
    if (expected == actual) {
        return true;
    } else {
        cout << "Expected: " << expected << "; Actual: " << actual << endl;
        return false;
    }
}

bool assertEquals(Vector< Set<string> > expected, Vector< Set<string> > actual) {
    if (expected.size() != actual.size()) {
        cout << "Unequal Vectors" << endl;
        return false;
    }
    for (int i = 0; i < expected.size(); i++) {
        if (expected[i] != actual[i]) {
            cout << "Vector " << i << " is unequal" << endl;
            return false;
        }
    }
    return true;
}

void testDoesLocationCombinationCoverCities() {
    Set<string> cities1;
    cities1 += "A", "B", "C", "D", "E", "F";
    
    Set<string> hospital1;
    hospital1 += "A", "B", "C";
    
    Set<string> hospital2;
    hospital2 += "A", "C", "D";
    
    Set<string> hospital3;
    hospital3 += "C", "E", "F";
    
    Vector< Set<string> > locationCombination;
    locationCombination.add(hospital1);
    locationCombination.add(hospital2);
    locationCombination.add(hospital3);
    
    assertEquals(true, doesLocationCombinationCoverCities(cities1,
                                                          locationCombination));
    Set<string> cities2;
    cities2 += "A", "B", "C", "D", "E", "F";
    
    Set<string> hospitalA1;
    hospitalA1 += "A", "B", "C";
    
    Set<string> hospitalA2;
    hospitalA2 += "A", "C", "D";
    
    Set<string> hospitalA3;
    hospitalA3 += "B", "F";
    
    Vector< Set<string> > locationCombination2;
    locationCombination2.add(hospitalA1);
    locationCombination2.add(hospitalA2);
    locationCombination2.add(hospitalA3);
    
    assertEquals(false, doesLocationCombinationCoverCities(cities2,
                                                           locationCombination2));
}

void testCanOfferUniversalCoverage() {
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
    
    Vector< Set<string> > result1;
    
    assertEquals(true, canOfferUniversalCoverage(cities1,
                                                 locations1,
                                                 3,
                                                 result1));
    
    assertEquals(false, canOfferUniversalCoverage(cities1,
                                                  locations1,
                                                  2,
                                                  result1));
    
}

void testEvaluateCombinations() {
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
    
    Set<string> hospitalCoverage5;
    hospitalCoverage5 += "C", "F";
    
    Vector< Set<string> > layoutPlan1;
    layoutPlan1.add(hospitalCoverage1);
    layoutPlan1.add(hospitalCoverage5);
    
    Vector< Set<string> > layoutPlan2;
    layoutPlan2.add(hospitalCoverage3);
    layoutPlan2.add(hospitalCoverage5);
    
    Vector< Set<string> > layoutPlan3;
    layoutPlan3.add(hospitalCoverage1);
    layoutPlan3.add(hospitalCoverage2);
    layoutPlan3.add(hospitalCoverage4);
    
    Vector< Set<string> > layoutPlan4;
    layoutPlan4.add(hospitalCoverage1);
    layoutPlan4.add(hospitalCoverage2);
    
    Vector< Vector< Set<string> > > coverageCombinations1;
    coverageCombinations1.add(layoutPlan1);
    coverageCombinations1.add(layoutPlan2);
    coverageCombinations1.add(layoutPlan3);
    Vector< Set<string> > result1 = evaluateCombinations(cities1,
                                                         coverageCombinations1,
                                                         3);
    assertEquals(layoutPlan3, result1);
    
    // TEST2
    Set<string> cities2;
    cities2 += "A", "B", "C", "D", "E", "F";
    Vector< Vector< Set<string> > > coverageCombinations2;
    coverageCombinations2.add(layoutPlan1);
    coverageCombinations2.add(layoutPlan2);
    coverageCombinations2.add(layoutPlan4);
    Vector< Set<string> > result2 = evaluateCombinations(cities2,
                                                         coverageCombinations2,
                                                         3);
    Vector< Set<string> > layoutPlanE;
    assertEquals(layoutPlanE, result2);
}

void runTests() {
    testDoesLocationCombinationCoverCities();
    testEvaluateCombinations();
    testCanOfferUniversalCoverage();
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

/*
 * Code taken from CS106B lecture.
 */
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

Vector< Vector< Set<string> > > getAllPossibleLocationCombinations(
                                                                   Vector< Set<string> > locations) {
    Set<string> compressed = deflateVecOfSets(locations);
    
    Vector<Set<string> > compressedLocationCombos = subsetsOf(compressed);
    
    Vector< Vector< Set<string> > > locationCombos =
    enflateCombos(compressedLocationCombos);
    return locationCombos;
}

Vector< Set<string> > evaluateCombinations(const Set<string> cities,
                                           Vector< Vector< Set<string> > > coverageCombinations,
                                           const int numHospitals) {
    // need to set the coverage combination here or it will be
    //   blank for some reason after
    Vector< Set<string> > blank;
    const Vector< Set<string> > toEvaluate =
    (coverageCombinations.size() != 0) ? coverageCombinations[0] : blank;
    
    if (coverageCombinations.size() == 0) {
        Vector< Set<string> > blank;
        return blank;
    } else {
        if (toEvaluate.size() <= numHospitals &&
            doesLocationCombinationCoverCities(cities,
                                               toEvaluate)) {
                return toEvaluate;
            } else {
                coverageCombinations.remove(0);
                return evaluateCombinations(cities,
                                            coverageCombinations,
                                            numHospitals);
            }
    }
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result) {
    
    // STEP 1: Determine Combinations of Locations <= numHospitals
    //   Iterate over each element in the vector $locations
    //   and determine all combinations;
    //   at each element, only look to the right to generate combinations as
    //   you don't want duplicates
    Vector< Vector< Set<string> > > coverageCombinations;
    coverageCombinations = getAllPossibleLocationCombinations(locations);
    
    // STEP 2: Evaluate whether any possible combination works
    Vector< Set<string> > resultCombo = evaluateCombinations(cities,
                                                             coverageCombinations,
                                                             numHospitals);
    if (resultCombo.size() == 0) {
        return false;
    } else {
        result = resultCombo;
        return true;
    }
}

int main() {
    runTests();
    return 0;
}