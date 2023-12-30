# Code

包含qt工程项目文件KToDoList，其中主要包含以下文件

##### Qt designer类

1.MainWindow 主页面设计，数据库打开

2.first_window 首页设计

3.mytodowindow 我的待办页面设计

4.groupwindow 分组页面设计

5.mycalenderwidget 到期日期选择页面设计

6.remindcalendarwidget 提醒时间选择页面设计

##### Qt类

1.customerqlabel 对qlabel类的重写，使其具备clicked()信号槽函数

2.mylineedit 对lineedit类的重写，使其具备lineeditclicked()信号槽函数

##### c++文件

1.data_struct.h 待办的数据结构声明

2.data_struct.cpp 全局变量定义

3.main.cpp 主函数定义

##### image文件夹

包含所有用到的图片文件

# Exec

包含可执行文件KToDoList.exe以及其执行依赖的文件。



# markdown_image

存储readme中的图片文件

# 用户手册

1.点击首页，回到首页界面（默认界面）

![](markdown_image\2022-11-16-12-59-14-image.png)

点击刷新，得到所有未完成的待办

![](markdown_image\2022-11-16-13-00-06-image.png)

点击新建待办，输入待办后回车，成功新建待办

点击待办条目，出现右侧选择框，得待办信息进行修改

![](markdown_image\2022-11-16-13-01-16-image.png)

在右侧点击时间，出现时间选择框，完成选择后点击确定，实现到期时间的修改

![](markdown_image\2022-11-16-13-02-55-image.png)

在右侧点击提醒，出现提醒时间选择框，完成选择后点击确定，实现提醒时间的修改

![](markdown_image\2022-11-16-13-03-30-image.png)

2.点击我的待办，进入我的待办界面

![](markdown_image\2022-11-16-13-04-53-image.png)

基本功能与首页类似，添加功能有

点击排序，选择排序方式，实现项目排序

![](markdown_image\2022-11-16-13-05-59-image.png)

点击显示已完成，展示已完成项目，通过连续点击该按钮实现已完成项目的刷新

![](markdown_image\2022-11-16-13-06-27-image.png)

分别点击两个ListWidget中的项目，右侧展示对应项目详细信息

![](markdown_image\2022-11-16-13-08-24-image.png)

3.点击分组，进入分组界面

基本功能与我的待办界面相似，添加功能如下

在左侧输入分组名字后点击添加分组，实现分组添加

点击左侧分组名字，切换到当前分组，此时添加的待办是当前分组的待办，点击刷新则只出现当前分组的待办

![](markdown_image\2022-11-16-13-16-31-image.png)

点击显示/隐藏已完成按钮，实现分组已完成项的刷新。
