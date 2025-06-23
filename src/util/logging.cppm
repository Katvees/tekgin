/**
 * @file
 * @brief Implements logging functions and allows classes to have a formatter function to easily log the object
 */

export module katvees.tekgin.util.logging;
import std;

import katvees.tekgin.paths;
import katvees.tekgin.core.engine;

using std::strcmp;

namespace Tekgin::Util
{
export enum LogLevel : std::int8_t { FATAL = -1, NONE, ERROR, WARN, INFO, DEBUG, TRACE };

/// @brief The logging level set through an environment variable
export const LogLevel LOG_LEVEL = [] {
	const char* log_level_str = std::getenv("LOG_LEVEL");
	if (log_level_str != nullptr) {
		if (strcmp(log_level_str, "FATAL") == 0) { return FATAL; }
		if (strcmp(log_level_str, "NONE") == 0) { return NONE; }
		if (strcmp(log_level_str, "ERROR") == 0) { return ERROR; }
		if (strcmp(log_level_str, "WARN") == 0) { return WARN; }
		if (strcmp(log_level_str, "INFO") == 0) { return INFO; }
		if (strcmp(log_level_str, "DEBUG") == 0) { return DEBUG; }
		if (strcmp(log_level_str, "TRACE") == 0) { return TRACE; }
	}
	return INFO;
}();

constexpr bool shouldLog(LogLevel level) { return level <= LOG_LEVEL; }

std::string logLevelToString(LogLevel level);

export template<typename... Args>
struct LogData
{
	std::string_view    fmt;
	std::tuple<Args...> args;
};

export struct LogDest
{
 public:
	explicit LogDest(LogLevel level = LogLevel::INFO);

	template<typename T>
	LogDest& operator<<(const T& value)
	{
		*stream << value;
		if (file.is_open()) { file << value; }
		return *this;
	}

 private:
	std::ostream* stream;
	std::ofstream file;
};

template<typename T>
struct is_log_data : std::false_type
{};
template<typename... Args>
struct is_log_data<LogData<Args...>> : std::true_type
{};
template<typename T>
constexpr bool is_log_data_v = is_log_data<T>::value;

/// @brief Concept requiring the class to have the member function logFormat
template<typename T>
concept HasLogFormat = requires(const T& t) { is_log_data_v<decltype(t.logFormat())>; };

/**
 * @brief Function to log a class
 *
 * @tparam T Type of the object
 * @param level The verbosity/severity level of the log
 * @param obj The object to log
 */
export template<typename T>
	requires HasLogFormat<T>
void log(LogLevel level, const T& obj)
{
	auto data = obj.logFormat();
	std::apply([level, &data](auto&&... args) { log(level, data.fmt, std::forward<decltype(args)>(args)...); }, data.args);
}

/**
 * @brief Function to log a class (with default options)
 *
 * @tparam T Type of the object
 * @param obj The object to log
 */
export template<typename T>
	requires HasLogFormat<T>
void log(const T& obj)
{
	log(INFO, obj);
}

/**
 * @brief Log a string into cout or cerr depending on log level or to specified stream
 *
 * @param level The verbosity/severity level of the log
 * @param fmt Format string
 * @tparam Args Any type that has std::format specialization
 * @param args Arguments for format string
 */
export template<typename... Args>
void log(LogLevel level, std::string_view fmt, Args&&... args)
{
	if (shouldLog(level)) {
		LogDest dest(level);
		dest << (logLevelToString(level) + ": ") << std::format(std::runtime_format(fmt), std::forward<Args>(args)...) << "\n";
	}
}

/**
 * @brief Log a string into cout or cerr depending on log level
 *
 * @param fmt Format string
 * @tparam Args Any type that has std::format specialization
 * @param args Arguments for format string
 */
export template<typename... Args>
void log(const std::string& fmt, Args&&... args)
{
	if (shouldLog(INFO)) {
		std::cout << "INFO: " << std::format(std::runtime_format(fmt), std::forward<Args>(args)...) << "\n";
	}
}

export template<typename... Args>
constexpr LogData<std::decay_t<Args>...> log_format_helper(std::string_view fmt, Args&&... args)
{
	return { fmt, std::forward_as_tuple(std::forward<Args>(args)...) };
}

} // namespace Tekgin::Util
