//##############################################################################
//## Project: ClAni ############################# Created by hury on 27.06.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_SCHEDULER_H
#define CLIANIMATION_SCHEDULER_H

#include <functional>
#include <future>
#include <deque>
#include <thread>


class Scheduler {
private:
    template<typename T>
    class ThreadSafeQueue {
    private:
        std::deque<T> m_Queue;
        std::mutex m_Mutex;
        std::condition_variable m_Cond;

    public:
        ThreadSafeQueue() = default;
        ThreadSafeQueue(const ThreadSafeQueue &t) = delete;

        /**
         * Removes the first element of the queue and returns it if the queue is not empty
         * @return shared_ptr to the first element or null if the queue is empty
         */
        [[nodiscard]] std::shared_ptr<T> try_pop() {
            std::unique_lock<std::mutex> mlock(m_Mutex);
            if (!m_Queue.empty()) {
                std::shared_ptr<T>(m_Queue.pop_front());
            } else {
                return nullptr;
            }
        }

        /**
         * Removes the first element of the queue and returns it.
         * If the queue is empty, this call blocks until at least one element is in the queue
         * @return Shared_ptr to the first element
         */
        [[nodiscard]] std::shared_ptr<T> wait_and_pop() {
            std::unique_lock<std::mutex> mlock(m_Mutex);
            while (m_Queue.empty())
            {
                m_Cond.wait(mlock);
            }
            return std::shared_ptr<T>(m_Queue.pop_front());
        }

        /**
         * Pushes the value to the end of the queue
         * @param value The value
         */
        void push(T value) {
            std::unique_lock<std::mutex> mlock(m_Mutex);
            m_Queue.push_back(value);
            mlock.unlock();     // unlock before notificiation to minimize mutex contention
            m_Cond.notify_one(); // notify one waiting thread
        }

        /**
         * Returns true if the queue is empty
         * @return True if the queue is empty
         */
        [[nodiscard]] bool empty() {
            std::unique_lock<std::mutex> mlock(m_Mutex);
            return m_Queue.empty();
        }
    };

    struct FunctionWrapper {
    private:
        struct impl_base
        {
            virtual void call() = 0;
            virtual ~impl_base() = default;
        };

        std::unique_ptr<impl_base> impl;

        template<typename F>
        struct impl_type : impl_base
        {
            F f;
            explicit impl_type(F&& f_): f(std::move(f_)) {}
            void call() override { f(); }
        };

    public:
        template<typename F>
        explicit FunctionWrapper(F&& f) : impl(new impl_type<F>(std::move(f))) {}
        FunctionWrapper(FunctionWrapper&& other) noexcept : impl(std::move(other.impl)) {}

        void call() { impl->call(); }

        FunctionWrapper& operator=(FunctionWrapper&& other) noexcept {
            impl = std::move(other.impl);
            return *this;
        }

        FunctionWrapper(const FunctionWrapper&) = delete;
        FunctionWrapper(FunctionWrapper&) = delete;
        FunctionWrapper& operator=(const FunctionWrapper&) = delete;
    };


    class StealQueue {
    private:
        using DataType = FunctionWrapper;
        std::deque<DataType> m_Queue;
        mutable std::mutex m_Mutex;
    public:
        StealQueue() = default;
        StealQueue(const StealQueue& queue) = delete;
        StealQueue& operator=(const StealQueue& queue) = delete;
        void push(DataType func);
        bool empty() const;
        bool try_pop(DataType& res);
        bool try_steal(DataType& res);
    };
    class ThreadPool {
    public:
        ThreadPool();
        ~ThreadPool();

        template<typename _ResultType>
        using TaskHandle = std::future<_ResultType>;

        template<typename _FunctionType>
        TaskHandle<typename std::invoke_result<_FunctionType>::type> submit(_FunctionType func);
        void run_pending_task();

    private:
        using _TaskType = FunctionWrapper;

        // Thread local management
        static thread_local StealQueue* m_LocalQueue;
        static thread_local uint32_t m_MyIndex;

        // Global management
        std::atomic_bool m_IsDone;
        ThreadSafeQueue<_TaskType> m_PoolQueue;
        std::vector<std::unique_ptr<StealQueue>> m_Queues;
        std::vector<std::thread> m_Threads;

        void worker_thread(uint32_t _my_index);
        bool pop_task_from_local_queue(_TaskType& task);
        bool pop_task_from_pool_queue(_TaskType& task);
        bool pop_task_from_other_thread_queue(_TaskType& task);

    };
public:
Scheduler();

};


#endif //CLIANIMATION_SCHEDULER_H