#ifndef RIVERCROSSING_H
#define RIVERCROSSING_H

#include <iostream>
#include <bitset>
#include <queue>
#include <string>
#include <list>
#include <math.h>

#define TOTAL_NUMBER_OF_PEOPLE 9    //People are 8, +1 is the boat

using namespace std;

class Node
{
public:
    Node();
    bitset<TOTAL_NUMBER_OF_PEOPLE> combination;
    int fValue;
    int gValue;
    bool bank;
    int parentHashValue;
    //We don't need and hValue here as the count of
    //number of ones is what the hValue is
};


struct CompareFValue {
    bool operator()(Node *e1, Node *e2)
    {
        //Sorting in ascending order based on ending time
        if(e1->fValue == e2->fValue)
            return e1->combination.to_ulong() > e1->combination.to_ulong();
        return e1->fValue > e2->fValue;
    }
};


class RiverCrossing
{
public:
    RiverCrossing();
    enum People
    {
        F = 0,
        M = 1,
        G = 2,
        S1 = 3,
        S2 = 4,
        D1 = 5,
        D2 = 6,
        P = 7,
        B = 8
    };
    priority_queue<Node*, vector<Node*>, CompareFValue> priorityQueue;
    int hashTable [(int)(pow(2, TOTAL_NUMBER_OF_PEOPLE) - 1)];
    bool constraintFilter(bitset<TOTAL_NUMBER_OF_PEOPLE>);
    void start();
    bool isAlreadyInHashTable(bitset<TOTAL_NUMBER_OF_PEOPLE>, Node*);
    bool addToQueue(bitset<TOTAL_NUMBER_OF_PEOPLE>, Node*);
    void printTrace();
};

#endif // RIVERCROSSING_H
