module katvees.tekgin.util.logging;

namespace Tekgin::Util
{
std::string logLevelToString(Log::Level level)
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

std::ostream& Log::getStream(Log::Level level)
{
	switch (level) {
	case FATAL ... WARN: return std::cerr; break;
	case INFO ... TRACE: return std::cout;
	}
}

std::ostream& Log::getFile()
{
	static std::ofstream file{ std::format("{}/Tekgin_{:%Y-%m-%d_%H-%M-%S}.log", log_dir.string(), START_TIME), std::ios::out };
	return file;
}


} // namespace Tekgin::Util
