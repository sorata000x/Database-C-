#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include <iostream>
#include <stack>
#include "btree_array_funcs.h"
#include "../stl_utils/vector_utilities.h"

using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator
    {
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T> *_it = NULL, int _key_ptr = 0) : it(_it), key_ptr(_key_ptr) {}

        T operator*()
        {
            //WENT THOUGH BASIC TEST
            //WENT THOUGH TESTB

            if (it)
                return it->data[key_ptr];
            return T(); //not sure about here
        }
        Iterator operator++(int un_used) //postfix
        {
            //NOT TESTED

            Iterator original(it, key_ptr);
            if (key_ptr < it->data_count - 1)
                key_ptr++;
            else if (it->next)
                it = it->next;
            return original;
        }
        Iterator operator++() //prefix
        {
            //WENT THOUGH BASIC TEST
            //WENT THOUGH TESTB

            if (key_ptr < it->data_count - 1)
                key_ptr++;
            else
            {
                it = it->next;
                key_ptr = 0;
            }
            return *this;
        }
        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            //WENT THOUGH BASIC TEST
            //WENT THOUGH TESTB

            return (lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr); //true if left == right
        }
        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            //WENT THOUGH BASIC TEST
            //WENT THOUGH TESTB

            return (lhs.it != rhs.it || lhs.key_ptr != rhs.key_ptr); //true if left != right
        }
        void print_Iterator()
        {
            //UNTOUCHED

            if (it)
            {
                cout << "iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else
            {
                cout << "iterator: NULL, key_ptr: " << key_ptr << endl;
            }
        }
        bool is_null() { return !it; } //UNTOUCHED
        void info()
        {
            //UNTOUCHED

            cout << endl
                 << "Iterator info:" << endl;
            cout << "key_ptr: " << key_ptr << endl;
            cout << "it: " << *it << endl;
        }

    private:
        BPlusTree<T> *it;
        int key_ptr;
    };

    BPlusTree(bool dups = false) : dups_ok(dups), data_count(0), child_count(0), next(NULL) {}
    BPlusTree(T *a, int size, bool dups = false) : dups_ok(dups), data_count(0), child_count(0), next(NULL)
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB
        assert(size >= 0);

        for (int i = 0; i < size; i++)
        {
            insert(a[i]);
        }
    }

    //big three:
    BPlusTree(const BPlusTree<T> &other) : dups_ok(other.dups_ok), data_count(0), child_count(0), next(NULL)
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB
        assert(empty());

        copy_tree(other);
    }
    ~BPlusTree()
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        clear_tree();
    }
    BPlusTree<T> &operator=(const BPlusTree<T> &RHS)
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        if (this != &RHS)
        {
            clear_tree();
            copy_tree(RHS);
        }
        return *this;
    }
    void copy_tree(const BPlusTree<T> &other) //copy other into this object
    {
        //WENT THOUGH TESTB

        //assumes this btree is empty. [memory leaks otherwise]
        assert(empty());

        //copy from top to bottom
        if (!other.is_leaf())
        {
            copy_array(data, other.data, data_count, other.data_count);
            child_count = other.child_count;
            for (int i = 0; i < child_count; i++)
            {
                subset[i] = new BPlusTree<T>(dups_ok);
                subset[i]->copy_tree(*other.subset[i]);
                //link list (connect leaf pointer)
                if (i > 0)
                {
                    subset[i - 1]->get_biggest_node()->next = subset[i]->get_biggest_node();
                }
            }
        }
        else //if other is leaf
        {
            copy_array(data, other.data, data_count, other.data_count);
        }
    }
    void copy_tree(const BPlusTree<T> &other, stack<BPlusTree<T> *> &s)
    {
        //NOT USED
    }

    //Modifier:
    void insert(const T &entry) //insert entry into the tree
    {
        //WENT THOUGH TESTB
        //WENT THOUGH BASIC TEST

        loose_insert(entry);
        if (data_count > MAXIMUM) // root excess
        {
            BPlusTree<T> *new_node = new BPlusTree<T>(dups_ok);
            //copy root array to new array
            copy_array(new_node->data, data, new_node->data_count, data_count);       //copy data
            copy_array(new_node->subset, subset, new_node->child_count, child_count); //copy childern
            data_count = 0;
            child_count = 1;
            subset[0] = new_node;
            fix_excess(0);
        }
        count();
    }
    void remove(const T &entry) //remove entry from the tree
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        loose_remove(entry);
        //shrink
        if (data_count < MINIMUM && !is_leaf())
        {
            BPlusTree<T> *shrink_ptr = new BPlusTree<T>(dups_ok);
            shrink_ptr = subset[0];
            copy_array(data, shrink_ptr->data, data_count, shrink_ptr->data_count);
            copy_array(subset, shrink_ptr->subset, child_count, shrink_ptr->child_count);
            shrink_ptr->data_count = 0;
            shrink_ptr->child_count = 0;
            delete (shrink_ptr);
        }
        count();
    }
    void clear_tree() //clear this object (delete all nodes etc.)
    {
        //WENT THOUGH TESTB

        if (child_count > 0)
        {
            subset[0]->clear_tree();
            free(subset[0]);
        }
        for (int i = 0; i < data_count; i++)
        {
            if (child_count > i + 1)
            {
                subset[i + 1]->clear_tree();
                if (is_leaf())
                    next = NULL;
                free(subset[i + 1]);
            }
        }
        data_count = 0;
        child_count = 0;
    }

    //Accessor
    bool contains(const T &entry) const //true if entry can be found
    {
        //WENT THOUGH BASIC TEST

        if (empty())
            return false;

        int i = first_ge(data, data_count, entry);
        bool found = (i < data_count && data[i] == entry);
        if (found || is_leaf())
            return found;

        return subset[i]->contains(entry);
    }
    T &get(const T &entry) //return a reference to entry
    {
        //WENT THOUGH TESTB

        //If entry is not in the tree, add it to the tree
        //assert(contains(entry));

        if (!contains(entry))
            insert(entry);
        return get_existing(entry);
    }
    const T &get(const T &entry) const //return a reference to entry
    {
        //WENT THOUGH TESTB

        const bool debug = false;
        int i = first_ge(data, data_count, entry);
        bool found = (i < data_count && data[i] == entry);
        if (is_leaf())
            if (found)
            {
                return data[i];
            }
            else
            {
                if (debug)
                    cout << "get_existing was called with nonexistent entry" << endl;
                assert(found);
            }
        if (found) //inner node
            return subset[i + 1]->get(entry);
        //or just return true?
        else //not found yet...
            return subset[i]->get(entry);
    }
    T &get_existing(const T &entry) //return a reference to entry
    {
        //WENT THOUGH TESTB

        const bool debug = false;
        int i = first_ge(data, data_count, entry);
        bool found = (i < data_count && data[i] == entry);

        if (is_leaf())
        {
            if (found)
            {
                return data[i];
            }
            else
            {
                if (debug)
                    cout << "get_existing was called with nonexistent entry" << endl;
                assert(found);
            }
        }
        if (found) //inner node
            return subset[i + 1]->get_existing(entry);
        //or just return true?
        else //not found yet...
            return subset[i]->get_existing(entry);
    }
    Iterator find(const T &key) //return an iterator to this key.
    {                           //     NULL if not there.
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        //go through tree to find the key
        const bool debug = false;
        int i = first_ge(data, data_count, key);
        bool found = (i < data_count && data[i] == key);

        if (is_leaf())
        {
            if (found)
            {
                Iterator ito(this);
                for (int j = 0; j < i; j++)
                {
                    ++ito;
                }
                return ito;
            }
            else
            {
                if (debug)
                    cout << "key not found" << endl;
                return Iterator(NULL);
            }
        }
        if (found) //inner node
            return subset[i + 1]->find(key);
        //or just return true?
        else //not found yet...
            return subset[i]->find(key);
    }
    Iterator lower_bound(const T &key) //return first that goes NOT BEFORE
    {                                  // key entry or next if does not
                                       // exist: >= entry
        //TESTED

        const bool debug = false;
        int i = first_ge(data, data_count, key);
        bool found = (i < data_count && data[i] == key);

        if (is_leaf()) //this algorithm will return the ptr to the key == entry
        {              //if not found it will try to find the key > entry
                       //if there is not key >= entry, ptr will advance to nullptr
            Iterator ito(this);
            while (*ito < key && *ito != T())
            {
                ++ito;
            }
            return ito;
        }
        if (found) //inner node
            return subset[i + 1]->lower_bound(key);
        //or just return true?
        else //not found yet...
            return subset[i]->lower_bound(key);
    }
    Iterator upper_bound(const T &key) //return first that goes AFTER key
    {                                  //exist or not, the next entry  >entry
        //TESTED

        const bool debug = false;
        int i = first_ge(data, data_count, key);
        bool found = (i < data_count && data[i] == key);

        if (is_leaf()) //this algorithm will advance the ptr to the key > entry
        {              //if there is not key > entry, ptr will advance to nullptr
            Iterator ito(this);
            while (*ito <= key && *ito != T())
            {
                ++ito;
            }
            return ito;
        }
        if (found) //inner node
            return subset[i + 1]->upper_bound(key);
        //or just return true?
        else //not found yet...
            return subset[i]->upper_bound(key);
    }

    int size() const //count the number of elements
    {
        //TESTED

        return count();
    }

    bool empty() const //true if the tree is empty
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        return count() == 0;
    }

    void print_tree(int level = 0,
                    ostream &outs = cout) const
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        assert(level >= 0);
        int d = data_count;
        int c = child_count;

        if (c - 1 >= 0)
            subset[c - 1]->print_tree(level + 1);
        if (is_leaf())
        {
            if (next)
                cout << setw(4 * level) << "^" << endl;
        }
        if (data_count > 0)
            cout << setw(4 * level) << "--" << endl;
        while (d > 0)
        {
            cout << setw(4 * level) << data[d - 1] << endl; //root node
            if (d - 1 == 0)
                cout << setw(4 * level) << "--" << endl;
            if (c - 2 >= 0)
                subset[c - 2]->print_tree(level + 1); //next child
            d--;
            c--;
        }
        if (data_count == 0)
        {
            cout << setw(4 * level) << "--" << endl
                 << endl;
            cout << setw(4 * level) << "--" << endl;
        }
    }
    void print_table(ostream &outs = cout) //NEW for Table class
    {
        //TESTED in Table

        for (Iterator it = begin(); it != end(); ++it)
        {
            cout << *it << endl;
        }
    }
    friend ostream &operator<<(ostream &outs,
                               const BPlusTree<T> &print_me)
    {
        // UNTOUCHED

        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid()
    {
        //WENT THOUGH TESTB

        bool valid = true;
        T entry;

        //should check that every data[i] < data[i+1]
        for (int i = 0; i + 1 < data_count; i++)
        {
            valid = data[i] < data[i + 1];
            if (!valid)
                return valid;
        }
        if (is_leaf())
            return true;
        //data[data_count-1] must be less than equal to
        //  every subset[child_count-1]->data[ ]
        for (int i = 0; i > subset[child_count - 1]->data_count; i--)
        {
            valid = data[data_count - 1] <= subset[child_count - 1]->data[i];
            if (!valid)
                return valid;
        }
        //every data[i] is greater than every subset[i]->data[ ]
        for (int i = 0; i + 1 < data_count; i++)
        {
            valid = data[i] > subset[i]->data[subset[i]->data_count - 1]; //whould be enough to only check last (greatest) element
            if (!valid)
                return valid;
        }
        //B+Tree: Every data[i] is equal to subset[i+1]->smallest
        for (int i = 0; i + 1 < data_count; i++)
        {
            subset[i + 1]->get_smallest(entry);
            valid = data[i] == entry;

            if (!valid)
                return valid;
        }
        //Recursively validate every subset[i]
        for (int i = 0; i < child_count; i++)
        {
            subset[i]->is_valid();
            if (!valid)
                return valid;
        }
        return valid;
    }
    string in_order()
    {
        //WENT THOUGH BASIC TEST

        string str = "";

        if (!is_leaf())
            str += subset[0]->in_order();

        for (int i = 0; i < data_count; i++)
        {
            str += to_string(data[i]);
            str += "|";
            if (!is_leaf())
                str += subset[i + 1]->in_order(); //next child
        }

        return str;
    }

    Iterator begin()
    {
        // UNTOUCHED

        return Iterator(get_smallest_node());
    }
    Iterator end()
    {
        // UNTOUCHED

        return Iterator(NULL);
    }
    ostream &list_keys(Iterator from = NULL, Iterator to = NULL)
    {
        // IMPLEMENTATION FROM CANVAS
        // NOT USED

        if (from == NULL)
            from = begin();
        if (to == NULL)
            to = end();
        for (Iterator it = from; it != to; it++)
            cout << *it << " ";
        return cout;
    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                   //true if duplicate keys are allowed
    int data_count;                 //number of data elements
    T data[MAXIMUM + 1];            //holds the keys
    int child_count;                //number of children
    BPlusTree *subset[MAXIMUM + 2]; //subtrees
    BPlusTree *next;                //link of leafs

    bool is_leaf() const //true if this is a leaf node
    {
        // UNTOUCHED

        return child_count == 0;
    }

    T *find_ptr(const T &entry) //return a pointer to this key.
    {                           // NULL if not there.
        //NOT TESTED

        T *ptr = NULL;
        //find the key in the linked list
        for (Iterator ito = begin(); ito != end(); ++ito)
        {
            if (entry == ito.it->data[ito.key_ptr]) //Stop here, I will implement iterator first
                ptr = ito.it->data[ito.key_ptr];
        }
        return ptr;
    }

    //insert element functions
    void loose_insert(const T &entry) //allows MAXIMUM+1 data elements in
    {                                 //   the root
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        int i = first_ge(data, data_count, entry);
        bool found = (i < data_count && data[i] == entry);

        if (found)
        {
            if (is_leaf()) //overwrite
            {
                if (dups_ok)
                    data[i] = data[i] + entry;
                else
                    data[i] = entry;
                return;
            }
            subset[i + 1]->loose_insert(entry);
            if (subset[i + 1]->data_count >= MAXIMUM + 1) //check if child excess
                fix_excess(i + 1);
        }
        else //!found
        {
            if (is_leaf()) //insert
            {
                insert_item(data, i, data_count, entry);
                return;
            }
            subset[i]->loose_insert(entry);
            if (subset[i]->data_count >= MAXIMUM + 1) //check if child excess
                fix_excess(i);
        }
    }
    void fix_excess(int i) //fix excess in child i
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        T entry;
        insert_item(subset, i + 1, child_count, new BPlusTree<T>(dups_ok)); //create a new child
        split(subset[i]->data, subset[i]->data_count,
              subset[i + 1]->data, subset[i + 1]->data_count); //move half excess child elements to new child
        if (subset[i]->child_count > 0)
            split(subset[i]->subset, subset[i]->child_count,
                  subset[i + 1]->subset, subset[i + 1]->child_count); //move half excess child childern to new child
        detach_item(subset[i]->data, subset[i]->data_count, entry);

        int f = first_ge(data, data_count, entry);

        insert_item(data, f, data_count, entry);
        if (subset[i]->is_leaf()) //make a duplicate since the entry become parent from leaf
        {
            insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, entry);
            subset[i + 1]->next = subset[i]->next;
            subset[i]->next = subset[i + 1]; //point to new child
        }
    }

    //remove element functions:
    void loose_remove(const T &entry) // allows MINIMUM-1 data elements
    {                                 //  in the root
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        const bool debug = false;
        T found_entry;
        int i = first_ge(data, data_count, entry);
        bool found = (i < data_count && data[i] == entry);

        if (is_leaf())
        {
            if (!found)
            {
                if (debug)
                    cout << "Entry is not in the tree" << endl;
                return;
            }
            else
            {
                delete_item(data, i, data_count, found_entry);
            }
        }
        else
        {
            //not leaf:
            // ---- 000 B_PLUS_TREE: no more remove_biggest
            if (!found)
            {
                subset[i]->loose_remove(entry);
                if (subset[i]->data_count == 0)
                {
                    if (debug)
                    {
                        cout << "Tree before fix_shortage" << endl
                             << endl;
                        print_tree();
                    }
                    fix_shortage(i);
                    if (debug)
                    {
                        cout << "Tree after fix_shortage" << endl
                             << endl;
                        print_tree();
                    }
                }
                //not found yet. search in the next level:
            }
            else
            {
                assert(i < child_count - 1);

                subset[i + 1]->loose_remove(entry);
                if (subset[i + 1]->data_count == 0)
                {
                    subset[i + 1]->get_smallest(found_entry);
                    data[i] = found_entry;
                    if (debug)
                    {
                        cout << "Tree before fix_shortage" << endl
                             << endl;
                        print_tree();
                    }
                    fix_shortage(i + 1);
                    if (debug)
                    {
                        cout << "Tree after fix_shortage" << endl
                             << endl;
                        print_tree();
                    }
                    subset[i + 1]->get_smallest(found_entry);
                    data[i] = found_entry;
                }
                else
                {
                    subset[i + 1]->get_smallest(found_entry);
                    data[i] = found_entry;
                }
            }
        }
    }

    BPlusTree<T> *fix_shortage(int i) //fix shortage in child i
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        const bool debug = false;

        if (0 <= i + 1 && i + 1 < child_count) //borrow from right sibling if its data_count > min
        {
            if (subset[i + 1]->data_count > MINIMUM)
            {
                transfer_left(i + 1);
                return subset[i];
            }
        }
        if (0 <= i - 1 && i - 1 < child_count) //borrow from left sibling if its data_count > min
        {
            if (subset[i - 1]->data_count > MINIMUM)
            {
                transfer_right(i - 1);
                return subset[i];
            }
        }
        if (i + 1 < child_count)
        {
            merge_with_next_subset(i);
            return subset[i];
        }
        else
        {
            merge_with_next_subset(i - 1);
            return subset[i];
        }
        return subset[i];
    }
    // and return the smallest key in this subtree
    BPlusTree<T> *get_smallest_node()
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        BPlusTree<T> *key = nullptr;
        if (!is_leaf())
        {
            if (subset[0])
                key = subset[0]->get_smallest_node();
            return key;
        }
        else if (data_count > 0)
            key = this;
        return key;
    }
    BPlusTree<T> *get_biggest_node() //custom: to help copying tree
    {
        //TESTED

        BPlusTree<T> *key = nullptr;
        if (!is_leaf())
        {
            if (subset[child_count - 1])
            {
                key = subset[child_count - 1]->get_biggest_node();
            }
            return key;
        }
        else if (data_count > 0)
            key = this;
        return key;
    }
    void get_smallest(T &entry) //entry := leftmost leaf
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        if (!is_leaf())
            subset[0]->get_smallest(entry);
        else
            entry = data[0];
    }
    void get_biggest(T &entry) //entry := rightmost leaf
    {
        //NOT TESTED

        if (!is_leaf())
            subset[child_count - 1]->get_biggest();
        else
            entry = data[data_count - 1];
    }
    void remove_biggest(T &entry) //remove the biggest child of tree->entry
    {
        //NOT TESTED

        if (!is_leaf())
        {
            subset[child_count - 1]->remove_biggest(entry);
            if (subset[child_count - 1]->data_count <= 0)
                fix_shortage();
        }
        else
            detach_item(data, data_count, entry);
    }
    void transfer_left(int i) //transfer one element LEFT from child i
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        assert((i < child_count) && (subset[i]->data_count > MINIMUM));

        const bool debug = false;
        T entry;
        BPlusTree<T> *entry_b;

        if (!subset[i]->is_leaf())
        {
            delete_item(subset[i]->data, 0, subset[i]->data_count, entry);
            int f = first_ge(data, data_count, entry);
            insert_item(data, f, data_count, entry);
            delete_item(data, f - 1, data_count, entry);
            attach_item(subset[i - 1]->data, subset[i - 1]->data_count, entry);
            //move the childern of moved child's data to the new child
            if (subset[i]->child_count > 0)
            {
                delete_item(subset[i]->subset, 0, subset[i]->child_count, entry_b);
                attach_item(subset[i - 1]->subset, subset[i - 1]->child_count, entry_b);
            }
        }
        else //if leaf
        {
            //transfer data item from [i-1] to [i]
            delete_item(subset[i]->data, 0, subset[i]->data_count, entry);
            insert_item(subset[i - 1]->data, 0, subset[i - 1]->data_count, entry);
            //replace data[i-1] with [i] smallest data item
            data[i - 1] = subset[i]->data[0];
        }
    }
    void transfer_right(int i) //transfer one element RIGHT from child i
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        assert((i < child_count - 1) && (subset[i]->data_count > MINIMUM));

        const bool debug = false;
        T entry = T();
        BPlusTree<T> *entry_b;

        if (!subset[i]->is_leaf())
        {
            detach_item(subset[i]->data, subset[i]->data_count, entry);
            int f = first_ge(data, data_count, entry);
            insert_item(data, f, data_count, entry);
            delete_item(data, f + 1, data_count, entry);
            attach_item(subset[i + 1]->data, subset[i + 1]->data_count, entry);
            //move the childern of moved child's data to the new child
            if (subset[i]->child_count > 0)
            {
                detach_item(subset[i]->subset, subset[i]->child_count, entry_b);
                insert_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count, entry_b);
            }
        }
        else //if leaf
        {
            //transfer data item from [i-1] to [i]
            detach_item(subset[i]->data, subset[i]->data_count, entry);
            insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, entry);
            //replace data[i] with data item
            data[i] = entry;
        }
    }
    BPlusTree<T> *merge_with_next_subset(int i) //merge subset i with  i+1
    {
        //WENT THOUGH BASIC TEST
        //WENT THOUGH TESTB

        const bool debug = false;
        T entry;
        BPlusTree<T> *entry_b;

        if (debug)
        {
            cout << "merge_with_next_subset called" << endl;
            cout << "here is the tree before merge" << endl;
            print_tree();
        }

        if (!subset[i]->is_leaf())
        {
            if (i < child_count - 1)
                delete_item(data, i, data_count, entry);
            else
                delete_item(data, i - 1, data_count, entry);
            int f = first_ge(subset[i]->data, subset[i]->data_count, entry);
            insert_item(subset[i]->data, f, subset[i]->data_count, entry);
            merge(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);
            merge(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset, subset[i + 1]->child_count);
            subset[i + 1]->clear_tree();
            delete_item(subset, i + 1, child_count, entry_b);
        }
        else //if [i] is leaf
        {
            if (i < child_count - 1)
                delete_item(data, i, data_count, entry);
            else
                delete_item(data, i - 1, data_count, entry);
            merge(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);
            subset[i]->next = subset[i + 1]->next;
            subset[i + 1]->clear_tree();
            delete_item(subset, i + 1, child_count, entry_b);
        }

        if (debug)
        {
            cout << "here is the tree after merge" << endl;
            print_tree();
        }

        return subset[i];
    }
    int count() const
    {
        //WENT THOUGH TESTB

        int _count = 0;
        if (!is_leaf())
        {
            _count += subset[0]->count();
        }

        for (int i = 0; i < data_count; i++)
        {
            _count++;
            if (!is_leaf())
            {
                for (int j = 1; j < child_count; j++)
                    _count += subset[j]->count();
            }
        }

        return _count;
    }
};

#endif // BPLUSTREE_H_