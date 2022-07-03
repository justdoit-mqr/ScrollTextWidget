/*
 *@author:  缪庆瑞
 *@date:    2022.07.02
 *@brief:   滚动字幕部件
 */
#include "scrolltextwidget.h"
#include <QPainter>
#include <QFontMetrics>
#include <QDebug>

ScrollTextWidget::ScrollTextWidget(QWidget *parent) : QWidget(parent)
{
    scrollTimer = new QTimer(this);
    connect(scrollTimer,SIGNAL(timeout()),this,SLOT(scrollTimerSlot()));

    setScrollProperty();
    setTextProperty();
}
/*
 *@brief:  设置滚动属性
 *@date:   2022.07.02
 *@param:  step_pixel:滚动歩长，单位像素
 *@param:  interval_ms:滚动间隔，单位ms
 *@param:  repeat_spacing:循环间距，即上次字幕尾和下次字幕头的间距，单位像素
 */
void ScrollTextWidget::setScrollProperty(int step_pixel, int interval_ms, int repeat_spacing)
{
    this->scroll_step_pixel = step_pixel;
    this->scroll_interval_ms = interval_ms;
    this->scroll_repeat_spacing = repeat_spacing;
}
/*
 *@brief:  设置字幕属性
 *@date:   2022.07.02
 *@param:  fg_color:前景色(文本颜色)
 *@param:  font:字体
 */
void ScrollTextWidget::setTextProperty(const QColor &fg_color, const QFont &font)
{
    this->fg_color = fg_color;
    this->text_font = font;
    //计算文本宽度
    QFontMetrics fm(this->text_font);
    this->scroll_text_width = fm.width(this->scroll_text);
}
/*
 *@brief:  设置滚动字幕文本内容
 *@date:   2022.07.02
 *@param:  text:文本内容
 */
void ScrollTextWidget::setScrollText(QString text)
{
    this->scroll_text = text;
    //计算文本宽度
    QFontMetrics fm(this->text_font);
    this->scroll_text_width = fm.width(this->scroll_text);

    //重置滚动数据，重新开始
    this->scroll_count = 0;
    this->scroll_distance = 0;

    if(this->isVisible())
    {
        scrollTimer->start(scroll_interval_ms);
        update();
    }
}
/*
 *@brief:  定时器超时处理函数
 *@date:   2022.07.02
 */
void ScrollTextWidget::scrollTimerSlot()
{
    //当界面不显示时，停止定时器
    if(!this->isVisible())
    {
        this->scrollTimer->stop();
        return;
    }
    this->scroll_count++;
    this->scroll_distance = scroll_count*scroll_step_pixel;
    //当滚动距离大于等于文本宽度与循环间距之和时重置计数
    if(this->scroll_distance >= (this->scroll_text_width + this->scroll_repeat_spacing))
    {
        this->scroll_count = 0;
        this->scroll_distance = 0;
    }
    update();
}
/*
 *@brief:  显示事件处理函数
 *@date:   2022.07.02
 *@param:  event:显示事件
 */
void ScrollTextWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    scrollTimer->start(scroll_interval_ms);
}
/*
 *@brief:  绘图事件处理函数，绘制滚动的字幕
 *@date:   2022.07.02
 *@param:  event:绘图事件
 */
void ScrollTextWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(fg_color);
    painter.setFont(text_font);

    //文本长度小于控件宽度,不滚动居中显示
    if(scroll_text_width < width())
    {
        painter.drawText(QRect(0,0,width(),height()),Qt::AlignCenter,scroll_text);
        if(scrollTimer->isActive())
        {
            scrollTimer->stop();
        }
    }
    else//滚动展示
    {
        painter.drawText(QRect(-scroll_distance,0,scroll_text_width,height()),
                         Qt::AlignVCenter|Qt::AlignLeft,scroll_text);
        painter.drawText(QRect(scroll_text_width+scroll_repeat_spacing-scroll_distance,0,scroll_text_width,height()),
                         Qt::AlignVCenter|Qt::AlignLeft,scroll_text);
    }
}
/*
 *@brief:  尺寸调整事件处理函数，当尺寸不足以容纳字幕长度时自动开启定时器
 *@date:   2022.07.02
 *@param:  event:尺寸事件
 */
void ScrollTextWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if(scroll_text_width >= width())
    {
        if(!scrollTimer->isActive())
        {
            scrollTimer->start(scroll_interval_ms);
        }
    }
}
