module katvees.tekgin.util.logging;

namespace Tekgin::Util
{
std::string logLevelToString(LogLevel level)
{
	switch (level) {
	case FATAL: return "FATAL";
	case ERROR: return "ERROR";
	case WARN:  return "WARN";
	case INFO:  return "INFO";
	case DEBUG: return "DEBUG";
	case TRACE: return "TRACE";
	case NONE:  return "";
	}
}

LogDest::LogDest(LogLevel level)
{
	namespace fs = std::filesystem;

	switch (level) {
	case FATAL ... WARN: stream = &std::cerr; break;
	case INFO ... TRACE: stream = &std::cout;
	}

	// Format filename with time
	std::string timestamp = std::format(std::runtime_format("{:%Y-%m-%d_%H-%M-%S}"), Engine::get().getStartTime());

	fs::path filePath = log_dir / ("Tekgin_" + timestamp + ".log");
	fs::create_directories(filePath.parent_path());
	file.open(filePath, std::ios::app);
}


} // namespace Tekgin::Util
