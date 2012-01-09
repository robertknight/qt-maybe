#include "TestMaybe.h"

#include "Maybe.h"

#include <QtTest/QtTest>

Q_DECLARE_METATYPE(int*);

void TestMaybe::testMaybe()
{
	Maybe<int> tryOk = just(42);
	Maybe<int> tryFail = nothing();
	Maybe<int> tryZero = just(0);

	QVERIFY(tryOk);
	QVERIFY(!tryFail);
	QVERIFY(tryZero);
	QCOMPARE(tryZero.value(),0);
	QCOMPARE(tryOk.value(),42);
}

void TestMaybe::testMaybeCast()
{
	Maybe<QString> fromCStr = just("hello world");
	Maybe<QString> fromNothing = nothing();

	QVERIFY(!fromNothing);
	QCOMPARE(fromCStr.value(),QString("hello world"));

	Maybe<char> maybeShort = just(42);
	QVERIFY(maybeShort);
	QCOMPARE(maybeShort.value(),'*');
}

struct BigStruct
{
	double array[42];
};

void TestMaybe::testMaybeSize()
{
	Maybe<int> maybeInt;
	Maybe<double> maybeDouble;
	Maybe<int*> maybeIntPtr;
	Maybe<QString> maybeQString;
	Maybe<BigStruct> maybeBig;

	QCOMPARE(sizeof(maybeInt),12U);
	QCOMPARE(sizeof(maybeDouble),12U);
	QCOMPARE(sizeof(maybeIntPtr),12U);
	QCOMPARE(sizeof(maybeQString),12U);
	QCOMPARE(sizeof(maybeBig),12U);
}

void TestMaybe::testMaybePtr()
{
	int foo = 42;
	int* bar = 0;

	Maybe<int*> nullPtr = just(bar);
	Maybe<int*> nullPtr2 = nothing();
	Maybe<int*> notNullPtr = just(&foo);

	QVERIFY(!nullPtr);
	QVERIFY(!nullPtr2);
	QVERIFY(notNullPtr);
}

void TestMaybe::testEither()
{
	Either<int,bool> eitherInt = some(42);
	Either<int,bool> eitherBool = some(true);

	QVERIFY(eitherInt.is<int>());
	QVERIFY(eitherInt.is1st());
	QVERIFY(!eitherInt.is<bool>());
	QVERIFY(!eitherInt.is2nd());
	QCOMPARE(eitherInt.as<int>(),42);
	QCOMPARE(eitherInt.as1st(),42);

	QVERIFY(eitherBool.is<bool>());
	QVERIFY(eitherBool.is2nd());
	QVERIFY(!eitherBool.is<int>());
	QVERIFY(!eitherBool.is1st());
	QCOMPARE(eitherBool.as<bool>(),true);
	QCOMPARE(eitherBool.as2nd(),true);
}

QTEST_APPLESS_MAIN(TestMaybe)
