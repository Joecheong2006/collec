#pragma once

#include <assert.h>
#include <stddef.h>

typedef void (*unit_func)(void);

struct TestFuncNode {
    struct TestFuncNode *next;
    const char *filename;
    const char *funcName;
    unit_func func;
};

typedef struct TestFuncNode TestFuncNode;

void register_test_func(TestFuncNode *node);

#define UNIT(name) \
    void TEST_FUNC_##name();\
    static TestFuncNode _node_##name = {\
        .next = NULL,\
        .filename = __FILE_NAME__,\
        .funcName = #name, \
        .func = TEST_FUNC_##name,\
    }; \
    __attribute__((constructor))\
    static void register_test_func_##name(void) { register_test_func(&_node_##name); }\
    void TEST_FUNC_##name()
