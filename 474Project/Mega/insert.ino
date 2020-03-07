// Insert function
//
//This function was written by a former TA for this course named J.D. Olsen
//
// Arguments: Pointer to TCB node
// Returns: void
// Function: Adds the TCB node to the end of the list and updates head and tail pointers
// This function assumes that head and tail pointers have already been created
// and are global and that the pointers contained in the TCB node have already been initialized to NULL
// This function also assumes that the “previous” and “next” pointers in the TCB node are called “prev”
// and “next” respectively
void insert(TCB* node)
{
 if(NULL == head) // If the head pointer is pointing to nothing
 {
 head = node; // set the head and tail pointers to point to this node
 tail = node;
 }
else // otherwise, head is not NULL, add the node to the end of the list
{
 tail -> next = node;
 node -> prev = tail; // note that the tail pointer is still pointing
 // to the prior last node at this point
 tail = node; // update the tail pointer
}
 return;
} 
