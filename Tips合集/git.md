# git 在 vscode 中的入门教程

## 安装 git 和 vscode 插件

### Windows Git: 
参考 [01-stm32基础，环境配置.md](../01-stm32基础，环境配置/01-stm32基础，环境配置.md#git)

### Ubuntu Git:
```bash
sudo apt install git
```

vscode 插件：git history

## git 本地使用流程

### 全局配置

用户名和邮箱
```bash
git config --global user.name  "用户名"
git config --global user.email "邮箱"
```

### 本地库正常流程
1. 创建本地仓库
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

