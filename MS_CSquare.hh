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
    void fnSetNeighborhoodInfos(CSquare** poNeighborhood);
    bool fnIsBomb()const;
    bool fnIsRevealed()const;
    bool fnIsFlagged()const;
    bool fnIsQuestionMarked()const;
    void fnfreeze();
    void fnDistantTry();

private slots:
    void fnTry();
    void fnFlag();

signals:
    void SigExplosion();
    void SigFlagged();
    void SigUnFlagged();
    void SigRevealed();

private:
    void fnRevealAndDistantSearch();
    void fnColouringRevelation();
    void fnFinalColouringRevelation();

    uint32_t m_uiXPos;
    uint32_t m_uiYPos;
    bool m_bIsBomb;
    bool m_bIsRevealed;
    bool m_bIsFlagged;
    bool m_bIsQuestionMarked;
    uint32_t m_uiNbOfSurrondingBomb;
    CSquare* m_poNeighborhood[C_NB_OF_NEIGHBORS];

};

#endif // MS_CSQUARE_HH
