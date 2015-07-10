#ifndef WEIGHTEDQUICKUNIONUF_H
#define WEIGHTEDQUICKUNIONUF_H

#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class WeightedQuickUnionUF {
    private:
        int *parent;   // parent[i] = parent of i
        int *size;     // size[i] = number of objects in subtree rooted at i
        int COUNT;      // number of components
        int N;
        unordered_map<int, list<int> > connectedComponents;
        void validate(int p);

    public:
        WeightedQuickUnionUF(int N);
        int count();
        int ufFind(int p);
        void ufUnion(int p, int q);
        bool ufConnected(int p, int q);
        unordered_map<int, list<int> > getComponents();

        void printComponents();
};

#endif // WEIGHTEDQUICKUNIONUF_H
