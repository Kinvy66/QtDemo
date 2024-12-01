/******************************************************************************
 * File     : MainWindow.cpp
 * Brief    : 主窗口类
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2024-11-20
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    this->setWindowTitle(QString("Qt+ffmpeg视频播放（软解码）Demo V").arg(APP_VERSION));
    
    m_readThread = new ReadThread();
    connect(m_readThread, &ReadThread::updateImage, ui->widget, &PlayImage::updateImage, Qt::DirectConnection);
    connect(m_readThread, &ReadThread::playState, this, &MainWindow::on_playState);

    
    ui->comboBox_url->addItem("http://playertest.longtailvideo.com/adaptive/bipbop/gear4/prog_index.m3u8");
    ui->comboBox_url->addItem("http://vjs.zencdn.net/v/oceans.mp4");
    ui->comboBox_url->addItem("https://media.w3.org/2010/05/sintel/trailer.mp4");
    ui->comboBox_url->addItem("https://sf1-hscdn-tos.pstatp.com/obj/media-fe/xgplayer_doc_video/flv/xgplayer-demo-360p.flv");
}

MainWindow::~MainWindow()
{
    // 释放视频读取线程
    if (m_readThread)
    {
        m_readThread->close();
        m_readThread->wait();
        delete m_readThread;
    }
    delete ui;
}

/**
 * @brief 获取本地视频路径
 */
void MainWindow::on_pushButton_file_clicked()
{
    QString strName = QFileDialog::getOpenFileName(this, "选择播放视频~！", "/", "视频 (*.mp4 *.m4v *.mov *.avi *.flv);; 其它(*)");
    if (strName.isEmpty())
    {
        return;
    }
    ui->comboBox_url->addItem(strName);
    
    ui->comboBox_url->setCurrentText(strName);
}

/**
 * @brief  视频播放/停止
 */
void MainWindow::on_pushButton_start_clicked()
{
    if (ui->pushButton_start->text() == "开始播放")
    {
        m_readThread->open(ui->comboBox_url->currentText());
    }
    else
    {
        m_readThread->close();
    }
}

/**
 * @brief 视频暂停/继续
 */
void MainWindow::on_pushButton_pause_clicked()
{
    if (ui->pushButton_pause->text() == "暂停")
    {
        m_readThread->pause(true);
        ui->pushButton_pause->setText("继续");
    }
    else
    {
        m_readThread->pause(false);
        ui->pushButton_pause->setText("暂停");
    }
}


/**
 * @brief        根据视频播放状态切换界面设置
 * @param state
 */
void MainWindow::on_playState(ReadThread::PlayState state)
{
    if(state == ReadThread::play)
    {
        // this->setWindowTitle(QString("正在播放：%1").arg(m_readThread.at(0)->url()));
        ui->pushButton_pause->setText("停止播放");
    }
    else
    {
        ui->pushButton_file->setText("开始播放");
        ui->pushButton_pause->setText("暂停");
        // this->setWindowTitle(QString("Qt+ffmpeg视频播放（硬解码）Demo V%1").arg(APP_VERSION));
    }
}


