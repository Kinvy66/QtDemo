#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./VideoPlay/readthread.h"
#include "playimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_but_file_clicked();
    
    void on_but_open_clicked();
    
    void on_but_pause_clicked();
    
    void on_playState(ReadThread::PlayState state);
    
    void on_check_HW_clicked(bool checked);
    
private:
    Ui::MainWindow *ui;
    PlayImage* playImage = nullptr;
    ReadThread* m_readThread = nullptr;
};
#endif // MAINWINDOW_H
