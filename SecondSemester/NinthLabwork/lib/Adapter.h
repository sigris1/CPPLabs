//
// Created by sigris on 23.03.2024.
//

#pragma once
#include "iostream"
#include "functional"

template<class Container>
concept IsContainer =
        requires (Container cont){
            cont.begin();
            cont.end();
        };

template<class Container>
concept IsBidirectional =
        requires (Container cont){
            cont.begin()++;
            cont.end()--;
        };

template<class Container>
concept IsAssociative =
    requires (Container cont){
        cont.begin()->first;
        cont.begin()->second;
    };

class reverse{
public:
    reverse()= default;
    template<class Container>
    Container DoCommand(Container cont){
        static_assert(IsContainer<Container>, "It isn't container");
        static_assert(IsBidirectional<Container>, "There isn't Bidirectional iterator");
        std::reverse(cont.begin(), cont.end());
        return cont;
    }
};

class take{
public:
    explicit take(int n) {
        count_ = n;
    }
    template<class Container>
    Container DoCommand(Container cont){
        static_assert(IsContainer<Container>, "It isn't container");
        Container returned(cont.begin(), (-count_) + cont.end());
        return cont;
    }
private:
    int count_;
};

class drop {
public:
    explicit drop(int n) {
        count_ = n;
    }
    template<class Container>
    Container DoCommand(Container cont){
        static_assert(IsContainer<Container>, "It isn't container");
        Container returned(count_ + cont.begin(), cont.end());
        return returned;
    }
private:
    int count_;
};

template<class T>
class filter{
public:
    explicit filter(std::function<bool(T)> operation){
        func_ = operation;
    }
    template<class Container>
    Container DoCommand(Container cont){
        static_assert(IsContainer<Container>, "It isn't container");
        Container returned(cont.begin(), cont.end());
        int current_size = returned.size();
        int corrected = 0;
        for (int i = 0; i < current_size; ++i){
            if (!func_(i)){
                returned.erase(i + returned.begin() - corrected + 1);
                corrected++;
            }
        }
        return returned;
    }
private:
    std::function<bool(T)> func_;
};

template<class T>
class transform{
public:
    explicit transform(std::function<T(T)> operation){
        func_ = operation;
    }
    template<class Container>
    Container DoCommand(Container cont){
        static_assert(IsContainer<Container>, "It isn't container");
        Container returned(cont.begin(), cont.end());
        for (T& i : returned){
            i = func_(i);
        }
        return returned;
    }
private:
    std::function<T(T)> func_;
};

class keys{
public:
    keys()= default;

    template<class Container>
    class ret{
    public:
        explicit ret(Container cont)
                : now_(cont)
        {}

        template<typename Iter>
        class Iterator {
        public:
            explicit Iterator(const Iter& iter) :
            iterator_(iter)
            {}
            Iterator& operator++() {
                ++iterator_;
                return *this;
            }
            Iterator& operator++(int) {
                ++iterator_;
                return *this;
            }
            Iterator& operator--() {
                --iterator_;
                return *this;
            }
            Iterator& operator--(int) {
                --iterator_;
                return *this;
            }
            auto operator*() {
                return std::get<0>(*iterator_);
            }
            bool operator==(const Iterator<Iter>& other) {
                return iterator_ == other.it_;
            }
            bool operator!=(const Iterator<Iter>& other) {
                return iterator_ != other.it_;
            }
        private:
            Iter iterator_;
        };

        Iterator<typename Container::iterator> begin(){
            return Iterator<typename Container::iterator>(now_.begin());
        };

        Iterator<typename Container::iterator> end(){
            return Iterator<typename Container::iterator>(now_.end());
        };

    private:
        Container now_;
    };

    template<class Container>
    auto DoCommand(Container cont){
        static_assert(IsContainer<Container>, "It isn't container");
        static_assert(IsAssociative<Container>, "It isn't associative container");
        return ret(cont);
    }
};

class values{
public:
    values()= default;

    template<class Container>
    class ret{
    public:
        explicit ret(Container cont)
                : now_(cont)
        {}

        template<typename Iter>
        class Iterator {
        public:
            explicit Iterator(const Iter& iter) :
                    iterator_(iter)
            {}
            Iterator& operator--() {
                --iterator_;
                return *this;
            }
            Iterator& operator--(int) {
                --iterator_;
                return *this;
            }
            Iterator& operator++() {
                ++iterator_;
                return *this;
            }
            Iterator& operator++(int) {
                ++iterator_;
                return *this;
            }
            auto operator*() {
                return std::get<1>(*iterator_);
            }
            bool operator==(const Iterator<Iter>& other) const {
                return iterator_ == other.it_;
            }
            bool operator!=(const Iterator<Iter>& other) const {
                return iterator_ != other.it_;
            }
        private:
            Iter iterator_;
        };

        Iterator<typename Container::iterator> begin(){
            return Iterator<typename Container::iterator>(now_.begin());
        };

        Iterator<typename Container::iterator> end(){
            return Iterator<typename Container::iterator>(now_.end());
        };

    private:
        Container now_;
    };

    template<class Container>
    auto DoCommand(Container cont){
        static_assert(IsContainer<Container>, "It isn't container");
        static_assert(IsAssociative<Container>, "It isn't associative container");
        return ret(cont);
    }
};

template<class Container, class Adapter>
auto operator|(Container cont, Adapter adap){
    auto returned = adap.DoCommand(cont);
    return returned;
}


