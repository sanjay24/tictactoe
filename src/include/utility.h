/*
 * utility.h
 *
 *  Created on: Dec 17, 2016
 *      Author: Sanjay Kumar
 */

#ifndef UTILITY_H_
#define UTILITY_H_
#include <ostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define DEBUG 0

#define debug_print(...) do { if (DEBUG) fprintf(stderr, "%s:%d", __FILE__, __LINE__, __VA_ARGS__); } while (0)

#endif /* UTILITY_H_ */
