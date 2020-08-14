#include<iostream>
#include<fstream>
#include<string.h>
#include "defn.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include <sstream>

/*
    Definitions for all functions used in storm.cpp
*/
int getNumLines(std::ifstream &file);

int hashTableSize(int size);

int hashFunction(int eventId, int tableSize);

bool TestForPrime(int val);

void findEvent(hash_table_entry** arr, annual_storms* arr2, int event_i, int hashS, int inputNum, int lines);

void summary(hash_table_entry** hashT, int hashS);

void printDetails(annual_storms* arr2, int arrI, int eventI);

void findMaxFatality(int number, std::string year, int* size, annual_storms* arr, int numYears, std::string type);

void findMax(int number, std::string year, int* size, annual_storms* arr, int numYears, std::string type);

std::pair<int, int>* buildArr(int year, annual_storms* arr, int* size, int numYears, std::string type);

void heapSort(std::pair<int, int>* arr, int n);

std::pair<int, int> extractMax(std::pair<int, int>* arr, int n);

void printArr(std::pair<int, int>* arr, int n);

int PARENT(int i);

int LEFT(int i);

int RIGHT(int i);

void MAXHEAPIFY(std::pair<int, int>* arr, int i, int n);

void BUILDMAXHEAP(std::pair<int, int>* arr, int n);

void range(std::string year, std::string field, std::string low, std::string high, int* size, int numYears, annual_storms* arr);