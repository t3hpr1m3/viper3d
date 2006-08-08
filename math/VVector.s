	.file	"VVector.cpp"
	.version	"01.01"
gcc2_compiled.:
.text
	.align 4
.globl __Q23UDP7VVectorfff
	.type	 __Q23UDP7VVectorfff,@function
__Q23UDP7VVectorfff:
.LFB1:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	movl	8(%ebp), %eax
	pushl	%ebx
.LCFI2:
	movl	12(%ebp), %edx
	movl	20(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	$__vt_Q23UDP7VVector, 16(%eax)
	movl	%edx, (%eax)
	movl	%ecx, 4(%eax)
	movl	%ebx, 8(%eax)
	movl	$0x3f800000, 12(%eax)
	movl	(%esp), %ebx
	leave
	ret
.LFE1:
.Lfe1:
	.size	 __Q23UDP7VVectorfff,.Lfe1-__Q23UDP7VVectorfff
	.align 4
.globl __Q23UDP7VVectorRCQ23UDP7VVector
	.type	 __Q23UDP7VVectorRCQ23UDP7VVector,@function
__Q23UDP7VVectorRCQ23UDP7VVector:
.LFB2:
	pushl	%ebp
.LCFI3:
	movl	%esp, %ebp
.LCFI4:
	movl	12(%ebp), %edx
	movl	8(%ebp), %ecx
	movl	(%edx), %eax
	movl	%eax, (%ecx)
	movl	4(%edx), %eax
	movl	%eax, 4(%ecx)
	movl	8(%edx), %eax
	movl	%eax, 8(%ecx)
	movl	12(%edx), %eax
	movl	%eax, 12(%ecx)
	movl	$__vt_Q23UDP7VVector, 16(%ecx)
	popl	%ebp
	ret
.LFE2:
.Lfe2:
	.size	 __Q23UDP7VVectorRCQ23UDP7VVector,.Lfe2-__Q23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl _._Q23UDP7VVector
	.type	 _._Q23UDP7VVector,@function
_._Q23UDP7VVector:
.LFB3:
	pushl	%ebp
.LCFI5:
	movl	%esp, %ebp
.LCFI6:
	subl	$8, %esp
.LCFI7:
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	andl	$1, %eax
	movl	$__vt_Q23UDP7VVector, 16(%edx)
	je	.L9
	leave
.LCFI8:
	jmp	__builtin_delete
	.p2align 2
.L9:
	leave
	ret
.LFE3:
.Lfe3:
	.size	 _._Q23UDP7VVector,.Lfe3-_._Q23UDP7VVector
.globl __rethrow
	.align 4
.globl Length__Q23UDP7VVector
	.type	 Length__Q23UDP7VVector,@function
Length__Q23UDP7VVector:
.LFB4:
	pushl	%ebp
.LCFI9:
	movl	%esp, %ebp
.LCFI10:
	pushl	%edi
.LCFI11:
	pushl	%esi
.LCFI12:
	subl	$16, %esp
.LCFI13:
	movl	8(%ebp), %esi
	movl	$0x0, -12(%ebp)
	call	HaveSSE__Q23UDP4VCPU
	testb	%al, %al
	je	.L11
	movl	$0x0, 12(%esi)
	leal	-12(%ebp), %edi
#APP
	movups	(%esi), %xmm0
	mulps	%xmm0, %xmm0
	movaps	%xmm0, %xmm1
	shufps $0x4E, %xmm1, %xmm1
	addps	%xmm1, %xmm0
	movaps %xmm0, %xmm1
	shufps $0x11, %xmm1, %xmm1
	addps	%xmm1, %xmm0
	sqrtss	%xmm0, %xmm0
	movss	%xmm0, (%edi)
	
#NO_APP
	movl	$0x3f800000, 12(%esi)
	jmp	.L12
	.p2align 2
.L11:
	flds	(%esi)
	flds	4(%esi)
	fmul	%st(0), %st
	fxch	%st(1)
	fmul	%st(0), %st
	faddp	%st, %st(1)
	flds	8(%esi)
	fmul	%st(0), %st
	faddp	%st, %st(1)
#APP
	fsqrt
#NO_APP
	fstps	-12(%ebp)
.L12:
	flds	-12(%ebp)
	addl	$16, %esp
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.LFE4:
.Lfe4:
	.size	 Length__Q23UDP7VVector,.Lfe4-Length__Q23UDP7VVector
	.align 4
.globl SquaredLength__CQ23UDP7VVector
	.type	 SquaredLength__CQ23UDP7VVector,@function
SquaredLength__CQ23UDP7VVector:
.LFB5:
	pushl	%ebp
.LCFI14:
	movl	%esp, %ebp
.LCFI15:
	movl	8(%ebp), %eax
	flds	(%eax)
	flds	4(%eax)
	fmul	%st(0), %st
	fxch	%st(1)
	fmul	%st(0), %st
	faddp	%st, %st(1)
	flds	8(%eax)
	fmul	%st(0), %st
	faddp	%st, %st(1)
	popl	%ebp
	ret
.LFE5:
.Lfe5:
	.size	 SquaredLength__CQ23UDP7VVector,.Lfe5-SquaredLength__CQ23UDP7VVector
	.align 4
.globl UnitVector__Q23UDP7VVector
	.type	 UnitVector__Q23UDP7VVector,@function
UnitVector__Q23UDP7VVector:
.LFB6:
	pushl	%ebp
.LCFI16:
	movl	%esp, %ebp
.LCFI17:
	pushl	%esi
.LCFI18:
	pushl	%ebx
.LCFI19:
	subl	$28, %esp
.LCFI20:
	movl	12(%ebp), %ebx
	movl	8(%ebp), %esi
	pushl	%ebx
.LCFI21:
	call	Length__Q23UDP7VVector
	addl	$12, %esp
	leal	-12(%ebp), %eax
	pushl	%eax
	pushl	%ebx
	pushl	%esi
	fstps	-12(%ebp)
.LCFI22:
	call	__dv__CQ23UDP7VVectorRCf
	leal	-8(%ebp), %esp
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%ebp
	ret	$4
.LFE6:
.Lfe6:
	.size	 UnitVector__Q23UDP7VVector,.Lfe6-UnitVector__Q23UDP7VVector
	.align 4
.globl SetValues__Q23UDP7VVectorffff
	.type	 SetValues__Q23UDP7VVectorffff,@function
SetValues__Q23UDP7VVectorffff:
.LFB7:
	pushl	%ebp
.LCFI23:
	movl	%esp, %ebp
.LCFI24:
	pushl	%esi
.LCFI25:
	pushl	%ebx
.LCFI26:
	movl	24(%ebp), %esi
	movl	20(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	16(%ebp), %ecx
	movl	%ecx, 4(%eax)
	movl	%edx, (%eax)
	movl	%ebx, 8(%eax)
	movl	%esi, 12(%eax)
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
.LFE7:
.Lfe7:
	.size	 SetValues__Q23UDP7VVectorffff,.Lfe7-SetValues__Q23UDP7VVectorffff
	.align 4
.globl Negate__Q23UDP7VVector
	.type	 Negate__Q23UDP7VVector,@function
Negate__Q23UDP7VVector:
.LFB8:
	pushl	%ebp
.LCFI27:
	movl	%esp, %ebp
.LCFI28:
	movl	8(%ebp), %eax
	xorb	$128, 3(%eax)
	xorb	$128, 7(%eax)
	xorb	$128, 11(%eax)
	popl	%ebp
	ret
.LFE8:
.Lfe8:
	.size	 Negate__Q23UDP7VVector,.Lfe8-Negate__Q23UDP7VVector
	.align 4
.globl Normalize__Q23UDP7VVector
	.type	 Normalize__Q23UDP7VVector,@function
Normalize__Q23UDP7VVector:
.LFB9:
	pushl	%ebp
.LCFI29:
	movl	%esp, %ebp
.LCFI30:
	pushl	%esi
.LCFI31:
	pushl	%eax
	movl	8(%ebp), %esi
	call	HaveSSE__Q23UDP4VCPU
	testb	%al, %al
	je	.L31
	movl	$0x0, 12(%esi)
#APP
	movups	(%esi),		%xmm0
	movaps	%xmm0,		%xmm2
	mulps	%xmm0,		%xmm0
	movaps	%xmm0,		%xmm1
	shufps	$0x4E,		%xmm1,	%xmm1
	addps	%xmm1,		%xmm0
	movaps	%xmm0,		%xmm1
	shufps	$0x11,		%xmm1,	%xmm1
	addps	%xmm1,		%xmm0
	rsqrtps	%xmm0,		%xmm0
	mulps	%xmm0,		%xmm2
	movups	%xmm2,		(%esi)
#NO_APP
	movl	$0x3f800000, 12(%esi)
	jmp	.L43
	.p2align 2
.L31:
	flds	(%esi)
	flds	4(%esi)
	fld	%st(1)
	fld	%st(1)
	fmul	%st(0), %st
	flds	8(%esi)
	fxch	%st(2)
	fmul	%st(0), %st
	faddp	%st, %st(1)
	fld	%st(1)
	fmul	%st(0), %st
	faddp	%st, %st(1)
#APP
	fsqrt
#NO_APP
	fldz
	fxch	%st(1)
	fucom	%st(1)
	fnstsw	%ax
	fstp	%st(1)
	andb	$69, %ah
	cmpb	$64, %ah
	je	.L44
	fdivr	%st, %st(3)
	fdivr	%st, %st(2)
	fdivrp	%st, %st(1)
	fxch	%st(2)
	fstps	(%esi)
	fstps	4(%esi)
	fstps	8(%esi)
	jmp	.L43
.L44:
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
.L43:
	movl	-4(%ebp), %esi
	leave
	ret
.LFE9:
.Lfe9:
	.size	 Normalize__Q23UDP7VVector,.Lfe9-Normalize__Q23UDP7VVector
	.align 4
.globl AngleWith__Q23UDP7VVectorRQ23UDP7VVector
	.type	 AngleWith__Q23UDP7VVectorRQ23UDP7VVector,@function
AngleWith__Q23UDP7VVectorRQ23UDP7VVector:
.LFB10:
	pushl	%ebp
.LCFI32:
	movl	%esp, %ebp
.LCFI33:
	pushl	%esi
.LCFI34:
	pushl	%ebx
.LCFI35:
	subl	$24, %esp
.LCFI36:
	movl	12(%ebp), %esi
	movl	8(%ebp), %ebx
	pushl	%esi
	pushl	%ebx
.LCFI37:
	call	__ml__CQ23UDP7VVectorRCQ23UDP7VVector
	fstps	-12(%ebp)
	movl	%ebx, (%esp)
	call	Length__Q23UDP7VVector
	fstps	-16(%ebp)
	movl	%esi, (%esp)
	call	Length__Q23UDP7VVector
	fmuls	-16(%ebp)
	fstps	-16(%ebp)
	flds	-12(%ebp)
	fdivs	-16(%ebp)
	fstps	8(%ebp)
	addl	$16, %esp
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
.LCFI38:
	jmp	ACos__Q23UDP5VMathf
.LFE10:
.Lfe10:
	.size	 AngleWith__Q23UDP7VVectorRQ23UDP7VVector,.Lfe10-AngleWith__Q23UDP7VVectorRQ23UDP7VVector
	.align 4
.globl RotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix
	.type	 RotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix,@function
RotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix:
.LFB11:
	pushl	%ebp
.LCFI39:
	movl	%esp, %ebp
.LCFI40:
	pushl	%edi
.LCFI41:
	pushl	%esi
.LCFI42:
	pushl	%ebx
.LCFI43:
	subl	$20, %esp
.LCFI44:
	pushl	$0
	pushl	12(%ebp)
.LCFI45:
	call	__vc__CQ23UDP7VMatrixUi
	popl	%edi
	movl	%eax, %esi
	popl	%eax
	pushl	$1
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%ecx
	popl	%ebx
	pushl	$2
	movl	%eax, %edi
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	movl	8(%ebp), %edx
	flds	(%edx)
	fmuls	(%esi)
	fstps	-16(%ebp)
	flds	4(%edx)
	fmuls	(%edi)
	fadds	-16(%ebp)
	fstps	-16(%ebp)
	flds	8(%edx)
	fmuls	(%eax)
	popl	%eax
	popl	%edx
	fadds	-16(%ebp)
	pushl	$0
	fstps	-16(%ebp)
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%esi
	popl	%edi
	pushl	$1
	movl	%eax, %ebx
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%edx
	popl	%ecx
	pushl	$2
	movl	%eax, %edi
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	movl	8(%ebp), %edx
	flds	(%edx)
	fmuls	4(%ebx)
	fstps	-20(%ebp)
	flds	4(%edx)
	fmuls	4(%edi)
	fadds	-20(%ebp)
	fstps	-20(%ebp)
	flds	8(%edx)
	popl	%edi
	fmuls	4(%eax)
	popl	%eax
	fadds	-20(%ebp)
	pushl	$0
	fstps	-20(%ebp)
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%ebx
	popl	%esi
	pushl	$1
	pushl	12(%ebp)
	movl	%eax, -24(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%edx
	popl	%ecx
	pushl	$2
	movl	%eax, %edi
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	movl	8(%ebp), %edx
	flds	(%edx)
	movl	-24(%ebp), %edx
	fmuls	8(%edx)
	movl	8(%ebp), %edx
	flds	4(%edx)
	fmuls	8(%edi)
	faddp	%st, %st(1)
	flds	8(%edx)
	fmuls	8(%eax)
	faddp	%st, %st(1)
	flds	-16(%ebp)
	fstps	(%edx)
	flds	-20(%ebp)
	fstps	4(%edx)
	fstps	8(%edx)
	addl	$16, %esp
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.LFE11:
.Lfe11:
	.size	 RotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix,.Lfe11-RotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix
	.align 4
.globl InvRotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix
	.type	 InvRotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix,@function
InvRotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix:
.LFB12:
	pushl	%ebp
.LCFI46:
	movl	%esp, %ebp
.LCFI47:
	pushl	%edi
.LCFI48:
	pushl	%esi
.LCFI49:
	pushl	%ebx
.LCFI50:
	subl	$20, %esp
.LCFI51:
	pushl	$0
	pushl	12(%ebp)
.LCFI52:
	call	__vc__CQ23UDP7VMatrixUi
	popl	%edi
	movl	%eax, %esi
	popl	%eax
	pushl	$0
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%ecx
	popl	%ebx
	pushl	$0
	movl	%eax, %edi
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	movl	8(%ebp), %edx
	flds	(%edx)
	fmuls	(%esi)
	fstps	-16(%ebp)
	flds	4(%edx)
	fmuls	4(%edi)
	fadds	-16(%ebp)
	fstps	-16(%ebp)
	flds	8(%edx)
	fmuls	8(%eax)
	popl	%eax
	popl	%edx
	fadds	-16(%ebp)
	pushl	$1
	fstps	-16(%ebp)
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%esi
	popl	%edi
	pushl	$1
	movl	%eax, %ebx
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%edx
	popl	%ecx
	pushl	$1
	movl	%eax, %edi
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	movl	8(%ebp), %edx
	flds	(%edx)
	fmuls	(%ebx)
	fstps	-20(%ebp)
	flds	4(%edx)
	fmuls	4(%edi)
	fadds	-20(%ebp)
	fstps	-20(%ebp)
	flds	8(%edx)
	popl	%edi
	fmuls	8(%eax)
	popl	%eax
	fadds	-20(%ebp)
	pushl	$2
	fstps	-20(%ebp)
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%ebx
	popl	%esi
	pushl	$2
	pushl	12(%ebp)
	movl	%eax, -24(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	popl	%edx
	popl	%ecx
	pushl	$2
	movl	%eax, %edi
	pushl	12(%ebp)
	call	__vc__CQ23UDP7VMatrixUi
	movl	8(%ebp), %edx
	flds	(%edx)
	movl	-24(%ebp), %edx
	fmuls	(%edx)
	movl	8(%ebp), %edx
	flds	4(%edx)
	fmuls	4(%edi)
	faddp	%st, %st(1)
	flds	8(%edx)
	fmuls	8(%eax)
	faddp	%st, %st(1)
	flds	-16(%ebp)
	fstps	(%edx)
	flds	-20(%ebp)
	fstps	4(%edx)
	fstps	8(%edx)
	addl	$16, %esp
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.LFE12:
.Lfe12:
	.size	 InvRotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix,.Lfe12-InvRotateWith__Q23UDP7VVectorRCQ23UDP7VMatrix
	.align 4
.globl Difference__Q23UDP7VVectorRCQ23UDP7VVectorT1
	.type	 Difference__Q23UDP7VVectorRCQ23UDP7VVectorT1,@function
Difference__Q23UDP7VVectorRCQ23UDP7VVectorT1:
.LFB13:
	pushl	%ebp
.LCFI53:
	movl	%esp, %ebp
.LCFI54:
	movl	12(%ebp), %eax
	flds	(%eax)
	movl	16(%ebp), %edx
	movl	8(%ebp), %ecx
	fsubrs	(%edx)
	fstps	(%ecx)
	flds	4(%eax)
	fsubrs	4(%edx)
	fstps	4(%ecx)
	flds	8(%eax)
	fsubrs	8(%edx)
	fstps	8(%ecx)
	movl	$0x3f800000, 12(%ecx)
	popl	%ebp
	ret
.LFE13:
.Lfe13:
	.size	 Difference__Q23UDP7VVectorRCQ23UDP7VVectorT1,.Lfe13-Difference__Q23UDP7VVectorRCQ23UDP7VVectorT1
	.align 4
.globl CrossProduct__CQ23UDP7VVectorRCQ23UDP7VVector
	.type	 CrossProduct__CQ23UDP7VVectorRCQ23UDP7VVector,@function
CrossProduct__CQ23UDP7VVectorRCQ23UDP7VVector:
.LFB14:
	pushl	%ebp
.LCFI55:
	movl	%esp, %ebp
.LCFI56:
	pushl	%edi
.LCFI57:
	pushl	%esi
.LCFI58:
	pushl	%ebx
.LCFI59:
	subl	$44, %esp
.LCFI60:
	pushl	$0x0
	pushl	$0x0
	pushl	$0x0
	leal	-56(%ebp), %edi
	pushl	%edi
	movl	8(%ebp), %esi
	movl	16(%ebp), %ebx
.LCFI61:
	call	__Q23UDP7VVectorfff
	addl	$12, %esp
.LEHB54:
	pushl	%ebx
	pushl	12(%ebp)
	pushl	%edi
	call	Cross__Q23UDP7VVectorRCQ23UDP7VVectorT1
	popl	%edx
	popl	%ecx
	pushl	%edi
	pushl	%esi
	call	__Q23UDP7VVectorRCQ23UDP7VVector
	subl	$8, %esp
	pushl	$2
	pushl	%edi
	call	_._Q23UDP7VVector
	addl	$16, %esp
	jmp	.L53
	.p2align 2
.L54:
.LEHE54:
	subl	$8, %esp
	pushl	$2
	leal	-56(%ebp), %eax
	pushl	%eax
	call	_._Q23UDP7VVector
	subl	$12, %esp
	pushl	$.LRTH54
	call	__rethrow
	.p2align 2
.L53:
	leal	-12(%ebp), %esp
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%edi
	popl	%ebp
	ret	$4
.LFE14:
.Lfe14:
	.size	 CrossProduct__CQ23UDP7VVectorRCQ23UDP7VVector,.Lfe14-CrossProduct__CQ23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl Cross__Q23UDP7VVectorRCQ23UDP7VVectorT1
	.type	 Cross__Q23UDP7VVectorRCQ23UDP7VVectorT1,@function
Cross__Q23UDP7VVectorRCQ23UDP7VVectorT1:
.LFB15:
	pushl	%ebp
.LCFI62:
	movl	%esp, %ebp
.LCFI63:
	pushl	%edi
.LCFI64:
	pushl	%esi
.LCFI65:
	pushl	%ebx
.LCFI66:
	subl	$12, %esp
.LCFI67:
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	16(%ebp), %edi
	call	HaveSSE__Q23UDP4VCPU
	testb	%al, %al
	je	.L60
#APP
	movups	(%ebx),		%xmm0
	movups	(%edi),		%xmm1
	movaps	%xmm0,		%xmm2
	movaps	%xmm1,		%xmm3
	shufps	$0xC9,		%xmm0,	%xmm0
	shufps	$0xD2,		%xmm1,	%xmm1
	mulps	%xmm1,		%xmm0
	shufps	$0xD2,		%xmm2,	%xmm2
	shufps	$0xC9,		%xmm3,	%xmm3
	mulps	%xmm3,		%xmm2
	subps	%xmm2,		%xmm0
	movups	%xmm0,		(%esi)
	
#NO_APP
	jmp	.L63
	.p2align 2
.L60:
	flds	4(%ebx)
	flds	8(%ebx)
	fmuls	4(%edi)
	fxch	%st(1)
	fmuls	8(%edi)
	fsubp	%st, %st(1)
	fstps	(%esi)
	flds	8(%ebx)
	flds	(%ebx)
	fmuls	8(%edi)
	fxch	%st(1)
	fmuls	(%edi)
	fsubp	%st, %st(1)
	fstps	4(%esi)
	flds	(%ebx)
	flds	4(%ebx)
	fxch	%st(1)
	fmuls	4(%edi)
	fxch	%st(1)
	fmuls	(%edi)
	fsubrp	%st, %st(1)
	fstps	8(%esi)
.L63:
	movl	$0x3f800000, 12(%esi)
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.LFE15:
.Lfe15:
	.size	 Cross__Q23UDP7VVectorRCQ23UDP7VVectorT1,.Lfe15-Cross__Q23UDP7VVectorRCQ23UDP7VVectorT1
	.align 4
.globl DotProduct__CQ23UDP7VVectorRCQ23UDP7VVector
	.type	 DotProduct__CQ23UDP7VVectorRCQ23UDP7VVector,@function
DotProduct__CQ23UDP7VVectorRCQ23UDP7VVector:
.LFB16:
	pushl	%ebp
.LCFI68:
	movl	%esp, %ebp
.LCFI69:
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	flds	(%eax)
	flds	4(%eax)
	fmuls	4(%edx)
	fxch	%st(1)
	fmuls	(%edx)
	faddp	%st, %st(1)
	flds	8(%eax)
	fmuls	8(%edx)
	faddp	%st, %st(1)
	popl	%ebp
	ret
.LFE16:
.Lfe16:
	.size	 DotProduct__CQ23UDP7VVectorRCQ23UDP7VVector,.Lfe16-DotProduct__CQ23UDP7VVectorRCQ23UDP7VVector
	.section	.rodata.cst8,"am",@progbits,8
	.align 8
.LC12:
	.long	0x0,0x3fe00000
.text
	.align 4
.globl GetRotationTo__CQ23UDP7VVectorRCQ23UDP7VVector
	.type	 GetRotationTo__CQ23UDP7VVectorRCQ23UDP7VVector,@function
GetRotationTo__CQ23UDP7VVectorRCQ23UDP7VVector:
.LFB17:
	pushl	%ebp
.LCFI70:
	movl	%esp, %ebp
.LCFI71:
	pushl	%edi
.LCFI72:
	pushl	%esi
.LCFI73:
	pushl	%ebx
.LCFI74:
	subl	$164, %esp
.LCFI75:
	pushl	12(%ebp)
	leal	-56(%ebp), %esi
	pushl	%esi
	movl	16(%ebp), %ebx
.LCFI76:
	call	__Q23UDP7VVectorRCQ23UDP7VVector
	popl	%edx
	popl	%ecx
.LEHB67:
	pushl	%ebx
	leal	-88(%ebp), %ebx
	pushl	%ebx
	call	__Q23UDP7VVectorRCQ23UDP7VVector
.LEHB68:
	movl	%esi, (%esp)
	call	Normalize__Q23UDP7VVector
	movl	%ebx, (%esp)
	call	Normalize__Q23UDP7VVector
	addl	$12, %esp
	pushl	%ebx
	leal	-120(%ebp), %edi
	pushl	%esi
	pushl	%edi
	call	CrossProduct__CQ23UDP7VVectorRCQ23UDP7VVector
.LEHB69:
	movl	%ebx, (%esp)
	pushl	%esi
	call	DotProduct__CQ23UDP7VVectorRCQ23UDP7VVector
	fld1
	fxch	%st(1)
	fucom	%st(1)
	fnstsw	%ax
	addl	$16, %esp
	testb	$5, %ah
	jne	.L70
	fstp	%st(0)
	fstp	%st(0)
	subl	$8, %esp
	pushl	$_Q23UDP5VMath.QUATERNION_IDENTITY
	pushl	8(%ebp)
	call	__Q23UDP11VQuaternionRCQ23UDP11VQuaternion
	subl	$8, %esp
	pushl	$2
	pushl	%edi
	call	_._Q23UDP7VVector
	popl	%edi
	popl	%eax
	pushl	$2
	pushl	%ebx
	call	_._Q23UDP7VVector
	popl	%edx
	popl	%ecx
	pushl	$2
	pushl	%esi
	call	_._Q23UDP7VVector
	addl	$16, %esp
	jmp	.L66
	.p2align 2
.L70:
	fld	%st(1)
	faddp	%st, %st(1)
	fadd	%st(0), %st
#APP
	fsqrt
#NO_APP
	fdivr	%st, %st(1)
	flds	-112(%ebp)
	subl	$28, %esp
	fmul	%st(2), %st
	fstps	12(%esp)
	flds	-116(%ebp)
	fmul	%st(2), %st
	fstps	8(%esp)
	flds	-120(%ebp)
	fmulp	%st, %st(2)
	fxch	%st(1)
	fstps	4(%esp)
	fldl	.LC12
	fmulp	%st, %st(1)
	fstps	-156(%ebp)
	flds	-156(%ebp)
	leal	-152(%ebp), %ebx
	fstps	(%esp)
	pushl	%ebx
.LCFI77:
	call	__Q23UDP11VQuaternionffff
	addl	$24, %esp
.LEHB78:
	pushl	%ebx
	pushl	8(%ebp)
.LCFI78:
	call	__Q23UDP11VQuaternionRCQ23UDP11VQuaternion
	subl	$8, %esp
	pushl	$2
	leal	-120(%ebp), %eax
	pushl	%eax
	movl	$__vt_Q23UDP11VQuaternion, -136(%ebp)
	call	_._Q23UDP7VVector
	popl	%edi
	popl	%eax
	pushl	$2
	leal	-88(%ebp), %eax
	pushl	%eax
	call	_._Q23UDP7VVector
	popl	%ebx
	popl	%esi
	pushl	$2
	leal	-56(%ebp), %eax
	pushl	%eax
	call	_._Q23UDP7VVector
	addl	$16, %esp
	jmp	.L66
	.p2align 2
.L78:
.LEHE78:
.LEHE69:
.LEHE68:
.LEHE67:
	subl	$12, %esp
	movl	$__vt_Q23UDP11VQuaternion, -136(%ebp)
	pushl	$.LRTH78
	call	__rethrow
.L69:
	subl	$8, %esp
	pushl	$2
	leal	-120(%ebp), %eax
	pushl	%eax
	call	_._Q23UDP7VVector
	subl	$12, %esp
	pushl	$.LRTH69
	call	__rethrow
.L68:
	subl	$8, %esp
	pushl	$2
	leal	-88(%ebp), %eax
	pushl	%eax
	call	_._Q23UDP7VVector
	subl	$12, %esp
	pushl	$.LRTH68
	call	__rethrow
.L67:
	subl	$8, %esp
	pushl	$2
	leal	-56(%ebp), %eax
	pushl	%eax
	call	_._Q23UDP7VVector
	subl	$12, %esp
	pushl	$.LRTH67
	call	__rethrow
	.p2align 2
.L66:
	movl	8(%ebp), %eax
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret	$4
.LFE17:
.Lfe17:
	.size	 GetRotationTo__CQ23UDP7VVectorRCQ23UDP7VVector,.Lfe17-GetRotationTo__CQ23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl __as__Q23UDP7VVectorRCQ23UDP7VVector
	.type	 __as__Q23UDP7VVectorRCQ23UDP7VVector,@function
__as__Q23UDP7VVectorRCQ23UDP7VVector:
.LFB18:
	pushl	%ebp
.LCFI79:
	movl	%esp, %ebp
.LCFI80:
	movl	12(%ebp), %ecx
	movl	8(%ebp), %eax
	movl	(%ecx), %edx
	movl	%edx, (%eax)
	movl	4(%ecx), %edx
	movl	%edx, 4(%eax)
	movl	8(%ecx), %edx
	movl	%edx, 8(%eax)
	popl	%ebp
	ret
.LFE18:
.Lfe18:
	.size	 __as__Q23UDP7VVectorRCQ23UDP7VVector,.Lfe18-__as__Q23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl __eq__CQ23UDP7VVectorRCQ23UDP7VVector
	.type	 __eq__CQ23UDP7VVectorRCQ23UDP7VVector,@function
__eq__CQ23UDP7VVectorRCQ23UDP7VVector:
.LFB19:
	pushl	%ebp
.LCFI81:
	movl	%esp, %ebp
.LCFI82:
	movl	8(%ebp), %edx
	pushl	%ebx
.LCFI83:
	movl	12(%ebp), %ecx
	flds	(%edx)
	flds	(%ecx)
	fxch	%st(1)
	fucompp
	fnstsw	%ax
	andb	$69, %ah
	xorl	%ebx, %ebx
	xorb	$64, %ah
	jne	.L100
	flds	4(%edx)
	flds	8(%ecx)
	fxch	%st(1)
	fucomp	%st(1)
	fnstsw	%ax
	andb	$69, %ah
	xorb	$64, %ah
	jne	.L105
	flds	8(%edx)
	fucompp
	fnstsw	%ax
	andb	$69, %ah
	xorb	$64, %ah
	jne	.L100
	movb	$1, %bl
	jmp	.L100
.L105:
	fstp	%st(0)
.L100:
	movb	%bl, %al
	movl	(%esp), %ebx
	leave
	ret
.LFE19:
.Lfe19:
	.size	 __eq__CQ23UDP7VVectorRCQ23UDP7VVector,.Lfe19-__eq__CQ23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl __ne__CQ23UDP7VVectorRCQ23UDP7VVector
	.type	 __ne__CQ23UDP7VVectorRCQ23UDP7VVector,@function
__ne__CQ23UDP7VVectorRCQ23UDP7VVector:
.LFB20:
	pushl	%ebp
.LCFI84:
	movl	%esp, %ebp
.LCFI85:
	subl	$16, %esp
.LCFI86:
	pushl	12(%ebp)
	pushl	8(%ebp)
.LCFI87:
	call	__eq__CQ23UDP7VVectorRCQ23UDP7VVector
	xorl	$1, %eax
	leave
	ret
.LFE20:
.Lfe20:
	.size	 __ne__CQ23UDP7VVectorRCQ23UDP7VVector,.Lfe20-__ne__CQ23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl __apl__Q23UDP7VVectorRCQ23UDP7VVector
	.type	 __apl__Q23UDP7VVectorRCQ23UDP7VVector,@function
__apl__Q23UDP7VVectorRCQ23UDP7VVector:
.LFB21:
	pushl	%ebp
.LCFI88:
	movl	%esp, %ebp
.LCFI89:
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	flds	(%eax)
	fadds	(%edx)
	fstps	(%eax)
	flds	4(%eax)
	fadds	4(%edx)
	fstps	4(%eax)
	flds	8(%eax)
	fadds	8(%edx)
	fstps	8(%eax)
	popl	%ebp
	ret
.LFE21:
.Lfe21:
	.size	 __apl__Q23UDP7VVectorRCQ23UDP7VVector,.Lfe21-__apl__Q23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl __ami__Q23UDP7VVectorRCQ23UDP7VVector
	.type	 __ami__Q23UDP7VVectorRCQ23UDP7VVector,@function
__ami__Q23UDP7VVectorRCQ23UDP7VVector:
.LFB22:
	pushl	%ebp
.LCFI90:
	movl	%esp, %ebp
.LCFI91:
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	flds	(%edx)
	fsubrs	(%eax)
	fstps	(%eax)
	flds	4(%edx)
	fsubrs	4(%eax)
	fstps	4(%eax)
	flds	8(%edx)
	fsubrs	8(%eax)
	fstps	8(%eax)
	popl	%ebp
	ret
.LFE22:
.Lfe22:
	.size	 __ami__Q23UDP7VVectorRCQ23UDP7VVector,.Lfe22-__ami__Q23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl __aml__Q23UDP7VVectorRCf
	.type	 __aml__Q23UDP7VVectorRCf,@function
__aml__Q23UDP7VVectorRCf:
.LFB23:
	pushl	%ebp
.LCFI92:
	movl	%esp, %ebp
.LCFI93:
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	flds	(%eax)
	fmuls	(%edx)
	fstps	(%eax)
	flds	4(%eax)
	fmuls	(%edx)
	fstps	4(%eax)
	flds	8(%eax)
	fmuls	(%edx)
	fstps	8(%eax)
	popl	%ebp
	ret
.LFE23:
.Lfe23:
	.size	 __aml__Q23UDP7VVectorRCf,.Lfe23-__aml__Q23UDP7VVectorRCf
	.align 4
.globl __adv__Q23UDP7VVectorRCf
	.type	 __adv__Q23UDP7VVectorRCf,@function
__adv__Q23UDP7VVectorRCf:
.LFB24:
	pushl	%ebp
.LCFI94:
	movl	%esp, %ebp
.LCFI95:
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	flds	(%edx)
	fdivrs	(%eax)
	fstps	(%eax)
	flds	(%edx)
	fdivrs	4(%eax)
	fstps	4(%eax)
	flds	(%edx)
	fdivrs	8(%eax)
	fstps	8(%eax)
	popl	%ebp
	ret
.LFE24:
.Lfe24:
	.size	 __adv__Q23UDP7VVectorRCf,.Lfe24-__adv__Q23UDP7VVectorRCf
	.align 4
.globl __apl__Q23UDP7VVectorRCf
	.type	 __apl__Q23UDP7VVectorRCf,@function
__apl__Q23UDP7VVectorRCf:
.LFB25:
	pushl	%ebp
.LCFI96:
	movl	%esp, %ebp
.LCFI97:
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	flds	(%eax)
	fadds	(%edx)
	fstps	(%eax)
	flds	4(%eax)
	fadds	(%edx)
	fstps	4(%eax)
	flds	8(%eax)
	fadds	(%edx)
	fstps	8(%eax)
	popl	%ebp
	ret
.LFE25:
.Lfe25:
	.size	 __apl__Q23UDP7VVectorRCf,.Lfe25-__apl__Q23UDP7VVectorRCf
	.align 4
.globl __ami__Q23UDP7VVectorRCf
	.type	 __ami__Q23UDP7VVectorRCf,@function
__ami__Q23UDP7VVectorRCf:
.LFB26:
	pushl	%ebp
.LCFI98:
	movl	%esp, %ebp
.LCFI99:
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	flds	(%edx)
	fsubrs	(%eax)
	fstps	(%eax)
	flds	(%edx)
	fsubrs	4(%eax)
	fstps	4(%eax)
	flds	(%edx)
	fsubrs	8(%eax)
	fstps	8(%eax)
	popl	%ebp
	ret
.LFE26:
.Lfe26:
	.size	 __ami__Q23UDP7VVectorRCf,.Lfe26-__ami__Q23UDP7VVectorRCf
	.align 4
.globl __ml__CQ23UDP7VVectorRCQ23UDP7VVector
	.type	 __ml__CQ23UDP7VVectorRCQ23UDP7VVector,@function
__ml__CQ23UDP7VVectorRCQ23UDP7VVector:
.LFB27:
	pushl	%ebp
.LCFI100:
	movl	%esp, %ebp
.LCFI101:
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	flds	(%eax)
	flds	4(%eax)
	fmuls	4(%edx)
	fxch	%st(1)
	fmuls	(%edx)
	faddp	%st, %st(1)
	flds	8(%eax)
	fmuls	8(%edx)
	faddp	%st, %st(1)
	popl	%ebp
	ret
.LFE27:
.Lfe27:
	.size	 __ml__CQ23UDP7VVectorRCQ23UDP7VVector,.Lfe27-__ml__CQ23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl __ml__CQ23UDP7VVectorRCf
	.type	 __ml__CQ23UDP7VVectorRCf,@function
__ml__CQ23UDP7VVectorRCf:
.LFB28:
	pushl	%ebp
.LCFI102:
	movl	%esp, %ebp
.LCFI103:
	pushl	%ebx
.LCFI104:
	subl	$16, %esp
.LCFI105:
	movl	12(%ebp), %eax
	flds	8(%eax)
	movl	16(%ebp), %edx
	fmuls	(%edx)
	fstps	8(%esp)
	flds	4(%eax)
	fmuls	(%edx)
	fstps	4(%esp)
	flds	(%eax)
	movl	8(%ebp), %ebx
	fmuls	(%edx)
	fstps	(%esp)
	pushl	%ebx
.LCFI106:
	call	__Q23UDP7VVectorfff
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret	$4
.LFE28:
.Lfe28:
	.size	 __ml__CQ23UDP7VVectorRCf,.Lfe28-__ml__CQ23UDP7VVectorRCf
	.align 4
.globl __dv__CQ23UDP7VVectorRCf
	.type	 __dv__CQ23UDP7VVectorRCf,@function
__dv__CQ23UDP7VVectorRCf:
.LFB29:
	pushl	%ebp
.LCFI107:
	movl	%esp, %ebp
.LCFI108:
	pushl	%ebx
.LCFI109:
	subl	$16, %esp
.LCFI110:
	movl	16(%ebp), %eax
	flds	(%eax)
	movl	12(%ebp), %edx
	fdivrs	8(%edx)
	fstps	8(%esp)
	flds	(%eax)
	fdivrs	4(%edx)
	fstps	4(%esp)
	flds	(%eax)
	movl	8(%ebp), %ebx
	fdivrs	(%edx)
	fstps	(%esp)
	pushl	%ebx
.LCFI111:
	call	__Q23UDP7VVectorfff
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret	$4
.LFE29:
.Lfe29:
	.size	 __dv__CQ23UDP7VVectorRCf,.Lfe29-__dv__CQ23UDP7VVectorRCf
	.align 4
.globl __pl__CQ23UDP7VVectorRCf
	.type	 __pl__CQ23UDP7VVectorRCf,@function
__pl__CQ23UDP7VVectorRCf:
.LFB30:
	pushl	%ebp
.LCFI112:
	movl	%esp, %ebp
.LCFI113:
	pushl	%ebx
.LCFI114:
	subl	$16, %esp
.LCFI115:
	movl	12(%ebp), %eax
	flds	8(%eax)
	movl	16(%ebp), %edx
	fadds	(%edx)
	fstps	8(%esp)
	flds	4(%eax)
	fadds	(%edx)
	fstps	4(%esp)
	flds	(%eax)
	movl	8(%ebp), %ebx
	fadds	(%edx)
	fstps	(%esp)
	pushl	%ebx
.LCFI116:
	call	__Q23UDP7VVectorfff
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret	$4
.LFE30:
.Lfe30:
	.size	 __pl__CQ23UDP7VVectorRCf,.Lfe30-__pl__CQ23UDP7VVectorRCf
	.align 4
.globl __mi__CQ23UDP7VVectorRCf
	.type	 __mi__CQ23UDP7VVectorRCf,@function
__mi__CQ23UDP7VVectorRCf:
.LFB31:
	pushl	%ebp
.LCFI117:
	movl	%esp, %ebp
.LCFI118:
	pushl	%ebx
.LCFI119:
	subl	$16, %esp
.LCFI120:
	movl	16(%ebp), %eax
	flds	(%eax)
	movl	12(%ebp), %edx
	fsubrs	8(%edx)
	fstps	8(%esp)
	flds	(%eax)
	fsubrs	4(%edx)
	fstps	4(%esp)
	flds	(%eax)
	movl	8(%ebp), %ebx
	fsubrs	(%edx)
	fstps	(%esp)
	pushl	%ebx
.LCFI121:
	call	__Q23UDP7VVectorfff
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret	$4
.LFE31:
.Lfe31:
	.size	 __mi__CQ23UDP7VVectorRCf,.Lfe31-__mi__CQ23UDP7VVectorRCf
	.align 4
.globl __ml__CQ23UDP7VVectorRCQ23UDP11VQuaternion
	.type	 __ml__CQ23UDP7VVectorRCQ23UDP11VQuaternion,@function
__ml__CQ23UDP7VVectorRCQ23UDP11VQuaternion:
.LFB32:
	pushl	%ebp
.LCFI122:
	movl	%esp, %ebp
.LCFI123:
	pushl	%ebx
.LCFI124:
	subl	$32, %esp
.LCFI125:
	movl	16(%ebp), %eax
	movl	12(%ebp), %edx
	flds	(%eax)
	flds	4(%eax)
	fmuls	4(%edx)
	fxch	%st(1)
	fmuls	(%edx)
	faddp	%st, %st(1)
	flds	8(%eax)
	fmuls	8(%edx)
	faddp	%st, %st(1)
	fchs
	fstps	12(%esp)
	flds	12(%eax)
	flds	4(%eax)
	fmuls	(%edx)
	fxch	%st(1)
	fmuls	8(%edx)
	faddp	%st, %st(1)
	flds	(%eax)
	fmuls	4(%edx)
	fsubrp	%st, %st(1)
	fstps	8(%esp)
	flds	12(%eax)
	flds	(%eax)
	fmuls	8(%edx)
	fxch	%st(1)
	fmuls	4(%edx)
	faddp	%st, %st(1)
	flds	8(%eax)
	fmuls	(%edx)
	fsubrp	%st, %st(1)
	fstps	4(%esp)
	flds	12(%eax)
	flds	8(%eax)
	fmuls	4(%edx)
	fxch	%st(1)
	fmuls	(%edx)
	faddp	%st, %st(1)
	flds	4(%eax)
	fmuls	8(%edx)
	movl	8(%ebp), %ebx
	fsubrp	%st, %st(1)
	fstps	(%esp)
	pushl	%ebx
.LCFI126:
	call	__Q23UDP11VQuaternionffff
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret	$4
.LFE32:
.Lfe32:
	.size	 __ml__CQ23UDP7VVectorRCQ23UDP11VQuaternion,.Lfe32-__ml__CQ23UDP7VVectorRCQ23UDP11VQuaternion
	.align 4
.globl __ml__CQ23UDP7VVectorRCQ23UDP7VMatrix
	.type	 __ml__CQ23UDP7VVectorRCQ23UDP7VMatrix,@function
__ml__CQ23UDP7VVectorRCQ23UDP7VMatrix:
.LFB33:
	pushl	%ebp
.LCFI127:
	movl	%esp, %ebp
.LCFI128:
	pushl	%edi
.LCFI129:
	pushl	%esi
.LCFI130:
	pushl	%ebx
.LCFI131:
	subl	$92, %esp
.LCFI132:
	pushl	$0x0
	pushl	$0x0
	leal	-56(%ebp), %eax
	pushl	$0x0
	movl	12(%ebp), %esi
	movl	16(%ebp), %ebx
	movl	%eax, -60(%ebp)
	pushl	%eax
.LCFI133:
	call	__Q23UDP7VVectorfff
	popl	%ecx
	popl	%edi
.LEHB133:
	pushl	$0
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	movl	%eax, -64(%ebp)
	popl	%eax
	popl	%edx
	pushl	$1
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	popl	%ecx
	popl	%edi
	pushl	$2
	movl	%eax, -68(%ebp)
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	movl	%eax, %edi
	popl	%eax
	popl	%edx
	pushl	$3
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	flds	(%esi)
	movl	-64(%ebp), %edx
	fmuls	(%edx)
	flds	4(%esi)
	movl	-68(%ebp), %edx
	fmuls	(%edx)
	faddp	%st, %st(1)
	flds	8(%esi)
	fmuls	(%edi)
	popl	%ecx
	popl	%edi
	faddp	%st, %st(1)
	fadds	(%eax)
	pushl	$0
	fstps	-56(%ebp)
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	movl	%eax, -72(%ebp)
	popl	%eax
	popl	%edx
	pushl	$1
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	popl	%ecx
	popl	%edi
	pushl	$2
	movl	%eax, -76(%ebp)
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	movl	%eax, %edi
	popl	%eax
	popl	%edx
	pushl	$3
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	flds	(%esi)
	movl	-72(%ebp), %edx
	fmuls	4(%edx)
	flds	4(%esi)
	movl	-76(%ebp), %edx
	fmuls	4(%edx)
	faddp	%st, %st(1)
	flds	8(%esi)
	fmuls	4(%edi)
	popl	%ecx
	popl	%edi
	faddp	%st, %st(1)
	fadds	4(%eax)
	pushl	$0
	fstps	-52(%ebp)
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	movl	%eax, -80(%ebp)
	popl	%eax
	popl	%edx
	pushl	$1
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	popl	%ecx
	popl	%edi
	pushl	$2
	movl	%eax, -84(%ebp)
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	movl	%eax, %edi
	popl	%eax
	popl	%edx
	pushl	$3
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	flds	(%esi)
	movl	-80(%ebp), %edx
	fmuls	8(%edx)
	flds	4(%esi)
	movl	-84(%ebp), %edx
	fmuls	8(%edx)
	faddp	%st, %st(1)
	flds	8(%esi)
	fmuls	8(%edi)
	popl	%ecx
	popl	%edi
	faddp	%st, %st(1)
	fadds	8(%eax)
	pushl	$0
	fstps	-48(%ebp)
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	movl	%eax, -88(%ebp)
	popl	%eax
	popl	%edx
	pushl	$1
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	popl	%ecx
	popl	%edi
	pushl	$3
	movl	%eax, -92(%ebp)
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	movl	%eax, %edi
	popl	%eax
	popl	%edx
	pushl	$3
	pushl	%ebx
	call	__vc__CQ23UDP7VMatrixUi
	flds	(%esi)
	movl	-88(%ebp), %edx
	fmuls	12(%edx)
	flds	4(%esi)
	movl	-92(%ebp), %edx
	fmuls	12(%edx)
	faddp	%st, %st(1)
	flds	8(%esi)
	fmuls	12(%edi)
	faddp	%st, %st(1)
	fadds	12(%eax)
	flds	-56(%ebp)
	fdiv	%st(1), %st
	popl	%ebx
	popl	%esi
	fstps	-56(%ebp)
	flds	-52(%ebp)
	fdiv	%st(1), %st
	fxch	%st(1)
	pushl	-60(%ebp)
	fdivrs	-48(%ebp)
	fxch	%st(1)
	fstps	-52(%ebp)
	fstps	-48(%ebp)
	pushl	8(%ebp)
	movl	$0x3f800000, -44(%ebp)
	call	__Q23UDP7VVectorRCQ23UDP7VVector
	subl	$8, %esp
	pushl	$2
	pushl	-60(%ebp)
	call	_._Q23UDP7VVector
	addl	$16, %esp
	jmp	.L132
	.p2align 2
.L133:
.LEHE133:
	subl	$8, %esp
	pushl	$2
	leal	-56(%ebp), %eax
	pushl	%eax
	call	_._Q23UDP7VVector
	subl	$12, %esp
	pushl	$.LRTH133
	call	__rethrow
	.p2align 2
.L132:
	movl	8(%ebp), %eax
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret	$4
.LFE33:
.Lfe33:
	.size	 __ml__CQ23UDP7VVectorRCQ23UDP7VMatrix,.Lfe33-__ml__CQ23UDP7VVectorRCQ23UDP7VMatrix
	.align 4
.globl __pl__CQ23UDP7VVectorRCQ23UDP7VVector
	.type	 __pl__CQ23UDP7VVectorRCQ23UDP7VVector,@function
__pl__CQ23UDP7VVectorRCQ23UDP7VVector:
.LFB34:
	pushl	%ebp
.LCFI134:
	movl	%esp, %ebp
.LCFI135:
	pushl	%ebx
.LCFI136:
	subl	$16, %esp
.LCFI137:
	movl	12(%ebp), %eax
	flds	8(%eax)
	movl	16(%ebp), %edx
	fadds	8(%edx)
	fstps	8(%esp)
	flds	4(%eax)
	fadds	4(%edx)
	fstps	4(%esp)
	flds	(%eax)
	movl	8(%ebp), %ebx
	fadds	(%edx)
	fstps	(%esp)
	pushl	%ebx
.LCFI138:
	call	__Q23UDP7VVectorfff
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret	$4
.LFE34:
.Lfe34:
	.size	 __pl__CQ23UDP7VVectorRCQ23UDP7VVector,.Lfe34-__pl__CQ23UDP7VVectorRCQ23UDP7VVector
	.align 4
.globl __mi__CQ23UDP7VVectorRCQ23UDP7VVector
	.type	 __mi__CQ23UDP7VVectorRCQ23UDP7VVector,@function
__mi__CQ23UDP7VVectorRCQ23UDP7VVector:
.LFB35:
	pushl	%ebp
.LCFI139:
	movl	%esp, %ebp
.LCFI140:
	pushl	%ebx
.LCFI141:
	subl	$16, %esp
.LCFI142:
	movl	16(%ebp), %eax
	flds	8(%eax)
	movl	12(%ebp), %edx
	fsubrs	8(%edx)
	fstps	8(%esp)
	flds	4(%eax)
	fsubrs	4(%edx)
	fstps	4(%esp)
	flds	(%eax)
	movl	8(%ebp), %ebx
	fsubrs	(%edx)
	fstps	(%esp)
	pushl	%ebx
.LCFI143:
	call	__Q23UDP7VVectorfff
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret	$4
.LFE35:
.Lfe35:
	.size	 __mi__CQ23UDP7VVectorRCQ23UDP7VVector,.Lfe35-__mi__CQ23UDP7VVectorRCQ23UDP7VVector
	.weak	__vt_Q23UDP11VQuaternion
	.section	.gnu.linkonce.d.__vt_Q23UDP11VQuaternion,"aw",@progbits
	.align 8
	.type	 __vt_Q23UDP11VQuaternion,@object
	.size	 __vt_Q23UDP11VQuaternion,16
__vt_Q23UDP11VQuaternion:
	.long	0
	.long	__tfQ23UDP11VQuaternion
	.long	_._Q23UDP11VQuaternion
	.zero	4
	.weak	__vt_Q23UDP7VVector
	.section	.gnu.linkonce.d.__vt_Q23UDP7VVector,"aw",@progbits
	.align 8
	.type	 __vt_Q23UDP7VVector,@object
	.size	 __vt_Q23UDP7VVector,16
__vt_Q23UDP7VVector:
	.long	0
	.long	__tfQ23UDP7VVector
	.long	_._Q23UDP7VVector
	.zero	4
	.comm	__tiQ23UDP7VVector,8,4
	.section	.rodata.str1.1,"ams",@progbits,1
.LC30:
	.string	"Q23UDP7VVector"
	.comm	__tiQ23UDP11VQuaternion,8,4
.LC31:
	.string	"Q23UDP11VQuaternion"
	.section	.gnu.linkonce.t.__tfQ23UDP7VVector,"ax",@progbits
	.align 4
	.weak	__tfQ23UDP7VVector
	.type	 __tfQ23UDP7VVector,@function
__tfQ23UDP7VVector:
.LFB36:
	pushl	%ebp
.LCFI144:
	movl	%esp, %ebp
.LCFI145:
	subl	$8, %esp
.LCFI146:
	movl	__tiQ23UDP7VVector, %eax
	testl	%eax, %eax
	jne	.L143
	subl	$8, %esp
	pushl	$.LC30
	pushl	$__tiQ23UDP7VVector
.LCFI147:
	call	__rtti_user
	addl	$16, %esp
.L143:
	movl	$__tiQ23UDP7VVector, %eax
	leave
	ret
.LFE36:
.Lfe36:
	.size	 __tfQ23UDP7VVector,.Lfe36-__tfQ23UDP7VVector
	.section	.gnu.linkonce.t.__tfQ23UDP11VQuaternion,"ax",@progbits
	.align 4
	.weak	__tfQ23UDP11VQuaternion
	.type	 __tfQ23UDP11VQuaternion,@function
__tfQ23UDP11VQuaternion:
.LFB37:
	pushl	%ebp
.LCFI148:
	movl	%esp, %ebp
.LCFI149:
	subl	$8, %esp
.LCFI150:
	movl	__tiQ23UDP11VQuaternion, %edx
	testl	%edx, %edx
	jne	.L146
	subl	$8, %esp
	pushl	$.LC31
	pushl	$__tiQ23UDP11VQuaternion
.LCFI151:
	call	__rtti_user
	addl	$16, %esp
.L146:
	movl	$__tiQ23UDP11VQuaternion, %eax
	leave
	ret
.LFE37:
.Lfe37:
	.size	 __tfQ23UDP11VQuaternion,.Lfe37-__tfQ23UDP11VQuaternion
	.section	.gnu.linkonce.t._._Q23UDP11VQuaternion,"ax",@progbits
	.align 4
	.weak	_._Q23UDP11VQuaternion
	.type	 _._Q23UDP11VQuaternion,@function
_._Q23UDP11VQuaternion:
.LFB38:
	pushl	%ebp
.LCFI152:
	movl	%esp, %ebp
.LCFI153:
	subl	$8, %esp
.LCFI154:
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	andl	$1, %eax
	movl	$__vt_Q23UDP11VQuaternion, 16(%edx)
	je	.L151
	leave
.LCFI155:
	jmp	__builtin_delete
	.p2align 2
.L151:
	leave
	ret
.LFE38:
.Lfe38:
	.size	 _._Q23UDP11VQuaternion,.Lfe38-_._Q23UDP11VQuaternion
	.section	.gcc_except_table,"aw",@progbits
	.align 4
__EXCEPTION_TABLE__:
	.long	-2
	.value	4
	.value	1
.LRTH0:
.LRTH54:
	.long	.LEHB54
	.long	.LEHE54
	.long	.L54
	.long	0

.LRTH78:
	.long	.LEHB78
	.long	.LEHE78
	.long	.L78
	.long	0

.LRTH69:
	.long	.LEHB69
	.long	.LEHE69
	.long	.L69
	.long	0

.LRTH68:
	.long	.LEHB68
	.long	.LEHE68
	.long	.L68
	.long	0

.LRTH67:
	.long	.LEHB67
	.long	.LEHE67
	.long	.L67
	.long	0

.LRTH133:
	.long	.LEHB133
	.long	.LEHE133
	.long	.L133
	.long	0

.LRTH1:
	.long	-1


	.section	.eh_frame,"aw",@progbits
__FRAME_BEGIN__:
	.4byte	.LLCIE1
.LSCIE1:
	.4byte	0x0
	.byte	0x1
	.string	"eh"

	.4byte	__EXCEPTION_TABLE__
	.byte	0x1
	.byte	0x7c
	.byte	0x8
	.byte	0xc
	.byte	0x4
	.byte	0x4
	.byte	0x88
	.byte	0x1
	.align 4
.LECIE1:
	.set	.LLCIE1,.LECIE1-.LSCIE1
	.4byte	.LLFDE7
.LSFDE7:
	.4byte	.LSFDE7-__FRAME_BEGIN__
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.byte	0x4
	.4byte	.LCFI9-.LFB4
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI10-.LCFI9
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI11-.LCFI10
	.byte	0x87
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI12-.LCFI11
	.byte	0x86
	.byte	0x4
	.align 4
.LEFDE7:
	.set	.LLFDE7,.LEFDE7-.LSFDE7
	.4byte	.LLFDE11
.LSFDE11:
	.4byte	.LSFDE11-__FRAME_BEGIN__
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.byte	0x4
	.4byte	.LCFI16-.LFB6
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI17-.LCFI16
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI18-.LCFI17
	.byte	0x86
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI19-.LCFI18
	.byte	0x83
	.byte	0x4
	.byte	0x4
	.4byte	.LCFI21-.LCFI19
	.byte	0x2e
	.byte	0xc
	.byte	0x4
	.4byte	.LCFI22-.LCFI21
	.byte	0x2e
	.byte	0x10
	.align 4
.LEFDE11:
	.set	.LLFDE11,.LEFDE11-.LSFDE11
	.4byte	.LLFDE17
.LSFDE17:
	.4byte	.LSFDE17-__FRAME_BEGIN__
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.byte	0x4
	.4byte	.LCFI29-.LFB9
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI30-.LCFI29
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI31-.LCFI30
	.byte	0x86
	.byte	0x3
	.align 4
.LEFDE17:
	.set	.LLFDE17,.LEFDE17-.LSFDE17
	.4byte	.LLFDE19
.LSFDE19:
	.4byte	.LSFDE19-__FRAME_BEGIN__
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.byte	0x4
	.4byte	.LCFI32-.LFB10
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI33-.LCFI32
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI34-.LCFI33
	.byte	0x86
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI35-.LCFI34
	.byte	0x83
	.byte	0x4
	.byte	0x4
	.4byte	.LCFI37-.LCFI35
	.byte	0x2e
	.byte	0x10
	.byte	0x4
	.4byte	.LCFI38-.LCFI37
	.byte	0x2e
	.byte	0x4
	.align 4
.LEFDE19:
	.set	.LLFDE19,.LEFDE19-.LSFDE19
	.4byte	.LLFDE21
.LSFDE21:
	.4byte	.LSFDE21-__FRAME_BEGIN__
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.byte	0x4
	.4byte	.LCFI39-.LFB11
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI40-.LCFI39
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI41-.LCFI40
	.byte	0x87
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI42-.LCFI41
	.byte	0x86
	.byte	0x4
	.byte	0x4
	.4byte	.LCFI43-.LCFI42
	.byte	0x83
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI45-.LCFI43
	.byte	0x2e
	.byte	0x10
	.align 4
.LEFDE21:
	.set	.LLFDE21,.LEFDE21-.LSFDE21
	.4byte	.LLFDE23
.LSFDE23:
	.4byte	.LSFDE23-__FRAME_BEGIN__
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.byte	0x4
	.4byte	.LCFI46-.LFB12
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI47-.LCFI46
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI48-.LCFI47
	.byte	0x87
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI49-.LCFI48
	.byte	0x86
	.byte	0x4
	.byte	0x4
	.4byte	.LCFI50-.LCFI49
	.byte	0x83
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI52-.LCFI50
	.byte	0x2e
	.byte	0x10
	.align 4
.LEFDE23:
	.set	.LLFDE23,.LEFDE23-.LSFDE23
	.4byte	.LLFDE27
.LSFDE27:
	.4byte	.LSFDE27-__FRAME_BEGIN__
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.byte	0x4
	.4byte	.LCFI55-.LFB14
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI56-.LCFI55
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI57-.LCFI56
	.byte	0x87
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI58-.LCFI57
	.byte	0x86
	.byte	0x4
	.byte	0x4
	.4byte	.LCFI59-.LCFI58
	.byte	0x83
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI61-.LCFI59
	.byte	0x2e
	.byte	0x10
	.align 4
.LEFDE27:
	.set	.LLFDE27,.LEFDE27-.LSFDE27
	.4byte	.LLFDE29
.LSFDE29:
	.4byte	.LSFDE29-__FRAME_BEGIN__
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.byte	0x4
	.4byte	.LCFI62-.LFB15
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI63-.LCFI62
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI64-.LCFI63
	.byte	0x87
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI65-.LCFI64
	.byte	0x86
	.byte	0x4
	.byte	0x4
	.4byte	.LCFI66-.LCFI65
	.byte	0x83
	.byte	0x5
	.align 4
.LEFDE29:
	.set	.LLFDE29,.LEFDE29-.LSFDE29
	.4byte	.LLFDE33
.LSFDE33:
	.4byte	.LSFDE33-__FRAME_BEGIN__
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.byte	0x4
	.4byte	.LCFI70-.LFB17
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI71-.LCFI70
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI72-.LCFI71
	.byte	0x87
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI73-.LCFI72
	.byte	0x86
	.byte	0x4
	.byte	0x4
	.4byte	.LCFI74-.LCFI73
	.byte	0x83
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI76-.LCFI74
	.byte	0x2e
	.byte	0x10
	.byte	0x4
	.4byte	.LCFI77-.LCFI76
	.byte	0x2e
	.byte	0x20
	.byte	0x4
	.4byte	.LCFI78-.LCFI77
	.byte	0x2e
	.byte	0x10
	.align 4
.LEFDE33:
	.set	.LLFDE33,.LEFDE33-.LSFDE33
	.4byte	.LLFDE63
.LSFDE63:
	.4byte	.LSFDE63-__FRAME_BEGIN__
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.byte	0x4
	.4byte	.LCFI122-.LFB32
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI123-.LCFI122
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI124-.LCFI123
	.byte	0x83
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI126-.LCFI124
	.byte	0x2e
	.byte	0x20
	.align 4
.LEFDE63:
	.set	.LLFDE63,.LEFDE63-.LSFDE63
	.4byte	.LLFDE65
.LSFDE65:
	.4byte	.LSFDE65-__FRAME_BEGIN__
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.byte	0x4
	.4byte	.LCFI127-.LFB33
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.4byte	.LCFI128-.LCFI127
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI129-.LCFI128
	.byte	0x87
	.byte	0x3
	.byte	0x4
	.4byte	.LCFI130-.LCFI129
	.byte	0x86
	.byte	0x4
	.byte	0x4
	.4byte	.LCFI131-.LCFI130
	.byte	0x83
	.byte	0x5
	.byte	0x4
	.4byte	.LCFI133-.LCFI131
	.byte	0x2e
	.byte	0x10
	.align 4
.LEFDE65:
	.set	.LLFDE65,.LEFDE65-.LSFDE65
	.ident	"GCC: (GNU) 2.96 20000731 (Red Hat Linux 7.1 2.96-98)"
