#include <rinha_exception.hpp>

namespace rinha_compiler{

    template<typename ... Args>
    std::string string_format( const std::string&, Args ...);

    RinhaException::RinhaException(std::string msg, Location location){
        this->msg = msg;
        this->location = location;
    }

    std::string RinhaException::message() const throw()
    {
        return string_format("File: %s -> Start: %d, End: %d. Error: %s", location.filename.c_str(), location.start, location.end, msg.c_str());
    }

    template<typename ... Args>
    std::string string_format( const std::string& format, Args ... args )
    {//https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
        int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
        if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
        auto size = static_cast<size_t>( size_s );
        std::unique_ptr<char[]> buf( new char[ size ] );
        std::snprintf( buf.get(), size, format.c_str(), args ... );
        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
    }
}