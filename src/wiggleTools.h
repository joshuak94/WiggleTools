// Copyright (c) 2013, Daniel Zerbino
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
// (1) Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer. 
// 
// (2) Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in
// the documentation and/or other materials provided with the
// distribution.  
// 
// (3)The name of the author may not be used to
// endorse or promote products derived from this software without
// specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef _WIGGLETOOLS_DEF_
#define _WIGGLETOOLS_DEF_

#ifndef true
typedef int bool;
#define true 1
#define false 0
#endif

#include <stdio.h>

typedef struct wiggleIterator_st WiggleIterator;
typedef struct multiplexer_st Multiplexer;

// Creators
WiggleIterator * SmartReader (char *);
WiggleIterator * CatWiggleIterator (char **, int);
// Secondar creators (to force file format recognition)
WiggleIterator * WiggleReader (char *);
WiggleIterator * BigWiggleReader (char *);
WiggleIterator * BedReader (char *);
WiggleIterator * BigBedReader (char *);
WiggleIterator * BamReader (char *);
WiggleIterator * BinaryFileReader (char *);
Multiplexer * newStreamingMultiplexer(FILE * input);

// Basic ops
void seek(WiggleIterator *, const char *, int, int);
void runWiggleIterator(WiggleIterator * wi);

// Algebraic operations on iterators
	
	// Unary
WiggleIterator * UnitWiggleIterator (WiggleIterator *);
WiggleIterator * UnionWiggleIterator (WiggleIterator *);
WiggleIterator * AbsWiggleIterator (WiggleIterator * );
WiggleIterator * NaturalLogWiggleIterator (WiggleIterator *);
WiggleIterator * NaturalExpWiggleIterator (WiggleIterator *);
	// Scalar operations
WiggleIterator * ScaleWiggleIterator (WiggleIterator *, double);
WiggleIterator * PowerWiggleIterator (WiggleIterator *, double);
WiggleIterator * LogWiggleIterator (WiggleIterator * , double);
WiggleIterator * ExpWiggleIterator (WiggleIterator *, double);

// Mapping operations
Multiplexer * newMultiplexer(WiggleIterator **, int);
Multiplexer * newIteratorMultiplexer(WiggleIterator *, int, int);

// Reduction operators on sets

WiggleIterator * SelectReduction(Multiplexer *, int);
WiggleIterator * MaxReduction ( Multiplexer * );
WiggleIterator * MinReduction ( Multiplexer * );
WiggleIterator * SumReduction ( Multiplexer * );
WiggleIterator * ProductReduction ( Multiplexer * );
WiggleIterator * MeanReduction ( Multiplexer * );
WiggleIterator * VarianceReduction ( Multiplexer * );
WiggleIterator * StdDevReduction ( Multiplexer * );
WiggleIterator * MedianReduction ( Multiplexer * );

// Output
void toFile (WiggleIterator *, char *);
void toBinaryFile (WiggleIterator *, char *);
void toStdout (WiggleIterator *);
void streamWiggleIteratorAtIndex(FILE * dest, WiggleIterator * iter, int index, int count);
void streamMultiplexer(FILE * dest, Multiplexer * multi);
WiggleIterator * BinaryTeeWiggleIterator(WiggleIterator *, FILE *);
WiggleIterator * TeeWiggleIterator(WiggleIterator *, FILE *);

// Statistics
double AUC (WiggleIterator *);
double mean (WiggleIterator *);
double variance (WiggleIterator *);

// Regional statistics
// I wonder what the algebraic classification of this thing is...?
WiggleIterator * apply(WiggleIterator * regions, double (*statistic)(WiggleIterator *), WiggleIterator * data);

// Comparison
double pearsonCorrelation (WiggleIterator * , WiggleIterator * );

// Cleaning up
void destroyWiggleIterator (WiggleIterator *);

// Big file params
void setMaxBlocks(int value);
void setMaxHeadStart(int value);

void rollYourOwn(char *);
#endif