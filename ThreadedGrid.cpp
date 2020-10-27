#include "ThreadedGrid.h"
ThreadedGrid::ThreadedGrid() 
    : NumberGrid(), mTasks(){
}

ThreadedGrid::ThreadedGrid(const int& height, const int& width)
    : NumberGrid(height, width), mTasks(){
}

ThreadedGrid::~ThreadedGrid(){}

void ThreadedGrid::calculateAllNumbers(){
    unsigned int max_threads = std::thread::hardware_concurrency();
    int row;
    for(row=0; row<mHeight; row++){
        GridTask task;
        task.row = row;
        mTasks.push_back(task);
    }

    std::vector<std::thread> threads;
    int i;
    for(i=0; i< int(max_threads); i++){
        threads.push_back(std::thread(&ThreadedGrid::worker, this));
    }
    for(i=0; i<int(max_threads); i++){
        threads[i].join();
    }
}

void ThreadedGrid::worker(){
    std::vector<GridTask> my_tasks;
    while(!mTasks.empty()){
        my_tasks.clear();
        mTasks.pop_back(my_tasks, 1);

        if(my_tasks.size() > 0){
            int column;
            for( column=0; column<mWidth; column++){
                int num = calculateNumber(my_tasks[0].row, column);
                setNumber(my_tasks[0].row, column, num);
            }
        }
    }
}