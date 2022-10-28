# git 在 vscode 中的入门教程

## 安装 git 和 vscode 插件

### Windows Git: 
参考 [01-stm32基础，环境配置.md](../01-stm32基础，环境配置/01-stm32基础，环境配置.md#git)

### Ubuntu Git:
```bash
sudo apt install git
```

vscode 插件：git history

> vscode 里面集成了 git 操作，点击相关按钮实际上是在执行 git 命令。  
> 比如`初始化仓库`是在后台执行 `git init`  
> 因此不用记住 git 命令也能方便地用 git  

## git 本地使用流程

### 全局配置
用户名和邮箱
```bash
git config --global user.name  "用户名"
git config --global user.email "邮箱"
```

### 本地库一般流程
1. 初始化仓库（此时会在当前目录创建隐藏文件夹`.git`，本仓库的所有配置和历史代码都保存在这里面）
2. 修改代码
3. 暂存
4. 提交（填写提交信息，一般写你干了啥（有一些流行的提交信息规范，感兴趣可以百度学习））

### 撤回
- 未暂存：放弃更改
- 已暂存：取消暂存更改
- 已提交：撤销上次提交

### 撤回大量提交
使用 Git History 插件，soft reset

## git 添加远程库
1. 注册 github 账号（或者 gitee 账号）
2. （推荐）配置 ssh 密钥（不建议设置 ssh 密码，设置后每次连接都要输入密码）  
   > 配置方法参考 <https://cloud.tencent.com/developer/article/2059781>  
   > ssh 是一种安全传输协议，使用 ssh 协议连接 git 远程仓库不需要输入账号和密码，并且克隆 github 仓库更稳定更快（大部分时间能直连 github）  

3. 在网页上创建一个空仓库
   > 一定要全空，一个文件都不要有，否则本地仓库推不上去（如果发生这种情况，可以用 git push --force 强制推送，之后正常推送就行
4. **选择 SSH 方式**（如果前面没有配置 ssh 就只能选择 http 方式），按照网页中给出的代码，给本地git仓库添加远程库并推送
5. 刷新网页，检查是否成功推送

## 同步到远程库的一般流程
1. 修改代码
2. 暂存
3. 提交
> 此时还没有访问远程库，接下来的操作会访问远程库
4. 点击同步更改

> 同步按钮实际上做了先拉取再推送的操作

## 克隆远程库
git clone 地址（选 SSH 地址则使用 SSH 通信，选 https 则使用 https 通信）

## 拉取远程库
点拉取（或 git pull）

## 拉取和克隆的区别
- 克隆是在没有本地库的情况下，创建一个本地库并把远程库的代码复制进来
- 拉取是在有本地库的情况下，把远程库中的更新同步到本地库中

## 更多教程
这只是入门操作，更多操作和概念解释请自行搜索资源

推荐一个：<https://www.runoob.com/git/git-tutorial.html>

## 附录
### git 查看配置文件
```shell
# 当前仓库的配置
git config --local --list

# 全局配置
git config --global --list
```

> 查看当前仓库的配置也可以直接查看 `.git/config` 文件

### git 配置代理
#### 使用 HTTP 或 HTTPS 协议连接到 Git 仓库的代理方法

以下两种二选一即可：
```shell
# 对于 sock5 代理
git config --global http.proxy 'sock5://localhost:你的端口号'

# 对于 http 代理
git config --global http.proxy 'http://localhost:你的端口号'
```

取消代理：
```shell
git config --global --unset http.proxy
```

> 网上很多中文教程，可能会告诉你 https:// 打头的 url 使用 `git config --global https.proxy`，这种做法其实是错的！记住一点：Git 不认 https.proxy ，设置 http.proxy 就可以支持 https 了。

#### 使用 SSH 协议连接到 Git 仓库的代理方法
##### Linux 和 macOS 用户
编辑 ~/.ssh/config 文件，加上如下内容：  

- 如果用 https 代理：
   ```
   Host github.com
      User git
      ProxyCommand nc -X connect -x localhost:你的端口号 %h %p
   ```

- 如果用 sock5 代理：
   ```
   Host github.com
      User git
      ProxyCommand nc -X 5 -x localhost:你的端口号 %h %p
   ```

##### Windows 用户
用 vscode 或记事本编辑 C:/Users/用户名/.ssh/config 文件，加上如下内容： 

- 如果用 https 代理：
   ```
   Host github.com
      User git
      ProxyCommand connect -H localhost:你的端口号 %h %p
   ```

- 如果用 sock5 代理：
   ```
   Host github.com
      User git
      ProxyCommand connect -S localhost:你的端口号 %h %p
   ```

取消代理：用 # 注释掉添加的内容就行

> 参考链接：[一文让你了解如何为 Git 设置代理](https://ericclose.github.io/git-proxy-config.html)
