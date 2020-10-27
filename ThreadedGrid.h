#ifndef _THREADED_GRID_H
#define _THREADED_GRID_H
#include "ThreadedVector.h"
#include "NumberGrid.h"
#include <thread>
#include <vector>

class GridTask {
    public:
        int row;
};

class ThreadedGrid: public NumberGrid {
    public:
        ThreadedGrid();
        ThreadedGrid( const int& height, const int& width);
        virtual ~ThreadedGrid();
        virtual void calculateAllNumbers();
        virtual void worker();
    protected:
        ThreadedVector<GridTask> mTasks;
};

#endif