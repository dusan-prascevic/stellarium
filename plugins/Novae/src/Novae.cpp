/*
 * Copyright (C) 2013 Alexander Wolf
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#include "StelProjector.hpp"
#include "StelApp.hpp"
#include "StelCore.hpp"
#include "StelLocaleMgr.hpp"
#include "StelModuleMgr.hpp"
#include "StelObjectMgr.hpp"
#include "StelJsonParser.hpp"
#include "StelFileMgr.hpp"
#include "StelUtils.hpp"
#include "StelPainter.hpp"
#include "StelTranslator.hpp"
#include "StelTextureMgr.hpp"
#include "LabelMgr.hpp"
#include "Nova.hpp"
#include "Novae.hpp"
#include "NovaeDialog.hpp"
#include "StelProgressController.hpp"
#include "StarMgr.hpp"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QKeyEvent>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QList>
#include <QSettings>
#include <QSharedPointer>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>
#include <QDir>
#include <stdexcept>

#define CATALOG_FORMAT_VERSION 1 /* Version of format of catalog */

/*
 This method is the one called automatically by the StelModuleMgr just 
 after loading the dynamic library
*/
StelModule* NovaeStelPluginInterface::getStelModule() const
{
	return new Novae();
}

StelPluginInfo NovaeStelPluginInterface::getPluginInfo() const
{
	Q_INIT_RESOURCE(Novae);

	StelPluginInfo info;
	info.id = "Novae";
	info.displayedName = N_("Bright Novae");
	info.authors = "Alexander Wolf";
	info.contact = STELLARIUM_DEV_URL;
	info.description = N_("A plugin that shows some bright novae in the Milky Way galaxy.");
	info.version = NOVAE_PLUGIN_VERSION;
	info.license = NOVAE_PLUGIN_LICENSE;
	return info;
}

/*
 Constructor
*/
Novae::Novae()
	: NovaCnt(0)
	, texPointer(Q_NULLPTR)
	, updateState(CompleteNoUpdates)
	, networkManager(Q_NULLPTR)
	, downloadReply(Q_NULLPTR)
	, progressBar(Q_NULLPTR)
	, updateTimer(Q_NULLPTR)
	, updatesEnabled(false)
	, updateFrequencyDays(0)
{
	setObjectName("Novae");
	configDialog = new NovaeDialog();
	conf = StelApp::getInstance().getSettings();
	setFontSize(StelApp::getInstance().getScreenFontSize());
	connect(&StelApp::getInstance(), SIGNAL(screenFontSizeChanged(int)), this, SLOT(setFontSize(int)));
}

/*
 Destructor
*/
Novae::~Novae()
{
	delete configDialog;
}

/*
 Reimplementation of the getCallOrder method
*/
double Novae::getCallOrder(StelModuleActionName actionName) const
{
	if (actionName==StelModule::ActionDraw)
		return StelApp::getInstance().getModuleMgr().getModule("ConstellationMgr")->getCallOrder(actionName)+10.;
	return 0;
}


/*
 Init our module
*/
void Novae::init()
{
	try
	{
		StelFileMgr::makeSureDirExistsAndIsWritable(StelFileMgr::getUserDir()+"/modules/Novae");

		// If no settings in the main config file, create with defaults
		if (!conf->childGroups().contains("Novae"))
		{
			qDebug() << "[Novae] no Novae section exists in main config file - creating with defaults";
			restoreDefaultConfigIni();
		}

		// populate settings from main config file.
		readSettingsFromConfig();

		novaeJsonPath = StelFileMgr::findFile("modules/Novae", static_cast<StelFileMgr::Flags>(StelFileMgr::Directory|StelFileMgr::Writable)) + "/novae.json";
		if (novaeJsonPath.isEmpty())
			return;

		texPointer = StelApp::getInstance().getTextureManager().createTexture(StelFileMgr::getInstallationDir()+"/textures/pointeur2.png");
		addAction("actionShow_Novae_ConfigDialog", N_("Bright Novae"), N_("Bright Novae configuration window"), configDialog, "visible", ""); // Allow assign shortkey
	}
	catch (std::runtime_error &e)
	{
		qWarning() << "[Novae] init error:" << e.what();
		return;
	}

	// If the json file does not already exist, create it from the resource in the Qt resource
	if(QFileInfo::exists(novaeJsonPath))
	{
		if (!checkJsonFileFormat() || getJsonFileVersion()<CATALOG_FORMAT_VERSION)
		{
			restoreDefaultJsonFile();
		}
	}
	else
	{
		qInfo().noquote() << "[Novae] novae.json does not exist - copying default file to" << QDir::toNativeSeparators(novaeJsonPath);
		restoreDefaultJsonFile();
	}

	qInfo().noquote() << "[Novae] Loading catalog file:" << QDir::toNativeSeparators(novaeJsonPath);

	readJsonFile();

	// Set up download manager and the update schedule
	//networkManager = StelApp::getInstance().getNetworkAccessManager();
	networkManager = new QNetworkAccessManager(this);
	updateState = CompleteNoUpdates;
	updateTimer = new QTimer(this);
	updateTimer->setSingleShot(false);   // recurring check for update
	updateTimer->setInterval(13000);     // check once every 13 seconds to see if it is time for an update
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkForUpdate()));
	updateTimer->start();

	connect(this, SIGNAL(jsonUpdateComplete(void)), this, SLOT(reloadCatalog()));
	connect(StelApp::getInstance().getCore(), SIGNAL(configurationDataSaved()), this, SLOT(saveSettings()));
	StarMgr* smgr = GETSTELMODULE(StarMgr);
	connect(smgr, SIGNAL(starLabelsDisplayedChanged(bool)), this, SLOT(setFlagSyncShowLabels(bool)));

	GETSTELMODULE(StelObjectMgr)->registerStelObjectMgr(this);
}

/*
 Draw our module. This should print name of first Nova in the main window
*/
void Novae::draw(StelCore* core)
{
	StelProjectorP prj = core->getProjection(StelCore::FrameJ2000);
	StelPainter painter(prj);
	painter.setFont(font);
	
	for (const auto& n : std::as_const(nova))
	{
		if (n && n->initialized)
		{
			n->draw(core, &painter);
		}
	}

	if (GETSTELMODULE(StelObjectMgr)->getFlagSelectedObjectPointer())
	{
		drawPointer(core, painter);
	}
}

void Novae::drawPointer(StelCore* core, StelPainter &painter)
{
	const QList<StelObjectP> newSelected = GETSTELMODULE(StelObjectMgr)->getSelectedObject("Nova");
	if (!newSelected.empty())
	{
		const StelObjectP obj = newSelected[0];
		Vec3d pos=obj->getJ2000EquatorialPos(core);

		Vec3f screenpos;
		// Compute 2D pos and return if outside screen
		if (!painter.getProjector()->project(pos, screenpos))
			return;

		painter.setColor(obj->getInfoColor());
		texPointer->bind();
		painter.setBlending(true);
		painter.drawSprite2dMode(screenpos[0], screenpos[1], 13.f, StelApp::getInstance().getTotalRunTime()*40.);
	}
}

QList<StelObjectP> Novae::searchAround(const Vec3d& av, double limitFov, const StelCore*) const
{
	QList<StelObjectP> result;

	Vec3d v(av);
	v.normalize();
	const double cosLimFov = cos(limitFov * M_PI/180.);
	Vec3d equPos;

	for (const auto& n : nova)
	{
		if (n->initialized)
		{
			equPos = n->XYZ;
			equPos.normalize();
			if (equPos.dot(v) >= cosLimFov)
			{
				result.append(qSharedPointerCast<StelObject>(n));
			}
		}
	}

	return result;
}

StelObjectP Novae::searchByName(const QString& englishName) const
{
	for (const auto& n : nova)
	{
		if (n->getEnglishName().toUpper() == englishName.toUpper() || n->getDesignation().toUpper() == englishName.toUpper())
			return qSharedPointerCast<StelObject>(n);
	}

	return Q_NULLPTR;
}

StelObjectP Novae::searchByNameI18n(const QString& nameI18n) const
{
	for (const auto& n : nova)
	{
		if (n->getNameI18n().toUpper() == nameI18n.toUpper() || n->getDesignation().toUpper() == nameI18n.toUpper())
			return qSharedPointerCast<StelObject>(n);
	}

	return Q_NULLPTR;
}

QStringList Novae::listMatchingObjects(const QString& objPrefix, int maxNbItem, bool useStartOfWords) const
{
	QStringList result;
	if (maxNbItem <= 0)
		return result;

	QStringList names;
	for (const auto& n : nova)
	{
		names.append(n->getNameI18n());
		names.append(n->getEnglishName());
		names.append(n->getDesignation());
	}

	QString fullMatch = "";
	for (const auto& name : names)
	{
		if (!matchObjectName(name, objPrefix, useStartOfWords))
			continue;

		if (name==objPrefix)
			fullMatch = name;
		else
			result.append(name);

		if (result.size() >= maxNbItem)
			break;
	}

	result.sort();
	if (!fullMatch.isEmpty())
		result.prepend(fullMatch);
	return result;
}

QStringList Novae::listAllObjects(bool inEnglish) const
{
	QStringList result;
	if (inEnglish)
	{
		for (const auto& n : nova)
		{
			result << n->getEnglishName();
		}
	}
	else
	{
		for (const auto& n : nova)
		{
			result << n->getNameI18n();
		}
	}
	return result;
}

/*
  Replace the JSON file with the default from the compiled-in resource
*/
void Novae::restoreDefaultJsonFile(void)
{
    if (QFileInfo::exists(novaeJsonPath))
		backupJsonFile(true);

	QFile src(":/Novae/novae.json");
	if (!src.copy(novaeJsonPath))
	{
		qWarning() << "[Novae] cannot copy JSOIN resource to" + QDir::toNativeSeparators(novaeJsonPath);
	}
	else
	{
		qDebug() << "[Novae] copied default novae.json to" << QDir::toNativeSeparators(novaeJsonPath);
		// The resource is read only, and the new file inherits this...  make sure the new file
		// is writable by the Stellarium process so that updates can be done.
		QFile dest(novaeJsonPath);
		dest.setPermissions(dest.permissions() | QFile::WriteOwner);

		// Make sure that in the case where an online update has previously been done, but
		// the json file has been manually removed, that an update is schreduled in a timely
		// manner
		conf->remove("Novae/last_update");
		lastUpdate = QDateTime::fromString("2012-05-24T12:00:00", Qt::ISODate);
	}
}

/*
  Creates a backup of the novae.json file called novae.json.old
*/
bool Novae::backupJsonFile(bool deleteOriginal)
{
	QFile old(novaeJsonPath);
	if (!old.exists())
	{
		qWarning() << "[Novae] no file to backup";
		return false;
	}

	QString backupPath = novaeJsonPath + ".old";
	if (QFileInfo::exists(backupPath))
		QFile(backupPath).remove();

	if (old.copy(backupPath))
	{
		if (deleteOriginal)
		{
			if (!old.remove())
			{
				qWarning() << "[Novae] Could not remove old novae.json file";
				return false;
			}
		}
	}
	else
	{
		qWarning() << "[Novae] Failed to copy novae.json to novae.json.old";
		return false;
	}

	return true;
}

/*
  Read the JSON file and create list of novae.
*/
void Novae::readJsonFile(void)
{
	setNovaeMap(loadNovaeMap());
}

/*
  Parse JSON file and load novae to map
*/
QVariantMap Novae::loadNovaeMap(QString path)
{
	if (path.isEmpty())
	    path = novaeJsonPath;

	QVariantMap map;
	QFile jsonFile(path);
	if (!jsonFile.open(QIODevice::ReadOnly))
		qWarning() << "[Novae] cannot open" << QDir::toNativeSeparators(path);
	else
	{
		try
		{
			map = StelJsonParser::parse(jsonFile.readAll()).toMap();
			jsonFile.close();
		}
		catch (std::runtime_error &e)
		{
			qDebug() << "[Novae] File format is wrong! Error: " << e.what();
			return QVariantMap();
		}
	}
	return map;
}

/*
  Set items for list of struct from data map
*/
void Novae::setNovaeMap(const QVariantMap& map)
{
	nova.clear();
	novalist.clear();
	NovaCnt=0;
	QVariantMap novaeMap = map.value("nova").toMap();
	for (auto &novaeKey : novaeMap.keys())
	{
		QVariantMap novaeData = novaeMap.value(novaeKey).toMap();
		novaeData["designation"] = QString("%1").arg(novaeKey);

		novalist.insert(novaeData.value("name").toString(), novaeData.value("peakJD").toDouble());
		NovaCnt++;

		NovaP n(new Nova(novaeData));
		if (n->initialized)
			nova.append(n);
	}
}

int Novae::getJsonFileVersion(void) const
{	
	int jsonVersion = -1;
	QFile novaeJsonFile(novaeJsonPath);
	if (!novaeJsonFile.open(QIODevice::ReadOnly))
	{
		qWarning() << "[Novae] cannot open" << QDir::toNativeSeparators(novaeJsonPath);
		return jsonVersion;
	}

	QVariantMap map;
	try
	{
		map = StelJsonParser::parse(&novaeJsonFile).toMap();
		novaeJsonFile.close();
	}
	catch (std::runtime_error &e)
	{
		qDebug() << "[Novae] File format is wrong! Error: " << e.what();
		return jsonVersion;
	}
	if (map.contains("version"))
	{
		jsonVersion = map.value("version").toInt();
	}
	qInfo().noquote() << "[Novae] version of the catalog:" << jsonVersion;
	return jsonVersion;
}

bool Novae::checkJsonFileFormat() const
{
	QFile novaeJsonFile(novaeJsonPath);
	if (!novaeJsonFile.open(QIODevice::ReadOnly))
	{
		qWarning() << "[Novae] cannot open" << QDir::toNativeSeparators(novaeJsonPath);
		return false;
	}

	QVariantMap map;
	try
	{
		map = StelJsonParser::parse(&novaeJsonFile).toMap();
		novaeJsonFile.close();
	}
	catch (std::runtime_error& e)
	{
		qDebug() << "[Novae] file format is wrong! Error:" << e.what();
		return false;
	}

	return true;
}

NovaP Novae::getByID(const QString& id) const
{
	for (const auto& n : nova)
	{
		if (n->initialized && n->designation == id)
			return n;
	}
	return NovaP();
}

bool Novae::configureGui(bool show)
{
	if (show)
		configDialog->setVisible(true);
	return true;
}

void Novae::restoreDefaults(void)
{
	restoreDefaultConfigIni();
	restoreDefaultJsonFile();
	readJsonFile();
	readSettingsFromConfig();
}

void Novae::restoreDefaultConfigIni(void)
{
	conf->beginGroup("Novae");

	// delete all existing Novae settings...
	conf->remove("");

	conf->setValue("updates_enabled", true);
	conf->setValue("url", "https://stellarium.org/json/novae.json");
	conf->setValue("update_frequency_days", 100);
	conf->endGroup();
}

void Novae::readSettingsFromConfig(void)
{
	conf->beginGroup("Novae");

	updateUrl = conf->value("url", "https://stellarium.org/json/novae.json").toString();
	updateFrequencyDays = conf->value("update_frequency_days", 100).toInt();
	lastUpdate = QDateTime::fromString(conf->value("last_update", "2013-08-28T12:00:00").toString(), Qt::ISODate);
	updatesEnabled = conf->value("updates_enabled", true).toBool();

	conf->endGroup();
}

void Novae::saveSettingsToConfig(void)
{
	conf->beginGroup("Novae");

	conf->setValue("url", updateUrl);
	conf->setValue("update_frequency_days", updateFrequencyDays);
	conf->setValue("updates_enabled", updatesEnabled );

	conf->endGroup();
}

int Novae::getSecondsToUpdate(void)
{
	QDateTime nextUpdate = lastUpdate.addSecs(updateFrequencyDays * 3600 * 24);
	return static_cast<int>(QDateTime::currentDateTime().secsTo(nextUpdate));
}

void Novae::checkForUpdate(void)
{
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
	if (updatesEnabled && lastUpdate.addSecs(updateFrequencyDays * 3600 * 24) <= QDateTime::currentDateTime())
#else
	if (updatesEnabled && lastUpdate.addSecs(updateFrequencyDays * 3600 * 24) <= QDateTime::currentDateTime() && networkManager->networkAccessible()==QNetworkAccessManager::Accessible)
#endif
		updateJSON();
}

void Novae::updateJSON(void)
{
	if (updateState==Novae::Updating)
	{
		qWarning() << "[Novae] already updating...  will not start again current update is complete.";
		return;
	}

	qDebug() << "[Novae] Updating novae catalog...";
	startDownload(updateUrl);
}

void Novae::deleteDownloadProgressBar()
{
	disconnect(this, SLOT(updateDownloadProgress(qint64,qint64)));

	if (progressBar)
	{
		StelApp::getInstance().removeProgressBar(progressBar);
		progressBar = Q_NULLPTR;
	}
}

void Novae::startDownload(const QString &urlString)
{
	QUrl url(urlString);
	if (!url.isValid() || url.isRelative() || !url.scheme().startsWith("http", Qt::CaseInsensitive))
	{
		qWarning() << "[Novae] Invalid URL:" << urlString;
		return;
	}

	if (progressBar == Q_NULLPTR)
		progressBar = StelApp::getInstance().addProgressBar();
	progressBar->setValue(0);
	progressBar->setRange(0, 0);

	connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadComplete(QNetworkReply*)));
	QNetworkRequest request;
	request.setUrl(QUrl(updateUrl));
	request.setRawHeader("User-Agent", StelUtils::getUserAgentString().toUtf8());
#if (QT_VERSION<QT_VERSION_CHECK(6,0,0))
	request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, true);
#endif
	downloadReply = networkManager->get(request);
	connect(downloadReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDownloadProgress(qint64,qint64)));

	updateState = Novae::Updating;
	emit updateStateChanged(updateState);
}

void Novae::updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	if (progressBar == Q_NULLPTR)
		return;

	int currentValue = 0;
	int endValue = 0;

	if (bytesTotal > -1 && bytesReceived <= bytesTotal)
	{
		//Round to the greatest possible derived unit
		while (bytesTotal > 1024)
		{
			bytesReceived = static_cast<qint64>(std::floor(static_cast<double>(bytesReceived) / 1024.));
			bytesTotal    = static_cast<qint64>(std::floor(static_cast<double>(bytesTotal) / 1024.));
		}
		currentValue = static_cast<int>(bytesReceived);
		endValue = static_cast<int>(bytesTotal);
	}

	progressBar->setValue(currentValue);
	progressBar->setRange(0, endValue);
}

void Novae::downloadComplete(QNetworkReply *reply)
{
	if (reply == Q_NULLPTR)
		return;

	disconnect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadComplete(QNetworkReply*)));
	deleteDownloadProgressBar();

	if (reply->error() || reply->bytesAvailable()==0)
	{
		qWarning() << "[Novae] Download error: While trying to access"
			   << reply->url().toString()
			   << "the following error occurred:"
			   << reply->errorString();

		reply->deleteLater();
		downloadReply = Q_NULLPTR;
		return;
	}

	// download completed successfully.
	try
	{
		QString jsonFilePath = StelFileMgr::findFile("modules/Novae", StelFileMgr::Flags(StelFileMgr::Writable|StelFileMgr::Directory)) + "/novae.json";
		QFile jsonFile(jsonFilePath);
		if (jsonFile.exists())
			jsonFile.remove();

		if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			jsonFile.write(reply->readAll());
			jsonFile.close();
		}

		updateState = Novae::CompleteUpdates;

		lastUpdate = QDateTime::currentDateTime();
		conf->setValue("Novae/last_update", lastUpdate.toString(Qt::ISODate));
	}
	catch (std::runtime_error &e)
	{
		qWarning() << "[Novae] Cannot write JSON data to file:" << e.what();
		updateState = Novae::DownloadError;
	}

	emit updateStateChanged(updateState);
	emit jsonUpdateComplete();

	reply->deleteLater();
	downloadReply = Q_NULLPTR;

	qDebug() << "[Novae] Updating novae catalog is complete...";
	//readJsonFile();
}


void Novae::displayMessage(const QString& message, const QString &hexColor)
{
	messageIDs << GETSTELMODULE(LabelMgr)->labelScreen(message, 30, 30 + (20*messageIDs.count()), true, 16, hexColor, false, 9000);
}

QString Novae::getNovaeList()
{
	QStringList out;
	int year, month, day;
	QList<double> vals = novalist.values();
	std::sort(vals.begin(), vals.end());
	for (auto val : vals)
	{
		StelUtils::getDateFromJulianDay(val, &year, &month, &day);
		out << QString("%1 (%2 %3 %4)").arg(novalist.key(val)).arg(day).arg(StelLocaleMgr::longGenitiveMonthName(month)).arg(year);
	}

	return out.join(", ");
}

float Novae::getLowerLimitBrightness()
{
	float lowerLimit = 10.f;
	QFile novaeJsonFile(novaeJsonPath);
	if (!novaeJsonFile.open(QIODevice::ReadOnly))
	{
		qWarning() << "[Novae] cannot open" << QDir::toNativeSeparators(novaeJsonPath);
		return lowerLimit;
	}

	QVariantMap map;
	try
	{
		map = StelJsonParser::parse(&novaeJsonFile).toMap();
		novaeJsonFile.close();
	}
	catch (std::runtime_error &e)
	{
		qDebug() << "[Novae] File format is wrong! Error: " << e.what();
		return lowerLimit;
	}
	if (map.contains("limit"))
	{
		lowerLimit = map.value("limit").toFloat();
	}
	return lowerLimit;
}

void Novae::reloadCatalog(void)
{
	bool hasSelection = false;
	StelObjectMgr* objMgr = GETSTELMODULE(StelObjectMgr);
	// Whether any nova are selected? Save the current selection...
	const QList<StelObjectP> selectedObject = objMgr->getSelectedObject("Nova");
	if (!selectedObject.isEmpty())
	{
		// ... unselect current nova.
		hasSelection = true;
		objMgr->unSelect();
	}

	readJsonFile();

	if (hasSelection)
	{
		// Restore selection...
		StelObjectP obj = selectedObject[0];
		objMgr->findAndSelect(obj->getEnglishName(), obj->getType());
	}
}
