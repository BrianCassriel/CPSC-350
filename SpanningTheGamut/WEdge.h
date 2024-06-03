// WEdge Class Header & Implementation
// Created by Brian Cassriel on 12/5/23.
// Represents a weighted edge in a WGraph. The weight is of type T.
// Provides useful overloaded operators for comparison.

#ifndef SPANNINGTHEGAMUT_WEDGE_H
#define SPANNINGTHEGAMUT_WEDGE_H

template<typename T>
class WEdge {
public:
    int vertex1;
    int vertex2;
    T weight;
    WEdge();
    WEdge(int vertex1, int vertex2, T weight);
};

/** Constructor
 * Initializes the WEdge with default values
 */
template<typename T>
WEdge<T>::WEdge() {
    this->vertex1 = 0;
    this->vertex2 = 0;
    this->weight = 0;
}

/** Overloaded Constructor
 * Initializes the WEdge with the given values
 * @param vertex1, vertex2 - the vertices that the edge connects
 * @param weight - the weight of the edge
 */
template<typename T>
WEdge<T>::WEdge(int vertex1, int vertex2, T weight) {
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->weight = weight;
}

/** Equality operator overload
 * @param left - the left WEdge
 * @param right - the right WEdge
 * @return bool - true if the edges are equal, false otherwise
 */
template<typename T>
bool operator==(const WEdge<T>& left, const WEdge<T>& right) {
    return (left.vertex1 == right.vertex1 && left.vertex2 == right.vertex2
           || left.vertex1 == right.vertex2 && left.vertex2 == right.vertex1)
           && left.weight == right.weight;
}

/** Less than operator overload
 * Has several cases to ensure that the same edge is not added twice to a std::set
 * @param left - the left WEdge
 * @param right - the right WEdge
 * @return bool - true if the left WEdge is less than the right WEdge, false otherwise
 */
template<typename T>
bool operator<(const WEdge<T>& left, const WEdge<T>& right) {
    if ((left.vertex1 == right.vertex1 && left.vertex2 == right.vertex2)
    || (left.vertex1 == right.vertex2 && left.vertex2 == right.vertex1)) {
        return left.weight < right.weight;
    }
    if (std::min(left.vertex1, left.vertex2) != std::min(right.vertex1, right.vertex2)) {
        return std::min(left.vertex1, left.vertex2) < std::min(right.vertex1, right.vertex2);
    }
    return std::max(left.vertex1, left.vertex2) < std::max(right.vertex1, right.vertex2);
}


#endif //SPANNINGTHEGAMUT_WEDGE_H
