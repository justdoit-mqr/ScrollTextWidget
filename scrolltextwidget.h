/*
 *@author:  缪庆瑞
 *@date:    2022.07.02
 *@brief:   滚动字幕部件
 *该部件使用QPainter的drawText()方法，绘制字幕文本，并根据文本和部件的宽度自行决定是否滚动播放，
 *目前仅支持设置单行字幕文本从右向左循环滚动播放。
 */
#ifndef SCROLLTEXTWIDGET_H
#define SCROLLTEXTWIDGET_H

#include <QWidget>
#include <QColor>
#include <QFont>
#include <QTimer>

class ScrollTextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollTextWidget(QWidget *parent = nullptr);

    void setScrollProperty(int step_pixel=5,int interval_ms=200,int repeat_spacing=50);
    void setTextProperty(const QColor &fg_color=QColor(Qt::white),const QFont &font=QFont());
    void setScrollText(QString text);

public slots:
    void scrollTimerSlot();

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QTimer *scrollTimer;//滚动定时器
    //滚动属性
    int scroll_step_pixel;//滚动歩长(单位像素)
    int scroll_interval_ms;//滚动时间间隔(单位ms)
    int scroll_repeat_spacing;//滚动循环间距(上次字幕尾和下次字幕头的间距，单位像素)
    //字幕(文本)属性
    QColor fg_color;//前景色
    QFont  text_font;//字体
    //实时滚动数据
    QString scroll_text;//当前字幕(文本)的内容
    int scroll_text_width;//当前字幕(文本)的宽度
    int scroll_count=0;//滚动计数
    int scroll_distance=0;//滚动距离

};

#endif // SCROLLTEXTWIDGET_H
