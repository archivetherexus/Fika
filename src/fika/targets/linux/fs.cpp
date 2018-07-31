#include "fika/fs.hpp"
#include "syscall.hpp"
#include "syscalls.hpp"
#include <cstring>

namespace fika {

    const U64 F_OK = 0; // Test for existence.          //
    const U64 X_OK = 1; // Test for execute permission. //
    const U64 W_OK = 2; // Test for write permission.   //
    const U64 R_OK = 4; // Test for read permission.    //

    class StandardEntryResource : public VirtualFileSystem::EntryResource {
    public:
        virtual bool exists() override {

            // TODO: Move this elsewhere. Perhaps... c_string()
            auto c_string = new char[path.count() + 1];
            auto iterator = path.iterator(0);
            U64 index = 0;
            while(iterator.has_next()) {
                c_string[index++] = iterator.next();
            }
            c_string[index] = '\0';

            // TODO: Maybe not use hardcoded constants?
            auto result = fika_sysv_syscall(fika::Syscalls::ACCESS, (U64)c_string, F_OK, 0) == 0;

            delete[] c_string;

            return result;
        }

        Path path;
        StandardEntryResource(Path path)
        : path(path) {

        }
    };

    static FileSystemImplementation<StandardEntryResource> fs_implementation{};

    VirtualFileSystem &fs = fs_implementation;
}