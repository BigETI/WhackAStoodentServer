#include <chrono>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <thread>

#include <span.hpp>

#include <Misc/Server.hpp>
#include <Static/Defaults.hpp>
#include <Static/Program.hpp>

/// <summary>
/// Exit code
/// </summary>
int WhackAStoodentServer::Program::exitCode(-1);

/// <summary>
/// Main entry point
/// </summary>
/// <param name="arguments">Arguments</param>
void WhackAStoodentServer::Program::Main(nonstd::span<const std::string> arguments)
{
	try
	{
		std::map<std::string, std::string> command_line_arguments;
		std::uint16_t port(WhackAStoodentServer::Defaults::ServerPort);
		std::uint32_t timeout_time(WhackAStoodentServer::Defaults::TimeoutTime);
		std::uint32_t tick_count_per_second(WhackAStoodentServer::Defaults::TickCountPerSecond);

		// TODO: Parse configuration

		std::chrono::microseconds tick_time(1000000U / tick_count_per_second);
		WhackAStoodentServer::Server server(port, timeout_time);
		std::cout << "Starting Whack-A-Stoodent server at port " << port << "..." << std::endl;
		server.Start();
		std::cout << "Whack-A-Stoodent server started!" << std::endl;
		while (server.ProcessMessages())
		{
			std::this_thread::sleep_for(tick_time);
		}
		std::cout << "Stopping Whack-A-Stoodent server..." << std::endl;
		server.Stop();
		std::cout << "Whack-A-Stoodent server stopped!" << std::endl;
		exitCode = 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (int e)
	{
		std::cerr << "An exception has occured. Exception code: " << e << std::endl;
	}
	catch (...)
	{
		std::cerr << "An unknown exception has occured." << std::endl;
	}
}

/// <summary>
/// Gets the current exit code
/// </summary>
/// <returns>Exit code</returns>
int WhackAStoodentServer::Program::GetExitCode() noexcept
{
	return exitCode;
}

/// <summary>
/// Sets the current exit code
/// </summary>
/// <param name="newExitCode">New exit code</param>
void WhackAStoodentServer::Program::SetExitCode(int newExitCode) noexcept
{
	exitCode = newExitCode;
}
