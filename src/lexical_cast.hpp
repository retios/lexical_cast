// =====================================================================================
// 
//       Filename:  lexical_cast.hpp
// 
//    Description:  字符串 <=> 数字之间的互相转换:
//
//        Version:  1.0
//        Created:  2015-12-17 10:32:48
//       Revision:  none
// 
//         Author:  wendyhu (csuwenbinhu@gmail.com)
//      Copyright:  Copyright (c) 2010, Tencent Co.Ltd
// 
// =====================================================================================

#ifndef LEXICAL_CAST_HPP_
#define LEXICAL_CAST_HPP_

#include <sstream>
#include <typeinfo>
#include <cstring>
#include <stdexcept>
//#include <type_traits>

namespace retio {

/**
 * @class lexical_cast类型转换异常
 * @brief lexical_cast类型转换异常, 源类型无法转换成目标类型
 */
class bad_lexical_cast: public std::bad_cast {
public:
	bad_lexical_cast() :
			source(&typeid(void)), target(&typeid(void)) {
	}

	bad_lexical_cast(const std::type_info &source_type_arg,
			const std::type_info &target_type_arg) :
			source(&source_type_arg), target(&target_type_arg) {
	}

	const std::type_info &source_type() const {
		return *source;
	}
	const std::type_info &target_type() const {
		return *target;
	}

	virtual const char *what() const throw () {
		return "bad lexical cast: "
				"source type value could not be interpreted as target";
	}
	virtual ~bad_lexical_cast() throw () {
	}
private:
	const std::type_info *source;
	const std::type_info *target;
};

namespace detail {

const std::string m_sTrue = "true";
const std::string m_sFalse = "false";

template<typename Target, typename Source>
struct Converter {
	/**
	 * @fn convert
	 * @brief 完成源类型和目标类型之间的转换
	 *
	 * @param arg 源类型值
	 * @param bThrow 类型转换失败时是否抛出异常
	 *
	 * @return 目标类型值
	 */
	static Target convert(const Source& arg, const bool bThrow) {
		std::stringstream interpreter;
		Target result;

		if (!(interpreter << arg && interpreter >> result) && bThrow)
			throw bad_lexical_cast(typeid(Source), typeid(Target));

		return result;
	}
};

/**
 * 模板特化，支持bool
 */
template<typename Source>
struct Converter<bool, Source> {

	static bool convert(const Source& arg, const bool bThrow) {
		return !!arg;
	}
};

inline bool convert(const char* from, const bool bThrow) {
	const unsigned int len = strlen(from);
	if (len != 4 && len != 5 && bThrow)
		throw std::invalid_argument("argument is invalid");

	bool r = true;
	if (len == 4) {
		r = m_sTrue.compare(from);

		if (r)
			return true;
	} else if (len == 5) {
		r = m_sFalse.compare(from);

		if (r)
			return false;
	}
	if (bThrow)
		throw std::invalid_argument("argument is invalid");
	else
		return false;
}

template<>
struct Converter<bool, std::string> {
	static bool convert(const std::string& source, const bool bThrow = false) {
		return detail::convert(source.c_str(), bThrow);
	}
};

template<>
struct Converter<bool, const char*> {
	static bool convert(const char* source, const bool bThrow = false) {
		return detail::convert(source, bThrow);
	}
};

template<>
struct Converter<bool, char*> {
	static bool convert(char* source, const bool bThrow = false) {
		return detail::convert(source, bThrow);
	}
};

template<unsigned N>
struct Converter<bool, const char[N]> {
	static bool convert(const char (&source)[N], const bool bThrow = false) {
		return detail::convert(source, bThrow);
	}
};

template<unsigned N>
struct Converter<bool, char[N]> {
	static bool convert(const char (&source)[N], const bool bThrow = false) {
		return detail::convert(source, bThrow);
	}
};
}
/**
 * @fn lexical_cast
 * @brief 完成源类型和目标类型之间的转换
 *
 * @param arg 源类型值
 * @param bThrow 类型转换失败时是否抛出异常
 *
 * @return 目标类型值
 */
template<typename Target, typename Source>
Target lexical_cast(const Source& arg, const bool bThrow = false) {
	return detail::Converter<Target, Source>::convert(arg, bThrow);
}

}
#endif /* LEXICAL_CAST_HPP_ */
