#include <string>
#include <exception>
#ifndef VALIDATOR_H
#define VALIDATOR_H

namespace Exceptions
{

	class Keyword_order_error : public std::exception
	{
	public:
		Keyword_order_error(const std::string& Lastkey, const std::string& key)
			: m_what(" violation of the order of keywords:" + Lastkey + " " + key)
		{
		}

		virtual const char* what() const throw() {
			return m_what.c_str();
		}

	private:
		std::string m_what;
	};

	class Bad_keyword_error : public std::exception
	{
	public:
		Bad_keyword_error( const std::string& key)
			: m_what(" found incorrect keyword:" + key)
		{
		}

		virtual const char* what() const throw() {
			return m_what.c_str();
		}

	private:
		std::string m_what;
	};

	class File_Error : public std::exception
	{
	public:
		File_Error(const std::string& file)
			: m_what(" I/O error:" + file)
		{
		}

		virtual const char* what() const throw() {
			return m_what.c_str();
		}

	private:
		std::string m_what;
	};

	class EOF_Error : std::exception
	{
	public:
		EOF_Error(const std::string& file)
			: m_what("Unexpected end of file " + file)
		{
		}

		virtual const char* what() const throw() {
			return m_what.c_str();
		}

	private:
		std::string m_what;
	};

	class BlockNotDefined : std::exception
	{
	public:
		BlockNotDefined(const std::string& block)
			: m_what("Can't find block with name: " + block)
		{
		}

		virtual const char* what() const throw() {
			return m_what.c_str();
		}

	private:
		std::string m_what;
	};

	class BlockRedefinition : std::exception
	{
	public:
		BlockRedefinition(const std::string& block)
			: m_what("Block " + block + " is already defined")
		{
		}

		virtual const char* what() const throw() {
			return m_what.c_str();
		}

	private:
		std::string m_what;
	};

	class FileNotCreated : std::exception
	{
	public:
		FileNotCreated(const std::string& file)
			: m_what("File Not Created " + file)
		{
		}

		virtual const char* what() const throw() {
			return m_what.c_str();
		}

	private:
		std::string m_what;
	};

	class BadArguments : std::exception
	{
	public:
		BadArguments(const std::string& m)
			: m_what("Bad Argument " + m)
		{
		}

		virtual const char* what() const throw() {
			return m_what.c_str();
		}

	private:
		std::string m_what;
	};
}

#endif // !VALIDATOR_H