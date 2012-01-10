# Option/Sum Types for Qt Projects

A set of simple(ish) C++ templates which implement [sum](http://en.wikipedia.org/wiki/Sum_type) and [option](http://en.wikipedia.org/wiki/Option_type)
types.  They serve a similar purpose to `boost::variant` and `boost::optional`
but are implemented on top of Qt's QVariant container.

## Templates

### Either

`Either<T1,T2>` represents either a value of type `T1` or
a value of type `T2`.  You can think of it as a QVariant which is restricted
to being either a `T1` or `T2` rather than any type which QVariant supports.

`Either<T1,T2>` instances can be constructed directly from an instance
of `T1` or `T2` or by using the `some(T)` function which returns a type that
can be implicitly cast to any `Either` type that has `T` as one of its
types.

Simple example:

	// parse a value which might either be a
	// string or an integer

	Either<QString,int> value = parseValue(data);
	if (value.is1st()) {
		qDebug() << "Read string " << value.as1st();
	} else {
		qDebug() << "Read integer " << value.as2nd();
	}

### Maybe

`Maybe<T>` represents either a value of type T or no value.  You can think of it
as a QVariant which is restricted to either being a T or a null type.

`Maybe<T>` instances are constructed using the `just(T)` or `nothing()`
functions.

`just(T)` handles pointers specially.  If passed a null pointer it returns
a `Maybe` representing no value.  This is useful when working with existing code
which uses a null pointer to represent no value.

Simple example:

	// try to read the size of a file, which may fail if
	// the file is not readable

	Maybe<int> size = fileSize(path);
	if (size) {
		std::cout << "file size is " << size.value() << " bytes" << std::endl;
	} else {
		std::cout << "could not read file size" << std::endl;
	}

## Examples

See `TestMaybe.cpp` for unit tests which show example usage of the `Maybe` and
`Either` templates.

## Performance

The templates use `QVariant` as the underlying storage and the same performance considerations apply.  A QVariant in Qt 4 is 12 bytes in size on most platforms - 8 bytes for the data itself or a pointer to the data, plus 4 bytes for the type tag and flags.  Pointers and primitive types of 8 bytes in size or less are stored within the QVariant.  Larger types are stored in heap-allocated storage.

## Exceptions

Unlike `boost::variant`, no attempt is made to [handle exceptions](http://www.boost.org/doc/libs/1_48_0/doc/html/variant/design.html#variant.design.never-empty) that may be thrown when constructing or copying types.  The state of a `Maybe` or `Either` after a failed copy constructor call is undefined.
