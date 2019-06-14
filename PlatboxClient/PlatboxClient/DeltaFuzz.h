#pragma once
#ifndef __DeltaFuzz_h__
#define __DeltaFuzz_h__


#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

/* Definitions */

#define DEFAULT_FUZZ_POSSIBILITY 100
#define DEFAULT_UNMAP_POSSIBILITY 0

/* Structures and Variables */

typedef struct _FUZZER_OBJECT {
	UINT32 Seed;
	double FuzzPossibility;
	double UnmapPossibility;
	UINT64 Iterations;
	BOOL FuzzGenerate;
	BOOL FuzzMutate;
	int(*get_random)(void *fuzzer);
	void(*fuzz_blob)(void *fuzzer, UCHAR *blob, UINT32 size);
	unsigned int(*get_fuzzy_len)(void *fuzzer, unsigned int max);
	int (*gen_int)(void *fuzzer, unsigned long long *qp);
} FUZZER_OBJECT, *PFUZZER_OBJECT;


int wrapper_rand(FUZZER_OBJECT *fuzzer);
void _swapValues_UINT(UINT32 *a, UINT32 *b);
void _mutateNullRange(FUZZER_OBJECT *fuzzer, UCHAR *blob, UINT32 start, UINT32 end);
void _mutateRangeSpecial(FUZZER_OBJECT *fuzzer, UCHAR *blob, UINT32 start, UINT32 end);
void _mutateUnNullRange(FUZZER_OBJECT *fuzzer, UCHAR *blob, UINT32 start, UINT32 end);
void _mutateRangeRandom(FUZZER_OBJECT *fuzzer, UCHAR *blob, UINT32 start, UINT32 end);
void _mutateBitFlipping(FUZZER_OBJECT *fuzzer, UCHAR *blob, UINT32 start, UINT32 end);
void _singleBitFlipping(FUZZER_OBJECT *fuzzer, UCHAR *blob, UINT32 start, UINT32 end);
//BOOL FuzzDeallocateMemory(FUZZER_OBJECT *fuzzer, PVOID allocation, UINT size, BOOL virtualAllocated);

void CreateFuzzerObject(FUZZER_OBJECT **fuzzer, UINT32 seed, BOOL FuzzGenerate, BOOL FuzzMutate);
void DestroyFuzzerObject(FUZZER_OBJECT *fuzzer);

void FuzzBlob(FUZZER_OBJECT *fuzzer, UCHAR *blob, UINT32 size);
unsigned int get_fuzzy_len(FUZZER_OBJECT *fuzzer, unsigned int max);
int genInt(FUZZER_OBJECT *fuzzer, unsigned long long *qp);
unsigned int getOffset(FUZZER_OBJECT *fuzzer, UINT size, UINT SpaceNeeded, BOOLEAN *error);
unsigned char getCharDelta(FUZZER_OBJECT *fuzzer);
unsigned short getWordDelta(FUZZER_OBJECT *fuzzer);
unsigned int getDwordDelta(FUZZER_OBJECT *fuzzer);
unsigned long long getQwordDelta(FUZZER_OBJECT *fuzzer);
unsigned char mutateBit(FUZZER_OBJECT *fuzzer, unsigned char b);
unsigned char mutateBit(FUZZER_OBJECT *fuzzer, unsigned char b);
unsigned short mutateWord(FUZZER_OBJECT *fuzzer, unsigned short w);
unsigned int mutateDword(FUZZER_OBJECT *fuzzer, unsigned int dw);
unsigned long long mutateQword(FUZZER_OBJECT *fuzzer, unsigned long long qw);

#endif



