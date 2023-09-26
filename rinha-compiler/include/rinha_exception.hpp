#include <iostream>
#include <exception>
#include <ast.hpp>
#include <memory>
#include <string>
#include <stdexcept>

#ifndef RINHA_EXEPTION_HPP
#define RINHA_EXEPTION_HPP

namespace rinha_compiler{
    

    class RinhaException: public std::exception
    {
        private:
            std::string msg;
            Location location;
        
        public:
            RinhaException(std::string, Location);

            virtual std::string message() const throw();
    };

    
}

#endif