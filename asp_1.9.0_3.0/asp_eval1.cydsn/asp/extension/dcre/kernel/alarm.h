/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
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
 *  @(#) $Id: alarm.h 1966 2010-11-20 07:23:56Z ertl-hiro $
 */

/*
 *		アラームハンドラ機能
 */

#ifndef TOPPERS_ALARM_H
#define TOPPERS_ALARM_H

#include <queue.h>
#include "time_event.h"

/*
 *  アラームハンドラ初期化ブロック
 */
typedef struct alarm_handler_initialization_block {
	ATR			almatr;			/* アラームハンドラ属性 */
	intptr_t	exinf;			/* アラームハンドラの拡張情報 */
	ALMHDR		almhdr;			/* アラームハンドラの起動番地 */
} ALMINIB;

/*
 *  アラームハンドラ管理ブロック
 */
typedef struct alarm_handler_control_block {
	const ALMINIB *p_alminib;	/* 初期化ブロックへのポインタ */
	bool_t		almsta;			/* アラームハンドラの動作状態 */
	TMEVTB		tmevtb;			/* タイムイベントブロック */
} ALMCB;

/*
 *  使用していないアラームハンドラ管理ブロックのリスト
 */
extern QUEUE	free_almcb;

/*
 *  アラームハンドラIDの最大値（kernel_cfg.c）
 */
extern const ID	tmax_almid;
extern const ID	tmax_salmid;

/*
 *  アラームハンドラ初期化ブロックのエリア（kernel_cfg.c）
 */
extern const ALMINIB	alminib_table[];
extern ALMINIB			aalminib_table[];

/*
 *  アラームハンドラ管理ブロックのエリア（kernel_cfg.c）
 */
extern ALMCB	almcb_table[];

/*
 *  アラームハンドラ管理ブロックからアラームハンドラIDを取り出すための
 *  マクロ
 */
#define	ALMID(p_almcb)	((ID)(((p_almcb) - almcb_table) + TMIN_ALMID))

/*
 *  アラームハンドラ機能の初期化
 */
extern void	initialize_alarm(void);

/*
 *  アラームハンドラ起動ルーチン
 */
extern void	call_almhdr(ALMCB *p_almcb);

#endif /* TOPPERS_ALARM_H */
