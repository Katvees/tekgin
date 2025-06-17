export module katvees.tekgin.combat.elements;
import std;
// Consider moving to another file to reduce filecount and avoid nearly empty files

export namespace Tekgin
{
/// Elements for damage types etc.
/// COUNT is always the last member
enum class Element : std::uint8_t { NONE = 0, ALL, FIRE, COLD, LIGHTNING, POISON, COUNT };
} // namespace Tekgin
