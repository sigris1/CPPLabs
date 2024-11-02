//
// Created by sigris on 21.04.2024.
//

#pragma once

class my_any{
public:

    my_any() = default;

    template<class T>
    explicit my_any(const T& value)
            : now_(new type_<T>(value))
    {}

    my_any(const my_any& other)
            : now_(other.now_->getCopy())
    {}

    my_any(my_any&& other) = default;

    ~my_any(){
        delete now_;
    }

    template<class T>
    T Getval(){
        return dynamic_cast<type_<T>*>(now_)->value_;
    }

    class object_{
    public:
        virtual object_* getCopy() = 0;
        virtual ~object_() = default;
    };

    template<class T>
    class type_ : public object_{
    public:
        T value_;
        explicit type_(const T& value)
                : value_(value)
        {}
        object_* getCopy() override{
            return new type_(value_);
        }
    };

    object_* now_;
};
