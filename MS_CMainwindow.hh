#ifndef MS_CMAINWINDOW_H
#define MS_CMAINWINDOW_H

#include <QMainWindow>
#include "MS_CMenubar.hh"
#include "MS_CSquare.hh"
#include "MS_CConfiguration.hh"
#include "MS_CInformationbar.hh"

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

public slots:
    void SlotInMenuBar(EMenuBarPossibility);
    void SlotStartingGame(QPoint QStart);
    void SlotGameLoss();
    void SlotRevelation();
    void SlotFlaggation();
    void SlotUnFlaggation();

signals:
    void SigSupposedMinesLeft(int32_t);
    void SigResetTimer(bool bStartTimer);
    void SigStopTimer();

private:
    void fnDeleteOldGrid();
    void fnCreateGrid();
    void fnSetSizeFromConfiguration();
    void fnRamdomBombImplant();
    void fnCheckWin();
    void fnWin();

    uint32_t m_uiRevealedSquares;
    uint32_t m_uiFlaggedSquares;
    CMenuBar* m_poMenuBar;
    uint32_t m_uiHightMenuBar;
    CInformationBar* m_poInfoBar;
    uint32_t m_uiHightInfoBar;
    CConfiguration* m_poConfiguration;
    CSquare* m_poGrid[C_MAX_SIZE_NUMBER][C_MAX_SIZE_NUMBER];
    bool m_pbBombGrid[C_MAX_SIZE_NUMBER][C_MAX_SIZE_NUMBER];

};

#endif // MS_CMAINWINDOW_H
