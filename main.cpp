#include "src/fika/pair.hpp"
#include "src/fika/lambda.hpp"
#include "src/fika/io.hpp"
#include "src/fika/containers/fixed_array.hpp"
#include "src/fika/containers/array.hpp"
#include "src/fika/containers/immutable_array.hpp"
#include "src/fika/containers/map.hpp"
#include "src/fika/fs.hpp"
#include <cstdio>

#include "syscall.hpp"

int main(int argc, char **args) {

    //fika::FixedArray<2, int>::from({1, 2, 3, 4});

    auto e1 = fika::fs.entry("/home/katou/file");
    puts(e1.exists() ? "It exists!" : "It does not exist!");
    auto e2 = fika::fs.entry("/home/katou/file-blablabla");
    puts(e2.exists() ? "It exists!" : "It does not exist!");

    (void)argc;
    (void)args;

    auto ll3 = new fika::Lambda<int()>([](){return 3;});

    auto ll4 = fika::Lambda<int()>([](){return 3;});

    (*ll3)();

    delete ll3;

    ll4();

    auto l3 = fika::Array<fika::Lambda<int(void)>>::fill(32, ll4);

    auto l4 = fika::Array<int>::from({1, 2});

    auto l5 = fika::Array<int>::fill(32, 4);

    auto arra1 = fika::Array<int>::from({32, 3});
    arra1 = {1, 2, 3};

    auto arra2 = fika::FixedArray<2, int>::from({1, 2});
    arra2 = {3, 4};


    auto m = fika::Map<int, int>::create(-1);
    m.set(2, 42);
    m.set(5, 32);
    printf("The get: %d, %d\n", m.get(2), m.get(5));
    fika::to_hash(32);

    auto m2 = m;

    auto iterator2 = m.iterator(fika::Pair<int, int>(2, 3));
    while(iterator2.has_next()) {
        auto p = iterator2.next();
        printf("%d: %d\n", p.a, p.b);
    }

    m.clear();

    auto iterator3 = m.iterator(fika::Pair<int, int>(2, 3));
    while(iterator3.has_next()) {
        auto p = iterator3.next();
        printf("%d: %d\n", p.a, p.b);
    }

    m.set(999, 43);

    auto iterator4 = m.iterator(fika::Pair<int, int>(2, 3));
    while(iterator4.has_next()) {
        auto p = iterator4.next();
        printf("%d: %d\n", p.a, p.b);
    }

    auto p2 = iterator4.next();
    printf("Default value: %d, %d\n", p2.a, p2.b);

    int *a = new int(1);
    int *b = new int(2);

    auto p = fika::Pair<int*, int*>(a, b);
    printf("Result: %d", *p.a + *p.b);

    const fika::String str1 = "Hello ";
    const fika::String str2 = "World\n";

    fika::io.print(str1);
    fika::io.print(str1, str2);

    auto arr1 = fika::FixedArray<32, int>();

    auto arr2 = fika::Array<int>::create(32);

    auto arr3 = fika::ImmutableArray<int>::from({32});

    fika::ImmutableArray<int> arrs = {42, 14, 123};
    auto iterator = arrs.iterator(0);
    while(iterator.has_next()) {
        printf("From immutable array: %d\n", iterator.next());
    }

    arr1.iterator(1).next();
    arr2.iterator(1).next();
    arr3.iterator(1).next();

    for(int i: {1, 2, 3, 4, 5}) {
        printf("OK: %d\n", i);
    }

    delete a;
    delete b;

    return 0;
}