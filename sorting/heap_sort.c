/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "record.h"
#include <stdio.h>
#include <assert.h>

// heapsort maintains a binary tree in a flat array. For any index I
// the children indexes will be (2I) and (2I + 1). Zero-based C arrays
// make things interesting, as the zero-th index would result in the
// wrong children indexes: (2I) = 2 * 0 = 0. To simplify the code we
// treat the array as 1's based rather than zero.
#define LEFT(i) ((i) * 2)
#define RIGHT(i) ((i) * 2 + 1)
#define PARENT(i) ((i) / 2)
#define INDEX(i) ((i) - 1)  // used when accessing the C array

// A max heap maintains that the child node's values are less than or
// equal to the parent's value.
// array[INDEX(PARENT(i))] >= array[INDEX(i)]

/**
 * Max Heapify
 *
 * Ensure that the subtree rooted at index i is a proper max heap.
 * heap_size is the total number of records in the array.
 */
void heapify_max(record_t *array, size_t heap_size, int i)
{
    assert(i > 0);  // 1's based index
    int left = LEFT(i);
    int right = RIGHT(i);

    int largest = i;
    if (left <= heap_size && array[INDEX(left)].key > array[INDEX(largest)].key) {
        largest = left;
    }
    if (right <= heap_size && array[INDEX(right)].key > array[INDEX(largest)].key) {
        largest = right;
    }
    if (largest != i) {
        // One of the children is largest. Swap that with the parent (i):
        swap_records(&array[INDEX(i)], &array[INDEX(largest)]);

        // now the new key in largest may be < its children so
        // rebalance that subtree
        heapify_max(array, heap_size, largest);
    }
}


/**
 * Convert the array of records into a max heap.
 *
 * The heap array has an interesting property: the array entries
 * (LENGTH / 2 + 1)..LENGTH are all leaf nodes (no children). A leaf
 * node is by definition a max heap. Start with the lowest parent and
 * modify the parent sub tree into a max heap. Bubble that up to all
 * parents of the array.
 */
void max_heap_build(record_t *array, size_t array_len)
{
    int index = array_len / 2;
    while (index > 0) {
        heapify_max(array, array_len, index--);
    }
}

/**
 * Heapsort
 *
 * Sort array into ascending key values.
 *
 * The largest key value in an max heap is always in the first array
 * index (INDEX(1)). The heapsort works by moving the INDEX(1) value
 * to the end of the array (swapping it with the last heap element)
 * then reducing the array length by one (effectively removing that
 * last entry from the heap). Then we rebalance the heap to move the
 * first element to its proper place in the heap.  This results in
 * sorting the array in place.
 */
void heapsort_max(record_t *array, size_t array_len)
{
    // make the array a max heap
    max_heap_build(array, array_len);

    while (array_len > 1) {
        swap_records(&array[INDEX(1)], &array[INDEX(array_len)]);
        array_len -= 1;
        heapify_max(array, array_len, 1);
    }
}


/**
 * Retrieve the record with the maximum key value in the heap.
 */
record_t *heap_get_max(record_t *array, size_t array_len)
{
    assert(array_len > 0);
    return &array[0];
}


/**
 * Remove the maximum key value element from the heap. Return a copy
 * of the record.  Note this reduces the heap length by one!
 */
record_t heap_pop_max(record_t *array, size_t array_len)
{
    assert(array_len > 0);

    record_t max = array[0];

    // overwrite the max index with the last element, then rebalance the tree
    array[0].key = array[INDEX(array_len)].key;
    array[0].payload = array[INDEX(array_len)].payload;
    heapify_max(array, array_len - 1, 1);
    return max;
}


/**
 * Insert a new element into the max heap.
 *
 * array_capacity - this is the total size of the array.
 * heap_size - this is the number of elements in the heap.
 *
 * Note: this assumes that the array has (at least) one empty entry at
 * the end of the array! In other words array_capacity must be greater
 * than heap_size by at least one!
 */
void max_heap_insert(record_t *array, size_t array_capacity, size_t heap_size,
                     int key, void *payload)
{
    assert(array_capacity > heap_size);

    // create new entry at end of heap
    heap_size += 1;
    array[INDEX(heap_size)].key = key;
    array[INDEX(heap_size)].payload = payload;

    // bubble up the new entry to its proper place in the heap
    int i = (int) heap_size;
    while (i > 1 && array[INDEX(PARENT(i))].key < array[INDEX(i)].key) {
        swap_records(&array[INDEX(PARENT(i))], &array[INDEX(i)]);
        i = PARENT(i);
    }
}


void print_array(const record_t *array, size_t length)
{
    for (int i = 0; i < length; ++i) {
        fprintf(stdout, "array[%d].key = %d\n", i, array[i].key);
    }
}


#define ARRAY_LEN 11
int main(int argc, char *argv[])
{
    record_t array[ARRAY_LEN];
    for (int i = 0; i < ARRAY_LEN; ++i) {
        array[i].payload = (void *) 0;
        array[i].key = ARRAY_LEN - i;
    }

    fprintf(stdout, "----\n");
    print_array(array, ARRAY_LEN);
    heapsort_max(array, ARRAY_LEN);
    print_array(array, ARRAY_LEN);

    for (int i = 0; i < ARRAY_LEN; ++i) {
        array[i].key = i + 1;
    }
    fprintf(stdout, "----\n");
    print_array(array, ARRAY_LEN);
    heapsort_max(array, ARRAY_LEN);
    print_array(array, ARRAY_LEN);

    return 0;
}
