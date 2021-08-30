#pragma once

#include <cstddef>
#include <mutex>
#include <queue>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a concurrent queue
	/// </summary>
	/// <typeparam name="T">Element type</typeparam>
	template <typename T>
	class ConcurrentQueue
	{
	public:

		/// <summary>
		/// Constructs a concurrrent queue
		/// </summary>
		ConcurrentQueue()
		{
			// ...
		}

		/// <summary>
		/// Constructs a concurrent queue from the specified concurrent queue
		/// </summary>
		/// <param name="concurrentQueue">Concurrent queue</param>
		ConcurrentQueue(const ConcurrentQueue& concurrentQueue) :
			queue(concurrentQueue.queue)
		{
			// ...
		}

		/// <summary>
		/// Constructs a concurrent queue from the specified concurrent queue
		/// </summary>
		/// <param name="concurrentQueue">Concurrent queue</param>
		ConcurrentQueue(ConcurrentQueue&& concurrentQueue) :
			queue(concurrentQueue.queue),
			mutex(concurrentQueue.mutex)
		{
			// ...
		}

		/// <summary>
		/// Destroys concurrent queue
		/// </summary>
		virtual ~ConcurrentQueue()
		{
			// ...
		}

		/// <summary>
		/// Enqueues element to queue
		/// </summary>
		/// <param name="element">Element</param>
		virtual void Enqueue(const T& element)
		{
			mutex.lock();
			queue.push(element);
			mutex.unlock();
		}

		/// <summary>
		/// Enqueues element to queue
		/// </summary>
		/// <param name="element">Element</param>
		virtual void Enqueue(T&& element)
		{
			mutex.lock();
			queue.push(element);
			mutex.unlock();
		}

		/// <summary>
		/// Tries to dequeue an element
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>"true" if an element has been successfully dequeued, otherwise "false"</returns>
		virtual bool TryDequeue(T& result)
		{
			mutex.lock();
			bool ret(!queue.empty());
			if (ret)
			{
				result = queue.front();
				queue.pop();
			}
			mutex.unlock();
			return ret;
		}

	private:

		/// <summary>
		/// Queue
		/// </summary>
		std::queue<T> queue;

		/// <summary>
		/// Mutex
		/// </summary>
		std::mutex mutex;
	};
}
