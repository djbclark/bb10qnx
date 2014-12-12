/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information. $
 */
#ifndef __FS_QNX6_H_INCLUDED
#define __FS_QNX6_H_INCLUDED

#include <sys/platform.h>
#include <sys/types.h>

#define QNX6FS_NAME_MAX			510
#define QNX6FS_SYMLINK_MAX		512
#ifdef PATH_MAX
#define QNX6FS_PATH_MAX			PATH_MAX
#else
#define QNX6FS_PATH_MAX			1024
#endif

#define QNX6FS_DIRECT_BLKS		16
#define QNX6FS_INDIRECT_LEVELS	3
#define QNX6FS_UNUSED_BLK		((_Uint32t)-1)

#define QNX6FS_INO_USED			0x01
#define QNX6FS_INO_MODIFIED		0x02

typedef struct q6_dinode {
	_Uint64t			i_size;
	_Uint32t			i_uid;
	_Uint32t			i_gid;
	_Uint32t			i_ftime;
	_Uint32t			i_mtime;
	_Uint32t			i_atime;
	_Uint32t			i_ctime;
	_Uint16t			i_mode;
	_Uint16t			i_nlink;
	_Uint32t			i_blocks[QNX6FS_DIRECT_BLKS];
	_Uint8t				i_indirect;
	_Uint8t				i_flags;
	_Uint8t				i_spare1[2];
	_Uint32t			i_crypt;
	_Uint32t			i_emode;
	_Uint8t				i_spare2[16];
} q6_dinode_t;

typedef struct q6_iinode {
	_Uint64t			i_size;
	_Uint32t			i_blocks[QNX6FS_DIRECT_BLKS];
	_Uint8t				i_indirect;
	_Uint8t				i_flags;
	_Uint8t				i_spare[6];
} q6_iinode_t;


/*  Bits for the q6_iinode_t.i_emode field
*/
#define QNX6FS_EMODE_ALIMIT		0x0001		/* Don't allocate beyond allocation limit */
#define QNX6FS_EMODE_INPLACE	0x0002		/* Do not COW the inode */
#define QNX6FS_EMODE_MASK		0x0003		/* Mask of valid emode bits */


/*  The .iextra file is organized as a set of fixed size records
 *  and only the first record is fixed as the keylist.
 */
#define QNX6FS_IEXTRA_VERSION       1
#define QNX6FS_IEXTRA_SIZE          512
#define QNX6FS_IEXTRA_TRAILER       16

#define QNX6FS_IEXTRA_UNUSED        0
#define QNX6FS_IEXTRA_DOMAIN_LIST	1
#define QNX6FS_IEXTRA_DOMAIN_KEY    2
#define QNX6FS_IEXTRA_FILE_KEY		3
#define QNX6FS_IEXTRA_FILE_NAME		4
#define QNX6FS_IEXTRA_ATTRIBUTE		5

#define QNX6FS_IEXTRA_SALT_SIZE     64
#define QNX6FS_IEXTRA_KEY_SIZE     (512/8)
#define QNX6FS_IEXTRA_MAX_KEY_SIZE (2048/8)

#define QNX6FS_DOMAIN_UNUSED        0
#define QNX6FS_DOMAIN_MAX		\
			((QNX6FS_IEXTRA_SIZE - QNX6FS_IEXTRA_TRAILER) / 4 - 2)

/*  Flags used in the public iextra record information (trailer)
*/

/*	The mask of valid bits describing the migration state. If any bit is set in
	this mask, the file is undergoing some form of migration. The migration
	state values are NOT binary exclusive. Since only four states can ever
	exist, we only use 2 bits to store the state.
*/
#define QNX6FS_IEXTRA_FLAG_MIGRATION        0x03

/*	The file is being migrated from plaintext 'P' to ciphertext 'C'.
*/
#define QNX6FS_IEXTRA_FLAG_MIGRATION_P2C	0x01

/*	The file is being migrated from ciphertext 'C' to plaintext 'P'.
*/
#define QNX6FS_IEXTRA_FLAG_MIGRATION_C2P	0x02

/*	The file is being migrated from ciphertext 'C' produced from one key to
	ciphertext 'C' produced by a different key.

	This flag is currently not supported.
*/
#define QNX6FS_IEXTRA_FLAG_MIGRATION_C2C	0x03

/*	Flags saved exclusively in the domain list entry of the iextra file.
	These flags cannot use the lower 2 bits since that is technically reserved
	for migration, even if these flags should never be set on the same record.
*/

/*	Defines if the whole disk is being encrypted under one domain.
	This will assume all plaintext files are 'tagged' to be migrated.
*/
#define QNX6FS_IEXTRA_FLAG_DL_WHOLE_DISK	0x04

/*	Defines if we need to hide plaintext files from the caller, and only make then
	visible when they have been completely migrated into their encrypted state.
*/
#define QNX6FS_IEXTRA_FLAG_DL_HIDE_PT		0x08


typedef struct q6_iextra {
	union {
		struct {
			_Uint32t		il_version;
			_Uint32t		il_key[QNX6FS_DOMAIN_MAX+1];
		}				ie_keylist;
		struct {
			_Uint8t			ik_random[QNX6FS_IEXTRA_SALT_SIZE];
			_Uint32t		ik_version;
			_Uint32t		ik_signature;
			_Uint8t			ik_keyno;
			_Uint8t			ik_reserved1;
			_Uint16t		ik_reserved2;
			_Uint8t			ik_spare[50];
			_Uint8t			ik_keytype;
			_Uint8t			ik_keylen;
			_Uint8t			ik_key[QNX6FS_IEXTRA_MAX_KEY_SIZE];
		}				ie_domainkey;
		struct {
			_Uint8t			ic_random[QNX6FS_IEXTRA_SALT_SIZE];
			_Uint32t		ic_version;
			_Uint16t		ic_flags;
			_Uint16t		ic_mode;
			_Uint64t		ic_size;
			_Uint64t		ic_ino;
			_Uint32t		ic_uid;
			_Uint32t		ic_gid;
			_Uint64t        ic_migration;
			_Uint8t			ic_spare[22];
			_Uint8t			ic_keytype;
			_Uint8t			ic_keylen;
			_Uint8t			ic_key[QNX6FS_IEXTRA_MAX_KEY_SIZE];
		}				ie_filekey;
		_Uint8t			ie_data[QNX6FS_IEXTRA_SIZE - QNX6FS_IEXTRA_TRAILER];
	}				ie_extra;

	_Uint64t        ie_inode;
	_Uint8t			ie_spare[4];
	_Uint8t         ie_flags;
	_Uint8t         ie_domaintype;
	_Uint8t			ie_domain;
	_Uint8t			ie_rectype;
} q6_iextra_t;

#define QNX6FS_DIR_EOF			0x00
#define QNX6FS_DIR_LONGNAME		0xFFu
#define QNX6FS_DIR_DELETED		0
#define QNX6FS_DIR_SHORT_LEN	27

typedef struct q6_direntry {
	_Uint32t			d_inode;
	union {
		struct {
			_Uint8t		d_length;
			char		d_name[QNX6FS_DIR_SHORT_LEN];
		}				d_short;
		struct {
			_Uint8t		d_islfn;
			_Uint8t		d_spare1[3];
			_Uint32t	d_blkno;
			_Uint32t	d_cksum;
			_Uint8t		d_spare2[16];
		}				d_long;
	}					d_name;
} q6_direntry_t;

typedef struct q6_longname {
	_Uint16t			d_length;
	char				d_name[QNX6FS_NAME_MAX];
} q6_longname_t;

#define QNX6FS_SIGNATURE		0x68191122
#define QNX6FS_ROOT_INODE		1
#define QNX6FS_BOOTDIR_INODE	2
#define QNX6FS_FSYS_VERSION		4
#define QNX6FS_SBLK_SIZE		512
#define QNX6FS_SBLK_RSRV		4096
#define QNX6FS_BOOT_RSRV		8192
#define QNX6FS_BOOTDIR_SIZE		4096
#define QNX6FS_DEFAULT_RSRV		3
#define QNX6FS_MAX_NGROUPS		64

#define QNX6FS_MAX_BLK_SIZE     (32 * 1024)

/* With block sizes larger than 4KiB, an offset must be added to ensure data
   contents are aligned to the block size boundaries:
   0...8KiB-1         Boot Block
   8KiB..12KiB-1      Superblock reserved
   12KiB..Block Size  Padding
*/
#define QNX6FS_MIN_RSRV_SIZE    (QNX6FS_BOOT_RSRV + QNX6FS_SBLK_RSRV)
#define QNX6FS_OVERHEAD_SIZE(b) (QNX6FS_BOOT_RSRV + 2 * max(QNX6FS_SBLK_RSRV, (b)))
#define QNX6FS_DATA_START(b)    ((QNX6FS_BOOT_RSRV + QNX6FS_SBLK_RSRV)        \
								+ ( ((b) <= QNX6FS_SBLK_RSRV) ? 0             \
								  : abs((b) - QNX6FS_MIN_RSRV_SIZE)) )

#define QNX6FS_SBLK_UNSTABLE	0x00000001
#define QNX6FS_SBLK_V3_LE_RSRV	0x00000002
#define QNX6FS_VOLUME_LABEL		0x00000004	/* Volume label is a string, not a UUID */
#define QNX6FS_LFN_CKSUM		0x00000100
#define QNX6FS_IEXTRA			0x00000200
#define QNX6FS_SBLK_V3_BE_RSRV	0x40000000
#define QNX6FS_MASK_INCOMPAT	0x00FF0000
#define QNX6FS_MASK_READONLY	0x0000FF00


/*
 * max volume label length: overlays s_uuid[]
 */
#define QNX6FS_MAX_LABEL_LEN	16

typedef struct q6_superblock {
	_Uint32t			s_signature;
	_Uint32t			s_chksum;
	_Uint64t			s_seqno;
	_Uint32t			s_fmttime;
	_Uint32t			s_wrtime;
	_Uint32t			s_flags;
	_Uint16t			s_version;
	_Uint16t			s_rsrvblks;
	_Uint8t				s_uuid[16];
	_Uint32t			s_blksize;
	_Uint32t			s_ninodes;
	_Uint32t			s_finodes;
	_Uint32t			s_nblocks;
	_Uint32t			s_fblocks;
	_Uint32t			s_ngroups;
	q6_iinode_t			s_inodes;
	q6_iinode_t			s_bitmap;
	q6_iinode_t			s_lnames;
	q6_iinode_t			s_iclaim;
	q6_iinode_t			s_iextra;
	_Uint32t            s_migrate_blocks;
	_Uint32t            s_scrub_block;
	_Uint8t				s_spare[32];
} q6_superblock_t;

#define QNX6FS_BG_DEFRAG		0x4000
#define QNX6FS_SNAPSHOT_HOLD	0x8000

#define QNX6FS_BOOT_QUIET		0x01
#define QNX6FS_BOOT_CLS			0x02

typedef struct q6_boothdr {
	_Uint8t				b_jmp[3];
	_Uint8t				b_flags;
	_Uint32t			b_offset;
	_Uint32t			b_sblk0;
	_Uint32t			b_sblk1;
} q6_boothdr_t;

__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_2_0X/services/blk/fs/qnx6/public/sys/fs_qnx6.h $ $Rev: 703292 $")
#endif
