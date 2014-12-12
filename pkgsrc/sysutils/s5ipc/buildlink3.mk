# $NetBSD$
# XXX
# XXX This file was created automatically using createbuildlink-3.14.
# XXX After this file has been verified as correct, the comment lines
# XXX beginning with "XXX" should be removed.  Please do not commit
# XXX unverified buildlink3.mk files.
# XXX
# XXX Packages that only install static libraries or headers should
# XXX include the following line:
# XXX
# XXX	BUILDLINK_DEPMETHOD.s5ipc?=	build

BUILDLINK_TREE+=	s5ipc

.if !defined(S5IPC_BUILDLINK3_MK)
S5IPC_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.s5ipc+=	s5ipc>=0.1
BUILDLINK_PKGSRCDIR.s5ipc?=	../../sysutils/s5ipc
.endif	# S5IPC_BUILDLINK3_MK

BUILDLINK_TREE+=	-s5ipc
