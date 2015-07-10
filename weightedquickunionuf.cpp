#include "weightedquickunionuf.h"

WeightedQuickUnionUF::WeightedQuickUnionUF(int N) {
        this->COUNT = N;
        this->N = N;
        this->parent = new int[N];
        this->size = new int[N];
        for (int i = 0; i < N; i++) {
            this->parent[i] = i;
            this->size[i] = 1;
        }
    }

    int WeightedQuickUnionUF::count() {
        return this->COUNT;
    }


    int WeightedQuickUnionUF::ufFind(int p) {
        this->validate(p);
        while (p != this->parent[p])
            p = this->parent[p];
        return p;
    }

    // validate that p is a valid index
    void WeightedQuickUnionUF::validate(int p) {
        //int N = ((int[])this->parent).length;
        if (p < 0 || p >= this->N) {
            throw std::invalid_argument("index is out of bound");
        }
    }

    bool WeightedQuickUnionUF::ufConnected(int p, int q) {
        return this->ufFind(p) == this->ufFind(q);
    }


    void WeightedQuickUnionUF::ufUnion(int p, int q) {
        int rootP = this->ufFind(p);
        int rootQ = this->ufFind(q);
        if (rootP == rootQ) return;

        // make smaller root point to larger one
        if (this->size[rootP] < this->size[rootQ]) {
            this->parent[rootP] = rootQ;
            this->size[rootQ] += size[rootP];
        }
        else {
            this->parent[rootQ] = rootP;
            this->size[rootP] += size[rootQ];
        }
        this->COUNT--;
    }

    unordered_map<int, list<int> > WeightedQuickUnionUF::getComponents() {
        cout << this->connectedComponents.size() << " components" << endl;
        this->connectedComponents.clear();

        for (int i = 0; i < this->N; i++) {
            int root = this->ufFind(i);
            auto pointer = this->connectedComponents.find(root);
            if (pointer == this->connectedComponents.end()) {
                //TODO insert new list
                list<int> *connectedElements = new list<int>();
                connectedElements->push_back(i);
                pair<int, list<int> > *rootMapping = new pair<int, list<int> >(root, *connectedElements);
                this->connectedComponents.insert(*rootMapping);
            } else { // insert into existing list
                pointer->second.push_back(i);
            }
        }
        cout << this->connectedComponents.size() << " components" << endl;
        return this->connectedComponents;
    }

    void WeightedQuickUnionUF::printComponents() {
        for (auto it = this->connectedComponents.begin(); it != this->connectedComponents.end(); ++it) {
            cout << "size : " << (it->second).size() << " ";
            cout << "component: ";
            for (list<int>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2) {
                cout << *it2 << " ";
            }
            cout << endl;
        }
    }
