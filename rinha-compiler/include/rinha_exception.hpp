#include <iostream>
#include <exception>
#include <ast.hpp>
#include <memory>
#include <string>
#include <stdexcept>

#ifndef RINHA_EXEPTION_HPP
#define RINHA_EXEPTION_HPP

namespace rinha_compiler{
    
    template<typename ... Args>
    std::string string_format( const std::string&, Args ...);

    class RinhaException: public std::exception
    {
        private:
            std::string msg;
            Location location;
            int has_location = false;
        
        public:
            RinhaException(std::string, Location);
            RinhaException(std::string);
            //template<typename ... Args>
            //RinhaException(const std::string&, Args ...);

            virtual std::string message() const throw();
    };

    
}

#endif