#include "rivercrossing.h"


Node::Node()
{}


RiverCrossing::RiverCrossing()
{
    Node *tempNode = new Node();
    tempNode->combination.set();
    tempNode->bank = 1;
    tempNode->gValue = 0;
    tempNode->fValue = tempNode->gValue + tempNode->combination.count();
    priorityQueue.push(tempNode);
    for(auto &v: hashTable)
    {
        v = -1;
    }
    hashTable[(int)(tempNode->combination.to_ulong())] = (int)(tempNode->combination.to_ulong());
}


void RiverCrossing::start()
{
    Node *tempNode;
    bitset<TOTAL_NUMBER_OF_PEOPLE> tempCombination;
    while (!priorityQueue.empty())
    {
        tempNode = priorityQueue.top();
        cout<<"\nPopped from queue : "<<tempNode->combination<<", hValue, gValue : "
           <<tempNode->combination.count() - 1<<", "<<tempNode->gValue;
        priorityQueue.pop();
        cout<<"\nQueue Size after Popping : "<<priorityQueue.size();
        cout<<"\nBank : "<<tempNode->bank;
        if(tempNode->combination[F] == tempNode->bank)
        {
            cout<<"\nFather is on Bank,Boat : "<<tempNode->bank<<","
               <<tempNode->combination[B]<<" with combination : ";
            for(int i = F; i<= P; i++)
            {
                if(tempNode->combination[i] == tempNode->bank)
                {
                    tempCombination = tempNode->combination;
                    tempCombination[F] = tempNode->bank*-1 + 1;
                    tempCombination[i] = tempNode->bank*-1 + 1;
                    tempCombination[B] = tempNode->combination[B]*-1 + 1;
                    if(tempCombination.count() == 0)
                    {
                        cout<<"\nGoal State Reached with : "<<tempCombination;
                        isAlreadyInHashTable(tempCombination, tempNode);
                        printTrace();
                        cout<<"\n\n";
                        exit(0);
                    }
                    cout<<tempCombination<<", ";
                    if(!isAlreadyInHashTable(tempCombination, tempNode) && constraintFilter(tempCombination))
                    {
                        cout<<" Consistent and do not exist in Hash Table";
                        addToQueue(tempCombination, tempNode);
                    }
                }
            }
        }
        if(tempNode->combination[M] == tempNode->bank)
        {
            cout<<"\nMother is on Bank,Boat : "<<tempNode->bank<<","
               <<tempNode->combination[B]<<" with combination : ";
            for(int i = F; i<= P; i++)
            {
                if(tempNode->combination[i] == tempNode->bank)
                {
                    tempCombination = tempNode->combination;
                    tempCombination[M] = tempNode->bank*-1 + 1;
                    tempCombination[i] = tempNode->bank*-1 + 1;
                    tempCombination[B] = tempNode->combination[B]*-1 + 1;
                    if(tempCombination.count() == 0)
                    {
                        cout<<"\nGoal State Reached with : "<<tempCombination;
                        isAlreadyInHashTable(tempCombination, tempNode);
                        printTrace();
                        cout<<"\n\n";
                        exit(0);
                    }
                    cout<<tempCombination<<", ";
                    if(!isAlreadyInHashTable(tempCombination, tempNode) && constraintFilter(tempCombination))
                    {
                        cout<<" Consistent and do not exist in Hash Table";
                        addToQueue(tempCombination, tempNode);
                    }
                }
            }
        }
        if(tempNode->combination[G] == tempNode->bank)
        {
            cout<<"\nGaurd is on Bank, Boat : "<<tempNode->bank<<","
               <<tempNode->combination[B]<<" with combination : ";
            for(int i = F; i<= P; i++)
            {
                if(tempNode->combination[i] == tempNode->bank)
                {
                    tempCombination = tempNode->combination;
                    tempCombination[G] = tempNode->bank*-1 + 1;
                    tempCombination[i] = tempNode->bank*-1 + 1;
                    tempCombination[B] = tempNode->combination[B]*-1 + 1;
                    if(tempCombination.count() == 0)
                    {
                        cout<<"\nGoal State Reached with : "<<tempCombination;
                        isAlreadyInHashTable(tempCombination, tempNode);
                        printTrace();
                        cout<<"\n\n";
                        exit(0);
                    }
                    cout<<tempCombination<<", ";
                    if(!isAlreadyInHashTable(tempCombination, tempNode) && constraintFilter(tempCombination))
                    {
                        cout<<" Consistent and do not exist in Hash Table";
                        addToQueue(tempCombination, tempNode);
                    }
                }
            }
        }
    }
}


bool RiverCrossing::addToQueue(bitset<TOTAL_NUMBER_OF_PEOPLE> tempCombination, Node *tempNode)
{
    Node *newNode = new Node();
    newNode->gValue = tempNode->gValue + 1;
    newNode->fValue = tempCombination.count() - 1 + newNode->gValue;
    newNode->combination = tempCombination;
    newNode->bank = tempNode->bank*-1 + 1;
    cout<<"\nAdded to queue : "<<tempCombination<<", fValue : "<<newNode->fValue;
    priorityQueue.push(newNode);
    cout<<"\nQueue Size = "<<priorityQueue.size()<<"\n";
    return true;
}


bool RiverCrossing::isAlreadyInHashTable(bitset<TOTAL_NUMBER_OF_PEOPLE> combination, Node *tempNode)
{
    if(hashTable[(int)(combination.to_ulong())] != -1)
        return true;
    else
    {
        hashTable[(int)(combination.to_ulong())] = (int)(tempNode->combination.to_ulong());
        return false;
    }
}


bool RiverCrossing::constraintFilter(bitset<TOTAL_NUMBER_OF_PEOPLE> combination)
{
    //(M xor F) -> (D1 xor F) and (D2 xor F)
    if(
        (!(!combination[M] && combination[F]) &&
         !(combination[M] && !combination[F])) ||
            (
                (
                    (!combination[D1] && combination[F]) ||
                    (combination[D1] && !combination[F])
                ) &&
                (
                    (!combination[D2] && combination[F]) ||
                    (combination[D2] && !combination[F])
                )
            )
      )
    {// and
        //(M xor F) -> (S1 xor M) and (S2 xor M)
        if(
            (!(!combination[M] && combination[F]) &&
             !(combination[M] && !combination[F])) ||
                (
                    (
                        (!combination[S1] && combination[M]) ||
                        (combination[S1] && !combination[M])
                    ) &&
                    (
                        (!combination[S2] && combination[M]) ||
                        (combination[S2] && !combination[M])
                    )
                )
          )
        {//and
            //P xor G
            if(
                    (!(
                        (!combination[P] && combination[G]) ||
                        (combination[P] && !combination[G])
                    ))
              )
            {
                return 1;
            } //P is not with gaurd or the family, i.e. alone on the bank
            else if(
                        ((!combination[P] && combination[M]) ||
                        (combination[P] && !combination[M])) &&
                        ((!combination[P] && combination[F]) ||
                        (combination[P] && !combination[F])) &&
                        ((!combination[P] && combination[S1]) ||
                        (combination[P] && !combination[S1])) &&
                        ((!combination[P] && combination[S2]) ||
                        (combination[P] && !combination[S2])) &&
                        ((!combination[P] && combination[D1]) ||
                        (combination[P] && !combination[D1])) &&
                        ((!combination[P] && combination[D2]) ||
                        (combination[P] && !combination[D2]))
                   )
            {
                return 1;
            }
        }
    }
    return 0;
}


void RiverCrossing::printTrace()
{
    cout<<"\n\nTrace : ";
    int traceInteger = 0;
    cout<<bitset<TOTAL_NUMBER_OF_PEOPLE>(traceInteger).to_string()<<" , ";
    while(traceInteger != (int)(pow(2, TOTAL_NUMBER_OF_PEOPLE) - 1))
    {
        traceInteger = hashTable[traceInteger];
        cout<<bitset<TOTAL_NUMBER_OF_PEOPLE>(traceInteger).to_string()<<" , ";
    }
}
