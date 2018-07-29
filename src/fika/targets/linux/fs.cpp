#include "fika/fs.hpp"


namespace fika {
    StandardFileSystem fs{};

    class StandardEntry : public VirtualFileSystem::Entry {
    public:
        virtual bool exists() override {

            // TODO: Move this elsewhere.
            auto c_string = new char[path.count()];
            auto iterator = path.iterator(0);
            U64 index = 0;
            while(iterator.has_next()) {
                c_string[index++] = iterator.next();
            }

            puts(c_string);

            auto result = false;

            delete[] c_string;

            return result;
        }

        Path path;
        StandardEntry(Path path)
        : path(path) {

        }
    };

    VirtualFileSystem::Entry StandardFileSystem::entry(Path path) {
        // TODO: Object slicing takes place here... Solve with proper "smart pointers..."
        return StandardEntry(path);
    }
}