#ifndef _BASE_SYSTEMS_H
#define _BASE_SYSTEMS_H

#include <stdexcept>
#include <string>

namespace linalg {

    class base_systems_init_error : public std::runtime_error {
    public:
        explicit base_systems_init_error( const std::string& what)
            : std::runtime_error { what } {}
        explicit base_systems_init_error( const char* what)
            : std::runtime_error { what } {}
    };

    // initialise base resources and free them at destruction
    class base_systems {
    public:
        base_systems();
        ~base_systems();
    };
    

} // namespace linalg
#endif
