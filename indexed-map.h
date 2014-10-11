#ifndef __indexed_map_IndexedMap__
#define __indexed_map_IndexedMap__

#include <cstddef>

namespace indexed_map
{
    private:

        template <typename K, typename V>
        class RedBlackTree<K,V>;


        template <typename K, typename V>
        RedBlackTree<K,V> * singleRotate(RedBlackTree<K,V> * tree,
               int direction)
        {
            // TODO: Needs null pointer checks
            RedBlackTree<K,V> * returned = tree->child[!direction];
            tree->child[!direction] = returned->child[direction];
            returned->child[direction] = this;
            tree->color = RED;
            returned->color = BLACK;
            return returned;
        }

        template <typename K, typename V>
        RedBlackTree<K,V> * doubleRotate(RedBlackTree<K,V> * tree,
                int direction)
        {
            tree->child[!direction] = singleRotate(tree->child[!direction], !direction);
            return SingleRotate(tree, direction);
        }

        template <typename K, typename V>
        RedBlackTree<K,V> * insertRecursive(RedBlackTree<K,V> * tree,
                const K & key, const V & value, RedBlackTree<K,V> * bookmark)
        {
            if (tree == NULL)
            {
                // equality test
                if (bookmark != NULL && !(bookmark->key < key))
                {
                    bookmark->key = key;
                    bookmark->value = value;
                }
                else
                {
                    return new RedBlackTree<K,V>(key, value);
                }
            }
            else
            {
                int direction = key < this->key;
                tree->child[direction] = insertRecursive(tree->child[direction],
                        key, value,
                        direction == LARGER_CHILD ? bookmark : this);
                return tree;
            }
        }

        template <typename K, typename V>
        class RedBlackTree
        {
            private:
                // 0 = red, -1 = negative color, 1 = color, 2 = double color
                static const int NEGATIVE_BLACK = -1;
                static const int RED = 0;
                static const int BLACK = 1;
                static const int DOUBLE_BLACK = 2;
                int color;
                K key;
                V value;
                size_t size;
                RedBlackTree *child[2];
                static const int LARGER_CHILD = 0;
                static const int SMALLER_CHILD = 1;

                void init(const K & key, const V & value)
                {
                    color = RED;
                    this->key = key;
                    this->value = value;
                    size = 1UL;
                    child = {NULL, NULL};
                }

                void copyChildren(const RedBlackTree<K,V> & other)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        if (other.child[i] != NULL)
                        {
                            child[i] = new RedBlackTree(*(other.child[i]));
                        }
                    }
                }

                void copy(const RedBlackTree<K,V> & other)
                {
                    color = other.color;
                    key = other.key;
                    value = other.value;
                    size = other.size;
                    copyChildren(other);
                }

                void free()
                {
                    color = 0;
                    size = 0UL;
                    for (int i = 0; i < 2; i++)
                    {
                        if (child[i] != NULL)
                        {
                            delete child[i];
                        }
                    }
                }


            public:
                RedBlackTree(const K & key, const V & value)
                {
                    init(key, value);
                }
                RedBlackTree(const RedBlackTree<K,V> & other)
                {
                    copy(other);
                }
                RedBlackTree<K,V> & operator = (const RedBlackTree<K,V> & other)
                {
                    if (&other != this)
                    {
                        free();
                        copy(other);
                    }
                }
                ~RedBlackTree()
                {
                    free();
                }
        };

};

#endif
