//
// Created by tanny on 7/12/2020.
//

#include <vector>
using namespace std;

template <class K,class V>
class NodeT{
public:
    /* Attribute: Key (Template Type)
     * The key stored in the tree node
     * */
    K key;

    /* Attribute: Value (Template Type)
     * The value stored in the tree node
     * */
    V value;

    /* Attribute: Left Child
     * NodeT pointer to the left child
     * */
    NodeT *left;

    /* Attribute: Right Child
     * NodeT pointer to the right child
     * */
    NodeT *right;

    /* Attribute: Parent Node
     * NodeT pointer to the parent
     * */
    NodeT *parent;

    /* Attribute: isBlack
     * The colour of the node, either black or red but represented as a bool that is true if the node is blac
     * */
    bool isBlack;

    /* Constructor
     * POST:Sets the key and value to its two template type parameters, pointers to null, and isBlack to false
     * */
    NodeT(K key, V value) : key(key), value(value), left(nullptr), right(nullptr),parent(nullptr), isBlack(false){};

    /* Constructor
     * POST:Sets the key,value and isBlack to its three template type parameters, pointers to null
     * */
    NodeT(K key, V value, bool isBlack) : key(key),value(value),left(nullptr), right(nullptr),parent(nullptr),isBlack(isBlack){};
};


template <class K,class V>
class RedBlackTree{
public:
    /* Default Constructor
     * POST:Creates an empty tree whose root is a null pointer
     * */
    RedBlackTree();

    /* Copy Constructor
     * POST:A constructor that creates a deep copy of its RedBlackTree reference parameter
     * */
    RedBlackTree(const RedBlackTree<K,V> &rbTree);

    /* Operator = – Overloads
     * PARAM: The tree which whose nodes will be deeply copied if it is not exactly the current tree
     * POST:Deeply copies the nodes of RedBlackTree reference parameter into the calling object and returns a reference to the calling
     * object after de-allocating any dynamic memory associated with the original contents of the calling object; if the calling object is the same as the parameter the operator will not copy it
     * */
    RedBlackTree<K,V> & operator=(const RedBlackTree<K,V> &rbTree);

    /* Destructor
     * POST: Deletes dynamic memory allocated by the tree
     * */
    ~RedBlackTree();

    /* Insert Node (With  Red Black Tree Properties Preserved)
     * PARAM: The key and value which need to be constructed into a new nodes, then insert into the tree
     * POST: Insert the new created node with the key and value provided(if the key is not duplicate in the tree)
     *       and return a feedback of whether the insertion is successfully done or not.
     * */
    bool insert(K key, V value);

    /* Remove A Node
     * PARAM: The key which need to be searched in the tree, if found, delete it.
     * POST: Delete the node which contains the key(from parameter),if successfully found and deleted, return true, otherwise, return false.
     * */
    bool remove(K key);

    /* Search for a Node
     * POST: Search for the node which contains the key in the parameter and return true if found.
     * */
    bool search(K key) const;

    /* Search for the value in a specific range
     * PARAM: Two keys in the parameter are provided to construct a range for the searching task(both endpoints are included)
     * POST: Return the values of nodes whose keys are falling into the range(in ascending order of the keys).
     * */
    vector<V> search(K firstKey, K secondKey) const; // template

    /* The Whole Values of A Tree
     * POST:  returns a vector that contains all of the values in the tree(in ascending order of the keys)
     * */
    vector<V> values() const; // template

    /* All Keys of A Tree
     * POST: Returns a vector that contains all of the keys in the tree(in ascending order)
     * */
    vector<K> keys() const; // template

    /* The Quantity of Nodes In A Tree
     * POST: Return the quantity of a tree's nodes.
     * */
    int size() const;

    /* The Tree Root
     * POST: Returns a pointer to the tree's root node.
     * */
    NodeT<K,V>* getRoot () const;

private:
    /* Attribute: The Root of the Tree
     * */
    NodeT<K,V> * root;

    /* Attribute: The Quantity of the Nodes in the Tree
     * */
    int nodeQuantity;

    /* Copy A Subtree
     * PARAM: The head node of the subtree which will be copied
     * POST:  Insert the elements of a subtree into current tree(Preorder)
     * */
    void copyAndInsert(const NodeT<K,V> *nd);

    /* Left Rotate
     * PARAM: The head node of the subtree which need to be left rotated
     * POST: Left rotate a subtree
     * */
    void leftRotate(NodeT<K,V> * nd);

    /* Right Rotate
     * PARAM: The head node of the subtree which need to be right rotated
     * POST: Right rotate a subtree
     * */
    void rightRotate(NodeT<K,V> * nd);

    /* Get the Successor of Target Node
     * PARAM: 1.target - the node of which need to be found
     *        2.sParent - The parent of the successor(record the value in the reference parameter)
     * POST: Return the Successor of the target node in the 1st parameter
     *       (The successor of a node who has no right child is defined as itself in this function)
     * */
    NodeT<K,V> *getSuccessor(NodeT<K,V> *target, NodeT<K,V> *&sParent) const;

    /* Regular BST Node Insert
     * PARAM: Tree node which need to be insert
     * POST: 1.Regular BST node insertion and sent back feedback of whether the insertion is successful or not
     *       2.Will not insert duplicate key.
     * */
    bool bstInsertWithoutDuplicateKey(NodeT<K,V> *newNode);

    /* Regular BST Node Insert(Will Create New Node Inside)
     * PARAM: The key, value and color which are provided to construct a new node to be inserted.
     * POST: 1.Regular BST node insertion and sent back feedback of whether the insertion is successful or not
     *       2.Will not insert duplicate key.
     * */
    bool bstCreateNodeAndInsertWithoutDuplicateKey(K key,V value,bool isBlack);

    /* Search for a Node
     * POST: Search for the node which contains the key in the parameter and return it back if found.
     * */
    NodeT<K,V> *searchAndReturnNode(K key) const;

    /* Collect Valid Values
     * PARAM: current - The starting node.
     *        rangeStart and rangeEnd - the definition of the targeted range
     *        valueContainer - The container which will take the valid value back
     * POST:  Collect the valid value recursively
     * */
    void inOrderTraverseAndCollectValidData(NodeT<K,V> *current, K rangeStart, K rangeEnd, vector<V> &valueContainer)const;

    /* Collect All Values
     * PARAM: current - The starting node.
     *        valueContainer - The container which will take the valid value back
     * POST:  Collect all the value recursively
     * */
    void inOrderTraverseAndCollectAllData(NodeT<K,V> *current, vector<V> &valueContainer)const;

    /* Collect All Keys
     * PARAM: current - The starting node.
     *        valueContainer - The container which will take the keys back
     * POST:  Collect all the keys recursively
     * */
    void inOrderTraverseAndCollectAllKeys(NodeT<K,V> *current, vector<K> &keyContainer)const;

    /* Fix The Tree to Make it Keep the Properties of A Red Black Tree
     * PARAM: 1.child - The original non-null child node of the removed node  2. childparent - the parent of the child nodes(1st parameter)
     *        3.isLeftChildOfParent - whether the first parameter is the left node of its parent  4.childIsBlack - color of the first paremeter
     * POST: By doing the re-coloring or tree rotation to maintain the properties of the red black tree(if necessary)
     * */
    void rbRemoveFix(NodeT<K,V> *child, NodeT<K,V> *childParent, bool isLeftChildOfParent, bool childIsBlack);

    /* Empty()
     * POST: Return a feedback of whether the tree is empty or not
     * */
    bool empty() const;

    /* Clear Subtree
     * PARAM: The root node of the subtree which needs to be deleted.
     * POST: Removes all nodes from subtree, and deallocate dynamic memory
     * */
    void clear(NodeT<K,V> *nd);
};


/* Default Constructor
 * POST:Creates an empty tree whose root is a null pointer
 * */
template <class K,class V>
RedBlackTree<K,V>::RedBlackTree() {
    nodeQuantity = 0;
    root = nullptr;
}


/* Copy Constructor
 * POST:A constructor that creates a deep copy of its RedBlackTree reference parameter
 * */
template <class K,class V>
RedBlackTree<K,V>::RedBlackTree(const RedBlackTree<K,V> &rbTree){
    root = nullptr;
    nodeQuantity = 0;
    copyAndInsert(rbTree.root);
}


/* Operator = – Overloads
 * PARAM: The tree which whose nodes will be deeply copied if it is not exactly the current tree
 * POST:Deeply copies the nodes of RedBlackTree reference parameter into the calling object and returns a reference to the calling
 * object after de-allocating any dynamic memory associated with the original contents of the calling object; if the calling object is the same as the parameter the operator will not copy it
 * */
template <class K,class V>
RedBlackTree<K,V> & RedBlackTree<K,V>::operator=(const RedBlackTree<K,V> &rbTree) {
    if (this != &rbTree) {
        clear(root);
        root = nullptr;
        nodeQuantity = 0;
        copyAndInsert(rbTree.root);
    }
    return *this;
}


/* Destructor
 * POST: Deletes dynamic memory allocated by the tree
 * */
template <class K,class V>
RedBlackTree<K,V>::~RedBlackTree(){
    clear(root);
    root = nullptr;
}


/* Insert Node (With  Red Black Tree Properties Preserved)
 * PARAM: The key and value which need to be constructed into a new nodes, then insert into the tree
 * POST: Insert the new created node with the key and value provided(if the key is not duplicate in the tree)
 *       and return a feedback of whether the insertion is successfully done or not.
 * */
template <class K,class V>
bool RedBlackTree<K,V>::insert(K key, V value)  {
    NodeT<K,V> *newNode = new NodeT<K,V>(key, value);
    //nodeQuantity will increase in bstInsert, DO NOT -1 TWICE
    if(!bstInsertWithoutDuplicateKey(newNode)){
        delete newNode;
        newNode = nullptr;
        return false;
    };

    //isBlack initialized as 'false' - red(root must be black)
    while (newNode != root && !newNode->parent->isBlack){
        //1. parent is the left child of grandparent
        if(newNode->parent == newNode->parent->parent->left){
            // p is red, then there must exist a grandpa who is black
            NodeT<K,V>* uncle = newNode->parent->parent->right;
            //1.1 uncle is red,simply recoloring
            if((uncle != nullptr) && (!uncle->isBlack)){
                newNode->parent->isBlack = true;
                uncle->isBlack = true;
                newNode->parent->parent->isBlack = false;
                newNode = newNode->parent->parent;
            }
                //1.2 uncle is black or uncle is null
            else{
                //1.2.1 new node is rightChild
                if(newNode == newNode->parent->right){
                    newNode = newNode->parent;
                    leftRotate(newNode);
                }
                newNode->parent->isBlack = true;
                newNode->parent->parent->isBlack = false;
                rightRotate(newNode->parent->parent);
            }
        }
            //2. parent is the right child of grandparent
        else{
            NodeT<K,V>* uncle = newNode->parent->parent->left;
            //2.1 uncle is red
            if((uncle!= nullptr) && (!uncle->isBlack)){
                newNode->parent->isBlack = true;
                uncle->isBlack = true;
                newNode->parent->parent->isBlack = false;
                newNode = newNode->parent->parent;
            }
                //2.2 uncle is black or null
            else{
                if(newNode == newNode->parent->left){
                    newNode = newNode->parent;
                    rightRotate(newNode);
                }
                newNode->parent->isBlack = true;
                newNode->parent->parent->isBlack = false;
                leftRotate(newNode->parent->parent);
            }
        }
    }
    root->isBlack = true;
    return true;
}


/* Remove A Node
 * PARAM: The key which need to be searched in the tree, if found, delete it.
 * POST: Delete the node which contains the key(from parameter),if successfully found and deleted, return true, otherwise, return false.
 * */
template <class K,class V>
bool RedBlackTree<K,V>::remove(K key) {
    NodeT<K,V>* target = searchAndReturnNode(key);
    // 1. Target is not in the tree
    if (target == nullptr){
        return false;
    }

    // realTarget is the one which will be finally removed, it is not necessarily the target itself. can be pre or successor
    NodeT<K,V>* realTarget = nullptr;
    NodeT<K,V>* parentOfRealTarget = nullptr;
    bool realTargetIsLeftChild = true;

    NodeT<K,V>* onlyChildOfRealTarget = nullptr;
    // target has one or has no child, delete itself
    if (target->left == nullptr || target->right == nullptr){
        realTarget = target;
    }
        // target has two child -> has to get successor to replace it and delete successor
    else{
        NodeT<K,V>* successorParent = nullptr;
        NodeT<K,V>* successor = getSuccessor(target, successorParent);
        realTarget = successor;
    }
    //last if..else -- is to ensure that realTarget should have only one child
    //Locate realTarget's children and arrange them to be sons of their grandparent
    if(realTarget->left != nullptr){
        onlyChildOfRealTarget = realTarget->left;
    }else{
        onlyChildOfRealTarget = realTarget->right;
    }
    if(onlyChildOfRealTarget != nullptr){
        onlyChildOfRealTarget->parent = realTarget->parent;
    }
    // realTarget is the root
    parentOfRealTarget = realTarget->parent;
    if(realTarget->parent == nullptr){
        root = onlyChildOfRealTarget;
    } else{
        // Attach onlyChildOfRealTarget to its grandParent
        if(realTarget == realTarget->parent->left){
            realTarget->parent->left = onlyChildOfRealTarget;
            realTargetIsLeftChild = true;
        }else{
            realTarget->parent->right = onlyChildOfRealTarget;
            realTargetIsLeftChild = false;
        }
    }
    //replace original target with realTarget
    if(realTarget != target){
        target->key = realTarget->key;
        target->value = realTarget->value;
    }
    // Note that onlyChildOfRealTarget could be null
    // if go through the following line, target must not be null
    bool OriginalRealTargetColorIsBlack = realTarget->isBlack;

    if(OriginalRealTargetColorIsBlack){
        bool childIsBlack = true; // if child is null
        if(onlyChildOfRealTarget){
            childIsBlack = onlyChildOfRealTarget->isBlack;
        }
        rbRemoveFix(onlyChildOfRealTarget,parentOfRealTarget,realTargetIsLeftChild,childIsBlack);
    }
    delete realTarget;
    nodeQuantity -- ;
    return true;
}


/* Search for a Node
 * POST: Search for the node which contains the key in the parameter and return true if found.
 * */
template <class K,class V>
bool RedBlackTree<K,V>::search(K key) const {
    NodeT<K,V>* current = root;
    //parent = nullptr;
    while (current != nullptr){
        if (key ==  current -> key){
            //return current;
            return true;
        }
        //parent = current;
        if (key < current -> key){
            current = current -> left;
        }else{
            current = current -> right;
        }
    }
    return false;
}


/* Search for the value in a specific range
 * PARAM: Two keys in the parameter are provided to construct a range for the searching task(both endpoints are included)
 * POST: Return the values of nodes whose keys are falling into the range(in ascending order of the keys).
 * */
template <class K,class V>
vector<V> RedBlackTree<K,V>::search(K firstKey, K secondKey) const {
    NodeT<K,V>* current = root;
    vector<V> valueContainer ;
    K rangeStart;
    K rangeEnd;
    if(firstKey < secondKey){
        rangeStart = firstKey;
        rangeEnd = secondKey;
    }else{
        rangeStart = secondKey;
        rangeEnd = firstKey;
    }
    inOrderTraverseAndCollectValidData(current,rangeStart,rangeEnd,valueContainer);
    return valueContainer;
}


/* The Whole Values of A Tree
 * POST:  returns a vector that contains all of the values in the tree(in ascending order of the keys)
 * */
template <class K,class V>
vector<V> RedBlackTree<K,V>::values() const {
    NodeT<K,V>* current = root;
    vector<V> valueContainer ;
    inOrderTraverseAndCollectAllData(current,valueContainer);
    return valueContainer;

}


/* All Keys of A Tree
 * POST: Returns a vector that contains all of the keys in the tree(in ascending order)
 * */
template <class K,class V>
vector<K> RedBlackTree<K,V>::keys() const {
    NodeT<K,V>* current = root;
    vector<K> keyContainer ;
    inOrderTraverseAndCollectAllKeys(current,keyContainer);
    return keyContainer;
}


/* The Quantity of Nodes In A Tree
 * POST: Return the quantity of a tree's nodes.
 * */
template <class K,class V>
int RedBlackTree<K,V>::size() const {
    return nodeQuantity;
}


/* The Tree Root
 * POST: Returns a pointer to the tree's root node.
 * */
template <class K,class V>
NodeT<K,V>* RedBlackTree<K,V>::getRoot () const {
    return root;
}


/* Copy A Subtree
 * PARAM: The head node of the subtree which will be copied
 * POST:  Insert the elements of a subtree into current tree(Preorder)
 * */
template <class K,class V>
void RedBlackTree<K,V>::copyAndInsert(const NodeT<K,V> *nd){
    if (nd != nullptr){
        bstCreateNodeAndInsertWithoutDuplicateKey(nd->key, nd->value, nd->isBlack);
        copyAndInsert(nd->left);
        copyAndInsert(nd->right);
    }
}


/* Left Rotate
 * PARAM: The head node of the subtree which need to be left rotated
 * POST: Left rotate a subtree
 * */
template <class K,class V>
void RedBlackTree<K,V>::leftRotate(NodeT<K,V> * nd){
    NodeT<K,V> * rightChild = nd->right;
    nd->right = rightChild->left;

    if (rightChild->left != nullptr){
        rightChild->left->parent = nd;
    }
    rightChild->parent = nd->parent;
    if (nd->parent == nullptr){
        root = rightChild;
    }
    else if (nd == nd->parent->left) {
        nd->parent->left = rightChild;
    }
    else {
        nd->parent->right = rightChild;
    }
    rightChild->left = nd;
    nd->parent = rightChild;
}


/* Right Rotate
 * PARAM: The head node of the subtree which need to be right rotated
 * POST: Right rotate a subtree
 * */
template <class K,class V>
void RedBlackTree<K,V>::rightRotate(NodeT<K,V> * nd){
    NodeT<K,V> * leftChild = nd->left;
    nd->left = leftChild->right;
    if (leftChild->right != nullptr){
        leftChild->right->parent = nd;
    }
    leftChild->parent = nd->parent;
    if (nd->parent == nullptr){
        root = leftChild;
    }
    else if (nd == nd->parent->left) {
        nd->parent->left = leftChild;
    }
    else {
        nd->parent->right = leftChild;
    }
    leftChild->right = nd;
    nd->parent = leftChild;
}


/* Get the Successor of Target Node
 * PARAM: 1.target - the node of which need to be found
 *        2.sParent - The parent of the successor(record the value in the reference parameter)
 * POST: Return the Successor of the target node in the 1st parameter
 *       (The successor of a node who has no right child is defined as itself in this function)
 * */
template <class K,class V>
NodeT<K,V>* RedBlackTree<K,V>::getSuccessor(NodeT<K,V> *target, NodeT<K,V> *&sParent) const {
    // Successor is the left most node of the right sub-tree
    if(target == nullptr){
        //cout<<"successor error!"<<endl;
        return nullptr;
    }
    NodeT<K,V>* current = target -> right;
    if(current == nullptr){
        return current;
    }
    sParent = target;
    while(current -> left != nullptr){
        sParent = current;
        current = current -> left;
    }
    return current;
}


/* Regular BST Node Insert
 * PARAM: Tree node which need to be insert
 * POST: 1.Regular BST node insertion and sent back feedback of whether the insertion is successful or not
 *       2.Will not insert duplicate key.
 * */
template <class K,class V>
bool RedBlackTree<K,V>::bstInsertWithoutDuplicateKey(NodeT<K,V> *newNode){
    //This function does simple insertion, No new node will be created inside!
    //newNode is a single node without parent and children by default
    NodeT<K,V>* parent = root;
    NodeT<K,V>* next = root;
    if (empty()) {
        root = newNode;
    }
    else {
        // Find parent of new node
        while (next != nullptr) {
            parent = next;
            if (newNode->key < parent->key) {
                next = parent->left;
            }
            else if(newNode->key > parent->key) {
                next = parent->right;
            }else{
                //There is a same key, insertion failed
                return false;
            }
        }
        // Insert new node
        if (newNode->key < parent->key) {
            parent->left = newNode;
            newNode->parent = parent;
        }
        else {
            parent->right = newNode;
            newNode->parent = parent;
        }
    }
    ++nodeQuantity;
    return true;
}


/* Regular BST Node Insert(Will Create New Node Inside)
 * PARAM: The key, value and color which are provided to construct a new node to be inserted.
 * POST: 1.Regular BST node insertion and sent back feedback of whether the insertion is successful or not
 *       2.Will not insert duplicate key.
 * */
template <class K,class V>
bool RedBlackTree<K,V>::bstCreateNodeAndInsertWithoutDuplicateKey(K key,V value,bool isBlack){
    NodeT<K,V>* newNode = new NodeT<K,V>(key,value,isBlack);
    return bstInsertWithoutDuplicateKey(newNode);
}


/* Search for a Node
 * POST: Search for the node which contains the key in the parameter and return it back if found.
 * */
template <class K,class V>
NodeT<K,V>* RedBlackTree<K,V>::searchAndReturnNode(K key) const{
    NodeT<K,V>* current = root;
    //parent = nullptr;
    while (current != nullptr){
        if (key ==  current -> key){
            return current;
        }
        //parent = current;
        if (key < current -> key){
            current = current -> left;
        }else{
            current = current -> right;
        }
    }
    // if the above line is gone through, then nothing found --
    // Parent might be the position whose left or right child position can be inserted.
    return current;
}


/* Collect Valid Values
 * PARAM: current - The starting node.
 *        rangeStart and rangeEnd - the definition of the targeted range
 *        valueContainer - The container which will take the valid value back
 * POST:  Collect the valid value recursively
 * */
template <class K,class V>
void RedBlackTree<K,V>::inOrderTraverseAndCollectValidData(NodeT<K,V> *current, K rangeStart, K rangeEnd, vector<V> &valueContainer)const{
    if(current != nullptr){
        inOrderTraverseAndCollectValidData(current->left,rangeStart,rangeEnd,valueContainer);
        if (current->key >= rangeStart && current->key <= rangeEnd){
            valueContainer.push_back(current->value);
        }
        inOrderTraverseAndCollectValidData(current->right,rangeStart,rangeEnd,valueContainer);
    }
}


/* Collect All Values
 * PARAM: current - The starting node.
 *        valueContainer - The container which will take the valid value back
 * POST:  Collect all the value recursively
 * */
template <class K,class V>
void RedBlackTree<K,V>::inOrderTraverseAndCollectAllData(NodeT<K,V> *current, vector<V> &valueContainer)const{
    if(current != nullptr){
        inOrderTraverseAndCollectAllData(current->left,valueContainer);
        valueContainer.push_back(current->value);
        inOrderTraverseAndCollectAllData(current->right,valueContainer);
    }
}


/* Collect All Keys
 * PARAM: current - The starting node.
 *        valueContainer - The container which will take the keys back
 * POST:  Collect all the keys recursively
 * */
template <class K,class V>
void RedBlackTree<K,V>::inOrderTraverseAndCollectAllKeys(NodeT<K,V> *current, vector<K> &keyContainer)const{
    if(current != nullptr){
        inOrderTraverseAndCollectAllKeys(current->left,keyContainer);
        keyContainer.push_back(current->key);
        inOrderTraverseAndCollectAllKeys(current->right,keyContainer);
    }
}


/* Fix The Tree to Make it Keep the Properties of A Red Black Tree
 * PARAM: 1.child - The original non-null child node of the removed node  2. childparent - the parent of the child nodes(1st parameter)
 *        3.isLeftChildOfParent - whether the first parameter is the left node of its parent  4.childIsBlack - color of the first paremeter
 * POST: By doing the re-coloring or tree rotation to maintain the properties of the red black tree(if necessary)
 * */
template <class K,class V>
void RedBlackTree<K,V>::rbRemoveFix(NodeT<K,V> *child, NodeT<K,V> *childParent, bool isLeftChildOfParent, bool childIsBlack){
    //1. if root == child = null
    if (root == nullptr){
        return;
    }
    //2. if root == child != null simply run child->isBlack = true; in the last line
    if(root == child && child != nullptr){
        child->isBlack = true;
        return;
    }
    //in 3 and 4, child has a parent and has a silbing.
    //3. if root != child and child is null
    //4. if root != child and child is not null
    if (!childParent){
        //cout<<"ERROR! CHILDPARENT IS NULL!"<<endl;
    }
    //target is black and has a parent
    NodeT<K,V> * sibling = nullptr;

    //1.child is not root and its color is black
    while (child != root and childIsBlack== true){
        //target is not root and not null, which means its parent must NOT be null
        //1.node is the left child
        if(isLeftChildOfParent){
            sibling = childParent->right;
            //1.1 sibling is red
            if(sibling->isBlack == false){
                sibling->isBlack = true;
                childParent->isBlack = false;
                leftRotate(childParent);
                sibling = childParent->right;
            }
            bool siblingLeftChildIsBlack = (sibling->left)?(sibling->left->isBlack):true;
            bool siblingRightChildIsBlack = (sibling->right)?(sibling->right->isBlack):true;

            //1.2 sibling's left and right child are both black
            if (siblingLeftChildIsBlack && siblingRightChildIsBlack){
                sibling->isBlack = false;
                child = childParent;
            }
            else{
                //1.3 sibling's right child is black but left child is not
                if (siblingRightChildIsBlack){
                    if(sibling->left){
                        sibling->left->isBlack = true;
                    }
                    sibling->isBlack = false;
                    rightRotate(sibling);
                    sibling = childParent->right;
                }
                sibling->isBlack = childParent->isBlack;
                childParent->isBlack = true;
                if(sibling->right){
                    sibling->right->isBlack = true;
                }
                leftRotate(childParent);
                child = root;
            }
            childIsBlack = child->isBlack;
        }
            //2.node is the right child
        else{
            sibling = childParent->left;//
            if(sibling->isBlack == false){
                sibling->isBlack = true;
                childParent->isBlack = false;
                rightRotate(childParent);//
                sibling = childParent->left;//
            }
            bool siblingLeftChildIsBlack = (sibling->left)?(sibling->left->isBlack):true;
            bool siblingRightChildIsBlack = (sibling->right)?(sibling->right->isBlack):true;
            if (siblingLeftChildIsBlack && siblingRightChildIsBlack){
                sibling->isBlack = false;
                child = childParent;
            }
            else{
                if (siblingLeftChildIsBlack){//
                    if(sibling->right){
                        sibling->right->isBlack = true;
                    }
                    sibling->isBlack = false;
                    leftRotate(sibling);//
                    sibling = childParent->left;//
                }
                sibling->isBlack = childParent->isBlack;
                childParent->isBlack = true;
                if(sibling->left){
                    sibling->left->isBlack = true;
                }
                rightRotate(childParent);//
                child = root;
            }
            childIsBlack = child->isBlack;
        }
    }
    if(child){
        child->isBlack = true;
    }
}


/* Empty()
 * POST: Return a feedback of whether the tree is empty or not
 * */
template <class K,class V>
bool RedBlackTree<K,V>::empty() const{
    return root == nullptr;
}


/* Clear Subtree
 * PARAM: The root node of the subtree which needs to be deleted.
 * POST: Removes all nodes from subtree, and deallocate dynamic memory
 * */
template <class K,class V>
void RedBlackTree<K,V>::clear(NodeT<K,V> *nd){
    if (nd != nullptr) {
        clear(nd->left);
        clear(nd->right);
        delete nd;
        --nodeQuantity;
    }
}



