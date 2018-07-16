#include "src/fika/io.hpp"
#include "src/fika/array.hpp"

int main(int argc, char **args) {
    const fika::String str1 = fika::String{};
    const fika::String str2 = fika::String{};

    const fika::Array<32, int> arr;

    arr.iterator().next();

    fika::io.print(str1);
    fika::io.print(str1, str2);

    return 0;
}