#include "../../include/cutehmi/Internationalizer.hpp"
#include "../../cutehmi.dirs.hpp"

#include <cutehmi/functions.hpp>

#include <QDir>
#include <QJsonArray>
#include <QLibraryInfo>

namespace cutehmi {

QString Internationalizer::uiLanguage() const
{
	return m->uiLanguage.name();
}

void Internationalizer::setUILanguage(const QString & uiLanguage)
{
	if (uiLanguage != m->uiLanguage.name()) {
		m->uiLanguage = QLocale(uiLanguage);
		CUTEHMI_DEBUG("Setting UI language to '" << uiLanguage << "'.");

		if (m->qtTranslator)
			updateQtTranslation(*m->qtTranslator);

		for (auto productTranslator = m->translators.begin(); productTranslator != m->translators.end(); ++productTranslator)
			updateTranslation(*productTranslator.value(), productTranslator.key(), translationDirectories());

		if (QCoreApplication::instance()) {
			QEvent event(QEvent::LanguageChange);
			QCoreApplication::sendEvent(QCoreApplication::instance(), & event);
		}

		emit uiLanguageChanged();
	}
}

void Internationalizer::loadQtTranslation()
{
	if (!m->qtTranslator) {
		m->qtTranslator = new QTranslator(this);
		updateQtTranslation(*m->qtTranslator);
		QCoreApplication::installTranslator(m->qtTranslator);
	} else
		CUTEHMI_WARNING("Qt translation already loaded.");
}

void Internationalizer::loadTranslation(const QString & product, bool dependencies)
{
	if (!m->translators.contains(product)) {
		QTranslator * translator = new QTranslator(this);
		m->translators.insert(product, translator);
		updateTranslation(*translator, product, translationDirectories());
		QCoreApplication::installTranslator(translator);
	} else
		CUTEHMI_DEBUG("Translation of product '" << product << "' already loaded.");

	if (dependencies) {
		QJsonArray dependenciesArray = metadata(product).value("dependencies").toArray();
		for (auto dependency : dependenciesArray) {
			QString dependencyName = dependency.toObject().value("name").toString();
			if (metadataExists(dependencyName))
				if (metadata(dependencyName).value("i18n").toBool())
					loadTranslation(dependencyName, dependencies);
		}
	}
}

QStringList Internationalizer::standardTranslationDirectories() const
{
	QStringList directories;
	QString translationsRelativeDir = QDir("/" CUTEHMI_DIRS_TOOLS_INSTALL_SUBDIR).relativeFilePath("/" CUTEHMI_DIRS_TRANSLATIONS_INSTALL_SUBDIR);
	directories << QDir::cleanPath(QDir::currentPath() + "/" + translationsRelativeDir);

	QStringList uiLanguages = m->uiLanguage.uiLanguages();
	uiLanguages.replaceInStrings("-", "_");

	if (!qEnvironmentVariable("LOCPATH").isEmpty())
		for (auto lang : uiLanguages)
			directories << qEnvironmentVariable("LOCPATH") + lang + "/LC_MESSAGES";

	QStringList xdgDirectories = qEnvironmentVariable("XDG_DATA_HOME").split(':', QString::SkipEmptyParts);
	if (qEnvironmentVariable("XDG_DATA_HOME").isEmpty())
		xdgDirectories << qEnvironmentVariable("HOME") + "/.local/share";
	xdgDirectories << qEnvironmentVariable("XDG_DATA_DIRS").split(':', QString::SkipEmptyParts);
	if (qEnvironmentVariable("XDG_DATA_DIRS").isEmpty())
		xdgDirectories << "/usr/local/share/" << "/usr/share/";
	for (auto directory : xdgDirectories)
		for (auto lang : uiLanguages)
			directories << directory + "/locale/" + lang + "/LC_MESSAGES";

	directories << QLibraryInfo::location(QLibraryInfo::TranslationsPath);

	return directories;
}

QStringList Internationalizer::additionalTranslationDirectories() const
{
	return m->additionalTranslationDirectories;
}

void Internationalizer::setAdditionalTranslationDirectories(const QStringList & additionalDirectories)
{
	m->additionalTranslationDirectories = additionalDirectories;
}

Internationalizer::Internationalizer(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

bool Internationalizer::updateTranslation(QTranslator & translator, const QString & product, const QStringList & directories)
{
	for (auto directory : directories) {
		if (translator.load(m->uiLanguage, translationFileStem(product), ".", directory)
				// Handle files with lanugage part after underscore as well (Qbs Qt.core module does not handle files with dot-separated subextensions before '.ts' part).
				|| translator.load(m->uiLanguage, translationFileStem(product), "_", directory, ".qm")
				// Handle files with "_qt.qm" suffix (KDE internationalization framework convention).
				|| translator.load(m->uiLanguage, translationFileStem(product), "_", directory, "_qt.qm")) {
			CUTEHMI_DEBUG("Translation of product '" << product << "' loaded from '" << directory << "' directory.");
			return true;
		}
	}
	CUTEHMI_WARNING("Translation of product '" << product << "' not found.");
	return false;
}

bool Internationalizer::updateQtTranslation(QTranslator & translator)
{
	if (translator.load(m->uiLanguage, "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
		CUTEHMI_DEBUG("Loaded Qt translation.");
		return true;
	}

	CUTEHMI_WARNING("Could not load Qt translation.");
	return false;
}

QString Internationalizer::translationFileStem(const QString & product)
{
	return product.toLower().replace('.', '-');
}

QStringList Internationalizer::translationDirectories() const
{
	return additionalTranslationDirectories() + standardTranslationDirectories();
}

}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
