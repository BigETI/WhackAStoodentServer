#pragma once

#include <forward_list>
#include <functional>

namespace WhackAStoodentServer
{
	template <typename... Ts>
	class Event
	{
	public:

		Event()
		{
			// ...
		}

		Event(const Event& e)
		{
			*this = e;
		}

		Event(Event&& e)
		{
			*this = e;
		}

		virtual ~Event()
		{
			// ...
		}

		virtual bool IsEmpty() const
		{
			return listeners.empty();
		}

		virtual void Clear()
		{
			listeners.clear();
		}

		virtual Event& operator=(const Event& e)
		{
			listeners = e.listeners;
			return *this;
		}

		virtual Event& operator=(Event&& e)
		{
			listeners = e.listeners;
			return *this;
		}

		virtual Event& operator+=(const std::function<void(Ts...)>& listener)
		{
			listeners.push_front(listener);
			return *this;
		}

		virtual Event& operator+=(std::function<void(Ts...)>&& listener)
		{
			listeners.push_front(listener);
			return *this;
		}

		virtual Event operator+(const std::function<void(Ts...)>& listener)
		{
			return Event(*this) += listener;
		}

		virtual Event operator+(std::function<void(Ts...)>&& listener)
		{
			return Event(*this) += listener;
		}

		virtual void operator()(Ts... arguments)
		{
			for (const auto& listener : listeners)
			{
				listener(arguments...);
			}
		}

	private:

		std::forward_list<std::function<void(Ts...)>> listeners;
	};
}
