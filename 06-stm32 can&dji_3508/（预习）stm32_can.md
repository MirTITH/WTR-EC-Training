**stm32 HAL can协议：**
https://blog.csdn.net/weixin_41082463/article/details/104914371
（1）物理层硬件连接
（2）波特率计算
（3）数据帧结构
（4）关注两个结构体：CAN_TxHeaderTypeDef/CAN_TxHeaderTypeDef
（5）关注几个HAL_CAN的库函数：
HAL_CAN_GetRxMessage();
HAL_CAN_AddTxMessage();
HAL_CAN_GetTxMailboxesFreeLevel();