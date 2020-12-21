/*
 * 
 * 
 * Copyright (c) 2017 tangm <tangm421@outlook.com>
 * 
 * This file is part of mansys
 * 
 */

#ifndef __MANSYS_CLIST_HEADER__
#define __MANSYS_CLIST_HEADER__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif
/*
 * 操作链表时返回的错误码。
 */
typedef int clist_errcode_t;
#define EOK             ((clist_errcode_t)0)
#define EOUTOFMEM       ((clist_errcode_t)-1)
#define ENOTCREATE      ((clist_errcode_t)-10)
#define EBADARGS        ((clist_errcode_t)-100)

/*
 * 获取错误码对应的错误描述字符串。
 */
PROJECT_IMPORTEXPORT
const char* clist_get_error_string(clist_errcode_t code);


/*
 * 自定义标志类型。
 */
typedef char flag_t;
#define false   ((flag_t)0)
#define true    ((flag_t)1)

/*
 * 循环双向链表结构，无哨兵节点，并定义链表访问的迭代器。
 */
typedef struct clist_t{
    void           *data;
    struct clist_t *next;
    struct clist_t *prev;
}clist_t, *clist_iterator_t;

/*
 * 链表。
 */
typedef struct clist {
    unsigned int    size;
    clist_t        *head;
    clist_t        *tail;
}clist;

/*
 * 链表结尾无效节点。
 */
PROJECT_IMPORTEXPORT
extern const clist_iterator_t clist_iterator_end;

/*
 * 链表迭代器的后向或者前向步进。
 */
typedef enum clist_step_dir_t {
    increase,
    decrease
}clist_step_dir_t;


/*
 * 回调函数声明，供调用者作为条件比对使用。
 * 当用作查找回调时，data1参数为遍历的当前节点，data2为用户数据。
 * 当用作排序回调时，data1，data2参数分别为遍历链表时的前后节点。
 */
typedef flag_t (*comp_handler)(const void* const data1, const void* const data2);




/* 链表操作函数全家福 */

/*
 * 获取版本信息
 *
*/
PROJECT_IMPORTEXPORT
const char*     clist_version();

/*
 * 创建链表
 * 输入参数：
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 * 返回值        ： 错误码。
 * 说明          ： 此函数不会增加内部节点。
 *  
 */
PROJECT_IMPORTEXPORT
clist_errcode_t clist_create(clist* pl);

/*
 * 销毁链表
 * 输入参数
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 * 返回值        ： 错误码。
 * 说明          ： 此函数会销毁调用者在外部申请的堆空间。
 */
PROJECT_IMPORTEXPORT
void            clist_destroy(clist* const pl);

/*
 * 获取链表节点个数
 * 输入参数
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 * 返回值        ： 链表节点个数。
 */
PROJECT_IMPORTEXPORT
unsigned int    clist_size(const clist* const pl);

/*
 * 增加节点
 * 输入参数
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 *  data        - 调用者外部堆数据。
 *  push        - 尾部追加或者头部追加标志。
 * 返回值        ： 错误码。
 */
PROJECT_IMPORTEXPORT
clist_errcode_t clist_add(clist* const pl, void* const data, flag_t push);

/*
 * 获取链表头迭代器
 * 输入参数
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 * 返回值        ： 链表头迭代器。
 */
PROJECT_IMPORTEXPORT
clist_iterator_t clist_begin(clist* const pl);

/*
 * 获取链表尾迭代器
 * 输入参数
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 * 返回值        ： 链表尾迭代器。
 */
PROJECT_IMPORTEXPORT
clist_iterator_t clist_end(clist* const pl);

/*
 * 迭代器步进
 * 输入参数
 *  it          - 迭代器。
 *  dir         - 步进方向。
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 * 返回值        ： 迭代器步进后的新迭代器。
 */
PROJECT_IMPORTEXPORT
clist_iterator_t clist_step(clist_iterator_t it, clist_step_dir_t dir, clist* const pl);

/*
 * 判断迭代器是否已到无效尾部
 * 输入参数
 *  it          - 迭代器。
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 * 返回值        ： 判断结果标志。
 */
PROJECT_IMPORTEXPORT
flag_t           clist_is_end(clist_iterator_t const it, clist* const pl);

/*
 * 从链表中删除迭代器指示的节点
 * 输入参数
 *  it          - 要删除节点位置的迭代器。
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 * 返回值        ： 迭代器指示位置的下一个节点位置的新迭代器。
 */
PROJECT_IMPORTEXPORT
clist_iterator_t clist_erase(clist_iterator_t it, clist* const pl);

/*
 * 查找
 * 输入参数
 *  it          - 匹配起始位置的迭代器。
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 *  h           - 回调函数。
 *  userdata    - 回调函数中传入的用户数据。
 * 返回值        ： 满足条件的迭代器。
 * 说明          ： 回调函数返回结果为true表示匹配，起始位置的迭代器传入NULL值，代表从头节点开始查找。
 */
PROJECT_IMPORTEXPORT
clist_iterator_t clist_find(clist_iterator_t const it, clist* const pl, comp_handler h, const void* const userdata);

/*
 * 排序
 * 输入参数
 *  it          - 排序起始位置的迭代器。
 *  pl          - 外部声明的链表变量指针，不能为空或者无效。
 *  h           - 回调函数。
 * 返回值        ： 无。
 * 说明          ： 回调函数返回结果为true表示匹配。
 */
PROJECT_IMPORTEXPORT
void             clist_sort(clist_iterator_t const it, clist* const pl, comp_handler h);

/*
 * 返回迭代器指示位置的节点数据
 * 输入参数
 *  it          - 迭代器。
 * 返回值        ： 调用者外部堆数据。
 */
PROJECT_IMPORTEXPORT
void*            clist_get(clist_iterator_t it);


#ifdef __cplusplus
    }
#endif

#endif//#ifndef __MANSYS_CLIST_HEADER__
