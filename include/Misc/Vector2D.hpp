#pragma once

#include <type_traits>

#include <Interfaces/ISerializable.hpp>
#include <Static/NumericSerializer.hpp>

namespace WhackAStoodentServer
{
	template <typename T>
	class Vector2D : ISerializable
	{
	public:

		static_assert(std::is_same<float, T>::value || std::is_same<double, T>::value);

		using ValueType = T;

		Vector2D() :
			x(0.0f),
			y(0.0f)
		{
			// ...
		}

		Vector2D(const Vector2D<T>& vector2D) :
			x(vector2D.x),
			y(vector2D.y)
		{
			// ...
		}

		Vector2D(Vector2D<T>&& vector2D) :
			x(vector2D.x),
			y(vector2D.y)
		{
			// ...
		}

		Vector2D(T x, T y) :
			x(x),
			y(y)
		{
			// ...
		}

		virtual ~Vector2D()
		{
			// ...
		}

		virtual inline T GetX() const
		{
			return x;
		}

		virtual inline T GetY() const
		{
			return y;
		}

		virtual Vector2D& operator=(const Vector2D<T>& vector2D)
		{
			x = vector2D.x;
			y = vector2D.y;
			return *this;
		}

		virtual Vector2D& operator=(Vector2D<T>&& vector2D) noexcept
		{
			x = vector2D.x;
			y = vector2D.y;
			return *this;
		}

		virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override
		{
			NumericSerializer::Serialize<T>(x, result);
			return NumericSerializer::Serialize<T>(y, result);
		}

		virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override
		{
			std::span<std::uint8_t const> next_bytes(NumericSerializer::Deserialize<T>(data, x));
			return NumericSerializer::Deserialize<T>(next_bytes, y);
		}

	private:

		T x;

		T y;
	};
}
