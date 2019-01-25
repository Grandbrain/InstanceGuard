/// \file InstanceGuard.hpp
/// \brief Contains classes and functions declarations that help prevent
/// \brief multiple instances of an application from running.
/// \bug No known bugs.

#ifndef INSTANCEGUARD_HPP
#define INSTANCEGUARD_HPP

#include <memory>
#include <string>

/// Contains classes and functions that help prevent multiple instances of an
/// application from running.
namespace InstanceGuard {

    /// Class that helps prevent multiple instances of an application from
    /// running.
    class InstanceGuard {
    public:

        /// Constructor.
        /// \param name Name of the blocking handle.
        explicit InstanceGuard(const std::string& name);

        /// Destructor.
        ~InstanceGuard();

        /// Checks if another instance of the application is running.
        /// \retval true if multiple instances are running.
        /// \retval false if single instance is running.
        bool IsAnotherInstanceRunning() const;

    private:

        /// Structure that provides private storage for OS dependent objects.
        struct Private;

        /// Private data.
        std::unique_ptr<Private> private_;
    };
}

#endif
