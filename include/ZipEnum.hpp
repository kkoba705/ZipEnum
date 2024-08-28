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


template <typename ... A, typename ... E, std::size_t ... Index>
inline bool iterator_cmp(std::tuple<A...> const& a, std::tuple<E...> const& end, 
    std::index_sequence<Index...>) {
    bool r = true;
    r = (... && (std::get<Index>(a) != std::get<Index>(end)));
    return r;
}

template<typename ... T>
struct ZipN {
    std::tuple<T...> c_;

    using iterators = std::tuple<decltype(std::begin(std::declval<T>())) ...>;
    using terminators = std::tuple<decltype(std::end(std::declval<T>())) ...>;
    using values = std::tuple<decltype(*std::begin(std::declval<T>())) ...>;

    ZipN(T && ... c)  : c_{std::forward<T>(c) ...} {}

    struct terminator {
        terminators t_;
    };

    struct iterator {
        iterators i_;

        bool operator!=(terminator const& a) const {
            return iterator_cmp(i_, a.t_, std::index_sequence_for<T...>{});
        }

        values operator*() const {
            return std::apply([](auto && ... args){
                return values(*args...);}, i_);
        }

        iterator& operator++() {std::apply([](auto && ... args){
            ((++args), ...); }, i_);
            return *this;
        }
    };

    iterator begin() {
        return {std::apply([](auto && ... args){
            return iterators(std::begin(args)...);
        }, c_)};
    }

    terminator end() {
        return {std::apply([](auto && ... args){
            return terminators(std::end(args)...);
        }, c_)};
    }
};

template<typename ... T>
inline auto zip(T && ... t) {
    return ZipN<T...> {std::forward<T>(t)...};
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

template<class T>
inline auto enumerate(T && a) {
    return Enumerate<T>(std::forward<T>(a));
}

template<typename Int = int>
struct counter {
    Int c_ = 0;
    auto begin() {return counter{0};}
    auto end() {return counter{};}
    auto operator*() const {return c_;}
    void operator++() {++c_; }
    bool operator!=(counter) const {return true;}
};

template<typename ... T>
inline auto enumerate(T && ... t) {
    return ZipN<counter<>, T...> {{}, std::forward<T>(t)...};
}


} // end of namespace