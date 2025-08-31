/*! 
voice command list 
 */ 
#ifndef _VOICE_CMD_LIST_H 
#define _VOICE_CMD_LIST_H 

/*voice*/ 
#define VOC_1 		 (0x00) 

/*sentence*/ 

#endif 

#pragma once
// 句子索引對應你燒進 BMV31T001 的 SEN_01、SEN_02...
// 沒有的自己改成對應的號碼，範圍 1~96
#define SEN_FALL_ALERT   1   // SEN_01：跌倒警示
#define SEN_TIMER_DONE   2   // SEN_02：計時結束
// 如果你還有「開始計時」也可以順手定
//#define SEN_TIMER_START  3
