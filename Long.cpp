#include "Long.h"
#include <sstream>

Long::Long() {
	this->number = new char[2];
	this->size = 2;

	number[0] = '0';
	number[1] = '\0';
	
	this->isMinus = false;
}

Long::Long(int other) {

	std::string buf = std::to_string(other);

	this->size = buf.length()+1;
	
	this->number = new char[this->size];

	for (int i = 0; i < size-1; i++) {
		this->number[i] = buf[i];
	}

	if (other < 0)
		this->isMinus = true;
	else
		this->isMinus = false;

	this->number[this->size-1] = '\0';
}

Long::Long(char* other) {
	this->size = strlen(other) + 1;

	this->number = new char[this->size];

	for (int i = 0; i < this->size; i++) {
		this->number[i] = other[i];
	}
	this->number[this->size - 1] = '\0';

	this->isMinus = (this->number[0] == '-');
}

Long::Long(const char* other) {
	this->size = strlen(other)+1;

	this->number = new char[this->size];

	for (int i = 0; i < this->size; i++) {
		this->number[i] = other[i];
	}
	this->number[this->size - 1] = '\0';

	this->isMinus = (this->number[0] == '-');

}

Long::Long(const Long& other) {
	this->size = other.size;
	this->isMinus = other.isMinus;
	char* bufStr = new char[this->size + 1];

	for (int i = 0; i < this->size; i++) {
		bufStr[i] = other.number[i];
	}

	bufStr[this->size] = '\0';
	this->number = bufStr;
}

Long::~Long() {
	delete[] this->number;
}

char* Long::remove_start_zeros(char* n) {
	char* bufStr;
	int bufInt = (n[0] == '-');

	int nLen = strlen(n);

	while (bufInt < strlen(n)) {
		if (n[bufInt] != '0') {
			break;
		}
		bufInt++;
	}

	bufInt -= (n[0] == '-');

	bufStr = new char[strlen(n) - bufInt];

	if (n[0] == '-') {

		bufStr[0] = '-';

		for (int i = 0; i < strlen(n) - bufInt; i++)
			bufStr[i + 1] = n[i + 1 + bufInt];

	}
	else {
		
		for (int i = 0; i < strlen(n) - bufInt; i++)
			bufStr[i] = n[i + bufInt];

	}


	bufStr[strlen(n) - bufInt] = '\0';
	return bufStr;
	
}
char* Long::remove_start_zeros(const char* n) {
	char* bufStr;
	int bufInt = (n[0] == '-');

	int nLen = strlen(n);

	while (bufInt < strlen(n)) {
		if (n[bufInt] != '0') {
			break;
		}
		bufInt++;
	}

	bufInt -= (n[0] == '-');

	bufStr = new char[strlen(n) - bufInt];

	if (n[0] == '-') {

		bufStr[0] = '-';

		for (int i = 0; i < strlen(n) - bufInt; i++)
			bufStr[i + 1] = n[i + 1 + bufInt];

	}
	else {

		for (int i = 0; i < strlen(n) - bufInt; i++)
			bufStr[i] = n[i + bufInt];

	}


	bufStr[strlen(n) - bufInt] = '\0';
	return bufStr;
}

Long& Long::change_minus() {
	Long* bufLong = this;

	if (*bufLong < 0) {
		this->isMinus = false;
		bufLong->number[0] = '0';
		*bufLong = remove_start_zeros(bufLong->number);
	}
	else if (*bufLong > 0){
		char* bufStr = new char[bufLong->size + 1];
		bufStr[0] = '-';
		for (int i = 0; i < bufLong->size+1; i++) {
			bufStr[i + 1] = bufLong->number[i];
		}
		*bufLong = bufStr;
	}
	return *this;
}

Long operator+(Long first, Long second) {
	char* bufStr;
	Long bufLong, bufLong2;

	if ((second < 0) && (first<0)) {
		second = second * -1;
		first = first * -1;
		return (second + first) * -1;
	}
	else if (second < 0) {
		second = second * -1;
		
		return (first - second);
	}
	else if (first<0) {
		bufLong = first * -1;
		Long bufLong2 = bufLong + second;
		return bufLong2;
	}
	else {
		int minSize = (first.size <= second.size ? first.size : second.size);
		int maxSize = (first.size > second.size ? first.size : second.size);

		bufStr = new char[maxSize+1];
		bufStr[maxSize] = '\0';
		bufStr[0] = '0';

		for (int i = 1; i < minSize; i++) {
			bufStr[i] = first.number[i-1] + second.number[i-1] - '0';
		}

		for (int i = minSize; i < maxSize; i++) {
			bufStr[i] = first.size > second.size ? first.number[i-1] : second.number[i-1];
		}

		for (int i = maxSize - 2; i >= 1; i--) {
			if (bufStr[i] > '9') {
				bufStr[i] -= 10;
				bufStr[i - 1] += 1;
			}
		}

		bufStr = Long::remove_start_zeros(bufStr);
		bufLong = bufStr;

		return bufLong;
	}
}

template<typename T>
Long operator+(Long first, T second) {
	Long buf = second;
	return (first + buf);
}
template<>
Long operator+<int>(Long first, int second) {
	Long buf = second;
	return (first + buf);
}
template<>
Long operator+<char*>(Long first, char* second) {
	Long buf = second;
	return (first + buf);
}
template<>
Long operator+<const char*>(Long first, const char* second) {
	Long buf = second;
	return (first + buf);
}

template<typename T>
Long operator+(T first, Long second) {
	Long buf = first;
	return (buf + second);
}
template<>
Long operator+<int>(int first, Long second) {
	Long buf = first;
	return (buf + second);
}
template<>
Long operator+<char*>(char* first, Long second) {
	Long buf = first;
	return (buf + second);
}
template<>
Long operator+<const char*>(const char* first, Long second) {
	Long buf = first;
	return (buf + second);
}


Long operator-(Long first, Long second) {

	if (second <= first) {

		if (second <= 0 && first >= 0) {
			second = second * -1;
			return first + second;
		}
		else if (first <= 0 && second <= 0) {
			second = second * -1;
			first = first * -1;
			return ((second + first) * -1);
		}
		else {
			int minSize = (first.size <= second.size ? first.size : second.size);
			int maxSize = (first.size > second.size ? first.size : second.size);

			char* bufStr = new char[maxSize + 1];
			bufStr[maxSize] = '\0';
			bufStr[0] = '0';

			for (int i = 1; i < minSize; i++) {
				bufStr[i] = (char)((int)first.number[i - 1] - (int)second.number[i - 1] + (int)'0');
			}

			for (int i = minSize; i < maxSize; i++) {
				bufStr[i] = first.size > second.size ? first.number[i - 1] : second.number[i - 1];
			}

			for (int i = maxSize - 1; i >= 1; i--) {
				if (bufStr[i] < '0') {
					bufStr[i] += 10;
					bufStr[i - 1] -= 1;
				}
			}

			bufStr = Long::remove_start_zeros(bufStr);
			Long bufLong = bufStr;

			return bufLong;
		}
	}
	else {
		return ((second - first) * -1);
	}

}

template<typename T>
Long operator-(T first, Long second) {
	Long bufFirst = first;
	return bufFirst-second;
}
template<>
Long operator-<int>(int first, Long second) {
	Long buf = first;
	return (buf - second);
}
template<>
Long operator-<char*>(char* first, Long second) {
	Long buf = first;
	return (buf - second);
}
template<>
Long operator-<const char*>(const char* first, Long second) {
	Long buf = first;
	return (buf - second);
}

template<typename T>
Long operator-(Long first, T second) {
	Long bufSecond = second;
	return first - bufSecond;
}
template<>
Long operator-<int>(Long first, int second) {
	Long buf = second;
	return (first - buf);
}
template<>
Long operator-<char*>(Long first, char* second) {
	Long buf = second;
	return (first - buf);
}
template<>
Long operator-<const char*>(Long first, const char* second) {
	Long buf = second;
	return (first - buf);
}


Long operator*(Long first, Long second) {
	Long bufLong=0;
	if (first == 0 || second == 0)
		return bufLong;
	if (first < 0) {
		first.change_minus();
		bufLong.isMinus = !bufLong.isMinus;
	}
	if (second < 0) {
		second.change_minus();
		bufLong.isMinus = !bufLong.isMinus;
	}

	if (second == -1) {
		first.change_minus();
	}

	while (!(second == 0)) {
		bufLong = bufLong + first;
		second--;
	}


	return bufLong;
}


template<typename T>
Long operator*(T first, Long second) {
	Long bufFirst = first;
	return bufFirst * second;
}
template<>
Long operator*<int>(int first, Long second) {
	Long buf = first;
	return (buf * second);
}
template<>
Long operator*<char*>(char* first, Long second) {
	Long buf = first;
	return (buf * second);
}
template<>
Long operator*<const char*>(const char* first, Long second) {
	Long buf = first;
	return (buf * second);
}

template<typename T>
Long operator*(Long first, T second) {
	Long bufSecond = second;
	return first * bufSecond;
}
//template<>
//Long operator*<int>(Long first, int second) {
//	Long buf = second;
//	return (first * buf);
//}
template<>
Long operator*<char*>(Long first, char* second) {
	Long buf = second;
	return (first * buf);
}
template<>
Long operator*<const char*>(Long first, const char* second) {
	Long buf = second;
	return (first * buf);
}



template<typename T>
bool operator==(T& first, Long& second) {
	Long bufLong = first;
	if (bufLong.isMinus == second.isMinus && bufLong.size == second.size) {

		for (int i = 0; i < bufLong.size; i++) {
			
			if (bufLong.number[i] != second.number[i])
				return false;
		
		}
		return true;
	}
	return false;
}
template<typename T>
bool operator==(Long& first, T& second) {
	Long bufLong = second;
	if (first.isMinus == bufLong.isMinus && first.size == bufLong.size) {

		for (int i = 0; i < bufLong.size; i++) {

			if (bufLong.number[i] != first.number[i])
				return false;

		}
		return true;
	}
	return false;
}
bool operator==(Long first, Long second) {
	std::cout << std::endl;
	if (first.isMinus == second.isMinus && first.size == second.size) {

		for (int i = 0; i < first.size; i++) {

			if (first.number[i] != second.number[i])
				return false;

		}
		return true;
	}
	return false;
}


bool Long::operator>=(Long& second) {
	if (this->isMinus && second.isMinus) {
		if (this->size < second.size)
			return true;
		if (this->size > second.size)
			return false;

		for (int i = 0; i < this->size; i++) {
			if (this->number[i] < second.number[i])
				return true;
			if (this->number[i] > second.number[i])
				return false;
		}
		return true;
	}
	else if (this->isMinus && (!second.isMinus)) {
		return false;
	}
	else if (!this->isMinus && second.isMinus) {
		return true;
	}
	else {
		if (this->size > second.size)
			return true;
		if (this->size < second.size)
			return false;

		for (int i = 0; i < this->size; i++) {
			if (this->number[i] > second.number[i])
				return true;
			if (this->number[i] < second.number[i])
				return false;
		}
		return true;
	
	}
}
bool Long::operator<=(Long& second) {
	if (this->isMinus && second.isMinus) {
		if (this->size > second.size)
			return true;
		if (this->size < second.size)
			return false;

		for (int i = 0; i < this->size; i++) {
			if (this->number[i] > second.number[i])
				return true;
			if (this->number[i] < second.number[i])
				return false;
		}
		return true;
	}
	else if (this->isMinus && (!second.isMinus)) {
		return true;
	}
	else if (!(this->isMinus) && second.isMinus) {
		return false;
	}
	else {
		if (this->size < second.size)
			return true;
		if (this->size > second.size)
			return false;

		for (int i = 0; i < this->size; i++) {
			if (this->number[i] < second.number[i])
				return true;
			if (this->number[i] > second.number[i])
				return false;
		}
		return true;
	}
}
bool Long::operator>(Long& second) {
	if (this->isMinus && second.isMinus) {
		if (this->size < second.size)
			return true;
		if (this->size > second.size)
			return false;

		for (int i = 0; i < this->size; i++) {
			if (this->number[i] < second.number[i])
				return true;
			if (this->number[i] > second.number[i])
				return false;
		}
		return true;
	}
	else if (this->isMinus && (!second.isMinus)) {
		return false;
	}
	else if (!this->isMinus && second.isMinus) {
		return true;
	}
	else {
		if (this->size > second.size)
			return true;
		if (this->size < second.size)
			return false;

		for (int i = 0; i < this->size; i++) {
			if (this->number[i] > second.number[i])
				return true;
			if (this->number[i] < second.number[i])
				return false;
		}
		return false;
	}
}
bool Long::operator<(Long& second) {
	if (this->isMinus && second.isMinus) {
		if (this->size > second.size)
			return true;
		if (this->size < second.size)
			return false;

		for (int i = 0; i < this->size; i++) {
			if (this->number[i] > second.number[i])
				return true;
			if (this->number[i] < second.number[i])
				return false;
		}
		return true;
	}
	else if (this->isMinus && (!second.isMinus)) {
		return true;
	}
	else if (!(this->isMinus) && second.isMinus) {
		return false;
	}
	else {
		if (this->size < second.size)
			return true;
		if (this->size > second.size)
			return false;

		for (int i = 0; i < this->size; i++) {
			if (this->number[i] < second.number[i])
				return true;
			if (this->number[i] > second.number[i])
				return false;
		}
		return false;
	}
}


bool Long::operator>=(int second) {
	Long bufLong = second;
	return (*this >= bufLong);
}
bool Long::operator<=(int second) {
	Long bufLong = second;
	return (*this <= bufLong);
}
bool Long::operator>(int second) {
	Long bufLong = second;
	return (*this > bufLong);
}
bool Long::operator<(int second) {
	Long bufLong = second;
	return (*this < bufLong);
}

bool Long::operator>=(char* second) {
	Long bufLong = second;
	return (*this >= bufLong);
}
bool Long::operator<=(char* second) {
	Long bufLong = second;
	return (*this <= bufLong);
}
bool Long::operator>(char* second) {
	Long bufLong = second;
	return (*this > bufLong);
}
bool Long::operator<(char* second) {
	Long bufLong = second;
	return (*this < bufLong);
}

bool Long::operator>=(const char* second) {
	Long bufLong = second;
	return (*this >= bufLong);
}
bool Long::operator<=(const char* second) {
	Long bufLong = second;
	return (*this <= bufLong);
}
bool Long::operator>(const char* second) {
	Long bufLong = second;
	return (*this > bufLong);
}
bool Long::operator<(const char* second) {
	Long bufLong = second;
	return (*this < bufLong);
}

std::istream& operator>> (std::istream& in, Long& object) {
	int buf;
	in >> buf;
	object = buf;
	return in;
}
std::ostream& operator<< (std::ostream& out, const Long& object){
	char* bufStr = new char[object.size];
	for (int i = 0; i < object.size; i = i + 1) {
		out.put(object.number[i]);
	}
	return out;
}


Long& Long::operator--(int) {
	if (*this <= 0) {
		*this = *this * -1;
		this->operator++(1);

		*this = *this * -1;
		return *this;
	}
	else {
		this->number[this->size - 2] -= 1;
		for (int i = this->size - 2; i >= 1; i--) {
			if (this->number[i] < '0') {
				this->number[i] += 10;
				this->number[i - 1] -= 1;
			}
		}
		return *this;
	}
}
Long& Long::operator++(int) {
	if (*this <= 0) {
		*this = *this * -1;
		this->operator--(1);

		*this = *this * -1;
		return *this;

	}
	else {
		this->number[this->size - 2] += 1;
		for (int i = this->size - 2; i >= 1; i--) {
			if (this->number[i] > '9') {
				this->number[i] -= 10;
				this->number[i - 1] += 1;
			}
		}
		return *this;
	}
}

template <typename T>
Long& Long::operator=(T& second) {
	Long bufLong = second;
	this->size = bufLong.size;
	this->isMinus = bufLong.isMinus;
	char* bufStr = new char[this->size + 1];
	for (int i = 0; i < this->size; i++) {
		bufStr[i] = bufLong.number[i];
	}
	bufStr[this->size] = '\0';
	delete[] this->number;
	this->number = bufStr;
	return *this;
}

template <>
Long& Long::operator=<Long>(Long& second) {
	this->size = second.size;
	this->isMinus = second.isMinus;
	char* bufStr = new char[this->size + 1];
	for (int i = 0; i < this->size; i++) {
		bufStr[i] = second.number[i];
	}
	bufStr[this->size] = '\0';
	delete[] this->number;
	this->number = bufStr;
	return *this;
}

template <>
Long& Long::operator=<const Long>(const Long& second) {
	this->size = second.size;
	this->isMinus = second.isMinus;
	char* bufStr = new char[this->size + 1];
	for (int i = 0; i < this->size; i++) {
		bufStr[i] = second.number[i];
	}
	bufStr[this->size] = '\0';
	delete[] this->number;
	this->number = bufStr;
	return *this;
}






