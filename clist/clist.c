/*
 * 
 * 
 * Copyright (c) 2017 tangm <tangm421@outlook.com>
 * 
 * This file is part of mansys
 * 
 */

#include "clist.h"
#include <stdio.h>
#include <malloc.h>

#ifdef CLIST_DEBUG
#   define DEBUGOUT(s, fmt, ...)    fprintf(s, fmt, __VA_ARGS__)
#else
#   define DEBUGOUT(s, fmt, ...)
#endif

#define SAFE_FREE(p)    if(NULL != (p))\
                        {\
                            free((p));\
                            (p) = NULL;\
                        }

#define SIZEOF_CLIST_NODE   sizeof(clist_t)


const clist_iterator_t clist_iterator_end = (clist_iterator_t)0xdeadbeef;

typedef struct clist_errdesc_t {
    clist_errcode_t     code;
    const char         *desc;
}clist_errdesc_t;

static const clist_errdesc_t table_errors[] = {
    { EOK,                          "" },
    { EOUTOFMEM,                    "Out of memory" },
    { ENOTCREATE,                   "Clist not create" },
    { EBADARGS,                     "Bad argument" },

    { (clist_errcode_t)0x7fffffff,  "Unknow error" }
};

const char* clist_get_error_string(clist_errcode_t code)
{
    int i = 0;
    int tablesize = sizeof(table_errors) / sizeof(table_errors[0]);

    for (; i < tablesize; ++i) {
        if (code == table_errors[i].code)
            return table_errors[i].desc;
    }

    return table_errors[tablesize - 1].desc;
}

const char* clist_version()
{
#ifdef HAVE_CONFIG_H
    return (PACKAGE_VERSION);
#endif
    return "";
}

clist_errcode_t clist_create(clist* pl)
{
    if (NULL == pl) {
        return EBADARGS;
    }

    pl->size = 0;
    pl->head = NULL;
    pl->tail = NULL;

    return EOK;
}

void clist_destroy(clist* const pl)
{
    clist_t *p = NULL;
    if (NULL == pl) {
        return;
    }

    while (pl->head && (pl->head != pl->tail)) {
        DEBUGOUT(stdout, "[clist debug] destroy : prev[%p] --> head[%p] --> next[%p], size:%d\n",
            pl->head->prev, pl->head, pl->head->next, pl->size);

        p = pl->head->next;
        SAFE_FREE(pl->head->data);
        pl->head->prev->next = p;
        pl->head->next->prev = pl->head->prev;
        SAFE_FREE(pl->head);
        pl->head = p;
        pl->size--;
    }

    if (pl->head)
    {
        DEBUGOUT(stdout, "[clist debug] destroy : prev[%p] --> head[%p] --> next[%p], size:%d\n",
            pl->head->prev, pl->head, pl->head->next, pl->size);

        SAFE_FREE(pl->head->data);
        SAFE_FREE(pl->head);
        pl->tail = NULL;
        pl->size = 0;
    }

    DEBUGOUT(stdout, "[clist debug] destroy done: head[%p] --> tail[%p], size:%d\n",
        pl->head, pl->tail, pl->size);
}

unsigned int clist_size(const clist * const pl)
{
    return pl->size;
}

clist_errcode_t clist_add(clist * const pl, void * const data, flag_t push)
{
    clist_t* node = NULL;

    if (NULL == pl) {
        return ENOTCREATE;
    }

    node = (clist_t*)malloc(SIZEOF_CLIST_NODE);
    if (NULL == node) {
        return EOUTOFMEM;
    }

    if (NULL == pl->head) {
        pl->head = node;
        pl->tail = node;
        node->next = node;
        node->prev = node;
    }
    else {
        node->next = pl->head;
        node->prev = pl->tail;
        pl->tail->next = node;
        pl->head->prev = node;
    }

    if (push) {
        pl->tail = node;
    } else {
        pl->head = node;
    }

    node->data = data;
    pl->size++;

    DEBUGOUT(stdout, "[clist debug] add : prev[%p] --> new node[%p] --> next[%p], size:%d\n",
        node->prev, node, node->next, pl->size);

    return EOK;
}

clist_iterator_t clist_begin(clist * const pl)
{
    return pl->head;
}

clist_iterator_t clist_end(clist * const pl)
{
    return pl->tail;
}

clist_iterator_t clist_step(clist_iterator_t it, clist_step_dir_t dir, clist* const pl)
{
    clist_iterator_t iter;

    if (dir == increase) {
        iter = it->next;
        if (iter == pl->head) {
            iter = clist_iterator_end;
        }
    } else if (dir == decrease) {
        iter = it->prev;
        if (iter == pl->tail) {
            iter = clist_iterator_end;
        }
    }

    return iter;
}

flag_t clist_is_end(clist_iterator_t const it, clist * const pl)
{
    return (it->next == pl->head) ? true : false;
}

clist_iterator_t clist_erase(clist_iterator_t it, clist* const pl)
{
    clist_iterator_t iter = it->next;

    DEBUGOUT(stdout, "[clist debug] delete before : prev[%p] --> delete node[%p] --> next[%p], size:%d\n",
        it->prev, it, it->next, pl->size);

    if (it == pl->head) pl->head = it->next;
    if (it == pl->tail) pl->tail = it->prev;

    it->next->prev = it->prev;
    it->prev->next = it->next;
    SAFE_FREE(it->data);
    SAFE_FREE(it);
    pl->size--;

    DEBUGOUT(stdout, "[clist debug] delete after : prev[%p] --> current node[%p] --> next[%p], size:%d\n",
        iter->prev, iter, iter->next, pl->size);

    return iter;
}

clist_iterator_t clist_find(clist_iterator_t const it, clist* const pl, comp_handler h, const void* const userdata)
{
    clist_iterator_t    iter;
    clist_t            *p;

    if (NULL == it) {
        p = pl->head;
    }
    else if (clist_iterator_end == it) {
        return it;
    }
    else {
        p = it;
    }
    while (p) {
        if (true == h(p->data, userdata)) {
            iter = p;
            return iter;
        }
        p = p->next;
        if (p == pl->head) {
            return clist_iterator_end;
        }
    }

    return clist_iterator_end;
}

void clist_sort(clist_iterator_t const it, clist* const pl, comp_handler h)
{
    clist_t    *p, *q;
    void       *data;

    if (NULL == it) {
        p = pl->head;
    } else {
        p = it;
    }

    for (; p->next != pl->head; p = p->next) {
        for (q = p->next; q != pl->head; q = q->next) {
            if (true == h(p->data, q->data)) {
                data = p->data;
                p->data = q->data;
                q->data = data;
            }
        }
    }
}

void * clist_get(clist_iterator_t it)
{
    if (it != clist_iterator_end) {
        return it->data;
    }
    return NULL;
}
