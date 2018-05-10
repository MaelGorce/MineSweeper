#include "MS_CMainwindow.hh"
#include "MS_Traces.hh"
#include <QMessageBox>

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent,Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    trace_debug("Construction of MainWindow");

    m_poConfiguration = new CConfiguration();

    m_poMenuBar = new CMenuBar(this);
    connect(m_poMenuBar,&CMenuBar::SigOutMenuBar,
            this,&CMainWindow::SlotInMenuBar);
    m_uiHightMenuBar = m_poMenuBar->height();
    trace_debug("Hight of Menu Bar : " << m_uiHightMenuBar);

    fnSetSizeFromConfiguration();

    fnCreateGrid();

    trace_debug("End Construction of MainWindow");
}

CMainWindow::~CMainWindow()
{
    trace_debug("Destruction of MainWindow");

    fnDeleteOldGrid();
    delete m_poMenuBar;
    delete m_poConfiguration;


    trace_debug("End Destruction of MainWindow");
}

void CMainWindow::fnDeleteOldGrid()
{
    trace_debug("Deleting Old Grid");
    uint32_t uiNumberOfColumn = m_poConfiguration->fnGetNumberOfColumn();
    uint32_t uiNumberOfRow = m_poConfiguration->fnGetNumberOfRow();

    for(uint32_t iI=0; iI <uiNumberOfColumn;++iI)
    {
        for(uint32_t iJ=0; iJ <uiNumberOfRow;++iJ)
        {
            delete m_poGrid[iI][iJ];
        }
    }
}

void CMainWindow::fnCreateGrid()
{
    trace_debug("Creating Grid");

    fnRamdomBombImplant();

    uint32_t uiNumberOfColumn = m_poConfiguration->fnGetNumberOfColumn();
    uint32_t uiNumberOfRow = m_poConfiguration->fnGetNumberOfRow();

    for(uint32_t iI=0; iI <uiNumberOfColumn;++iI)
    {
        for(uint32_t iJ=0; iJ <uiNumberOfRow;++iJ)
        {
            m_poGrid[iI][iJ] = new CSquare(iI,iJ,m_pbBombGrid[iI][iJ],m_uiHightMenuBar,this);
            QObject::connect(m_poGrid[iI][iJ],&CSquare::SigExplosion,this,&CMainWindow::SlotGameLoss);
            QObject::connect(m_poGrid[iI][iJ],&CSquare::SigRevealed,this,&CMainWindow::SlotRevelation);
            QObject::connect(m_poGrid[iI][iJ],&CSquare::SigFlagged,this,&CMainWindow::SlotFlaggation);
        }
    }

    trace_debug("Neighbooring the Grid");

    CSquare* pCNeighboors[C_NB_OF_NEIGHBORS];
    int pucVoisCorrX[C_NB_OF_NEIGHBORS] = {-1,0,1,-1,1,-1,0,1};
    int pucVoisCorrY[C_NB_OF_NEIGHBORS] = {-1,-1,-1,0,0,1,1,1};

    trace_debug("Beginning of the neighbooring");
    for(int32_t iI=0; iI < (int)uiNumberOfColumn;++iI)
    {
        for(int32_t iJ=0; iJ < (int)uiNumberOfRow;++iJ)
        {
            for(int32_t iN=0; iN < C_NB_OF_NEIGHBORS;++iN)
                {
                    (iI+pucVoisCorrX[iN]>=0 &&                                                \
                     iI+pucVoisCorrX[iN]< (int)uiNumberOfColumn &&                            \
                     iJ+pucVoisCorrY[iN]>=0 &&                                                \
                     iJ+pucVoisCorrY[iN]< (int)uiNumberOfRow ) ?                              \
                     pCNeighboors[iN]=m_poGrid[iI+pucVoisCorrX[iN]][iJ+pucVoisCorrY[iN]] :    \
                     pCNeighboors[iN]=nullptr;
                }
            m_poGrid[iI][iJ]->fnSetNeighborhoodInfos(pCNeighboors);
        }
    }

    for(uint32_t iI=0; iI <uiNumberOfColumn;++iI)
    {
        for(uint32_t iJ=0; iJ <uiNumberOfRow;++iJ)
        {
            m_poGrid[iI][iJ]->show();
        }
    }

    m_uiRevealedSquares = 0;
    m_uiFlaggedSquares = 0;

    trace_debug("End of the grid creation");
}

void CMainWindow::fnRamdomBombImplant()
{
    uint32_t uiNumberOfColumn = m_poConfiguration->fnGetNumberOfColumn();
    uint32_t uiNumberOfRow = m_poConfiguration->fnGetNumberOfRow();
    uint32_t uiNumberOfMines = m_poConfiguration->fnGetNumberOfMines();
    uint32_t uiNumberOfImplantedMine = 0;
    uint32_t uiRandomrow,uiRandomColumn;

    // Cleaning the grid
    for(uint32_t iI=0; iI <uiNumberOfColumn;++iI)
    {
        for(uint32_t iJ=0; iJ <uiNumberOfRow;++iJ)
        {
            m_pbBombGrid[iI][iJ]=false;
        }
    }

    trace_debug("Implanting mines");
    srand(time(NULL));
    if (uiNumberOfMines > uiNumberOfColumn * uiNumberOfRow)
    {
        trace_error("More Mines than Squares ! wrong configuration");

    }
    else
    {
        while (uiNumberOfImplantedMine < uiNumberOfMines)
        {
            uiRandomColumn = (uint32_t)rand() % uiNumberOfColumn;
            uiRandomrow = (uint32_t)rand() % uiNumberOfRow;
            if (!m_pbBombGrid[uiRandomColumn][uiRandomrow])
            {
                m_pbBombGrid[uiRandomColumn][uiRandomrow] = true;
                ++uiNumberOfImplantedMine;
            }
        }
    }

}

void CMainWindow::fnSetSizeFromConfiguration()
{
    uint32_t uiNumberOfRow = m_poConfiguration->fnGetNumberOfRow();
    uint32_t uiNumberOfColumn = m_poConfiguration->fnGetNumberOfColumn();
    uint32_t uiLength = C_SIZE_SQUARE * uiNumberOfColumn;
    uint32_t uiHight = m_uiHightMenuBar + C_SIZE_SQUARE * uiNumberOfRow;
    trace_info("Size of the window = " << uiLength << "x" << uiHight );
    this->setFixedSize(uiLength, uiHight);
    m_poMenuBar->fnSetLength(uiLength);
}

void CMainWindow::SlotInMenuBar(EMenuBarPossibility eInputMenuBar)
{
    switch (eInputMenuBar)
    {
        case ENewGame:
            trace_info("New Game");
            fnDeleteOldGrid();
            fnCreateGrid();
            this->show();
            break;
        case EPreferences:
        {
        int iReturnedExec=0;
            trace_info("Preferences");
            iReturnedExec = m_poConfiguration->fnConfigure(this);
            if (QMessageBox::Apply == iReturnedExec)
            {
                fnDeleteOldGrid();
                m_poConfiguration->fnUpdateConfiguration();
                fnSetSizeFromConfiguration();
                fnCreateGrid();
                this->show();
            }
        }
            break;
        case EHelp:
        {
            trace_info("Help");
            const QString strHelpText =
"Quick Start:\n \
\n \
*\tYou are presented with a board of squares. Some squares contain mines (bombs), others don't.\n\
If you click on a square containing a bomb, you lose. If you manage to click all the squares (without clicking on any bombs) you win.\n\
*\tClicking a square which doesn't have a bomb reveals the number of neighbouring squares containing bombs.\n\
Use this information plus some guess work to avoid the bombs.\n\
*\tTo open a square, point at the square and click on it. To mark a square you think is a bomb, point and right-click.\n\
\n\
Detailed Instructions:\n\
\n\
A squares \"neighbours\" are the squares adjacent above, below, left, right, and all 4 diagonals.\n\
Squares on the sides of the board or in a corner have fewer neighbors. The board does not wrap around the edges.\n\
If you open a square with 0 neighboring bombs, all its neighbors will automatically open. This can cause a large area to automatically open.\n\
To remove a bomb marker from a square, point at it and right-click again.\n\
If you mark a bomb incorrectly, you will have to correct the mistake before you can win.\n\
Incorrect bomb marking doesn't kill you, but it can lead to mistakes which do.\n\
You don't have to mark all the bombs to win; you just need to open all non-bomb squares.\n";

            QMessageBox *poQMesgBox = new QMessageBox(QMessageBox::Information,
                                                      "Help",
                                                      strHelpText,
                                                      QMessageBox::Ok,
                                                      this);
            //poQMesgBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
poQMesgBox->setFixedWidth(100);
            poQMesgBox->exec();
            delete poQMesgBox;
        }
            break;
        default:
            trace_debug("Case " << eInputMenuBar << " causes no action here");
    }
}

void CMainWindow::SlotGameLoss()
{
    uint32_t uiNumberOfColumn = m_poConfiguration->fnGetNumberOfColumn();
    uint32_t uiNumberOfRow = m_poConfiguration->fnGetNumberOfRow();
    trace_info("Game lost");
    // Freeze the squares
    for(uint32_t iI=0; iI <uiNumberOfColumn;++iI)
    {
        for(uint32_t iJ=0; iJ <uiNumberOfRow;++iJ)
        {
            m_poGrid[iI][iJ]->fnfreeze();
        }
    }
}

void CMainWindow::SlotRevelation()
{
    ++m_uiRevealedSquares;
    trace_debug("Squares revealed : " << m_uiRevealedSquares);
    fnCheckWin();
}

void CMainWindow::SlotFlaggation()
{
    ++m_uiFlaggedSquares;
    trace_debug("Squares Flagged : " << m_uiFlaggedSquares);
    fnCheckWin();
}

void  CMainWindow::fnCheckWin()
{
    if(m_uiRevealedSquares == \
            (m_poConfiguration->fnGetNumberOfRow()*m_poConfiguration->fnGetNumberOfColumn()-m_poConfiguration->fnGetNumberOfMines()))
    {
        fnWin();
    }
}

void  CMainWindow::fnWin()
{
    uint32_t uiNumberOfColumn = m_poConfiguration->fnGetNumberOfColumn();
    uint32_t uiNumberOfRow = m_poConfiguration->fnGetNumberOfRow();
    trace_info("Game Won !");
    // Freeze the squares
    for(uint32_t iI=0; iI <uiNumberOfColumn;++iI)
    {
        for(uint32_t iJ=0; iJ <uiNumberOfRow;++iJ)
        {
            m_poGrid[iI][iJ]->fnfreeze();
        }
    }
}
