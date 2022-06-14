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

using local_limb_type = std::uint32_t;

constexpr std::int32_t local_wide_decimal_digits10 = INT32_C(51);

#if defined(WIDE_DECIMAL_NAMESPACE)
using local_wide_decimal_type = WIDE_DECIMAL_NAMESPACE::math::wide_decimal::decwide_t<local_wide_decimal_digits10, local_limb_type>;
#else
using local_wide_decimal_type = ::math::wide_decimal::decwide_t<local_wide_decimal_digits10, local_limb_type, void>;
#endif

std::uniform_int_distribution<std::uint32_t> dist_sgn    (UINT32_C(   0), UINT32_C(    1)); // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
std::uniform_int_distribution<std::uint32_t> dist_dig    (UINT32_C(0x31), UINT32_C( 0x39)); // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
std::uniform_int_distribution<std::uint32_t> dist_exp    (UINT32_C(   0), UINT32_C(10000)); // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
std::uniform_int_distribution<std::uint32_t> dist_exp_lim(UINT32_C(   0), UINT32_C(   65)); // NOLINT(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)

using eng_sgn_type = std::ranlux24;
using eng_dig_type = std::minstd_rand0;
using eng_exp_type = std::mt19937;

eng_sgn_type eng_sgn; // NOLINT(cert-msc32-c,cert-msc51-cpp,cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
eng_dig_type eng_dig; // NOLINT(cert-msc32-c,cert-msc51-cpp,cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)
eng_dig_type eng_exp; // NOLINT(cert-msc32-c,cert-msc51-cpp,cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables)

template<typename FloatingPointTypeWithStringConstruction>
auto generate_wide_decimal_value(bool is_positive     = false,
                                 bool exp_is_limited  = false,
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

  const auto val_exp = (exp_is_limited ? dist_exp_lim(eng_exp) : dist_exp(eng_exp));

  const auto sgn_exp = (dist_sgn(eng_sgn) != static_cast<std::uint32_t>(UINT32_C(0)));

  char pstr_exp[static_cast<std::size_t>(UINT8_C(32))] = { '\0' }; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)

  pstr_exp[static_cast<std::size_t>(UINT8_C(0))] = 'E';
  pstr_exp[static_cast<std::size_t>(UINT8_C(1))] = static_cast<char>(sgn_exp ? '-' : '+');

  const char* p_end = util::baselexical_cast(val_exp, &pstr_exp[2U]); // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)

  {
    for(auto p = static_cast<const char*>(pstr_exp); p != p_end; ++p) // NOLINT(llvm-qualified-auto,readability-qualified-auto)
    {
      const auto len = str_x.length();

      str_x.insert(len, static_cast<std::size_t>(1U), *p);
    }
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

  // Insert a decimal point.
  str_x.insert(static_cast<std::size_t>(1U), static_cast<std::size_t>(1U), '.');

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
  const auto local_zero                 = local_wide_decimal_type(0U);
  const auto local_zero_as_pow_to_raise = local_wide_decimal_type(0U);

  auto result_is_ok = true;

  const auto zero_raised_to_the_zero = pow(local_zero, local_zero_as_pow_to_raise);

  const auto result_zero_raised_to_the_zero = (zero_raised_to_the_zero == 1);

  result_is_ok = (result_zero_raised_to_the_zero && result_is_ok);

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(128));
           ++i)
  {
    const auto x          = generate_wide_decimal_value<local_wide_decimal_type>(true);
    const auto x_pow_zero = pow(x, local_zero);

    result_is_ok = ((x_pow_zero == 1) && result_is_ok);
  }

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(128));
           ++i)
  {
    const auto x          = generate_wide_decimal_value<local_wide_decimal_type>();
    const auto x_div_zero = x / local_zero;

    result_is_ok = ((x_div_zero == 0) && result_is_ok);
  }

  return result_is_ok;
}

auto test_various_one_operations() -> bool
{
  const auto local_one = local_wide_decimal_type(1U);

  auto result_is_ok = true;

  for(auto   i = static_cast<unsigned>(UINT32_C(0));
             i < static_cast<unsigned>(UINT32_C(128));
           ++i)
  {
    const auto x               = generate_wide_decimal_value<local_wide_decimal_type>();
    const auto x_div_one       = x /  local_one;
    const auto x_div_one_minus = x / -local_one;

    result_is_ok = ((x_div_one == x) && (x_div_one_minus == -x) && result_is_ok);
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
    const auto x = generate_wide_decimal_value<local_wide_decimal_type>(false, true);

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

} // namespace test_decwide_t_algebra_edge

#if defined(WIDE_DECIMAL_NAMESPACE)
auto WIDE_DECIMAL_NAMESPACE::test_decwide_t_algebra_edge____() -> bool // NOLINT(readability-identifier-naming,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
#else
auto test_decwide_t_algebra_edge____() -> bool // NOLINT(readability-identifier-naming,bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp)
#endif
{
  auto result_is_ok = true;

  result_is_ok = (test_decwide_t_algebra_edge::test_div_by_other_sign_same () && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_various_zero_operations() && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_various_one_operations () && result_is_ok);
  result_is_ok = (test_decwide_t_algebra_edge::test_string_round_tripping  () && result_is_ok);

  return result_is_ok;
}
