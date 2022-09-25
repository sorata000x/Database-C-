#ifndef MAP_H_
#define MAP_H_

#include "bplustree.h"

template <typename K, typename V>
struct Pair
{
    K key;
    V value;

    Pair(const K &k = K(), const V &v = V()) : key(k), value(v)
    {
        //WENT THOUGH TESTB
    }
    friend ostream &operator<<(ostream &outs, const Pair<K, V> &print_me)
    {
        //WENT THOUGH TESTB

        cout << print_me.key << " : " << print_me.value;
        return outs;
    }
    friend bool operator==(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        //WENT THOUGH TESTB

        return lhs.key == rhs.key;
    }
    friend bool operator!=(const Pair<K, V> &lhs, const Pair<K, V> &rhs) //custom
    {
        //WENT THOUGH TESTB

        return lhs.key != rhs.key;
    }
    friend bool operator<(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        //WENT THOUGH TESTB

        return lhs.key < rhs.key;
    }
    friend bool operator>(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        //WENT THOUGH TESTB

        return lhs.key > rhs.key;
    }
    friend bool operator<=(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        //WENT THOUGH TESTB

        return lhs.key <= rhs.key;
    }
    friend bool operator>=(const Pair<K, V> &lhs, const Pair<K, V> &rhs) //custom
    {
        //WENT THOUGH TESTB

        return lhs.key >= rhs.key;
    }
    friend Pair<K, V> operator+(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        //DUMMY

        return rhs;
    }
};

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V>> map_base;
    class Iterator
    {
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it) : _it(it)
        {
            //WENT THOUGH TESTB
        }
        Iterator operator++(int unused)
        {
            //NOT TESTED

            Iterator original(_it);
            _it++;
            return original;
        }
        Iterator operator++()
        {
            //WENT THOUGH TESTB

            ++_it;
            return *this;
        }
        Pair<K, V> operator*()
        {
            //WENT THOUGH TESTB

            Pair<K, V> pair = *_it;
            return pair;
        }
        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            //WENT THOUGH TESTB

            return lhs._it == rhs._it; //true if left == right
        }
        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            //WENT THOUGH TESTB

            return lhs._it != rhs._it; //true if left != right
        }

    private:
        typename map_base::Iterator _it;
    };

    Map() {}

    //  Iterators
    Iterator begin()
    {
        //WENT THOUGH TESTB

        return map.begin();
    }
    Iterator end()
    {
        //WENT THOUGH TESTB

        return map.end();
    }

    //  Capacity
    int size() const
    {
        //TESTED

        return map.size();
    }
    bool empty() const
    {
        //TESTED

        return map.empty();
    }

    //  Element Access
    V &operator[](const K &key)
    {
        //WENT THOUGH TESTB

        Pair<K, V> pair(key);
        return map.get(pair).value;
    }
    V &at(const K &key)
    {
        //WENT THOUGH TESTB

        Pair<K, V> pair(key);
        return map.get(pair).value;
    }
    const V &at(const K &key) const
    {
        //TESTED

        Pair<K, V> pair(key);
        return map.get(pair).value;
    }

    //  Modifiers
    void insert(const K &k, const V &v)
    {
        //WENT THOUGH TESTB

        Pair<K, V> p(k, v);
        map.insert(p);
    }
    void erase(const K &key)
    {
        //WENT THOUGH TESTB

        Pair<K, V> p(key);
        map.remove(p);
    }
    void clear()
    {
        //WENT THOUGH TESTB

        map.clear_tree();
    }
    V get(const K &key)
    {
        //WENT THOUGH TESTB

        Pair<K, V> pair(key);
        return map.get(pair).value;
    }

    //  Operations:
    Iterator find(const K &key)
    {
        //WENT THOUGH TESTB

        Pair<K, V> pair(key);
        return map.find(pair);
    }
    bool contains(const Pair<K, V> &target) const
    {
        //WENT THOUGH TESTB

        return map.contains(target);
    }

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    equal_range:

    Iterator lower_bound(const K &key)
    {
        //NOT TESTED

        return map.lower_bound(Pair<K, V>(key));
    }
    Iterator upper_bound(const K &key)
    {
        //NOT TESTED

        return map.upper_bound(Pair<K, V>(key));
    }

    bool is_valid() { return map.is_valid(); }

    friend ostream &operator<<(ostream &outs, const Map<K, V> &print_me)
    {
        //UNTOUCHED

        outs << print_me.map << endl;
        return outs;
    }

private:
    int key_count;
    BPlusTree<Pair<K, V>> map;
};

#endif // MAP_H_
