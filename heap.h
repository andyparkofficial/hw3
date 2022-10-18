#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heap_;
  void trickleUp(unsigned int loc);
  void heapify(unsigned int loc);
  PComparator compare;
  int m_ary;
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c){
  m_ary = m;
  compare = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty!");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty!");

  }
  heap_[0] = heap_.back();
  heap_.pop_back();
  heapify(0);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  heap_.push_back(item);
  if (size()>1){
    trickleUp(size()-1);
  }
  
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  if (heap_.size() == 0) {
    return true;
  } else {
    return false;
  }
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return heap_.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(unsigned int loc){
  unsigned int parent = (loc-1)/m_ary;
  bool parentIsZero = false;
  while(!parentIsZero && compare(heap_[loc], heap_[parent]) )
  { 
  if (parent == 0){ // this is to make sure the while loop doesn't repeat multiple times when parent is 0.
    parentIsZero = true;
  }
  std::swap(heap_[parent], heap_[loc]);

  loc = parent;
  parent = (loc-1)/m_ary;
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(unsigned int loc){
  if(!(m_ary*loc+1 <= size())) return; // if leaf node; if left child does not exist
  unsigned int smallerChild = m_ary*loc+1; // start w/ left
  
  
  for (unsigned int i = smallerChild+1; i <= m_ary*loc+m_ary; i++){
    if (i <= size()-1){
      if(compare(heap_[i], heap_[smallerChild])){
      smallerChild = i;
      }
    }
  }
  if(compare(heap_[smallerChild], heap_[loc])){
    std::swap(heap_[loc], heap_[smallerChild]);
    heapify(smallerChild);
  }
}



#endif

