#pragma once

#include <Misc/Vector2D.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a hole
	/// </summary>
	class Hole
	{
	public:
		Hole() = delete;
		Hole(const Hole&) = delete;
		Hole(Hole&&) = delete;

		/// <summary>
		/// Constructs a hole
		/// </summary>
		/// <param name="position">Position</param>
		/// <param name="radius">Radius</param>
		Hole(const Vector2D<float>& position, const Vector2D<float>& radius);

		/// <summary>
		/// Destroys hole
		/// </summary>
		virtual ~Hole();

		/// <summary>
		/// Gets the position
		/// </summary>
		/// <returns>Position</returns>
		virtual const Vector2D<float>& GetPosition() const;

		/// <summary>
		/// Gets the radius
		/// </summary>
		/// <returns>Radius</returns>
		virtual const Vector2D<float>& GetRadius() const;

		/// <summary>
		/// Is position in hole
		/// </summary>
		/// <param name="position">Position</param>
		/// <returns>"true" if position is in hole, otherwise "false"</returns>
		virtual bool IsPositionInHole(const Vector2D<float>& position) const;

		Hole& operator=(const Hole&) = delete;
		Hole& operator=(Hole&&) = delete;

	private:

		/// <summary>
		/// Position
		/// </summary>
		Vector2D<float> position;

		/// <summary>
		/// Radius
		/// </summary>
		Vector2D<float> radius;
	};
}
