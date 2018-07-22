#pragma once
#ifndef FIKA_RE_IF_HPP
#define FIKA_RE_IF_HPP

namespace fika {
    namespace re {
        template<bool B, class T = void> class If {
            
        };

        template<class T> class If<true, T> {
        public:
            typedef T type;
        };
    }
}

#endif