/******************************************************************************/
/*
  Name: Idan Nave
  Project: Task
  Reviewer: Dima
  Date: 06/09/23
  Version: 1.0

  Overview: Implementation of Task Generator.
*/

/******************************** Libraries  **********************************/
#include <assert.h>             /* assert() */
#include <stdio.h>              /* perror */
#include <stdlib.h>             /* malloc(), free() */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */
#include <time.h>               /*time_t*/

#include "uid.h"
#include "../include/task.h"

/********************************* Type Definitions **************************/
/*#undef assert
#define assert(condition) \
do { \
    if (!(condition)) { \
        fprintf(stderr, "assert was true on condition = '%s'\n", #condition); \
    } \
} while (0)*/

struct task
{
  uid_ty uid;
  time_t time_to_exec;
  double interval_in_sec;
  task_operation_t op_func;
  task_cleanup_t cleanup_func;
  void* op_params;
  void* cleanup_params;
};

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
 task_t* TaskCreate(time_t time_to_exec, 
            task_operation_t op_func, void* op_params,
            task_cleanup_t cleanup_func, void* cleanup_params )
{
  task_t* task = NULL;
  /*unallowd past-execution time*/
  assert(NULL != op_func);

  task = (task_t*)malloc(sizeof(task_t));
  if(NULL == task)
  {
    return NULL;
  }
  
  task->uid = UIDCreate();
  if(TRUE == UIDIsSame(invalid_uid, task->uid))
  {
    free(task);
    task = NULL;
    return NULL;
  }

  task->time_to_exec = time_to_exec;
  task->interval_in_sec = difftime(time_to_exec, time(NULL));
  task->op_func = op_func;
  task->cleanup_func = cleanup_func;
  task->op_params = op_params;
  task->cleanup_params = cleanup_params;

  return task;
}

void TaskDestroy(task_t *task)
{
  assert(NULL != task);

  if(NULL != task->cleanup_func)
  {
      task->cleanup_func(task->cleanup_params);
  }

  free(task);
  task = NULL;
}

int TaskExecute(task_t *task)
{
  assert(NULL != task);
  
  return task->op_func(task->op_params);
}

time_t TaskGetTimeToExecute(const task_t *task)
{
  assert(NULL != task);

  return task->time_to_exec;
}

uid_ty TaskGetUID(const task_t *task)
{
  assert(NULL != task);

  return task->uid;
}

void* TaskUpdateTimeToExecute(task_t *task)
{
  assert(NULL != task);

  task->time_to_exec += task->interval_in_sec;
  return (void*)(task->time_to_exec);
}

int TaskIsMatch(task_t *task, uid_ty match_uid)
{
  assert(NULL != task);

  return UIDIsSame(task->uid, match_uid);
}

int TaskCompare(const task_t *task1, const task_t *task2)
{
  assert(NULL != task1);
  assert(NULL != task2);

  return difftime( task1->time_to_exec, task2->time_to_exec);
}


/******************************************************************************/
/******************* Interval Vs. Absolute Timing Managment *******************/
/******************************************************************************/
/*
The decision of whether to require the user to provide a task's interval or a specific time to execute depends on the flexibility and use cases of your scheduler app

Based on below considerations, implementation of 'Time to Execute' approach was decided, as this app aims to provide precision and use only 2 parameters: time_t time_to_exec & double interval_in_sec, relying on manual interval updates rather on auto-update as a derivative of current and exec_time is
a risk.
as a result, "exec_time" will serve a comparision parameter, raher than a user input/editable.
*/

/*************************In-Detail Explanations*******************************/
/*

**1. Task's Interval:**

- **Pros:**
  - Simplicity: Providing an interval (e.g., every 2 hours, daily, weekly) is straightforward and user-friendly.
  - Flexibility: Users can set recurring tasks with ease, allowing for automation of repetitive tasks.
  - Predictability: Tasks scheduled at regular intervals are predictable and can be easily managed.

- **Cons:**
  - Limited Precision: Intervals may not align with specific times of day, making it challenging to schedule tasks for exact moments.
  - Lack of Granularity: Users might not have the flexibility to schedule tasks at specific minutes and seconds of each hour.

**2. Task's Time to Execute:**

- **Pros:**
  - Precision: Users can schedule tasks to run at exact moments, down to the minute and second.
  - Versatility: It allows for one-time tasks or tasks with specific execution times.
  - Supports Event-Driven: Suitable for scheduling tasks based on external events or conditions.

- **Cons:**
  - Complexity: Users may find it more complex to set up recurring tasks or tasks with complex schedules.
  - Increased Input: Users have to specify both the date and time, which might be cumbersome for some use cases.

**Recommendations:**

1. **Hybrid Approach:** Consider offering both options to users. Allow them to choose whether they want to provide a specific time for one-time or precise tasks or specify an interval for recurring tasks. This approach provides versatility and flexibility.

2. **Default Behavior:** You can set a default behavior that simplifies the task creation process for users who don't require fine-grained scheduling. For example, you could default to an interval-based task creation and offer an advanced option for specifying execution times.

3. **User Guidance:** Provide clear instructions and user-friendly interfaces to guide users in creating tasks, regardless of the chosen approach. Use tooltips, examples, and help sections to assist users in understanding how to set up tasks effectively.

4. **Consider Use Cases:** Think about the primary use cases for your scheduler app and prioritize the approach that best serves those use cases. For instance, if your app is primarily used for precise, one-time tasks, emphasizing specific execution times may be more critical.

Ultimately, the choice should cater to your target user base and the scenarios your scheduler app aims to support. By offering flexibility and clear user guidance, you can create an app that meets various scheduling needs effectively.
*/