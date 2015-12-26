#ifndef QT_MAYBE_H
#define QT_MAYBE_H

#include "Either.h"

/** A simple option type implementation which represents the result
  * of an operation which returned either a valid result or nothing.
  *
  * Maybe<T> is built on top of Either<T1,T2>, using one type to
  * hold the result (of type T) and the other to represent no result.
  *
  * Since Maybe<T> is built on Either<T1,T2>, it uses QVariant for the underlying
  * value storage and has the same size.
  *
  * Maybe<T> instances can be constructed using the just(T) and
  * nothing() helper functions.
  */
template <class T>
class Maybe
{
	public:
		/** Construct a Maybe<T> instance representing no
		  * value.
		  */
		Maybe()
		: m_value(false)
		{}

		/** Returns true if this Maybe<T> has a value. */
		operator bool() const {
			return m_value.template is<T>();
		}

		/** Returns the value from this Maybe<T>.  Asserts
		  * in debug builds if there is no value.
		  */
		T value() const {
			return m_value.template as<T>();
		}

		// helper method for the non-member just() function,
		// which external helpers should use instead
		template <class U>
		static Maybe<T> just(const U& value);

	private:
		// use the just() function to create a new
		// Maybe<T> instance with a value
		Maybe(const T& value)
		: m_value(value) 
		{}

		Either<bool,T> m_value;
};

template <class T>
template <class U>
Maybe<T> Maybe<T>::just(const U& value)
{
	return Maybe<T>(value);
}

// helper type used by nothing()
struct NothingType
{
	template <typename T>
	operator Maybe<T>() const {
		return Maybe<T>();
	}
};

// helper type used by just()
template <typename T>
struct JustType
{
	JustType(const T& _value)
	: value(_value)
	{}

	template <typename U>
	operator Maybe<U>() const {
		return Maybe<U>::just(value);
	}

	const T& value;
};

// helper type specialized for pointer types
template <typename T>
struct JustType<T*>
{
	JustType(T* _value)
	: value(_value)
	{}

	operator Maybe<T*>() const {
		// just(T*) returns a no-value Maybe if the pointer
		// is null
		return value ? Maybe<T*>::just(value) : Maybe<T*>();
	}

	T* value;
};

/** Returns a type which can be implicitly cast to any Maybe<T> type,
  * representing a function which returned no value.
  */
NothingType nothing()
{
	return NothingType();
}

/** Returns a type which can be implicitly cast to a Maybe<T> type
  * representing a function which did return a value of @p value.
  *
  * just() is specialized for pointer types to return nothing()
  * if the pointer is null.
  */
template <typename T>
JustType<T> just(const T& value) {
	return JustType<T>(value);
}

#endif
