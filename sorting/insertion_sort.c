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

// insertion_sort
//
// Loop through array maintaining a cursor that increments from 1 to (length - 1).
// All entries with index < cursor are sorted. All entries with index >= cursor are not.
// Sort array[cursor] into the sorted portion of the array, then advance cursor.
//
void insertion_sort(record_t *array, size_t length)
{
    int cursor = 1;
    while (cursor < length) {
        record_t target = array[cursor];
        int index = cursor;
        while (index > 0 && array[index - 1].key > target.key) {
            array[index] = array[index - 1];
            index -= 1;
        }
        array[index] = target;
        cursor += 1;
    }
}

void print_array(const record_t *array, size_t length)
{
    for (int i = 0; i < length; ++i) {
        fprintf(stdout, "array[%d].key = %d\n", i, array[i].key);
    }
}

int main(int argc, char *argv[])
{
    record_t array[10];
    for (int i = 0; i < 10; ++i) {
        array[i].payload = (void *) 0;
        array[i].key = 10 - i;
    }

    fprintf(stdout, "----\n");
    print_array(array, 10);
    insertion_sort(array, 10);
    print_array(array, 10);

    for (int i = 0; i < 10; ++i) {
        array[i].key = i;
    }
    fprintf(stdout, "----\n");
    print_array(array, 10);
    insertion_sort(array, 10);
    print_array(array, 10);

    return 0;
}
