//Takes a tcb node, and removes it from the head of the list
//This function only operates propperly if the given node is at the head of the list
//PARAMS:
//tcb node: the node to be removed from the list
void removeHead(TCB* node) {
  head = node -> next; //change the front
  node -> next = NULL; // remove the front pointer of this node
  head -> prev = NULL;
}
