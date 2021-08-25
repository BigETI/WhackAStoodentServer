#pragma once

#include <forward_list>
#include <functional>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes an event handler
	/// </summary>
	/// <typeparam name="...Ts">Event argument types</typeparam>
	template <typename... Ts>
	class Event
	{
	public:

		/// <summary>
		/// Constructs an event handler
		/// </summary>
		Event()
		{
			// ...
		}

		/// <summary>
		/// Constructs an event handler
		/// </summary>
		/// <param name="e">Event handler</param>
		Event(const Event& e)
		{
			*this = e;
		}

		/// <summary>
		/// Constructs an event handler
		/// </summary>
		/// <param name="e">Event handler</param>
		Event(Event&& e)
		{
			*this = e;
		}

		/// <summary>
		/// Destroys event handler
		/// </summary>
		virtual ~Event()
		{
			// ...
		}

		/// <summary>
		/// Is event handler empty
		/// </summary>
		/// <returns></returns>
		virtual bool IsEmpty() const
		{
			return listeners.empty();
		}

		/// <summary>
		/// Clears event handler
		/// </summary>
		virtual void Clear()
		{
			listeners.clear();
		}

		/// <summary>
		/// Assigns the specified event handler to this object
		/// </summary>
		/// <param name="e">Event handler</param>
		/// <returns>This object</returns>
		virtual Event& operator=(const Event& e)
		{
			listeners = e.listeners;
			return *this;
		}

		/// <summary>
		/// Assigns the specified event handler to this object
		/// </summary>
		/// <param name="e">Event handler</param>
		/// <returns>This object</returns>
		virtual Event& operator=(Event&& e)
		{
			listeners = e.listeners;
			return *this;
		}

		/// <summary>
		/// Subscribes a new event listener
		/// </summary>
		/// <param name="listener">Event listener</param>
		/// <returns>This object</returns>
		virtual Event& operator+=(const std::function<void(Ts...)>& listener)
		{
			listeners.push_front(listener);
			return *this;
		}

		/// <summary>
		/// Subscribes a new event listener
		/// </summary>
		/// <param name="listener">Event listener</param>
		/// <returns>This object</returns>
		virtual Event& operator+=(std::function<void(Ts...)>&& listener)
		{
			listeners.push_front(listener);
			return *this;
		}

		/// <summary>
		/// Subscribes a new event listener and creates a new object
		/// </summary>
		/// <param name="listener">Listener</param>
		/// <returns>Event handler</returns>
		virtual Event operator+(const std::function<void(Ts...)>& listener)
		{
			return Event(*this) += listener;
		}

		/// <summary>
		/// Subscribes a new event listener and creates a new object
		/// </summary>
		/// <param name="listener">Listener</param>
		/// <returns>Event handler</returns>
		virtual Event operator+(std::function<void(Ts...)>&& listener)
		{
			return Event(*this) += listener;
		}

		/// <summary>
		/// Invokes this event
		/// </summary>
		/// <param name="...arguments">Event arguments</param>
		virtual void operator()(Ts... arguments)
		{
			for (const auto& listener : listeners)
			{
				listener(arguments...);
			}
		}

	private:

		/// <summary>
		/// Event listeners
		/// </summary>
		std::forward_list<std::function<void(Ts...)>> listeners;
	};
}
