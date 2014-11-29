#ifndef MIS_OPERLIST_H
#define MIS_OPERLIST_H

typedef struct OperNode OperNode;

typedef struct OperNode {
	void* target;
	void (*operFunc) (void*);
	OperNode* prevNode;
	OperNode* nextNode; }
OperNode;

typedef struct OperList {
	OperNode* head;
	OperNode* tail; }
OperList;

void initOperNode(OperNode* node);
void initOperList(OperList* list);
void execOperList(OperList* list);
void addOperNode(OperNode* node, OperList* list);
void rmvOperNode(OperNode* node, OperList* list);

#endif
