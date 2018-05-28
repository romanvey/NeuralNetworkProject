#ifndef ARCHIVE_TSAFE_QUEUE_H
#define ARCHIVE_TSAFE_QUEUE_H


#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template<typename Data>
class tsafe_queue
{
private:
    std::queue<Data> the_queue;
    mutable mutex the_mutex;
    condition_variable the_condition_variable;
public:
    void push(Data const& data);

    bool empty() const;
    int size() const;

    bool try_pop(Data& popped_value);
    bool try_pop2(Data& popped_value1, Data& popped_value2);

    void wait_and_pop(Data& popped_value);
    void wait_and_pop2(Data& popped_value1, Data& popped_value2);

    tsafe_queue() = default;
    tsafe_queue(const tsafe_queue&) = delete;
    tsafe_queue& operator=(const tsafe_queue&) = delete;
};


template<typename Data>
void tsafe_queue<Data>::push(Data const& data)
{

    std::unique_lock<std::mutex> lock(the_mutex);
    the_queue.push(data);
    lock.unlock();
    the_condition_variable.notify_one();
}
template<typename Data>
bool tsafe_queue<Data>::empty() const
{
    std::unique_lock<std::mutex> lock(the_mutex);
    return the_queue.empty();
}

template<typename Data>
int tsafe_queue<Data>::size() const
{
    std::unique_lock<std::mutex> lock(the_mutex);
    return the_queue.size();
}

template<typename Data>
bool tsafe_queue<Data>::try_pop(Data& popped_value)
{
    std::unique_lock<std::mutex> lock(the_mutex);
    if(the_queue.empty())
    {
        return false;
    }

    popped_value=the_queue.front();

    the_queue.pop();
    return true;
}

template<typename Data>
void tsafe_queue<Data>::wait_and_pop(Data& popped_value)
{
    std::unique_lock<std::mutex> lock(the_mutex);
    while(the_queue.empty())
    {
        the_condition_variable.wait(lock);
    }

    popped_value=the_queue.front();
    the_queue.pop();
}

template<typename Data>
void tsafe_queue<Data>::wait_and_pop2(Data& popped_value1, Data& popped_value2)
{
    std::unique_lock<std::mutex> lock(the_mutex);

    while(the_queue.size() < 2)
    {
        the_condition_variable.wait(lock);
    }

    popped_value1=the_queue.front();
    the_queue.pop();
    popped_value2=the_queue.front();
    the_queue.pop();
}

template<typename Data>
bool tsafe_queue<Data>::try_pop2(Data& popped_value1, Data& popped_value2)
{
    std::unique_lock<std::mutex> lock(the_mutex);
    if(the_queue.size() < 2)
    {
        return false;
    }
    popped_value1=the_queue.front();
    the_queue.pop();
    popped_value2=the_queue.front();
    the_queue.pop();
    return true;
}


#endif //ARCHIVE_TSAFE_QUEUE_H
