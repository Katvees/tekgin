module katvees.tekgin.util.logging;

namespace Tekgin::Util
{
std::string logLevelLabel(Log::Level level)
{
	switch (level) {
	case fatal: return "\033[1;97;41mFATAL\033[0m"; // bold white on red
	case error: return "\033[1;31mERROR\033[0m";    // bold red
	case warn:  return "\033[1;33mWARN\033[0m";     // bold yellow
	case info:  return "\033[1;32mINFO\033[0m";     // bold green
	case debug: return "\033[1;36mDEBUG\033[0m";    // bold cyan
	case trace: return "\033[1;90mTRACE\033[0m";    // bold gray
	case none:  return "";
	}
}

std::ostream& Log::getStream(Log::Level level)
{
	switch (level) {
	case fatal ... warn: return std::cerr; break;
	case info ... trace: return std::cout;
	}
}

std::ostream& Log::getFile()
{
	static std::ofstream file{ std::format("{}/Tekgin_{:%Y-%m-%d_%H-%M-%S}.log", log_dir.string(), START_TIME), std::ios::out };
	return file;
}


} // namespace Tekgin::Util
