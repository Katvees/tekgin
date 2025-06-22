export module katvees.tekgin.combat.elements;
import std;

export namespace Tekgin
{
/// Elements for damage types etc.
/// COUNT is always the last member
enum class Element : std::uint8_t { NONE = 0, ALL, FIRE, COLD, LIGHTNING, POISON, COUNT };

/// Specialized class to associate balues with elements without the overhead of a map
template<typename DataType>
struct ElementMap
{
 private:
	static constexpr std::size_t       toIndex(Element element) { return static_cast<std::size_t>(element); }
	static constexpr const std::size_t k_size = toIndex(Element::COUNT);

	std::array<DataType, k_size> m_data{};

 public:
	void                set(Element element, const DataType& value) { m_data.at(toIndex(element)) = value; }
	constexpr DataType  get(Element element) const { return m_data.at(toIndex(element)); }
	constexpr DataType& get(Element element) { return m_data.at(toIndex(element)); }

	constexpr DataType&       operator[](Element element) { return m_data[toIndex(element)]; }
	constexpr const DataType& operator[](Element element) const { return m_data[toIndex(element)]; }

	constexpr ElementMap& operator+=(const ElementMap& rhs)
	{
		for (std::size_t i = 0; i < k_size; ++i) { this->m_data[i] += rhs.m_data[i]; }
	};

	constexpr ElementMap& operator-=(const ElementMap& rhs)
	{
		for (std::size_t i = 0; i < k_size; ++i) { this->m_data[i] -= rhs.m_data[i]; }
	};

	friend ElementMap operator+(ElementMap lhs, const ElementMap& rhs) { return lhs += rhs; };
	friend ElementMap operator-(ElementMap lhs, const ElementMap& rhs) { return lhs += rhs; };
};
} // namespace Tekgin
