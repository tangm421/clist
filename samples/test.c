
#include "clist.h"
#include "mydefines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct member {
    int no;
    char str[20];
}member;

flag_t find_process_handler(const void* const data1, const void* const data2) {
    member* p = (member*)data1;
    if ((int)data2 == p->no) {
        return true;
    } else {
        return false;
    }
}

flag_t sort_process_handler(const void* const data1, const void* const data2) {
    member* p1 = (member*)data1;
    member* p2 = (member*)data2;
    if (p2->no > p1->no) {
        return true;
    } else {
        return false;
    }
}

void showall(clist* pcl, flag_t dir) {
    member* p;
    clist_iterator_t it;
    if (true == dir) {
        printf("----------------- traverse from head to tail\n");
        it = clist_begin(pcl);
        for (; it != clist_iterator_end; it = clist_step(it, increase, pcl)) {
            p = clist_get(it);
            printf("%d, %s\n", p->no, p->str);
        }
    } else {
        printf("----------------- traverse from tail to head\n");
        it = clist_end(pcl);
        for (; it != clist_iterator_end; it = clist_step(it, decrease, pcl)) {
            p = clist_get(it);
            printf("%d, %s\n", p->no, p->str);
        }
    }
}

void test_data(clist *pcl) {
    member* p;

    p = (member*)malloc(sizeof(member));
    p->no = 0;
    strcpy(p->str, "name0");
    clist_add(pcl, p, true);
    printf("insert tail: %d\n", p->no);

    p = (member*)malloc(sizeof(member));
    p->no = 10;
    strcpy(p->str, "name10");
    clist_add(pcl, p, true);
    printf("insert tail: %d\n", p->no);

    p = (member*)malloc(sizeof(member));
    p->no = 100;
    strcpy(p->str, "name100");
    clist_add(pcl, p, true);
    printf("insert tail: %d\n", p->no);

    p = (member*)malloc(sizeof(member));
    p->no = 1000;
    strcpy(p->str, "name1000");
    clist_add(pcl, p, true);
    printf("insert tail: %d\n", p->no);


    p = (member*)malloc(sizeof(member));
    p->no = 0;
    strcpy(p->str, "name-0");
    clist_add(pcl, p, false);
    printf("insert front: %d\n", p->no);

    p = (member*)malloc(sizeof(member));
    p->no = -10;
    strcpy(p->str, "name-10");
    clist_add(pcl, p, false);
    printf("insert front: %d\n", p->no);

    p = (member*)malloc(sizeof(member));
    p->no = -100;
    strcpy(p->str, "name-100");
    clist_add(pcl, p, false);
    printf("insert front: %d\n", p->no);

    p = (member*)malloc(sizeof(member));
    p->no = -1000;
    strcpy(p->str, "name-1000");
    clist_add(pcl, p, false);
    printf("insert front: %d\n", p->no);
}

int main(int argc, char* argv[])
{
    // test to use defines in custom headers
    printf("test to use defines in custom headers - INSTALL_BINDIR:%s\n", INSTALL_BINDIR);
    // test to use preprocessor definitions
    printf("test to use preprocessor definitions - _BINDIR:%s\n", _BINDIR);

    clist cl;
    member* p;
    clist_iterator_t it;
    clist_errcode_t code;

    printf("press any key to begin...");
    getchar();

    clist* test = NULL;
    printf("----------------- invalid call -----------------\n");
    code = clist_create(test);
    if (code != EOK) {
        printf("%s\n", clist_get_error_string(code));
    }

    p = (member*)malloc(sizeof(member));
    p->no = 3546846;
    strcpy(p->str, "xasxas");
    code = clist_add(test, p, true);
    if (code != EOK) {
        printf("%s\n", clist_get_error_string(code));
        free(p);
    }

    clist_create(&cl);

    printf("----------------- input data -----------------\n");
    test_data(&cl);

    showall(&cl, true);

    showall(&cl, false);

    printf("----------------- find data -----------------\n");
    it = NULL;
    while (1) {
        it = clist_find(it, &cl, find_process_handler, 0);
        if (it == clist_iterator_end) {
            break;
        }
        p = clist_get(it);
        printf("%d, %s\n", p->no, p->str);
        it = clist_step(it, increase, &cl);
    }

    printf("----------------- modify data -----------------\n");
    it = clist_find(NULL, &cl, find_process_handler, (void*)-1000);
    if (it != clist_iterator_end) {
        p = clist_get(it);
        strcpy(p->str, "modified");
    }
    showall(&cl, true);

    printf("----------------- delete data -----------------\n");
    it = NULL;
    while (1) {
        it = clist_find(it, &cl, find_process_handler, 0);
        if (it == clist_iterator_end) {
            break;
        } else {
            it = clist_erase(it, &cl);
        }
    }
    showall(&cl, true);

    printf("----------------- sort -----------------\n");
    clist_sort(NULL, &cl, sort_process_handler);
    showall(&cl, true);

    clist_destroy(&cl);

    return 0;
}
