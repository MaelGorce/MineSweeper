#include "MS_CMainwindow.hh"
#include "MS_CConfiguration.hh"
#include "MS_Traces.hh"


CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    trace_debug("Construction of MainWindow");

    trace_info("Size of the window = " << C_WINDOW_LENGTH << "x" << C_WINDOW_HIGHT );
    setFixedSize(C_WINDOW_LENGTH, C_WINDOW_HIGHT);

    m_poMenuBar = new CMenuBar(this);
    connect(m_poMenuBar,&CMenuBar::SigOutMenuBar,
            this,&CMainWindow::SfnInMenuBar);
    trace_debug("Hight of Menu Bar : " << m_poMenuBar->height());

    trace_debug("End Construction of MainWindow");
}

CMainWindow::~CMainWindow()
{
    trace_debug("Destruction of MainWindow");

    delete m_poMenuBar;

    trace_debug("End Destruction of MainWindow");
}

void CMainWindow::SfnInMenuBar(EMenuBarPossibility eInputMenuBar)
{
    switch (eInputMenuBar)
    {
        case ENewGame:
            trace_debug("New Game");
            break;
        case EPreferences:
            trace_debug("Preferences");
            break;
        case EHelp:
            trace_debug("Help");
            break;
        default:
            trace_debug("Case " << eInputMenuBar << " causes no action here");
    }
}
