#ifndef OPTIONGUI_H
#define OPTIONGUI_H

#include <QDialog>

namespace Ui {
class optionGUI;
}

class optionGUI : public QDialog
{
    Q_OBJECT

public:
    explicit optionGUI(QWidget *parent = 0);
    ~optionGUI();

private:
    Ui::optionGUI *ui;
};

#endif // OPTIONGUI_H
