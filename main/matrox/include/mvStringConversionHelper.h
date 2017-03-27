#pragma once
#include <string>

class CMvWideCharString
{
public:
	CMvWideCharString(const std::string in_string);
	~CMvWideCharString();
	
public:
	operator std::wstring ()
	{
		return m_wString;
	}

	void Set(const std::string in_string);
	
	std::wstring Get()
	{
		return m_wString;
	}
	
	wchar_t * c_str()
	{
		return (wchar_t *) m_wString.c_str();
	}
private:
	std::wstring	m_wString;
};

class CMvMultiByteString
{
public:
	CMvMultiByteString(const std::wstring in_string);
	~CMvMultiByteString();
	
public:
	operator std::string ()
	{
		return m_String;
	}

	void Set(const std::wstring in_string);
	
	std::string Get()
	{
		return m_String;
	}

	char * c_str()
	{
		return (char *) m_String.c_str();
	}

private:
	std::string	m_String;
};


