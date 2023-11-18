#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include "HeapQueue.hpp"
#include "list.hpp"
#include <algorithm>
#include <iostream>
#include <map>

struct vert; // Struct declaration

struct edge {
    unsigned long weight;
    vert         *label_ptr;
    edge(unsigned long _w, vert *_label) : weight(_w), label_ptr(_label) {}
};

struct vert {
    std::string        label;
    DoubleList<edge *> edges;
    bool               visited;
    unsigned long      distance;
    vert              *predecessor;
    vert(std::string l)
        : label(l), visited(false), distance(ULONG_MAX), predecessor(nullptr) {}
};

class Graph : public GraphBase {
public:
    void          addVertex(std::string label) override;
    void          removeVertex(std::string label) override;
    void          addEdge(std::string   label1,
                          std::string   label2,
                          unsigned long weight) override;
    void          removeEdge(std::string label1, std::string label2) override;
    unsigned long shortestPath(std::string               startLabe,
                               std::string               endLabel,
                               std::vector<std::string> &path) override;

    // Helper functions:
    void print() const;

private:
    std::vector<vert *>           vertices;
    std::map<std::string, vert *> lmap;
};

class compare {
public:
    compare(bool lessThan = true) : lessThan(lessThan){};
    bool operator()(const vert *&n1, const vert *&n2) const {
        return lessThan ? n2->distance > n1->distance
                        : n2->distance <= n1->distance;
    }
    bool operator()(const vert *n1, const vert *n2) const {

        return lessThan ? n2->distance > n1->distance
                        : n2->distance <= n1->distance;
    }

private:
    bool lessThan;
};

#endif // GRAPH_H
