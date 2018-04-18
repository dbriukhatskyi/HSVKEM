/*
 * IncFile1.h
 *
 * Created: 27.04.2017 10:40:58
 *  Author: dmitry
 */ 


#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#define CONTAINER_CAPACITY 32

typedef void(*action_t)(uint8_t);

class CTaskManager {
    public:
        CTaskManager();
        uint8_t addTask(action_t action, uint8_t arg, uint32_t startTimeMillis);
        uint8_t size();
        void removeTask(uint8_t taskID);
        void process();

    private:
        action_t[CONTAINER_CAPACITY] actions;
        uint8_t[CONTAINER_CAPACITY] arguments;
        uint32_t[CONTAINER_CAPACITY] startTimes;
        bool[CONTAINER_CAPACITY] active;
        uint8_t currentSize;
        uint8_t lastPosition;
};



#endif /* TASKMANAGER_H_ */