#ifndef _LCF_LOG_H_
#define _LCF_LOG_H_

#ifdef _USE_LCF_LOG_

#include	<cf_log.h>
#define LCF_MSG	CF_MSG
#define LCF_DBG	CF_DBG
#define	LCF_ERR	CF_ERR
#define LCF_ERR_OUT CF_ERR_OUT
#define LCF_SYS_ERR    CF_SYS_ERR
#define LCF_SYS_ERR_OUT    CF_SYS_ERR_OUT

#define LCF_DBG_N CF_DBG_N
#define LCF_DBG_IN_FUNC CF_DBG_IN_FUNC
#define LCF_DBG_OUT_FUNC CF_DBG_OUT_FUNC
#define LCF_DBG_TS  CF_DBG_TS

#elif defined _USE_GLOBAL_LOG_

#include <glb_log.h>
#define LCF_DBG	GLB_DBG
#define LCF_ERR	GLB_ERR
#define LCF_ERR_OUT GLB_ERR_OUT
#define LCF_SYS_ERR    GLB_SYS_ERR
#define LCF_SYS_ERR_OUT GLB_SYS_ERR_OUT
#define LCF_DBG_N GLB_DBG_N
#define LCF_DBG_IN_FUNC GLB_DBG_IN_FUNC
#define LCF_DBG_OUT_FUNC GLB_DBG_OUT_FUNC
#define LCF_DBG_TS  GLB_DBG_TS

#else
#include <cf_log.h>

#define LCF_MSG	CF_MSG
#define LCF_DBG(...)
#define LCF_ERR(...)
#define LCF_ERR_OUT(__dest, ...)    goto __dest
#define LCF_SYS_ERR(...)
#define LCF_SYS_ERR_OUT(__dest, ...) goto __dest
#define LCF_DBG_N()
#define LCF_DBG_IN_FUNC()
#define LCF_DBG_OUT_FUNC()
#define LCF_DBG_TS()

#endif	/* _LCF_LOG_ */

#endif	/* _LCF_LOG_H_ */
