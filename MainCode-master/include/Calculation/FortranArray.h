#ifndef Calculation_FortranArray_h
#define Calculation_FortranArray_h

#include <array>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <type_traits>

//namespace DragonWell {

template<typename T, int Rank>
struct FortranArray {
 static_assert(Rank >= 1, "Rank must be >= 1");
 //static_assert(std::is_arithmetic_v<T>, "T should be arithmetic (or relax this if you want).");

  std::array<int, Rank> lb{};   // lower bounds
  std::array<int, Rank> ub{};   // upper bounds
  std::array<int, Rank> ext{};  // extents
  std::array<std::size_t, Rank> stride{}; // column-major strides
  std::vector<T> v;

  FortranArray() = default;

  template<typename... Ints>
  explicit FortranArray(Ints... bounds) {
    static_assert(sizeof...(bounds) == 2 * Rank, "Need exactly 2*Rank bounds: (l1,u1,l2,u2,...)");
    resize(bounds...);
  }

  template<typename... Ints>
  void resize(Ints... bounds) {
    static_assert(sizeof...(bounds) == 2 * Rank, "Need exactly 2*Rank bounds: (l1,u1,l2,u2,...)");
    std::array<int, 2 * Rank> b{ static_cast<int>(bounds)... };

    for (int d = 0; d < Rank; ++d) {
      lb[d] = b[2 * d + 0];
      ub[d] = b[2 * d + 1];
      if (ub[d] < lb[d]) throw std::invalid_argument("FortranArray: upper bound < lower bound");
      ext[d] = ub[d] - lb[d] + 1;
    }

    // Fortran column-major:
    // stride[0]=1; stride[d]=stride[d-1]*ext[d-1]
    stride[0] = 1;
    for (int d = 1; d < Rank; ++d) {
      stride[d] = stride[d - 1] * static_cast<std::size_t>(ext[d - 1]);
    }

    std::size_t total = 1;
    for (int d = 0; d < Rank; ++d) total *= static_cast<std::size_t>(ext[d]);

    v.assign(total, T{});
  }

  void fill(const T& value) {
    std::fill(v.begin(), v.end(), value);
  }

  int lbound(int dim) const { return lb.at(dim - 1); }  // dim=1..Rank
  int ubound(int dim) const { return ub.at(dim - 1); }
  int extent(int dim) const { return ext.at(dim - 1); }
  std::size_t size()  const { return v.size(); }

  T* data() { return v.data(); }
  const T* data() const { return v.data(); }

private:
  template<typename... Ints>
  std::size_t linear_index(Ints... indices) const {
    static_assert(sizeof...(indices) == Rank, "Need exactly Rank indices");
    std::array<int, Rank> idx{ static_cast<int>(indices)... };

//#ifndef NDEBUG
//    for (int d = 0; d < Rank; ++d) {
//      if (idx[d] < lb[d] || idx[d] > ub[d]) {
//        throw std::out_of_range("FortranArray: index out of range");
//      }
//    }
//#endif

    std::size_t lin = 0;
    for (int d = 0; d < Rank; ++d) {
      lin += static_cast<std::size_t>(idx[d] - lb[d]) * stride[d];
    }
    return lin;
  }

public:
  template<typename... Ints>
  T& operator()(Ints... indices) {
    return v[linear_index(indices...)];
  }

  template<typename... Ints>
  const T& operator()(Ints... indices) const {
    return v[linear_index(indices...)];
  }
};

template<typename T> using FortranArray1D = FortranArray<T,1>;
template<typename T> using FortranArray2D = FortranArray<T,2>;
template<typename T> using FortranArray3D = FortranArray<T,3>;
template<typename T> using FortranArray4D = FortranArray<T,4>;
template<typename T> using FortranArray5D = FortranArray<T,5>;

//
// FortranArray1D<double> a(-2, 5);                 // array(-2:5)
// a(-2) = 1.0;  a(5) = 2.0;
//
// FortranArray2D<double> b(-2, 5, -5, 10);         // array(-2:5, -5:10)
// b(-2, -5) = 3.14; b(5, 10) = 2.71;
//
// FortranArray5D<double> c(1,2,  -1,1,  0,3,  5,5,  -2,2); //
// c(1,-1,0,5,-2) = 42.0;

//}
#endif
