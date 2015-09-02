#ifndef _LAST_H_
#define _LAST_H_

enum node_type {
    NODE_VALUE,
    NODE_IF,
    NODE_FOR
};

typedef struct node{
    enum node_type nt;

}node;

#endif /*_LAST_H_*/
