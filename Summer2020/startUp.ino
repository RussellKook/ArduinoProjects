void startUp() {

  //declare TCBs
  TCB LineFollower;
  TCB FreeRoam;

  //declare struct for data
  lineFollowerDataStruct lineFollowerData;
  freeRoamDataStruct freeRoamData;
  
  //assign dataPtr in TCB to void data structs
  LineFollower.dataPtr = (void*)&lineFollowerData;
  FreeRoam.dataPtr = (void*)&freeRoamData;
  
  //assign task* to corresponding method
  LineFollower.task = lineFollower;
  FreeRoam.task = freeRoam;

  //assign pointeres to null
  LineFollower.next = NULL;
  FreeRoam.next = NULL;
  head = NULL;
  LineFollower.prev = NULL;
  FreeRoam.prev = NULL;
  tail = NULL;

  //assign TCB pointers to TCBs
  freeRoamTask = &FreeRoam;
  lineFollowerTask = &LineFollower;
  insert(NULL);
  
}
