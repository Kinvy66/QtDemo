/******************************************************************************
 * File     : MainWindow.h
 * Brief    : 主窗口类
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2024-11-20
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VideoPlay/ReadThread.h"

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
        
    void on_pushButton_file_clicked();
    
    void on_pushButton_start_clicked();
    
    void on_pushButton_pause_clicked();
    
    void on_playState(ReadThread::PlayState state);    
    
private:
    Ui::MainWindow *ui;
    
    ReadThread* m_readThread = nullptr;
};
#endif // MAINWINDOW_H
