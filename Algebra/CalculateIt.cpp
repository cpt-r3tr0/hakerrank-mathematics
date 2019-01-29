#include <cmath>
#include <vector>
#include <iostream>
typedef unsigned __int128 uint128_t;
typedef std::vector<uint64_t> uint64_vec;
uint64_t const prime = 9223372036854775783;
uint64_t const ten18 = 1000000000000000000;
uint64_t const ten19 = ten18 * 10;

class binomials
{
public:
    explicit binomials(size_t size)
    {
        values_.reserve((size + 1) * (size + 2) / 2);
        values_.push_back(1);
        for (size_t i = 0, j = 0; i < size; ++i, ++j)
        {
            values_.push_back(1);
            for (size_t k = 0; k < i; ++j, ++k)
            {
                values_.push_back(values_[j] + values_[j + 1]);
            }
            values_.push_back(1);
        }
    }
    uint64_t operator()(size_t upper, size_t lower) const
    {
        return values_[upper * (upper + 1) / 2 + lower];
    }
private:
    uint64_vec values_;
};

class big_number
{
public:
    explicit big_number(uint64_t base)
    : base_(base)
    {
    }
    uint64_t base() const
    {
        return base_;
    }
    uint64_vec const& digits() const
    {
        return digits_;
    }
    void swap_digits(uint64_vec& digits)
    {
        digits_.swap(digits);
    }
    double approx() const
    {
        double result = 0;
        for (auto i = digits_.size(); i; )
            result = result * base_ + digits_[--i];
        return result;
    }
    void strip_zeros()
    {
        while (digits_.size() && !digits_.back())
            digits_.pop_back();
    }
    void grow(uint64_t scale, uint64_t delta)
    {
        for (auto& digit : digits_)
        {
            auto value = uint128_t(digit)
                * scale + delta;
            digit = uint64_t(value % base_);
            delta = uint64_t(value / base_);
        }
        if (delta) digits_.push_back(delta);
    }
private:
    uint64_vec digits_;
    uint64_t base_;
};

std::istream& operator>>(
    std::istream& stream, big_number& value)
{
    std::istream::sentry _(stream);
    auto const base = value.base();
    if (base > 10) return stream;
    uint64_t power = base;
    while (power < ten18) power *= base;
    big_number compound(power);
    uint64_t scale = 1, delta = 0;
    for (;;)
    {
        auto digit = unsigned(stream.get() - '0');
        if (digit > 9) break;
        if (scale == ten18)
        {
            compound.grow(scale, delta);
            scale = 1, delta = 0;
        }
        scale = scale * 10;
        delta = delta * 10 + digit;
    }
    compound.grow(scale, delta);
    uint64_vec digits;
    for (auto digit : compound.digits())
    for (auto rest = power; rest /= base; digit /= base)
        digits.push_back(digit % base);
    value.swap_digits(digits);
    value.strip_zeros();
    return stream;
}

std::ostream& operator<<(
    std::ostream& stream, big_number const& value)
{
    uint64_t divisor = ten19;
    auto digits = value.digits();
    if (digits.empty() || value.base() != divisor)
        return stream << '0';
    while (divisor > digits.back()) divisor /= 10;
    for (auto index = digits.size(); index; divisor = ten18)
    for (auto digit = digits[--index]; divisor; divisor /= 10)
        stream.put(char('0' + ((digit / divisor) % 10)));
    return stream;
}

template <class T = void> class adic;
template <class L, class R> class adic_add;
template <class L, class R> class adic_sub;
template <class T> class adic_mul;
template <class T> class adic_div;
class small;

template <class L, class R>
class adic< adic_add<L, R> >
{
public:
    adic(adic<L> const& lhs, adic<R> const& rhs)
    : lhs_(lhs), rhs_(rhs), carry_(false)
    {
    }
    uint64_t generate()
    {
        auto lhs = lhs_.generate();
        auto rhs = rhs_.generate()
            + (carry_ ? 1 : 0);
        auto result = lhs + rhs;
        if ((carry_ = (result >= prime)))
            result -= prime;
        return result;
    }
private:
    adic<L> lhs_;
    adic<R> rhs_;
    bool carry_;
};

template <class L, class R>
class adic< adic_sub<L, R> >
{
public:
    adic(adic<L> const& lhs, adic<R> const& rhs)
    : lhs_(lhs), rhs_(rhs), carry_(false)
    {
    }
    uint64_t generate()
    {
        auto lhs = lhs_.generate();
        auto rhs = rhs_.generate()
            + (carry_ ? 1 : 0);
        auto result = lhs - rhs;
        if ((carry_ = (lhs < rhs)))
            result += prime;
        return result;
    }
private:
    adic<L> lhs_;
    adic<R> rhs_;
    bool carry_;
};

template <class T>
class adic< adic_mul<T> >
{
public:
    adic(adic<T> const& arg, uint64_t factor)
    : arg_(arg), factor_(factor), remain_(0)
    {
    }
    uint64_t generate()
    {
        auto result = uint128_t(factor_)
            * arg_.generate() + remain_;
        remain_ = uint64_t(result / prime);
        return uint64_t(result % prime);
    }
private:
    adic<T> arg_;
    uint64_t factor_;
    uint64_t remain_;
};

template <class T>
class adic< adic_div<T> >
{
public:
    adic(adic<T> const& arg, uint64_t factor)
    : arg_(arg), factor_(factor), modinv_(1), remain_(0)
    {
        uint64_t u = prime, v = factor, w = 0;
        while (uint64_t r = u % v)
        {
            uint64_t q = u / v + 1, t = w;
            u = v; v -= r; w = modinv_;
            modinv_ = modinv_ * q - t;
        }
    }
    uint64_t generate()
    {
        auto result = arg_.generate();
        if (result < remain_) result += prime;
        result = uint64_t((uint128_t(modinv_)
            * (result -  remain_)) % prime);
        remain_ = uint64_t((uint128_t(result)
            * factor_ + remain_) / prime);
        return result;
    }
private:
    adic<T> arg_;
    uint64_t factor_;
    uint64_t modinv_;
    uint64_t remain_;
};

template <>
class adic<void>
{
public:
    explicit adic(uint64_t* ptr)
    : ptr_(ptr)
    {
    }
    uint64_t generate()
    {
        return *(ptr_++);
    }
protected:
    uint64_t* ptr_;
};

template <>
class adic<small>
{
public:
    explicit adic(uint64_t value)
    : value_(value)
    {
    }
    uint64_t generate()
    {
        auto result = value_;
        value_ = 0;
        return result;
    }
private:
    uint64_t value_;
};

template <class L, class R>
inline adic< adic_add<L, R> > operator+(
    adic<L> const& lhs, adic<R> const& rhs)
{
    return adic< adic_add<L, R> >(lhs, rhs);
}

template <class L, class R>
inline adic< adic_sub<L, R> > operator-(
    adic<L> const& lhs, adic<R> const& rhs)
{
    return adic< adic_sub<L, R> >(lhs, rhs);
}

template <class T>
inline adic< adic_mul<T> > operator*(
    adic<T> const& lhs, uint64_t rhs)
{
    return adic< adic_mul<T> >(lhs, rhs);
}

template <class T>
inline adic< adic_mul<T> > operator*(
    uint64_t lhs, adic<T> const& rhs)
{
    return adic< adic_mul<T> >(rhs, lhs);
}

template <class T>
inline adic< adic_div<T> > operator/(
    adic<T> const& lhs, uint64_t rhs)
{
    return adic< adic_div<T> >(lhs, rhs);
}

class adic_number : public adic<>
{
public:
    adic_number(uint64_t* ptr, size_t length)
    : adic<>(ptr), length_(length)
    {
    }
    void store(big_number& value) const
    {
        for (size_t i = length_; i--; )
            value.grow(prime, ptr_[i]);
        value.strip_zeros();
    }
    template <class T>
    adic_number& operator=(adic<T> rhs)
    {
        for (size_t i = 0; i < length_; ++i)
            ptr_[i] = rhs.generate();
        return *this;
    }
private:
    size_t length_;
};

class adic_vector
{
public:
    adic_vector(size_t count, size_t length)
    : data_(count * length), length_(length)
    {
    }
    adic_number operator()(size_t index)
    {
        return adic_number(data_.data()
            + index * length_, length_);
    }
private:
    uint64_vec data_;
    size_t length_;
};

int main()
{
    uint64_t base;
    std::cin >> base;
    big_number number(base);
    std::cin >> number;
    auto const& digits = number.digits();
    auto count = digits.size();
    if (count < 2)
    {
        std::cout << 1 << std::endl;
        return 0;
    }
    auto numlog = std::log(number.approx());
    size_t length = 1 + std::floor(numlog * numlog
        / (std::log(prime) * std::log(base) * 2));
    binomials binom(count);
    auto digit = digits[1];
    adic_vector cffs(count, length);
    cffs(0) = adic<small>(1);
    adic_vector bufs(count, length);
    bufs(0) = adic<small>(digit + 1);
    for (size_t d = 2; d < count; ++d)
    {
        for (size_t k = 0; ++k < d;)
        {
            adic_number buf(bufs(k));
            buf = adic<small>(0);
            for (size_t n = d; --n >= k;)
            {
                adic_number cff(cffs(n - 1));
                cff = cff * base;
                buf = buf * digit + cff * binom(n, k);
            }
        }
        for (size_t k = d; k--;)
        {
            adic_number cff(cffs(k));
            cff = adic<small>(0);
            for (size_t n = d; --n > k;)
            {
                cff = cffs(n) * binom(n + 1, k) - cff;
            }
            cff = (bufs(k) + cff) / (k + 1);
        }
        digit = digits[d];
        adic_number buf(bufs(1));
        buf = adic<small>(0);
        for (size_t k = d; k--;)
            buf = buf * digit + cffs(k);
        bufs(0) = buf * digit + bufs(0);
    }
    big_number answer(ten19);
    bufs(0).store(answer);
    std::cout << answer << std::endl;
    return 0;
}
