#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <qsharedpointer.h>

namespace Configuration {
static const quint64 WIDTH_MAIN_WINDOW			= 800;
static const quint64 HEIGHT_MAIN_WINDOW			= 600;
static const quint64 WIDTH_MATRIX_WINDOW		= 1240;
static const quint64 HEIGHT_MATRIX_WINDOW		= 800;
static const qreal WIDTH_VIEW					= 500;
static const qreal HEIGHT_VIEW					= 400;

static const QString ORGANIZATION               = "UnitedTimurCompany";
static const QString PROJECT_NAME				= "UniGame";

static const QString HOWTOPLAY					= ":/img/images/howtoplay.png";
static const QString ABOUT						= ":/img/images/about.png";
static const QString EXIT						= ":/img/images/exit.png";
static const QString UNIGAME					= ":/img/images/unigame.png";

static const QString AUDIO_MATRIX				= "qrc:/sounds/sounds/AUDIO_MATRIX.wav";
static const QString AUDIO_PRESS_MOUSE_LEFT		= "qrc:/sounds/sounds/AUDIO_PRESS_MOUSE_LEFT.wav";
static const QString AUDIO_HINT					= "qrc:/sounds/sounds/AUDIO_HINT.wav";
static const QString LEVEL_WON                  = "qrc:/sounds/sounds/LEVEL_WON.wav";

static const QString STATISTIC_RESOURCE			= ":/statistic/statistic/statistic.csv";
static const QString STATISTIC_PATH				= "/statistic.csv";

static const QString BUTTON_FONT				= ":/fonts/fonts/font.otf";


static const QString START_BUTTON_STYLE_SHEET = "\
            QPushButton { "
                          "color: #8e9297; "
                          "background: #36393f; "
                          "border-radius: 20px; "
                          "border-style: outset; "
                          "border-width: 2px; "
                          "border-color: beige; "
                          "min-width: 10em; "
                          "padding: 10px; "
                          "font: 25px PerfoC; "
                          "}\
            QPushButton:hover { "
                                "color: #ffffff; "
                                "background: #393c43; "
                                "border-radius: 20px; "
                                "border-style: outset; "
                                "border-width: 2px; "
                                "border-color: #2ecc71; "
                                "min-width: 10em; "
                                "padding: 10px; "
                                "}\
            ";
}

        namespace Errors {
        static const char* LOAD_ERROR					= "The statistics file cannot be opened. Fatal error!";
        static const char* SAVE_ERROR					= "The statistics file has been deleted. Saving is not possible!";
}

        #endif
