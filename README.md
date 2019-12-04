#### 此工具只是针对creator-lua-support的改进，由原来的 Scene 作为根节点，改为 Node作为根节点，去掉了关于分辨率的设置，方便导出各种场景和页面



#### 使用前，请先熟悉一下Cocos官方手册，以表敬意，[这里点一下就行](https://docs.cocos.com/cocos2d-x/manual/zh/editors_and_tools/creator_to_cocos2dx.html)



#### C++代码引用：

```c++
#include "reader/CreatorReader.h"

using namespace creator;
  
CreatorReader* reader = CreatorReader::createWithFilename("filename.ccreator");
Node* root = reader->getNodeTree();
layer->addChild(root);
```



注意：此工具裁掉了DragonBones && Animations，请不要在UI界面使用这两项功能



#### 资源目录说明：

由于每次Build都会导出所用到的所有资源，所以，需要按照和自己项目同样的目录结果来组织资源，JS和Lua项目导出资源在res文件夹下，C++在Resources文件夹下，

核心就是：

1. 根据自己所摆的界面功能，划分单独的文件夹，能使用图集的，最好使用图集
2. 公共文件夹的资源，尽量不要做删减，避免其他功能引用失败
3. 如果项目使用了动态加载资源，那就设置导出资源到其他地方即可



#### 已知导出问题：

如果第一次点击Build没有反应，可以在项目根目录建立一个名为UI-Export的空文件夹