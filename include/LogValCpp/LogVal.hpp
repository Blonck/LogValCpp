#pragma once

#include <cmath>
#include <compare>
#include <concepts>
#include <cstdint>
#include <iostream>

// TODO need to add flag for negative numbers
// Remarks:
// * division with 0 will lead to nan, in contrast to doubles where it could be
// -inf, nan, inf depending on dividend
template <typename T = double>
    requires std::floating_point<T>
class LogVal {
   public:
    explicit LogVal(T val) {
        if (val > 0) {
            this->sign_ = Sign::positive;
            this->log_val_ = std::log(val);
        } else if (val < 0) {
            this->sign_ = Sign::negative;
            this->log_val_ = std::log(std::abs(val));
        } else {
            this->sign_ = Sign::null;
            // done on purpose for now
            this->log_val_ = std::log(val);
        }
    }

    /**
     * Converts this LogVal into `T` (default = `double`).
     *
     * @returns this LogVal as `T`.
     */
    template <typename ToType = T>
    [[nodiscard]] auto to() const noexcept -> ToType {
        return static_cast<ToType>(static_cast<T>(this->sign_) *
                                   std::exp(this->log_val_));
    }

    /**
     * Return internal representation of this LogVal as T (default = `double`)
     * without conversion.
     *
     * @returns this LogVal as is.
     */
    [[nodiscard]] auto as_is() const noexcept -> T {
        return static_cast<T>(this->sign_) * this->log_val_;
    }

    /**
     * Multiplies this LogVal with `rhs`.
     *
     * @param rhs factor with which this LogVal is multiplied with.
     *
     * @returns reference to this LogVal.
     */
    auto operator*=(const LogVal rhs) noexcept -> LogVal & {
        this->sign_ = as_sign(as_int(this->sign_) * as_int(rhs.sign_));
        this->log_val_ += rhs.log_val_;

        return *this;
    }

    auto operator/=(const LogVal rhs) noexcept -> LogVal & {
        // ignore division with 0.0 for now, log_val_ will be no-finite in this
        // case for now
        this->sign_ = as_sign(as_int(this->sign_) * as_int(rhs.sign_));
        this->log_val_ -= rhs.log_val_;

        return *this;
    }

    /**
     * Adds `rhs` to this LogVal.
     *
     * @param rhs summand added to this LogVal.
     *
     * @returns reference to this LogVal.
     */
    auto operator+=(const LogVal rhs) noexcept -> LogVal & {
        // Quick workaround until the following is adopted for negative LogVals
        // this->log_val_ += std::log1p(rhs_to/lhs_to);
        *this = LogVal(this->to() + rhs.to());

        return *this;
    }

    auto operator-=(const LogVal rhs) noexcept -> LogVal & {
        // Quick workaround until the following is adopted for negative LogVals
        // this->log_val_ += std::log(1.0 - rhs_to/lhs_to);
        // TODO remove using .to() as it undermines the idea of this class
        *this = LogVal(this->to() - rhs.to());

        return *this;
    }

    /**
     * Three-way comparison of this LogVal with \p rhs.
     *
     * @returns weak_ordering of the two LogVals.
     */
    [[nodiscard]] auto operator<=>(const LogVal rhs) const noexcept {
        // TODO: remove using .to() as it undermines the idea of this class
        return this->to() <=> rhs.to();
    }

    /**
     * Test if `rhs` is equal to this LogVal.
     *
     * @param rhs LogVal to compare with.
     *
     * @returns `true` if both LogVals are equal, else `false`.
     */
    [[nodiscard]] auto operator==(const LogVal rhs) const noexcept -> bool {
        return (this->sign_ == rhs.sign_) && (this->log_val_ == rhs.log_val_);
    }

    auto negate() noexcept -> LogVal & {
        this->sign_ = as_sign(-1 * as_int(this->sign_));
        return *this;
    }

    [[nodiscard]] auto operator-() const noexcept -> LogVal {
        return LogVal(*this).negate();
    }

    [[nodiscard]] auto operator+() const noexcept -> LogVal { return *this; }

    /**
     * Create LogVal from value which is already a logarithm
     *
     * @param log_val used directly for the internal representation of the
     * created LogVal.
     *
     * @returns a LogVal equivalent to `std::exp(log_val)`.
     */
    [[nodiscard]] static auto from_log(T log_val) noexcept -> LogVal {
        return LogVal(log_val, 1);
    }

   private:
    explicit LogVal(T log_val, int8_t sign) : log_val_(log_val), sign_(sign) {}

    enum class Sign : int8_t {
        positive = 1,
        negative = -1,
        null = 0,
    };

    [[nodiscard]] static auto as_int(Sign sign) -> int8_t {
        return static_cast<int8_t>(sign);
    }

    [[nodiscard]] static auto as_sign(int8_t integer) -> Sign {
        return static_cast<Sign>(integer);
    }

    T log_val_;
    Sign sign_;
};

/**
 * Multiplication of two LogVals.
 *
 * Multiplies two LogVals by using the identity:
 * \f[
 *   \log_b(xy) = \log_b(x) + \log_b(y)
 * \f]
 *
 * @param lhs left factor.
 * @param rhs right factor.
 *
 * @returns Product of `lhs` and `rhs`.
 */
template <typename T>
[[nodiscard]] auto operator*(LogVal<T> lhs, const LogVal<T> &rhs) noexcept
    -> LogVal<T> {
    return lhs *= rhs;
}

template <typename T>
[[nodiscard]] auto operator/(LogVal<T> lhs, const LogVal<T> &rhs) noexcept
    -> LogVal<T> {
    return lhs /= rhs;
}

template <typename T>
[[nodiscard]] auto operator+(LogVal<T> lhs, const LogVal<T> &rhs) noexcept
    -> LogVal<T> {
    return lhs += rhs;
}

template <typename T>
[[nodiscard]] auto operator-(LogVal<T> lhs, const LogVal<T> &rhs) noexcept
    -> LogVal<T> {
    return lhs -= rhs;
}

// only for debugging for now
template <typename T>
auto operator<<(std::ostream &os, const LogVal<T> &rhs) -> std::ostream & {
    os << "LogVal(" << rhs.as_is() << ")";
    return os;
}