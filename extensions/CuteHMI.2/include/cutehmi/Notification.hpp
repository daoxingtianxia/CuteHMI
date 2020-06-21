#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_NOTIFICATION_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_NOTIFICATION_HPP

#include "internal/platform.hpp"
#include "ErrorInfo.hpp"
#include "MPtr.hpp"

#include <QObject>
#include <QDateTime>

namespace cutehmi {

/**
 * %Notification.
 *
 * Notifications are a mean to store information about events that occur to the system. Compared to logs they shall be more concise,
 * accessible and friendly in general. They belong to user space or power-user space rather than developer/expert space. Contrary to
 * log messages, notification messages shall be translatable. Compared to @ref Messages "messages" they are less intrusive and do
 * not require user action.
 *
 * %Notification objects are designed to work with Notifier and NotificationListModel classes.
 */
class CUTEHMI_API Notification:
	public QObject
{
		Q_OBJECT

	public:
		Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
		Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

		enum Type {
			INFO = 1,		///< Informative level notification type.
			WARNING = 2,	///< Warning level notification type.
			CRITICAL = 3	///< Critical level notification type.
		};
		Q_ENUM(Type)

		/**
		 * Default constructor.
		 * @param text notification text.
		 * @param type notification type.
		 * @param parent parent object.
		 */
		explicit Notification(const QString & text = QString(), Type type = INFO, QObject * parnt = nullptr);


		/**
		 * Constructor.
		 * @param type notification type.
		 * @param text notification text.
		 * @param parent parent object.
		 *
		 * @deprecated
		 */
		explicit Notification(Type type, const QString & text = QString(), QObject * parent = nullptr);

		/**
		 * Add informative notification. Convenient function that creates informative notification and adds it to the
		 * Notifier.
		 * @param text notification text.
		 */
		static void Info(const QString & text);

		/**
		 * Add warning notification. Convenient function that creates warning notification and adds it to the Notifier.
		 * @param text notification text.
		 */
		static void Warning(const QString & text);

		/**
		 * Add critical notification. Convenient function that creates critical notification and adds it to the Notifier.
		 * @param text notification text.
		 */
		static void Critical(const QString & text);

		/**
		 * Add critical notification. Convenient function that creates critical notification from ErrorInfo object and adds
		 * it to the Notifier.
		 * @param errorInfo ErrorInfo object.
		 */
		static void Critical(const ErrorInfo & errorInfo);

		/**
		 * Get type.
		 * @return notification type.
		 */
		Type type() const;

		/**
		 * Set type.
		 * @param type notification type.
		 */
		void setType(Type type);

		/**
		 * Get text.
		 * @return notification text.
		 */
		QString text() const;

		/**
		 * Set text.
		 * @param text notification text.
		 */
		void setText(const QString & text);

		/**
		 * Get date. Date is set automatically upon notification creation.
		 * @return date of notification.
		 */
		const QDateTime & dateTime() const;

		/**
		 * Cone notification.
		 * @return notification clone.
		 */
		std::unique_ptr<Notification> clone() const;

	signals:
		/**
		 * Type changed signal.
		 */
		void typeChanged();

		/**
		 * Text changed signal.
		 */
		void textChanged();

	private:
		struct Members
		{
			Type type;
			QString text;
			QDateTime dateTime;
		};

		MPtr<Members> m;
};

}

#endif

//(c)C: Copyright © 2018-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
