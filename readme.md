# ScrollTextWidget
这是一个基于Qt widget开发的滚动字幕组件。  
## 示例:
![1.gif](./screenshots/1.gif)
## 功能概述：
该组件使用QPainter的drawText()方法，绘制字幕文本，并根据文本和部件的宽度自行决定是否滚动播放，目前仅支持设置单行字幕文本从右向左循环滚动播放。该组件由单独一个类(ScrollTextWidget)实现，继承自QWidget，默认是背景透明的，对外提供了几个简单接口，可设置一些属性参数以及字幕文本，具体如下：    
```
//设置滚动属性(歩长、时间间隔、循环间距)
void setScrollProperty(int step_pixel=5,int interval_ms=100,int repeat_spacing=50);
//设置文本属性(前景色、字体)
void setTextProperty(const QColor &fg_color=QColor(Qt::white),const QFont &font=QFont());
//设置滚动文本
void setScrollText(QString text);
```
## 小结：
该组件源自一个简单的项目需求，因为要求不高，所以代码实现比较简单，也没什么值得多说的。  
## 作者联系方式:
**邮箱:justdoit_mqr@163.com**  
**新浪微博:@为-何-而来**  
