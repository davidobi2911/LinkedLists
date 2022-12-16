// list/list.c
// 
// Implementation for linked list.
//
// Aniya Wilson

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() {
  list_t* list = (list_t*) malloc(sizeof(list_t));
  list->head = NULL;
  return list;
}

node_t *node_alloc(elem val) {
  node_t* new_node = (node_t*) malloc(sizeof(node_t));
  new_node->value = val;
  new_node->next = NULL;
  return new_node;
}

void list_free(list_t *l) {
  node_t *temp;
  node_t *next;
  if (l == NULL)
    return;
  temp = l->head;
  while (temp != NULL) {
    next = temp->next;
    free(temp);
    temp = next;
  }
}

void list_print(list_t *l) {
  //use current pointer to track node currently printing
  node_t * curr = l->head;
  if (curr == NULL) {
    printf("List is empty.");
  }
  else {
    //set current pointer to next node, print again, until end of list reached (next->NULL)
    while (curr != NULL) {
      printf("%d->", curr->value);
      curr = curr->next;
    }
    printf("\n");
  }
}

int list_length(list_t *l) {
  //intialize length
  int length = 0;
  //use current pointer to track node currently printing
  node_t * curr = l->head;

  //set current pointer to next node, add 1 to length, until end of list reached (next->NULL)
  while (curr != NULL) {
    length += 1;
    curr = curr->next;;
  }
  return length;
}

void list_add_to_back(list_t *l, elem value) {
  node_t *new_node; 
  new_node = (node_t *) malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;
  // empty list
  if (l->head == NULL) {
    l->head = new_node;
  }
  // nonempty list
  else {
    node_t *tail = l->head;
    while(tail->next != NULL) {
      tail = tail->next;
    }
    tail->next = new_node;
  }  
}

void list_add_to_front(list_t *l, elem value) {
  //create new item and set its value
  node_t *new_node;
  new_node = (node_t *) malloc(sizeof(node_t));
  //link new item to point to head of the list
  new_node->value = value;
  new_node->next = l->head;
  //set head of list to be new item
  l->head = new_node;
}

void list_add_at_index(list_t *l, elem value, int index) {
  int size;
  size = list_length(l);
  //printf("size: %d\n", size);
  node_t *new_node; 
  new_node = (node_t *) malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;
  // inserting as head
  if (index == 0) {
    new_node->next = l->head;
    l->head = new_node;
  }
  // empty list, out of range
  else if ((index < 0 && l->head == NULL) || (index > size && l->head == NULL)) {
    new_node->next = l->head;
    l->head = new_node;
  }  
  // nonempty list, out of range
  else if (index > size && l->head != NULL) {
    node_t *tail = l->head;
    while(tail->next != NULL) {
      tail = tail->next;
    }
    tail->next = new_node;
  }  
  else {
    node_t *curr = l->head;
    while (--index) {
      curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
  }
}

elem list_remove_from_back(list_t *l) {
  int retval = -1;
  if (l->head == NULL) {
    return retval;
  }
  //if only one item in list, remove it
  if (l->head->next == NULL) {
    retval = l->head->value;
    free(l->head);
    return retval;
  }

  //move to second to last node
  node_t * curr = l->head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }

  //current points to second to last item, remove curr->next 
  retval = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return retval;
}


elem list_remove_from_front(list_t *l) {
  int retval = -1;
  node_t * next_node = NULL;

  if (l->head == NULL) {
    return retval;
  }
  //save next item head points to
  next_node = (l->head)->next;
  retval = (l->head)->value;
  //free head item
  free(l->head);
  //set head to next item stored
  l->head = next_node;

  return retval;
}


elem list_remove_at_index(list_t *l, int index) {
  int retval = -1;
  if (index < 1 || l->head == NULL) {
    return retval;
  }
  else if (index == 0 && l->head != NULL) {
    node_t *del;
    del = l->head;
    l->head = (l->head)->next;
    retval = l->head->value;
    free(del);
    return retval;
  }
  else {
    node_t *temp;
    temp = l->head;
    int i;
    for (i = 0; i < index-1; i++) {
      if (temp != NULL) {
        temp = temp->next;
      }
    }
    if (temp != NULL && temp->next != NULL) {
      node_t *del = temp->next;
      retval = temp->next->value;
      temp->next = temp->next->next;
      free(del);
      return retval;
    }
    else {
      return retval;
    }
  }
}

bool list_is_in(list_t *l, elem value) {
  node_t * curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}


elem list_get_elem_at(list_t *l, int index) {
  node_t * curr = l->head; 
  int i = 0;
  while (curr != NULL) {
    if (i == index) {
      return curr->value;
    }
    i++;
    curr = curr->next;
  }
  return -1;
}

int list_get_index_of(list_t *l, elem value) {
  int retval;
  node_t * curr;
  retval = 0;
  curr = l->head;
  while (curr != NULL && curr->value != value) {
    retval++;
    curr = curr->next;
  }
  return (curr != NULL) ? retval : -1;
}
