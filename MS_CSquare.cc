#include "MS_CSquare.hh"
#include "MS_Traces.hh"
#include <string>

// Color configuration
QColor oColorRevealedBackground = QColor(255,255,255);

QColor poColorRevealedText[C_NB_OF_NEIGHBORS+1] =
{
    oColorRevealedBackground,  // 0
    QColor(0,0,200), //1
    QColor(0,200,0), //2
    QColor(200,0,0), //3
    QColor(0,0,80),  //4
    QColor(0,80,0),  //5
    QColor(80,0,0),  //6
    QColor(80,80,80),//7
    QColor(0,0,0),   //8

};

CSquare::CSquare(uint32_t uiXPos, uint32_t uiYPos, bool bIsBomb, uint32_t uiVerticalOffset, QWidget *parent): QPushButton(parent),
    m_uiXPos(uiXPos),
    m_uiYPos(uiYPos),
    m_bIsBomb(bIsBomb),
    m_bIsRevealed(false),
    m_uiNbOfSurrondingBomb(0)
{
    trace_debug("Construction of square [" << m_uiXPos << "][" << m_uiYPos << "]");
    for(int iI=0; iI < C_NB_OF_NEIGHBORS;iI++)
    {
        m_poNeighborhood[iI]=nullptr;
    }
    this->setGeometry( C_SIZE_SQUARE * m_uiXPos,
                       uiVerticalOffset + C_SIZE_SQUARE * m_uiYPos,
                       C_SIZE_SQUARE,
                       C_SIZE_SQUARE);

    // Proprieties of the button
    this->setBackgroundRole(QPalette::Button);
    this->setForegroundRole(QPalette::NoRole);
    this->setAutoFillBackground(true);
    this->setCursor(Qt::PointingHandCursor);

    QFont oFont;
    oFont = this->font();
    oFont.setBold(true);
    oFont.setPointSize(C_POINT_SIZE);
    this->setFont(oFont);

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(fnTry()));

    // using custom context menu button to flag : right click on Windows
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(fnFlag()));

}

void CSquare::fnSetNeighborhoodInfos(CSquare** poNeighborhood)
{
    m_uiNbOfSurrondingBomb = 0;
    for(int iI=0; iI < C_NB_OF_NEIGHBORS;iI++)
    {
        m_poNeighborhood[iI]=poNeighborhood[iI];
        if (poNeighborhood[iI] != nullptr)
        {
            if (m_poNeighborhood[iI]->fnIsBomb())
            {
                ++m_uiNbOfSurrondingBomb;
            }
        }

    }
}

bool CSquare::fnIsBomb()
{
    return m_bIsBomb;
}

bool CSquare::fnIsRevealed()
{
    return m_bIsRevealed;
}

void CSquare::fnTry()
{
    if (!m_bIsRevealed)
    {
        trace_debug("Trying [" << m_uiXPos << "][" << m_uiYPos << "]");
        if (m_bIsBomb)
        {
            QPalette oPalette;

            trace_debug("IT'S A BOMB");
            // colouring in red the bomb we tryed on
            this->setAutoFillBackground(true);
            this->setFlat(true);
            oPalette = this->palette();
            oPalette.setColor(QPalette::Button,Qt::red);
            this->setPalette(oPalette);
            fnColouringRevelation();
            emit SigExplosion();
        }
        else
        {
            fnRevealAndDistantSearch();
        }
    }
    else
    {
        trace_debug("Already revealed [" << m_uiXPos << "][" << m_uiYPos << "]");
    }
}

void CSquare::fnFlag()
{
    trace_info("Flagging [" << m_uiXPos << "][" << m_uiYPos << "]");
    emit SigFlagged();

    this->setText("F");
    this->show();
}

void CSquare::fnfreeze()
{
    // little trick: it won't try as it's reveal
    m_bIsRevealed = true;
    // Reveal all the bombs
    if (m_bIsBomb)
    {
        fnColouringRevelation();
    }
}
void CSquare::fnDistantTry()
{
    trace_debug("Distant Trying [" << m_uiXPos << "][" << m_uiYPos << "]");
    if (!m_bIsBomb)
    {
        // Reveal only if it's not a bomb
        fnRevealAndDistantSearch();
    }
}

void CSquare::fnRevealAndDistantSearch()
{
    // Revealing itself
    m_bIsRevealed= true;
    emit SigRevealed();
    trace_debug("Number of surronding bombs : " << m_uiNbOfSurrondingBomb);
    fnColouringRevelation();

    // Distant Searhing In neighboors if there is no surronding bomb
    if (!m_uiNbOfSurrondingBomb)
    {
        for(int iI=0; iI < C_NB_OF_NEIGHBORS;iI++)
        {
            if (m_poNeighborhood[iI]!= nullptr)
            {
                if ( !m_poNeighborhood[iI]->fnIsBomb() && !m_poNeighborhood[iI]->fnIsRevealed())
                {
                    m_poNeighborhood[iI]->fnDistantTry();
                }
            }
        }
    }
}

void CSquare::fnColouringRevelation()
{
    QPalette oPalette;
    QFont oFont;

    if (!m_bIsBomb)
    {
        //If it's not a bomb : show the number of surronding bombs
        this->setAutoFillBackground(true);
        this->setFlat(true);

        oPalette = this->palette();
        oPalette.setColor(QPalette::Button,oColorRevealedBackground);
        oPalette.setColor(QPalette::ButtonText,poColorRevealedText[m_uiNbOfSurrondingBomb]);
        this->setPalette(oPalette);

        this->setText(QString::number(m_uiNbOfSurrondingBomb));
    }
    else
    {
        // it's a bomb then
        this->setText("*");
    }

    this->show();
}
