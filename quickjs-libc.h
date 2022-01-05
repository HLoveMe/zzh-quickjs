/*
 * QuickJS C library
 * 
 * Copyright (c) 2017-2018 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef QUICKJS_LIBC_H
#define QUICKJS_LIBC_H

#include <stdio.h>
#include <stdlib.h>

#include "quickjs.h"

#ifdef __cplusplus
extern "C" {
#endif
/***
 * std os 具体实现 promise 一个扩展
 * 第三方扩展样例
 * */

// 加载os std模块
//std 输入输出模块
JSModuleDef *js_init_module_std(JSContext *ctx, const char *module_name);
/**
 * os 文件操作相关的api
 * 设置监听os-poll函数
 * Timer class
 * Worker 相关设置
 * */
JSModuleDef *js_init_module_os(JSContext *ctx, const char *module_name);


void js_std_add_helpers(JSContext *ctx, int argc, char **argv);

//开启事件循环 可能有所不同
void js_std_loop(JSContext *ctx);

//初始化std模块处理函数的link
// std 定时器处理。信号处理 。读写处理
void js_std_init_handlers(JSRuntime *rt);
void js_std_free_handlers(JSRuntime *rt);
void js_std_dump_error(JSContext *ctx);

// 加载文件内容
uint8_t *js_load_file(JSContext *ctx, size_t *pbuf_len, const char *filename);

// 设置模块导出信息
/**
js_module_set_import_meta:记录模块导出信息
 tag === JS_EVAL_TYPE_MODULE
 该方法用于记录模块的信息 路径，内容等。用于其他模块导入该模块时使用 

js_module_loader:加载模块
 默认的加载器 ES6 模块导入的加载器
 import XX from './xx.js'
 
模块加载过程
 1：js_load_file加载文件的内容
 2：JS_EVAL 执行编译内容，
 3：js_module_set_import_meta 记录模块信息
 */
int js_module_set_import_meta(JSContext *ctx, JSValueConst func_val,

JSModuleDef *js_module_loader(JSContext *ctx,
                              const char *module_name, void *opaque);

// 加载扩展库  大数据运算等                              
void js_std_eval_binary(JSContext *ctx, const uint8_t *buf, size_t buf_len,
                        int flags);

// promise 一个扩展函数
void js_std_promise_rejection_tracker(JSContext *ctx, JSValueConst promise,
                                      JSValueConst reason,
                                      JS_BOOL is_handled, void *opaque);
// 设置如何创建Worker
void js_std_set_worker_new_context_func(JSContext *(*func)(JSRuntime *rt));
                                        
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* QUICKJS_LIBC_H */
