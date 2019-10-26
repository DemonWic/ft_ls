#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
  /* print use instruction unless a folder name was given */
  if (argc < 2)
    fprintf(stderr,
            "\nuse:\n"
            "    %s <directory>\n"
            "for example:\n"
            "    %s ./\n\n",
            argv[0], argv[0]),
        exit(0);

  /*************** a small linked list macro implementation ***************/

  typedef struct list_s {
    struct list_s *next;
    struct list_s *prev;
  } list_s;

#define LIST_INIT(name)                                                        \
  { .next = &name, .prev = &name }

#define LIST_PUSH(dest, node)                                                  \
  do {                                                                         \
    (node)->next = (dest)->next;                                               \
    (node)->prev = (dest);                                                     \
    (node)->next->prev = (node);                                               \
    (dest)->next = (node);                                                     \
  } while (0);

#define LIST_POP(list, var)                                                    \
  if ((list)->next == (list)) {                                                \
    var = NULL;                                                                \
  } else {                                                                     \
    var = (list)->next;                                                        \
    (list)->next = var->next;                                                  \
    var->next->prev = var->prev;                                               \
  }

  /*************** a record (file / folder) item type ***************/

  typedef struct record_s {
    /* this is a flat processing queue. */
    list_s queue;
    /* this will list all the completed items (siblings and such) */
    list_s list;
    /* unique ID */
    ino_t ino;
    /* name length */
    size_t len;
    /* name string */
    char name[];
  } record_s;

/* take a list_s pointer and convert it to the record_s pointer */
#define NODE2RECORD(node, list_name)                                           \
  ((record_s *)(((uintptr_t)(node)) -                                          \
                ((uintptr_t) & ((record_s *)0)->list_name)))

/* initializes a new record */
#define RECORD_INIT(name)                                                      \
  (record_s){.queue = LIST_INIT((name).queue), .list = LIST_INIT((name).list)}

  /*************** the actual code ***************/

  record_s records = RECORD_INIT(records);
  record_s *pos, *item;
  list_s *tmp;
  DIR *dir;
  struct dirent *entry;

  /* initialize the root folder record and add it to the queue */
  pos = malloc(sizeof(*pos) + strlen(argv[1]) + 2);
  *pos = RECORD_INIT(*pos);
  pos->len = strlen(argv[1]);
  memcpy(pos->name, argv[1], pos->len);
  if (pos->name[pos->len - 1] != '/')
    pos->name[pos->len++] = '/';
  pos->name[pos->len] = 0;
  /* push to queue, but also push to list (first item processed) */
  LIST_PUSH(&records.queue, &pos->queue);
  LIST_PUSH(&records.list, &pos->list);

  /* as long as the queue has items to be processed, do so */
  while (records.queue.next != &records.queue) {
    /* pop queued item */
    LIST_POP(&records.queue, tmp);
    /* collect record to process */
    pos = NODE2RECORD(tmp, queue);

    /* process the folder and add all folder data to current list */
    dir = opendir(pos->name);
    if (!dir)
      continue;

    while ((entry = readdir(dir)) != NULL) {

      /* create new item, copying it path data and unique ID */
      item = malloc(sizeof(*item) + pos->len + strlen(entry->d_name) + 2);
      *item = RECORD_INIT(*item);
      item->len = pos->len + strlen(entry->d_name);
      memcpy(item->name, pos->name, pos->len);
      memcpy(item->name + pos->len, entry->d_name, strlen(entry->d_name));
      item->name[item->len] = 0;
      item->ino = entry->d_ino;
      /* add item to the list, right after the `pos` item */
      LIST_PUSH(&pos->list, &item->list);

      /* unless it a folder, we're done. */
      if (entry->d_type != DT_DIR)
        continue;

      /* test for '.' and '..' */
      if (entry->d_name[0] == '.' &&
          (entry->d_name[1] == 0 ||
           (entry->d_name[1] == '.' && entry->d_name[2] == 0)))
        continue;

      /* add folder marker */
      item->name[item->len++] = '/';
      item->name[item->len] = 0;

      /* item is a new folder, add to queue */
      LIST_PUSH(&records.queue, &item->queue);
    }
    closedir(dir);
  }

  /*************** Printing the results and cleaning up ***************/
  while (records.list.next != &records.list) {
    /* pop list item */
    LIST_POP(&records.list, tmp);
    /* collect record to process */
    pos = NODE2RECORD(tmp, list);
    /* prepare for next iteration */
    LIST_POP(&records.list, tmp);
    fwrite(pos->name, pos->len, 1, stderr);
    fwrite("\n", 1, 1, stderr);
    free(pos);
  }
  return 0;
}