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
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void print_array(const record_t *array, size_t length)
{
    for (int i = 0; i < length; ++i) {
        fprintf(stdout, "%d ", array[i].key);
    }
    fprintf(stdout, "\n");
}

static void merge(record_t *array, size_t left, size_t right, record_t *scratch)
{
    //fprintf(stdout, "Merging left=%zu right=%zu\n", left, right);
    //print_array(array, left + right);

    record_t *sptr = &scratch[0];
    const record_t *ptr1 = &array[0];
    const record_t *end1 = &array[left];
    const record_t *ptr2 = &array[left];
    const record_t *end2 = &array[left + right];

    while (ptr1 != end1 && ptr2 != end2) {
        if (ptr1->key < ptr2->key) {
            //fprintf(stdout, "Moving %d\n", ptr1->key);
            *sptr++ = *ptr1++;
        } else {
            //fprintf(stdout, "Moving %d\n", ptr2->key);
            *sptr++ = *ptr2++;
        }
    }

    if (ptr1 != end1) {
        memcpy(sptr, ptr1, (end1 - ptr1) * sizeof(record_t));
    } else if (ptr2 != end2) {
        memcpy(sptr, ptr2, (end2 - ptr2) * sizeof(record_t));
    }

    memcpy(array, scratch, (left + right) * sizeof(record_t));
}


void merge_sort(record_t *array, size_t length)
{
    record_t *scratch = calloc(length, sizeof(record_t));
    if (!scratch)
        exit(1);

    for (size_t span = 1; span < length; span *= 2) {
        for (size_t index = 0; index + span < length; index += 2 * span) {
            size_t left_len = span;
            size_t right_len = MIN(span, length - (index + left_len));
            merge(&array[index], left_len, right_len, scratch);
        }
        //print_array(array, length);
    }
}


int main(int argc, char *argv[])
{
#define ASIZE 15
    record_t array[ASIZE];
    for (int i = 0; i < ASIZE; ++i) {
        array[i].payload = (void *) 0;
        array[i].key = ASIZE - i;
    }

    fprintf(stdout, "----\nStarting array: ");
    print_array(array, ASIZE);
    merge_sort(array, ASIZE);
    fprintf(stdout, "Sorted array: ");
    print_array(array, ASIZE);

    for (int i = 0; i < ASIZE; ++i) {
        array[i].key = i;
    }
    fprintf(stdout, "----\nStarting array: ");
    print_array(array, ASIZE);
    merge_sort(array, ASIZE);
    print_array(array, ASIZE);

    return 0;
}
