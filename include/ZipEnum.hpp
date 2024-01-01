#pragma once

#include <tuple>
#include <type_traits>

namespace zip_enum {

template <class T>
using ref_or_copy_t = std::conditional_t<
    std::is_convertible_v<T, std::add_lvalue_reference<T>>,
    std::add_lvalue_reference<T>, T>;

template<class T1, class T2>
struct Zip {
    T1 &c1_;
    T2 &c2_;

    using iterator1 = decltype(c1_.begin());
    using iterator2 = decltype(c2_.begin());
    using terminator1 = decltype(c1_.end());
    using terminator2 = decltype(c2_.end());

    Zip(T1 &c1, T2 &c2) : c1_(c1), c2_(c2) {}

    struct terminator {
        terminator1 t1_;
        terminator2 t2_;
    };

    struct iterator {
        iterator1 i1_;
        iterator2 i2_;

        using V1 = ref_or_copy_t<decltype(*i1_)>;
        using V2 = ref_or_copy_t<decltype(*i2_)>;

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
        return iterator {c1_.begin(), c2_.begin()};
    }

    auto end() {
        return terminator {c1_.end(), c2_.end()};
    }
};

template<class T1, class T2>
inline auto zip(T1 &a, T2 &b) {
    return Zip<T1, T2>(a, b);
}

template<class T1, class T2, class T3>
struct Zip3 {
    T1 &c1_;
    T2 &c2_;
    T3 &c3_;

    using iterator1 = decltype(c1_.begin());
    using iterator2 = decltype(c2_.begin());
    using iterator3 = decltype(c3_.begin());
    using terminator1 = decltype(c1_.end());
    using terminator2 = decltype(c2_.end());
    using terminator3 = decltype(c3_.end());

    Zip3(T1 &c1, T2 &c2, T3 &c3) : c1_(c1), c2_(c2), c3_(c3) {}

    struct terminator {
        terminator1 t1_;
        terminator2 t2_;
        terminator3 t3_;
    };

    struct iterator {
        iterator1 i1_;
        iterator2 i2_;
        iterator3 i3_;

        using V1 = ref_or_copy_t<decltype(*i1_)>;
        using V2 = ref_or_copy_t<decltype(*i2_)>;
        using V3 = ref_or_copy_t<decltype(*i3_)>;

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
        return iterator {c1_.begin(), c2_.begin(), c3_.begin()};
    }

    auto end() {
        return terminator {c1_.end(), c2_.end(), c3_.end()};
    }
};

template<class T1, class T2, class T3>
inline auto zip(T1 &a, T2 &b, T3 &c) {
    return Zip3<T1, T2, T3>(a, b, c);
}


template<class T, class Int = int>
struct Enumerate {
    T &c_;
    Enumerate(T &c) : c_(c) {}

    using Iterator = decltype(c_.begin());
    using Terminator = decltype(c_.end());

    struct iterator {
        Iterator i_;
        Int c_ = 0;

        using Value = ref_or_copy_t<decltype(*i_)>;

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
        return iterator(c_.begin());
    }

    auto end() {
        return c_.end();
    }
};

template<class T1, class T2, class Int = int>
struct Enumerate2 {
    T1 &c1_;
    T2 &c2_;
    Enumerate2(T1 &c1, T2 &c2) : c1_(c1), c2_(c2) {}

    using Iterator1 = decltype(c1_.begin());
    using Iterator2 = decltype(c2_.begin());
    using Terminator1 = decltype(c1_.end());
    using Terminator2 = decltype(c2_.end());

    struct terminator {
        Terminator1 t1_;
        Terminator2 t2_;
    };

    struct iterator {
        Iterator1 i1_;
        Iterator2 i2_;
        Int c_ = 0;

        using Value1 = ref_or_copy_t<decltype(*i1_)>;
        using Value2 = ref_or_copy_t<decltype(*i2_)>;

        bool operator!=(terminator const& a) const {
            return (i1_ != a.t1_) && (i2_ != a.t2_);
        }

        auto operator*() const {
            return std::tuple<int, Value1, Value2> {c_, *i1_, *i2_};
        }

        iterator& operator++() {
            ++i1_;
            ++i2_;
            ++c_;
            return *this;
        }
    };

    auto begin() {
        return iterator {c1_.begin(), c2_.begin()};
    }

    auto end() {
        return terminator {c1_.end(), c2_.end()};
    }
};

template<class T>
inline auto enumerate(T &a) {
    return Enumerate<T>(a);
}

template<class T1, class T2>
inline auto enumerate(T1 &a, T2 &b) {
    return Enumerate2<T1, T2>(a, b);
}


} // end of namespace