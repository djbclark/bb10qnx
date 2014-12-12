/*
 * Copyright � 1996-2013 Certicom Corp. All rights reserved.
 * 
 * This software contains trade secrets, confidential information, and other
 * intellectual property of Certicom Corp. and its licensors. This software
 * cannot be used, reproduced, or distributed in whole or in part by any means
 * without the explicit prior consent of Certicom Corp. Such consent must arise
 * from a separate license agreement from Certicom or its licensees, as 
 * appropriate.
 * 
 * Certicom, Certicom AMS, ACC, Asset Control Core, Certicom Bar Code
 * Authentication Agent, Certicom ECC Core, Certicom Security Architecture,
 * Certicom Trusted Infrastructure, Certicom CodeSign, Certicom KeyInject,
 * ChipActivate, DieMax, Security Builder, Security Builder API, 
 * Security Builder API for .NET, Security Builder BSP, Security Builder Crypto,
 * Security Builder ETS, Security Builder GSE, Security Builder IPSec, Security
 * Builder MCE, Security Builder NSE, Security Builder PKI, Security Builder SSL
 * and SysActivate are trademarks or registered trademarks of Certicom Corp.
 * All other companies and products listed herein are trademarks or registered
 * trademarks of their respective holders.
 *
 * BlackBerry�, RIM�, Research In Motion� and related trademarks are owned by
 * Research In Motion Limited. Used under license.
 * 
 */
/* $Id: sbidberr.h 41815 2010-12-06 16:15:04Z mimueller $
 * $Source$
 * $Name$
 */
#ifndef SBIDBERR_H
#define SBIDBERR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sbreturn.h"

/*
Generic SBI Database errors 

All generic SBI Database errors map in the range 0x3030 - 0x304F SBI will use
only the lo-byte for specific errors.
*/

#define SB_ERR_DB_NOT_EXISTS             0x3C31  /**< database does not exist. */
#define SB_ERR_DB_NULL_ENGINE            0x3C32  /**< engine function is NULL. */ 
#define SB_ERR_DB_OPEN                   0x3C33  /**< cannot open the database. */
#define SB_ERR_DB_CLOSE                  0x3C34  /**< cannot close the database. */
#define SB_ERR_DB_DELETE                 0x3C35  /**< cannot delete the database. */
#define SB_ERR_DB_WRITE                  0x3C36  /**< error occured during the write operation. */
#define SB_ERR_DB_READ                   0x3C37  /**< error occured during the read operation. */
#define SB_ERR_DB_NO_RECORD              0x3C38  /**< cursor object does not point to any record. */
#define SB_ERR_DB_NO_FIELD               0x3C39  /**< record object does not contain the requested field. */
#define SB_ERR_DB_BAD_ENCRYPTION_SUITE   0x3C3A  /**< encryption suite object is not set properly to access the data in the database. */
#define SB_ERR_DB_BAD_ALLOC_POLICY       0x3C3B  /**< unsupported alloc policy */                         
#define SB_ERR_DB_PASSWORD_REQUIRED      0x3C3C  /**< existing database require a password. */
#define SB_ERR_DB_AUTH_FAILED            0x3C3D  /**< bad password for the existing database is provided. */
#define SB_ERR_DB_CORRUPTED              0x3C3E  /**< the database is corrupted. */
#define SB_ERR_DB_EXISTS                 0x3C3F  /**< the database exists */
#define SB_ERR_DB_CREATE                 0x3C40  /**< cannot create the database. */

/* 
Bases for SBI Database provider specific errors.  

If the error generated by the provider cannot be mapped to a Security Builder
error then the error will have the bottom nibble of the hi-byte set to
determine which provider generated the error.

*/

#define SB_ERR_DB_DIRECTORY_BASE         0x3B00  /**< base of Directory-based provider specific errors. */
#define SB_ERR_DB_WINCE_BASE             0x3C00  /**< base of WinCE-based provider specific errors. */
#define SB_ERR_DB_CAC_BASE               0x3D00  /**< base of CAC-based provider specific errors. */

#ifdef __cplusplus
}
#endif

#endif
