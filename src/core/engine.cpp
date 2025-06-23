module katvees.tekgin.core.engine;

namespace Tekgin
{
Engine::Engine() : startTime(std::chrono::system_clock::now())
{
	std::filesystem::create_directories(data_dir);
	std::filesystem::create_directory(log_dir);
}
} // namespace Tekgin
