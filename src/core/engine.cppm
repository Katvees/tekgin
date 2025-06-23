export module katvees.tekgin.core.engine;
import std;

import katvees.tekgin.paths;

namespace Tekgin
{

export class Engine
{
 public:
	Engine(const Engine&)            = delete;
	Engine(Engine&&)                 = delete;
	Engine& operator=(const Engine&) = delete;
	Engine& operator=(Engine&&)      = delete;

	static Engine& get()
	{
		static Engine instance;
		return instance;
	}

	[[nodiscard]] std::chrono::system_clock::time_point getStartTime() const { return startTime; }

 private:
	// Private constructor
	Engine();

	// Member variables
	std::chrono::system_clock::time_point startTime;
};

} // namespace Tekgin
