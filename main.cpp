#include "src/fika/initializer_list.hpp"

#include "src/fika/io.hpp"
#include "src/fika/fixed_array.hpp"
#include "src/fika/array.hpp"
#include "src/fika/immutable_array.hpp"
#include "src/fika/pair.hpp"
#include "src/fika/map.hpp"

#include <cstdio>

int main(int argc, char **args) {

    auto m = new fika::Map<int, int>();
    m->set(2, 42);
    printf("The get: %d\n", m->get(2));

    fika::to_hash(32);

    delete m;

    int *a = new int(1);
    int *b = new int(2);

    auto p = fika::Pair<int*, int*>(a, b);
    *p.a + *p.b;

    const fika::String str1 = "Hello ";
    const fika::String str2 = "World\n";

    fika::io.print(str1);
    fika::io.print(str1, str2);

    const fika::FixedArray<32, int> arr1;

    const fika::Array<int> arr2(32);

    const fika::ImmutableArray<int> arr3(32);

    fika::ImmutableArray<int> arrs = {42, 14, 123};
    auto iterator = arrs.iterator();
    while(iterator.has_next()) {
        printf("From immutable array: %d\n", iterator.next());
    }

    arr1.iterator().next();
    arr2.iterator().next();
    arr3.iterator().next();

    for(int i: {1, 2, 3, 4, 5}) {
        printf("OK: %d\n", i);
    }

    return 0;
}