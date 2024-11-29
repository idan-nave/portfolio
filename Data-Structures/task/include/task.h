/******************************************************************************/
/*
  Name: Idan Nave
  Project: Task
  Reviewer: HRD32
  Date: 06/09/23
  Version: 1.0
  
  Overview: Implementation of a Task Manager.
*/

#ifndef __ILRD_TASK_H__
#define __ILRD_TASK_H__

/******************************** Libraries  **********************************/

#include <stddef.h>         /*size_t*/
#include <sys/types.h>      /*pid_t, time_t*/
#include <time.h>           /*time_t*/
#include "/home/idan/Documents/Dev/Git_WD/ds/uid/include/uid.h" /*uid_ty*/

/******************************** Definitions  ********************************/

typedef struct task task_t;

/*typedef enum {FALSE = 0, TRUE} boolean_t;*/
typedef enum {UNSCHEDULE = 0, RESCHEDULE} task_mode_t;

typedef int (*task_operation_t)(void*);
typedef void (*task_cleanup_t)(void*);

/*********************** Task API Declerations  ****************************/

/*Function that creates a Task. By default, interval remembers original interval between creation & execuition time. If change is needed, use a self operation-func() to update task's self interval.
  Arguments:  'time_to_exec' - task's excecution time (relative to epoch)
              'op_func' - task's operation function
              'op_params' - operation function-related parameters
              'cleanup_func' - task's optional clenaup operation for tasks
                               that allocate memory.
              'cleanup_params' - should be sent as an array of pointers to be
                                 freed. arr[0] should contain number of params.
                                 If Cleanup Function isn't available, freeing of the params won't be attempted.
  Return value: pointer to newly generated Task. On Error, returns NULL.
  Complexity: O(1). 
  Undefined B.: NULL pointer to Task, Task's execuition time too close to present time, will result in execution miss due to Scheduler computation time */

task_t* TaskCreate(time_t time_to_exec, task_operation_t op_func, void* op_params, task_cleanup_t cleanup_func, void* cleanup_params );
/*Function that destroys a Task. If Cleanup Function isn't available,
  freeing of the params won't be attempted.
  Arguments: 'task' - Task pointer.
  Return value: None.
  Complexity: o(1) or O(cleanup function). 
  Undefined B.: NULL ptr of task, NULL functions & params delivered by user */
void TaskDestroy(task_t *task);

/*Function that executes a task function
  Arguments: 'task' - Task pointer. Task won't be changed except if user operation func explicitly assigns self-change logics (task is not const).
  Return value: UNSCHEDULE / RESCHEDULE given by task's operation function
  Complexity: O(func).
  Undefined B.: NULL pointer to Task. */
int TaskExecute(task_t *task);

/*Function that retrieves the value of the tasks' execution time.
  Arguments: 'task' - Task pointer, 
  Return value: tasks' execution time in seconds since 1970 or epoch.
  Complexity: O(1).
  Undefined B.: NULL pointer to Task. */
time_t TaskGetTimeToExecute(const task_t *task);

/*Function that retrieves the UID of the task
  Arguments: 'task' - pointer to Task,
  Return value: task UID
  Complexity: O(1).
  Undefined B.: NULL pointer to Task,  */
uid_ty TaskGetUID(const task_t *task);

/*Function that updates a tasks' execution time.
  Arguments: 'task' - pointer to Task.
  Return value: updated task's TimeToExecute
  Complexity: O(1).
  Undefined B.: NULL pointer to Task */
void* TaskUpdateTimeToExecute(task_t *task);

/*Function that searches a match between to tasks based on UID
  Arguments: 'task' - pointer to Task,
             'task_uid' - uniqe task id 
  Return value: match result: TRUE / FALSE.
  Complexity: O(1).
  Undefined B.: NULL pointer to Task, invalid uid.*/
int TaskIsMatch(task_t *task, uid_ty match_uid);

/*Function that compares tasks execution times.
  Arguments: 'task1,2' - pointers to Tasks
  Return value: difference between tasks execution time in seconds.
  Undefined B.: NULL pointers to Tasks*/
int TaskCompare(const task_t *task1, const task_t *task2);

#endif /*__ILRD_TASK_H__*/