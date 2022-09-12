# 第五天培训：

## 培训提纲：

stm32定时器；定时器中断&PWM波；基于PWM的直流电机闭环控制；多闭环控制结构；*FOC

## STM32定时器

参考资料1（关注概念）：[(81条消息) STM32-定时器详解_KevinFlyn的博客-CSDN博客_stm32定时器](https://blog.csdn.net/qq_44016222/article/details/123507270)
[STM32 定时器详细篇（基于HAL库） - 东小东 - 博客园 (cnblogs.com)](https://www.cnblogs.com/dongxiaodong/p/14351398.html)

## 重点*定时器中断和PWM的产生及作用

参考资料2（关注用法）：[【STM32】STM32定时器_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1AE411A7oc?spm_id_from=333.337.search-card.all.click&vd_source=51c04c8c10dc450fdd03d4f00d880ba9)

## 基于PWM的直流电机闭环控制

参考资料3（H桥 PWM调速）：[PWM是如何调节直流电机转速的？电机正反转的原理又是怎样的？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/83373994)

## 多闭环控制结构



参考资料（了解三闭环之间的关系，每一环的输出作为高一阶环的输入）：[(81条消息) 三个闭环负反馈PID调节系统：电流环、速度环和位置环的关系_JH17369320302的博客-CSDN博客_速度环和位置环的关系](https://blog.csdn.net/JH17369320302/article/details/79100764)

## （拓展内容）FOC

（1）传统旋转电机分类：直流电机；交流电机

（2）市场常用：PMSM（永磁同步电机）和**BLDC**（无刷直流电机）

附加参考资料1（PMSM和BLDC区别浅述）：[(81条消息) 一文了解BLDC与PMSM的区别_电机与控制的博客-CSDN博客_bldc和pmsm](https://blog.csdn.net/sphinz1/article/details/109265584)

（3）BLDC的旋转原理

附加参考资料2（BLDC的结构 换相过程）:[干货 | 无刷直流（BLDC）电机的原理及正确的使用方法-面包板社区 (eet-china.com)](https://www.eet-china.com/mp/a21338.html)

（4）FOC算法

附加参考资料3（park clark 矢量控制）[【自制FOC驱动器】深入浅出讲解FOC算法与SVPWM技术 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/147659820)

（5）无位置传感器FOC算法

了解即可 很多电机方向的研究生论文就这个水平了

