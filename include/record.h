#ifndef _record_h
#define _record_h 1
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


// A dummy keyed record object. Used as an example data item in some of the array-based sorting code.

typedef struct record_t {
    int key;
    void *payload;
} record_t;

static inline void swap_records(record_t *a, record_t *b)
{
    int tmp_key = a->key;
    void *tmp_payload = a->payload;
    a->key = b->key;
    a->payload = b->payload;
    b->key = tmp_key;
    b->payload = tmp_payload;
}
#endif
