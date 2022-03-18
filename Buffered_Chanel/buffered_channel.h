#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

template<class T>
class BufferedChannel {
public:
 explicit BufferedChannel(int size) {
  buffer_size = size;
 }

 void Send(T value) {
	std::unique_lock<std::mutex> uLock(_lock);
	
	if (!is_opened) {
	 throw std::runtime_error("This channel is closed");
	}
	bool condition = (queue.size() != buffer_size);
	condition_var.wait(uLock, condition && is_opened);
	queue.push(value);
	uLock.unlock();
	condition_var.notify_one();
 }

 std::pair<T, bool> Recv() {
	std::unique_lock<std::mutex> uLock(_lock);
	condition_var.wait(uLock, !queue.empty() && is_opened);
	T value = queue.front();
	queue.pop();
	uLock.unlock();
	condition_var.notify_one();
	return std::make_pair(value, is_opened);
 }

 void Close() {
	std::unique_lock<std::mutex> uLock(_lock);
	is_opened = false;
	uLock.unlock();
	condition_var.notify_all();
 }

private:
 std::queue<T> queue;
 std::condition_variable condition_var;
 std::mutex _lock;
 int buffer_size;
 bool is_opened = true;
};