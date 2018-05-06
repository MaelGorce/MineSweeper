#ifndef MS_CSQUARE_HH
#define MS_CSQUARE_HH

#include <QObject>
#include <QPushButton>
#include "MS_CConfiguration.hh"

#define C_NB_OF_NEIGHBORS 8

class CSquare: public QPushButton
{
    Q_OBJECT
public:
    CSquare(uint32_t uiXPos, uint32_t uiYPos, bool bIsBomb, uint32_t uiVerticalOffset, QWidget *parent);
    //static uint32_t s_uiFlagNumber=0;
    void fnSetNeighborhoodInfos(CSquare** poNeighborhood);
    bool fnIsBomb();
    bool fnIsRevealed();
    void fnDistantTry();

private slots:
    void fnTry();
    void fnFlag();

signals:
    void SigExplosion();

private:
    void fnRevealAndDistantSearch();
    void fnColouringRevelation();

    uint32_t m_uiXPos;
    uint32_t m_uiYPos;
    bool m_bIsBomb;
    bool m_bIsRevealed;
    uint32_t m_uiNbOfSurrondingBomb;
    CSquare* m_poNeighborhood[C_NB_OF_NEIGHBORS];

};

#endif // MS_CSQUARE_HH
