#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widgets/keyboardnumeric/keyboardnumeric.h"
#include "widgets/keyboardfunctions/keyboardfunctions.h"
#include "widgets/pile/pile.h"
#include "widgets/commandline/commandline.h"
#include "widgets/variables/variables.h"
#include "widgets/programmes/programmes.h"

#include <QDebug>
#include <QDockWidget>
#include <QKeyEvent>
#include <QFileDialog>

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    pile = new Pile(this);
    commandline = new Commandline(this);
    keyboardfunctions = new KeyboardFunctions(this);
    programmes = new Programmes(this);
    variables = new Variables(this);
    keyboardnumeric = new KeyboardNumeric(this);
    editAtomDialog = new EditAtom(this);
    settings = new Settings(this);
    about = new About(this);
    saveW = new SaveWindow(this);

    connect(ui->a_keyboardnumeric, SIGNAL(toggled(bool)),keyboardnumeric,SLOT(toggleDock(bool)));
    connect(ui->a_keyboardfunctions, SIGNAL(toggled(bool)),keyboardfunctions,SLOT(toggleDock(bool)));
    connect(ui->a_programs, SIGNAL(toggled(bool)),programmes,SLOT(toggleDock(bool)));
    connect(ui->a_vars, SIGNAL(toggled(bool)),variables,SLOT(toggleDock(bool)));
    connect(ui->actionParametres, SIGNAL(triggered()), this, SLOT(openSettingsWindow()));
    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(openAboutWindow()));
    connect(ui->actionOuvrir, SIGNAL(triggered()), this, SLOT(loadFiles()));
    connect(ui->actionSauvegarder, SIGNAL(triggered()), this, SLOT(openSaveWindow()));
    ui->mainLayout->addWidget(pile);

    ui->mainLayout->addWidget(commandline);
    setFocusPolicy(Qt::StrongFocus);

}

Mainwindow::~Mainwindow()
{
    delete ui;
}


void Mainwindow::clickEval()
{
    notify("clickEval");
}

void Mainwindow::updateTabDocks()
{
    ui->a_keyboardfunctions->setChecked(!keyboardfunctions->getDock()->isHidden());
    ui->a_keyboardnumeric->setChecked(!keyboardnumeric->getDock()->isHidden());
    ui->a_programs->setChecked(!programmes->getDock()->isHidden());
    ui->a_vars->setChecked(!variables->getDock()->isHidden());
}

void Mainwindow::addToCommandline(const QString str)
{
    QString c = commandline->getText();

    if(!c.endsWith(" ",Qt::CaseInsensitive))
    {
        if(str.contains(QRegExp("[!=<>\\d.\' ]")))
            commandline->addText(str);
        else
            commandline->addText(" "+str+" ");
    }
    else if(!str.contains(QRegExp(" ")))
        commandline->addText(str);
    if(str.contains(QRegExp("[-*+/]$")))
    {
        notify("clickEval");
    }
}

void Mainwindow::keyPressEvent(QKeyEvent *ev) // Gestions des differentes touches
{
    QString text = ev->text();
    if(text.contains(QRegExp("^[A-Za-z]+$")))
        commandline->addText(text.toUpper());
    else if(text.contains(QRegExp("[!=<>-\\d*-+/.\[\\]']")))
        addToCommandline(text);
    else
    {
        switch(ev->key())
        {
            case Qt::Key_Return:
            case Qt::Key_Enter:
                notify("clickEval");
                break;
            case Qt::Key_Delete:
            case Qt::Key_Backspace:
                commandline->backspace();
                break;
            case Qt::Key_Space:
                addToCommandline(" ");
                break;
            default:
                break;
        }
        if(ev->matches(QKeySequence::Paste))
        {
            QClipboard *clip = QApplication::clipboard();
            addToCommandline(clip->text());
        }
    }
}



void Mainwindow::updateAtoms(const std::list<std::tuple<QString,QString,QString>> l)
{
    std::list<QString> vars;
    std::list<QString> progs;
    for(auto it = l.begin(); it!=l.end(); ++it)
    {
        if(std::get<2>(*it)!="Lprogram")
            vars.push_back(std::get<0>(*it));
        else
            progs.push_back(std::get<0>(*it));
    }
    vars.sort();
    progs.sort();
    variables->updateVars(vars);
    programmes->updateProgs(progs);
    saveW->updateAtoms(progs,vars);
}

void Mainwindow::execute(const QString a)
{
    buffer = a;
    notify("executeBuffer");
}

void Mainwindow::editAtom(const QString s)
{
    editAtomDialog->setAtomName(s);
    buffer = s;
    notify("needAtomValue");
    editAtomDialog->setAtomValue(buffer);
    editAtomDialog->show();
}
void Mainwindow::getAtomEditValueToSave()
{
    buffer = saveW->getBuffer();
    notify("needAtomValue");
    saveW->setBuffer(buffer);
}
void Mainwindow::openSettingsWindow()
{
    settings->setInputValue(pile->getSize());
    settings->show();
}
void Mainwindow::openAboutWindow()
{
    about->show();
}

void Mainwindow::openSaveWindow()
{
    saveW->show();
}
void Mainwindow::updateSizeStack(int s)
{
    pile->updateSize(s);
    notify("stackChanged");
}
void Mainwindow::loadFiles() // Permet de charger des fichiers
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Programs (*.txt *.comput)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if ( QDialog::Accepted == dialog.exec() )
    {
        QStringList filenames = dialog.selectedFiles();
        QStringList::const_iterator it = filenames.begin();
        QStringList::const_iterator eIt = filenames.end();
        while ( it != eIt )
        {
            QString fileName = *it++;
            if ( !fileName.isEmpty() )
            {
               QFile file(fileName);
               if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                   return;
               buffer = "";
               while (!file.atEnd()) {
                   QByteArray line = file.readLine();
                   buffer += " "+line.trimmed()+" ";
               }
               notify("executeBuffer");
            }
        }
    }
}
