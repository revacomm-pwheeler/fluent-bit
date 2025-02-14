/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  CFL
 *  ===
 *  Copyright (C) 2022 The CFL Authors
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <cfl/cfl.h>
#include <cfl/cfl_variant.h>
#include <cfl/cfl_array.h>
#include <cfl/cfl_kvlist.h>

struct cfl_variant *cfl_variant_create_from_string(char *value)
{
    struct cfl_variant *instance;

    instance = cfl_variant_create();

    if (instance != NULL) {
        instance->data.as_string = cfl_sds_create(value);
        if (instance->data.as_string == NULL) {
            free(instance);
            instance = NULL;
        }
        else {
            instance->type = CFL_VARIANT_STRING;
        }
    }

    return instance;
}

struct cfl_variant *cfl_variant_create_from_bytes(char *value, size_t length)
{
    struct cfl_variant *instance;

    instance = cfl_variant_create();

    if (instance != NULL) {
        instance->data.as_bytes = cfl_sds_create_len(value, length);
        if (instance->data.as_bytes == NULL) {
            free(instance);
            instance = NULL;
        }
        else {
            instance->type = CFL_VARIANT_BYTES;
        }
    }

    return instance;
}

struct cfl_variant *cfl_variant_create_from_bool(int value)
{
    struct cfl_variant *instance;

    instance = cfl_variant_create();
    if (instance != NULL) {
        instance->data.as_bool = value;
        instance->type = CFL_VARIANT_BOOL;
    }

    return instance;
}

struct cfl_variant *cfl_variant_create_from_int64(int64_t value)
{
    struct cfl_variant *instance;

    instance = cfl_variant_create();
    if (instance != NULL) {
        instance->data.as_int64 = value;
        instance->type = CFL_VARIANT_INT;
    }

    return instance;
}

struct cfl_variant *cfl_variant_create_from_double(double value)
{
    struct cfl_variant *instance;

    instance = cfl_variant_create();
    if (instance != NULL) {
        instance->data.as_double = value;
        instance->type = CFL_VARIANT_DOUBLE;
    }

    return instance;
}

struct cfl_variant *cfl_variant_create_from_array(struct cfl_array *value)
{
    struct cfl_variant *instance;

    instance = cfl_variant_create();
    if (instance != NULL) {
        instance->data.as_array = value;
        instance->type = CFL_VARIANT_ARRAY;
    }

    return instance;
}

struct cfl_variant *cfl_variant_create_from_kvlist(struct cfl_kvlist *value)
{
    struct cfl_variant *instance;

    instance = cfl_variant_create();
    if (instance != NULL) {
        instance->data.as_kvlist = value;
        instance->type = CFL_VARIANT_KVLIST;
    }

    return instance;
}

struct cfl_variant *cfl_variant_create_from_reference(void *value)
{
    struct cfl_variant *instance;

    instance = cfl_variant_create();
    if (instance != NULL) {
        instance->data.as_reference = value;
        instance->type = CFL_VARIANT_REFERENCE;
    }

    return instance;
}

struct cfl_variant *cfl_variant_create()
{
    struct cfl_variant *instance;

    instance = calloc(1, sizeof(struct cfl_variant));
    if (instance == NULL) {
        cfl_errno();
        return NULL;
    }

    return instance;
}

void cfl_variant_destroy(struct cfl_variant *instance)
{
    if (!instance) {
        return;
    }

    if (instance->type == CFL_VARIANT_STRING ||
        instance->type == CFL_VARIANT_BYTES) {
        if (instance->data.as_string != NULL) {
            cfl_sds_destroy(instance->data.as_string);
        }
    }
    else if (instance->type == CFL_VARIANT_ARRAY) {
        cfl_array_destroy(instance->data.as_array);
    }
    else if (instance->type == CFL_VARIANT_KVLIST) {
        cfl_kvlist_destroy(instance->data.as_kvlist);
    }

    free(instance);
}
