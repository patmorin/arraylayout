	.file	"main.cpp"
	.section	.text.unlikely,"ax",@progbits
	.type	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc.part.7, @function
_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc.part.7:
.LFB4676:
	.cfi_startproc
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	(%rdi), %rax
	addq	-24(%rax), %rdi
	movl	32(%rdi), %esi
	orl	$1, %esi
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
	popq	%rdx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE4676:
	.size	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc.part.7, .-_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc.part.7
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"uint32"
	.text
	.p2align 4,,15
	.globl	_Z9type_nameIjEPKcv
	.type	_Z9type_nameIjEPKcv, @function
_Z9type_nameIjEPKcv:
.LFB4292:
	.cfi_startproc
	movl	$.LC0, %eax
	ret
	.cfi_endproc
.LFE4292:
	.size	_Z9type_nameIjEPKcv, .-_Z9type_nameIjEPKcv
	.section	.rodata.str1.1
.LC1:
	.string	"uint64"
	.text
	.p2align 4,,15
	.globl	_Z9type_nameImEPKcv
	.type	_Z9type_nameImEPKcv, @function
_Z9type_nameImEPKcv:
.LFB4293:
	.cfi_startproc
	movl	$.LC1, %eax
	ret
	.cfi_endproc
.LFE4293:
	.size	_Z9type_nameImEPKcv, .-_Z9type_nameImEPKcv
	.section	.rodata.str1.1
.LC2:
	.string	"float32"
	.text
	.p2align 4,,15
	.globl	_Z9type_nameIfEPKcv
	.type	_Z9type_nameIfEPKcv, @function
_Z9type_nameIfEPKcv:
.LFB4294:
	.cfi_startproc
	movl	$.LC2, %eax
	ret
	.cfi_endproc
.LFE4294:
	.size	_Z9type_nameIfEPKcv, .-_Z9type_nameIfEPKcv
	.section	.rodata.str1.1
.LC3:
	.string	"float64"
	.text
	.p2align 4,,15
	.globl	_Z9type_nameIdEPKcv
	.type	_Z9type_nameIdEPKcv, @function
_Z9type_nameIdEPKcv:
.LFB4295:
	.cfi_startproc
	movl	$.LC3, %eax
	ret
	.cfi_endproc
.LFE4295:
	.size	_Z9type_nameIdEPKcv, .-_Z9type_nameIdEPKcv
	.section	.rodata.str1.1
.LC4:
	.string	"Usage: "
.LC5:
	.string	" <dtype> <itype> <n> <m>"
.LC6:
	.string	"  where "
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC7:
	.string	"  <dtype> is in {uint32, uint64, float32, float64, int128}"
	.align 8
.LC8:
	.string	"  <itype> is in {uint32, uint64, fast_uint32}"
	.text
	.p2align 4,,15
	.globl	_Z5usagePc
	.type	_Z5usagePc, @function
_Z5usagePc:
.LFB4307:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$7, %edx
	movl	$.LC4, %esi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	movl	$_ZSt4cerr, %edi
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	testq	%rbx, %rbx
	je	.L31
	movq	%rbx, %rdi
	call	strlen
	movq	%rbx, %rsi
	movq	%rax, %rdx
	movl	$_ZSt4cerr, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
.L9:
	movl	$24, %edx
	movl	$.LC5, %esi
	movl	$_ZSt4cerr, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	_ZSt4cerr(%rip), %rax
	movq	-24(%rax), %rax
	movq	_ZSt4cerr+240(%rax), %rbx
	testq	%rbx, %rbx
	je	.L13
	cmpb	$0, 56(%rbx)
	je	.L11
	movzbl	67(%rbx), %eax
.L12:
	movsbl	%al, %esi
	movl	$_ZSt4cerr, %edi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	$8, %edx
	movq	%rax, %rbx
	movl	$.LC6, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	(%rbx), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %rbp
	testq	%rbp, %rbp
	je	.L13
	cmpb	$0, 56(%rbp)
	je	.L14
	movzbl	67(%rbp), %eax
.L15:
	movsbl	%al, %esi
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	$58, %edx
	movq	%rax, %rbx
	movl	$.LC7, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	(%rbx), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %rbp
	testq	%rbp, %rbp
	je	.L13
	cmpb	$0, 56(%rbp)
	je	.L16
	movzbl	67(%rbp), %eax
.L17:
	movsbl	%al, %esi
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	$45, %edx
	movq	%rax, %rbx
	movl	$.LC8, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	(%rbx), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %rbp
	testq	%rbp, %rbp
	je	.L13
	cmpb	$0, 56(%rbp)
	je	.L18
	movzbl	67(%rbp), %eax
.L19:
	movq	%rbx, %rdi
	movsbl	%al, %esi
	call	_ZNSo3putEc
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rax, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZNSo5flushEv
	.p2align 4,,10
	.p2align 3
.L11:
	.cfi_restore_state
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movl	$10, %esi
	movq	%rbx, %rdi
	call	*48(%rax)
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L14:
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
	jmp	.L15
	.p2align 4,,10
	.p2align 3
.L16:
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L18:
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L31:
	movq	_ZSt4cerr(%rip), %rax
	movq	-24(%rax), %rdi
	addq	$_ZSt4cerr, %rdi
	movl	32(%rdi), %esi
	orl	$1, %esi
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
	jmp	.L9
.L13:
	call	_ZSt16__throw_bad_castv
	.cfi_endproc
.LFE4307:
	.size	_Z5usagePc, .-_Z5usagePc
	.section	.text._ZN3fbs15eytzinger_arrayIjmLb1EE9copy_dataIPjEET_S4_m,"axG",@progbits,_ZN3fbs15eytzinger_arrayIjmLb1EE9copy_dataIPjEET_S4_m,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN3fbs15eytzinger_arrayIjmLb1EE9copy_dataIPjEET_S4_m
	.type	_ZN3fbs15eytzinger_arrayIjmLb1EE9copy_dataIPjEET_S4_m, @function
_ZN3fbs15eytzinger_arrayIjmLb1EE9copy_dataIPjEET_S4_m:
.LFB4642:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdx, %rcx
	movq	%rsi, %rax
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rdi, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$120, %rsp
	.cfi_def_cfa_offset 176
	movq	%rdx, 56(%rsp)
	movq	8(%rdi), %rdx
	cmpq	%rdx, %rcx
	jae	.L33
	movq	56(%rsp), %rcx
.L58:
	addq	%rcx, %rcx
	movq	%rcx, 64(%rsp)
	addq	$1, %rcx
	movq	%rcx, %rdi
	movq	%rcx, 16(%rsp)
	movq	%rax, %rcx
	cmpq	%rdx, %rdi
	movq	16(%rsp), %rax
	jae	.L79
.L59:
	addq	%rax, %rax
	movq	%rax, 72(%rsp)
	addq	$1, %rax
	cmpq	%rdx, %rax
	movq	%rax, 24(%rsp)
	jae	.L80
.L60:
	movq	24(%rsp), %rax
	addq	%rax, %rax
	movq	%rax, 80(%rsp)
	addq	$1, %rax
	movq	%rax, %rdi
	movq	%rax, 32(%rsp)
	movq	%rcx, %rax
	cmpq	%rdx, %rdi
	jae	.L81
.L61:
	movq	32(%rsp), %rdi
	movq	%rcx, %rsi
	addq	%rdi, %rdi
	movq	%rdi, 88(%rsp)
	addq	$1, %rdi
	cmpq	%rdx, %rdi
	movq	%rdi, 40(%rsp)
	jae	.L82
.L62:
	movq	40(%rsp), %rax
	addq	%rax, %rax
	movq	%rax, 96(%rsp)
	addq	$1, %rax
	cmpq	%rdx, %rax
	movq	%rax, 48(%rsp)
	jae	.L83
	movq	48(%rsp), %rax
	movq	%r14, %r15
.L63:
	addq	%rax, %rax
	movq	%rsi, %rcx
	leaq	1(%rax), %r12
	movq	%rax, 104(%rsp)
	cmpq	%rdx, %r12
	jae	.L84
.L64:
	leaq	(%r12,%r12), %rax
	leaq	1(%rax), %rbp
	movq	%rax, 8(%rsp)
	movq	%rcx, %rax
	cmpq	%rdx, %rbp
	jae	.L85
	.p2align 4,,10
	.p2align 3
.L65:
	leaq	(%rbp,%rbp), %r14
	movq	%rax, %rsi
	leaq	1(%r14), %rbx
	cmpq	%rdx, %rbx
	jae	.L86
	.p2align 4,,10
	.p2align 3
.L66:
	leaq	(%rbx,%rbx), %r13
	movq	%r15, %rdi
	leaq	1(%r13), %rdx
	call	_ZN3fbs15eytzinger_arrayIjmLb1EE9copy_dataIPjEET_S4_m
	movq	(%r15), %rdi
	leaq	4(%rax), %rsi
	movl	(%rax), %eax
	movq	8(%r15), %rdx
	movl	%eax, (%rdi,%rbx,4)
	leaq	2(%r13), %rbx
	cmpq	%rbx, %rdx
	ja	.L66
.L49:
	movl	(%rsi), %ecx
	leaq	4(%rsi), %rax
	movl	%ecx, (%rdi,%rbp,4)
	leaq	2(%r14), %rbp
	cmpq	%rdx, %rbp
	jb	.L65
.L47:
	leaq	4(%rax), %rcx
	movl	(%rax), %eax
	movl	%eax, (%rdi,%r12,4)
	movq	8(%rsp), %r12
	addq	$2, %r12
	cmpq	%rdx, %r12
	jb	.L64
.L45:
	movl	(%rcx), %eax
	leaq	4(%rcx), %rsi
	movq	48(%rsp), %rcx
	movl	%eax, (%rdi,%rcx,4)
	movq	104(%rsp), %rax
	addq	$2, %rax
	cmpq	%rdx, %rax
	movq	%rax, 48(%rsp)
	jb	.L63
	movq	%r15, %r14
.L43:
	movl	(%rsi), %ecx
	leaq	4(%rsi), %rax
	movq	40(%rsp), %rsi
	movl	%ecx, (%rdi,%rsi,4)
	movq	96(%rsp), %rcx
	addq	$2, %rcx
	cmpq	%rdx, %rcx
	movq	%rcx, 40(%rsp)
	jae	.L41
	movq	%rax, %rsi
	jmp	.L62
.L86:
	movq	(%r15), %rdi
	jmp	.L49
.L85:
	movq	(%r15), %rdi
	.p2align 4,,2
	jmp	.L47
.L84:
	movq	(%r15), %rdi
	.p2align 4,,2
	jmp	.L45
.L82:
	movq	(%r14), %rdi
.L41:
	movq	32(%rsp), %rsi
	leaq	4(%rax), %rcx
	movl	(%rax), %eax
	movl	%eax, (%rdi,%rsi,4)
	movq	88(%rsp), %rax
	addq	$2, %rax
	cmpq	%rdx, %rax
	movq	%rax, 32(%rsp)
	jae	.L39
	movq	%rcx, %rax
	jmp	.L61
.L83:
	movq	(%r14), %rdi
	jmp	.L43
.L81:
	movq	(%r14), %rdi
.L39:
	movq	24(%rsp), %rsi
	leaq	4(%rcx), %rax
	movl	(%rcx), %ecx
	movl	%ecx, (%rdi,%rsi,4)
	movq	80(%rsp), %rcx
	addq	$2, %rcx
	cmpq	%rdx, %rcx
	movq	%rcx, 24(%rsp)
	jae	.L37
	movq	%rax, %rcx
	jmp	.L60
.L79:
	movq	(%r14), %rdi
.L35:
	movq	56(%rsp), %rsi
	leaq	4(%rcx), %rax
	movl	(%rcx), %ecx
	movl	%ecx, (%rdi,%rsi,4)
	movq	64(%rsp), %rcx
	addq	$2, %rcx
	cmpq	%rdx, %rcx
	movq	%rcx, 56(%rsp)
	jb	.L58
.L33:
	addq	$120, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L80:
	.cfi_restore_state
	movq	(%r14), %rdi
	movq	%rcx, %rax
.L37:
	movq	16(%rsp), %rsi
	leaq	4(%rax), %rcx
	movl	(%rax), %eax
	movl	%eax, (%rdi,%rsi,4)
	movq	72(%rsp), %rax
	addq	$2, %rax
	cmpq	%rdx, %rax
	movq	%rax, 16(%rsp)
	jb	.L59
	jmp	.L35
	.cfi_endproc
.LFE4642:
	.size	_ZN3fbs15eytzinger_arrayIjmLb1EE9copy_dataIPjEET_S4_m, .-_ZN3fbs15eytzinger_arrayIjmLb1EE9copy_dataIPjEET_S4_m
	.section	.rodata.str1.1
.LC9:
	.string	"array length "
	.section	.rodata.str1.8
	.align 8
.LC10:
	.string	" is too big, use a larger I class"
	.section	.rodata.str1.1
.LC11:
	.string	"eytzinger_array.h"
	.section	.rodata.str1.8
	.align 8
.LC12:
	.string	"posix_memalign((void **)&a, 64, sizeof(T) * (n+1)) == 0"
	.section	.text._ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m,"axG",@progbits,_ZN3fbs15eytzinger_arrayIjmLb1EEC5IPjEET_m,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m
	.type	_ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m, @function
_ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m:
.LFB4622:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA4622
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	subq	$384, %rsp
	.cfi_def_cfa_offset 416
	testq	%rdx, %rdx
	movq	$0, (%rdi)
	movq	$0, 8(%rdi)
	js	.L98
	movq	%rdx, 8(%rbx)
	leaq	4(,%rdx,4), %rdx
	movq	%rsi, %r12
	movl	$64, %esi
	call	posix_memalign
	testl	%eax, %eax
	jne	.L99
	addq	$4, (%rbx)
	movq	%r12, %rsi
	movq	%rbx, %rdi
	xorl	%edx, %edx
	call	_ZN3fbs15eytzinger_arrayIjmLb1EE9copy_dataIPjEET_S4_m
	addq	$384, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L98:
	.cfi_restore_state
	leaq	32(%rsp), %rdi
	movl	$16, %esi
.LEHB0:
	call	_ZNSt19basic_ostringstreamIcSt11char_traitsIcESaIcEEC1ESt13_Ios_Openmode
.LEHE0:
	leaq	32(%rsp), %rdi
	movl	$.LC9, %esi
.LEHB1:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rbp, %rsi
	movq	%rax, %rdi
	call	_ZNSo9_M_insertImEERSoT_
	movl	$.LC10, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
.LEHE1:
	movl	$16, %edi
	call	__cxa_allocate_exception
	leaq	40(%rsp), %rsi
	leaq	16(%rsp), %rdi
	movq	%rax, %rbx
.LEHB2:
	call	_ZNKSt15basic_stringbufIcSt11char_traitsIcESaIcEE3strEv
.LEHE2:
	leaq	16(%rsp), %rsi
	movq	%rbx, %rdi
.LEHB3:
	call	_ZNSt12out_of_rangeC1ERKSs
.LEHE3:
	movq	16(%rsp), %rax
	leaq	15(%rsp), %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	movl	$_ZNSt12out_of_rangeD1Ev, %edx
	movl	$_ZTISt12out_of_range, %esi
	movq	%rbx, %rdi
.LEHB4:
	call	__cxa_throw
.LEHE4:
.L93:
	movq	%rax, %rbx
.L92:
	leaq	32(%rsp), %rdi
	call	_ZNSt19basic_ostringstreamIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbx, %rdi
.LEHB5:
	call	_Unwind_Resume
.LEHE5:
.L99:
	movl	$_ZZN3fbs15eytzinger_arrayIjmLb1EEC1IPjEET_mE19__PRETTY_FUNCTION__, %ecx
	movl	$107, %edx
	movl	$.LC11, %esi
	movl	$.LC12, %edi
	call	__assert_fail
.L95:
	movq	%rax, %rbp
	movq	16(%rsp), %rax
	leaq	15(%rsp), %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
.L91:
	movq	%rbx, %rdi
	movq	%rbp, %rbx
	call	__cxa_free_exception
	jmp	.L92
.L94:
	movq	%rax, %rbp
	jmp	.L91
	.cfi_endproc
.LFE4622:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m,"aG",@progbits,_ZN3fbs15eytzinger_arrayIjmLb1EEC5IPjEET_m,comdat
.LLSDA4622:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4622-.LLSDACSB4622
.LLSDACSB4622:
	.uleb128 .LEHB0-.LFB4622
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB4622
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L93-.LFB4622
	.uleb128 0
	.uleb128 .LEHB2-.LFB4622
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L94-.LFB4622
	.uleb128 0
	.uleb128 .LEHB3-.LFB4622
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L95-.LFB4622
	.uleb128 0
	.uleb128 .LEHB4-.LFB4622
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L93-.LFB4622
	.uleb128 0
	.uleb128 .LEHB5-.LFB4622
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE4622:
	.section	.text._ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m,"axG",@progbits,_ZN3fbs15eytzinger_arrayIjmLb1EEC5IPjEET_m,comdat
	.size	_ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m, .-_ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m
	.weak	_ZN3fbs15eytzinger_arrayIjmLb1EEC1IPjEET_m
	.set	_ZN3fbs15eytzinger_arrayIjmLb1EEC1IPjEET_m,_ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m
	.section	.text._ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv,"axG",@progbits,_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv
	.type	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv, @function
_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv:
.LFB4645:
	.cfi_startproc
	movq	4992(%rdi), %rax
	cmpq	$623, %rax
	ja	.L101
	leaq	1(%rax), %rdx
	movq	(%rdi,%rax,8), %rax
.L102:
	movq	%rdx, 4992(%rdi)
	movq	%rax, %rdx
	shrq	$11, %rdx
	movl	%edx, %edx
	xorq	%rax, %rdx
	movq	%rdx, %rax
	salq	$7, %rax
	andl	$2636928640, %eax
	xorq	%rdx, %rax
	movq	%rax, %rdx
	salq	$15, %rdx
	andl	$4022730752, %edx
	xorq	%rax, %rdx
	movq	%rdx, %rax
	shrq	$18, %rax
	xorq	%rdx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L101:
	leaq	8(%rdi), %rdx
	movq	(%rdi), %rax
	xorl	%esi, %esi
	movl	$2567483615, %r10d
	xorl	%r9d, %r9d
	jmp	.L104
	.p2align 4,,10
	.p2align 3
.L109:
	movq	%r8, %rax
.L104:
	movq	(%rdx), %r8
	andq	$-2147483648, %rax
	addq	$1, %rsi
	movq	%r8, %rcx
	andl	$2147483647, %ecx
	orq	%rax, %rcx
	movq	%r9, %rax
	testb	$1, %cl
	cmovne	%r10, %rax
	xorq	3168(%rdx), %rax
	shrq	%rcx
	addq	$8, %rdx
	xorq	%rcx, %rax
	movq	%rax, -16(%rdx)
	cmpq	$227, %rsi
	jne	.L109
	leaq	1824(%rdi), %rdx
	movq	1816(%rdi), %rax
	movl	$227, %esi
	movl	$2567483615, %r10d
	xorl	%r9d, %r9d
	jmp	.L106
	.p2align 4,,10
	.p2align 3
.L110:
	movq	%r8, %rax
.L106:
	movq	(%rdx), %r8
	andq	$-2147483648, %rax
	addq	$1, %rsi
	movq	%r8, %rcx
	andl	$2147483647, %ecx
	orq	%rax, %rcx
	movq	%r9, %rax
	testb	$1, %cl
	cmovne	%r10, %rax
	xorq	-1824(%rdx), %rax
	shrq	%rcx
	addq	$8, %rdx
	xorq	%rcx, %rax
	movq	%rax, -16(%rdx)
	cmpq	$623, %rsi
	jne	.L110
	movq	(%rdi), %rax
	movq	4984(%rdi), %rdx
	movl	$2567483615, %esi
	movq	%rax, %rcx
	andq	$-2147483648, %rdx
	andl	$2147483647, %ecx
	orq	%rdx, %rcx
	movq	%rcx, %rdx
	shrq	%rdx
	xorq	3168(%rdi), %rdx
	andl	$1, %ecx
	movl	$0, %ecx
	cmove	%rcx, %rsi
	xorq	%rsi, %rdx
	movq	%rdx, 4984(%rdi)
	movl	$1, %edx
	jmp	.L102
	.cfi_endproc
.LFE4645:
	.size	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv, .-_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv
	.section	.text._ZNSt24uniform_int_distributionIjEclISt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEEEjRT_RKNS0_10param_typeE,"axG",@progbits,_ZNSt24uniform_int_distributionIjEclISt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEEEjRT_RKNS0_10param_typeE,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt24uniform_int_distributionIjEclISt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEEEjRT_RKNS0_10param_typeE
	.type	_ZNSt24uniform_int_distributionIjEclISt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEEEjRT_RKNS0_10param_typeE, @function
_ZNSt24uniform_int_distributionIjEclISt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEEEjRT_RKNS0_10param_typeE:
.LFB4624:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movl	(%rdx), %eax
	movl	4(%rdx), %r15d
	subq	%rax, %r15
	movl	$4294967294, %eax
	cmpq	%rax, %r15
	ja	.L112
	leaq	1(%r15), %rcx
	movb	$-1, %al
	xorl	%edx, %edx
	divq	%rcx
	imulq	%rax, %rcx
	movq	%rax, %r12
	movq	%rcx, %r13
.L114:
	movq	%rbx, %rdi
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv
	cmpq	%rax, %r13
	jbe	.L114
	xorl	%edx, %edx
	divq	%r12
.L115:
	addl	0(%rbp), %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L112:
	.cfi_restore_state
	movl	$4294967295, %r13d
	cmpq	%r13, %r15
	je	.L116
	movq	%r15, %r14
	shrq	$32, %r14
	leaq	1(%r14), %r12
.L122:
	cmpq	%r13, %r14
	je	.L117
	movq	%r13, %rax
	xorl	%edx, %edx
	divq	%r12
	movq	%rax, %rsi
	imulq	%r12, %rax
	movq	%rax, (%rsp)
	.p2align 4,,10
	.p2align 3
.L119:
	movq	%rbx, %rdi
	movq	%rsi, 8(%rsp)
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv
	cmpq	%rax, (%rsp)
	movq	8(%rsp), %rsi
	jbe	.L119
	xorl	%edx, %edx
	divq	%rsi
.L120:
	salq	$32, %rax
	movq	%rbx, %rdi
	movq	%rax, (%rsp)
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv
	addq	(%rsp), %rax
	jc	.L122
	cmpq	%r15, %rax
	ja	.L122
	.p2align 4,,4
	jmp	.L115
.L117:
	movq	%rbx, %rdi
	.p2align 4,,5
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv
	.p2align 4,,5
	jmp	.L120
.L116:
	movq	%rsi, %rdi
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEclEv
	.p2align 4,,5
	jmp	.L115
	.cfi_endproc
.LFE4624:
	.size	_ZNSt24uniform_int_distributionIjEclISt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEEEjRT_RKNS0_10param_typeE, .-_ZNSt24uniform_int_distributionIjEclISt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEEEjRT_RKNS0_10param_typeE
	.section	.text._ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb0EEEmj,"axG",@progbits,_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb0EEEmj,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb0EEEmj
	.type	_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb0EEEmj, @function
_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb0EEEmj:
.LFB4646:
	.cfi_startproc
	movq	8(%rdi), %r9   # r9 = n (rdi = this)
	testq	%r9, %r9
	je	.L131
	movq	(%rdi), %r10   # r10 = a
	movq	%r9, %rax
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L130:

	movq	%rdx, %rdi           # copy (i=rdx) into rdi
	salq	$6, %rdi             # multiply rdi by 64 (16*4bytes)
	prefetcht0	92(%r10,%rdi)

	movl	(%r10,%rdx,4), %ecx # load r10 + 4*rdx into ecx [r10 = a, rdx = i]. 
	leaq	(%rdx,%rdx), %rdi   # rdi = 2*i
	leaq	1(%rdi), %r8        # r8 = 2*i + 1 (r8 = left)
	addq	$2, %rdi            # rdi = 2*i + 2
	cmpl	%esi, %ecx   # (esi = x) <= (ecx = current)
	cmovae	%rdx, %rax   # j = i if x <= current
	movq	%rdi, %rdx   # rdx = 2*i + 2
	cmovae	%r8, %rdx    # rdx = 2*i + 1 if x <= current
	cmpq	%rdx, %r9    # compare i (rdx) and n (r9)
	ja	.L130
	rep ret
.L131:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE4646:
	.size	_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb0EEEmj, .-_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb0EEEmj
	.section	.rodata.str1.1
.LC13:
	.string	" "
	.section	.text._Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,"axG",@progbits,_Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,comdat
	.p2align 4,,15
	.weak	_Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs
	.type	_Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs, @function
_Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs:
.LFB4561:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA4561
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	movl	$1, %r8d
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdi, %r12
	movabsq	$945986875574848801, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdx, %rbp
	movl	$232342, %edx
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rsi, %rbx
	subq	$5040, %rsp
	.cfi_def_cfa_offset 5088
	movq	$232342, 32(%rsp)
	.p2align 4,,10
	.p2align 3
.L134:
	movq	%rdx, %rax
	shrq	$30, %rax
	xorq	%rdx, %rax
	movq	%r8, %rdx
	shrq	$4, %rdx
	imulq	$1812433253, %rax, %rsi
	movq	%rdx, %rax
	mulq	%rdi
	movq	%r8, %rax
	shrq	%rdx
	imulq	$624, %rdx, %rdx
	subq	%rdx, %rax
	movq	%rax, %rdx
	addl	%esi, %edx
	movq	%rdx, 32(%rsp,%r8,8)
	addq	$1, %r8
	cmpq	$624, %r8
	jne	.L134
	movq	(%rcx), %rsi
	leal	1(%rbx,%rbx), %eax
	movl	$_ZSt4cout, %edi
	movq	$624, 5024(%rsp)
	movl	$0, (%rsp)
	movl	%eax, 4(%rsp)
	movq	-24(%rsi), %rdx
.LEHB6:
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$1, %edx
	movq	%rax, %r13
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movl	$6, %edx
	movl	$.LC0, %esi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movl	$1, %edx
	movl	$.LC13, %esi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movl	$6, %edx
	movl	$.LC1, %esi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$1, %edx
	movq	%r13, %rdi
	movl	$.LC13, %esi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movq	%rbx, %rsi
	call	_ZNSo9_M_insertImEERSoT_
	movl	$1, %edx
	movq	%rax, %r13
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movq	%rbp, %rsi
	call	_ZNSo9_M_insertImEERSoT_
	movl	$1, %edx
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$_ZSt4cout, %edi
	call	_ZNSo5flushEv
	call	_ZNSt6chrono3_V212system_clock3nowEv
	leaq	16(%rsp), %rdi
	movq	%rax, %r13
	movq	%rbx, %rdx
	movq	%r12, %rsi
	call	_ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m
.LEHE6:
	call	_ZNSt6chrono3_V212system_clock3nowEv
	subq	%r13, %rax
	movl	$_ZSt4cout, %edi
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC14(%rip), %xmm0
.LEHB7:
	call	_ZNSo9_M_insertIdEERSoT_
	movl	$1, %edx
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$_ZSt4cout, %edi
	call	_ZNSo5flushEv
	call	_ZNSt6chrono3_V212system_clock3nowEv
	testq	%rbp, %rbp
	movq	%rax, %r14
	je	.L142
	xorl	%r12d, %r12d
	xorl	%r13d, %r13d
	.p2align 4,,10
	.p2align 3
.L137:
	leaq	32(%rsp), %rsi
	movq	%rsp, %rdx
	movq	%rsp, %rdi
	call	_ZNSt24uniform_int_distributionIjEclISt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEEEjRT_RKNS0_10param_typeE
	leaq	16(%rsp), %rdi
	movl	%eax, %esi
	call	_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb0EEEmj
	cmpq	%rax, %rbx
	movl	$-1, %edx
	jbe	.L136
	movq	16(%rsp), %rdx
	movl	(%rdx,%rax,4), %edx
.L136:
	addq	$1, %r12
	addl	%edx, %r13d
	cmpq	%rbp, %r12
	jne	.L137
.L135:
	call	_ZNSt6chrono3_V212system_clock3nowEv
	subq	%r14, %rax
	movl	$_ZSt4cout, %edi
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC14(%rip), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_
	movl	$1, %edx
	movl	$.LC13, %esi
	movq	%rax, %rdi
	movq	%rax, %rbx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%r13d, %esi
	movq	%rbx, %rdi
	call	_ZNSo9_M_insertImEERSoT_
	movq	%rax, %rbp
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %rbx
	testq	%rbx, %rbx
	je	.L147
	cmpb	$0, 56(%rbx)
	je	.L139
	movzbl	67(%rbx), %eax
.L140:
	movsbl	%al, %esi
	movq	%rbp, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movq	16(%rsp), %rax
	leaq	-4(%rax), %rdi
	call	free
	addq	$5040, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L139:
	.cfi_restore_state
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movl	$10, %esi
	movq	%rbx, %rdi
	call	*48(%rax)
.LEHE7:
	jmp	.L140
.L142:
	xorl	%r13d, %r13d
	jmp	.L135
.L144:
	movq	%rax, %rbx
	movq	16(%rsp), %rax
	leaq	-4(%rax), %rdi
	call	free
	movq	%rbx, %rdi
.LEHB8:
	call	_Unwind_Resume
.LEHE8:
.L147:
.LEHB9:
	call	_ZSt16__throw_bad_castv
.LEHE9:
	.cfi_endproc
.LFE4561:
	.section	.gcc_except_table._Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,"aG",@progbits,_Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,comdat
.LLSDA4561:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4561-.LLSDACSB4561
.LLSDACSB4561:
	.uleb128 .LEHB6-.LFB4561
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB7-.LFB4561
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L144-.LFB4561
	.uleb128 0
	.uleb128 .LEHB8-.LFB4561
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB9-.LFB4561
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L144-.LFB4561
	.uleb128 0
.LLSDACSE4561:
	.section	.text._Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,"axG",@progbits,_Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,comdat
	.size	_Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs, .-_Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs
	.section	.text._ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb1EEEmj,"axG",@progbits,_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb1EEEmj,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb1EEEmj
	.type	_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb1EEEmj, @function
_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb1EEEmj:
.LFB4647:
	.cfi_startproc
	movq	8(%rdi), %r8
	testq	%r8, %r8
	je	.L153
	movq	(%rdi), %rcx
	movq	%r8, %rax
	xorl	%edx, %edx
	jmp	.L151
	.p2align 4,,10
	.p2align 3
.L156:
	leaq	2(%rdx,%rdx), %rdx   # rdx = 2i+2
	cmpq	%rdx, %r8            # compare rdx = i and n
	jbe	.L155                # gtfo if i >= n
.L151:
	movq	%rdx, %rdi           # copy (i=rdx) into rdi
	salq	$6, %rdi             # multiply rdi by 64 (16*4bytes)
	cmpl	%esi, (%rcx,%rdx,4)  # compare (x=esi) to a[i] (rcx = a, rdx = i)
	prefetcht0	92(%rcx,%rdi)
	jb	.L156                # go right if x > a[i]
	movq	%rdx, %rax           # going left
	leaq	1(%rdx,%rdx), %rdx   # rdx = 2i+1
	cmpq	%rdx, %r8            # compare i and n
	ja	.L151                # keep going if n > i
.L155:
	rep ret
.L153:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE4647:
	.size	_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb1EEEmj, .-_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb1EEEmj
	.section	.text._Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,"axG",@progbits,_Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,comdat
	.p2align 4,,15
	.weak	_Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs
	.type	_Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs, @function
_Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs:
.LFB4576:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA4576
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	movl	$1, %r8d
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdi, %r12
	movabsq	$945986875574848801, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdx, %rbp
	movl	$232342, %edx
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rsi, %rbx
	subq	$5040, %rsp
	.cfi_def_cfa_offset 5088
	movq	$232342, 32(%rsp)
	.p2align 4,,10
	.p2align 3
.L159:
	movq	%rdx, %rax
	shrq	$30, %rax
	xorq	%rdx, %rax
	movq	%r8, %rdx
	shrq	$4, %rdx
	imulq	$1812433253, %rax, %rsi
	movq	%rdx, %rax
	mulq	%rdi
	movq	%r8, %rax
	shrq	%rdx
	imulq	$624, %rdx, %rdx
	subq	%rdx, %rax
	movq	%rax, %rdx
	addl	%esi, %edx
	movq	%rdx, 32(%rsp,%r8,8)
	addq	$1, %r8
	cmpq	$624, %r8
	jne	.L159
	movq	(%rcx), %rsi
	leal	1(%rbx,%rbx), %eax
	movl	$_ZSt4cout, %edi
	movq	$624, 5024(%rsp)
	movl	$0, (%rsp)
	movl	%eax, 4(%rsp)
	movq	-24(%rsi), %rdx
.LEHB10:
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$1, %edx
	movq	%rax, %r13
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movl	$6, %edx
	movl	$.LC0, %esi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movl	$1, %edx
	movl	$.LC13, %esi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movl	$6, %edx
	movl	$.LC1, %esi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$1, %edx
	movq	%r13, %rdi
	movl	$.LC13, %esi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movq	%rbx, %rsi
	call	_ZNSo9_M_insertImEERSoT_
	movl	$1, %edx
	movq	%rax, %r13
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r13, %rdi
	movq	%rbp, %rsi
	call	_ZNSo9_M_insertImEERSoT_
	movl	$1, %edx
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$_ZSt4cout, %edi
	call	_ZNSo5flushEv
	call	_ZNSt6chrono3_V212system_clock3nowEv
	leaq	16(%rsp), %rdi
	movq	%rax, %r13
	movq	%rbx, %rdx
	movq	%r12, %rsi
	call	_ZN3fbs15eytzinger_arrayIjmLb1EEC2IPjEET_m
.LEHE10:
	call	_ZNSt6chrono3_V212system_clock3nowEv
	subq	%r13, %rax
	movl	$_ZSt4cout, %edi
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC14(%rip), %xmm0
.LEHB11:
	call	_ZNSo9_M_insertIdEERSoT_
	movl	$1, %edx
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$_ZSt4cout, %edi
	call	_ZNSo5flushEv
	call	_ZNSt6chrono3_V212system_clock3nowEv
	testq	%rbp, %rbp
	movq	%rax, %r14
	je	.L167
	xorl	%r12d, %r12d
	xorl	%r13d, %r13d
	.p2align 4,,10
	.p2align 3
.L162:
	leaq	32(%rsp), %rsi
	movq	%rsp, %rdx
	movq	%rsp, %rdi
	call	_ZNSt24uniform_int_distributionIjEclISt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EEEEjRT_RKNS0_10param_typeE
	leaq	16(%rsp), %rdi
	movl	%eax, %esi
	call	_ZNK3fbs15eytzinger_arrayIjmLb1EE18_branchfree_searchILb1EEEmj
	cmpq	%rax, %rbx
	movl	$-1, %edx
	jbe	.L161
	movq	16(%rsp), %rdx
	movl	(%rdx,%rax,4), %edx
.L161:
	addq	$1, %r12
	addl	%edx, %r13d
	cmpq	%rbp, %r12
	jne	.L162
.L160:
	call	_ZNSt6chrono3_V212system_clock3nowEv
	subq	%r14, %rax
	movl	$_ZSt4cout, %edi
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC14(%rip), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_
	movl	$1, %edx
	movl	$.LC13, %esi
	movq	%rax, %rdi
	movq	%rax, %rbx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%r13d, %esi
	movq	%rbx, %rdi
	call	_ZNSo9_M_insertImEERSoT_
	movq	%rax, %rbp
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %rbx
	testq	%rbx, %rbx
	je	.L172
	cmpb	$0, 56(%rbx)
	je	.L164
	movzbl	67(%rbx), %eax
.L165:
	movsbl	%al, %esi
	movq	%rbp, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movq	16(%rsp), %rax
	leaq	-4(%rax), %rdi
	call	free
	addq	$5040, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L164:
	.cfi_restore_state
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movl	$10, %esi
	movq	%rbx, %rdi
	call	*48(%rax)
.LEHE11:
	jmp	.L165
.L167:
	xorl	%r13d, %r13d
	jmp	.L160
.L169:
	movq	%rax, %rbx
	movq	16(%rsp), %rax
	leaq	-4(%rax), %rdi
	call	free
	movq	%rbx, %rdi
.LEHB12:
	call	_Unwind_Resume
.LEHE12:
.L172:
.LEHB13:
	call	_ZSt16__throw_bad_castv
.LEHE13:
	.cfi_endproc
.LFE4576:
	.section	.gcc_except_table._Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,"aG",@progbits,_Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,comdat
.LLSDA4576:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4576-.LLSDACSB4576
.LLSDACSB4576:
	.uleb128 .LEHB10-.LFB4576
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB11-.LFB4576
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L169-.LFB4576
	.uleb128 0
	.uleb128 .LEHB12-.LFB4576
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB13-.LFB4576
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L169-.LFB4576
	.uleb128 0
.LLSDACSE4576:
	.section	.text._Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,"axG",@progbits,_Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs,comdat
	.size	_Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs, .-_Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs
	.section	.rodata.str1.1
.LC15:
	.string	"eytzinger_bf_a"
.LC18:
	.string	"eytzinger_bfp_a"
	.section	.text._Z9run_testsIjmEvT0_S0_,"axG",@progbits,_Z9run_testsIjmEvT0_S0_,comdat
	.p2align 4,,15
	.weak	_Z9run_testsIjmEvT0_S0_
	.type	_Z9run_testsIjmEvT0_S0_, @function
_Z9run_testsIjmEvT0_S0_:
.LFB4490:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA4490
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movabsq	$2287828610704211968, %rax
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$48, %rsp
	.cfi_def_cfa_offset 80
	cmpq	%rax, %rdi
	ja	.L174
	leaq	0(,%rdi,4), %rdi
.LEHB14:
	call	_Znam
	testq	%rbp, %rbp
	movq	%rax, %rbx
	je	.L186
.L175:
	movq	%rbx, %rax
	movq	%rbp, %rcx
	andl	$15, %eax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	cmpq	%rbp, %rax
	cmova	%rbp, %rax
	cmpq	$6, %rbp
	ja	.L220
.L177:
	cmpq	$1, %rcx
	movl	$0, (%rbx)
	jbe	.L203
	cmpq	$2, %rcx
	movl	$2, 4(%rbx)
	jbe	.L204
	cmpq	$3, %rcx
	movl	$4, 8(%rbx)
	jbe	.L205
	cmpq	$4, %rcx
	movl	$6, 12(%rbx)
	jbe	.L206
	cmpq	$5, %rcx
	movl	$8, 16(%rbx)
	jbe	.L207
	movl	$10, 20(%rbx)
	movl	$6, %eax
.L179:
	cmpq	%rcx, %rbp
	je	.L186
.L178:
	movq	%rbp, %r8
	subq	%rcx, %r8
	movq	%r8, %rsi
	shrq	$2, %rsi
	leaq	0(,%rsi,4), %rdi
	testq	%rdi, %rdi
	je	.L181
	leaq	1(%rax), %rdx
	movq	%rax, 8(%rsp)
	leaq	(%rbx,%rcx,4), %rcx
	movq	8(%rsp), %xmm0
	movq	%rdx, (%rsp)
	xorl	%edx, %edx
	movdqa	.LC16(%rip), %xmm3
	movhps	(%rsp), %xmm0
	movdqa	.LC17(%rip), %xmm2
.L187:
	movdqa	%xmm0, %xmm1
	addq	$1, %rdx
	movdqa	%xmm0, %xmm4
	addq	$16, %rcx
	paddq	%xmm2, %xmm1
	shufps	$136, %xmm1, %xmm0
	paddq	%xmm3, %xmm4
	pslld	$1, %xmm0
	movdqa	%xmm0, -16(%rcx)
	cmpq	%rdx, %rsi
	jbe	.L221
	movdqa	%xmm4, %xmm0
	jmp	.L187
	.p2align 4,,10
	.p2align 3
.L221:
	addq	%rdi, %rax
	cmpq	%rdi, %r8
	je	.L186
.L181:
	leal	(%rax,%rax), %edx
	movl	%edx, (%rbx,%rax,4)
	leaq	1(%rax), %rdx
	cmpq	%rdx, %rbp
	jbe	.L186
	leal	(%rdx,%rdx), %ecx
	addq	$2, %rax
	cmpq	%rax, %rbp
	movl	%ecx, (%rbx,%rdx,4)
	jbe	.L186
	leal	(%rax,%rax), %edx
	movl	%edx, (%rbx,%rax,4)
.L186:
	leaq	30(%rsp), %rdx
	leaq	32(%rsp), %rdi
	movl	$.LC15, %esi
	call	_ZNSsC1EPKcRKSaIcE
.LEHE14:
	leaq	32(%rsp), %rcx
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
.LEHB15:
	call	_Z11run_test1_bIN3fbs18eytzinger_array_bfIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs
.LEHE15:
	movq	32(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L222
.L189:
	leaq	30(%rsp), %rdx
	leaq	32(%rsp), %rdi
	movl	$.LC18, %esi
.LEHB16:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE16:
	leaq	32(%rsp), %rcx
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
.LEHB17:
	call	_Z11run_test1_bIN3fbs19eytzinger_array_bfpIjmLb1EEEjmSt24uniform_int_distributionIjEEvPT0_T1_S7_RKSs
.LEHE17:
	movq	32(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L223
.L194:
	testq	%rbx, %rbx
	je	.L173
	movq	%rbx, %rdi
	call	_ZdaPv
.L173:
	addq	$48, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L174:
	.cfi_restore_state
	movq	$-1, %rdi
.LEHB18:
	call	_Znam
	movq	%rax, %rbx
	jmp	.L175
	.p2align 4,,10
	.p2align 3
.L220:
	testq	%rax, %rax
	jne	.L224
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L178
	.p2align 4,,10
	.p2align 3
.L203:
	movl	$1, %eax
	jmp	.L179
	.p2align 4,,10
	.p2align 3
.L204:
	movl	$2, %eax
	jmp	.L179
	.p2align 4,,10
	.p2align 3
.L205:
	movl	$3, %eax
	jmp	.L179
	.p2align 4,,10
	.p2align 3
.L206:
	movl	$4, %eax
	jmp	.L179
	.p2align 4,,10
	.p2align 3
.L207:
	movl	$5, %eax
	jmp	.L179
.L224:
	movq	%rax, %rcx
	jmp	.L177
.L223:
	movl	$_ZL28__gthrw___pthread_key_createPjPFvPvE, %ecx
	leaq	16(%rdi), %rdx
	testq	%rcx, %rcx
	je	.L195
	movl	$-1, %eax
	lock xaddl	%eax, (%rdx)
.L196:
	testl	%eax, %eax
	jg	.L194
	leaq	31(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L194
.L209:
.L219:
	movq	%rax, %rbx
	movq	32(%rsp), %rax
	leaq	31(%rsp), %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE18:
.L195:
	movl	-8(%rax), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, -8(%rax)
	movl	%edx, %eax
	jmp	.L196
.L222:
	movl	$_ZL28__gthrw___pthread_key_createPjPFvPvE, %ecx
	leaq	16(%rdi), %rdx
	testq	%rcx, %rcx
	je	.L190
	movl	$-1, %eax
	lock xaddl	%eax, (%rdx)
.L191:
	testl	%eax, %eax
	jg	.L189
	leaq	31(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L189
.L208:
	.p2align 4,,3
	jmp	.L219
.L190:
	movl	-8(%rax), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, -8(%rax)
	movl	%edx, %eax
	jmp	.L191
	.cfi_endproc
.LFE4490:
	.section	.gcc_except_table._Z9run_testsIjmEvT0_S0_,"aG",@progbits,_Z9run_testsIjmEvT0_S0_,comdat
.LLSDA4490:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4490-.LLSDACSB4490
.LLSDACSB4490:
	.uleb128 .LEHB14-.LFB4490
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB15-.LFB4490
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L208-.LFB4490
	.uleb128 0
	.uleb128 .LEHB16-.LFB4490
	.uleb128 .LEHE16-.LEHB16
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB17-.LFB4490
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L209-.LFB4490
	.uleb128 0
	.uleb128 .LEHB18-.LFB4490
	.uleb128 .LEHE18-.LEHB18
	.uleb128 0
	.uleb128 0
.LLSDACSE4490:
	.section	.text._Z9run_testsIjmEvT0_S0_,"axG",@progbits,_Z9run_testsIjmEvT0_S0_,comdat
	.size	_Z9run_testsIjmEvT0_S0_, .-_Z9run_testsIjmEvT0_S0_
	.section	.rodata.str1.1
.LC19:
	.string	"int128"
.LC20:
	.string	"fast_uint32"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB4309:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA4309
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rsi, %r12
	movl	$.LC0, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movl	%edi, %ebx
	subq	$904, %rsp
	.cfi_def_cfa_offset 960
	leaq	112(%rsp), %r15
	leaq	528(%rsp), %rdx
	movq	%r15, %rdi
.LEHB19:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE19:
	leaq	8(%r15), %rdi
	leaq	528(%rsp), %rdx
	movl	$.LC2, %esi
.LEHB20:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE20:
	leaq	16(%r15), %rdi
	leaq	528(%rsp), %rdx
	movl	$.LC1, %esi
.LEHB21:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE21:
	leaq	24(%r15), %rdi
	leaq	528(%rsp), %rdx
	movl	$.LC3, %esi
.LEHB22:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE22:
	leaq	32(%r15), %rdi
	leaq	528(%rsp), %rdx
	movl	$.LC19, %esi
.LEHB23:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE23:
	leaq	528(%rsp), %rdx
	leaq	80(%rsp), %rdi
	movl	$.LC0, %esi
.LEHB24:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE24:
	leaq	80(%rsp), %rax
	leaq	528(%rsp), %rdx
	movl	$.LC1, %esi
	leaq	8(%rax), %rdi
.LEHB25:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE25:
	leaq	80(%rsp), %rax
	leaq	528(%rsp), %rdx
	movl	$.LC20, %esi
	leaq	16(%rax), %rdi
.LEHB26:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE26:
	cmpl	$5, %ebx
	jne	.L240
	movq	%r15, %r13
	xorb	%bl, %bl
.L244:
	movq	8(%r12), %rsi
	movq	%r13, %rdi
	leaq	160(%rsp), %rbp
.LEHB27:
	call	_ZNKSs7compareEPKc
	testl	%eax, %eax
	je	.L243
	addl	$1, %ebx
	addq	$8, %r13
	cmpl	$5, %ebx
	jne	.L244
.L243:
	leaq	80(%rsp), %r14
	xorl	%r13d, %r13d
.L242:
	movq	16(%r12), %rsi
	movq	%r14, %rdi
	leaq	160(%rsp), %rbp
	call	_ZNKSs7compareEPKc
	testl	%eax, %eax
	je	.L245
	addl	$1, %r13d
	addq	$8, %r14
	cmpl	$3, %r13d
	jne	.L242
.L245:
	movq	24(%r12), %rsi
	leaq	48(%rsp), %rdx
	leaq	528(%rsp), %rdi
	leaq	160(%rsp), %rbp
	call	_ZNSsC1EPKcRKSaIcE
.LEHE27:
	leaq	160(%rsp), %rbp
	leaq	528(%rsp), %rsi
	movl	$8, %edx
	movq	%rbp, %rdi
.LEHB28:
	call	_ZNSt19basic_istringstreamIcSt11char_traitsIcESaIcEEC1ERKSsSt13_Ios_Openmode
.LEHE28:
	movq	528(%rsp), %rax
	leaq	64(%rsp), %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	leaq	32(%rsp), %rsi
	movq	%rbp, %rdi
.LEHB29:
	call	_ZNSi10_M_extractImEERSiRT_
	movq	32(%r12), %rsi
	leaq	31(%rsp), %rdx
	leaq	64(%rsp), %rdi
	call	_ZNSsC1EPKcRKSaIcE
.LEHE29:
	leaq	64(%rsp), %rsi
	leaq	528(%rsp), %rdi
	movl	$8, %edx
.LEHB30:
	call	_ZNSt19basic_istringstreamIcSt11char_traitsIcESaIcEEC1ERKSsSt13_Ios_Openmode
.LEHE30:
	movq	64(%rsp), %rax
	leaq	48(%rsp), %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	leaq	48(%rsp), %rsi
	leaq	528(%rsp), %rdi
.LEHB31:
	call	_ZNSi10_M_extractImEERSiRT_
.LEHE31:
	leaq	528(%rsp), %rdi
	call	_ZNSt19basic_istringstreamIcSt11char_traitsIcESaIcEED1Ev
	movq	%rbp, %rdi
	call	_ZNSt19basic_istringstreamIcSt11char_traitsIcESaIcEED1Ev
	cmpl	$5, %ebx
	je	.L346
	cmpl	$3, %r13d
	je	.L346
	movq	48(%rsp), %rsi
	movq	32(%rsp), %rdi
.LEHB32:
	call	_Z9run_testsIjmEvT0_S0_
	movl	$_ZL28__gthrw___pthread_key_createPjPFvPvE, %eax
	testq	%rax, %rax
	je	.L347
	movq	96(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L348
.L257:
	movq	88(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L349
.L259:
	movq	80(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L350
.L261:
	movq	144(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L351
.L269:
	movq	136(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L352
.L271:
	movq	128(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L353
.L273:
	movq	120(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L354
.L275:
	movq	112(%rsp), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L355
.L315:
	addq	$904, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L240:
	.cfi_restore_state
	leaq	160(%rsp), %rbp
.L346:
	movq	(%r12), %rdi
	call	_Z5usagePc
.LEHE32:
	orl	$-1, %edi
	call	exit
.L355:
	orl	$-1, %edx
	lock xaddl	%edx, -8(%rax)
	testl	%edx, %edx
	jg	.L315
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L315
.L354:
	orl	$-1, %edx
	lock xaddl	%edx, -8(%rax)
	testl	%edx, %edx
	jg	.L275
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L275
.L353:
	orl	$-1, %edx
	lock xaddl	%edx, -8(%rax)
	testl	%edx, %edx
	jg	.L273
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L273
.L352:
	orl	$-1, %edx
	lock xaddl	%edx, -8(%rax)
	testl	%edx, %edx
	jg	.L271
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L271
.L351:
	orl	$-1, %edx
	lock xaddl	%edx, -8(%rax)
	testl	%edx, %edx
	jg	.L269
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L269
.L350:
	orl	$-1, %edx
	lock xaddl	%edx, -8(%rax)
	testl	%edx, %edx
	jg	.L261
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L261
.L349:
	orl	$-1, %edx
	lock xaddl	%edx, -8(%rax)
	testl	%edx, %edx
	jg	.L259
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L259
.L348:
	orl	$-1, %edx
	lock xaddl	%edx, -8(%rax)
	testl	%edx, %edx
	jg	.L257
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L257
.L347:
	leaq	104(%rsp), %rbx
.L255:
	subq	$8, %rbx
	movq	(%rbx), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L356
.L253:
	leaq	80(%rsp), %rax
	cmpq	%rax, %rbx
	jne	.L255
	leaq	40(%r15), %rbx
.L268:
	subq	$8, %rbx
	movq	(%rbx), %rax
	leaq	-24(%rax), %rdi
	cmpq	$_ZNSs4_Rep20_S_empty_rep_storageE, %rdi
	jne	.L357
.L266:
	cmpq	%r15, %rbx
	jne	.L268
	jmp	.L315
.L293:
	xorl	%ecx, %ecx
.L237:
	movl	$2, %edx
	subq	%rcx, %rdx
	leaq	80(%rsp,%rdx,8), %rbx
.L284:
	leaq	80(%rsp), %rcx
	cmpq	%rcx, %rbx
	je	.L283
	subq	$8, %rbx
	movq	%rax, 8(%rsp)
	leaq	528(%rsp), %rsi
	movq	(%rbx), %rax
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	movq	8(%rsp), %rax
	jmp	.L284
.L356:
	movl	-8(%rax), %edx
	leal	-1(%rdx), %ecx
	testl	%edx, %edx
	movl	%ecx, -8(%rax)
	jg	.L253
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L253
.L283:
	leaq	40(%r15), %rbx
	leaq	160(%rsp), %rbp
	movq	%rax, %r12
.L326:
	subq	$8, %rbx
	movq	(%rbx), %rax
	movq	%rbp, %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	cmpq	%r15, %rbx
	jne	.L326
	movq	%r12, %rdi
.LEHB33:
	call	_Unwind_Resume
.L357:
	movl	-8(%rax), %edx
	leal	-1(%rdx), %ecx
	testl	%edx, %edx
	movl	%ecx, -8(%rax)
	jg	.L266
	leaq	528(%rsp), %rsi
	call	_ZNSs4_Rep10_M_destroyERKSaIcE
	jmp	.L266
.L296:
	movq	%rax, %rbx
	movq	64(%rsp), %rax
	leaq	48(%rsp), %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
.L289:
	movq	%rbp, %rdi
	call	_ZNSt19basic_istringstreamIcSt11char_traitsIcESaIcEED1Ev
.L287:
	movq	96(%rsp), %rax
	movq	%rbp, %rsi
	movq	%rbx, %r12
	leaq	40(%r15), %rbx
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	movq	88(%rsp), %rax
	movq	%rbp, %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	movq	80(%rsp), %rax
	movq	%rbp, %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	jmp	.L326
.L299:
	movl	$4, %edx
.L228:
	movl	$4, %ecx
	subq	%rdx, %rcx
	leaq	(%r15,%rcx,8), %rbx
.L281:
	cmpq	%r15, %rbx
	je	.L280
	subq	$8, %rbx
	movq	%rax, 8(%rsp)
	leaq	528(%rsp), %rsi
	movq	(%rbx), %rax
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	movq	8(%rsp), %rax
	jmp	.L281
.L297:
	leaq	528(%rsp), %rdi
	movq	%rax, %rbx
	call	_ZNSt19basic_istringstreamIcSt11char_traitsIcESaIcEED1Ev
	jmp	.L289
.L303:
	movl	$2, %ecx
	jmp	.L237
.L280:
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE33:
.L294:
	movq	%rax, %rbx
	movq	528(%rsp), %rax
	leaq	64(%rsp), %rsi
	leaq	-24(%rax), %rdi
	call	_ZNSs4_Rep10_M_disposeERKSaIcE
	jmp	.L287
.L298:
	movq	%rax, %rbx
	jmp	.L287
.L304:
	movl	$1, %ecx
	.p2align 4,,3
	jmp	.L237
.L302:
	movl	$1, %edx
	jmp	.L228
.L292:
	xorl	%edx, %edx
	jmp	.L228
.L295:
	movq	%rax, %rbx
	jmp	.L289
.L301:
	movl	$2, %edx
	jmp	.L228
.L300:
	movl	$3, %edx
	jmp	.L228
	.cfi_endproc
.LFE4309:
	.section	.gcc_except_table,"a",@progbits
.LLSDA4309:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4309-.LLSDACSB4309
.LLSDACSB4309:
	.uleb128 .LEHB19-.LFB4309
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L299-.LFB4309
	.uleb128 0
	.uleb128 .LEHB20-.LFB4309
	.uleb128 .LEHE20-.LEHB20
	.uleb128 .L300-.LFB4309
	.uleb128 0
	.uleb128 .LEHB21-.LFB4309
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L301-.LFB4309
	.uleb128 0
	.uleb128 .LEHB22-.LFB4309
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L302-.LFB4309
	.uleb128 0
	.uleb128 .LEHB23-.LFB4309
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L292-.LFB4309
	.uleb128 0
	.uleb128 .LEHB24-.LFB4309
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L303-.LFB4309
	.uleb128 0
	.uleb128 .LEHB25-.LFB4309
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L304-.LFB4309
	.uleb128 0
	.uleb128 .LEHB26-.LFB4309
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L293-.LFB4309
	.uleb128 0
	.uleb128 .LEHB27-.LFB4309
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L298-.LFB4309
	.uleb128 0
	.uleb128 .LEHB28-.LFB4309
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L294-.LFB4309
	.uleb128 0
	.uleb128 .LEHB29-.LFB4309
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L295-.LFB4309
	.uleb128 0
	.uleb128 .LEHB30-.LFB4309
	.uleb128 .LEHE30-.LEHB30
	.uleb128 .L296-.LFB4309
	.uleb128 0
	.uleb128 .LEHB31-.LFB4309
	.uleb128 .LEHE31-.LEHB31
	.uleb128 .L297-.LFB4309
	.uleb128 0
	.uleb128 .LEHB32-.LFB4309
	.uleb128 .LEHE32-.LEHB32
	.uleb128 .L298-.LFB4309
	.uleb128 0
	.uleb128 .LEHB33-.LFB4309
	.uleb128 .LEHE33-.LEHB33
	.uleb128 0
	.uleb128 0
.LLSDACSE4309:
	.section	.text.startup
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I__Z9type_nameIjEPKcv, @function
_GLOBAL__sub_I__Z9type_nameIjEPKcv:
.LFB4668:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE4668:
	.size	_GLOBAL__sub_I__Z9type_nameIjEPKcv, .-_GLOBAL__sub_I__Z9type_nameIjEPKcv
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z9type_nameIjEPKcv
	.section	.rodata
	.align 32
	.type	_ZZN3fbs15eytzinger_arrayIjmLb1EEC1IPjEET_mE19__PRETTY_FUNCTION__, @object
	.size	_ZZN3fbs15eytzinger_arrayIjmLb1EEC1IPjEET_mE19__PRETTY_FUNCTION__, 174
_ZZN3fbs15eytzinger_arrayIjmLb1EEC1IPjEET_mE19__PRETTY_FUNCTION__:
	.string	"fbs::eytzinger_array<T, I, aligned>::eytzinger_array(ForwardIterator, I) [with ForwardIterator = unsigned int*; T = unsigned int; I = long unsigned int; bool aligned = true]"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC14:
	.long	0
	.long	1104006501
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC16:
	.quad	4
	.quad	4
	.align 16
.LC17:
	.quad	2
	.quad	2
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
