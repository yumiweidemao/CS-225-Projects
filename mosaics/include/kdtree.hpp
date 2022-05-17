/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim])
      return true;
    else if (first[curDim] > second[curDim])
      return false;
    else
      return (first < second);
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double pot_target = 0;
    double target_best = 0;
    for (int d = 0; d < Dim; d++) {
      pot_target += (potential[d] - target[d]) * (potential[d] - target[d]);
      target_best += (target[d] - currentBest[d]) * (target[d] - currentBest[d]);
    }
    if (pot_target < target_best) {
      return true;
    }
    if (pot_target == target_best && potential < currentBest) {
      return true;
    }
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    // call constructor helper function
    build_tree(newPoints, this->root, 0);
    this->size = newPoints.size();
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  _copy(other->root, this->root);
  this->size = other->size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (&rhs != this) {
    _destroy(this->root);
    _copy(rhs->root, this->root);
    this->size = rhs->size;
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _destroy(this->root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> currBest;
    for (int i = 0; i < Dim; i++) {
      currBest[i] = -666; // sentinel
    }
    _find(query, &currBest, this->root, 0);
    return currBest;
}

// quickselect functions

// swap function: swap two points in a vector, pass by reference
template <int Dim>
void swap(vector<Point<Dim>> & points, int i, int j) {
  Point<Dim> temp = points[i];
  points[i] = points[j];
  points[j] = temp;
}

// partition function: partition a vector using the given pivotindex, pass by reference
template <int Dim>
int partition(vector<Point<Dim>> & points, int left, int right, int pivot, int d) {
  Point<Dim> pivotPoint = points[pivot];
  swap(points, pivot, right);
  int storeIndex = left;
  for (int i = left; i < right; i++) {
    if (points[i][d] < pivotPoint[d]) {
      swap(points, storeIndex, i);
      storeIndex++;
    } else if (points[i][d] == pivotPoint[d]) {
      // use built-in operator <
      if (points[i] < pivotPoint) {
        swap(points, storeIndex, i);
        storeIndex++;
      }
    }
  }
  swap(points, right, storeIndex);
  return storeIndex;
}

// quickselect function: select the kth smallest element, pass by value
template <int Dim>
Point<Dim> quickselect(vector<Point<Dim>> & points, int left, int right, int k, int d) {
  if (left == right) {
    return points[left];
  }
  int pivot = (left + right) / 2;
  pivot = partition(points, left, right, pivot, d);
  if (k == pivot) {
    return points[k];
  } else if (k < pivot) {
    return quickselect(points, left, pivot-1, k, d);
  } else {
    return quickselect(points, pivot+1, right, k, d);
  }
  return Point<Dim>();
}

// vector slicing function
template <int Dim>
vector<Point<Dim>> slice(const vector<Point<Dim>> & v, int start, int end) {
  auto s = v.begin() + start;
  auto e = v.begin() + end + 1;
  vector<Point<Dim>> vect(s, e);
  return vect;
}

// constructor helper function
template <int Dim>
void KDTree<Dim>::build_tree(vector<Point<Dim>> points, KDTreeNode *& root, int d) {
  // base case: points is empty
  if (points.empty()) {
    root = NULL;
    return;
  }
  // find the median of points
  int right = points.size() - 1;
  int k = right / 2; // index of median
  Point<Dim> median = quickselect(points, 0, right, k, d);
  // now points[k] should be median
  root = new KDTreeNode(median);
  // recurse on left & right subtrees
  auto left_sub = slice(points, 0, k-1);
  auto right_sub = slice(points, k+1, right);
  build_tree(left_sub, root->left, (d+1)%Dim);
  build_tree(right_sub, root->right, (d+1)%Dim);
  return;
}

// copy helper function
template <int Dim>
void KDTree<Dim>::_copy(const KDTreeNode *& other, KDTreeNode *& curr) {
  if (other == NULL) {
    return;
  }
  curr = new KDTreeNode(other->point);
  _copy(other->left, curr->left);
  _copy(other->right, curr->right);
}

// destroy helper function
template <int Dim>
void KDTree<Dim>::_destroy(KDTreeNode *& root) {
  if (root == NULL) {
    return;
  }
  _destroy(root->left);
  _destroy(root->right);
  delete root;
  root = NULL;
}

// find nearest neighbor helper function
template <int Dim>
Point<Dim> * KDTree<Dim>::_find(const Point<Dim> & query, Point<Dim> * currBest, KDTreeNode * currNode, int d) const {
  if (currNode == NULL) {
    return currBest;
  }
  if (currNode->point[d] < query[d] || (currNode->point[d] == query[d] && currNode->point < query)) {
    // go right
    _find(query, currBest, currNode->right, (d+1)%Dim);
    // update currBest
    if (shouldReplace(query, *currBest, currNode->point)) {
      *currBest = currNode->point;
    }
    // if within best radius, also go left
    double bestRadius = getDistance(*currBest, query);
    double dist;
    dist = query[d] - currNode->point[d];
    dist = dist > 0 ? dist : (-dist);
    if (dist <= bestRadius) {
      _find(query, currBest, currNode->left, (d+1)%Dim);
    }
  } else if (currNode->point[d] > query[d] || (currNode->point[d] == query[d] && currNode->point > query)) {
    // go left
    _find(query, currBest, currNode->left, (d+1)%Dim);
    // update currBest
    if (shouldReplace(query, *currBest, currNode->point)) {
      *currBest = currNode->point;
    }
    // if within best radius, also go right
    double bestRadius = getDistance(*currBest, query);
    double dist;
    dist = query[d] - currNode->point[d];
    dist = dist > 0 ? dist : (-dist);
    if (dist <= bestRadius) {
      _find(query, currBest, currNode->right, (d+1)%Dim);
    }
  }
  return currBest;
}

// get distance function
template <int Dim>
double getDistance(const Point<Dim> & p1, const Point<Dim> & p2) {
  double dist = 0;
  for (int i = 0; i < Dim; i++) {
    dist += (p1[i] - p2[i]) * (p1[i] - p2[i]);
  }
  dist = std::pow(dist, 0.5);
  return dist;
}
