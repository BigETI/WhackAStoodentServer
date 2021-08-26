#pragma once

#include <type_traits>

#include <Interfaces/ISerializable.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a 2D vector
	/// </summary>
	/// <typeparam name="T">Vector component type</typeparam>
	template <typename T>
	class Vector2D : ISerializable
	{
	public:

		static_assert(std::is_same<float, T>::value || std::is_same<double, T>::value);

		/// <summary>
		/// Value type
		/// </summary>
		using ValueType = T;

		/// <summary>
		/// Constructs a new 2D vector
		/// </summary>
		Vector2D() :
			x(0.0f),
			y(0.0f)
		{
			// ...
		}

		/// <summary>
		/// Constructs a new 2D vector
		/// </summary>
		/// <param name="vector2D">2D vector</param>
		Vector2D(const Vector2D<T>& vector2D) :
			x(vector2D.x),
			y(vector2D.y)
		{
			// ...
		}

		/// <summary>
		/// Constructs a new 2D vector
		/// </summary>
		/// <param name="vector2D">2D vector</param>
		Vector2D(Vector2D<T>&& vector2D) :
			x(vector2D.x),
			y(vector2D.y)
		{
			// ...
		}

		/// <summary>
		/// Constructs a new 2D vector
		/// </summary>
		/// <param name="x">X component</param>
		/// <param name="y">Y component</param>
		Vector2D(T x, T y) :
			x(x),
			y(y)
		{
			// ...
		}

		/// <summary>
		/// Destroys 2D vector
		/// </summary>
		virtual ~Vector2D()
		{
			// ...
		}

		/// <summary>
		/// Gets the X component
		/// </summary>
		/// <returns>X component</returns>
		virtual inline T GetX() const
		{
			return x;
		}

		/// <summary>
		/// Gets the Y component
		/// </summary>
		/// <returns>Y component</returns>
		virtual inline T GetY() const
		{
			return y;
		}

		/// <summary>
		/// Sets the X component
		/// </summary>
		/// <param name="x">X component</param>
		virtual inline void SetX(T x)
		{
			this->x = x;
		}

		/// <summary>
		/// Sets the Y component
		/// </summary>
		/// <param name="y">Y component</param>
		virtual inline void SetY(T y)
		{
			this->y = y;
		}

		/// <summary>
		/// Assigns a 2D vector to this object
		/// </summary>
		/// <param name="vector2D">2D vector</param>
		/// <returns>This object</returns>
		virtual Vector2D<T>& operator=(const Vector2D<T>& vector2D)
		{
			x = vector2D.x;
			y = vector2D.y;
			return *this;
		}

		/// <summary>
		/// Assigns a 2D vector to this object
		/// </summary>
		/// <param name="vector2D">2D vector</param>
		/// <returns>This object</returns>
		virtual Vector2D<T>& operator=(Vector2D<T>&& vector2D) noexcept
		{
			x = vector2D.x;
			y = vector2D.y;
			return *this;
		}

		/// <summary>
		/// Adds two vectors together
		/// </summary>
		/// <param name="vector2D">2D Vector</param>
		/// <returns>Added vector</returns>
		virtual Vector2D<T>& operator+=(const Vector2D<T>& vector2D) noexcept
		{
			x += vector2D.x;
			y += vector2D.y;
			return *this;
		}

		/// <summary>
		/// Adds two vectors together
		/// </summary>
		/// <param name="vector2D">2D Vector</param>
		/// <returns>Added vector</returns>
		virtual Vector2D<T> operator+(const Vector2D<T>& vector2D) const noexcept
		{
			return Vector2D<T>(*this) += vector2D;
		}

		/// <summary>
		/// Subtracts two vectors together
		/// </summary>
		/// <param name="vector2D">2D Vector</param>
		/// <returns>Subtracted vector</returns>
		virtual Vector2D<T>& operator-=(const Vector2D<T>& vector2D)noexcept
		{
			x -= vector2D.x;
			y -= vector2D.y;
			return *this;
		}

		/// <summary>
		/// Subtracts two vectors together
		/// </summary>
		/// <param name="vector2D">2D Vector</param>
		/// <returns>Subtracted vector</returns>
		virtual Vector2D<T> operator-(const Vector2D<T>& vector2D) const noexcept
		{
			return Vector2D<T>(*this) -= vector2D;
		}

		/// <summary>
		/// Serializes contents
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>Serialized contents</returns>
		virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override
		{
			NumericSerializer::Serialize<T>(x, result);
			return NumericSerializer::Serialize<T>(y, result);
		}

		/// <summary>
		/// Deserializes given input
		/// </summary>
		/// <param name="data">Data to deserialize</param>
		/// <returns>Remaining data to deserialize</returns>
		virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override
		{
			std::span<std::uint8_t const> next_bytes(NumericSerializer::Deserialize<T>(data, x));
			return NumericSerializer::Deserialize<T>(next_bytes, y);
		}

	private:

		/// <summary>
		/// X component
		/// </summary>
		T x;

		/// <summary>
		/// Y component
		/// </summary>
		T y;
	};
}
