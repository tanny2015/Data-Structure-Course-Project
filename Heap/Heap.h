//
// Created by tanny on 7/29/2020.
//


#include <stdexcept>
#include <vector>
using std::vector;
using std::runtime_error;

template <class T>
class Heap {
public:
    /* Default Constructor
     * POST: Creates a Heap with an underlying array size equal to the integer parameter
     * */
    Heap(int size);

    /* Copy Constructor
     * PARAM: The Heap to be deeply copied into
     * POST: Creates a deep copy of its constant Heap reference parameter
     * */
    Heap(const Heap &hp);

    /* Destructor
     * POST: Deallocate dynamic memory allocated by the Heap
     * */
    ~Heap();

    /* Operator= Overload
     * PARAM: The Heap to be deeply copied into
     * POST: (Deep) Copies its constant Heap reference parameter into the calling object
     * and returns a reference to the calling object; Deallocate dynamic memory as necessary
     * and behaves appropriately under self-assignment
     * */
    Heap &operator=(const Heap &hp);

    /* Insert New Item
     * PARAM: The Item which is going to be inserted into the heap
     * POST: Inserts its template parameter in the heap, while maintaining the heap properties;
     *       If the Heap is full throws a runtime_error
     * */
    void insert(T newItem);

    /* Remove the root
     * POST: removes and returns the root, while maintaining the heap properties;
     *       If the Heap is empty throws a runtime_error
     * */
    T remove();

    /* Peek (Return Root Item)
     * POST:  Returns the root; If the Heap is empty throws a runtime_error
     * */
    T peek() const;

    /* Merge Two Heaps
     * PARAM: The Heap which will be merged.
     * POST: Returns a Heap object that contains the values in the calling object and its constant reference Heap parameter
     * */
    Heap merge(const Heap &hp) const;

    /* Quantity of items
     * POST: Returns the number of items stored in the Heap, as an int
     * */
    int size() const;

    /* Output the items of Heap in ascending order(FOR PART 2)
     * PARAM: Container of the result
     * POST: Output the items of Heap ascendingly.
     *       The result will be brought back by the parameter(vector reference)
     *       Note:(**)This method will change the structure of the Heap structure(involves item removal)
     *       It is not a good idea to handle in this way, but simply to satisfy the algorithm run time requirement
     * */
    void getItemsInAscendingOrder(vector<T> &items);

private:
    /* Attribute(array): The Container which consists of all the items in the Heap
     * */
    T *array;

    /* Attribute(quantityOfItems): The real quantity of the items stored in the array
     * */
    int quantityOfItems;

    /* Attribute(maxSize): The Maximum size of the array in this Heap
     * */
    int maxSize;

    /* Remove Heap
     * POST: Remove the whole contents in the heap and release dynamic memory allocated by the Heap
     * */
    void deleteHeap();

    /* Copy Heap(Deeply)
     * PRE: (**)Note:Before using this method, MUST clear all the content of the previous heap
     * PARAM: The Heap to be deeply copied into
     * POST: Remove the whole contents in the heap and release dynamic memory allocated by the Heap
     * */
    void copyHeap(const Heap &hp);

    /* BubbleUp (MaxHeap)
     * PARAM: The index from which it will be heapify from
     * POST: (Max)Heapify from bottom to top
     *       Applied after the insertion of a newItem into the Heap
     * */
    void bubbleUp(int index);

    /* BubbleDown (MaxHeap)
     * PARAM: The index from which it will be heapify from
     * POST: (Max)Heapify from top to bottom
     *       Applied after the removal of the root of the Heap
     * */
    void bubbleDown(int parentIndex);
};

/* Default Constructor
 * POST: Creates a Heap with an underlying array size equal to the integer parameter
 * */
template <class T>
Heap<T>::Heap(int size) {
    if (size < 1) {
        array = nullptr;
    } else {
        array = new T[size];
    }
    quantityOfItems = 0;
    maxSize = size;
}

/* Copy Constructor
 * PARAM: The Heap to be deeply copied into
 * POST: Creates a deep copy of its constant Heap reference parameter
 * */
template <class T>
Heap<T>::Heap(const Heap &hp) {
    copyHeap(hp);
}

/* Destructor
 * POST: Deallocate dynamic memory allocated by the Heap
 * */
template <class T>
Heap<T>::~Heap() {
    deleteHeap();
}

/* Remove Heap
 * POST: Remove the whole contents in the heap and release dynamic memory allocated by the Heap
 * */
template <class T>
void Heap<T>::deleteHeap() {
    if (array != nullptr) {
        delete[] array;
        array = nullptr;
        quantityOfItems = 0;
        maxSize = 0;
    }
}

/* Copy Heap(Deeply)
 * PRE: (**)Note:Before using this method, MUST clear all the content of the previous heap
 * PARAM: The Heap to be deeply copied into
 * POST: Remove the whole contents in the heap and release dynamic memory allocated by the Heap
 * */
template <class T>
void Heap<T>::copyHeap(const Heap &hp) {
    if (&hp != nullptr) {
        if (hp.array != nullptr && hp.maxSize > 0) {
            array = new T[hp.maxSize];
            for (int i = 0; i < hp.quantityOfItems; ++i) {
                array[i] = hp.array[i];
            }
        } else {
            array = nullptr;
        }
        quantityOfItems = hp.quantityOfItems;
        maxSize = hp.maxSize;
    }
}

/* Operator= Overload
 * PARAM: The Heap to be deeply copied into
 * POST: (Deep) Copies its constant Heap reference parameter into the calling object
 * and returns a reference to the calling object; Deallocate dynamic memory as necessary
 * and behaves appropriately under self-assignment
 * */
template <class T>
Heap<T> &Heap<T>::operator=(const Heap &hp) {
    if (&hp != this) {
        deleteHeap();
        copyHeap(hp);
    }
    return *this;
}

/* Insert New Item
 * PARAM: The Item which is going to be inserted into the heap
 * POST: Inserts its template parameter in the heap, while maintaining the heap properties;
 *       If the Heap is full throws a runtime_error
 * */
template <class T>
void Heap<T>::insert(T newItem) {
    if (quantityOfItems >= maxSize) {
        throw runtime_error("ERROR: HEAP IS FULL, NO MORE CAPACITY");
    }
    array[quantityOfItems] = newItem;
    bubbleUp(quantityOfItems);
    quantityOfItems++;
}

/* BubbleUp (MaxHeap)
 * PARAM: The index from which it will be heapify from
 * POST: (Max)Heapify from bottom to top
 *       Applied after the insertion of a newItem into the Heap
 * */
template <class T>
void Heap<T>::bubbleUp(int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && array[index] > array[parent]) {
        T temp = array[index];
        array[index] = array[parent];
        array[parent] = temp;
        bubbleUp(parent);
    }
}

/* Remove the root
 * POST: removes and returns the root, while maintaining the heap properties;
 *       If the Heap is empty throws a runtime_error
 * */
template <class T>
T Heap<T>::remove() {
    //if it is an empty heap, throws a runtime_error
    if (quantityOfItems < 1) {
        throw runtime_error("ERROR: EMPTY HEAP !!");
    }

    T root = array[0];
    array[0] = array[quantityOfItems - 1];
    bubbleDown(0);
    quantityOfItems--;
    return root;
}

/* BubbleDown (MaxHeap)
 * PARAM: The index from which it will be heapify from
 * POST: (Max)Heapify from top to bottom
 *       Applied after the removal of the root of the Heap
 * */
template <class T>
void Heap<T>::bubbleDown(int parentIndex) {
    int leftChildIndex = 2 * parentIndex + 1;
    int rightChildIndex = 2 * parentIndex + 2;

    bool hasLeftChild = leftChildIndex < quantityOfItems;
    bool hasRightChild = rightChildIndex < quantityOfItems;

    int indexOfMaxItemOfTriangular = parentIndex;
    if (hasLeftChild || hasRightChild) {
        if (hasLeftChild) {
            indexOfMaxItemOfTriangular = array[indexOfMaxItemOfTriangular] > array[leftChildIndex] ? indexOfMaxItemOfTriangular:leftChildIndex;
        }
        if (hasRightChild) {
            indexOfMaxItemOfTriangular = array[indexOfMaxItemOfTriangular] > array[rightChildIndex] ? indexOfMaxItemOfTriangular:rightChildIndex;
        }
        //swap
        if (indexOfMaxItemOfTriangular != parentIndex) {
            T temp = array[indexOfMaxItemOfTriangular];
            array[indexOfMaxItemOfTriangular] = array[parentIndex];
            array[parentIndex] = temp;
            bubbleDown(indexOfMaxItemOfTriangular);
        }
    }
}

/* Peek (Return Root Item)
 * POST:  Returns the root; If the Heap is empty throws a runtime_error
 * */
template <class T>
T Heap<T>::peek() const {
    //if it is an empty heap, throws a runtime_error
    if (quantityOfItems < 1) {
        throw runtime_error("EMPTY HEAP !!");
    }
    return array[0];
}

/* Merge Two Heaps
 * PARAM: The Heap which will be merged.
 * POST: Returns a Heap object that contains the values in the calling object and its constant reference Heap parameter
 * */
template <class T>
Heap<T> Heap<T>::merge(const Heap &hp) const {
    int quantityOfItemsInNewArray = quantityOfItems + hp.quantityOfItems;
    Heap newHeap = Heap(quantityOfItemsInNewArray); //maxSize has been assigned after this line

    if (quantityOfItemsInNewArray < 1) {
        return newHeap;
    }
    if (array != nullptr && quantityOfItems > 0) {
        for (int i = 0; i < quantityOfItems; ++i) {
            newHeap.insert(array[i]);
        }
    }
    if (hp.array != nullptr && hp.quantityOfItems > 0) {
        for (int j = 0; j < hp.quantityOfItems; ++j) {
            newHeap.insert(hp.array[j]);
        }
    }
    return newHeap;
}

/* Quantity of items
 * POST: Returns the number of items stored in the Heap, as an int
 * */
template <class T>
int Heap<T>::size() const {
    return quantityOfItems;
}

/* Output the items of Heap in ascending order(FOR PART 2)
 * PARAM: Container of the result
 * POST: Output the items of Heap ascendingly.
 *       The result will be brought back by the parameter(vector reference)
 *       Note:(**)This method will change the structure of the Heap structure(involves item removal)
 *       It is not a good idea to handle in this way, but simply to satisfy the algorithm run time requirement
 * */
template <class T>
void Heap<T>::getItemsInAscendingOrder(vector<T> &items) {
    int itemSize = quantityOfItems;
    for (int i = 0; i < itemSize; ++i) {
        //insert from the front of the container
        items.insert(items.begin(), remove());
    }
}

/* Output the smallest m th items in the vector(PART 2)
 * PARAM: 1. array(vector type): from which the mth smallest items should be returned
 *        2. m(int type)       : The quantity of smallest items we need to generate from the vector
 * POST: Return the smallest m th items in the vector(in ascending order).
 *       Note: 1. Final quantity of items which are needed to be return = Min(Size of Vector, m)
 *             2. This method uses an object of the heap template class
 *             3. This method will not sort the items in the vector parameter
 *             4. This method is not a Heap class method
 *             5. This method runs in at most O(n log m) time, where n is the size of the vector parameter
 * */
template <class T>
vector<T> smallestm(const vector<T> array, int m) {
    vector<T> smallestItems;
    if (m <= 0 || array.size() <= 0) {
        return smallestItems;
    }

    int heapSize = array.size() < m ? array.size() : m;
    Heap<T> heap = Heap<T>(heapSize);
    for (int i = 0; i < heapSize; ++i) {
        heap.insert(array[i]);
    }
    //Assuming those items in current heap are the smallest 'heapSize'th items
    //And now, if there are remaining items which are not inserted into the heap,
    //simply compare it with the max(root) items of current heap, if the remaining item
    //is smaller, then remove the root item then make this remaining item into the heap
    int remainingItemSize = array.size() - heapSize;
    if (remainingItemSize > 0) {
        for (int j = heapSize; j < array.size(); ++j) {
            //remaining item is smaller than the maximum item of the heap
            if (array[j] < heap.peek()) {
                //remove root
                heap.remove();
                //insert this new item and maintain heap property
                heap.insert(array[j]);
            }
        }
    }
    heap.getItemsInAscendingOrder(smallestItems);
    return smallestItems;
}



