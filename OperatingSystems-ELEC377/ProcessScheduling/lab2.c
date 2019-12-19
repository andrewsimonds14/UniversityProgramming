/*+
 * Module:  lab2.c
 *
 * Purpose: Skeleton solution to ELEC 377 Lab2.
 *
nr_threads : c038b3a8
nr_running : c038b3a4 (Visible)

-*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>

static struct task_struct * firstTask, *lastTask;
struct task_struct *task;
int cnt;
int* thrd_loc = (int *)0xc038b3a8; 
int my_read_proc(char * page, char **start, off_t fpos, int blen, int * eof, void * data){

    int numChars = 0;
    if (fpos == 0){
        numChars += sprintf(page, "Number of running processes: %d", nr_running) ;
        numChars += sprintf(page + numChars, "\nNumber of threads: %d", *thrd_loc);
	    numChars += sprintf(page + numChars, "\nPID\tUID\tNICE\n");
	    task = &init_task;
        while(task->pid == 0){
              task = task->next_task;
        }
	    lastTask = task;
        numChars += sprintf(page + numChars, "%d\t%d\t%d\n", task->pid, task->uid, task->nice);
        do{
            task = task->next_task;
        }while(task->pid == 0);
      
    } else {
        if (task == lastTask){
            *eof = 0;
            *start = page;
            return 0;
        }
	    numChars = sprintf(page, "%d\t%d\t%d\n", task->pid, task->uid, task->nice);
        task = task->next_task;
        while(task->pid == 0){
              task = task->next_task;
        }
    }
    *eof = 1;
    *start = page;
    return numChars;
}

int init_module(){

   struct proc_dir_entry * proc_entry;
   proc_entry = create_proc_entry("lab2",0444,NULL);
   if(proc_entry == NULL) return 1;
    
   proc_entry->read_proc = my_read_proc;
   return 0;
}

void cleanup_module(){
    printk("Removed Lab2 kernal module");
    remove_proc_entry("lab2",NULL);
}
