//##############################################################################
//## Project: ClAni ############################# Created by hury on 28.06.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <scheduler.h>

void Scheduler::StealQueue::push(DataType func) {
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_Queue.push_back(std::move(func));
}