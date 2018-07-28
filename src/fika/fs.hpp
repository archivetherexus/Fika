#pragma once
#ifndef FIKA_FS_HPP
#define FIKA_FS_HPP

#include "fika/string.hpp"

namespace fika {
    // TODO: Not sure if this implmenetation is really the... best...
    typedef String Path;
    class Location {
    };
    class FileSystemEntryState {
    public:
        virtual bool move(Location other) = 0;
        virtual bool move(Location other, String newName) = 0;
        virtual bool rename(class String newName);

        virtual void open() = 0; 
        virtual void close() = 0;

        virtual class FileSystemEntry *entry(String entryName) = 0;
    };
    class FileSystemEntry {
    public:
        virtual bool move(Location other) {
            return state->move(other);
        };
        virtual bool move(Location other, String newName) {
            return state->move(other, newName);
        }
        virtual bool rename(class String newName) {
            return state->rename(newName);
        }
    protected:
        FileSystemEntryState *state;
    };
    class File : FileSystemEntry {
    public:
        // TODO: There should be a way to get a InputOutputStream here.
        virtual void open() {
            state->open();
        }; 
        virtual void close() {
            state->close();
        }
    };
    class Directory : FileSystemEntry, Location {
        virtual FileSystemEntry entry(String entryName) {
            return *state->entry(entryName);
        }
    };
    class VirtualFileSystem {
    public:   
        virtual FileSystemEntry entry(Path path) = 0;
    };
}

#endif