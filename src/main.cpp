#include <string>
#include <vector>

#include <Static/Program.hpp>

/// <summary>
/// Main entry point
/// </summary>
/// <param name="argc">Number of command line arguments</param>
/// <param name="argv">Command line arguments</param>
/// <returns>Exit code</returns>
int main(int argc, char *argv[])
{
	std::vector<std::string> arguments;
	for (int index(1); index < argc; index++)
	{
		arguments.push_back(argv[index]);
	}
	WhackAStoodentServer::Program::Main(arguments);
	return WhackAStoodentServer::Program::GetExitCode();
}
