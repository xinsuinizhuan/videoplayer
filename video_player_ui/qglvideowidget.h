#ifndef QGLVIDEOWIDGET_H
#define QGLVIDEOWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include "videoframe.h"
#include "video_player_core.h"

struct _texture_obj_{
    void init()
    {
        texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
        texture->create();
        id = texture->textureId();
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    QOpenGLTexture* texture;
    uint id;
};

class QGLVideoWidget : public QOpenGLWidget, public QOpenGLFunctions, public video_interface
{
    Q_OBJECT
    enum enum_pragram_attr_index
    {
        ATTR_VERTEX_IN = 0,
        ATTR_TEXTURE_IN,
    };

    enum enum_texture_index
    {
        TEXTURE_Y = 0,
        TEXTURE_U,
        TEXTURE_V,
        TEXTURE_IMG,

        TEXTURE_MAX
    };

public:
    QGLVideoWidget(QWidget *parent = nullptr);
    virtual ~QGLVideoWidget();
    // QOpenGLWidget interface
signals:
    void appendFrame(void*);
    void playOver(int);
    void start(int);
    void pause(int);
    void total(int);
    void setpos(int);
    void frameRate(int);
public slots:
    void onViewAdjust(bool = false);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initViewScale();
    void scaleViewCalc(bool bFlush = false);

    void totalTime(const int64_t t);
    void posChange(const int64_t t);
    void setVideoSize(int width, int height);
    void displayCall(void *data, int width, int height);
    void startCall(int);
    void endCall(int);
private:
    QOpenGLShader* m_vShader,* m_fShader;
    QOpenGLShaderProgram* m_program;
    int m_location[TEXTURE_MAX];
    GLfloat m_vertexVertices[8], m_textureVertices[8];
    _texture_obj_ m_texture[TEXTURE_MAX];
    QSize m_videoSize;
    /*_VideoFramePtr*/_video_frame_* m_pFrame;
    bool m_bViewAdjust;
    int m_frameCount;
};

#endif // QGLVIDEOWIDGET_H
