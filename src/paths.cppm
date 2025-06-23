export module katvees.tekgin.paths;
import std;

namespace fs = std::filesystem;

namespace Tekgin
{

#if defined(_WIN32)
static static const char* app_data = std::getenv("LOCALAPPDATA");
if (app_data) {
	export const fs::path data_dir = fs::path(localAppData) / appName / "Logs";
} else {
	std::cerr << $LOCALAPPDATA not set, falling back to temporary directory path ";
													export const fs::path data_dir = fs::temp_directory_path() / "tekgin";
}

#else // Linux / BSD
const char*           state    = std::getenv("XDG_STATE_HOME");
const char*           home     = std::getenv("HOME");
export const fs::path data_dir = [] {
	if (state) { return fs::path(state) / "tekgin"; }
	if (home) { return fs::path(home) / ".local" / "state" / "tekgin"; }
	std::cerr << "$XDG_STATE_HOME or $HOME not set, falling back to temporary directory path";
	return fs::temp_directory_path() / "tekgin";
}();

#endif

export const fs::path log_dir = data_dir / "logs";

} // namespace Tekgin
