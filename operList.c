#include "operList.h"
#include <stdio.h>

void initOperNode(OperNode* node) {
	node->target = NULL;
	node->operFunc = NULL;
	node->prevNode = NULL;
	node->nextNode = NULL; }

void initOperList(OperList* list) {
	list->head = NULL;
	list->tail = NULL; }

void execOperList(OperList* list) {
	OperNode* node = list->head;
	while (node != NULL) {
		node->operFunc(node->target);
		node = node->nextNode; } }

void addOperNode(OperNode* node, OperList* list) {
	if (list->head == NULL)
		list->head = list->tail = node;
	else {
		node->prevNode = list->tail;
		list->tail->nextNode = node;
		list->tail = node; } }
// What if: attempt to add same node twice

void rmvOperNode(OperNode* node, OperList* list) {
	if (node == list->head) {
		list->head = node->nextNode;
		if (list->head != NULL)
			list->head->prevNode = NULL; }
	else
		node->prevNode->nextNode = node->nextNode;
	if (node == list->tail) {
		list->tail = node->prevNode;
		if (list->tail != NULL)
			list->tail->nextNode = NULL; }
	else
		node->nextNode->prevNode = node->prevNode;
	node->prevNode = node->nextNode = NULL; }
// What if: attempt to remove nonexistent node
