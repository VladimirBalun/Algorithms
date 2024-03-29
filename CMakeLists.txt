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
add_executable (BresenhamsLine ./ComputationalGeometry/BresenhamsLine.cpp)
add_executable (RamerDouglasPeucker ./ComputationalGeometry/RamerDouglasPeucker.cpp)
add_executable (ScanLineMethod ./ComputationalGeometry/ScanLineMethod.cpp)
set_target_properties (BresenhamsLine RamerDouglasPeucker ScanLineMethod PROPERTIES FOLDER "ComputationalGeometry")

# Cryptography
add_executable (CaesarCipher ./Cryptography/CaesarCipher.cpp)
set_target_properties (CaesarCipher PROPERTIES FOLDER "Cryptography")

# Data structures
add_executable (AVLTree ./DataStructures/AVLTree.cpp)
add_executable (BinaryHeap ./DataStructures/BinaryHeap.cpp)
add_executable (BinaryTree ./DataStructures/BinaryTree.cpp)
add_executable (CircularBuffer ./DataStructures/CircularBuffer.cpp)
add_executable (DisjointSetUnion ./DataStructures/DisjointSetUnion.cpp)
add_executable (HashTableWithOpenAddressing ./DataStructures/HashTableWithOpenAddressing.cpp)
add_executable (HashTableWithSeparateChaining ./DataStructures/HashTableWithSeparateChaining.cpp)
add_executable (LinkedList ./DataStructures/LinkedList.cpp)
add_executable (InvertedIndex ./DataStructures/InvertedIndex.cpp)
add_executable (PrefixTree ./DataStructures/PrefixTree.cpp)
add_executable (Queue ./DataStructures/Queue.cpp)
add_executable (SegmentTree ./DataStructures/SegmentTree.cpp)
add_executable (Stack ./DataStructures/Stack.cpp)
add_executable (XORLinkedList ./DataStructures/XORLinkedList.cpp)
set_target_properties (AVLTree BinaryHeap BinaryTree DisjointSetUnion HashTableWithOpenAddressing HashTableWithSeparateChaining LinkedList InvertedIndex PrefixTree Queue SegmentTree Stack XORLinkedList PROPERTIES FOLDER "DataStructures")

# Dynamic programming
add_executable (Fibonacci ./DynamicProgramming/Fibonacci.cpp)
add_executable (ExchangeOfCoins ./DynamicProgramming/ExchangeOfCoins.cpp)
set_target_properties (ExchangeOfCoins Fibonacci PROPERTIES FOLDER "DynamicProgramming")

# Graphs
add_executable (BFS ./Graphs/BFS.cpp)
add_executable (Dijkstra ./Graphs/Dijkstra.cpp)
add_executable (DFS ./Graphs/DFS.cpp)
add_executable (TopologicalSort ./Graphs/TopologicalSort.cpp)
set_target_properties (BFS Dijkstra DFS TopologicalSort PROPERTIES FOLDER "Graphs")

# Multithreading
add_executable (PingPong ./Multithreading/PingPong.cpp)
add_executable (ProducerAndConsumer ./Multithreading/ProducerAndConsumer.cpp)
target_link_libraries (PingPong -pthread)
target_link_libraries (ProducerAndConsumer -pthread)
set_target_properties (PingPong ProducerAndConsumer PROPERTIES FOLDER "Multithreading")

# Others
add_executable (EuclideanAlgorithm ./Others/EuclideanAlgorithm.cpp)
add_executable (EratosthenesSieve ./Others/EratosthenesSieve.cpp)
add_executable (ReversalForwardList ./Others/ReversalForwardList.cpp)
add_executable (MaximumAmoundOfSubarrays ./Others/MaximumAmoundOfSubarrays.cpp)
add_executable (MatrixReverseDiagonals ./Others/MatrixReverseDiagonals.cpp)
add_executable (MaximumPathsNumber ./Others/MaximumPathsNumber.cpp)
add_executable (TomSawyerSence ./Others/TomSawyerSence.cpp)
add_executable (QueensPuzzle ./Others/QueensPuzzle.cpp)                                                           
set_target_properties (EuclideanAlgorithm EratosthenesSieve ReversalForwardList MatrixReverseDiagonals MaximumAmoundOfSubarrays MaximumPathsNumber TomSawyerSence QueensPuzzle PROPERTIES FOLDER "Others")

# Search
add_executable (BinarySearch ./Search/BinarySearch.cpp)
add_executable (LinearSearch ./Search/LinearSearch.cpp)
add_executable (TernarySearch ./Search/TernarySearch.cpp)
set_target_properties (BinarySearch LinearSearch TernarySearch PROPERTIES FOLDER "Search")

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
set_target_properties (AutoPtr SharedPtr UniquePtr PROPERTIES FOLDER "SmartPointers")

# Sorting
add_executable (BubbleSorting ./Sorting/BubbleSorting.cpp)
add_executable (BucketSorting ./Sorting/BucketSorting.cpp)
add_executable (CountingSorting ./Sorting/CountingSorting.cpp)
add_executable (InsertionSorting ./Sorting/InsertionSorting.cpp)
add_executable (MergeSorting ./Sorting/MergeSorting.cpp)
add_executable (QuickSorting ./Sorting/QuickSorting.cpp)
add_executable (SelectionSorting ./Sorting/SelectionSorting.cpp)
add_executable (ShellSorting ./Sorting/ShellSorting.cpp)
add_executable (StupidSorting ./Sorting/StupidSorting.cpp)
set_target_properties (BubbleSorting BucketSorting CountingSorting InsertionSorting MergeSorting QuickSorting SelectionSorting ShellSorting StupidSorting PROPERTIES FOLDER "Sorting")
