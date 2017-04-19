#pragma once

#include <algorithm>

template <class It>
void
insertion_sort(It f, It e) {
    auto const s = f;
    for (; f != e; ++f) {
        std::rotate(std::upper_bound(s, f, *f), f, f+1);
    }
}

