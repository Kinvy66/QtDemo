#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "./VideoPlay/readthread.h"
#include "../FFmpegVideoPlay/PlayImage.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    
private slots:
    void on_btn_file_clicked();
    
    void on_btn_open_clicked();
    
    void on_btn_pause_clicked();
    
    void on_playState(ReadThread::PlayState state);
    
private:
    Ui::MainWidget *ui;
    
    ReadThread* m_readThread = nullptr;
    QList<ReadThread*> m_readThreads;
    QList<PlayImage*>  m_playImages;
};
#endif // MAINWIDGET_H
