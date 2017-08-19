#include <stdio.h>
#include <math.h>

#define MAX_CHILD_NODE	64
typedef struct node {
	struct			node * child[MAX_CHILD_NODE];
	float			W[MAX_CHILD_NODE]; // Weights
	float			sig;
	char	index;
}st_node, *pst_node;

static st_node	nodeStack[256];

void comput() {
	for (pst_node this = &nodeStack[0]; this->index>=0; this++) {
		if (this->index) {
			this->sig = 0; // Clean signal
			for (unsigned int n = 0; n < this->index; n++) {
				this->sig += this->child[n]->sig * this->W[n];
			}
			this->sig = (float)tanh(this->sig);
		}
	}
}

// Actually, this function is going to create a sigle layer network
void createNetwork(
	unsigned int layer1,
	unsigned int layer2
) {
	for (unsigned int i = layer1; i < layer1+layer2; i++) {
		for (unsigned int ii = 0; ii < layer1; ii++) {
			nodeStack[i].child[ii] = &nodeStack[ii];
			nodeStack[i].index++;
		}
	}
	// set flag
	nodeStack[layer1+layer2].index = -1;

	// set input source node
	for (unsigned int i = 0; i < layer1; i++) {
		nodeStack[i].sig = 0.1;
	}
}

void setDNA(float *weights) {
	for (pst_node this = &nodeStack[0]; this->index>=0; this++) {
		for (unsigned char i = 0; i < this->index; i++) {
			this->W[i] = *weights++;
		}
	}
}
void getDNA(float *weights) {
	for (pst_node this = &nodeStack[0]; this->index>=0; this++) {
		for (unsigned char i = 0; i < this->index; i++) {
			*weights++ = this->W[i];
		}
	}
}

void console(pst_node n, unsigned char times) {
	for (unsigned char i = 0; i < times; i++,n++) {
		printf("Node %d - 0x%08x\t%d\t%f\n", i, (unsigned int)n, n->index, n->sig);
		for (unsigned char i = 0; i < n->index; i++) {
			printf("%f - ", n->W[i]);
		}
		printf("\n");
	}
}
float dna[] = {
	0.1, 0.2, 0.3, 0.4, 0.5, 0.1, 0.2, 0.3, 0.4, 0.5,
	0.1, 0.2, 0.3, 0.4, 0.5, 0.1, 0.2, 0.3, 0.4, 0.5,
	0.1, 0.2, 0.3, 0.4, 0.5, 0.1, 0.2, 0.3, 0.4, 0.5,
	0.1, 0.2, 0.3, 0.4, 0.5, 0.1, 0.2, 0.3, 0.4, 0.5,
	0.1, 0.2, 0.3, 0.4, 0.5, 0.1, 0.2, 0.3, 0.4, 0.5,
};
int main(int argc, char const *argv[]) {
	createNetwork(10, 5);
	setDNA(dna);
	comput();
	console(&nodeStack[0], 15);
	return 0;
}