/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;
    list_ele_t *tmp = q->head;
    while (q->head) {
        tmp = q->head;
        q->head = q->head->next;
        if (tmp->value)
            free(tmp->value);
        if (tmp)
            free(tmp);
    }
    if (q)
        free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh = NULL;
    char *_s = NULL;
    do {
        if (!q)
            break;
        newh = malloc(sizeof(list_ele_t));
        if (!newh)
            break;
        _s = malloc(strlen(s) + 1);
        if (!_s)
            break;
        strcpy(_s, s);
        newh->value = _s;
        newh->next = q->head;
        q->head = newh;
        if (!q->tail)
            q->tail = newh;
        q->size++;
        return true;
    } while (0);
    if (newh)
        free(newh);
    if (_s)
        free(_s);
    /* What should you do if the q is NULL? */
    return false;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh = NULL;
    char *_s = NULL;
    do {
        if (!q)
            break;
        newh = malloc(sizeof(list_ele_t));
        if (!newh)
            break;
        _s = malloc(strlen(s) + 1);
        if (!_s)
            break;
        strcpy(_s, s);
        newh->value = _s;
        newh->next = NULL;
        if (q->head)
            q->tail->next = newh;
        else
            q->head = newh;
        q->tail = newh;
        q->size++;
        return true;
    } while (0);
    if (newh)
        free(newh);
    if (_s)
        free(_s);
    return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || !(q->head))
        return false;
    list_ele_t *tmp = NULL;
    tmp = q->head;
    q->head = q->head->next;
    if (sp && tmp->value) {
        strncpy(sp, tmp->value, bufsize);
        sp[bufsize - 1] = 0;
    }
    q->size--;
    if (tmp->value)
        free(tmp->value);
    if (tmp)
        free(tmp);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q ? q->size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q || !q->head)
        return;
    if (q->head == q->tail)
        return;
    list_ele_t *buf[3] = {q->head, q->head->next, q->head->next->next};
    q->head->next = NULL;
    q->tail = q->head;
    while (buf[2]) {
        buf[1]->next = buf[0];
        buf[0] = buf[1];
        buf[1] = buf[2];
        buf[2] = buf[2]->next;
    }
    buf[1]->next = buf[0];
    q->head = buf[1];
}
