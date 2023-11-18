#include "Graph.hpp"

Graph::Graph() {}

Graph::~Graph() {
    for (auto &ptr : vertices) {
        delete ptr;
    }
}

void Graph::addVertex(std::string label) {
    vert *new_vert = new vert(label);
    vertices.push_back(new_vert);
    lmap.insert(std::pair<std::string, vert *>(label, new_vert));
}

void Graph::removeVertex(std::string label) {
    vert *ptr_label = lmap.at(label);

    for (DoubleList<edge *>::Iterator ptr = ptr_label->edges.begin();
         ptr != ptr_label->edges.end();
         ++ptr) {
        (*ptr)->label_ptr->edges.deleteNode(label);
    }
    delete ptr_label;
    std::swap(*vertices.begin(), *(vertices.end() - 1));
    vertices.pop_back();
}

void Graph::addEdge(std::string   label1,
                    std::string   label2,
                    unsigned long weight) {
    vert *ptr_label1 = lmap.at(label1);
    vert *ptr_label2 = lmap.at(label2);

    edge *new_edge1 = new edge(weight, ptr_label2);
    edge *new_edge2 = new edge(weight, ptr_label1);

    ptr_label1->edges.pushBack(new_edge1);
    ptr_label2->edges.pushBack(new_edge2);
}

void Graph::removeEdge(std::string label1, std::string label2) {
    vert *ptr_label1 = lmap.at(label1);
    vert *ptr_label2 = lmap.at(label2);

    ptr_label1->edges.deleteNode(label2);
    ptr_label2->edges.deleteNode(label1);
}

unsigned long Graph::shortestPath(std::string               startLabel,
                                  std::string               endLabel,
                                  std::vector<std::string> &path) {
    vert *ptr_start = lmap.at(startLabel);
    vert *ptr_end   = lmap.at(endLabel);
    path.resize(vertices.size());

    unsigned long distance = 0;

    HeapQueue<vert *, compare> Heap;
    Heap.insert(ptr_start);
    ptr_start->visited  = true;
    ptr_start->distance = 0;
    while (!Heap.empty() && ptr_start != ptr_end) {
        ptr_start = Heap.min();
        Heap.removeMin();
        for (auto ptr = ptr_start->edges.begin(); ptr != ptr_start->edges.end();
             ++ptr) {
            if ((*ptr)->label_ptr->distance >
                (*ptr)->weight + ptr_start->distance) {
                (*ptr)->label_ptr->distance =
                    (*ptr)->weight + ptr_start->distance;
                (*ptr)->label_ptr->predecessor = ptr_start;
            }
            if ((*ptr)->label_ptr->visited == false) {
                Heap.insert((*ptr)->label_ptr);
                (*ptr)->label_ptr->visited = true;
            }
        }
    }
    distance            = ptr_start->distance;
    std::size_t counter = 0;
    while (ptr_start != nullptr) {
        path.push_back(ptr_start->label);
        ptr_start = ptr_start->predecessor;
        ++counter;
    }
    std::reverse(path.begin(), path.end());
    path.resize(counter);

    // Reset the values:
    reset();

    return distance;
}

void Graph::print() const {
    for (std::vector<vert *>::const_iterator ptrV = vertices.begin();
         ptrV != vertices.end();
         ptrV++) {
        if ((*ptrV)->visited) {
            std::cout << std::endl;
            std::cout << (*ptrV)->label << std::endl;
            std::cout << " ---- Distance: " << (*ptrV)->distance << std::endl;

            if (!(*ptrV)->edges.isEmpty()) {
                for (DoubleList<edge *>::Iterator ptr1 = (*ptrV)->edges.begin();
                     ptr1 != (*ptrV)->edges.end();
                     ++ptr1) {
                    std::cout << ":    " << (*ptrV)->label << " to "
                              << (*ptr1)->label_ptr->label << std::endl
                              << " Weight: " << (*ptr1)->weight << std::endl;
                }
            }
        }
    }
}

void Graph::reset() {
    for (auto &ptr : vertices) {
        ptr->visited     = false;
        ptr->distance    = ULONG_MAX;
        ptr->predecessor = nullptr;
    }
}

/*
int main() {
    Graph g;
    for (char a = 'a'; a <= 'z'; a++) {
        std::string s = std::string(1, a);
        g.addVertex(s);
    }
    std::vector<std::string> gpath;
    struct EdgeStruct {
        std::string   a;
        std::string   b;
        unsigned long w;
    };

    std::vector<std::string> vertices1{"1", "2", "3", "4", "5", "6"};
    std::vector<EdgeStruct>  edges1{
         {"1", "2", 7},
         {"1", "3", 9},
         {"1", "6", 14},
         {"2", "3", 10},
         {"2", "4", 15},
         {"3", "4", 11},
         {"3", "6", 2},
         {"4", "5", 6},
         {"5", "6", 9},
    };
    // Adding the new set of edges
    for (const auto &label : vertices1)
        g.addVertex(label);
    for (const auto &e : edges1)
        g.addEdge(e.a, e.b, e.w);

    std::cout << std::endl;
    std::cout << std::endl << g.shortestPath("1", "5", gpath) << std::endl;
    g.print();
    for (auto a : gpath) {
        std::cout << a << ", " << std::flush;
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
*/
