/**
 * @file priority_queue.h
 */

#ifndef _PQUEUE_H_
#define _PQUEUE_H_

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;



/**
 * Implements the max priority queue ADT.
 *
 * The implementation is up to you, but you must complete all the given
 *  public functions. You will need to add some member variables and private
 *  helper functions.
 */

template <class T>
class PriorityQueue
{
    public:
        /**
         * Constructor: creates an empty priority queue.
         */
        PriorityQueue();

        /**
         * Copy Constructor: copy a existing priority queue.
         */
        PriorityQueue(PriorityQueue&theone);

        /**
         * Destructor: Destroy a existing priority queue.
         */
        ~PriorityQueue();

        /**
         * Inserts the given value into the queue.
         *
         * @param value The value to be inserted.
         */
        void insert(const T & value);

        /**
         * Removes the highest value (and its associated data) from the
         *  queue.
         *
         * @return A copy of the removed (maximum) element
         */
        T pop();

        /**
         * Returns the highest value from the queue. Does NOT remove it.
         *
         * @return A copy of the maximum element
         */
        const T & top() const;

        /**
         * Determines if the queue is empty. Should be O(1).
         *
         * @return A boolean value indicating whether the queue is
         *  empty.
         */
        bool isEmpty() const;
    private:

        //template <class T>
        struct node
        {
            node*parent;
            node*children;
            node*right;
            node*left;
            node*rightmost;
            node*leftmost;
            int numchildren;
            //T key;
            T value;
            node();
            node(T thevalue);
            node(node*theone);
            bool insertchild(node*child);
            bool insertsibling(node*leftorright);
            void remove();
            node*getrightmost();
            node*getleftmost();           
        };


        node*roots[100];
        bool join(node*root);
        node*maxroot;
        node*removemax();
    

};

#include "priority_queue.cpp"
#endif
