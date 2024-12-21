#include <vector>
#include <ostream>
#include <istream>

constexpr char SER_COMPONENT_DELIM = '[';
constexpr char SER_VALIDATOR_START_DELIM = '>';
constexpr char SER_SCHEM_NAME_DELIM = ';';
constexpr char SER_SCHEM_END_DELIM = ':';

template <typename T>
void Save(std::ostream& os, const std::vector<T>& v) {
	for(T& t : v) {
		assert(t != ' ');
		os << t; 
		os << ' ';
	}
}


template <typename T>
void Load(std::istream& is, const std::vector<T>& v) {
	T element;
	while(is >> element) {
		v.push_back(element);
	}
}