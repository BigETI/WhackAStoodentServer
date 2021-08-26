#include <limits>

#include <Misc/Hole.hpp>

/// <summary>
/// Constructs a hole
/// </summary>
/// <param name="position">Position</param>
/// <param name="radius">Radius</param>
WhackAStoodentServer::Hole::Hole(const WhackAStoodentServer::Vector2D<float>& position, const WhackAStoodentServer::Vector2D<float>& radius) :
	position(position),
	radius(radius)
{
	// ...
}

/// <summary>
/// Destroys hole
/// </summary>
WhackAStoodentServer::Hole::~Hole()
{
	// ...
}

/// <summary>
/// Is position in hole
/// </summary>
/// <param name="position">Position</param>
/// <returns>"true" if position is in hole, otherwise "false"</returns>
bool WhackAStoodentServer::Hole::IsPositionInHole(const WhackAStoodentServer::Vector2D<float>& position)
{
	Vector2D<float> delta(position - this->position);
	delta.SetY(((radius.GetX() > 0.0f) && (radius.GetY() > 0.0f)) ? (delta.GetY() * radius.GetX() / radius.GetY()) : std::numeric_limits<float>::infinity());
	return ((delta.GetX() * delta.GetX()) + (delta.GetY() * delta.GetY())) <= (radius.GetX() * radius.GetX());
}
