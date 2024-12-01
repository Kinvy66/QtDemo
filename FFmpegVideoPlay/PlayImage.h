/**
 * File     : PlayImage.h
 * Brief    : 图片绘制的方式视频播放控件
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2024-11-20
 * Version  : V0.0.1
 * Detail   : 参考：https://www.cnblogs.com/IntelligencePointer/p/17167922.html
 * Copyright: Copyright By Kinvy, All Rights Reserved
 */
#ifndef PLAYIMAGE_H
#define PLAYIMAGE_H

#include <QWidget>
#include <QMutex>

class PlayImage : public QWidget
{
    Q_OBJECT
public:
    explicit PlayImage(QWidget *parent = nullptr);
    
    void updateImage(const QImage& image);
    void updatePixmap(const QPixmap& pixmap);
    
signals:
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    QPixmap m_pixmap;
    QMutex m_mutex;
};

#endif // PLAYIMAGE_H
