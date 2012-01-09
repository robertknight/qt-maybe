#pragma once

#include <QtCore/QObject>

class TestMaybe : public QObject
{
	Q_OBJECT

	private Q_SLOTS:

		// Maybe
		void testMaybe();
		void testMaybeCast();
		void testMaybePtr();
		void testMaybeSize();

		// Either
		void testEither();

};
