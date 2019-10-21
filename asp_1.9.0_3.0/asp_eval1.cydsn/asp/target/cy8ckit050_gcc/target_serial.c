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
 *  @(#) $Id: target_serial.c 2202 2011-07-26 13:27:11Z ertl-honda $
 */

/*
 *  シリアルI/Oデバイス（SIO）ドライバ（CY8C5XLP用）
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_serial.h"
#include "core_insn.h"
#include "cyfitter.h"
#include "UART_1.h"
#if(UART_1_INTERNAL_CLOCK_USED)
    #include "UART_1_IntClock.h"
#endif /* End UART_1_INTERNAL_CLOCK_USED */

#if (TNUM_SIOP >= 2)
	#include "UART_2.h"
    
    #if(UART_2_INTERNAL_CLOCK_USED)
        #include "UART_2_IntClock.h"
    #endif /* End UART_2_INTERNAL_CLOCK_USED */
#endif /* TNUM_SIOP >= 2 */

#if (TNUM_SIOP >= 3)
	#include "UART_3.h"
    
    #if(UART_3_INTERNAL_CLOCK_USED)
        #include "UART_3_IntClock.h"
    #endif /* End UART_3_INTERNAL_CLOCK_USED */
#endif /* TNUM_SIOP >= 3 */

#if (TNUM_SIOP >= 4)
	#include "UART_4.h"
    
    #if(UART_4_INTERNAL_CLOCK_USED)
        #include "UART_4_IntClock.h"
    #endif /* End UART_4_INTERNAL_CLOCK_USED */
#endif /* TNUM_SIOP >= 4 */



/*
 *  シリアルI/Oポート初期化ブロックの定義
 */
typedef struct sio_port_initialization_block {
	ID       port;   /* SIOのポートID(論理番号) */
	INTNO    intno;  /* 割込み番号 */
} SIOPINIB;

/*
 *  シリアルI/Oポート管理ブロックの定義
 */
struct sio_port_control_block {
	const SIOPINIB  *p_siopinib;  /* シリアルI/Oポート初期化ブロック */
	intptr_t        exinf;        /* 拡張情報 */
	bool_t          opnflg;       /* オープン済みフラグ */
};

/*
 * シリアルI/Oポート初期化ブロック
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
	{(ID)0, (INTNO)INTNO_SIO},
#if (TNUM_SIOP >= 2)
	{(ID)1, (INTNO)INTNO_SIO},
#endif /* TNUM_SIOP >= 2 */
#if (TNUM_SIOP >= 3)
	{(ID)2, (INTNO)INTNO_SIO},
#endif /* TNUM_SIOP >= 3 */
#if (TNUM_SIOP >= 4)
	{(ID)3, (INTNO)INTNO_SIO},
#endif /* TNUM_SIOP >= 4 */
};

/*
 *  シリアルI/Oポート管理ブロックのエリア
 */
SIOPCB	siopcb_table[TNUM_SIOP];

/*
 *  シリアルI/OポートIDから管理ブロックを取り出すためのマクロ
 */
#define INDEX_SIOP(siopid)	((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	(&(siopcb_table[INDEX_SIOP(siopid)]))

/*
 *  ターゲットのシリアル初期化
 *
 * PSoC Creatorが生成するUARTドライバを参考に作成
 *
 * ・UART_*_TXCLKGENDPシンボルの定義が不明のためそのまま引用
 * ・UART_1_INTERNAL_CLOCK_USEDシンボルはユーザ選択可能とした
 */
void target_usart_init(ID siopid)
{
	switch(siopid) {
	case 0:	/* シリアルポートID:0 */
		if((UART_1_RXBITCTR_CONTROL_REG && UART_1_CNTR_ENABLE) == 0) {
	        /* Init Count7 period */
	        UART_1_RXBITCTR_PERIOD_REG = UART_1_RXBITCTR_INIT;
	        /* Configure the Initial RX interrupt mask */
	        UART_1_RXSTATUS_MASK_REG  = UART_1_INIT_RX_INTERRUPTS_MASK;
	
	        /* Write Counter Value for TX Bit Clk Generator*/
	        #if(UART_1_TXCLKGEN_DP)
	            UART_1_TXBITCLKGEN_CTR_REG = UART_1_BIT_CENTER;
	            UART_1_TXBITCLKTX_COMPLETE_REG = (UART_1_NUMBER_OF_DATA_BITS +
	                        UART_1_NUMBER_OF_START_BIT) * UART_1_OVER_SAMPLE_COUNT;
	        #else
	            UART_1_TXBITCTR_PERIOD_REG = ((UART_1_NUMBER_OF_DATA_BITS +
	                        UART_1_NUMBER_OF_START_BIT) * UART_1_OVER_SAMPLE_8) - 1u;
	        #endif /* End UART_1_TXCLKGEN_DP */

	        /* Configure the Initial TX interrupt mask */
	        #if(UART_1_TX_INTERRUPT_ENABLED && (UART_1_TXBUFFERSIZE > UART_1_FIFO_LENGTH))
	            UART_1_TXSTATUS_MASK_REG = UART_1_TX_STS_FIFO_EMPTY;
	        #else
	            UART_1_TXSTATUS_MASK_REG = UART_1_INIT_TX_INTERRUPTS_MASK;
	        #endif /*End UART_1_TX_INTERRUPT_ENABLED*/

	        /*RX Counter (Count7) Enable */
	        UART_1_RXBITCTR_CONTROL_REG |= UART_1_CNTR_ENABLE;
	        /* Enable the RX Interrupt. */
/*	        UART_1_RXSTATUS_ACTL_REG  |= UART_1_INT_ENABLE;*/

	        /*TX Counter (DP/Count7) Enable */
	        #if(!UART_1_TXCLKGEN_DP)
	            UART_1_TXBITCTR_CONTROL_REG |= UART_1_CNTR_ENABLE;
	        #endif /* End UART_1_TXCLKGEN_DP */
	        /* Enable the TX Interrupt. */
/*	        UART_1_TXSTATUS_ACTL_REG |= UART_1_INT_ENABLE;*/

		    #if(UART_1_INTERNAL_CLOCK_USED)
	    	   /* Enable the clock. */
		        UART_1_IntClock_Start();
		    #endif /* End UART_1_INTERNAL_CLOCK_USED */
		}
		break;
        
    #if (TNUM_SIOP >= 2)
    case 1:	/* シリアルポートID:1 */
		if((UART_2_RXBITCTR_CONTROL_REG && UART_2_CNTR_ENABLE) == 0) {
	        /* Init Count7 period */
	        UART_2_RXBITCTR_PERIOD_REG = UART_2_RXBITCTR_INIT;
	        /* Configure the Initial RX interrupt mask */
	        UART_2_RXSTATUS_MASK_REG  = UART_2_INIT_RX_INTERRUPTS_MASK;
	
	        /* Write Counter Value for TX Bit Clk Generator*/
	        #if(UART_2_TXCLKGEN_DP)
	            UART_2_TXBITCLKGEN_CTR_REG = UART_2_BIT_CENTER;
	            UART_2_TXBITCLKTX_COMPLETE_REG = (UART_2_NUMBER_OF_DATA_BITS +
	                        UART_2_NUMBER_OF_START_BIT) * UART_2_OVER_SAMPLE_COUNT;
	        #else
	            UART_2_TXBITCTR_PERIOD_REG = ((UART_2_NUMBER_OF_DATA_BITS +
	                        UART_2_NUMBER_OF_START_BIT) * UART_2_OVER_SAMPLE_8) - 1u;
	        #endif /* End UART_2_TXCLKGEN_DP */

	        /* Configure the Initial TX interrupt mask */
	        #if(UART_2_TX_INTERRUPT_ENABLED && (UART_2_TXBUFFERSIZE > UART_2_FIFO_LENGTH))
	            UART_2_TXSTATUS_MASK_REG = UART_2_TX_STS_FIFO_EMPTY;
	        #else
	            UART_2_TXSTATUS_MASK_REG = UART_2_INIT_TX_INTERRUPTS_MASK;
	        #endif /*End UART_2_TX_INTERRUPT_ENABLED*/

	        /*RX Counter (Count7) Enable */
	        UART_2_RXBITCTR_CONTROL_REG |= UART_2_CNTR_ENABLE;
	        /* Enable the RX Interrupt. */
/*	        UART_2_RXSTATUS_ACTL_REG  |= UART_2_INT_ENABLE;*/

	        /*TX Counter (DP/Count7) Enable */
	        #if(!UART_2_TXCLKGEN_DP)
	            UART_2_TXBITCTR_CONTROL_REG |= UART_2_CNTR_ENABLE;
	        #endif /* End UART_2_TXCLKGEN_DP */
	        /* Enable the TX Interrupt. */
/*	        UART_2_TXSTATUS_ACTL_REG |= UART_2_INT_ENABLE;*/

		    #if(UART_2_INTERNAL_CLOCK_USED)
	    	   /* Enable the clock. */
		        UART_2_IntClock_Start();
		    #endif /* End UART_2_INTERNAL_CLOCK_USED */
		}
		break;
    #endif
    #if (TNUM_SIOP >= 3)
    case 2:	/* シリアルポートID:2 */
		if((UART_3_RXBITCTR_CONTROL_REG && UART_3_CNTR_ENABLE) == 0) {
	        /* Init Count7 period */
	        UART_3_RXBITCTR_PERIOD_REG = UART_3_RXBITCTR_INIT;
	        /* Configure the Initial RX interrupt mask */
	        UART_3_RXSTATUS_MASK_REG  = UART_3_INIT_RX_INTERRUPTS_MASK;
	
	        /* Write Counter Value for TX Bit Clk Generator*/
	        #if(UART_3_TXCLKGEN_DP)
	            UART_3_TXBITCLKGEN_CTR_REG = UART_3_BIT_CENTER;
	            UART_3_TXBITCLKTX_COMPLETE_REG = (UART_3_NUMBER_OF_DATA_BITS +
	                        UART_3_NUMBER_OF_START_BIT) * UART_3_OVER_SAMPLE_COUNT;
	        #else
	            UART_3_TXBITCTR_PERIOD_REG = ((UART_3_NUMBER_OF_DATA_BITS +
	                        UART_3_NUMBER_OF_START_BIT) * UART_3_OVER_SAMPLE_8) - 1u;
	        #endif /* End UART_3_TXCLKGEN_DP */

	        /* Configure the Initial TX interrupt mask */
	        #if(UART_3_TX_INTERRUPT_ENABLED && (UART_3_TXBUFFERSIZE > UART_3_FIFO_LENGTH))
	            UART_3_TXSTATUS_MASK_REG = UART_3_TX_STS_FIFO_EMPTY;
	        #else
	            UART_3_TXSTATUS_MASK_REG = UART_3_INIT_TX_INTERRUPTS_MASK;
	        #endif /*End UART_3_TX_INTERRUPT_ENABLED*/

	        /*RX Counter (Count7) Enable */
	        UART_3_RXBITCTR_CONTROL_REG |= UART_3_CNTR_ENABLE;
	        /* Enable the RX Interrupt. */
/*	        UART_3_RXSTATUS_ACTL_REG  |= UART_3_INT_ENABLE;*/

	        /*TX Counter (DP/Count7) Enable */
	        #if(!UART_3_TXCLKGEN_DP)
	            UART_3_TXBITCTR_CONTROL_REG |= UART_3_CNTR_ENABLE;
	        #endif /* End UART_3_TXCLKGEN_DP */
	        /* Enable the TX Interrupt. */
/*	        UART_3_TXSTATUS_ACTL_REG |= UART_3_INT_ENABLE;*/

		    #if(UART_3_INTERNAL_CLOCK_USED)
	    	   /* Enable the clock. */
		        UART_3_IntClock_Start();
		    #endif /* End UART_3_INTERNAL_CLOCK_USED */
		}
		break;
    #endif
    #if (TNUM_SIOP >= 4)
	case 3:	/* シリアルポートID:3 */
		if((UART_4_RXBITCTR_CONTROL_REG && UART_4_CNTR_ENABLE) == 0) {
	        /* Init Count7 period */
	        UART_4_RXBITCTR_PERIOD_REG = UART_4_RXBITCTR_INIT;
	        /* Configure the Initial RX interrupt mask */
	        UART_4_RXSTATUS_MASK_REG  = UART_4_INIT_RX_INTERRUPTS_MASK;
	
	        /* Write Counter Value for TX Bit Clk Generator*/
	        #if(UART_4_TXCLKGEN_DP)
	            UART_4_TXBITCLKGEN_CTR_REG = UART_4_BIT_CENTER;
	            UART_4_TXBITCLKTX_COMPLETE_REG = (UART_4_NUMBER_OF_DATA_BITS +
	                        UART_4_NUMBER_OF_START_BIT) * UART_4_OVER_SAMPLE_COUNT;
	        #else
	            UART_4_TXBITCTR_PERIOD_REG = ((UART_4_NUMBER_OF_DATA_BITS +
	                        UART_4_NUMBER_OF_START_BIT) * UART_4_OVER_SAMPLE_8) - 1u;
	        #endif /* End UART_4_TXCLKGEN_DP */

	        /* Configure the Initial TX interrupt mask */
	        #if(UART_4_TX_INTERRUPT_ENABLED && (UART_4_TXBUFFERSIZE > UART_4_FIFO_LENGTH))
	            UART_4_TXSTATUS_MASK_REG = UART_4_TX_STS_FIFO_EMPTY;
	        #else
	            UART_4_TXSTATUS_MASK_REG = UART_4_INIT_TX_INTERRUPTS_MASK;
	        #endif /*End UART_4_TX_INTERRUPT_ENABLED*/

	        /*RX Counter (Count7) Enable */
	        UART_4_RXBITCTR_CONTROL_REG |= UART_4_CNTR_ENABLE;
	        /* Enable the RX Interrupt. */
/*	        UART_4_RXSTATUS_ACTL_REG  |= UART_4_INT_ENABLE;*/

	        /*TX Counter (DP/Count7) Enable */
	        #if(!UART_4_TXCLKGEN_DP)
	            UART_4_TXBITCTR_CONTROL_REG |= UART_4_CNTR_ENABLE;
	        #endif /* End UART_4_TXCLKGEN_DP */
	        /* Enable the TX Interrupt. */
/*	        UART_4_TXSTATUS_ACTL_REG |= UART_4_INT_ENABLE;*/

		    #if(UART_4_INTERNAL_CLOCK_USED)
	    	   /* Enable the clock. */
		        UART_4_IntClock_Start();
		    #endif /* End UART_4_INTERNAL_CLOCK_USED */
		}
		break;
    #endif
	default: /* 未定義ポート */
		break;
	};
}

/*
 *  SIOドライバの初期化
 */
void
sio_initialize(intptr_t exinf)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  シリアルI/Oポート管理ブロックの初期化
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++) {
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->opnflg = false;
	}
}


/*
 *  シリアルI/Oポートのオープン
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;
	bool_t  opnflg;
	ER      ercd;

	p_siopcb = get_siopcb(siopid);
	p_siopinib = p_siopcb->p_siopinib;

	/*
	 *  オープンしたポートがあるかをopnflgに読んでおく．
	 */
	opnflg = p_siopcb->opnflg;

	p_siopcb->exinf = exinf;

	/*
	 *  ハードウェアの初期化
	 */
	target_usart_init(siopid);

	/*
	 *  シリアルI/O割込みのマスクを解除する．
	 */
	if (!opnflg) {
		ercd = ena_int(p_siopinib->intno);
		assert(ercd == E_OK);
	}

	return(p_siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	/*
	 *  シリアルI/O割込みをマスクする．
	 */
	if (!(p_siopcb->opnflg)) {
		dis_int(p_siopcb->p_siopinib->intno);
	}
}

/*
 *  SIOの割込みサービスルーチン
 */
void
sio_isr(intptr_t exinf)
{
	SIOPCB          *p_siopcb;

	p_siopcb = get_siopcb(exinf);

	/*
	 *  割込みのクリア
	 */
/* PSoC UARTでも必要か要確認 */

/* シリアルポートを切り替える場合は，p_siopcb->p_siopinib->ID で判別する*/

	if ((UART_1_ReadRxStatus() & UART_1_RX_STS_FIFO_NOTEMPTY) != 0u) {
		/*
		 *  受信通知コールバックルーチンを呼び出す．
		 */
		sio_irdy_rcv(p_siopcb->exinf);
	}
	if ((UART_1_ReadTxStatus() & UART_1_TX_STS_FIFO_FULL) == 0u) {
		/*
		 *  送信可能コールバックルーチンを呼び出す．
		 */
		sio_irdy_snd(p_siopcb->exinf);
	}
}

/*
 *  シリアルI/Oポートへの文字送信
 */
bool_t
sio_snd_chr(SIOPCB *p_siopcb, char c)
{
/* シリアルポートを切り替える場合は，p_siopcb->p_siopinib->ID で判別する*/
	if((UART_1_ReadTxStatus() & UART_1_TX_STS_FIFO_FULL) == 0u){
        UART_1_TXDATA_REG = (uint8)c;
		return(true);
	}
	return(false);
}

/*
 *  シリアルI/Oポートからの文字受信
 */
int_t
sio_rcv_chr(SIOPCB *p_siopcb)
{
/* シリアルポートを切り替える場合は，p_siopcb->p_siopinib->ID で判別する*/
	if((UART_1_ReadRxStatus() & UART_1_RX_STS_FIFO_NOTEMPTY) != 0u){
		return((int_t) UART_1_GetChar());
	}
	return(-1);
}

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
void
sio_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
/* シリアルポートを切り替える場合は，p_siopcb->p_siopinib->ID で判別する*/
	switch (cbrtn) {
	  case SIO_RDY_SND:
        /* Enable the TX Interrupt. */
        UART_1_TXSTATUS_ACTL_REG |= UART_1_INT_ENABLE;
		break;
	  case SIO_RDY_RCV:
        /* Enable the RX Interrupt. */
        UART_1_RXSTATUS_ACTL_REG  |= UART_1_INT_ENABLE;
		break;
	}
}

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
void
sio_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
/* シリアルポートを切り替える場合は，p_siopcb->p_siopinib->ID で判別する*/
	switch (cbrtn) {
	  case SIO_RDY_SND:
        /* Disable the TX Interrupt. */
        UART_1_TXSTATUS_ACTL_REG &= (uint8)~UART_1_INT_ENABLE;
		break;
	  case SIO_RDY_RCV:
        /* Disable the RX Interrupt. */
        UART_1_RXSTATUS_ACTL_REG  &= (uint8)~UART_1_INT_ENABLE;
		break;
	}
}
