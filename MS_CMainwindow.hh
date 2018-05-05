#ifndef MS_CMAINWINDOW_H
#define MS_CMAINWINDOW_H

#include <QMainWindow>
#include "MS_CMenubar.hh"

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

public slots:
    void SfnInMenuBar(EMenuBarPossibility);

private:
    CMenuBar* m_poMenuBar;
};

#endif // MS_CMAINWINDOW_H
