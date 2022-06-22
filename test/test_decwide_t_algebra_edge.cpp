﻿///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <random>
#include <string>

#include <math/wide_decimal/decwide_t.h>
#include <test/test_decwide_t_algebra.h>
#include <util/utility/util_baselexical_cast.h>

namespace test_decwide_t_algebra_edge {

using local_limb_type = std::uint16_t;

constexpr std::int32_t local_wide_decimal_digits10 = INT32_C(51);

#if defined(WIDE_DECIMAL_NAMESPACE)
using local_wide_decimal_type = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<local_wide_decimal_digits10, local_limb_type, std::allocator<void>>;
#else
using local_wide_decimal_type = ::math::wide_decimal::decwide_t<local_wide_decimal_digits10, local_limb_type, std::allocator<void>>;
#endif

std::uniform_int_distribution<std::uint32_t> dist_sgn    (UINT32_C(   0), UINT32_C(    1)); // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
std::uniform_int_distribution<std::uint32_t> dist_dig    (UINT32_C(0x31), UINT32_C( 0x39)); // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)

using eng_sgn_type = std::ranlux24;
using eng_dig_type = std::minstd_rand0;
using eng_exp_type = std::mt19937;

eng_sgn_type eng_sgn; // NOLINT(cert-msc32-c,cert-msc51-cpp,cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
eng_dig_type eng_dig; // NOLINT(cert-msc32-c,cert-msc51-cpp,cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
eng_dig_type eng_exp; // NOLINT(cert-msc32-c,cert-msc51-cpp,cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)

auto local_zero    () -> const local_wide_decimal_type&;
auto local_one     () -> const local_wide_decimal_type&;
auto local_near_one() -> const local_wide_decimal_type&;
auto local_not_one () -> const local_wide_decimal_type&;

template<typename FloatingPointTypeWithStringConstruction>
auto generate_wide_decimal_value(bool is_positive     = false,
                                 int  exp_range       = 10000, // NOLINT(bugprone-easily-swappable-parameters)
                                 int  digits10_to_get = std::numeric_limits<FloatingPointTypeWithStringConstruction>::digits10 - 2) -> FloatingPointTypeWithStringConstruction
{
  using local_floating_point_type = FloatingPointTypeWithStringConstruction;

  static_assert(std::numeric_limits<local_floating_point_type>::digits10 > static_cast<int>(INT8_C(9)),
                "Error: Floating-point type destination does not have enough digits10");

  std::string str_x(static_cast<std::size_t>(digits10_to_get), '0');

  std::generate(str_x.begin(),
                str_x.end(),
                []() // NOLINT(modernize-use-trailing-return-type,-warnings-as-errors)
                {
                  return static_cast<char>(dist_dig(eng_dig));
                });

  if(exp_range != 0)
  {
    std::uniform_int_distribution<std::uint32_t>
      dist_exp
      (
        static_cast<std::uint32_t>(UINT32_C(0)),
        static_cast<std::uint32_t>(exp_range)
      );

    const auto val_exp = dist_exp(eng_exp);

    const auto sgn_exp = (dist_sgn(eng_sgn) != static_cast<std::uint32_t>(UINT32_C(0)));

    char pstr_exp[static_cast<std::size_t>(UINT8_C(32))] = { '\0' }; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)

    pstr_exp[static_cast<std::size_t>(UINT8_C(0))] = 'E';
    pstr_exp[static_cast<std::size_t>(UINT8_C(1))] = static_cast<char>(sgn_exp ? '-' : '+');

    {
      const char* p_end = util::baselexical_cast(val_exp, &pstr_exp[2U]); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)

      for(auto p = static_cast<const char*>(pstr_exp); p != p_end; ++p) // NOLINT(llvm-qualified-auto,readability-qualified-auto)
      {
        const auto len = str_x.length();

        str_x.insert(len, static_cast<std::size_t>(1U), *p);
      }
    }

    // Insert a decimal point.
    str_x.insert(static_cast<std::size_t>(1U), static_cast<std::size_t>(1U), '.');
  }

  // Insert either a positive sign or a negative sign
  // (always one or the other) depending on the sign of x.
  const auto sign_char_to_insert =
    static_cast<char>
    (
      is_positive
        ? '+'
        : static_cast<char>((dist_sgn(eng_sgn) != static_cast<std::uint32_t>(UINT32_C(0))) ? '+' : '-')
    );

  str_x.insert(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U), sign_char_to_insert);

  return local_floating_point_type(str_x.c_str());
}

auto test_div_by_other_sign_same() -> bool
{
  auto result_is_ok = true;

  eng_sgn.seed(static_cast<typename eng_sgn_type::result_type>(std::random_device{ }()));
  eng_dig.seed(static_cast<typename eng_dig_type::result_type>(std::random_device{ }()));

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(1024));
           ++i)
  {
    auto left = generate_wide_decimal_value<local_wide_decimal_type>();

    const local_wide_decimal_type right = -left;

    const local_wide_decimal_type result = left / right;

    const auto div_is_ok = (-result == 1);

    result_is_ok = (div_is_ok && result_is_ok);
  }

  return result_is_ok;
}

auto test_various_zero_operations() -> bool
{
  auto result_is_ok = true;

  {
    const auto pi_left =
      #if defined(WIDE_DECIMAL_NAMESPACE)
      WIDE_DECIMAL_NAMESPACE::math::wide_decimal::pi<local_wide_decimal_type::decwide_t_digits10, local_limb_type, std::allocator<void>>();
      #else
      ::math::wide_decimal::pi<local_wide_decimal_type::decwide_t_digits10, local_limb_type, std::allocator<void>>();
      #endif

    const auto pi_right =
      #if defined(WIDE_DECIMAL_NAMESPACE)
      WIDE_DECIMAL_NAMESPACE::math::wide_decimal::pi<local_wide_decimal_type::decwide_t_digits10, local_limb_type, std::allocator<void>>();
      #else
      ::math::wide_decimal::pi<local_wide_decimal_type::decwide_t_digits10, local_limb_type, std::allocator<void>>();
      #endif

    const auto result_of_sub_same_is_ok =
      (((pi_left - pi_right) == 0) && ((pi_left - pi_right) == local_zero()));

    result_is_ok = (result_of_sub_same_is_ok && result_is_ok);
  }

  {
    local_wide_decimal_type small =
      local_wide_decimal_type::from_lst
      (
        {
          static_cast<typename local_wide_decimal_type::limb_type>(1U)
        },
        static_cast<typename local_wide_decimal_type::exponent_type>
        (
          local_wide_decimal_type::decwide_t_min_exp10 + static_cast<std::int32_t>(INT8_C(32))
        )
      );

    auto result_underflow_is_ok = false;

    for(auto   i = static_cast<unsigned>(UINT8_C(0));
               i < static_cast<unsigned>(UINT8_C(200));
             ++i)
    {
      small /= static_cast<unsigned>(UINT8_C(7));

      if(   (small < (std::numeric_limits<local_wide_decimal_type>::min)())
         && (small == 0))
      {
        result_underflow_is_ok = true;

        break;
      }
    }

    result_is_ok = (result_underflow_is_ok && result_is_ok);
  }

  {
    using local_rep_type   = typename local_wide_decimal_type::representation_type;
    using local_value_type = typename local_rep_type::value_type;

    local_rep_type rep(local_rep_type::static_size(), (std::numeric_limits<local_value_type>::max)());

    rep.fill(static_cast<local_value_type>(0U));

    const auto result_zero_rep_is_ok = std::equal(rep.cbegin(), rep.cend(), local_zero().crepresentation().cbegin());

    result_is_ok = (result_zero_rep_is_ok && result_is_ok);
  }

  {
    const std::string str_zeros(static_cast<std::size_t>(33U), '0');

    const local_wide_decimal_type z(str_zeros.c_str());

    result_is_ok = ((z == local_zero()) && (z == 0) && result_is_ok);
  }

  {
    using std::exp;

    const auto exp_zero = exp(local_zero());

    const auto result_exp_zero_is_ok = (exp_zero == 1);

    result_is_ok = (result_exp_zero_is_ok && result_is_ok);
  }

  using std::pow;

  {
    const auto zero_raised_to_the_zero = pow(local_zero(), local_zero());

    const auto result_zero_raised_to_the_zero_is_ok = (zero_raised_to_the_zero == 1);

    result_is_ok = (result_zero_raised_to_the_zero_is_ok && result_is_ok);
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(128));
           ++i)
  {
    const auto x          = generate_wide_decimal_value<local_wide_decimal_type>(true);
    const auto x_pow_zero = pow(x, local_zero());

    result_is_ok = ((x_pow_zero == 1) && result_is_ok);
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(128));
           ++i)
  {
    const auto x              = generate_wide_decimal_value<local_wide_decimal_type>();
    const auto x_div_zero     = x / local_zero();
    const auto x_div_zero_ull = x / static_cast<unsigned long long>(local_zero()); // NOLINT(google-runtime-int)

    result_is_ok = ((x_div_zero == 0) && (x_div_zero_ull == 0) && result_is_ok);
  }

  return result_is_ok;
}

auto test_various_one_operations() -> bool
{
  auto result_is_ok = true;

  {
    const auto local_ten = local_wide_decimal_type(10U);

    for(auto u = static_cast<unsigned>(UINT8_C(1)); u < static_cast<unsigned>(UINT8_C(10)); ++u)
    {
      using std::ceil;

      const auto ceil_frac = ceil(local_wide_decimal_type(u) / local_ten);

      const auto result_ceil_frac_is_ok = (ceil_frac == local_one());

      result_is_ok = (result_ceil_frac_is_ok && result_is_ok);
    }
  }

  {
    using std::log;

    const auto log_one = log(local_one());

    const auto result_log_one_is_ok = (log_one == 0);

    result_is_ok = (result_log_one_is_ok && result_is_ok);
  }

  {
    std::stringstream strm;

    strm << local_near_one();

    const auto local_near_one_as_float = static_cast<float>(local_near_one());

    using std::fabs;

    const auto delta = fabs(1.0F - (local_near_one_as_float / 1.0F));

    const auto cast_local_near_one_to_float_is_ok = (delta < (std::numeric_limits<float>::epsilon() * 10.0F));

    result_is_ok = ((strm.str() == "1") && cast_local_near_one_to_float_is_ok && result_is_ok);
  }

  {
    std::stringstream strm;

    using std::ceil;

    strm << std::setprecision(std::numeric_limits<local_wide_decimal_type>::digits10)
         << ceil(local_near_one());

    const std::string str_one_from_strm = strm.str();

    result_is_ok = ((str_one_from_strm == "1") && result_is_ok);
  }

  {
    std::stringstream strm;

    strm << local_not_one();

    const auto local_not_one_as_float = static_cast<float>(local_not_one());

    using std::fabs;

    const auto delta = fabs(1.0F - (local_not_one_as_float / 0.9F));

    const auto cast_local_not_one_to_float_is_ok = (delta < (std::numeric_limits<float>::epsilon() * 10.0F));

    result_is_ok = ((strm.str() != "1") && cast_local_not_one_to_float_is_ok && result_is_ok);
  }

  {
    const auto one_div_near_one = local_one() / local_near_one();

    std::stringstream strm;

    strm << one_div_near_one;

    result_is_ok = ((strm.str() == "1") && result_is_ok);
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(128));
           ++i)
  {
    const auto x               = generate_wide_decimal_value<local_wide_decimal_type>();
    const auto x_div_one       = x /  local_one();
    const auto x_div_near_one  = x /  local_near_one();
    const auto x_div_one_minus = x / -local_one();

    result_is_ok = ((x_div_one == x) && (x_div_near_one == x) && (x_div_one_minus == -x) && result_is_ok);
  }

  return result_is_ok;
}

auto test_string_round_tripping() -> bool
{
  auto result_is_ok = true;

  const auto tol = local_wide_decimal_type(local_wide_decimal_type(1U) / 1000U);

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(8192));
           ++i)
  {
    const auto x =
      generate_wide_decimal_value<local_wide_decimal_type>
      (
        false,
        static_cast<int>(static_cast<float>(std::numeric_limits<double>::max_exponent10) * 0.65F)
      );

    {
      std::stringstream strm;

      // Use I/O streaming with no flags whatsoever.
      strm << x;

      using std::fabs;

      const auto delta = fabs(1 - fabs(x / local_wide_decimal_type(strm.str().c_str())));

      result_is_ok = ((delta < tol) && result_is_ok);
    }

    {
      std::stringstream strm;

      // Use I/O streaming with fixed flag only.
      strm << std::fixed << x;

      using std::fabs;

      const auto x_strm = local_wide_decimal_type(strm.str().c_str());

      const auto delta = fabs(1 - fabs(x / x_strm));

      result_is_ok = ((delta < tol) && result_is_ok);
    }

    {
      std::stringstream strm;

      // Use I/O streaming with scientific flag only.
      strm << std::scientific << x;

      using std::fabs;

      const auto delta = fabs(1 - fabs(x / local_wide_decimal_type(strm.str().c_str())));

      result_is_ok = ((delta < tol) && result_is_ok);
    }

    {
      std::stringstream strm;

      // Use I/O streaming with precision flags only.
      strm << std::setprecision(std::numeric_limits<local_wide_decimal_type>::max_digits10)
           << x;

      result_is_ok = ((x == local_wide_decimal_type(strm.str().c_str())) && result_is_ok);
    }

    {
      std::stringstream strm;

      // Use I/O streaming with precision and fixed flags combined.
      strm << std::setprecision(std::numeric_limits<local_wide_decimal_type>::max_digits10)
           << std::fixed
           << x;

      result_is_ok = ((x == local_wide_decimal_type(strm.str().c_str())) && result_is_ok);
    }

    {
      std::stringstream strm;

      // Use I/O streaming with precision and scientific flags combined.
      strm << std::setprecision(std::numeric_limits<local_wide_decimal_type>::max_digits10)
           << std::scientific
           << x;

      result_is_ok = ((x == local_wide_decimal_type(strm.str().c_str())) && result_is_ok);
    }

    {
      std::stringstream strm;

      // Use I/O streaming with precision and showpoint flags combined.
      strm << std::setprecision(std::numeric_limits<local_wide_decimal_type>::max_digits10)
           << std::showpoint
           << x;

      result_is_ok = ((x == local_wide_decimal_type(strm.str().c_str())) && result_is_ok);
    }
  }

  return result_is_ok;
}

template<typename NativeFloatType>
auto test_to_native_float_and_back() -> bool
{
  using native_float_type = NativeFloatType;

  static_assert(std::is_floating_point<native_float_type>::value,
                "Error: Invalid template floating-point parameter");

  auto result_is_ok = true;

  constexpr auto tol_factor =
    static_cast<long double>
    (
      (std::numeric_limits<native_float_type>::digits10 <=  6) ?  32.0L :
      (std::numeric_limits<native_float_type>::digits10 <= 15) ?  64.0L : 256.0L
    );

  const     auto tol1 = static_cast<local_wide_decimal_type>(static_cast<long double>(std::numeric_limits<native_float_type>::epsilon()) * tol_factor);
  constexpr auto tol2 = static_cast<native_float_type>      (static_cast<long double>(std::numeric_limits<native_float_type>::epsilon()) * tol_factor);

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(4096));
           ++i)
  {
    const auto x =
      generate_wide_decimal_value<local_wide_decimal_type>
      (
        false,
        static_cast<int>(static_cast<float>(std::numeric_limits<native_float_type>::max_exponent10) * 0.85F)
      );

    const auto x_as_native_float = static_cast<native_float_type>(x);

    const auto x_reloaded_from_native_float = local_wide_decimal_type(x_as_native_float);

    using std::fabs;

    const auto delta1 = fabs(local_one() - fabs(x / x_reloaded_from_native_float));
    const auto delta2 = fabs(static_cast<native_float_type>(1.0L) - fabs(x_as_native_float / static_cast<native_float_type>(x_reloaded_from_native_float)));

    result_is_ok = ((delta1 < tol1) && (delta2 < tol2) && result_is_ok);

    {
      std::stringstream strm;

      const auto prec_of_strm =
        (std::min)
        (
          std::numeric_limits<local_wide_decimal_type>::digits10,
          static_cast<int>(std::numeric_limits<long double>::digits10 + static_cast<int>(INT8_C(20)))
        );

      strm.precision(prec_of_strm);

      strm << std::scientific << x << 'L';

      auto x_as_long_double_from_strm = static_cast<long double>(0.0L);

      strm >> x_as_long_double_from_strm;

      const auto x_as_native_float_from_strm = static_cast<native_float_type>(x_as_long_double_from_strm);

      const auto delta3 = fabs(static_cast<native_float_type>(1.0L) - fabs(x_as_native_float / x_as_native_float_from_strm));

      const auto tol3 = tol2;

      result_is_ok = ((delta3 < tol3) && result_is_ok);
    }
  }

  return result_is_ok;
}

template<typename NativeUnsignedIntegralType>
auto test_various_int_operations() -> bool
{
  using local_unsigned_type = NativeUnsignedIntegralType;
  using local_signed_type   = typename std::make_signed<local_unsigned_type>::type;

  constexpr auto unsigned_integral_digits10_to_use =
    static_cast<unsigned>
    (
      std::numeric_limits<local_unsigned_type>::digits10 -1
    );

  const auto unsigned_integral_digits10_low_limit =
    static_cast<unsigned>
    (
      (std::max)
      (
        static_cast<unsigned>(UINT32_C(2)),
        static_cast<unsigned>(std::numeric_limits<std::uint8_t>::digits10)
      )
    );

  static_assert(   (std::numeric_limits<local_unsigned_type>::digits >= static_cast<int>(INT8_C(16)))
                && (unsigned_integral_digits10_to_use >= 3),
                "Error: Template integral type parameter is not wide enough");

  bool result_is_ok = true;

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(128));
           ++i)
  {
    for(auto   nd  = unsigned_integral_digits10_low_limit;
               nd <= unsigned_integral_digits10_to_use;
             ++nd)
    {
      const auto x =
        generate_wide_decimal_value<local_wide_decimal_type>
        (
          true,
          0,
          static_cast<int>(nd)
        );

      const auto u = static_cast<local_unsigned_type>(x);

      const auto result_native_convert_is_ok = (local_wide_decimal_type(u) == x);

      result_is_ok = (result_native_convert_is_ok && result_is_ok);
    }
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(128));
           ++i)
  {
    for(auto   nd  = unsigned_integral_digits10_low_limit;
               nd <= unsigned_integral_digits10_to_use;
             ++nd)
    {
      const auto x =
        generate_wide_decimal_value<local_wide_decimal_type>
        (
          false,
          0,
          static_cast<int>(nd)
        );

      const auto n = static_cast<local_signed_type>(x);

      const auto result_native_convert_is_ok = (local_wide_decimal_type(n) == x);

      result_is_ok = (result_native_convert_is_ok && result_is_ok);
    }
  }

  auto u10 = static_cast<local_unsigned_type>(UINT8_C(1));

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(std::numeric_limits<local_signed_type>::digits10);
           ++i)
  {
    const auto s10 = static_cast<local_signed_type>(-static_cast<local_signed_type>(u10));

    const auto x = local_wide_decimal_type(s10);

    const auto result_native_convert_is_ok =
      (static_cast<local_unsigned_type>(x) == static_cast<local_unsigned_type>(s10));

    result_is_ok = (result_native_convert_is_ok && result_is_ok);

    u10 = static_cast<local_unsigned_type>(u10 * static_cast<local_unsigned_type>(UINT8_C(10)));
  }

  return result_is_ok;
}

} // namespace test_decwide_t_algebra_edge

#if defined(WIDE_DECIMAL_NAMESPACE)
auto WIDE_DECIMAL_NAMESPACE::test_decwide_t_algebra_edge____() -> bool // NOLINT(readability-identifier-naming,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
#else
auto test_decwide_t_algebra_edge____() -> bool // NOLINT(readability-identifier-naming,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
#endif
{
  auto result_is_ok = true;

  result_is_ok = (test_decwide_t_algebra_edge::test_div_by_other_sign_same               () && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_various_zero_operations              () && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_various_one_operations               () && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_string_round_tripping                () && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_to_native_float_and_back<float>      () && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_to_native_float_and_back<double>     () && result_is_ok);
  #if (!defined(__APPLE__) && !defined(__MINGW32__))
  result_is_ok = (test_decwide_t_algebra_edge::test_to_native_float_and_back<long double>() && result_is_ok);
  #endif
  result_is_ok = (test_decwide_t_algebra_edge::test_various_int_operations<std::uint16_t>() && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_various_int_operations<std::uint32_t>() && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_various_int_operations<std::uint64_t>() && result_is_ok);

  return result_is_ok;
}

auto test_decwide_t_algebra_edge::local_zero    () -> const local_wide_decimal_type& { static const local_wide_decimal_type my_zero(0U); return my_zero; }
auto test_decwide_t_algebra_edge::local_one     () -> const local_wide_decimal_type& { static const local_wide_decimal_type my_one (1U); return my_one; }
auto test_decwide_t_algebra_edge::local_near_one() -> const local_wide_decimal_type& { static const local_wide_decimal_type my_near_one("0.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"); return my_near_one; }
auto test_decwide_t_algebra_edge::local_not_one () -> const local_wide_decimal_type& { static const local_wide_decimal_type my_not_one ("0.899999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"); return my_not_one; }