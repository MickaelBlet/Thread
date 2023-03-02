#!/usr/bin/env python3
# coding=utf-8

import os
import sys

gen_arg_nb = int(sys.argv[1]) + 1

lines = []
lines.extend([
'/**',
' * threadator.h',
' *',
' * Licensed under the MIT License <http://opensource.org/licenses/MIT>.',
' * Copyright (c) 2023 BLET Mickaël.',
' *',
' * Permission is hereby granted, free of charge, to any person obtaining a copy',
' * of this software and associated documentation files (the "Software"), to deal',
' * in the Software without restriction, including without limitation the rights',
' * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell',
' * copies of the Software, and to permit persons to whom the Software is',
' * furnished to do so, subject to the following conditions:',
' *',
' * The above copyright notice and this permission notice shall be included',
' * in all copies or substantial portions of the Software.',
' *',
' * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR',
' * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,',
' * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE',
' * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER',
' * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,',
' * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE',
' * SOFTWARE.',
' */',
'',
f'// generate with ./etc/script/generate.py {gen_arg_nb - 1}',
'',
'#ifndef _MBLET_THREADATOR_H_',
'#define _MBLET_THREADATOR_H_',
'',
'#include <pthread.h>',
'',
'#include <exception>',
'',
'namespace mblet {',
'',
'class Threadator {',
'  private:',
'    pthread_t _id;',
'    bool _isDetached;',
'    pthread_attr_t* _attr;',
'',
'  public:',
'    class Exception : public std::exception {',
'      public:',
'        Exception(const pthread_t& id, const char* message) :',
'            std::exception(),',
'            _what(message),',
'            _id(id) {{}}',
'        virtual ~Exception() throw() {{}}',
'        const char* what() const throw() {',
'            return _what;',
'        }',
'',
'      protected:',
'        const char* _what;',
'        pthread_t _id;',
'    };',
'',
'    Threadator() :',
'        _id(0),',
'        _isDetached(false),',
'        _attr(NULL) {{}}',
'',
'    virtual ~Threadator() throw() {',
'        if (_id != 0 && !_isDetached) {',
'            throw Exception(_id, "Thread is not joining");',
'        }',
'    }',
'',
'    void join() {',
'        if (_id == 0 || _isDetached) {',
'            throw Exception(_id, "Thread is not joinable");',
'        }',
'        pthread_join(_id, NULL);',
'        _id = 0;',
'    }',
'',
'    bool joinable() const {',
'        return _id != 0 && !_isDetached;',
'    }',
'',
'    void cancel() {',
'        if (_id == 0 || _isDetached) {',
'            throw Exception(_id, "Thread is not cancelable");',
'        }',
'',
'        int result = pthread_cancel(_id);',
'        if (result != 0) {',
'            throw Exception(_id, "Failed to cancel thread");',
'        }',
'    }',
'',
'    void detach() {',
'        if (_id == 0 || _isDetached) {',
'            throw Exception(_id, "Thread is not detachable");',
'        }',
'',
'        int result = pthread_detach(_id);',
'        if (result != 0) {',
'            throw Exception(_id, "Failed to detach thread");',
'        }',
'        _isDetached = true;',
'    }',
'',
'    const pthread_t& get_id() const {',
'        return _id;',
'    }',
'',
'    const pthread_t& native_handle() const {',
'        return _id;',
'    }',
'',
'    void set_attr(pthread_attr_t* attr) {',
'        _attr = attr;',
'    }',
''])

def template_args_typename(n):
    l = []
    for i in range(1, n + 1):
        l.append(f'typename A{i}')
    return ', '.join(l)

def template_args(n):
    l = []
    for i in range(1, n + 1):
        l.append(f'A{i}')
    return ', '.join(l)

def args_declaration(n):
    l = []
    for i in range(1, n + 1):
        l.append(f'A{i} a{i}')
    return ', '.join(l)

def args_var(n):
    l = []
    for i in range(1, n + 1):
        l.append(f'a{i}')
    return ', '.join(l)

def struct_args_declaration(n):
    l = []
    for i in range(1, n + 1):
        l.append(f'A{i} _a{i}')
    return '; '.join(l)  + ';'

def struct_args_instanciation(n):
    l = []
    for i in range(1, n + 1):
        l.append(f'_a{i}(a{i})')
    return ', '.join(l)

def struct_args(n):
    l = []
    for i in range(1, n + 1):
        l.append(f'_a{i}')
    return ', '.join(l)

lines.extend([
'',
'    Threadator(void(*pFunction)()) :',
'        _id(0),',
'        _isDetached(false),',
'        _attr(NULL) {',
'        start(pFunction);',
'    }'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<' + template_args_typename(n) + '>',
    '    Threadator(void(*pFunction)(' + template_args(n) + '), ' + args_declaration(n) + ') :',
    '        _id(0),',
    '        _isDetached(false),',
    '        _attr(NULL) {',
    '        start(pFunction, ' + args_var(n) + ');',
    '    }'
    ])

lines.extend([
'',
'    template<typename Class>',
'    Threadator(void(Class::*pFunction)(), Class* pObject) :',
'        _id(0),',
'        _isDetached(false),',
'        _attr(NULL) {',
'        start(pFunction, pObject);',
'    }'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<typename Class, ' + template_args_typename(n) + '>',
    '    Threadator(void(Class::*pFunction)(' + template_args(n) + '), Class* pObject, ' + args_declaration(n) + ') :',
    '        _id(0),',
    '        _isDetached(false),',
    '        _attr(NULL) {',
    '        start(pFunction, pObject, ' + args_var(n) + ');',
    '    }'
    ])

lines.extend([
'',
'    template<typename Class>',
'    Threadator(void(Class::*pFunction)() const, Class* pObject) :',
'        _id(0),',
'        _isDetached(false),',
'        _attr(NULL) {',
'        start(pFunction, pObject);',
'    }'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<typename Class, ' + template_args_typename(n) + '>',
    '    Threadator(void(Class::*pFunction)(' + template_args(n) + ') const, Class* pObject, ' + args_declaration(n) + ') :',
    '        _id(0),',
    '        _isDetached(false),',
    '        _attr(NULL) {',
    '        start(pFunction, pObject, ' + args_var(n) + ');',
    '    }'
    ])


lines.extend([
'',
'    void start(void(*pFunction)()) {',
'        if (_id != 0) {',
'            throw Exception(_id, "Thread already started");',
'        }',
'        ThreadDataStatic0* pThreadData = new ThreadDataStatic0(pFunction);',
'        int result = pthread_create(&_id, _attr, &startThreadStatic0, pThreadData);',
'        if (result != 0) {',
'            delete pThreadData;',
'            throw Exception(_id, "Failed to create thread");',
'        }',
'    }'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<' + template_args_typename(n) + '>',
    '    void start(void(*pFunction)(' + template_args(n) + '), ' + args_declaration(n) + ') {',
    '        if (_id != 0) {',
    '            throw Exception(_id, "Thread already started");',
    '        }',
    f'        ThreadDataStatic{n}<' + template_args(n) + '>* pThreadData = \\',
    f'            new ThreadDataStatic{n}<' + template_args(n) + '>(pFunction, ' + args_var(n) + ');',
    f'        int result = pthread_create(&_id, _attr, &startThreadStatic{n}<' + template_args(n) + '>, pThreadData);',
    '        if (result != 0) {',
    '            delete pThreadData;',
    '            throw Exception(_id, "Failed to create thread");',
    '        }',
    '    }'
    ])

lines.extend([
'',
'    template<typename Class>'
'    void start(void(Class::*pFunction)(), Class* pObject) {',
'        if (_id != 0) {',
'            throw Exception(_id, "Thread already started");',
'        }',
'        ThreadDataMethod0<Class>* pThreadData = new ThreadDataMethod0<Class>(pFunction, pObject);',
'        int result = pthread_create(&_id, _attr, &startThreadMethod0<Class>, pThreadData);',
'        if (result != 0) {',
'            delete pThreadData;',
'            throw Exception(_id, "Failed to create thread");',
'        }',
'    }'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<typename Class, ' + template_args_typename(n) + '>',
    '    void start(void(Class::*pFunction)(' + template_args(n) + '), Class* pObject, ' + args_declaration(n) + ') {',
    '        if (_id != 0) {',
    '            throw Exception(_id, "Thread already started");',
    '        }',
    f'        ThreadDataMethod{n}<Class, ' + template_args(n) + '>* pThreadData = \\',
    f'            new ThreadDataMethod{n}<Class, ' + template_args(n) + '>(pFunction, pObject, ' + args_var(n) + ');',
    f'        int result = pthread_create(&_id, _attr, &startThreadMethod{n}<Class, ' + template_args(n) + '>, pThreadData);',
    '        if (result != 0) {',
    '            delete pThreadData;',
    '            throw Exception(_id, "Failed to create thread");',
    '        }',
    '    }'
    ])

lines.extend([
'',
'    template<typename Class>'
'    void start(void(Class::*pFunction)() const, Class* pObject) {',
'        if (_id != 0) {',
'            throw Exception(_id, "Thread already started");',
'        }',
'        ThreadDataMethodConst0<Class>* pThreadData = new ThreadDataMethodConst0<Class>(pFunction, pObject);',
'        int result = pthread_create(&_id, _attr, &startThreadMethodConst0<Class>, pThreadData);',
'        if (result != 0) {',
'            delete pThreadData;',
'            throw Exception(_id, "Failed to create thread");',
'        }',
'    }'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<typename Class, ' + template_args_typename(n) + '>',
    '    void start(void(Class::*pFunction)(' + template_args(n) + ') const, Class* pObject, ' + args_declaration(n) + ') {',
    '        if (_id != 0) {',
    '            throw Exception(_id, "Thread already started");',
    '        }',
    f'        ThreadDataMethodConst{n}<Class, ' + template_args(n) + '>* pThreadData = \\',
    f'            new ThreadDataMethodConst{n}<Class, ' + template_args(n) + '>(pFunction, pObject, ' + args_var(n) + ');',
    f'        int result = pthread_create(&_id, _attr, &startThreadMethodConst{n}<Class, ' + template_args(n) + '>, pThreadData);',
    '        if (result != 0) {',
    '            delete pThreadData;',
    '            throw Exception(_id, "Failed to create thread");',
    '        }',
    '    }'
    ])


lines.extend([
'',
'  private:'
])

lines.extend([
'',
'    struct ThreadDataStatic0 {',
'        ThreadDataStatic0(void(*pFunction)()) :',
'            _pFunction(pFunction) {',
'        }',
'        void call() { _pFunction(); }',
'        void(*_pFunction)();',
'    };'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<' + template_args_typename(n) + '>',
    f'    struct ThreadDataStatic{n} ' + '{',
    f'        ThreadDataStatic{n}(void(*pFunction)(' + template_args(n) + '), ' + args_declaration(n) + ') :',
    '            _pFunction(pFunction), ' + struct_args_instanciation(n) + ' {',
    '        }',
    '        void call() { _pFunction(' + struct_args(n) + '); }',
    '        void(*_pFunction)(' + template_args(n) + ');',
    '        ' + struct_args_declaration(n),
    '    };'
    ])

lines.extend([
'',
'    template<typename Class>',
'    struct ThreadDataMethod0 {',
'        ThreadDataMethod0(void(Class::*pFunction)(), Class* pObject) :',
'            _pFunction(pFunction), _pObject(pObject) {',
'        }',
'        void call() { (_pObject->*_pFunction)(); }',
'        void(Class::*_pFunction)();',
'        Class* _pObject;',
'    };'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<typename Class, ' + template_args_typename(n) + '>',
    f'    struct ThreadDataMethod{n} ' + '{',
    f'        ThreadDataMethod{n}(void(Class::*pFunction)(' + template_args(n) + '), Class* pObject, ' + args_declaration(n) + ') :',
    '            _pFunction(pFunction), _pObject(pObject), ' + struct_args_instanciation(n) + ' {',
    '        }',
    '        void call() { (_pObject->*_pFunction)(' + struct_args(n) + '); }',
    '        void(Class::*_pFunction)(' + template_args(n) + ');',
    '        Class* _pObject;',
    '        ' + struct_args_declaration(n),
    '    };'
    ])

lines.extend([
'',
'    template<typename Class>',
'    struct ThreadDataMethodConst0 {',
'        ThreadDataMethodConst0(void(Class::*pFunction)() const, Class* pObject) :',
'            _pFunction(pFunction), _pObject(pObject) {',
'        }',
'        void call() { (_pObject->*_pFunction)(); }',
'        void(Class::*_pFunction)() const;',
'        Class* _pObject;',
'    };'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<typename Class, ' + template_args_typename(n) + '>',
    f'    struct ThreadDataMethodConst{n} ' + '{',
    f'        ThreadDataMethodConst{n}(void(Class::*pFunction)(' + template_args(n) + ') const, Class* pObject, ' + args_declaration(n) + ') :',
    '            _pFunction(pFunction), _pObject(pObject), ' + struct_args_instanciation(n) + ' {',
    '        }',
    '        void call() { (_pObject->*_pFunction)(' + struct_args(n) + '); }',
    '        void(Class::*_pFunction)(' + template_args(n) + ') const;',
    '        Class* _pObject;',
    '        ' + struct_args_declaration(n),
    '    };'
    ])

lines.extend([
'',
'    static void* startThreadStatic0(void* data) {',
'        ThreadDataStatic0* pThreadData = reinterpret_cast<ThreadDataStatic0*>(data);',
'        pThreadData->call();',
'        delete pThreadData;',
'        return NULL;',
'    }'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<' + template_args_typename(n) + '>',
    f'    static void* startThreadStatic{n}(void* data) ' + '{',
    f'        ThreadDataStatic{n}<' + template_args(n) + f'>* pThreadData = reinterpret_cast<ThreadDataStatic{n}<' + template_args(n) + '>*>(data);',
    '        pThreadData->call();',
    '        delete pThreadData;',
    '        return NULL;',
    '    }'
    ])

lines.extend([
'',
'    template<typename Class>',
'    static void* startThreadMethod0(void* data) {',
'        ThreadDataMethod0<Class>* pThreadData = reinterpret_cast<ThreadDataMethod0<Class>*>(data);',
'        pThreadData->call();',
'        delete pThreadData;',
'        return NULL;',
'    }'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<typename Class, ' + template_args_typename(n) + '>',
    f'    static void* startThreadMethod{n}(void* data) ' + '{',
    f'        ThreadDataMethod{n}<Class, ' + template_args(n) + f'>* pThreadData = reinterpret_cast<ThreadDataMethod{n}<Class, ' + template_args(n) + '>*>(data);',
    '        pThreadData->call();',
    '        delete pThreadData;',
    '        return NULL;',
    '    }'
    ])

lines.extend([
'',
'    template<typename Class>',
'    static void* startThreadMethodConst0(void* data) {',
'        ThreadDataMethodConst0<Class>* pThreadData = reinterpret_cast<ThreadDataMethodConst0<Class>*>(data);',
'        pThreadData->call();',
'        delete pThreadData;',
'        return NULL;',
'    }'
])

for n in range(1, gen_arg_nb):
    lines.extend([
    '',
    '    template<typename Class, ' + template_args_typename(n) + '>',
    f'    static void* startThreadMethodConst{n}(void* data) ' + '{',
    f'        ThreadDataMethodConst{n}<Class, ' + template_args(n) + f'>* pThreadData = reinterpret_cast<ThreadDataMethodConst{n}<Class, ' + template_args(n) + '>*>(data);',
    '        pThreadData->call();',
    '        delete pThreadData;',
    '        return NULL;',
    '    }'
    ])

lines.extend([
'};',
'',
'} // namespace mblet',
'',
'#endif // #ifndef _MBLET_THREADATOR_H_'
])

with open(os.path.dirname(os.path.realpath(__file__)) + '/../../include/mblet/threadator.h', 'w+') as f:
    for line in lines:
        f.write(line + '\n')