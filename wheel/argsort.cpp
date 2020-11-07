// https://gist.github.com/HViktorTsoi/58eabb4f7c5a303ced400bcfa816f6f5

#include <algorithm>
#include <vector>

/**
 * Argsort(currently support ascending sort)
 * @tparam T array element type
 * @param array input array
 * @return indices w.r.t sorted array
 */
template <typename T>
std::vector<size_t> argsort(const std::vector<T> &array) {
    std::vector<size_t> indices(array.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(),
              [&array](int left, int right) -> bool {
                  // sort indices according to corresponding array element
                  return array[left] < array[right];
              });

    return indices;
}