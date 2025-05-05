#include "renderlist.hpp"

std::array<float, 12> RenderList::k_vertices_ {
    1.0F,
    1.0F,
    0,
    1.0F,
    -1.0F,
    0,
    -1.0F,
    -1.0F,
    0,
    -1.0F,
    1.0F,
    0,
};

std::array<unsigned, 6> RenderList::k_indices_ {0, 1, 3, 1, 2, 3};
