// Simple helper file containing utility needed for this exercise: 
// signed to unsigned and vice versa, add/remove const, add/remove volatile.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>

template <typename T>
auto signed_conversion(T& t, std::false_type) {
	// Convert signed to unsigned.
	return std::make_signed_t<T>(t);
}

template <typename T>
auto signed_conversion(T& t, std::true_type) {
	// Convert unsigned to signed.
	return std::make_unsigned_t<T>(t);
}

template <typename T>
auto signed_conversion(T& t) {
	// Convert signed to unsigned if value is signed, else convert unsigned to signed.
	// Switchable bridge.
	return signed_conversion(t, std::is_signed<T>());
}

template<typename T>
auto const_specifier_conversion(T& t, std::false_type) {
	// Take variable t of type T and try to add the const specifier.
	// This doesn't seem to work. Can't create a constant from a non-constant in this manner.
	return std::as_const(t);
}

template<typename T>
auto const_specifier_conversion(T& t, std::true_type) {
	// Take variable t of type T and remove the const specifier.
	return std::remove_const_t<T>(t);
}

template<typename T>
auto const_specifier_conversion(T& t) {
	// Take variable t of type T and add or remove the const specifier.
	// Switchable bridge. 
	return const_specifier_conversion(t, std::is_const<T>());
}

template<typename T>
auto volatile_specifier_conversion(T& t, std::false_type) {
	// Take variable t of type T and add the volatile specifier.
	// This doesn't seem to work. Can't create a volatile from a non-volatile in this manner.
	return std::add_volatile_t<T>(t);
}

template<typename T>
auto volatile_specifier_conversion(T& t, std::true_type) {
	// Take variable t of type T and remove the volatile specifier.
	return std::remove_volatile_t<T>(t);
}

template<typename T>
auto volatile_specifier_conversion(T& t) {
	// Take variable t of type T and add or remove the const specifier.
	// Switchable bridge. 
	return volatile_specifier_conversion(t, std::is_volatile<T>());
}