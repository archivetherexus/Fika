#pragma once
#ifndef FIKA_OUTPUT_STREAM_HPP
#define FIKA_OUTPUT_STREAM_HPP

namespace fika {
    class OutputStream {
    public:
        virtual void print_string(const class String string) = 0;
        template <class... ObjectTypes> void print(const ObjectTypes... objects) {
            // TODO: Perhaps there is a better method?
            const PrintableObject *to_print[] = {&objects...};
            const int to_print_size = sizeof(to_print) / sizeof(to_print[0]);
            for(int i = 0; i < to_print_size; i++) {
                print_string(to_print[i]->to_string());
            }
        }
    };
}

#endif