export module katvees.tekgin.constants;
import std;

namespace Tekgin {
export constinit int ENGINE_VERSION_MAJOR = 0;
export constinit int ENGINE_VERSION_MINOR = 0;
export constinit int ENGINE_VERSION_PATCH = 0;

export constinit const char* ENGINE_VERSION_STRING = "0.0.0";

export const std::chrono::system_clock::time_point START_TIME{std::chrono::system_clock::now()};

}
