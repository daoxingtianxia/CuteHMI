#ifndef CUTEHMI_CUTEHMI__MODBUS__1__LIB_INCLUDE_MODBUS_INPUTREGISTER_HPP
#define CUTEHMI_CUTEHMI__MODBUS__1__LIB_INCLUDE_MODBUS_INPUTREGISTER_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QReadWriteLock>
#include <QVariant>
#include <QAtomicInt>

namespace cutehmi {
namespace modbus {

/**
 * Modbus input register.
 *
 * @note to make this class accessible from QML it must inherit after QObject,
 * thus keep in mind that this class is relatively heavy.
 */
class CUTEHMI_MODBUS_API InputRegister:
	public QObject
{
	Q_OBJECT

	public:
		enum encoding_t {
			INT16
		};
		Q_ENUM(encoding_t)

		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit InputRegister(uint16_t value = 0, QObject * parent = 0);

		Q_INVOKABLE QVariant value(encoding_t encoding = INT16) const;

		Q_INVOKABLE void rest();

		Q_INVOKABLE void awake();

		Q_INVOKABLE bool wakeful() const;

	public slots:
		/**
		 * Update value.
		 * @param value new value.
		 *
		 * @note this function is thread-safe.
		 */
		void updateValue(uint16_t value);

	signals:
		void valueUpdated();

	private:
		struct Members
		{
			uint16_t value;
			mutable QReadWriteLock valueLock;
			QAtomicInt awaken;

			Members(uint16_t p_value):
				value(p_value),
				awaken(0)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
