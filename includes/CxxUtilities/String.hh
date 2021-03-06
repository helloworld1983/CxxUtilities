/*
 * String.hh
 *
 *  Created on: Jun 7, 2011
 *      Author: yuasa
 */

#ifndef CXXUTILITIES_STRING_HH_
#define CXXUTILITIES_STRING_HH_

#include "CxxUtilities/CommonHeader.hh"
#include "CxxUtilities/Date.hh"

namespace CxxUtilities {

namespace CCTYPE {
#include <ctype.h>
}

class String {
public:
	static int64_t toInteger(char* str) {
		return toInteger(std::string(str));
	}

	static int64_t toInteger(const char* str) {
		return toInteger(std::string(str));
	}

	static int64_t toInteger(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
			unsigned int avalue = 0;
			ss >> hex >> avalue;
			return avalue;
		} else {
			int avalue = 0;
			ss >> avalue;
			return avalue;
		}
	}

	static uint8_t toUInt8(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		uint32_t avalue = 0;
		if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
			ss >> hex >> avalue;
		} else {
			ss >> avalue;
		}
		return (uint8_t) avalue;
	}

	static uint32_t toUInt32(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		uint32_t avalue = 0;
		if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
			ss >> hex >> avalue;
		} else {
			ss >> avalue;
		}
		return avalue;
	}

	static uint64_t toUInt64(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		uint64_t avalue = 0;
		if (str.size() >= 2 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x')) {
			ss >> hex >> avalue;
		} else {
			ss >> avalue;
		}
		return avalue;
	}

	static std::vector<int> toIntegerArray(std::string str) {
		using namespace std;
		vector<int> result;
		vector<string> stringArray = String::split(str, " ");
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			result.push_back(String::toInteger(stringArray[i]));
		}
		return result;
	}

	static std::vector<unsigned int> toUnsignedIntegerArray(std::string str) {
		using namespace std;
		vector<unsigned int> result;
		vector<string> stringArray = String::split(str, " ");
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			result.push_back((unsigned int) String::toInteger(stringArray[i]));
		}
		return result;
	}

	static std::vector<unsigned char> toUnsignedCharArray(std::string str) {
		using namespace std;
		vector<unsigned char> result;
		str = String::replace(str, "\n", "");
		str = String::replace(str, "\r", "");
		str = String::replace(str, "\t", " ");
		vector<string> stringArray = String::split(str, " ");
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			if (stringArray[i].size() > 2 && stringArray[i][0] == '0'
					&& (stringArray[i][1] == 'x' || stringArray[i][1] == 'X')) {
				string element = String::replace(String::toLowerCase(stringArray[i]), "0x", "");
				size_t elementLength = element.size();
				uint32_t avalue = 0;
				size_t o = 0;
				bool firstByte = true;

				while (o < element.size()) {
					std::stringstream ss;
					if (firstByte) {
						if (elementLength % 2 == 0) { //even number
							ss << "0x" << element.substr(o, 2);
							o += 2;
						} else { //odd number
							ss << "0x" << element.substr(o, 1);
							o++;
						}
						firstByte = false;
					} else {
						//read two characters
						ss << "0x" << element.substr(o, 2);
						o += 2;
					}
					ss >> hex >> avalue;
					result.push_back((uint8_t) avalue);
				}
			} else {
				unsigned char avalue = (unsigned char) String::toUInt32(stringArray[i]);
				result.push_back(avalue);
			}
		}
		return result;
	}

	static std::vector<uint8_t> toUInt8Array(std::string str) {
		using namespace std;
		vector<unsigned char> result;
		str = String::replace(str, "\n", "");
		str = String::replace(str, "\r", "");
		str = String::replace(str, "\t", " ");
		vector<string> stringArray = String::split(str, " ");
		for (unsigned int i = 0; i < stringArray.size(); i++) {
			if (stringArray[i].size() > 2 && stringArray[i][0] == '0'
					&& (stringArray[i][1] == 'x' || stringArray[i][1] == 'X')) {
				string element = String::replace(String::toLowerCase(stringArray[i]), "0x", "");
				size_t elementLength = element.size();
				uint32_t avalue = 0;
				size_t o = 0;
				bool firstByte = true;

				while (o < element.size()) {
					std::stringstream ss;
					if (firstByte) {
						if (elementLength % 2 == 0) { //even number
							ss << "0x" << element.substr(o, 2);
							o += 2;
						} else { //odd number
							ss << "0x" << element.substr(o, 1);
							o++;
						}
						firstByte = false;
					} else {
						//read two characters
						ss << "0x" << element.substr(o, 2);
						o += 2;
					}
					ss >> hex >> avalue;
					result.push_back((uint8_t) avalue);
				}
			} else {
				uint8_t uint8_value = (uint8_t) String::toUInt32(stringArray[i]);
				result.push_back(uint8_value);
			}
		}
		return result;
	}

	static double toDouble(char* str) {
		return toDouble(std::string(str));
	}

	static double toDouble(const char* str) {
		return toDouble(std::string(str));
	}

	static double toDouble(std::string str) {
		using namespace std;
		stringstream ss;
		ss << str;
		double avalue = 0;
		ss >> avalue;
		return avalue;
	}

	static std::vector<std::string> split(std::string str, std::string delimitter) {
		std::vector<std::string> result;
		size_t n = 0;
		for (size_t i = 0; i <= str.length(); i = n + 1) {
			n = str.find_first_of(delimitter, i);
			if (n == std::string::npos) {
				n = str.length();
			}
			std::string element = str.substr(i, n - i);
			if (element != "") {
				result.push_back(element);
			}
		}
		return result;
	}

	static std::vector<std::string> splitIntoLines(std::string str) {
		using namespace std;
		stringstream ss;
		std::vector<std::string> result;
		ss << str;
		while (!ss.eof()) {
			string line;
			getline(ss, line);
			result.push_back(line);
		}
		return result;
	}

	static std::string replace(std::string str, std::string find_what, std::string replace_with) {
		std::string::size_type pos = 0;
		while ((pos = str.find(find_what, pos)) != std::string::npos) {
			str.erase(pos, find_what.length());
			str.insert(pos, replace_with);
			pos += replace_with.length();
		}
		return str;
	}

	static std::string join(std::vector<std::string> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << list[i];
			} else {
				ss << list[i] << conjunction;
			}
		}
		return ss.str();
	}

#ifndef RASPBERRY_PI
	static std::string join(std::vector<size_t> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << list[i];
			} else {
				ss << list[i] << conjunction;
			}
		}
		return ss.str();
	}
#endif

	static std::string join(std::vector<uint8_t> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << (uint32_t)list[i];
			} else {
				ss << (uint32_t)list[i] << conjunction;
			}
		}
		return ss.str();
	}

	static std::string join(std::vector<uint16_t> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << (uint32_t)list[i];
			} else {
				ss << (uint32_t)list[i] << conjunction;
			}
		}
		return ss.str();
	}

	static std::string join(std::vector<uint32_t> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << (uint32_t)list[i];
			} else {
				ss << (uint32_t)list[i] << conjunction;
			}
		}
		return ss.str();
	}

	static std::string join(std::vector<int8_t> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << (int8_t)list[i];
			} else {
				ss << (int8_t)list[i] << conjunction;
			}
		}
		return ss.str();
	}

	static std::string join(std::vector<int16_t> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << (int32_t)list[i];
			} else {
				ss << (int32_t)list[i] << conjunction;
			}
		}
		return ss.str();
	}

	static std::string join(std::vector<int32_t> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << (int32_t)list[i];
			} else {
				ss << (int32_t)list[i] << conjunction;
			}
		}
		return ss.str();
	}

	static std::string join(std::vector<bool> list, std::string conjunction) {
		std::stringstream ss;
		size_t size = list.size();
		for (unsigned int i = 0; i < size; i++) {
			if (i == size - 1) {
				ss << (list[i]? "true":"false") ;
			} else {
				ss << (list[i]? "true":"false") << conjunction;
			}
		}
		return ss.str();
	}

	static std::vector<std::string> getRangeOf(std::vector<std::string>& list, int from, int to) {
		std::vector<std::string> newlist;
		size_t size = list.size();
		if (from < 0) {
			from = size + from;
		}
		if (to < 0) {
			to = size + to;
		}
		if (from < 0 || to < 0) {
			return newlist;
		}
		if (size <= (unsigned int) from || size <= (unsigned int) to) {
			return newlist;
		}
		if (from <= to) {
			for (size_t i = (unsigned int) from; i <= (unsigned int) to; i++) {
				newlist.push_back(list[i]);
			}
		} else {
			for (size_t i = (unsigned int) to; i <= (unsigned int) from; i++) {
				newlist.push_back(list[i]);
			}
		}
		return newlist;
	}

	static std::string dumpAddress(void* address, unsigned int width = 4) {
		std::stringstream ss;
		ss << "0x" << std::setw(width) << std::setfill('0') << std::hex << (long long) address;
		return ss.str();
	}

	static bool contains(std::string str1, std::string str2) {
		std::string::size_type index = str1.find(str2.c_str(), 0);
		if (index != std::string::npos) {
			return true;
		} else {
			return false;
		}
	}

public:
	static bool containsNumber(std::string str) {
		for (auto ch : str) {
			if ('0' <= ch && ch <= '9') {
				return true;
			}
		}
		return false;
	}

	static std::string toStringFromInteger(int avalue) {
		std::stringstream ss;
		ss << avalue;
		return ss.str();
	}

	static std::string toStringFromDouble(double avalue, unsigned int precision = 3) {
		std::stringstream ss;
		ss << std::setprecision(precision) << avalue;
		return ss.str();
	}

	static std::string toHexString(unsigned int avalue, unsigned int width = 2, std::string prefix = "0x") {
		using namespace std;
		stringstream ss;
		ss << prefix << setw(width) << setfill('0') << right << hex << avalue << dec;
		return ss.str();
	}

	static bool includes(std::string str, std::string searched_str) {
		if (str.find(searched_str) == std::string::npos) {
			return false;
		} else {
			return true;
		}
	}

	static bool include(std::string str, std::string searched_str) {
		return includes(str, searched_str);
	}

	static size_t indexOf(std::string str, std::string searched_str) {
		size_t result = str.find(searched_str);
		if (result == std::string::npos) {
			return std::string::npos;
		} else {
			return result;
		}
	}

public:
	static std::string put0xForAllElements(std::string str) {
		using namespace std;
		vector<string> array = String::split(str, " ");
		for (size_t i = 0; i < array.size(); i++) {
			string element = array[i];
			if (element[0] != '0' || !(element[1] == 'x' || element[1] == 'X')) {
				element = String::replace(element, " ", "");
				array[i] = "0x" + element;
			}
		}
		return String::join(array, " ");
	}

public:
	static std::string removeLeadingSpaces(std::string str) {
		size_t index = 0;
		while (str.at(index) == ' ' || str.at(index) == '\t') {
			index++;
		}
		return str.substr(index);
	}

public:
	static std::string upCase(std::string str) {
		std::string result;
		std::transform(str.begin(), str.end(), std::back_inserter(result), (int (*)(int))std::toupper);return
result		;
	}

public:
	static std::string toUpperCase(std::string str) {
		std::string result;
		std::transform(str.begin(), str.end(), std::back_inserter(result), (int (*)(int))std::toupper);
		return result;
	}

public:
	static std::string downCase(std::string str) {
		std::string result;
		std::transform(str.begin(), str.end(), std::back_inserter(result), (int (*)(int))std::tolower);
		return result;
	}

public:
	static std::string toLowerCase(std::string str) {
		std::string result;
		std::transform(str.begin(), str.end(), std::back_inserter(result), (int (*)(int))std::tolower);
		return result;
	}

public:
	static bool isNumeric(std::string str) {
		int base=10;
		if(str.size()>2 && str[0]=='0' && (str[1]=='x' || str[1]=='X') ) {
			base=16;
		}
		std::istringstream inputstream( str );
		if ( base == 10 ) {
			double dummy;
			inputstream >> dummy;
		}
		else if ( base == 8 || base == 16 ) {
			int dummy;
			inputstream >> ( ( base == 8 ) ? std::oct : std::hex ) >> dummy;
		} else {
			return false;
		}
		if ( ! inputstream ) {
			return false;
		}
		return ( inputstream.rdbuf()->in_avail() == 0 );
	}

public:
	static bool isIntegerNumeric(std::string str) {
		//first, check if numeric
		if(isNumeric(str)) { //is numeric
			if(str.find('.')==std::string::npos && str.find('e')==std::string::npos && str.find('E')==std::string::npos) {
				return true;
			} else {
				return false;
			}
		} else { //is not numeric
			return false;
		}
	}

public:
	/** Converts string to boolean.
	 * true or yes => true.
	 * false or no => false.
	 * otherwise => false.
	 */
	static bool toBoolean(std::string str) {
		if(str=="true" ||str=="TRUE" || str == "yes" || str=="YES") {
			return true;
		} else if(str=="false" ||str=="FALSE" || str == "no" || str=="NO") {
			return false;
		} else {
			return false;
		}

	}

public:
	static CxxUtilities::Date parseYYYYMMDD_HHMMSS(std::string yyyymmdd_hhmmss) {
		return CxxUtilities::Date::parseYYYYMMDD_HHMMSS(yyyymmdd_hhmmss);
	}

};
}

#endif /* CXXUTILITIES_STRING_HH_ */
