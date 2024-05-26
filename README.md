# tetris

#### 介绍
用c++写的俄罗斯方块，基于SDL2图像库、spdlog日志库，使用CMakeLists.txt方式编译代码
#### 软件架构
软件架构说明


#### 安装教程

1.  安装SDL2  
        sudo apt install libsdl2-dev  
        sudo apt install libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
2.  在本地/usr/lib/x86_64-linux-gnu/cmake下新建sdl2_image、sdl2_ttf、sdl2_mixer等文件夹
3.  各自文件夹里面新建文件,例sdl2_image下新建文件sdl2_image-config.cmake  
        文件内容:  
        set(prefix "/usr")  
        set(exec_prefix "\\\${prefix}")    
        set(libdir "\\\${prefix}/lib/x86_64-linux-gnu")  
        set(SDL2_IMAGE_PREFIX "/usr")  
        set(SDL2_IMAGE_EXEC_PREFIX "/usr")  
        set(SDL2_IMAGE_INCLUDE_DIRS "\\\${prefix}/include/SDL2_image")  
        set(SDL2_IMAGE_LIBRARIES "-lSDL2_image")  
4.  安装spdlog  
        代码库:https://github.com/gabime/spdlog/tree/v1.x  
        使用代码自带的CMakeLists.txt安装，命令:make install

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

#### 疑问
1.  play_game_manage.cpp中m_tile_vector.insert(m_tile_vector.end(), temp_vector.begin(), temp_vector.end());可以正常运行，m_tile_vector.insert(m_tile_vector.end(), temp->get_tiles_info().begin(), temp->get_tiles_info().end());会出core，难道temp->get_tiles_info()两次获取的vector有区别？

#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
