/**
 * thread.h
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2023 BLET Mickaël.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _BLET_THREAD_H_
#define _BLET_THREAD_H_

#include <pthread.h>

#include <exception>

namespace blet {

class Thread {
  private:
    pthread_t _id;
    bool _isDetached;
    pthread_attr_t* _attr;

  public:
    class Exception : public std::exception {
      public:
        Exception(const pthread_t& id, const char* message) :
            std::exception(),
            _what(message),
            _id(id) {}
        virtual ~Exception() throw() {}
        const char* what() const throw() {
            return _what;
        }

      protected:
        const char* _what;
        pthread_t _id;
    };

    Thread() :
        _id(0),
        _isDetached(false),
        _attr(NULL) {}

    virtual ~Thread() throw() {
        if (_id != 0 && !_isDetached) {
            throw Exception(_id, "Thread is not joining");
        }
    }

    void join() {
        if (_id == 0 || _isDetached) {
            throw Exception(_id, "Thread is not joinable");
        }
        pthread_join(_id, NULL);
        _id = 0;
    }

    bool joinable() const {
        return _id != 0 && !_isDetached;
    }

    void cancel() {
        if (_id == 0 || _isDetached) {
            throw Exception(_id, "Thread is not cancelable");
        }

        int result = pthread_cancel(_id);
        if (result != 0) {
            throw Exception(_id, "Failed to cancel thread");
        }
    }

    void detach() {
        if (_id == 0 || _isDetached) {
            throw Exception(_id, "Thread is not detachable");
        }

        int result = pthread_detach(_id);
        if (result != 0) {
            throw Exception(_id, "Failed to detach thread");
        }
        _isDetached = true;
    }

    const pthread_t& get_id() const {
        return _id;
    }

    const pthread_t& native_handle() const {
        return _id;
    }

    void set_attr(pthread_attr_t* attr) {
        _attr = attr;
    }

    // -------------------------------------------------------------------------
    // This following part is generate with ./etc/script/generate.py 10
    // -------------------------------------------------------------------------

  public:
    Thread(void (*pFunction)()) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction);
    }

    void start(void (*pFunction)()) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic0* pThreadData = new ThreadDataStatic0(pFunction);
        int result =
            pthread_create(&_id, _attr, &startThreadStatic0, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    struct ThreadDataStatic0 {
        ThreadDataStatic0(void (*pFunction)()) :
            _pFunction(pFunction) {}
        void call() {
            (*_pFunction)();
        }
        void (*_pFunction)();
    };

    static void* startThreadStatic0(void* data) {
        ThreadDataStatic0* pThreadData =
            reinterpret_cast<ThreadDataStatic0*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1>
    Thread(void (*pFunction)(A1), A1 a1) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1);
    }

    template<typename A1>
    void start(void (*pFunction)(A1), A1 a1) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic1<A1>* pThreadData =
            new ThreadDataStatic1<A1>(pFunction, a1);
        int result =
            pthread_create(&_id, _attr, &startThreadStatic1<A1>, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1>
    struct ThreadDataStatic1 {
        ThreadDataStatic1(void (*pFunction)(A1), A1 a1) :
            _pFunction(pFunction),
            _a1(a1) {}
        void call() {
            (*_pFunction)(_a1);
        }
        void (*_pFunction)(A1);
        A1 _a1;
    };

    template<typename A1>
    static void* startThreadStatic1(void* data) {
        ThreadDataStatic1<A1>* pThreadData =
            reinterpret_cast<ThreadDataStatic1<A1>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1, typename A2>
    Thread(void (*pFunction)(A1, A2), A1 a1, A2 a2) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1, a2);
    }

    template<typename A1, typename A2>
    void start(void (*pFunction)(A1, A2), A1 a1, A2 a2) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic2<A1, A2>* pThreadData =
            new ThreadDataStatic2<A1, A2>(pFunction, a1, a2);
        int result = pthread_create(&_id, _attr, &startThreadStatic2<A1, A2>,
                                    pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1, typename A2>
    struct ThreadDataStatic2 {
        ThreadDataStatic2(void (*pFunction)(A1, A2), A1 a1, A2 a2) :
            _pFunction(pFunction),
            _a1(a1),
            _a2(a2) {}
        void call() {
            (*_pFunction)(_a1, _a2);
        }
        void (*_pFunction)(A1, A2);
        A1 _a1;
        A2 _a2;
    };

    template<typename A1, typename A2>
    static void* startThreadStatic2(void* data) {
        ThreadDataStatic2<A1, A2>* pThreadData =
            reinterpret_cast<ThreadDataStatic2<A1, A2>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1, typename A2, typename A3>
    Thread(void (*pFunction)(A1, A2, A3), A1 a1, A2 a2, A3 a3) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1, a2, a3);
    }

    template<typename A1, typename A2, typename A3>
    void start(void (*pFunction)(A1, A2, A3), A1 a1, A2 a2, A3 a3) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic3<A1, A2, A3>* pThreadData =
            new ThreadDataStatic3<A1, A2, A3>(pFunction, a1, a2, a3);
        int result = pthread_create(
            &_id, _attr, &startThreadStatic3<A1, A2, A3>, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1, typename A2, typename A3>
    struct ThreadDataStatic3 {
        ThreadDataStatic3(void (*pFunction)(A1, A2, A3), A1 a1, A2 a2, A3 a3) :
            _pFunction(pFunction),
            _a1(a1),
            _a2(a2),
            _a3(a3) {}
        void call() {
            (*_pFunction)(_a1, _a2, _a3);
        }
        void (*_pFunction)(A1, A2, A3);
        A1 _a1;
        A2 _a2;
        A3 _a3;
    };

    template<typename A1, typename A2, typename A3>
    static void* startThreadStatic3(void* data) {
        ThreadDataStatic3<A1, A2, A3>* pThreadData =
            reinterpret_cast<ThreadDataStatic3<A1, A2, A3>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1, typename A2, typename A3, typename A4>
    Thread(void (*pFunction)(A1, A2, A3, A4), A1 a1, A2 a2, A3 a3, A4 a4) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1, a2, a3, a4);
    }

    template<typename A1, typename A2, typename A3, typename A4>
    void start(void (*pFunction)(A1, A2, A3, A4), A1 a1, A2 a2, A3 a3, A4 a4) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic4<A1, A2, A3, A4>* pThreadData =
            new ThreadDataStatic4<A1, A2, A3, A4>(pFunction, a1, a2, a3, a4);
        int result = pthread_create(
            &_id, _attr, &startThreadStatic4<A1, A2, A3, A4>, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1, typename A2, typename A3, typename A4>
    struct ThreadDataStatic4 {
        ThreadDataStatic4(void (*pFunction)(A1, A2, A3, A4), A1 a1, A2 a2,
                          A3 a3, A4 a4) :
            _pFunction(pFunction),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4) {}
        void call() {
            (*_pFunction)(_a1, _a2, _a3, _a4);
        }
        void (*_pFunction)(A1, A2, A3, A4);
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
    };

    template<typename A1, typename A2, typename A3, typename A4>
    static void* startThreadStatic4(void* data) {
        ThreadDataStatic4<A1, A2, A3, A4>* pThreadData =
            reinterpret_cast<ThreadDataStatic4<A1, A2, A3, A4>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1, typename A2, typename A3, typename A4, typename A5>
    Thread(void (*pFunction)(A1, A2, A3, A4, A5), A1 a1, A2 a2, A3 a3, A4 a4,
           A5 a5) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1, a2, a3, a4, a5);
    }

    template<typename A1, typename A2, typename A3, typename A4, typename A5>
    void start(void (*pFunction)(A1, A2, A3, A4, A5), A1 a1, A2 a2, A3 a3,
               A4 a4, A5 a5) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic5<A1, A2, A3, A4, A5>* pThreadData =
            new ThreadDataStatic5<A1, A2, A3, A4, A5>(pFunction, a1, a2, a3, a4,
                                                      a5);
        int result = pthread_create(
            &_id, _attr, &startThreadStatic5<A1, A2, A3, A4, A5>, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1, typename A2, typename A3, typename A4, typename A5>
    struct ThreadDataStatic5 {
        ThreadDataStatic5(void (*pFunction)(A1, A2, A3, A4, A5), A1 a1, A2 a2,
                          A3 a3, A4 a4, A5 a5) :
            _pFunction(pFunction),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5) {}
        void call() {
            (*_pFunction)(_a1, _a2, _a3, _a4, _a5);
        }
        void (*_pFunction)(A1, A2, A3, A4, A5);
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
    };

    template<typename A1, typename A2, typename A3, typename A4, typename A5>
    static void* startThreadStatic5(void* data) {
        ThreadDataStatic5<A1, A2, A3, A4, A5>* pThreadData =
            reinterpret_cast<ThreadDataStatic5<A1, A2, A3, A4, A5>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6>
    Thread(void (*pFunction)(A1, A2, A3, A4, A5, A6), A1 a1, A2 a2, A3 a3,
           A4 a4, A5 a5, A6 a6) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1, a2, a3, a4, a5, a6);
    }

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6>
    void start(void (*pFunction)(A1, A2, A3, A4, A5, A6), A1 a1, A2 a2, A3 a3,
               A4 a4, A5 a5, A6 a6) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic6<A1, A2, A3, A4, A5, A6>* pThreadData =
            new ThreadDataStatic6<A1, A2, A3, A4, A5, A6>(pFunction, a1, a2, a3,
                                                          a4, a5, a6);
        int result = pthread_create(&_id, _attr,
                                    &startThreadStatic6<A1, A2, A3, A4, A5, A6>,
                                    pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6>
    struct ThreadDataStatic6 {
        ThreadDataStatic6(void (*pFunction)(A1, A2, A3, A4, A5, A6), A1 a1,
                          A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) :
            _pFunction(pFunction),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6) {}
        void call() {
            (*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6);
        }
        void (*_pFunction)(A1, A2, A3, A4, A5, A6);
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
    };

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6>
    static void* startThreadStatic6(void* data) {
        ThreadDataStatic6<A1, A2, A3, A4, A5, A6>* pThreadData =
            reinterpret_cast<ThreadDataStatic6<A1, A2, A3, A4, A5, A6>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7>
    Thread(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7), A1 a1, A2 a2, A3 a3,
           A4 a4, A5 a5, A6 a6, A7 a7) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1, a2, a3, a4, a5, a6, a7);
    }

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7>
    void start(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7), A1 a1, A2 a2,
               A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic7<A1, A2, A3, A4, A5, A6, A7>* pThreadData =
            new ThreadDataStatic7<A1, A2, A3, A4, A5, A6, A7>(
                pFunction, a1, a2, a3, a4, a5, a6, a7);
        int result = pthread_create(
            &_id, _attr, &startThreadStatic7<A1, A2, A3, A4, A5, A6, A7>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7>
    struct ThreadDataStatic7 {
        ThreadDataStatic7(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7), A1 a1,
                          A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) :
            _pFunction(pFunction),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7) {}
        void call() {
            (*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7);
        }
        void (*_pFunction)(A1, A2, A3, A4, A5, A6, A7);
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
    };

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7>
    static void* startThreadStatic7(void* data) {
        ThreadDataStatic7<A1, A2, A3, A4, A5, A6, A7>* pThreadData =
            reinterpret_cast<ThreadDataStatic7<A1, A2, A3, A4, A5, A6, A7>*>(
                data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8>
    Thread(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8), A1 a1, A2 a2,
           A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8>
    void start(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8), A1 a1, A2 a2,
               A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic8<A1, A2, A3, A4, A5, A6, A7, A8>* pThreadData =
            new ThreadDataStatic8<A1, A2, A3, A4, A5, A6, A7, A8>(
                pFunction, a1, a2, a3, a4, a5, a6, a7, a8);
        int result = pthread_create(
            &_id, _attr, &startThreadStatic8<A1, A2, A3, A4, A5, A6, A7, A8>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8>
    struct ThreadDataStatic8 {
        ThreadDataStatic8(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8),
                          A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
                          A8 a8) :
            _pFunction(pFunction),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7),
            _a8(a8) {}
        void call() {
            (*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8);
        }
        void (*_pFunction)(A1, A2, A3, A4, A5, A6, A7, A8);
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
        A8 _a8;
    };

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8>
    static void* startThreadStatic8(void* data) {
        ThreadDataStatic8<A1, A2, A3, A4, A5, A6, A7, A8>* pThreadData =
            reinterpret_cast<
                ThreadDataStatic8<A1, A2, A3, A4, A5, A6, A7, A8>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8, typename A9>
    Thread(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9), A1 a1, A2 a2,
           A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8, typename A9>
    void start(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9), A1 a1,
               A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic9<A1, A2, A3, A4, A5, A6, A7, A8, A9>* pThreadData =
            new ThreadDataStatic9<A1, A2, A3, A4, A5, A6, A7, A8, A9>(
                pFunction, a1, a2, a3, a4, a5, a6, a7, a8, a9);
        int result = pthread_create(
            &_id, _attr,
            &startThreadStatic9<A1, A2, A3, A4, A5, A6, A7, A8, A9>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8, typename A9>
    struct ThreadDataStatic9 {
        ThreadDataStatic9(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9),
                          A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
                          A8 a8, A9 a9) :
            _pFunction(pFunction),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7),
            _a8(a8),
            _a9(a9) {}
        void call() {
            (*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9);
        }
        void (*_pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
        A8 _a8;
        A9 _a9;
    };

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8, typename A9>
    static void* startThreadStatic9(void* data) {
        ThreadDataStatic9<A1, A2, A3, A4, A5, A6, A7, A8, A9>* pThreadData =
            reinterpret_cast<
                ThreadDataStatic9<A1, A2, A3, A4, A5, A6, A7, A8, A9>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8, typename A9, typename A10>
    Thread(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), A1 a1,
           A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8, typename A9, typename A10>
    void start(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10),
               A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9,
               A10 a10) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataStatic10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>*
            pThreadData =
                new ThreadDataStatic10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>(
                    pFunction, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
        int result = pthread_create(
            &_id, _attr,
            &startThreadStatic10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8, typename A9, typename A10>
    struct ThreadDataStatic10 {
        ThreadDataStatic10(void (*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9,
                                             A10),
                           A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
                           A8 a8, A9 a9, A10 a10) :
            _pFunction(pFunction),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7),
            _a8(a8),
            _a9(a9),
            _a10(a10) {}
        void call() {
            (*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10);
        }
        void (*_pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
        A8 _a8;
        A9 _a9;
        A10 _a10;
    };

    template<typename A1, typename A2, typename A3, typename A4, typename A5,
             typename A6, typename A7, typename A8, typename A9, typename A10>
    static void* startThreadStatic10(void* data) {
        ThreadDataStatic10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>*
            pThreadData = reinterpret_cast<
                ThreadDataStatic10<A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>*>(
                data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class>
    Thread(void (Class::*pFunction)(), Class* pObject) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject);
    }

    template<typename Class>
    void start(void (Class::*pFunction)(), Class* pObject) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod0<Class>* pThreadData =
            new ThreadDataMethod0<Class>(pFunction, pObject);
        int result = pthread_create(&_id, _attr, &startThreadMethod0<Class>,
                                    pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class>
    struct ThreadDataMethod0 {
        ThreadDataMethod0(void (Class::*pFunction)(), Class* pObject) :
            _pFunction(pFunction),
            _pObject(pObject) {}
        void call() {
            (_pObject->*_pFunction)();
        }
        void (Class::*_pFunction)();
        Class* _pObject;
    };

    template<typename Class>
    static void* startThreadMethod0(void* data) {
        ThreadDataMethod0<Class>* pThreadData =
            reinterpret_cast<ThreadDataMethod0<Class>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1>
    Thread(void (Class::*pFunction)(A1), Class* pObject, A1 a1) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1);
    }

    template<typename Class, typename A1>
    void start(void (Class::*pFunction)(A1), Class* pObject, A1 a1) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod1<Class, A1>* pThreadData =
            new ThreadDataMethod1<Class, A1>(pFunction, pObject, a1);
        int result = pthread_create(&_id, _attr, &startThreadMethod1<Class, A1>,
                                    pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1>
    struct ThreadDataMethod1 {
        ThreadDataMethod1(void (Class::*pFunction)(A1), Class* pObject, A1 a1) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1) {}
        void call() {
            (_pObject->*_pFunction)(_a1);
        }
        void (Class::*_pFunction)(A1);
        Class* _pObject;
        A1 _a1;
    };

    template<typename Class, typename A1>
    static void* startThreadMethod1(void* data) {
        ThreadDataMethod1<Class, A1>* pThreadData =
            reinterpret_cast<ThreadDataMethod1<Class, A1>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2>
    Thread(void (Class::*pFunction)(A1, A2), Class* pObject, A1 a1, A2 a2) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2);
    }

    template<typename Class, typename A1, typename A2>
    void start(void (Class::*pFunction)(A1, A2), Class* pObject, A1 a1, A2 a2) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod2<Class, A1, A2>* pThreadData =
            new ThreadDataMethod2<Class, A1, A2>(pFunction, pObject, a1, a2);
        int result = pthread_create(
            &_id, _attr, &startThreadMethod2<Class, A1, A2>, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2>
    struct ThreadDataMethod2 {
        ThreadDataMethod2(void (Class::*pFunction)(A1, A2), Class* pObject,
                          A1 a1, A2 a2) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2);
        }
        void (Class::*_pFunction)(A1, A2);
        Class* _pObject;
        A1 _a1;
        A2 _a2;
    };

    template<typename Class, typename A1, typename A2>
    static void* startThreadMethod2(void* data) {
        ThreadDataMethod2<Class, A1, A2>* pThreadData =
            reinterpret_cast<ThreadDataMethod2<Class, A1, A2>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3>
    Thread(void (Class::*pFunction)(A1, A2, A3), Class* pObject, A1 a1, A2 a2,
           A3 a3) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3);
    }

    template<typename Class, typename A1, typename A2, typename A3>
    void start(void (Class::*pFunction)(A1, A2, A3), Class* pObject, A1 a1,
               A2 a2, A3 a3) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod3<Class, A1, A2, A3>* pThreadData =
            new ThreadDataMethod3<Class, A1, A2, A3>(pFunction, pObject, a1, a2,
                                                     a3);
        int result = pthread_create(
            &_id, _attr, &startThreadMethod3<Class, A1, A2, A3>, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3>
    struct ThreadDataMethod3 {
        ThreadDataMethod3(void (Class::*pFunction)(A1, A2, A3), Class* pObject,
                          A1 a1, A2 a2, A3 a3) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3);
        }
        void (Class::*_pFunction)(A1, A2, A3);
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
    };

    template<typename Class, typename A1, typename A2, typename A3>
    static void* startThreadMethod3(void* data) {
        ThreadDataMethod3<Class, A1, A2, A3>* pThreadData =
            reinterpret_cast<ThreadDataMethod3<Class, A1, A2, A3>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4), Class* pObject, A1 a1,
           A2 a2, A3 a3, A4 a4) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4>
    void start(void (Class::*pFunction)(A1, A2, A3, A4), Class* pObject, A1 a1,
               A2 a2, A3 a3, A4 a4) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod4<Class, A1, A2, A3, A4>* pThreadData =
            new ThreadDataMethod4<Class, A1, A2, A3, A4>(pFunction, pObject, a1,
                                                         a2, a3, a4);
        int result = pthread_create(&_id, _attr,
                                    &startThreadMethod4<Class, A1, A2, A3, A4>,
                                    pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4>
    struct ThreadDataMethod4 {
        ThreadDataMethod4(void (Class::*pFunction)(A1, A2, A3, A4),
                          Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4);
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4>
    static void* startThreadMethod4(void* data) {
        ThreadDataMethod4<Class, A1, A2, A3, A4>* pThreadData =
            reinterpret_cast<ThreadDataMethod4<Class, A1, A2, A3, A4>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5), Class* pObject, A1 a1,
           A2 a2, A3 a3, A4 a4, A5 a5) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5), Class* pObject,
               A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod5<Class, A1, A2, A3, A4, A5>* pThreadData =
            new ThreadDataMethod5<Class, A1, A2, A3, A4, A5>(
                pFunction, pObject, a1, a2, a3, a4, a5);
        int result = pthread_create(
            &_id, _attr, &startThreadMethod5<Class, A1, A2, A3, A4, A5>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5>
    struct ThreadDataMethod5 {
        ThreadDataMethod5(void (Class::*pFunction)(A1, A2, A3, A4, A5),
                          Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5);
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5>
    static void* startThreadMethod5(void* data) {
        ThreadDataMethod5<Class, A1, A2, A3, A4, A5>* pThreadData =
            reinterpret_cast<ThreadDataMethod5<Class, A1, A2, A3, A4, A5>*>(
                data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6), Class* pObject,
           A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6), Class* pObject,
               A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod6<Class, A1, A2, A3, A4, A5, A6>* pThreadData =
            new ThreadDataMethod6<Class, A1, A2, A3, A4, A5, A6>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6);
        int result = pthread_create(
            &_id, _attr, &startThreadMethod6<Class, A1, A2, A3, A4, A5, A6>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6>
    struct ThreadDataMethod6 {
        ThreadDataMethod6(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6),
                          Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
                          A6 a6) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6);
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6>
    static void* startThreadMethod6(void* data) {
        ThreadDataMethod6<Class, A1, A2, A3, A4, A5, A6>* pThreadData =
            reinterpret_cast<ThreadDataMethod6<Class, A1, A2, A3, A4, A5, A6>*>(
                data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7), Class* pObject,
           A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6, a7);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7),
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6,
               A7 a7) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod7<Class, A1, A2, A3, A4, A5, A6, A7>* pThreadData =
            new ThreadDataMethod7<Class, A1, A2, A3, A4, A5, A6, A7>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6, a7);
        int result = pthread_create(
            &_id, _attr, &startThreadMethod7<Class, A1, A2, A3, A4, A5, A6, A7>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7>
    struct ThreadDataMethod7 {
        ThreadDataMethod7(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7),
                          Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
                          A6 a6, A7 a7) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6, A7);
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7>
    static void* startThreadMethod7(void* data) {
        ThreadDataMethod7<Class, A1, A2, A3, A4, A5, A6, A7>* pThreadData =
            reinterpret_cast<
                ThreadDataMethod7<Class, A1, A2, A3, A4, A5, A6, A7>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8),
           Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
           A8 a8) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8),
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
               A8 a8) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod8<Class, A1, A2, A3, A4, A5, A6, A7, A8>* pThreadData =
            new ThreadDataMethod8<Class, A1, A2, A3, A4, A5, A6, A7, A8>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8);
        int result = pthread_create(
            &_id, _attr,
            &startThreadMethod8<Class, A1, A2, A3, A4, A5, A6, A7, A8>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8>
    struct ThreadDataMethod8 {
        ThreadDataMethod8(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7,
                                                   A8),
                          Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
                          A6 a6, A7 a7, A8 a8) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7),
            _a8(a8) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6, A7, A8);
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
        A8 _a8;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8>
    static void* startThreadMethod8(void* data) {
        ThreadDataMethod8<Class, A1, A2, A3, A4, A5, A6, A7, A8>* pThreadData =
            reinterpret_cast<
                ThreadDataMethod8<Class, A1, A2, A3, A4, A5, A6, A7, A8>*>(
                data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9),
           Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
           A8 a8, A9 a9) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9),
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
               A8 a8, A9 a9) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod9<Class, A1, A2, A3, A4, A5, A6, A7, A8,
                          A9>* pThreadData =
            new ThreadDataMethod9<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8, a9);
        int result = pthread_create(
            &_id, _attr,
            &startThreadMethod9<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9>
    struct ThreadDataMethod9 {
        ThreadDataMethod9(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7,
                                                   A8, A9),
                          Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
                          A6 a6, A7 a7, A8 a8, A9 a9) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7),
            _a8(a8),
            _a9(a9) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8,
                                    _a9);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
        A8 _a8;
        A9 _a9;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9>
    static void* startThreadMethod9(void* data) {
        ThreadDataMethod9<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9>*
            pThreadData = reinterpret_cast<
                ThreadDataMethod9<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9>*>(
                data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9,
             typename A10>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10),
           Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
           A8 a8, A9 a9, A10 a10) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9,
             typename A10>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9,
                                        A10),
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
               A8 a8, A9 a9, A10 a10) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethod10<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>*
            pThreadData = new ThreadDataMethod10<Class, A1, A2, A3, A4, A5, A6,
                                                 A7, A8, A9, A10>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
        int result =
            pthread_create(&_id, _attr,
                           &startThreadMethod10<Class, A1, A2, A3, A4, A5, A6,
                                                A7, A8, A9, A10>,
                           pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9,
             typename A10>
    struct ThreadDataMethod10 {
        ThreadDataMethod10(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7,
                                                    A8, A9, A10),
                           Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
                           A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7),
            _a8(a8),
            _a9(a9),
            _a10(a10) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9,
                                    _a10);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
        A8 _a8;
        A9 _a9;
        A10 _a10;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9,
             typename A10>
    static void* startThreadMethod10(void* data) {
        ThreadDataMethod10<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9,
                           A10>* pThreadData =
            reinterpret_cast<ThreadDataMethod10<Class, A1, A2, A3, A4, A5, A6,
                                                A7, A8, A9, A10>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class>
    Thread(void (Class::*pFunction)() const, Class* pObject) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject);
    }

    template<typename Class>
    void start(void (Class::*pFunction)() const, Class* pObject) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst0<Class>* pThreadData =
            new ThreadDataMethodConst0<Class>(pFunction, pObject);
        int result = pthread_create(
            &_id, _attr, &startThreadMethodConst0<Class>, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class>
    struct ThreadDataMethodConst0 {
        ThreadDataMethodConst0(void (Class::*pFunction)() const,
                               Class* pObject) :
            _pFunction(pFunction),
            _pObject(pObject) {}
        void call() {
            (_pObject->*_pFunction)();
        }
        void (Class::*_pFunction)() const;
        Class* _pObject;
    };

    template<typename Class>
    static void* startThreadMethodConst0(void* data) {
        ThreadDataMethodConst0<Class>* pThreadData =
            reinterpret_cast<ThreadDataMethodConst0<Class>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1>
    Thread(void (Class::*pFunction)(A1) const, Class* pObject, A1 a1) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1);
    }

    template<typename Class, typename A1>
    void start(void (Class::*pFunction)(A1) const, Class* pObject, A1 a1) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst1<Class, A1>* pThreadData =
            new ThreadDataMethodConst1<Class, A1>(pFunction, pObject, a1);
        int result = pthread_create(
            &_id, _attr, &startThreadMethodConst1<Class, A1>, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1>
    struct ThreadDataMethodConst1 {
        ThreadDataMethodConst1(void (Class::*pFunction)(A1) const,
                               Class* pObject, A1 a1) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1) {}
        void call() {
            (_pObject->*_pFunction)(_a1);
        }
        void (Class::*_pFunction)(A1) const;
        Class* _pObject;
        A1 _a1;
    };

    template<typename Class, typename A1>
    static void* startThreadMethodConst1(void* data) {
        ThreadDataMethodConst1<Class, A1>* pThreadData =
            reinterpret_cast<ThreadDataMethodConst1<Class, A1>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2>
    Thread(void (Class::*pFunction)(A1, A2) const, Class* pObject, A1 a1,
           A2 a2) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2);
    }

    template<typename Class, typename A1, typename A2>
    void start(void (Class::*pFunction)(A1, A2) const, Class* pObject, A1 a1,
               A2 a2) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst2<Class, A1, A2>* pThreadData =
            new ThreadDataMethodConst2<Class, A1, A2>(pFunction, pObject, a1,
                                                      a2);
        int result = pthread_create(
            &_id, _attr, &startThreadMethodConst2<Class, A1, A2>, pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2>
    struct ThreadDataMethodConst2 {
        ThreadDataMethodConst2(void (Class::*pFunction)(A1, A2) const,
                               Class* pObject, A1 a1, A2 a2) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2);
        }
        void (Class::*_pFunction)(A1, A2) const;
        Class* _pObject;
        A1 _a1;
        A2 _a2;
    };

    template<typename Class, typename A1, typename A2>
    static void* startThreadMethodConst2(void* data) {
        ThreadDataMethodConst2<Class, A1, A2>* pThreadData =
            reinterpret_cast<ThreadDataMethodConst2<Class, A1, A2>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3>
    Thread(void (Class::*pFunction)(A1, A2, A3) const, Class* pObject, A1 a1,
           A2 a2, A3 a3) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3);
    }

    template<typename Class, typename A1, typename A2, typename A3>
    void start(void (Class::*pFunction)(A1, A2, A3) const, Class* pObject,
               A1 a1, A2 a2, A3 a3) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst3<Class, A1, A2, A3>* pThreadData =
            new ThreadDataMethodConst3<Class, A1, A2, A3>(pFunction, pObject,
                                                          a1, a2, a3);
        int result = pthread_create(&_id, _attr,
                                    &startThreadMethodConst3<Class, A1, A2, A3>,
                                    pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3>
    struct ThreadDataMethodConst3 {
        ThreadDataMethodConst3(void (Class::*pFunction)(A1, A2, A3) const,
                               Class* pObject, A1 a1, A2 a2, A3 a3) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3);
        }
        void (Class::*_pFunction)(A1, A2, A3) const;
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
    };

    template<typename Class, typename A1, typename A2, typename A3>
    static void* startThreadMethodConst3(void* data) {
        ThreadDataMethodConst3<Class, A1, A2, A3>* pThreadData =
            reinterpret_cast<ThreadDataMethodConst3<Class, A1, A2, A3>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4) const, Class* pObject,
           A1 a1, A2 a2, A3 a3, A4 a4) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4>
    void start(void (Class::*pFunction)(A1, A2, A3, A4) const, Class* pObject,
               A1 a1, A2 a2, A3 a3, A4 a4) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst4<Class, A1, A2, A3, A4>* pThreadData =
            new ThreadDataMethodConst4<Class, A1, A2, A3, A4>(
                pFunction, pObject, a1, a2, a3, a4);
        int result = pthread_create(
            &_id, _attr, &startThreadMethodConst4<Class, A1, A2, A3, A4>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4>
    struct ThreadDataMethodConst4 {
        ThreadDataMethodConst4(void (Class::*pFunction)(A1, A2, A3, A4) const,
                               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4) const;
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4>
    static void* startThreadMethodConst4(void* data) {
        ThreadDataMethodConst4<Class, A1, A2, A3, A4>* pThreadData =
            reinterpret_cast<ThreadDataMethodConst4<Class, A1, A2, A3, A4>*>(
                data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5) const, Class* pObject,
           A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5) const,
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst5<Class, A1, A2, A3, A4, A5>* pThreadData =
            new ThreadDataMethodConst5<Class, A1, A2, A3, A4, A5>(
                pFunction, pObject, a1, a2, a3, a4, a5);
        int result = pthread_create(
            &_id, _attr, &startThreadMethodConst5<Class, A1, A2, A3, A4, A5>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5>
    struct ThreadDataMethodConst5 {
        ThreadDataMethodConst5(void (Class::*pFunction)(A1, A2, A3, A4, A5)
                                   const,
                               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4,
                               A5 a5) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5) const;
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5>
    static void* startThreadMethodConst5(void* data) {
        ThreadDataMethodConst5<Class, A1, A2, A3, A4, A5>* pThreadData =
            reinterpret_cast<
                ThreadDataMethodConst5<Class, A1, A2, A3, A4, A5>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6) const,
           Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6) const,
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst6<Class, A1, A2, A3, A4, A5, A6>* pThreadData =
            new ThreadDataMethodConst6<Class, A1, A2, A3, A4, A5, A6>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6);
        int result = pthread_create(
            &_id, _attr,
            &startThreadMethodConst6<Class, A1, A2, A3, A4, A5, A6>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6>
    struct ThreadDataMethodConst6 {
        ThreadDataMethodConst6(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6)
                                   const,
                               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4,
                               A5 a5, A6 a6) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6) const;
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6>
    static void* startThreadMethodConst6(void* data) {
        ThreadDataMethodConst6<Class, A1, A2, A3, A4, A5, A6>* pThreadData =
            reinterpret_cast<
                ThreadDataMethodConst6<Class, A1, A2, A3, A4, A5, A6>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7) const,
           Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6, a7);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7) const,
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6,
               A7 a7) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst7<Class, A1, A2, A3, A4, A5, A6, A7>* pThreadData =
            new ThreadDataMethodConst7<Class, A1, A2, A3, A4, A5, A6, A7>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6, a7);
        int result = pthread_create(
            &_id, _attr,
            &startThreadMethodConst7<Class, A1, A2, A3, A4, A5, A6, A7>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7>
    struct ThreadDataMethodConst7 {
        ThreadDataMethodConst7(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6,
                                                        A7) const,
                               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4,
                               A5 a5, A6 a6, A7 a7) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6, A7) const;
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7>
    static void* startThreadMethodConst7(void* data) {
        ThreadDataMethodConst7<Class, A1, A2, A3, A4, A5, A6, A7>* pThreadData =
            reinterpret_cast<
                ThreadDataMethodConst7<Class, A1, A2, A3, A4, A5, A6, A7>*>(
                data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8) const,
           Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
           A8 a8) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8) const,
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
               A8 a8) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst8<Class, A1, A2, A3, A4, A5, A6, A7,
                               A8>* pThreadData =
            new ThreadDataMethodConst8<Class, A1, A2, A3, A4, A5, A6, A7, A8>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8);
        int result = pthread_create(
            &_id, _attr,
            &startThreadMethodConst8<Class, A1, A2, A3, A4, A5, A6, A7, A8>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8>
    struct ThreadDataMethodConst8 {
        ThreadDataMethodConst8(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6,
                                                        A7, A8) const,
                               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4,
                               A5 a5, A6 a6, A7 a7, A8 a8) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7),
            _a8(a8) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6, A7, A8) const;
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
        A8 _a8;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8>
    static void* startThreadMethodConst8(void* data) {
        ThreadDataMethodConst8<Class, A1, A2, A3, A4, A5, A6, A7, A8>*
            pThreadData = reinterpret_cast<
                ThreadDataMethodConst8<Class, A1, A2, A3, A4, A5, A6, A7, A8>*>(
                data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const,
           Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
           A8 a8, A9 a9) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9)
                   const,
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
               A8 a8, A9 a9) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst9<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9>*
            pThreadData = new ThreadDataMethodConst9<Class, A1, A2, A3, A4, A5,
                                                     A6, A7, A8, A9>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8, a9);
        int result = pthread_create(
            &_id, _attr,
            &startThreadMethodConst9<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9>,
            pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9>
    struct ThreadDataMethodConst9 {
        ThreadDataMethodConst9(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6,
                                                        A7, A8, A9) const,
                               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4,
                               A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7),
            _a8(a8),
            _a9(a9) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8,
                                    _a9);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const;
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
        A8 _a8;
        A9 _a9;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9>
    static void* startThreadMethodConst9(void* data) {
        ThreadDataMethodConst9<Class, A1, A2, A3, A4, A5, A6, A7, A8,
                               A9>* pThreadData =
            reinterpret_cast<ThreadDataMethodConst9<Class, A1, A2, A3, A4, A5,
                                                    A6, A7, A8, A9>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }

  public:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9,
             typename A10>
    Thread(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)
               const,
           Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
           A8 a8, A9 a9, A10 a10) :
        _id(0),
        _isDetached(false),
        _attr(NULL) {
        start(pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9,
             typename A10>
    void start(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)
                   const,
               Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
               A8 a8, A9 a9, A10 a10) {
        if (_id != 0) {
            throw Exception(_id, "Thread already started");
        }
        ThreadDataMethodConst10<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>*
            pThreadData = new ThreadDataMethodConst10<Class, A1, A2, A3, A4, A5,
                                                      A6, A7, A8, A9, A10>(
                pFunction, pObject, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
        int result =
            pthread_create(&_id, _attr,
                           &startThreadMethodConst10<Class, A1, A2, A3, A4, A5,
                                                     A6, A7, A8, A9, A10>,
                           pThreadData);
        if (result != 0) {
            delete pThreadData;
            throw Exception(_id, "Failed to create thread");
        }
    }

  private:
    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9,
             typename A10>
    struct ThreadDataMethodConst10 {
        ThreadDataMethodConst10(void (Class::*pFunction)(A1, A2, A3, A4, A5, A6,
                                                         A7, A8, A9, A10) const,
                                Class* pObject, A1 a1, A2 a2, A3 a3, A4 a4,
                                A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) :
            _pFunction(pFunction),
            _pObject(pObject),
            _a1(a1),
            _a2(a2),
            _a3(a3),
            _a4(a4),
            _a5(a5),
            _a6(a6),
            _a7(a7),
            _a8(a8),
            _a9(a9),
            _a10(a10) {}
        void call() {
            (_pObject->*_pFunction)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9,
                                    _a10);
        }
        void (Class::*_pFunction)(A1, A2, A3, A4, A5, A6, A7, A8, A9,
                                  A10) const;
        Class* _pObject;
        A1 _a1;
        A2 _a2;
        A3 _a3;
        A4 _a4;
        A5 _a5;
        A6 _a6;
        A7 _a7;
        A8 _a8;
        A9 _a9;
        A10 _a10;
    };

    template<typename Class, typename A1, typename A2, typename A3, typename A4,
             typename A5, typename A6, typename A7, typename A8, typename A9,
             typename A10>
    static void* startThreadMethodConst10(void* data) {
        ThreadDataMethodConst10<Class, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>*
            pThreadData = reinterpret_cast<ThreadDataMethodConst10<
                Class, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>*>(data);
        pThreadData->call();
        delete pThreadData;
        return NULL;
    }
};

} // namespace blet

#endif // #ifndef _BLET_THREAD_H_