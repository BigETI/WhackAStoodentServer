#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <thread>

#include <Misc/Server.hpp>
#include <Static/Defaults.hpp>
#include <Static/Main.hpp>

int main(int argc, char *argv[])
{
	int ret(-1);
	try
	{
		std::map<std::string, std::string> command_line_arguments;
		std::uint16_t port(WhackAStoodentServer::Defaults::ServerPort);
		std::uint32_t timeout_time(WhackAStoodentServer::Defaults::TimeoutTime);
		std::uint32_t tick_count_per_second(WhackAStoodentServer::Defaults::TickCountPerSecond);

		// TODO: Parse configuration

		std::time_t tick_time(static_cast<double>(tick_count_per_second) * 0.000001);
		WhackAStoodentServer::Server server(port, timeout_time);
		std::cout << "Starting Whack-A-Stoodent server at port " << port << "..." << std::endl;
		server.Start();
		std::cout << "Whack-A-Stoodent server started!" << std::endl;
		while (server.ProcessMessages())
		{
			std::this_thread::sleep_for(std::chrono::microseconds(tick_time));
		}
		std::cout << "Stopping Whack-A-Stoodent server..." << std::endl;
		server.Stop();
		std::cout << "Whack-A-Stoodent server stopped!" << std::endl;
		ret = 0;
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
	return ret;
}
