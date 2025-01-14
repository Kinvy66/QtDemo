#ifndef PLAYIMAGE_H
#define PLAYIMAGE_H

#include <QWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <qopenglshaderprogram.h>
#include <QOpenGLTexture>
#include <qopenglpixeltransferoptions.h>


struct AVFrame;

#define USE_WINDOW 0    // 1:使用QOpenGLWindow显示, 0：使用QOpenGLWidget显示

#if USE_WINDOW
#include <QOpenGLWindow>
class PlayImage : public QOpenGLWindow, public  QOpenGLFunctions_3_3_Core
#else
#include <QOpenGLWidget>
class PlayImage : public QOpenGLWidget, public  QOpenGLFunctions_3_3_Core
#endif
{
    Q_OBJECT
public:
#if USE_WINDOW
    explicit PlayImage(UpdateBehavior updateBehavior = NoPartialUpdate, QWindow *parent = nullptr);
#else
    explicit PlayImage(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
#endif
    ~PlayImage() override;
    
    void repaint(AVFrame* frame);             // 设置需要绘制的图像帧
    
    
protected:
    void initializeGL() override;               // 初始化gl
    void resizeGL(int w, int h) override;       // 窗口尺寸变化
    void paintGL() override;                    // 刷新显示
    
private:
    // YUV420图像数据更新
    void repaintTexYUV420P(AVFrame* frame);
    void initTexYUV420P(AVFrame* frame);
    void freeTexYUV420P();
    // NV12图像数据更新
    void repaintTexNV12(AVFrame* frame);
    void initTexNV12(AVFrame* frame);
    void freeTexNV12();
    
private:
    QOpenGLShaderProgram* m_program = nullptr;
    QOpenGLTexture* m_texY = nullptr;
    QOpenGLTexture* m_texU = nullptr;
    QOpenGLTexture* m_texV = nullptr;
    QOpenGLTexture* m_texUV = nullptr;
    QOpenGLPixelTransferOptions m_options;
    
    GLuint VBO = 0;       // 顶点缓冲对象,负责将数据从内存放到缓存，一个VBO可以用于多个VAO
    GLuint VAO = 0;       // 顶点数组对象,任何随后的顶点属性调用都会储存在这个VAO中，一个VAO可以有多个VBO
    GLuint EBO = 0;       // 元素缓冲对象,它存储 OpenGL 用来决定要绘制哪些顶点的索引
    QSize  m_size;
    QSizeF  m_zoomSize;
    QPointF m_pos;
    int m_format;         // 像素格式
};

#endif // PLAYIMAGE_H
