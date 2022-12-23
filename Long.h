#pragma once
#include <iostream>
class Long
{
private:
	char*	number;
	int		size;

	bool	isMinus;


	
public:
	Long();
	Long(int other);
	Long(char* other);
	Long(const char* other);
	Long(const Long& other);

	~Long();
	Long& change_minus();

	//operator int()		{ return (atoi(this->number)); }
	//operator char*()	{ return (this->number); };


	static char* remove_start_zeros(char* n);
	static char* remove_start_zeros(const char* n);
	
	
	template<typename T>
	friend Long operator+(Long first, T second);
	template<typename T>
	friend Long operator+(T first, Long second);

	friend Long operator+(Long first, Long second);


	template<typename T>
	friend Long operator-(T first, Long second);
	template<typename T>
	friend Long operator-(Long first, T second);
	friend Long operator-(Long first, Long second);


	template<typename T>
	friend Long operator*(T first, Long second);
	template<typename T>
	friend Long operator*(Long first, T second);

	friend Long operator*(Long first, Long second);
	

	template<typename T>
	friend bool operator==(Long& first, T& second);
	template<typename T>
	friend bool operator==(T& first, Long& second);
	friend bool operator==(Long first, Long second);


	bool operator>=(Long& second);
	bool operator<=(Long& second);
	bool operator>(Long& second);
	bool operator<(Long& second);


	bool operator>=(int second);
	bool operator<=(int second);
	bool operator>(int second);
	bool operator<(int second);


	bool operator>=(char* second);
	bool operator<=(char* second);
	bool operator> (char* second);
	bool operator< (char* second);


	bool operator>=(const char* second);
	bool operator<=(const char* second);
	bool operator> (const char* second);
	bool operator< (const char* second);



	template <typename T>
	Long& operator=(T& second);


	
	Long& operator--(int);
	Long& operator++(int);

	//Long& operator=(const char* other);
	//Long& operator=(char* other);
	//Long& operator=(int second);

	friend std::ostream& operator<< (std::ostream& out, const Long& object);

	friend std::istream& operator>> (std::istream& in, Long& object);


};



