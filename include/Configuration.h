#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <qsharedpointer.h>

namespace Configuration
{
	static const quint64 WIDTH_MAIN_WINDOW			= 800;
	static const quint64 HEIGHT_MAIN_WINDOW			= 600;
	static const quint64 WIDTH_MATRIX_WINDOW		= 1240;
	static const quint64 HEIGHT_MATRIX_WINDOW		= 800;
	static const qreal WIDTH_VIEW					= 500;
	static const qreal HEIGHT_VIEW					= 400;

	static const QString PROJECT_NAME				= "UniGame";

	static const QString HOWTOPLAY					= ":/img/images/howtoplay.png";
	static const QString ABOUT						= ":/img/images/about.png";
	static const QString EXIT						= ":/img/images/exit.png";
	static const QString UNIGAME					= ":/img/images/unigame.png";

	static const QString AUDIO_MATRIX				= "qrc:/sounds/sounds/AUDIO_MATRIX.wav";
	static const QString AUDIO_PRESS_MOUSE_LEFT		= "qrc:/sounds/sounds/AUDIO_PRESS_MOUSE_LEFT.wav";
	static const QString AUDIO_HINT					= "qrc:/sounds/sounds/AUDIO_HINT.wav";

	static const QString STATISTIC_RESOURCE			= ":/statistic/statistic/statistic.csv";
	static const QString STATISTIC_PATH				= "/statistic.csv";
}

namespace Errors
{
	static const char* LOAD_ERROR					= "The statistics file cannot be opened. Fatal error!";
	static const char* SAVE_ERROR					= "The statistics file has been deleted. Saving is not possible!";
}

#endif
