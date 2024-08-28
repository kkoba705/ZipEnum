#pragma once

#include <utility>
#include <tuple>
#include <type_traits>

namespace zip_enum {

template<class T1, class T2>
struct Zip {
    T1 c1_;
    T2 c2_;

    using iterator1 = decltype(std::begin(c1_));
    using iterator2 = decltype(std::begin(c2_));
    using terminator1 = decltype(std::end(c1_));
    using terminator2 = decltype(std::end(c2_));

    Zip(T1 && c1, T2 && c2)  : 
        c1_(std::forward<T1>(c1)), c2_(std::forward<T2>(c2)) {}

    struct terminator {
        terminator1 t1_;
        terminator2 t2_;
    };

    struct iterator {
        iterator1 i1_;
        iterator2 i2_;

        using V1 = decltype(*i1_);
        using V2 = decltype(*i2_);

        bool operator!=(terminator const& a) const {
            return (i1_ != a.t1_) && (i2_ != a.t2_);
        }

        std::pair<V1, V2> operator*() const {
            return {*i1_, *i2_};
        }

        iterator& operator++() {
            ++i1_;
            ++i2_;
            return *this;
        }
    };

    auto begin() {
        return iterator {std::begin(c1_), std::begin(c2_)};
    }

    auto end() {
        return terminator {std::end(c1_), std::end(c2_)};
    }
};

template<class T1, class T2>
inline auto zip(T1 && a, T2 && b) {
    return Zip<T1, T2>(std::forward<T1>(a), std::forward<T2>(b));
}

template<class T1, class T2, class T3>
struct Zip3 {
    T1 c1_;
    T2 c2_;
    T3 c3_;

    using iterator1 = decltype(std::begin(c1_));
    using iterator2 = decltype(std::begin(c2_));
    using iterator3 = decltype(std::begin(c3_));
    using terminator1 = decltype(std::end(c1_));
    using terminator2 = decltype(std::end(c2_));
    using terminator3 = decltype(std::end(c3_));

    Zip3(T1 && c1, T2 && c2, T3 && c3) :
        c1_(std::forward<T1>(c1)), c2_(std::forward<T2>(c2)) , c3_(std::forward<T3>(c3)) {}

    struct terminator {
        terminator1 t1_;
        terminator2 t2_;
        terminator3 t3_;
    };

    struct iterator {
        iterator1 i1_;
        iterator2 i2_;
        iterator3 i3_;

        using V1 = decltype(*i1_);
        using V2 = decltype(*i2_);
        using V3 = decltype(*i3_);

        bool operator!=(terminator const& a) const {
            return (i1_ != a.t1_) && (i2_ != a.t2_) && (i3_ != a.t3_);
        }

        std::tuple<V1, V2, V3> operator*() const {
            return {*i1_, *i2_, *i3_};
        }

        iterator& operator++() {
            ++i1_;
            ++i2_;
            ++i3_;
            return *this;
        }
    };

    auto begin() {
        return iterator {std::begin(c1_), std::begin(c2_), std::begin(c3_)};
    }

    auto end() {
        return terminator {std::end(c1_), std::end(c2_), std::end(c3_)};
    }
};

template<class T1, class T2, class T3>
inline auto zip(T1 && a, T2 && b, T3 && c) {
    return Zip3<T1, T2, T3>(
        std::forward<T1>(a), std::forward<T2>(b), std::forward<T3>(c));
}


template<class T, class Int = int>
struct Enumerate {
    T c_;

    explicit Enumerate(T && c) : c_(std::forward<T>(c)) {}

    using Iterator = decltype(std::begin(c_));
    using Terminator = decltype(std::end(c_));

    struct iterator {
        Iterator i_;
        Int c_ = 0;

        using Value = decltype(*i_);

        iterator(Iterator i) : i_(i) {}

        bool operator!=(Terminator const& a) const {
            return (i_ != a);
        }

        auto operator*() const {
            return std::pair<int, Value>{c_, *i_};
        }

        iterator& operator++() {
            ++i_;
            ++c_;
            return *this;
        }
    };

    auto begin() {
        return iterator(std::begin(c_));
    }

    auto end() {
        return std::end(c_);
    }
};

template<class T1, class T2, class Int = int>
struct Enumerate2 {
    T1 c1_;
    T2 c2_;

    Enumerate2(T1 && c1, T2 && c2) : 
        c1_(std::forward<T1>(c1)), c2_(std::forward<T2>(c2)) {}

    using Iterator1 = decltype(std::begin(c1_));
    using Iterator2 = decltype(std::begin(c2_));
    using Terminator1 = decltype(std::end(c1_));
    using Terminator2 = decltype(std::end(c2_));

    struct terminator {
        Terminator1 t1_;
        Terminator2 t2_;
    };

    struct iterator {
        Iterator1 i1_;
        Iterator2 i2_;
        Int c_ = 0;

        using V1 = decltype(*i1_);
        using V2 = decltype(*i2_);

        bool operator!=(terminator const& a) const {
            return (i1_ != a.t1_) && (i2_ != a.t2_);
        }

        auto operator*() const {
            return std::tuple<int, V1, V2> {c_, *i1_, *i2_};
        }

        iterator& operator++() {
            ++i1_;
            ++i2_;
            ++c_;
            return *this;
        }
    };

    auto begin() {
        return iterator {std::begin(c1_), std::begin(c2_)};
    }

    auto end() {
        return terminator {std::end(c1_), std::end(c2_)};
    }
};

template<class T>
inline auto enumerate(T && a) {
    return Enumerate<T>(std::forward<T>(a));
}

template<class T1, class T2>
inline auto enumerate(T1 && a, T2 && b) {
    return Enumerate2<T1, T2>(std::forward<T1>(a), std::forward<T2>(b));
}


} // end of namespace