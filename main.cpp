#include "src/fika/initializer_list.hpp"

#include "src/fika/io.hpp"
#include "src/fika/containers/fixed_array.hpp"
#include "src/fika/containers/array.hpp"
#include "src/fika/containers/immutable_array.hpp"
#include "src/fika/pair.hpp"
#include "src/fika/containers/map.hpp"
#include "src/fika/lambda.hpp"
#include <cstdio>

int main(int argc, char **args) {

    auto l = []() {return 0;};

    fika::Lambda<int(void)> l2;
    l2 = [](){return 1;};

    // TODO: Allow this:
    // fika::Lambda<int(void)> l2 = [](){return 1;};

    printf("Test: %d\n", l2());


    auto arra1 = fika::Array<int>({32, 3});
    arra1 = {1, 2, 3};

    auto arra2 = fika::FixedArray<2, int>({1, 2});
    arra2 = {3, 4};


    auto m = new fika::Map<int, int>(-1);
    m->set(2, 42);
    m->set(5, 32);
    printf("The get: %d, %d\n", m->get(2), m->get(5));
    fika::to_hash(32);

    auto iterator2 = m->iterator();
    while(iterator2.has_next()) {
        auto p = iterator2.next();
        printf("%d: %d\n", p.a, p.b);
    }

    m->clear();

    auto iterator3 = m->iterator();
    while(iterator3.has_next()) {
        auto p = iterator3.next();
        printf("%d: %d\n", p.a, p.b);
    }

    m->set(999, 43);

    auto iterator4 = m->iterator();
    while(iterator4.has_next()) {
        auto p = iterator4.next();
        printf("%d: %d\n", p.a, p.b);
    }

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