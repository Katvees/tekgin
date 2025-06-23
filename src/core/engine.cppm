export module katvees.tekgin.core.engine;
import std;

import katvees.tekgin.paths;
import katvees.tekgin.constants;

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

 private:
	Engine();
	~Engine() = default;
};

} // namespace Tekgin
