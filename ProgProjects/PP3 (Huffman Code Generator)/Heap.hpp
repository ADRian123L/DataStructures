#ifndef HEAP_H
#define HEAP_H

#include <vector>

// Tree
template <typename T>
class CompleteTree {
public:
    CompleteTree() : tree() {}

    typedef typename std::vector<T>::iterator Position;

    void push_last(T &val);
    void del_last();
    int  size() const;
    void swap(const Position &a, const Position &b);

    Position parent(Position &index) {
        return pos(std::floor((indx(index) - 1) / 2));
    }
    Position root() { return pos(0); }
    Position last() { return pos(size() - 1); }
    Position rchild(const Position &index) { return pos(2 * indx(index) + 2); }
    Position lchild(const Position &index) { return pos(2 * indx(index) + 1); }

    bool isRight(const Position &index) const {
        return (tree.size() >= 2 * indx(index) + 2);
    }

    bool isLeft(const Position &index) const {
        return tree.size() >= 2 * indx(index) + 1;
    }
    bool isRoot(const Position &index) const { return (tree.begin() == index); }

private:
    Position pos(int index) { return tree.begin() + index; }
    int      indx(Position index) const { return index - tree.begin(); }

    std::vector<T> tree; // Concrete data structure
};

class compare {
public:
    compare(bool _isLeass = true) : isLess(_isLeass) {}
    bool operator()(const int &n1, const int &n2) const {
        return isLess ? n2 > n1 : false;
    }

private:
    bool isLess;
};

template <typename T>
void CompleteTree<T>::push_last(T &val) {
    tree.push_back(val);
}

template <typename T>
void CompleteTree<T>::del_last() {
    tree.pop_back();
}

template <typename T>
int CompleteTree<T>::size() const {
    return tree.size();
}

template <typename T>
void CompleteTree<T>::swap(const Position &a, const Position &b) {
    T tmp = *a;
    *a    = *b;
    *b    = tmp;
}

// heap
template <typename T, typename C>
class heap {
public:
    heap() : tree(CompleteTree<T>()) {}
    void insert(T &vala);
    void pop();
    T   &getMin();
    int  size() const;
    bool empty() const;

private:
    CompleteTree<T> tree;
    C               isLess;

    typedef typename CompleteTree<T>::Position Position;
};

template <typename T, typename C>
bool heap<T, C>::empty() const {
    return size() == 0;
}

template <typename T, typename C>
int heap<T, C>::size() const {
    return tree.size();
}

template <typename T, typename C>
T &heap<T, C>::getMin() {
    return *(tree.root());
}

template <typename T, typename C>
void heap<T, C>::insert(T &val) {
    tree.push_last(val);            // Insert the element to the end of the tree
    Position element = tree.last(); // Get iterator for the element
    while (!tree.isRoot(element) &&
           isLess(*element, *tree.parent(element))) { // Up Heap
        tree.swap(element, tree.parent(element));
        element = tree.parent(element);
    }
}

template <typename T, typename C>
void heap<T, C>::pop() {
    if (size() < 1) {
        throw std::out_of_range("The heap is empty");
    }
    // Swap the last and first (root) elements
    tree.swap(tree.root(), tree.last());
    // Delete the last element:
    tree.del_last();
    // Dow heap
    Position element = tree.root();
    while (tree.isLeft(element)) {
        if (tree.isRight(element) &&
            isLess(*tree.lchild(element), *tree.rchild(element))) {
            tree.swap(element, tree.lchild(element));
            element = tree.lchild(element);
        }
        else if (tree.isRight(element) &&
                 isLess(*tree.rchild(element), *tree.lchild(element))) {
            tree.swap(element, tree.rchild(element));
            element = tree.rchild(element);
        }
        else if (isLess(*tree.lchild(element), *element)) {
            tree.swap(element, tree.lchild(element));
            element = tree.lchild(element);
        }
        else {
            break;
        }
    }
}

#endif
