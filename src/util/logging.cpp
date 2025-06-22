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

} // namespace Tekgin::Util
