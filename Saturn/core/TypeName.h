#ifndef TYPENAME_H
#define TYPENAME_H
#include <string>

template <typename T>
constexpr std::string type_name() {
	std::string_view signature, prefix, suffix;

#ifdef __clang__
	signature = __PRETTY_FUNCTION__;
	prefix = "define your own prefix";
	suffix = "define your own suffix";
#elif defined(__GNUC__)
	signature = __PRETTY_FUNCTION__;
	prefix = "define your own prefix";
	suffix = "define your own suffix";
#elif defined(_MSC_VER)
	signature = __FUNCSIG__;
	prefix = "class std::basic_string<char, struct std::char_traits<char>,class std::allocator<char>> __cdecl type_name<";
	suffix = ">(void)";
#endif
	signature.remove_prefix(prefix.size());
	signature.remove_suffix(suffix.size());

	return (std::string)signature;
}

#endif TYPENAME_H