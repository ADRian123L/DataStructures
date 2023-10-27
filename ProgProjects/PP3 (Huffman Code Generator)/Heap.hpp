#ifndef HEAP_H
#define HEAP_H

#include <vector>

// Tree
template <typename T>
class CompleteTree {
public:
    CompleteTree(size_t size) : _size(size) {}
    CompleteTree() : _size(0) {}

    typedef typename std::vector<T>::iterator Position;

    void   push_last(T &val);
    void   del_last();
    size_t size() const;
    void   swap(Position &a, Position &b);

    Position &parent(Position &index) const;
    Position &root() const;
    Position &last() const;
    Position &rchild(Position &index) const { return get(2 * index + 2); }
    Position &child(Position &index) const { return get(2 * index + 1); }

    bool isRight(const Position &index) const;
    bool isLeft(const Position &index) const;

private:
    std::vector<T> tree; // Concrete data structure

    size_t _size;

    class compare {
    public:
        compare(bool _isLeass = true) : isLess(_isLeass) {}
        bool operator()(const T &n1, const T &n2) const {
            return isLess ? n2 > n1 : false;
        }

    private:
        bool isLess;
    };
};

template <typename T>
void CompleteTree<T>::push_last(T &val) {
    tree.push_back(val);
    ++_size;
}

template <typename T>
void CompleteTree<T>::del_last() {
    tree.pop_back();
    --_size;
}

template <typename T>
size_t CompleteTree<T>::size() const {
    return _size;
}

template <typename T>
void CompleteTree<T>::swap(Position &a, Position &b) {
    std::swap(a, b);
}

template <typename T>
Position &CompleteTree<T>::Parent(Position &index) const {}

// heap
template <typename T, typename C>
class heap {
public:
    void   insert(T &vala);
    void   minD();
    T     &getMin() const { return tree.get(0); }
    size_t size() const { return tree.size(); }

private:
    CompleteTree<T> tree;
    C               isLess;
};

template <typename T, typename C>
void heap<T, C>::insert(T &val) {
    tree.push(val);
    tree<T> c;
    if (isLess(tree.get(size() - 1), tree.get(size() - 1).paren())) {
        swap(
    }
}
#endif
