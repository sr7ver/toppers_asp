/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: target_config.c 2183 2011-07-23 10:29:36Z ertl-honda $
 */

/*
 * ターゲット依存モジュール（CY8C5XLP用）
 */
#include "kernel_impl.h"
#include <sil.h>
#include "t_stddef.h"

#include "device.h"

#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

extern void target_usart_init();
extern const FP _kernel_vector_table[];

/*
 *  ターゲット依存の初期化
 */
void
target_initialize(void){
    uint32 i;
    cyisraddress *ramVectorTable;

	/*
	 * RAM上のベクタテーブルアドレスを保存
	 */
    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

	/*
	 * コア依存の初期化
	 */
	core_initialize();

    /*
	 * ベクタアドレスをNVICへ再設定
	 */
    *CYINT_VECT_TABLE = ramVectorTable;
    for(i = 0; i < 48 ; i++)
    {
        *ramVectorTable++ = (cyisraddress)_kernel_vector_table[i];
    }

	/*
	 *  target_fput_log が可能になるようにUARTを初期化
	 */
	target_usart_init((ID) 0);

} 


/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
	/*
	 *  コア依存の終了処理
	 */
	core_terminate();

	/*
	 *  開発環境依存の終了処理
	 */
	while(1);
}


/*
 *  システムログの低レベル出力のための文字出力
 */
void
target_fput_log(char c)
{
	if (c == '\n') {
		UART_1_PutChar((uint8) '\r');
	}
	UART_1_PutChar((uint8) c);
}
