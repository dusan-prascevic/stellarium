/*
 * Pointer Coordinates plug-in for Stellarium
 *
 * Copyright (C) 2014 Alexander Wolf
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef POINTERCOORDINATES_HPP
#define POINTERCOORDINATES_HPP

#include "StelGui.hpp"
#include "StelModule.hpp"

#include <QFont>
#include <QString>
#include <QPair>

class QPixmap;
class StelButton;
class PointerCoordinatesWindow;

/*! @defgroup pointerCoordinates Pointer Coordinates Plug-in
@{
The %Pointer Coordinates plugin shows the coordinates of the mouse pointer.

<b>Configuration</b>

The plug-ins' configuration data is stored in Stellarium's main configuration
file (section [PointerCoordinates]).

@}
*/

//! @class PointerCoordinates
//! Main class of the %Pointer Coordinates plugin.
//! @author Alexander Wolf
//! @ingroup pointerCoordinates
class PointerCoordinates : public StelModule
{
	Q_OBJECT
	Q_PROPERTY(bool enabled		READ isEnabled			WRITE enableCoordinates		NOTIFY flagCoordinatesVisibilityChanged)
	Q_PROPERTY(bool enableAtStartup READ getFlagEnableAtStartup	WRITE setFlagEnableAtStartup	NOTIFY flagEnableAtStartupChanged)
	Q_PROPERTY(bool showCoordinatesButton	READ getFlagShowCoordinatesButton	WRITE setFlagShowCoordinatesButton	NOTIFY flagShowCoordinatesButtonChanged)
	Q_PROPERTY(bool showConstellation	READ getFlagShowConstellation		WRITE setFlagShowConstellation		NOTIFY flagShowConstellationChanged)
	Q_PROPERTY(bool showCrossedLines	READ getFlagShowCrossedLines		WRITE setFlagShowCrossedLines		NOTIFY flagShowCrossedLinesChanged)
	Q_PROPERTY(bool showElongation	READ getFlagShowElongation	WRITE setFlagShowElongation	NOTIFY flagShowElongationChanged)
	Q_PROPERTY(int fontSize		READ getFontSize		WRITE setFontSize		NOTIFY fontSizeChanged)
	Q_PROPERTY(Vec3f fontColor	READ getFontColor		WRITE setFontColor		NOTIFY fontColorChanged)

public:
	//! @enum CoordinatesPlace
	//! Available places of string with coordinates
	enum CoordinatesPlace
	{
		TopCenter,		//!< The top center of the screen
		TopRight,		//!< In center of the top right half of the screen
		RightBottomCorner,	//!< The right bottom corner of the screen
		NearMouseCursor,	//!< Near mouse cursor
		Custom			//!< The custom position on the screen
	};
	Q_ENUM(CoordinatesPlace)

	//! @enum CoordinateSystem
	//! Available coordinate systems
	enum CoordinateSystem
	{
		RaDecJ2000,
		RaDec,
		HourAngle,
		Ecliptic,
		EclipticJ2000,
		AltAzi,
		Galactic,
		Supergalactic
	};
	Q_ENUM(CoordinateSystem)

	PointerCoordinates();
	~PointerCoordinates() override;

	void init() override;
	void draw(StelCore *core) override;
	double getCallOrder(StelModuleActionName actionName) const override;
	bool configureGui(bool show) override;

	//! Set up the plugin with default values.  This means clearing out the PointerCoordinates section in the
	//! main config.ini (if one already exists), and populating it with default values.
	void restoreDefaultConfiguration(void);

	//! Read (or re-read) settings from the main config file.  This will be called from init and also
	//! when restoring defaults (i.e. from the configuration dialog / restore defaults button).
	void loadConfiguration(void);

	//! Save the settings to the main configuration file.
	void saveConfiguration(void);

	//! Get font size for messages
	int getFontSize(void) { return fontSize; }

	//! Is plugin enabled?
	bool isEnabled() const { return flagShowCoordinates; }
	bool getFlagEnableAtStartup(void) { return flagEnableAtStartup;	}
	bool getFlagShowCoordinatesButton(void)	{ return flagShowCoordinatesButton; }
	bool getFlagShowCrossedLines(void) { return flagShowCrossedLines; }
	bool getFlagShowElongation(void) const { return flagShowElongation; }
	bool getFlagShowConstellation(void) const { return flagShowConstellation; }

	QPair<int, int> getCoordinatesPlace(const QString &text, int line = 1);
	QPair<int, int> getCustomCoordinatesPlace() { return customPosition; }

signals:
	void flagCoordinatesVisibilityChanged(bool b);
	void flagEnableAtStartupChanged(bool b);
	void flagShowCoordinatesButtonChanged(bool b);
	void flagShowConstellationChanged(bool b);
	void flagShowCrossedLinesChanged(bool b);
	void flagShowElongationChanged(bool b);
	void fontSizeChanged(int i);
	void fontColorChanged(Vec3f);

private slots:
	//! Call when button "Save settings" in main GUI are pressed
	void saveSettings() { saveConfiguration(); }

public slots:
	//! Enable plugin usage
	void enableCoordinates(bool b);
	//! Enable plugin usage at startup
	void setFlagEnableAtStartup(bool b) { flagEnableAtStartup=b; }
	//! Set font size for message
	void setFontSize(int size) { fontSize=size; }
	//! Display plugin button on toolbar
	void setFlagShowCoordinatesButton(bool b);

	void setFlagShowCrossedLines(bool b) { flagShowCrossedLines=b; }

	//! Set the current place of the string with coordinates
	void setCurrentCoordinatesPlace(PointerCoordinates::CoordinatesPlace place) { currentPlace = place; }
	//! Get the current place of the string with coordinates
	PointerCoordinates::CoordinatesPlace getCurrentCoordinatesPlace() const { return currentPlace; }
	//! Get the current place of the string with coordinates
	QString getCurrentCoordinatesPlaceKey(void) const;
	//! Set the current place of the string with coordinates from its key
	void setCurrentCoordinatesPlaceKey(const QString &key);

	//! Set the current coordinate system
	void setCurrentCoordinateSystem(PointerCoordinates::CoordinateSystem cs) { currentCoordinateSystem = cs; }
	//! Get the current coordinate system
	PointerCoordinates::CoordinateSystem getCurrentCoordinateSystem() const	{ return currentCoordinateSystem; }
	//! Get the current coordinate system key
	QString getCurrentCoordinateSystemKey(void) const;
	//! Set the current coordinate system from its key
	void setCurrentCoordinateSystemKey(const QString &key);

	void setCustomCoordinatesPlace(int x, int y);

	void setFlagShowConstellation(bool b){ flagShowConstellation=b; }
	void setFlagShowElongation(bool b){ flagShowElongation=b; }

	//! Get color for text
	//! @return color
	Vec3f getFontColor() const;
	//! Set color for text
	//! @param c color
	//! @code
	//! // example of usage in scripts (Qt6-based Stellarium)
	//! var c = new Color(1.0, 0.0, 0.0);
	//! PointerCoordinates.setFontColor(c.toVec3f());
	//! @endcode
	void setFontColor(const Vec3f& c);

private:
	PointerCoordinatesWindow* mainWindow;
	QSettings* conf;
	StelGui* gui;

	// The current place for string with coordinates
	CoordinatesPlace currentPlace;
	// The current coordinate system
	CoordinateSystem currentCoordinateSystem;

	QFont font;
	bool flagShowCoordinates;
	bool flagEnableAtStartup;
	bool flagShowCoordinatesButton;
	bool flagShowConstellation;
	bool flagShowCrossedLines;
	bool flagShowElongation;
	Vec3f textColor;
	Vec3d coordinatesPoint;
	int fontSize;
	StelButton* toolbarButton;
	QPair<int, int> customPosition;
};


#include <QObject>
#include "StelPluginInterface.hpp"

//! This class is used by Qt to manage a plug-in interface
class PointerCoordinatesStelPluginInterface : public QObject, public StelPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID StelPluginInterface_iid)
	Q_INTERFACES(StelPluginInterface)
public:
	StelModule* getStelModule() const override;
	StelPluginInfo getPluginInfo() const override;
	//QObjectList getExtensionList() const override { return QObjectList(); }
};

#endif /* POINTERCOORDINATES_HPP */
