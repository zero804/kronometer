/*
    Copyright (C) 2014 by Elvis Angelaccio <elvis.angelaccio@kde.org>

    This file is part of Kronometer.

    Kronometer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Kronometer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Kronometer.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "session.h"

#include <KXmlGuiWindow>

#include <QPointer>
#include <QTimer>

#include <memory>

class LapModel;
class SessionModel;
class Stopwatch;
class TimeDisplay;

class KToggleAction;

class QAction;
class QDBusInterface;
class QLabel;
class QSortFilterProxyModel;
class QSplitter;
class QTableView;
class QTextStream;
class QToolButton;

/**
 * @brief Kronometer main window.
 */
class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:

    explicit MainWindow(SessionModel *sessionModel, QWidget *parent = nullptr, const Session& session = Session {});
    virtual ~MainWindow();

    /**
     * @param title The title for this window.
     */
    void setWindowTitle(const QString& title);

protected:

    bool queryClose() override;

private slots:

    /**
     * Stopwatch running state triggers.
     */
    void slotRunning();

    /**
     * Stopwatch paused state triggers.
     */
    void slotPaused();

    /**
     * Stopwatch inactive state triggers.
     */
    void slotInactive();

    /**
     * Slot for the system bus PrepareForSleep signal.
     * @param beforeSleep Whether the signal has been emitted before suspension.
     */
    void slotPrepareForSleep(bool beforeSleep);

    /**
     * Setup the settings dialog.
     */
    void slotShowSettings();

    /**
     * Write the new settings on filesystem.
     */
    void slotWriteSettings();

    /**
     * Fix lap dock appereance.
     */
    void slotUpdateLapDock();

    /**
     * Open a new MainWindow instance.
     */
    void slotNewSession();

    /**
     * Open an existing session in a new MainWindow instance.
     */
    void slotOpenSession();

    /**
     * Save current times in the current session.
     */
    void slotSaveSession();

    /**
     * Save current times as a new session.
     */
    void slotSaveSessionAs();

    /**
     * Export current lap times on a file.
     */
    void slotExportLapsAs();

    /**
     * Copy current stopwatch time to clipboard.
     */
    void slotCopyToClipboard();

    /**
     * Toggle menubar visibility.
     */
    void slotToggleMenuBar();

    void slotUpdateControlMenu();

    void slotToolBarUpdated();

private:

    Stopwatch *m_stopwatch;
    TimeDisplay *m_stopwatchDisplay;
    QTableView *m_lapView;

    QAction *m_startAction;
    QAction *m_pauseAction;
    QAction *m_resetAction;
    QAction *m_lapAction;
    QAction *m_exportAction;
    std::unique_ptr<QTimer> m_controlMenuTimer;
    QPointer<QToolButton> m_controlMenuButton;
    KToggleAction *m_toggleMenuAction;

    LapModel *m_lapModel;
    SessionModel *m_sessionModel;

    Session m_session;

    QDBusInterface *m_screensaverInterface = nullptr;
    quint32 m_screenInhibitCookie = 0;

    /**
     * Setup the central widget of the window.
     */
    void setupCentralWidget();

    /**
     * Setup standard and custom QActions.
     */
    void setupActions();

    /**
     * Load settings from app Config and apply them to the other objects.
     */
    void loadSettings();

    /**
     * Set the stopwatch refresh granularity.
     */
    void setupGranularity();

    /**
     * Create a session with the current stopwatch time and lap times.
     * @param name The name of the session to be saved.
     */
    void saveSessionAs(const QString& name);

    /**
     * Load a saved session.
     */
    void loadSession();

    /**
     * Export current lap times on a new file.
     * @param name The name of the file to be created.
     * @param mimeType The mime type of the file to be created.
     */
    void exportLapsAs(const QString& name, const QString& mimeType);

    /**
     * Write the JSON laps representation on the given object.
     * @param json The JSON object to be written.
     */
    void exportLapsAsJson(QJsonObject& json);

    /**
     * Write the CSV laps representation on the given stream.
     * @param out The stream to be written.
     */
    void exportLapsAsCsv(QTextStream& out);

    /**
     * @return Whether there is a window size saved in the kronometer config.
     */
    bool isWindowSizeSaved() const;

    /**
     * A "comment" message with timestamp, to be used in the created files.
     * @return The string "Created by Kronomer on <timestamp>"
     */
    QString timestampMessage();

    void createControlMenuButton();

    void deleteControlMenuButton();

    /**
     * @return true if @p action has been added to @p menu;
     * false if @p action or @p menu is null, or if @p action
     * is already on the toolBar().
     */
    bool addActionToMenu(QAction* action, QMenu* menu);

    void activateScreenInhibition();

    void disactivateScreenInhibition();

    Q_DISABLE_COPY(MainWindow)
};


#endif
