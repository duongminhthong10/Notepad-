#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("");
}

bool open = false;
void MainWindow::on_actionOpen_triggered()
{   open=true;
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    file_path = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"..","File not Open");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    this->setWindowTitle(file_path);
    file.close();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste()
;}

bool luu=false;
void MainWindow::on_actionSave_triggered()
{
    luu=true;
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","File not Save");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    this->setWindowTitle(file_path);
    file.close();

}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name= QFileDialog::getSaveFileName(this,"Open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not Save");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    this->setWindowTitle(file_path);
    file.flush();
    file.close();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionAbout_notepad_triggered()
{
    QString about_text;
    about_text = "Anh Thong bat dau hoc\n";
    about_text += "Date  : 10/5/2021\n";
    about_text += "(C) Notepad";
    QMessageBox::about(this,"About",about_text);
}

bool tat=false;
bool saveas =false;
void MainWindow::on_actionExit_triggered()
{
if(open==true){

if(luu==true){
    if(QMessageBox::question(this,"Exit","Do you want Close")==QMessageBox::Yes)
    {
        tat=true;
        this->close();

   }
  }
else {

    if(QMessageBox::question(this,"Save","Ban co muon luu ko?")==QMessageBox::Yes){
        on_actionSave_triggered();
        this->close();
    }
    else{}

}
}
else
{
     this->close();
}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   if(tat== false){
    on_actionExit_triggered();
   }


}

