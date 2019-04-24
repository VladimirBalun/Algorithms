cmake_minimum_required (VERSION 3.8)

project (Algorithms)

set (CMAKE_CXX_STANDARD 17)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)
 
# Allocators
add_executable (LinearAllocator ./Allocators/LinearAllocator.cpp)
add_executable (PoolAllocator ./Allocators/PoolAllocator.cpp)
set_target_properties (LinearAllocator PoolAllocator PROPERTIES FOLDER "Allocators")

# Caching
add_executable (FIFO ./Caching/FIFO.cpp)
add_executable (LRU ./Caching/LRU.cpp)
set_target_properties (FIFO LRU PROPERTIES FOLDER "Caching")

# ComputationalGeometry
add_executable (RamerDouglasPeucker ./ComputationalGeometry/RamerDouglasPeucker.cpp)
set_target_properties (RamerDouglasPeucker PROPERTIES FOLDER "ComputationalGeometry")

# Cryptography
add_executable (CaesarCipher ./Cryptography/CaesarCipher.cpp)
set_target_properties (CaesarCipher PROPERTIES FOLDER "Cryptography")

# Data structures
add_executable (BinaryHeap ./DataStructures/BinaryHeap.cpp)
add_executable (BinaryTree ./DataStructures/BinaryTree.cpp)
add_executable (LinkedList ./DataStructures/LinkedList.cpp)
add_executable (Queue ./DataStructures/Queue.cpp)
add_executable (Stack ./DataStructures/Stack.cpp)
set_target_properties (BinaryHeap BinaryTree LinkedList Queue Stack PROPERTIES FOLDER "DataStructures")

# Graphs
add_executable (BFS ./Graphs/BFS.cpp)
add_executable (DFS ./Graphs/DFS.cpp)
set_target_properties (BFS DFS PROPERTIES FOLDER "Graphs")

# Multithreading
add_executable (PingPong ./Multithreading/PingPong.cpp)
add_executable (ProducerAndConsumer ./Multithreading/ProducerAndConsumer.cpp)
set_target_properties (PingPong ProducerAndConsumer PROPERTIES FOLDER "Multithreading")

# Other
add_executable (QueensPuzzle ./Other/QueensPuzzle.cpp)
set_target_properties (QueensPuzzle PROPERTIES FOLDER "Other")

# Search
add_executable (BinarySearch ./Search/BinarySearch.cpp)
add_executable (LinearSearch ./Search/LinearSearch.cpp)
set_target_properties (BinarySearch LinearSearch PROPERTIES FOLDER "Search")

# Set operations
add_executable (DifferenceBetweenOrderedSets ./SetOperations/DifferenceBetweenOrderedSets.cpp)
add_executable (GenerationOfAllPermutationsFromSet ./SetOperations/GenerationOfAllPermutationsFromSet.cpp)
add_executable (GenerationOfAllSubsetsOfTheSet ./SetOperations/GenerationOfAllSubsetsOfTheSet.cpp)
add_executable (IntersectionOfTheOrderedSets ./SetOperations/IntersectionOfTheOrderedSets.cpp)
add_executable (SymmetricDifferenceOfOrderedSets  ./SetOperations/SymmetricDifferenceOfOrderedSets.cpp)
add_executable (UnionOfTheOrderedSets ./SetOperations/UnionOfTheOrderedSets.cpp)
set_target_properties (DifferenceBetweenOrderedSets GenerationOfAllPermutationsFromSet GenerationOfAllSubsetsOfTheSet IntersectionOfTheOrderedSets SymmetricDifferenceOfOrderedSets UnionOfTheOrderedSets PROPERTIES FOLDER "SetOperations")

# Smart pointers
add_executable (AutoPtr ./SmartPointers/AutoPtr.cpp)
add_executable (SharedPtr ./SmartPointers/SharedPtr.cpp)
add_executable (UniquePtr ./SmartPointers/UniquePtr.cpp)
set_target_properties (AutoPtr SharedPtr UniquePtr PROPERTIES FOLDER "SmartPinters")

# Sorting
add_executable (BubbleSorting ./Sorting/BubbleSorting.cpp)
add_executable (InsertionSorting ./Sorting/InsertionSorting.cpp)
add_executable (MergeSorting ./Sorting/MergeSorting.cpp)
add_executable (QuickSorting ./Sorting/QuickSorting.cpp)
add_executable (SelectionSorting ./Sorting/SelectionSorting.cpp)
add_executable (ShellSorting ./Sorting/ShellSorting.cpp)
add_executable (StupidSorting ./Sorting/StupidSorting.cpp)
set_target_properties (BubbleSorting InsertionSorting MergeSorting QuickSorting SelectionSorting ShellSorting StupidSorting PROPERTIES FOLDER "Sorting")
