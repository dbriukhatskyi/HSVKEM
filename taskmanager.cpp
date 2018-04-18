/*
 * taskmanager.cpp
 *
 * Created: 27.04.2017 10:52:02
 *  Author: dmitry
 */ 
 /*
#include "include/taskmanager.h"

CTaskManager::CTaskManager() {
    currentSize = 0;
    lastPosition = 0;

    for (uint8_t i = 0; i < CONTAINER_CAPACITY; i++) {
        active[i] = false;
    }
}

uint8_t CTaskManager::addTask(action_t action, uint8_t arg, uint32_t startTimeMillis) {
    uint8_t foundSlot = 0xFF;

    for (uint8_t i = 0; i < CONTAINER_CAPACITY; i++) {
        uint8_t currentSlot = (i + lastPosition) & (CONTAINER_CAPACITY - 1);

        if (!active[currentSlot]) {
            foundSlot = currentSlot;
            break;
        }
    }

    if (foundSlot < CONTAINER_CAPACITY) {
        actions[foundSlot] = action;
        arguments[foundSlot] = arg;
        startTimes[foundSlot] = startTimeMillis;
        active[foundSlot] = true;

        lastPosition = (foundSlot + 1) & (CONTAINER_CAPACITY - 1);
    }

    return foundSlot;
}

uint8_t CTaskManager::size() {
    return currentSize;
}

void CTaskManager::removeTask(uint8_t taskID) {

}

void CTaskManager::process() {
    
}
*/