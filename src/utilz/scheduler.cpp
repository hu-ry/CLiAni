//##############################################################################
//## Project: ClAni ############################# Created by hury on 28.06.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <scheduler.h>
#include <cassert>
#include <memory>

void Scheduler::StealQueue::push(DataType func) {
    std::unique_lock<std::mutex> mlock(m_Mutex);
    m_Queue.push_back(std::move(func));
}

bool Scheduler::StealQueue::empty() const {
    std::unique_lock<std::mutex> mlock(m_Mutex);
    return m_Queue.empty();
}

bool Scheduler::StealQueue::try_pop(DataType& res) {
    std::unique_lock<std::mutex> mlock(m_Mutex);
    if(!m_Queue.empty()) {
        res = std::move(m_Queue.front());
        m_Queue.pop_front();
        return true;
    } else {
        return false;
    }
}

bool Scheduler::StealQueue::try_steal(DataType& res) {
    std::unique_lock<std::mutex> mlock(m_Mutex);
    if(!m_Queue.empty()) {
        res = std::move(m_Queue.back());
        m_Queue.pop_back();
        return true;
    } else {
        return false;
    }
}

Scheduler::ThreadPool::ThreadPool() : m_IsDone(false) {
    const uint32_t threadCount = std::thread::hardware_concurrency();
    try {
        m_Queues.reserve(threadCount);
        m_Threads.reserve(threadCount);
        for(auto i = 0; i < threadCount; i++) {
            m_Queues.push_back(std::make_unique<StealQueue>());
            m_Threads.emplace_back(&ThreadPool::worker_thread, this, i);
        }
    } catch(std::system_error& err) {
        m_IsDone = true;
        assert(false);
        throw;
    }
}

Scheduler::ThreadPool::~ThreadPool() {
    m_IsDone = true;
}

void Scheduler::ThreadPool::worker_thread(uint32_t _my_index) {
    m_MyIndex = _my_index;
    m_LocalQueue = m_Queues[m_MyIndex].get();
    while(!m_IsDone) {
        run_pending_task();
    }
}

bool Scheduler::ThreadPool::pop_task_from_local_queue(_TaskType &task) {
    return m_LocalQueue && m_LocalQueue->try_pop(task);
}

bool Scheduler::ThreadPool::pop_task_from_pool_queue(_TaskType& task) {
    return m_PoolQueue.try_pop(task);
}

bool Scheduler::ThreadPool::pop_task_from_other_thread_queue(Scheduler::ThreadPool::_TaskType &task) {
    for(uint32_t i = 0; i < m_Queues.size(); ++i) {
        const uint32_t index = (m_MyIndex + i + 1) % m_Queues.size();
        if(m_Queues[index]->try_steal(task)) {
            return true;
        }
    }
    return false;
}

template<typename _FunctionType>
std::future<typename std::invoke_result<_FunctionType>::type> Scheduler::ThreadPool::submit(_FunctionType func) {
    using _ResultType = std::invoke_result<_FunctionType>::type;

    const std::packaged_task<_ResultType()> task(func);
    std::future<_ResultType> result(task.get_future());
    if(m_LocalQueue) {
        m_LocalQueue->push(std::move(task));
    } else {
        m_PoolQueue.push(std::move(task));
    }
    return result;
}

void Scheduler::ThreadPool::run_pending_task() {
    _TaskType task;
    if(pop_task_from_local_queue(task) ||
       pop_task_from_pool_queue(task)  ||
       pop_task_from_other_thread_queue(task)
    ) {
        task();
    } else {
        std::this_thread::yield();
    }
}