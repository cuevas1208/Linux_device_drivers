#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x551a9e15, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xa2e59924, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xb97a8d7, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0x74f7c4ce, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x2781cc10, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0x66724a48, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0x95023946, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xf88d4790, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x78f5ccab, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x2072ee9b, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x669acea2, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0x2bbd5c19, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x220464a8, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x680f185c, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0xb850176, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x42c8de35, __VMLINUX_SYMBOL_STR(ioremap_nocache) },
	{ 0x1fedf0f4, __VMLINUX_SYMBOL_STR(__request_region) },
	{ 0x69454d4, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xc4778388, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xf837b2d6, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xb21208a, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x754d539c, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x7c61340c, __VMLINUX_SYMBOL_STR(__release_region) },
	{ 0x69a358a6, __VMLINUX_SYMBOL_STR(iomem_resource) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cvendor,ALU_S_Mod*");

MODULE_INFO(srcversion, "7751280A554D910121BE92A");
