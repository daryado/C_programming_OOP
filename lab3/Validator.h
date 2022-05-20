#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <string>
#include <exception>

namespace Exceptions
{

    class File_missing_error : public std::exception
    {
    public:
        File_missing_error()
            : m_what(" File missing ")
        {
        }

        virtual const char* what() const throw() {
            return m_what.c_str();
        }

    private:
        std::string m_what;
    };

    class file_length_y_error : public std::exception
    {
    public:
        file_length_y_error()
            : m_what(" file length(y) error ")
        {
        }

        virtual const char* what() const throw() {
            return m_what.c_str();
        }

    private:
        std::string m_what;
    };

    class file_length_x_error : public std::exception
    {
    public:
        file_length_x_error()
            : m_what(" file length(x) error ")
        {
        }

        virtual const char* what() const throw() {
            return m_what.c_str();
        }

    private:
        std::string m_what;
    };

    class Invalid_number_of_args_error : public std::exception
    {
    public:
        Invalid_number_of_args_error()
            : m_what(" Invalid number of_args ")
        {
        }

        virtual const char* what() const throw() {
            return m_what.c_str();
        }

    private:
        std::string m_what;
    };

}


#endif // VALIDATOR_H
