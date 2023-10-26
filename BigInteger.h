#ifndef BIGINT_H
#define BIGINT_H
#include<stdio.h>
#include<string.h>
#include<malloc.h>

struct node
{
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *L;
    int length;
};


struct BigInteger initialize(char *s);

struct BigInteger rev(struct BigInteger);

struct BigInteger add(struct BigInteger, struct BigInteger);

struct BigInteger sub(struct BigInteger, struct BigInteger);

struct BigInteger mul(struct BigInteger, struct BigInteger);

struct BigInteger div1(struct BigInteger, struct BigInteger);

struct BigInteger mod(struct BigInteger, struct BigInteger);

struct node* addition(struct node *, int);

struct BigInteger length(struct BigInteger);

void compare(struct BigInteger*, struct BigInteger*);

int comp(struct BigInteger, struct BigInteger);

void free_list(struct node *);

void display(struct BigInteger);

struct BigInteger remove1(struct BigInteger a);


#endif