/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2006  Christophe Dumez
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Contact : chris@qbittorrent.org
 */

#ifndef SEARCH_H
#define SEARCH_H

#define TIME_TRAY_BALLOON 5000

#include <QProcess>
#include <QList>
#include "ui_search.h"
#include "engineSelectDlg.h"
#include "SearchTab.h"

class bittorrent;
class QSystemTrayIcon;
class downloadThread;
class QTimer;
class SearchEngine;

class SearchEngine : public QWidget, public Ui::search_engine{
  Q_OBJECT

  private:
    // Search related
    QHash<QString, QString> searchResultsUrls;
    QProcess *searchProcess;
    bool search_stopped;
    bool no_search_results;
    QByteArray search_result_line_truncated;
    unsigned long nb_search_results;
    QCompleter *searchCompleter;
    QStringList searchHistory;
    bittorrent *BTSession;
    QSystemTrayIcon *myTrayIcon;
    bool systrayIntegration;
    downloadThread *downloader;
    QStringList enabled_engines;
    QTimer *searchTimeout;
    SearchTab *tab_search;
  public:
    SearchEngine(bittorrent *BTSession, QSystemTrayIcon *myTrayIcon, bool systrayIntegration);
    ~SearchEngine();
    float getPluginVersion(QString filePath) const;
  public slots:
    void on_download_button_clicked();
    void downloadSelectedItem(const QModelIndex& index);
  protected slots:
    // Search slots
    void on_search_button_clicked();
    void on_stop_search_button_clicked();
    void on_clear_button_clicked();
    void appendSearchResult(QString line);
    void searchFinished(int exitcode,QProcess::ExitStatus);
    void readSearchOutput();
    void loadEngineSettings();
    void searchStarted();
    void startSearchHistory();
    void updateNova();
    void saveSearchHistory();
    void on_enginesButton_clicked();
    void on_clearPatternButton_clicked();
};

#endif
