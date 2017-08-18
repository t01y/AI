#include <stdio.h>
#include <math.h>

#define MAX_CHILD_NODE	10
typedef struct node {
	unsigned char	index;
	struct			node * child[MAX_CHILD_NODE];
	float			W[MAX_CHILD_NODE];
	float			sig;
}st_node, *pst_node;

void computSingleNode(st_node *this) {
	for (unsigned int i = 0; i < this->index; i++) {
		this->sig += this->child[i]->sig * this->W[i];
	}
	this->sig = (float)tanh(this->sig);
}

static st_node	nodeStack[256];
static long		sp = -1;

void test() {
	// Create some nodes
	pst_node	node1 = &nodeStack[++sp];
	pst_node	node2 = &nodeStack[++sp];
	pst_node	node3 = &nodeStack[++sp];

	// Add childs
	node1->child[0] = node2;
	node1->index++;
	node1->child[1] = node3;
	node1->index++;

	// Setup
	node1->W[0] = 1;
	node1->W[1] = 0.3;

	node2->sig = 1;
	node3->sig = 1.5;
}

void console(pst_node n) {
	printf("\n%d\n%f\n\n", n->index, n->sig);
}

int main(int argc, char const *argv[]) {
	test();
	computSingleNode(&nodeStack[0]);
	console(&nodeStack[0]);
	return 0;
}