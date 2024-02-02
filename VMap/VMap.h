#pragma once

#include <iostream>
#include <vector>

//Template so that we can make this a generic class 
template <typename K, typename V>
class VMap {
    //Not a member of the class but can access private methods and variables
    friend std::ostream& operator<<(std::ostream& os, const VMap<K, V>& map) {
        map.printInOrderHelper(os, map.root);
        return os;
    }

private:
    //For each node in the BST. Has key, value, and left and right children.
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        Node(K key, V value) : key(key), value(value), left(nullptr), right(nullptr) {}
    };
    //Root node and size of map
    Node* root;
    int _size;

    //Helper for printing out the map
    void printInOrderHelper(std::ostream& os, Node* node) const {
        //Base case - if it is empty do nothing
        if (!node) return;
        //Recursively traverse the tree and print out the key and value in the specified format
        printInOrderHelper(os, node->left);
        os << node->key << ": " << node->value << ", ";
        printInOrderHelper(os, node->right);
    }

    //Helper for BST visualizer
    void printTreeHelper(Node* node, int depth) const {
        if (!node) return;
        //Print right subtree first (with increased depth)
        printTreeHelper(node->right, depth + 1);
        //Print current node with indentation based on depth
        std::string indent(depth * 4, ' '); //4 spaces per depth level for indentation
        std::cout << indent << node->key << std::endl;
        //Print left subtree (with increased depth)
        printTreeHelper(node->left, depth + 1);
    }

    void getKeySetHelper(Node* node, std::vector<K>& keys) const {
        if (!node) return;
        getKeySetHelper(node->left, keys);
        keys.push_back(node->key);
        getKeySetHelper(node->right, keys);
    }

    void getValueSetHelper(Node* node, std::vector<V>& values) const {
        if (!node) return;
        getValueSetHelper(node->left, values);
        values.push_back(node->value);
        getValueSetHelper(node->right, values);
    }

    //Helper for getting key by value
    void getKeyHelper(Node* node, V value, std::vector<K>& keys) const {
        if (!node) return;
        getKeyHelper(node->left, value, keys); //Traverse left subtree
        if (node->value == value) {
            //Add key to the list if value matches
            keys.push_back(node->key); 
        }
        //Traverse right subtree
        getKeyHelper(node->right, value, keys);
    }

    //Helper for clearing map
    void clearHelper(Node* node) {
        if (!node) return;
        clearHelper(node->left);
        clearHelper(node->right);
        //Delete the node after its children have been deleted
        delete node;
    }

public:
    //Constructor creates map with empty key, value and size of 0 using member initializer lists 
    VMap() : root(nullptr), _size(0) {}

    //Destructor for freeing memory
    ~VMap()
    {
        clear();
    }

    //To visualize the binary search tree created with the current entries
    void printTree()
    {
        printTreeHelper(root, 0);
    }



    //Append function (adds entry to map)
    void put(K key, V value)
    {
        //Temporary copy to iteratively navigate the tree
        Node** current = &root;
        //Traverse the BST to reach the end using the information of the key
        while (*current) {
            //Check if the key is less than the key in the current tree
            if (key < (*current)->key)
                current = &((*current)->left); //Navigate to the the left child
            //Do the opposite if the key is greater
            else if (key > (*current)->key)
                current = &((*current)->right);
            else {
                (*current)->value = value; //Replace value if key exists
                return;
            }
        }
        //Now create the node and increment size 
        *current = new Node(key, value);
        _size++;
    }


    //Retrieve value from key
    V* get(K key) {
        Node* current = root;
        //Traverse binary tree

        while (current) {
            //Attempt to locate the key
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else
                return &(current->value); //Found - return a pointer to the value
        }
        //Key not found
        return nullptr;
    }

    //Retrieve key from value
    K* getKey(V value) {
        //Possible keys
        std::vector<K> keys;
        getKeyHelper(root, value, keys);
        if (!keys.empty()) {
            return new K(keys.front()); //Return a pointer to the first key found
        }
        //If no key with the given value was found
        return nullptr; 
    }


    //Remove entry given key
    void remove(K key) {
        Node* parent = nullptr;
        Node* current = root;
        //Locate item to remove
        while (current != nullptr && current->key != key) {
            parent = current;
            if (key < current->key) current = current->left;
            else current = current->right;
        }

        //Key not found, just return
        if (current == nullptr) return;

        //Case 1: Removing a node with no children or one child
        Node* replacement = nullptr;
        if (current->left && current->right) {
            //Case 3: Node has two children
            //Find inorder successor (smallest in the right subtree)
            Node* successorParent = current;
            Node* successor = current->right;
            while (successor->left) {
                successorParent = successor;
                successor = successor->left;
            }

            if (successorParent != current) successorParent->left = successor->right;
            else successorParent->right = successor->right;
            //Copy successor's key and value to current node
            current->key = successor->key; 
            current->value = successor->value;
            //Node to be deleted is now the successor
            current = successor; 
        }
        else {
            //One child or no child
            replacement = current->left ? current->left : current->right;

            if (!parent) {
                //Node is the root
                root = replacement;
            }
            else {
                if (parent->left == current) parent->left = replacement;
                else parent->right = replacement;
            }
        }
        //Free the memory
        delete current;
    }



    //Returns the list of keys in the map
    std::vector<K> getKeySet() {
        std::vector<K> keySet;
        getKeySetHelper(root, keySet);
        return keySet;
    }

    //Returns the list of values in the map
    std::vector<V> getValueSet() {
        std::vector<V> values;
        getValueSetHelper(root, values);
        return values; 
    }


    //Returns size of map
    int size() const { return _size; }
    //Is the size is 0 then it is empty
    bool isEmpty() const { return _size == 0; }

    //Remove all elements of the map
    void clear() 
    {
        clearHelper(root);
        root = nullptr;
    }
};

//Overloading the << operator for printing the map
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const VMap<K, V>& map)
{
    map.printInOrderHelper(os, map.root);
    return os;
}
