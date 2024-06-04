# A-Simple-Address-Book-Client-Based-on-OpenGauss-and-Qt
实现了Qt客户端连接部署好OpenGauss的服务器和图形化操作联系人数据库。
# 注意事项：
### 1.在sqlmgr.cpp文件中修改实际使用的数据库参数（前提是已经在服务器或虚拟机上部署好opengauss）
![image](https://github.com/su322/A-Simple-Address-Book-Client-Based-on-OpenGauss-and-Qt/assets/85404658/1b3351ef-0be4-4c7a-92ce-292d4a406731)

### 2.里面的功能函数是根据我的数据库表结构设计的（用的navicat），如果不改变函数的话表结构要和我一样。
#### contacts表：

![image](https://github.com/su322/A-Simple-Address-Book-Client-Based-on-OpenGauss-and-Qt/assets/85404658/924509b5-e416-4c94-a6aa-15ed4ecc4981)
#### stars表：

![image](https://github.com/su322/A-Simple-Address-Book-Client-Based-on-OpenGauss-and-Qt/assets/85404658/ea168e9e-e609-44d6-bfe3-508fbc09b6e9)
#### user表：

![image](https://github.com/su322/A-Simple-Address-Book-Client-Based-on-OpenGauss-and-Qt/assets/85404658/e314badf-73b4-4859-998e-8a96390212ab)

### 3.因为navicate里面的postgres数据库类型没有自动递增选项，还创建了三个序列用于自动递增（配置在了上面图片的默认中）。因为每次新建联系人和收藏联系人时序列加一，但是删除的时候又不会自动减一，所以功能函数SqlMgr::delCts和SqlMgr::delStar中专门写了每次删除联系人和删除收藏联系人时序列减一，就保证了序列始终是实际的值。
![image](https://github.com/su322/A-Simple-Address-Book-Client-Based-on-OpenGauss-and-Qt/assets/85404658/7694c8d8-8551-4fe6-97e0-f7cd43622dc9)

### 4.因为设置了登录功能，所以在user表里必须增加一条用户名和密码才能进入界面
如图：
![image](https://github.com/su322/A-Simple-Address-Book-Client-Based-on-OpenGauss-and-Qt/assets/85404658/094e76be-ee98-4692-a58a-d5a64cbd3690)
