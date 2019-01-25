/// \file InstanceGuard.cpp
/// \brief Contains classes and functions definitions that help prevent
/// \brief multiple instances of an application from running.
/// \bug No known bugs.

#include "InstanceGuard.hpp"
#include "config.h"

#if defined(OS_WIN)
    #include <windows.h>
#elif defined(OS_UNIX)
    #include <fcntl.h>
    #include <unistd.h>
#else
    #error "Code has not been ported to this platform"
#endif

/// Contains classes and functions that help prevent multiple instances of an
/// application from running.
namespace InstanceGuard {

    /// Structure that provides private storage for OS dependent objects.
    struct InstanceGuard::Private {
        /// Indicates whether another instance is running.
        bool exists_ = false;
#if defined(OS_WIN)
        /// Blocking mutex on Windows platforms.
        HANDLE mutex_ = nullptr;
#elif defined(OS_UNIX)
        /// Blocking file on Unix platforms.
        int fd_ = -1;
#endif
    };

    /// Constructor.
    /// \details Initializes blocking handles.
    /// \param name Name of the blocking handle.
    InstanceGuard::InstanceGuard(const std::string& name)
        : private_(new Private) {
#if defined(OS_WIN)
        private_->mutex_ = CreateMutexA(NULL, FALSE, name.c_str());
        private_->exists_ = GetLastError() == ERROR_ALREADY_EXISTS;
#elif defined(OS_UNIX)
        private_->fd_ = open(("/tmp/" + name).c_str(), O_CREAT | O_RDWR, 0666);

        struct flock lock {0};
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_CUR;
        lock.l_start = 0;
        lock.l_len = 0;

        private_->exists_ = fcntl(private_->fd_, F_SETLK, &lock) < 0;
#endif
    }

    /// Destructor,
    /// \details Releases and invalidates blocking handles.
    InstanceGuard::~InstanceGuard() {
#if defined(OS_WIN)
        if (private_->mutex_)
            CloseHandle(private_->mutex_);

        private_->mutex_ = nullptr;
        private_->exists_ = false;
#elif defined(OS_UNIX)
        close(private_->fd_);
        private_->fd_ = -1;
        private_->exists_ = false;
#endif
    }

    /// Checks if another instance of the application is running.
    /// \details Checks flag that indicates if another instance is running.
    /// \retval true if multiple instances are running.
    /// \retval false if single instance is running.
    bool InstanceGuard::IsAnotherInstanceRunning() const {
        return private_->exists_;
    }
}
