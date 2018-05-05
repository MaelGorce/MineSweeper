#include "MS_CMainwindow.hh"
#include "MS_Traces.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    trace_info("********** Starting MineSweeper **********");
    QApplication oApplication(argc, argv);
    CMainWindow oMainWindow;
    trace_debug("Affichage de MainWindow");
    oMainWindow.show();

    return oApplication.exec();
}
