#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QMainWindow>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class KeyboardNumeric; }
QT_END_NAMESPACE

// Clavier numerique
class KeyboardNumeric : public QWidget
{
    Q_OBJECT

public:
    KeyboardNumeric(QMainWindow *parent = nullptr);
    ~KeyboardNumeric();
    QDockWidget* getDock() const {return dock;}

private:
    Ui::KeyboardNumeric *ui;
    QDockWidget* dock;
    QSignalMapper* signalMapper;

public slots:
    void toggleDock(bool b);
};

#endif // KEYBOARD
