#ifndef PIECEGUI_H
#define PIECEGUI_H

#include <QWidget>
#include"GUI/piecegui.h"
#include"Base/base.h"
class beadData;
namespace Ui {
class pieceGUI;
}

class pieceGUI : public QWidget
{
    Q_OBJECT

public:
    explicit pieceGUI(beadData *_bead,QWidget *parent = 0);

    ~pieceGUI();

private:
    beadData* bead;
    std::vector<pieceData> vec_PieceData;
    Ui::pieceGUI *ui;
};

#endif // PIECEGUI_H
