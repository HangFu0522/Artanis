#include "piecegui.h"
#include "ui_piecegui.h"

pieceGUI::pieceGUI(beadData *_bead,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pieceGUI)
{
    bead=_bead;
    ui->setupUi(this);
}

pieceGUI::~pieceGUI()
{
    delete ui;
}
