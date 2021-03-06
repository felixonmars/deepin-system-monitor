#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
#include "dmainwindow.h"
#include "status_monitor.h"
#include "interactive_kill.h"
#include "process_manager.h"
#include "toolbar.h"
#include "event_monitor.h"
#include "ddialog.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(DMainWindow *parent = 0);
                                       
    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *, QEvent *);
    
public slots:
    void showWindowKiller();
    void responseEsc();
    void popupKillConfirmDialog(int pid);
    void dialogButtonClicked(int index, QString);
    
    void switchTab(int index);
    
private:
    ProcessManager *processManager;
    QHBoxLayout *layout;
    QWidget *layoutWidget;
    StatusMonitor *statusMonitor;
    Toolbar *toolbar;
    QMenu *menu;
    QAction *killAction;
    InteractiveKill *killer;
    EventMonitor eventMonitor;
    DDialog *killProcessDialog;
    
    int killPid;
};

#endif
