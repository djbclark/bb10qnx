# $NetBSD: buildlink3.mk,v 1.1.1.1 2009/10/14 11:26:15 tnn Exp $

BUILDLINK_TREE+=	openjdk7

.if !defined(OPENJDK7_BUILDLINK3_MK)
OPENJDK7_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.openjdk7+=	openjdk7>=1.7.0.72.20090924
BUILDLINK_PKGSRCDIR.openjdk7?=		../../lang/openjdk7

.endif	# OPENJDK7_BUILDLINK3_MK

BUILDLINK_TREE+=	-openjdk7
