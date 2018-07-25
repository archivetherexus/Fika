#include "fika/containers/immutable_array.hpp"

using namespace fika;

static ImmutableArrayResource<Empty> empty_immutable_array_resource_object(0, 0);

ImmutableArrayResource<Empty> *empty_immutable_array_resource = &empty_immutable_array_resource_object;