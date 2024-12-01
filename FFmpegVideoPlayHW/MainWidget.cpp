#include "MainWidget.h"
#include "./ui_MainWidget.h"
#include "../FFmpegVideoPlay/PlayImage.h"

#include <QFileDialog>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    
    // this->setWindowTitle(QString("Qt+ffmpeg视频播放（硬解码）Demo V%1").arg(APP_VERSION));
    
    
    m_playImages.append(ui->playImage_1);
    m_playImages.append(ui->playImage_2);
    m_playImages.append(ui->playImage_3);
    m_playImages.append(ui->playImage_4);
    m_playImages.append(ui->playImage_5);
    m_playImages.append(ui->playImage_6);
    m_playImages.append(ui->playImage_7);
    m_playImages.append(ui->playImage_8);
    m_playImages.append(ui->playImage_9);
    for(int i = 0; i < m_playImages.count(); i++)
    {
        m_readThreads.append(new ReadThread);
        connect(m_readThreads.at(i), &ReadThread::updateImage, m_playImages.at(i), &PlayImage::updateImage);  // 这里使用Qt::DirectConnection会大幅度降低性能
    }
    connect(m_readThreads.at(0), &ReadThread::playState, this, &MainWidget::on_playState);
}

MainWidget::~MainWidget()
{
    // 释放视频读取线程
    for(int i = 0; i < m_readThreads.count(); i++)
    {
        m_readThreads.at(i)->close();
    }
    while (m_readThreads.count())
    {
        m_readThreads.at(0)->wait();
        m_readThreads.removeFirst();
    }
    delete ui;
}

/**
 * @brief 获取本地视频路径
 */
void MainWidget::on_btn_file_clicked()
{
    QString strName = QFileDialog::getOpenFileName(this, "选择播放视频~！", "/", "视频 (*.mp4 *.m4v *.mov *.avi *.flv);; 其它(*)");
    if(strName.isEmpty())
    {
        return;
    }
    ui->com_url->addItem(strName);
    ui->com_url->setCurrentText(strName);
}

/**
 * @brief  视频播放/停止
 */
void MainWidget::on_btn_open_clicked()
{
    if(ui->btn_open->text() == "开始播放")
    {
        for(int i = 0; i < m_readThreads.count(); i++)
        {
            m_readThreads.at(i)->setHWDecoder(ui->checkHW->isChecked());
            m_readThreads.at(i)->open(ui->com_url->currentText());
        }
    }
    else
    {
        for(int i = 0; i < m_readThreads.count(); i++)
        {
            m_readThreads.at(i)->close();
        }
    }  
}

/**
 * @brief 视频暂停/继续
 */
void MainWidget::on_btn_pause_clicked()
{
    if(ui->btn_pause->text() == "暂停")
    {
        for(int i = 0; i < m_readThreads.count(); i++)
        {
            m_readThreads.at(i)->pause(true);
        }
        ui->btn_pause->setText("继续");
    }
    else
    {
        for(int i = 0; i < m_readThreads.count(); i++)
        {
            m_readThreads.at(i)->pause(false);
        }
        ui->btn_pause->setText("暂停");
    }
    
}

/**
 * @brief        根据视频播放状态切换界面设置
 * @param state
 */
void MainWidget::on_playState(ReadThread::PlayState state)
{
    
    if(state == ReadThread::play)
    {
        this->setWindowTitle(QString("正在播放：%1").arg(m_readThreads.at(0)->url()));
        ui->btn_open->setText("停止播放");
    }
    else
    {
        ui->btn_open->setText("开始播放");
        ui->btn_pause->setText("暂停");
        // this->setWindowTitle(QString("Qt+ffmpeg视频播放（硬解码）Demo V%1").arg(APP_VERSION));
    }
}

