#pragma once

#include <span>
#include <string>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes this program
	/// </summary>
	class Program
	{
	public:

		Program() = delete;
		Program(const Program&) = delete;
		Program(Program&&) = delete;
		~Program() = delete;

		/// <summary>
		/// Main entry point
		/// </summary>
		/// <param name="arguments">Arguments</param>
		static void Main(const std::span<const std::string> arguments);

		/// <summary>
		/// Gets the current exit code
		/// </summary>
		/// <returns>Exit code</returns>
		static int GetExitCode() noexcept;

		/// <summary>
		/// Sets the current exit code
		/// </summary>
		/// <param name="newExitCode">New exit code</param>
		static void SetExitCode(int newExitCode) noexcept;

		Program& operator=(const Program&) = delete;
		Program& operator=(Program&&) = delete;

	private:

		/// <summary>
		/// Exit code
		/// </summary>
		static int exitCode;
	};
}
