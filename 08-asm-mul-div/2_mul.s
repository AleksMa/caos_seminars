	.text
	.file	"2_mul.cpp"
	.globl	_Z4Mul3m                        # -- Begin function _Z4Mul3m
	.p2align	4, 0x90
	.type	_Z4Mul3m,@function
_Z4Mul3m:                               # @_Z4Mul3m
	.cfi_startproc
# %bb.0:
	leaq	(%rdi,%rdi,2), %rax
	retq
.Lfunc_end0:
	.size	_Z4Mul3m, .Lfunc_end0-_Z4Mul3m
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	movl	$30, %eax
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 18.1.3 (1ubuntu1)"
	.section	".note.GNU-stack","",@progbits
