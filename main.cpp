#include "src/fika/io.hpp"

int main(int argc, char **args) {
    const fika::String &str1{};
    const fika::String &str2{};

    fika::io.print(&str1);
    fika::io.print(&str1, &str2);

    return 0;
}